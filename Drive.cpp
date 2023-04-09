#pragma once
#include "comm.h"

Memory::Memory(DWORD PID) {
	KM_PID = PID;
	Setup();
}

BOOL Memory::Setup() {
	hDriver = CreateFileA(("\\\\.\\Discord"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (hDriver == INVALID_HANDLE_VALUE) {
		return false;
	}

	return true;
}

uint64_t Memory::GetModuleBase(const std::string& module_name) {

	return (uintptr_t)LoadLibraryA("C:\\Program Files\\Epic Games\\Fortnite\\FortniteGame\\Binaries\\Win64\\FortniteClient-Win64-Shipping.exe");
}


bool Memory::Rpm(uint64_t address, void* buffer, size_t size)
{
	return ReadMemoryFromKernel(KM_PID, address, buffer, size);
}

bool Memory::ReadMemoryFromKernel(int processId, uint64_t address, void* buffer, size_t size)
{
	struct
	{
		int pid;
		uintptr_t address;
		uintptr_t buffer;
		int size;
	} req = { processId, uintptr_t(address), uintptr_t(buffer), size };

	DeviceIoControl(hDriver, 0, &req, sizeof(req), &req, sizeof(req), NULL, NULL);

	return true;
}

bool Memory::Wpm(uint64_t address, void* buffer, size_t size)
{
	return WriteMemoryFromKernel(KM_PID, address, buffer, size);
}

bool Memory::WriteMemoryFromKernel(int processId, uint64_t address, void* buffer, size_t size)
{
	struct
	{
		int pid;
		uintptr_t address;
		uintptr_t buffer;
		int size;
	} req = { processId, uintptr_t(address), uintptr_t(buffer), size };

	DeviceIoControl(hDriver, 0, &req, sizeof(req), &req, sizeof(req), NULL, NULL);

	return true;
}