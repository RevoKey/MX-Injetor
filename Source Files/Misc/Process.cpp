#include "Misc\stdafx.h"
#include "Misc\Process.h"

#define MAXPATH 1024

namespace Process
{
	int GetPID(const char * ProcName)
	{
		PROCESSENTRY32 pe;
		HANDLE thSnapShot;
		BOOL retval, ProcFound = false;

		thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		if (thSnapShot == INVALID_HANDLE_VALUE)
			return false;
		pe.dwSize = sizeof(PROCESSENTRY32);
		retval = Process32First(thSnapShot, &pe);
		while (retval)
		{
			if (StrStrI(pe.szExeFile, ProcName))
			{
				return pe.th32ProcessID;
			}
			retval = Process32Next(thSnapShot, &pe);
		}
		return 0;
	}

	DWORD GetModuleInfo(DWORD dwProcessIdentifier, TCHAR *lpszModuleName)
	{
		HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessIdentifier);
		DWORD dwModuleBaseAddress = 0;
		if (hSnapshot != INVALID_HANDLE_VALUE)
		{
			MODULEENTRY32 ModuleEntry32 = { 0 };
			ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
			if (Module32First(hSnapshot, &ModuleEntry32))
			{
				do
				{
					if (strcmp(ModuleEntry32.szModule, lpszModuleName) == 0)
					{
						dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
						break;
					}
				} while (Module32Next(hSnapshot, &ModuleEntry32));
			}
			CloseHandle(hSnapshot);
		}
		return dwModuleBaseAddress;
	}

	bool Inject(unsigned int ProcessID, const char* ModulePath)
	{
		void* Token = nullptr;
		TOKEN_PRIVILEGES Privileges;

		bool IsInjected = false;

		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, reinterpret_cast<void**>(&Token));

		Privileges.PrivilegeCount = 1;
		LookupPrivilegeValue(nullptr, "SeDebugPrivilege", &Privileges.Privileges[0].Luid);
		Privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(Token, 0, &Privileges, sizeof(Privileges), nullptr, nullptr);
		CloseHandle(Token);

		void* Handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);

		if (Handle != INVALID_HANDLE_VALUE)
		{
			void* LoadLibraryAddress = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
			void* RemoteString = VirtualAllocEx(Handle, nullptr, strlen(ModulePath) + 1, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
			if (WriteProcessMemory(Handle, RemoteString, ModulePath, strlen(ModulePath) + 1, nullptr))
				IsInjected = true;
			void* Thread = CreateRemoteThread(Handle, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryAddress), RemoteString, 0, nullptr);
			WaitForSingleObject(Thread, INFINITE);
			VirtualFreeEx(Handle, RemoteString, strlen(ModulePath) + 1, MEM_FREE);

			CloseHandle(Thread);
		}

		CloseHandle(Handle);

		return IsInjected;
	}
}