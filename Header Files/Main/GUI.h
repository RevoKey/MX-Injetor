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

namespace GUI
{
	extern std::string ModulePath;
	extern std::string ModuleName;

	extern HWND MainWindow;
	extern HWND StateLabel;
	extern HWND SelectModuleButton;
	extern UINT Timer;

	void __stdcall Create(HINSTANCE Instance);
	long __stdcall MainUIProc(HWND Window, unsigned int Message, WPARAM wParam, LPARAM lParam);
	void __stdcall CommandHandler(unsigned int Command, unsigned int High);
}