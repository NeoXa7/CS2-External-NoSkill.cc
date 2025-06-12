#pragma once
#include "kdzero_kernel.h"

class KDZERO_PROCESS_MANAGER {
private:
	using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

public:
	KDZERO_PROCESS_MANAGER() {}
	~KDZERO_PROCESS_MANAGER() {}

	KDZERO_PROCESS_MANAGER(const KDZERO_PROCESS_MANAGER&) = delete;
	KDZERO_PROCESS_MANAGER& operator=(const KDZERO_PROCESS_MANAGER&) = delete;


	std::uint32_t GetProcessID(std::string_view process_name)
	{
		PROCESSENTRY32 processentry;
		const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));

		if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
			return NULL;

		processentry.dwSize = sizeof(MODULEENTRY32);

		while (Process32Next(snapshot_handle.get(), &processentry) == TRUE)
		{
			if (process_name.compare(processentry.szExeFile) == NULL)
			{
				return processentry.th32ProcessID;
			}
		}
		return NULL;
	}

	ULONG64 GetModuleBaseAddress(const char* module_name, std::uint32_t process_id)
	{
		NULL_MEMORY instructions = { 0 };
		instructions.pid = process_id;
		instructions.req_base = TRUE;
		instructions.read = FALSE;
		instructions.write = FALSE;
		instructions.draw_box = FALSE;
		instructions.module_name = module_name;
		CallHook(&instructions);

		ULONG64 base = NULL;
		base = instructions.base_address;
		return base;
	}
};