#include <windows.h>
#include "window.h"
#include "actors.h"
#include "overlaycleanup.h"
#include "driver.h"

#include <Windows.h>
#include <string>
#pragma comment(lib, "physmeme-lib.lib")
#include "Obsidium Sdk/obsidium64.h"
#include "driver\general.h"
#include "comm.h"
#include "fish.h"
std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}

namespace physmeme
{
	NTSTATUS __cdecl map_driver(std::vector<std::uint8_t>& raw_driver);
	NTSTATUS __cdecl map_driver(std::uint8_t* image, std::size_t size);
}


const UINT GetProcessThreadNumByID(DWORD dwPID)
{
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
		return 0;

	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(pe32);
	BOOL bRet = ::Process32First(hProcessSnap, &pe32);;
	while (bRet)
	{
		if (pe32.th32ProcessID == dwPID)
		{
			::CloseHandle(hProcessSnap);
			return pe32.cntThreads;
		}
		bRet = ::Process32Next(hProcessSnap, &pe32);
	}
	return 0;
}

const UINT GetProcessIdUD(const char* process_name) {
	UINT pid = 0;

	DWORD dwThreadCountMax = 0;

	// Create toolhelp snapshot.
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);
	// Walkthrough all processes.
	if (Process32First(snapshot, &process))
	{
		do
		{
			if (strstr(process.szExeFile, process_name))
			{
				DWORD dwTmpThreadCount = GetProcessThreadNumByID(process.th32ProcessID);
				if (dwTmpThreadCount > dwThreadCountMax)
				{
					dwThreadCountMax = dwTmpThreadCount;
					pid = process.th32ProcessID;
					break;
				}
			}
		} while (Process32Next(snapshot, &process));
	}
	CloseHandle(snapshot);
	return pid;
}




void scrollbar()
{
	try {
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(console, &csbi);
		COORD scrollbar = {
			csbi.srWindow.Right - csbi.srWindow.Left + 1,
			csbi.srWindow.Bottom - csbi.srWindow.Top + 1
		};

		if (console == 0) {
			throw 0;
		}
		else {
			SetConsoleScreenBufferSize(console, scrollbar);
		}
	}
	catch (...) {
	
	}

}


VOID ErasePEHeaderFromMemory()
{
	DWORD OldProtect = 0;

	// Get base address of module
	char* pBaseAddr = (char*)GetModuleHandle(NULL);

	// Change memory protection
	VirtualProtect(pBaseAddr, 4096, // Assume x86 page size
		PAGE_READWRITE, &OldProtect);

	// Erase the header
	SecureZeroMemory(pBaseAddr, 4096);
}


std::string path()
{
	char shitter[_MAX_PATH]; // defining the path
	GetModuleFileNameA(NULL, shitter, _MAX_PATH); // getting the path
	return std::string(shitter); //returning the path
}




/*std::string gen_random(const int len) {
	const std::string alpha_numeric("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");

	std::default_random_engine generator{ std::random_device{}() };
	const std::uniform_int_distribution< std::string::size_type > distribution{ 0, alpha_numeric.size() - 1 };

	std::string str(len, 0);
	for (auto& it : str) {
		it = alpha_numeric[distribution(generator)];
	}

	return str;
}*/


bool mrymc(const std::string& desired_file_path, const char* address, size_t size)
{
	std::ofstream file_ofstream(desired_file_path.c_str(), std::ios_base::out | std::ios_base::binary);

	if (!file_ofstream.write(address, size))
	{
		file_ofstream.close();	
		return false;
	}

	file_ofstream.close();
	return true;
}
void quittasks() {
	no_exec(("taskkill /F /IM EpicGamesLauncher.exe"));
	no_exec(("taskkill /F /IM EasyAntiCheatLauncher.exe"));
	no_exec(("taskkill /F /IM BEService.exe"));
	no_exec(("taskkill /F /IM Fortnite.exe"));
	no_exec(("taskkill /F /IM BattleEyeLauncher.exe"));
}






























#define TARGET_PROCESS L"FortniteClient-Win64-Shipping.exe"

DWORD GetPID(LPCWSTR processName)
{
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	DWORD procID = NULL;

	if (handle == INVALID_HANDLE_VALUE)
		return procID;

	PROCESSENTRY32W entry = { 0 };
	entry.dwSize = sizeof(PROCESSENTRY32W);

	if (Process32FirstW(handle, &entry)) {
		if (!_wcsicmp(processName, entry.szExeFile))
		{
			procID = entry.th32ProcessID;
		}
		else while (Process32NextW(handle, &entry)) {
			if (!_wcsicmp(processName, entry.szExeFile)) {
				procID = entry.th32ProcessID;
			}
		}
	}

	CloseHandle(handle);
	return procID;
}

HWND Entryhwnd = NULL;
auto get_process_wnd(uint32_t pid) -> HWND
{
	std::pair<HWND, uint32_t> params = { 0, pid };
	BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
		auto pParams = (std::pair<HWND, uint32_t>*)(lParam);
		uint32_t processId = 0;

		if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processId)) && processId == pParams->second) {
			SetLastError((uint32_t)-1);
			pParams->first = hwnd;
			return FALSE;
		}

		return TRUE;

		}, (LPARAM)&params);

	if (!bResult && GetLastError() == -1 && params.first)
		return params.first;

	return NULL;
}


int processid = 0;













struct EncryptedData_t
{
	std::string a;
	std::string b;
	std::string c;
	std::string d;
};

std::string Decrypt(EncryptedData_t encryptedData) {
	BLOWFISH blowfish1(XorStr("5565685563947512"));
	BLOWFISH blowfish2(XorStr("5958175082173221"));
	BLOWFISH blowfish3(XorStr("0966785654609401"));
	BLOWFISH blowfish4(XorStr("8936978002422920"));

	//decrypt each part
	std::string BufferDecrypted = blowfish1.Decrypt_CBC(encryptedData.a);
	BufferDecrypted += blowfish2.Decrypt_CBC(encryptedData.b);
	BufferDecrypted += blowfish3.Decrypt_CBC(encryptedData.c);
	BufferDecrypted += blowfish4.Decrypt_CBC(encryptedData.d);

	return BufferDecrypted;
}

std::string StreamFileToMemString(std::string URL) {
	const char* header = (XorStr("Accept: *" "/" "*\r\n\r\n").c_str());
	HANDLE hInterWebz = InternetOpenA(XorStr("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36").c_str(), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HANDLE hURL = InternetOpenUrlA(hInterWebz, URL.c_str(), header, strlen(header), INTERNET_FLAG_DONT_CACHE, 0);

	char* Buffer = new char[100000000]; //100mb
	memset(Buffer, 0, 100000000);
	DWORD BytesRead = 1;

	std::string data;

	if (InternetReadFile(hURL, Buffer, 100000000, &BytesRead))
	{
		data = std::string(Buffer);
	}

	delete[] Buffer;
	InternetCloseHandle(hInterWebz);
	InternetCloseHandle(hURL);

	return data;
}

std::string GetDecryptedSys()
{
	std::string data1 = StreamFileToMemString(XorStr(R"(https://cdn.discordapp.com/attachments/870469898600579132/1060099545771540520/1)"));
	std::string data2 = StreamFileToMemString(XorStr(R"(https://cdn.discordapp.com/attachments/870469898600579132/1060099546119684116/2)"));
	std::string data3 = StreamFileToMemString(XorStr(R"(https://cdn.discordapp.com/attachments/870469898600579132/1060099546497175652/3)"));
	std::string data4 = StreamFileToMemString(XorStr(R"(https://cdn.discordapp.com/attachments/870469898600579132/1060099546962739281/4)"));

	std::string decryptedSys = Decrypt({ data1, data2, data3, data4 });

	return decryptedSys;
}

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;



#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LITGRAY 7
#define DAKGREY 8
#define LITBLUE 9
#define LITGREEN 10
#define LITCYAN 11
#define LITRED 12
#define LITMEGENTA 13
#define YELLOW 14
#define WHITE 15


void SetCol(unsigned short color)
{
	HANDLE con = 0;
	con = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(con, color);
}

int process_id;

void error_handler(const char* message)
{
	printf("[error] %s\n", message);

	system("pause");
	while (true) {}
}

void mainudud() {
	system("CLS");
	std::cout << XorStr("\n[~] Initializing... ");

	Sleep(1000);
	SonyDriverHelper::api::Init();

	mouse_interface();
	std::cout << XorStr("\n[~] Step 1 : HOOKED");
	Sleep(500);
	std::cout << XorStr("\n");
	//MessageBoxA(0, XorStr("Press OK in lobby.").c_str(), XorStr("").c_str(), MB_OK || MB_ICONEXCLAMATION);
	system("cls");

	printf(XorStr("\n[~] Waiting For FortniteClient-Win64-Shipping.exe").c_str());
	while (windowid == NULL)
	{
		Sleep(50);
		windowid = FindWindowA_Spoofed(0, XorStr("Fortnite  ").c_str());
	}
	mem::find_driver();

	//ShowWindow_Spoofed(::GetConsoleWindow(), SW_HIDE);

	mem::process_id = mem::find_process("FortniteClient-Win64-Shipping.exe");
	Identifier::ADDRESS = mem::find_image();

	std::cout << ("Base Address = ") << (void*)Identifier::ADDRESS << std::endl;

	Sleep(1000);
	mrymc("C:\\ProgramData\\overlaycleanup.exe", reinterpret_cast<const char*>(overlaycleanup), sizeof(overlaycleanup));
	ShellExecuteA(NULL, XorStr("open").c_str(), XorStr("C:\\ProgramData\\overlaycleanup.exe").c_str(), NULL, NULL, SW_HIDE);
	//Identifier::ADDRESS = (uintptr_t)LoadLibrary("C://Program Files//Epic Games//Fortnite//FortniteGame//Binaries//Win64//FortniteClient-Win64-Shipping.exe");
	Beep(200, 200);
	setup_window();
	HANDLE worldcacheh = CreateThread_Spoofed(nullptr, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(world), nullptr, NULL, nullptr);
	CloseHandle_Spoofed(worldcacheh);
	
	mainloop();
	ErasePEHeaderFromMemory();
}


int main()
{
	//KeyAuthApp.init();

	//	login();
		mainudud();

}
