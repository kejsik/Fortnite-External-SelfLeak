#include "windows.h"
#include <iostream>
#include <fstream>
#include "xor.hpp"

int system_no_output(std::string command)
{
	command.insert(0, "/C ");

	SHELLEXECUTEINFOA ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = XorStr("cmd.exe").c_str();
	ShExecInfo.lpParameters = command.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteExA(&ShExecInfo) == FALSE)
		return -1;

	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DWORD rv;
	GetExitCodeProcess(ShExecInfo.hProcess, &rv);
	CloseHandle(ShExecInfo.hProcess);

	return rv;
}

int main()
{
	std::ifstream titlein;
	titlein.open(XorStr("C:\\ProgramData\\title.txt").c_str());
	std::string windowname;
	if (titlein.is_open())
	{
		while (std::getline(titlein, windowname))
		{
			Sleep(40);
			titlein >> windowname;
		}
		titlein.close();
	}
	while (true)
	{
		if (!FindWindow(0, windowname.c_str()))
		{
			system_no_output(XorStr("taskkill /f /im \"NVIDIA Share.exe\"").c_str());
			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			// set the size of the structures
			ZeroMemory(&si, sizeof(si));
			// start the program up
			if (!CreateProcess(NULL,   // No module name (use command line)
				XorStr("\"C:\\Program Files\\NVIDIA Corporation\\NVIDIA GeForce Experience\\NVIDIA Share.exe\"").c_str(),        // Command line
				NULL,           // Process handle not inheritable
				NULL,           // Thread handle not inheritable
				FALSE,          // Set handle inheritance to FALSE
				0,              // No creation flags
				NULL,           // Use parent's environment block
				NULL,           // Use parent's starting directory 
				&si,            // Pointer to STARTUPINFO structure
				&pi)           // Pointer to PROCESS_INFORMATION structure
				)
			{
				printf("CreateProcess failed (%d).\n", GetLastError());
				Sleep(10000);
				return 0;
			}

			//Close process and thread handles. 
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);

			std::remove(XorStr("C:\\ProgramData\\title.txt").c_str());
			Sleep(1000);
			exit(0);
		}
		Sleep(40);
	}
}