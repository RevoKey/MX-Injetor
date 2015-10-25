#pragma once
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*'    publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <Windows.h>
#include <Psapi.h>
#include <Shlwapi.h>
#include <TlHelp32.h>
#include <exception>
#include <string>
#include <iostream>

#include "..\Resource Files\resource.h"

#pragma comment(lib, "Psapi.lib")
#pragma comment(lib, "Shlwapi.lib")

#define null 0
typedef unsigned char byte;