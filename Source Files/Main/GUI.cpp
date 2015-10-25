#include "Misc\stdafx.h"
#include "Main\GUI.h"
#include "Main\EventTimer.h"

namespace GUI
{
	std::string ModulePath;
	std::string ModuleName;

	HWND MainWindow;
	HWND StateLabel;
	HWND SelectModuleButton;
	UINT Timer;

	void __stdcall Create(HINSTANCE Instance)
	{
		WNDCLASSEX WPClass;
		ZeroMemory(&WPClass, sizeof(WNDCLASSEX));

		MSG Message;
		WPClass.cbSize = sizeof(WNDCLASSEX);
		WPClass.lpfnWndProc = GUI::MainUIProc;
		WPClass.hInstance = Instance;
		WPClass.hCursor = LoadCursor(0, IDC_ARROW);
		WPClass.hIcon = LoadIcon(Instance, MAKEINTRESOURCE(IDI_ICON));
		WPClass.hIconSm = LoadIcon(Instance, MAKEINTRESOURCE(IDI_ICON));
		WPClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		WPClass.lpszClassName = "MX-Injetor";
		RegisterClassEx(&WPClass);

		MainWindow = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			"MX-Injetor",
			"MX-Injetor",
			WS_SYSMENU,
			CW_USEDEFAULT, CW_USEDEFAULT, 250, 120,
			nullptr, nullptr, Instance, nullptr);

		UpdateWindow(MainWindow);
		ShowWindow(MainWindow, SW_SHOW);

		while (GetMessage(&Message, 0, 0, 0) > 0)
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}

		return;
	}

	long __stdcall MainUIProc(HWND Window, unsigned int Message, WPARAM wParam, LPARAM lParam)
	{
		try
		{
			switch (Message)
			{
			case WM_CREATE:
				Timer = SetTimer(Window, 1, 10, NULL);

				StateLabel = CreateWindowEx(0, "Static", "Nenhuma dll selecionada!",
					WS_CHILD | WS_VISIBLE | SS_CENTER,
					0, 15, 240, 15, Window, nullptr, nullptr, nullptr);
				SendMessage(StateLabel, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
				SelectModuleButton = CreateWindowEx(0, "button", "Selecionar Dll",
					WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
					10, 40, 210, 25, Window, reinterpret_cast<HMENU>(2), nullptr, nullptr);
				SendMessage(SelectModuleButton, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
				break;

			case WM_COMMAND:
				CommandHandler(LOWORD(wParam), HIWORD(wParam));
				break;
			case WM_TIMER:
				switch (LOWORD(wParam), wParam)
				{
				case 1:
					EventTimer::Pulse();
					return 0;
				}
				return 0;
			case WM_CLOSE:
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			}
		}
		catch (std::exception ex)
		{
			char* Exception = new char[strlen(ex.what()) + 14];
			sprintf(Exception, "%s Erro: %d", ex.what(), GetLastError());

			MessageBox(Window, Exception, nullptr, MB_OK);
		}

		return DefWindowProc(Window, Message, wParam, lParam);
	}

	void __stdcall CommandHandler(unsigned int Command, unsigned int High)
	{
		switch (Command)
		{
		case 2:
		{
			char File[MAX_PATH] = { 0 };

			OPENFILENAME OpenFileName;
			ZeroMemory(&OpenFileName, sizeof(OpenFileName));

			OpenFileName.hwndOwner = MainWindow;
			OpenFileName.lpstrFilter = "*.dll\0*.dll\0";
			OpenFileName.nFilterIndex = 1;
			OpenFileName.lpstrFile = File;
			OpenFileName.nMaxFile = MAX_PATH;
			OpenFileName.lpstrTitle = "Selecione a Dll";
			OpenFileName.nFileExtension = 2;
			OpenFileName.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			OpenFileName.lStructSize = sizeof(OPENFILENAME);

			if (GetOpenFileName(&OpenFileName) == 0)
			{
				return;
			}

			ModulePath.clear();
			ModulePath.append(File);
			PathStripPath(File);
			ModuleName.clear();
			ModuleName.append(File);
			break;
		}
		default:
			break;
		}

		std::string NewSelectedText;

		if (ModuleName.length() > 4)
			NewSelectedText.append(ModuleName);
		else
			NewSelectedText.append("Nenhuma dll selecionada!");

		SendMessage(StateLabel, WM_SETTEXT, 0, reinterpret_cast<LPARAM>(NewSelectedText.c_str()));

		return;
	}
}