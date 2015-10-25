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
#include "Misc\Process.h"
#include "Main\EventTimer.h"
#include "Main\GUI.h"

namespace EventTimer
{
	void __cdecl Pulse() try
	{
		if (GUI::ModulePath.length() != 0)
		{
			unsigned int PID = Process::GetPID("game.exe");

			if (PID != 0)
			{
				unsigned int _PID;

				HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
				ReadProcessMemory(hProcess, (LPCVOID)REAL_PID, &_PID, 4, NULL);
				CloseHandle(hProcess);

				if (_PID != 0)
				{
					SetWindowText(GUI::StateLabel, "Injetando dll...");

					DWORD Entry;
					LPCVOID Mudele = (LPCVOID)Process::GetModuleInfo(_PID, "UnZipDataToDirectory");

					HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
					ReadProcessMemory(hProcess, Mudele, &Entry, 4, NULL);
					CloseHandle(hProcess);
					
					if (Entry != 0)
					{
						if (Process::Inject(_PID, GUI::ModulePath.c_str()))
						{
							SetWindowText(GUI::StateLabel, "Dll injetada!");

							Sleep(2000);
							PostQuitMessage(0);
						}
						else
						{
							SetWindowText(GUI::StateLabel, "Não foi possível injetar dll!");

							Sleep(2000);
							PostQuitMessage(0);
						}
					}
				}
			}
		}
	}
	catch (...) {}
}