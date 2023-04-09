
#include <windows.h>
#include "skStr.h"
#include <dwmapi.h>
#include "LIFN.hpp"
#include "xor.hpp"
enum InjectedInputMouseOptions
{
	move = 1,
	left_up = 4,
	left_down = 2,
	right_up = 8,
	right_down = 16
};

struct InjectedInputMouseInfo
{
	int move_direction_x; // 10 would move the mouse from the current position +10 on the X, same withe the Y
	int move_direction_y;
	unsigned int mouse_data;
	InjectedInputMouseOptions mouse_options;
	unsigned int time_offset_in_miliseconds;
	void* extra_info;
};

bool(*_NtUserInjectMouseInput)(InjectedInputMouseInfo*, int) = nullptr;
BOOL(*_GetCursorPos)(LPPOINT lpPoint) = nullptr;
BOOL(*_SetLayeredWindowAttributes)(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags) = nullptr;
HRESULT(*_DwmExtendFrameIntoClientArea)(HWND hwnd, const MARGINS* pMarInset) = nullptr;
LRESULT(*_DefWindowProc)(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam) = nullptr;
HWND(*_CreateWindowExA)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) = nullptr;
LONG(*_SetWindowLongA)(HWND hwnd, int nIndex, LONG dwNewLong) = nullptr;
LONG(*_GetWindowLongA)(HWND hwnd, int nIndex) = nullptr;
ATOM(*_RegisterClassExA)(const WNDCLASSEXA*) = nullptr;
int(*_GetSystemMetrics)(int nIndex) = nullptr;
HWND(*_FindWindowA)(LPCSTR lpClassName, LPCSTR lpWindowName) = nullptr;
SHORT(*_GetAsyncKeyState)(int vKey) = nullptr;
HWND(*_GetForegroundWindow)() = nullptr;
BOOL(*_MoveWindow)(HWND hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint) = nullptr;
BOOL(*_PeekMessageA)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) = nullptr;
BOOL(*_TranslateMessage)(const MSG* lpMsg) = nullptr;
LRESULT(*_DispatchMessageA)(const MSG* lpMsg) = nullptr;
HANDLE(*_CreateThread)(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE     lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) = nullptr;
BOOL(*_CloseHandle)(HANDLE hObject) = nullptr;
BOOL(*_SetWindowPos)(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) = nullptr;
BOOL(*_ShowWindow)(HWND hWnd, int nCmdShow) = nullptr;
BOOL(*_SetWindowDisplayAffinity)(HWND hWnd, DWORD dwAffinity) = nullptr;

void mouse_interface()
{
	HMODULE user32 = LI_FN(LoadLibraryA).get()(skCrypt("user32.dll"));
	HMODULE kernel32 = LI_FN(LoadLibraryA).get()(skCrypt("Kernel32.dll"));
	HMODULE win32u = LI_FN(LoadLibraryA).get()(skCrypt("win32u.dll"));
	HMODULE dwmapi = LI_FN(LoadLibraryA).get()(skCrypt("dwmapi.dll"));

	if (!win32u) {
		return;
	}

	if (!user32) {
		return;
	}

	if (!dwmapi) {
		return;
	}

	if (!kernel32) {
		return;
	}


	void* NtUserInjectMouseInputAddress = (void*)LI_FN(GetProcAddress).get()(win32u, skCrypt("NtUserInjectMouseInput"));
	void* GetCursorPos = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetCursorPos"));
	void* SetLayeredWindowAttributes = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("SetLayeredWindowAttributes"));
	void* DwmExtendFrameIntoClientArea = (void*)LI_FN(GetProcAddress).get()(dwmapi, skCrypt("DwmExtendFrameIntoClientArea"));
	void* DefWindowProcA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("DefWindowProcA"));
	void* CreateWindowExA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("CreateWindowExA"));
	void* SetWindowLongA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("SetWindowLongA"));
	void* GetWindowLongA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetWindowLongA"));
	void* RegisterClassExA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("RegisterClassExA"));
	void* GetSystemMetrics = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetSystemMetrics"));
	void* FindWindowA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("FindWindowA"));
	void* GetAsyncKeyState = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetAsyncKeyState"));
	void* GetForegroundWindow = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("GetForegroundWindow"));
	void* MoveWindow = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("MoveWindow"));
	void* PeekMessageA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("PeekMessageA"));
	void* TranslateMessage = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("TranslateMessage"));
	void* DispatchMessageA = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("DispatchMessageA"));
	void* CreateThread = (void*)LI_FN(GetProcAddress).get()(kernel32, skCrypt("CreateThread"));
	void* SetWindowPos = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("SetWindowPos"));
	void* CloseHandle = (void*)LI_FN(GetProcAddress).get()(kernel32, skCrypt("CloseHandle"));
	void* ShowWindow = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("ShowWindow"));
	void* SetWindowDisplayAffinity = (void*)LI_FN(GetProcAddress).get()(user32, skCrypt("SetWindowDisplayAffinity"));

	if (!NtUserInjectMouseInputAddress) {
		return;
	}

	if (!GetCursorPos) {
		return;
	}

	if (!SetLayeredWindowAttributes) {
		return;
	}

	if (!DwmExtendFrameIntoClientArea) {
		return;
	}

	if (!DefWindowProcA) {
		return;
	}

	if (!CreateWindowExA) {
		return;
	}

	if (!SetWindowLongA) {
		return;
	}

	if (!GetWindowLongA) {
		return;
	}

	if (!RegisterClassExA) {
		return;
	}

	if (!GetSystemMetrics) {
		return;
	}

	if (!FindWindowA) {
		return;
	}

	if (!GetAsyncKeyState) {
		return;
	}

	if (!GetForegroundWindow) {
		return;
	}

	if (!MoveWindow) {
		return;
	}

	if (!PeekMessageA) {
		return;
	}

	if (!TranslateMessage) {
		return;
	}

	if (!DispatchMessageA) {
		return;
	}

	if (!CreateThread) {
		return;
	}

	if (!CloseHandle) {
		return;
	}

	if (!SetWindowPos) {
		return;
	}

	if (!ShowWindow) {
		return;
	}

	if (!SetWindowDisplayAffinity) {
		return;
	}


	*(void**)&_NtUserInjectMouseInput = NtUserInjectMouseInputAddress;
	*(void**)&_GetCursorPos = GetCursorPos;
	*(void**)&_SetLayeredWindowAttributes = SetLayeredWindowAttributes;
	*(void**)&_DwmExtendFrameIntoClientArea = DwmExtendFrameIntoClientArea;
	*(void**)&_DefWindowProc = DefWindowProcA;
	*(void**)&_CreateWindowExA = CreateWindowExA;
	*(void**)&_SetWindowLongA = SetWindowLongA;
	*(void**)&_GetWindowLongA = GetWindowLongA;
	*(void**)&_RegisterClassExA = RegisterClassExA;
	*(void**)&_GetSystemMetrics = GetSystemMetrics;
	*(void**)&_FindWindowA = FindWindowA;
	*(void**)&_GetAsyncKeyState = GetAsyncKeyState;
	*(void**)&_GetForegroundWindow = GetForegroundWindow;
	*(void**)&_MoveWindow = MoveWindow;
	*(void**)&_PeekMessageA = PeekMessageA;
	*(void**)&_TranslateMessage = TranslateMessage;
	*(void**)&_DispatchMessageA = DispatchMessageA;
	*(void**)&_CreateThread = CreateThread;
	*(void**)&_CloseHandle = CloseHandle;
	*(void**)&_SetWindowPos = SetWindowPos;
	*(void**)&_ShowWindow = ShowWindow;
	*(void**)&_SetWindowDisplayAffinity = SetWindowDisplayAffinity;


	LI_FN(FreeLibrary).get()(kernel32);
	LI_FN(FreeLibrary).get()(user32);
	LI_FN(FreeLibrary).get()(win32u);
	LI_FN(FreeLibrary).get()(dwmapi);


}

bool Hijacked_Move(int x = 0, int y = 0, unsigned int time = 0)
{
	InjectedInputMouseInfo temp = {};
	temp.mouse_data = 0;
	temp.mouse_options = InjectedInputMouseOptions::move;
	temp.move_direction_x = x;
	temp.move_direction_y = y;
	temp.time_offset_in_miliseconds = time;
	return _NtUserInjectMouseInput(&temp, 1);
}

BOOL GetCursorPosA(LPPOINT lpPoint)
{
	return _GetCursorPos(lpPoint);
}

BOOL SetLayeredWindowAttributes_Spoofed(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
	return _SetLayeredWindowAttributes(hwnd, crKey, bAlpha, dwFlags);
}

HRESULT __stdcall DwmExtendFrameIntoClientArea_Spoofed(HWND hwnd, const MARGINS* pMarInset)
{
	return _DwmExtendFrameIntoClientArea(hwnd, pMarInset);
}

LRESULT __stdcall DefWindowProcA_Spoofed(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return _DefWindowProc(hwnd, Msg, wParam, lParam);
}

HWND __stdcall CreateWindowExA_Spoofed(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	return _CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

LONG __stdcall SetWindowLongA_Spoofed(HWND hwnd, int nIndex, LONG dwNewLong)
{
	return _SetWindowLongA(hwnd, nIndex, dwNewLong);
}

LONG __stdcall GetWindowLongA_Spoofed(HWND hwnd, int nIndex)
{
	return _GetWindowLongA(hwnd, nIndex);
}

ATOM __stdcall RegisterClassExA_Spoofed(const WNDCLASSEXA* softaim) {
	return _RegisterClassExA(softaim);
}

int __stdcall GetSystemMetrics_Spoofed(int nIndex) {
	return _GetSystemMetrics(nIndex);
}

HWND __stdcall FindWindowA_Spoofed(LPCSTR lpClassName, LPCSTR lpWindowName) {
	return _FindWindowA(lpClassName, lpWindowName);
}

HWND __stdcall GetForegroundWindow_Spoofed() {
	return _GetForegroundWindow();
}

SHORT GetAsyncKeyState_Spoofed(int vKey) {
	return _GetAsyncKeyState(vKey);
}

SHORT MoveWindow_Spoofed(HWND hWnd, int X, int Y, int nWidth, int nHeight, bool bRepaint) {
	return _MoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
}

BOOL __stdcall PeekMessageA_Spoofed(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg) {
	return _PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

BOOL __stdcall TranslateMessage_Spoofed(const MSG* lpMsg) {
	return _TranslateMessage(lpMsg);
}

LRESULT __stdcall DispatchMessageA_Spoofed(const MSG* lpMsg) {
	return _DispatchMessageA(lpMsg);
}

HANDLE __stdcall CreateThread_Spoofed(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) {
	return _CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
}

BOOL __stdcall CloseHandle_Spoofed(HANDLE hObject) {
	return _CloseHandle(hObject);
}

BOOL __stdcall SetWindowPos_Spoofed(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) {
	return _SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

BOOL __stdcall ShowWindow_Spoofed(HWND hWnd, int nCmdShow) {
	return _ShowWindow(hWnd, nCmdShow);
}

BOOL __stdcall SetWindowDisplayAffinity_Spoofed(HWND hWnd, DWORD dwAffinity) {
	return _SetWindowDisplayAffinity(hWnd, dwAffinity);
}



















#pragma once 
#pragma warning (disable : 6066)
#pragma warning(2:4235)

namespace mouse
{
	// where we can simulate any input!!! 
	enum MouseEnum
	{
		// whrere i got these https://docs.microsoft.com/en-us/uwp/api/windows.ui.input.preview.injection.injectedinputmouseoptions?view=winrt-22000
		move = 1,
		XDown = 128, // XBUTTON pressed.
		XUp = 256, // XBUTTON released.
		RightDown = 8, // Right mouse button pressed.
		RightUp = 16, // Right mouse button released.
		LeftDown = 2, // Left mouse button pressed.
		LeftUp = 4, // Left mouse button released.
	};

	// dont chnage struct or enum or class names...
	struct InjectedInputMouseInfo
	{
		int MoveX;
		int MoveY;
		unsigned int mouse_data;
		MouseEnum MouseOption;
		unsigned int time_offset_in_miliseconds;
		void* extra_info;
	};

	class MouseClass
	{
	public:
		static BOOL LoadMouse();
		static BOOL LoadNtGetKey();
		static BOOL NtGetAsyncKeyState(int VK_CODE);
		static BOOL Move(int x, int y);
	};
}




using mouse::MouseClass;





BYTE NtUserGetAsyncKeyState_Bytes[30];
BOOL MouseClass::LoadNtGetKey()
{
	LoadLibrary(XorStr("user32.dll").c_str());

	HMODULE win32u = LoadLibrary(XorStr("win32u.dll").c_str());
	if (!win32u) return FALSE;

	void* NtUserGetAsyncKeyState_Addr = (void*)GetProcAddress(win32u, XorStr("NtUserGetAsyncKeyState").c_str());
	if (!NtUserGetAsyncKeyState_Addr)	return FALSE;

	//*(void**)&tNtUserGetAsyncKeyState = NtUserInjectMouseInputAddress;
	memcpy(NtUserGetAsyncKeyState_Bytes, NtUserGetAsyncKeyState_Addr, 30);
	return TRUE;
}

UINT WINAPI NtUserGetAsyncKeyState(UINT Key)
{
	LPVOID NtUserGetAsyncKeyState_Spoof = VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE); // allocate space for syscall
	if (!NtUserGetAsyncKeyState_Spoof) return FALSE;
	memcpy(NtUserGetAsyncKeyState_Spoof, NtUserGetAsyncKeyState_Bytes, 30); // copy syscall
	NTSTATUS Result = reinterpret_cast<NTSTATUS(NTAPI*)(UINT)>(NtUserGetAsyncKeyState_Spoof)(Key); // calling spoofed function
	ZeroMemory(NtUserGetAsyncKeyState_Spoof, 0x1000); // clean address
	VirtualFree(NtUserGetAsyncKeyState_Spoof, 0, MEM_RELEASE); // free it
	return Result; // return the status
}

BOOL MouseClass::NtGetAsyncKeyState(int VK_CODE)
{
	if (VK_CODE < 0 || VK_CODE > 256)
		return FALSE;
	//return (SHORT)tNtUserGetAsyncKeyState(VK_CODE);
	return NtUserGetAsyncKeyState(VK_CODE);
}

// ========================

BYTE NtUserSendInput_Bytes[30];
BOOL MouseClass::LoadMouse()
{
	// DO NOT FORGET TO XOR THESE i didnt because my pc bsdoed and do not have access to my source rn LOL 
	LoadLibrary(XorStr("user32.dll").c_str());
	HMODULE win32u = LoadLibrary(XorStr("win32u.dll").c_str());
	if (!win32u) return FALSE;

	// xor
	void* NtUserInjectMouseInput_Addr = (void*)GetProcAddress(win32u, XorStr("NtUserInjectMouseInput").c_str());
	if (!NtUserInjectMouseInput_Addr)	return FALSE;

	//*(void**)&NtUserInjectMouseInput = NtUserInjectMouseInputAddress; *For just using straight function*
	memcpy(NtUserSendInput_Bytes, NtUserInjectMouseInput_Addr, 30);
	return TRUE;
}

BOOLEAN WINAPI InjectMouseInputSpoof(mouse::InjectedInputMouseInfo* Struct, int Value)
{
	LPVOID NtUserInjectMouseInput_Spoof = VirtualAlloc(0, 0x1000, MEM_COMMIT, PAGE_EXECUTE_READWRITE); // allocate space for syscall
	if (!NtUserInjectMouseInput_Spoof) return FALSE;
	memcpy(NtUserInjectMouseInput_Spoof, NtUserSendInput_Bytes, 30); // copy syscall
	NTSTATUS Result = reinterpret_cast<NTSTATUS(NTAPI*)(mouse::InjectedInputMouseInfo*, int)>(NtUserInjectMouseInput_Spoof)(Struct, Value); // calling spoofed function
	SecureZeroMemory(NtUserInjectMouseInput_Spoof, 0x1000); // clean address
	VirtualFree(NtUserInjectMouseInput_Spoof, 0, MEM_RELEASE); // free it
	return (Result > 0); // return the status
}

BOOL MouseClass::Move(int x, int y)
{
	InjectedInputMouseInfo mouse = {};
	mouse.MouseOption = MouseEnum::move;
	mouse.MoveX = x;
	mouse.MoveY = y;
	return InjectMouseInputSpoof(&mouse, 1);
}
