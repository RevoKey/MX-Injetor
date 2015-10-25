/*
* CoreMX.IO
*
* Este arquivo faz parte do projeto MX-Injetor.
*
* Fórum: http://coremx.io
* Facebook: https://www.facebook.com/coremx.io
* GitHub: https://github.com/NoxxDev/MX-Injetor
*/

#pragma once

namespace Process
{
	int GetPID(const char *ProcName);
	DWORD GetModuleInfo(DWORD dwProcessIdentifier, TCHAR *lpszModuleName);
	bool Inject(unsigned int ProcessID, const char *ModulePath);
}