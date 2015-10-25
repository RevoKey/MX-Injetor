/*
* CoreMX.IO
*
* Este arquivo faz parte do projeto MX-Injetor.
*
* Fórum: http://coremx.io
* Facebook: https://www.facebook.com/coremx.io
* GitHub: https://github.com/NoxxDev/MX-Injetor
*/

#include "Misc\stdafx.h"
#include "Main\GUI.h"

int __stdcall WinMain(HINSTANCE Instance, HINSTANCE PreviousInstance, char* CommandLine, int ShowCommand)
{
	GUI::Create(Instance);
	return 0;
}