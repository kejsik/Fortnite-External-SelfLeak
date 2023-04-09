#pragma once
#include "menu.h"
#include "streamproof.h"

void setup_window()
{
	
	win = FindWindowA_Spoofed(XorStr("CEF-OSC-WIDGET").c_str(), XorStr("NVIDIA GeForce Overlay").c_str());
	if (!win)
	{
		system("cls");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		MessageBoxA(0, XorStr("Failed To Find NVIDIA.").c_str(), XorStr("Overlay").c_str(), MB_OK);
		Sleep(5000);
		exit(1);
	}

	ShowWindow_Spoofed(win, SW_SHOW);

	SetWindowLongA_Spoofed(win, GWL_EXSTYLE, WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW | WS_EX_LAYERED);
	SetWindowLongA_Spoofed(
		win,
		-20,
		static_cast<LONG_PTR>(
			static_cast<int>(GetWindowLongA_Spoofed(win, -20)) | 0x20
			)
	);

	//transparency
	MARGINS margin = { -1, -1, -1, -1 };
	DwmExtendFrameIntoClientArea_Spoofed(
		win,
		&margin
	);

	SetLayeredWindowAttributes_Spoofed(
		win,
		NULL,
		0xFF,
		0x02
	);

	// top most
	SetWindowPos_Spoofed(
		win,
		HWND_TOPMOST,
		0, 0, 0, 0,
		0x0002 | 0x0001
	);



	UpdateWindow(win);

	if (FAILED(Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object)))
		exit(3);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = Width;
	d3dpp.BackBufferHeight = Height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_NONE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.hDeviceWindow = win;
	d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.Windowed = TRUE;

	p_Object->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, win, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &D3dDevice);

	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	ImGui::StyleColorsClassic();

	ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, 1.0f);

	ImGui_ImplWin32_Init(win);
	ImGui_ImplDX9_Init(D3dDevice);
	io.Fonts->AddFontFromMemoryTTF(&LightFont, sizeof LightFont, 14);
	light = io.Fonts->AddFontFromMemoryTTF(&LightFont, sizeof LightFont, 14);
	lightworld = io.Fonts->AddFontFromMemoryTTF(&LightFont, sizeof LightFont, features::fontsize);


	p_Object->Release();

}

void mainloop()
{
	static RECT old_rc;
	ZeroMemory(&Message, sizeof(MSG));

	while (Message.message != WM_QUIT)
	{
		if (PeekMessageA_Spoofed(&Message, win, 0, 0, PM_REMOVE))
		{
			TranslateMessage_Spoofed(&Message);
			DispatchMessageA_Spoofed(&Message);
		}

		HWND hwnd_active = GetForegroundWindow_Spoofed();

		if (hwnd_active == windowid) {
			HWND hwndtest = GetWindow(hwnd_active, GW_HWNDPREV);
			SetWindowPos_Spoofed(win, hwndtest, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		}

		RECT rc;
		POINT xy;

		ZeroMemory(&rc, sizeof(RECT));
		ZeroMemory(&xy, sizeof(POINT));
		GetClientRect(win, &rc);
		ClientToScreen(win, &xy);
		rc.left = xy.x;
		rc.top = xy.y;

		ImGuiIO& io = ImGui::GetIO();
		io.ImeWindowHandle = win;
		io.DeltaTime = 1.0f / 60.0f;

		POINT p;
		GetCursorPos(&p);
		io.MousePos.x = p.x - xy.x;
		io.MousePos.y = p.y - xy.y;


		if (GetAsyncKeyState_Spoofed(VK_F8)) {
			ShowWindow_Spoofed(win, SW_HIDE);
			exit(0);
		}
		if (GetAsyncKeyState_Spoofed(VK_LBUTTON)) {
			io.MouseDown[0] = true;
			io.MouseClicked[0] = true;
			io.MouseClickedPos[0].x = io.MousePos.x;
			io.MouseClickedPos[0].x = io.MousePos.y;
		}
		else
			io.MouseDown[0] = false;

		if (rc.left != old_rc.left || rc.right != old_rc.right || rc.top != old_rc.top || rc.bottom != old_rc.bottom)
		{
			old_rc = rc;

			Width = rc.right;
			Height = rc.bottom;

			d3dpp.BackBufferWidth = Width;
			d3dpp.BackBufferHeight = Height;
			SetWindowPos_Spoofed(win, (HWND)0, xy.x, xy.y, Width, Height, SWP_NOREDRAW);
			D3dDevice->Reset(&d3dpp);
		}

		io.MouseDown[0] = GetAsyncKeyState_Spoofed(VK_LBUTTON) & 0x8000;
		io.MouseDown[1] = GetAsyncKeyState_Spoofed(VK_RBUTTON) & 0x8000;
		io.MouseDown[2] = GetAsyncKeyState_Spoofed(VK_MBUTTON) & 0x8000;
		io.MouseDown[3] = GetAsyncKeyState_Spoofed(VK_XBUTTON1) & 0x8000;
		io.MouseDown[4] = GetAsyncKeyState_Spoofed(VK_XBUTTON2) & 0x8000;

		for (int i = 6; i < 512; i++) {
			io.KeysDown[i] = (GetKeyState(i) & 0x8000) != 0;
		}

		menu();

	}
	features::menu = false;
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

