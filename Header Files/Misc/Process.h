#pragma once

namespace Process
{
	int GetPID(const char *ProcName);
	DWORD GetModuleInfo(DWORD dwProcessIdentifier, TCHAR *lpszModuleName);
	bool Inject(unsigned int ProcessID, const char *ModulePath);
}