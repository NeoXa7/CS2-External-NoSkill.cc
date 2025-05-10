#pragma once
#include <globals/imports.h>

class Process {
public:
    Process() {}
    ~Process() {}

    Process(const Process&) = delete;
    Process& operator=(const Process&) = delete;

public:
    // Get process id by name
    uintptr_t GetProcessID(const char* process_name)
    {
        DWORD procId = 0;
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnap != INVALID_HANDLE_VALUE) {
            PROCESSENTRY32W procEntry;
            procEntry.dwSize = sizeof(procEntry);

            if (Process32FirstW(hSnap, &procEntry)) {
                do {
                    if (!_wcsicmp(procEntry.szExeFile, (const wchar_t*)process_name)) {
                        procId = procEntry.th32ProcessID;
                        break;
                    }
                } while (Process32NextW(hSnap, &procEntry));
            }
        }
        CloseHandle(hSnap);
        return procId;
    }

    // Get base address of a process
    uintptr_t GetModuleBaseAddress(DWORD processId, const wchar_t* ModuleTarget)
    {
        HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
        if (snapshotHandle == INVALID_HANDLE_VALUE) {
            return NULL;
        }
        MODULEENTRY32W moduleEntry = { };
        moduleEntry.dwSize = sizeof(MODULEENTRY32W);

        if (Module32FirstW(snapshotHandle, &moduleEntry)) {

            do {

                if (_wcsicmp(moduleEntry.szModule, ModuleTarget) == 0) {
                    CloseHandle(snapshotHandle);
                    return reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
                }
            } while (Module32NextW(snapshotHandle, &moduleEntry));
        }
        CloseHandle(snapshotHandle);
        return NULL;
    }

    // To check if the window process is focused or not
    bool InForeground(const std::string& window_name)
    {
        HWND current = GetForegroundWindow();
        char title[256] = { 0 };
        if (GetWindowTextA(current, title, sizeof(title))) {
            return std::string(title).find(window_name) != std::string::npos;
        }

        return false;
    }

    // To check if the process is opened or not (returns true or false)
    bool ProcessIsOpen(const char* process_name)
    {
        return GetProcessID(process_name) != 0;
    }
}; 

