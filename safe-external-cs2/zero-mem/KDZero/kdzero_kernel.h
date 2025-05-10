#pragma once
#include <globals/imports.h>

typedef struct _NULL_MEMORY
{
	void* buffer_address;
	UINT_PTR address;
	ULONGLONG size;
	ULONG pid;
	BOOLEAN write;
	BOOLEAN read;
	BOOLEAN req_base;
	BOOLEAN draw_box;
	int		r, g, b, x, y, w, h, t;
	void* output;
	const char* module_name;
	ULONG64 base_address;
}NULL_MEMORY;

struct HandleDisposer
{
	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};

template<typename ... Arg>
uint64_t CallHook(const Arg ... args)
{
	void* hooked_func = GetProcAddress(LoadLibrary("win32u.dll"), "NtDxgkGetTrackedWorkloadStatistics");

	auto func = static_cast<uint64_t(_stdcall*)(Arg...)>(hooked_func);

	return func(args ...);
}

inline bool IsDriverLoaded()
{
	NULL_MEMORY temp = { 0 };
	temp.read = false;
	temp.write = false;
	temp.req_base = false;

	// You can use a known good call — for example, check if it returns a specific expected value
	auto result = CallHook(&temp);

	// Based on your driver's behavior, determine the expected result
	return result != 0; // or whatever value your driver uses to signal success
}
