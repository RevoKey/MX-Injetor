#include "Misc\stdafx.h"
#include "Main\GUI.h"

int __stdcall WinMain(HINSTANCE Instance, HINSTANCE PreviousInstance, char* CommandLine, int ShowCommand)
{
	GUI::Create(Instance);
	return 0;
}