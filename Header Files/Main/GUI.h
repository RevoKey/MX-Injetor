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