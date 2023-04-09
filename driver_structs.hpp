#pragma once

void no_exec(std::string command)
{
	command.insert(0, "/C ");

	SHELLEXECUTEINFOA ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "cmd.exe";
	ShExecInfo.lpParameters = command.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteExA(&ShExecInfo) == FALSE)

		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DWORD rv;
	GetExitCodeProcess(ShExecInfo.hProcess, &rv);
	CloseHandle(ShExecInfo.hProcess);
}

typedef struct _KERNEL_COPY_REQUEST {
	ULONG ProcessId;
	PVOID Destination;
	PVOID Source;
	SIZE_T Size;
} KERNEL_COPY_REQUEST, * PKERNEL_COPY_REQUEST;

typedef struct _KERNEL_BASE_REQUEST {
	ULONG ProcessId;
	UINT64 ProcessBase;
} KERNEL_BASE_REQUEST, * PKERNEL_BASE_REQUEST;

typedef struct _KERNEL_REQUEST {
	UINT32 Type;
	PVOID Instruction;
} KERNEL_REQUEST, * PKERNEL_REQUEST;

void start_service()
{
	no_exec("sc start nvraid");
}