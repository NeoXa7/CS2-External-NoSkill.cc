#pragma once
#include <globals/imports.h>
#include <globals/defs.h>
#include <utils/process.h>
#include <globals/utils.h>

typedef NTSTATUS(__stdcall* pNtReadVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesRead);
typedef NTSTATUS(__stdcall* pNtWriteVirtualMemory)(HANDLE Processhandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToWrite, PULONG NumberOfBytesWritten);

class Memory {
private:
	HANDLE ProcessHandle = 0;
	uintptr_t ProcessID = 0;

    pNtReadVirtualMemory VRead = nullptr;
    pNtWriteVirtualMemory VWrite = nullptr;

public:
    Memory(const wchar_t* process_name)
    {
        HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
        if (!hNtdll)
        {
            std::cerr << "Failed to get handle to ntdll.dll\n";
            return;
        }

        this->VRead = (pNtReadVirtualMemory)GetProcAddress(hNtdll, "NtReadVirtualMemory");
        this->VWrite = (pNtWriteVirtualMemory)GetProcAddress(hNtdll, "NtWriteVirtualMemory");

        if (!this->VRead || !this->VWrite)
        {
            std::cerr << "Failed to get NtRead/WriteVirtualMemory addresses.\n";
            return;
        }

        this->ProcessID = Instance<Process>::Get().GetProcessID(process_name);

        if (this->ProcessID != NULL)
            this->ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->ProcessID);
        else
            std::cout << "Memory-Class : Handle to the process not found.\n";
    }

    ~Memory()
    {
        if (this->ProcessHandle != NULL)
        {
            CloseHandle(this->ProcessHandle);
        }
    }

    HANDLE GetProcessHandle()
    {
        return this->ProcessHandle;
    }

    template <typename T>
    T Read(uintptr_t address)
    {
        T buffer{ };
        this->VRead(this->ProcessHandle, (void*)address, &buffer, sizeof(T), 0);
        return buffer;
    }

    template <typename T>
    T Write(uintptr_t address)
    {
        T buffer{ };
        this->VWrite(this->ProcessHandle, (void*)address, &buffer, sizeof(T), 0);
        return buffer;
    }

    template <typename T>
    bool ReadRaw(uintptr_t address, void* buffer, size_t size)
    {
        SIZE_T bytesRead;
        if (VRead(this->ProcessHandle, (void*)address, buffer, static_cast<ULONG>(size), (PULONG)&bytesRead))
            return bytesRead = size;

        return false;
    }

    uintptr_t FindPattern(MODULEENTRY32 module, uint8_t* arr, const char* pattern, int offset, int extra) {
        uintptr_t scan = 0x0;
        const char* pat = pattern;
        uintptr_t firstMatch = 0;
        for (uintptr_t pCur = (uintptr_t)arr; pCur < (uintptr_t)arr + module.modBaseSize; ++pCur) {
            if (!*pat) { scan = firstMatch; break; }
            if (*(uint8_t*)pat == '\?' || *(uint8_t*)pCur == ((((pat[0] & (~0x20)) >= 'A' && (pat[0] & (~0x20)) <= 'F') ? ((pat[0] & (~0x20)) - 'A' + 0xa) : ((pat[0] >= '0' && pat[0] <= '9') ? pat[0] - '0' : 0)) << 4 | (((pat[1] & (~0x20)) >= 'A' && (pat[1] & (~0x20)) <= 'F') ? ((pat[1] & (~0x20)) - 'A' + 0xa) : ((pat[1] >= '0' && pat[1] <= '9') ? pat[1] - '0' : 0)))) {
                if (!firstMatch) firstMatch = pCur;
                if (!pat[2]) { scan = firstMatch; break; }
                if (*(WORD*)pat == 16191 /*??*/ || *(uint8_t*)pat != '\?') pat += 3;
                else pat += 2;
            }
            else { pat = pattern; firstMatch = 0; }
        }
        if (!scan) return 0x0;
        uint32_t read;
        ReadProcessMemory(this->ProcessHandle, (void*)(scan - (uintptr_t)arr + (uintptr_t)module.modBaseAddr + offset), &read, sizeof(read), NULL);
        return read + extra;
    }
};