#pragma once
#include "kdzero_kernel.h"
#include "kprocess.h"
#include <globals/utils.h>

class KDZERO_MEMORY_MANAGER {
private:
	std::uint32_t ProcessID = 0;

public:

	KDZERO_MEMORY_MANAGER(const char* process_name) {
		this->ProcessID = Instance<KDZERO_PROCESS_MANAGER>::Get().GetProcessID(process_name);
	}

	template <class T>
	T Read(UINT_PTR read_address)
	{
		T response{};
		NULL_MEMORY instructions;
		instructions.pid = ProcessID;
		instructions.size = sizeof(T);
		instructions.address = read_address;
		instructions.read = TRUE;
		instructions.write = FALSE;
		instructions.req_base = FALSE;
		instructions.draw_box = FALSE;
		instructions.output = &response;
		CallHook(&instructions);

		return response;
	}

	bool ReadRaw(uintptr_t address, void* buffer, size_t size)
	{
		NULL_MEMORY instructions;
		instructions.pid = ProcessID;
		instructions.size = size;
		instructions.address = address;
		instructions.read = TRUE;
		instructions.write = FALSE;
		instructions.req_base = FALSE;
		instructions.draw_box = FALSE;
		instructions.output = buffer;
		CallHook(&instructions);

		return true;
	}


	bool WriteMemory(UINT_PTR write_address, UINT_PTR source_address, SIZE_T write_size)
	{
		NULL_MEMORY instructions;
		instructions.address = write_address;
		instructions.pid = this->ProcessID;
		instructions.write = TRUE;
		instructions.read = FALSE;
		instructions.req_base = FALSE;
		instructions.draw_box = FALSE;
		instructions.buffer_address = (void*)source_address;
		instructions.size = write_size;

		CallHook(&instructions);

		return true;
	}

	template<typename S>
	bool Write(UINT_PTR write_address, const S& value)
	{
		return WriteMemory(write_address, (UINT_PTR)&value, sizeof(S));
	}

	bool DrawBox(int x, int y, int w, int h, int t, int r, int g, int b)
	{
		NULL_MEMORY instructions;
		instructions.write = FALSE;
		instructions.read = FALSE;
		instructions.req_base = FALSE;
		instructions.draw_box = TRUE;

		instructions.x = x;
		instructions.y = y;
		instructions.w = w;
		instructions.h = h;
		instructions.t = t;

		instructions.r = r;
		instructions.g = g;
		instructions.b = b;

		CallHook(&instructions);

		return true;
	}
};