#pragma once

#include "world.h"
ImFont* light;
ImFont* lightworld;
ImFont* test;

void OutlinedText(int x, int y, ImColor Color, const char* text)
{
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x - 1, y), ImColor(0, 0, 0), text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x + 1, y), ImColor(0, 0, 0), text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y - 1), ImColor(0, 0, 0), text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y + 1), ImColor(0, 0, 0), text);
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(x, y), Color, text);
}
static ImColor Color;

void draw_cornered_box(int x, int y, int w, int h, ImColor color, int thickness) {
	float line_w = (w / 1);
	float line_h = (h / 1);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + line_h), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + line_w, y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - line_w, y), ImVec2(x + w, y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + line_h), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h - line_h), ImVec2(x, y + h), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + line_w, y + h), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - line_w, y + h), ImVec2(x + w, y + h), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y + h - line_h), ImVec2(x + w, y + h), color, thickness);
}
void DrawCornerBox(int X, int Y, int W, int H, const ImU32& color, int thickness) {
	float lineW = (W / 3);
	float lineH = (H / 3);

	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y), ImVec2(X + lineW, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y), ImVec2(X + W, Y), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y), ImVec2(X + W, Y + lineH), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H - lineH), ImVec2(X, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X, Y + H), ImVec2(X + lineW, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W - lineW, Y + H), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(X + W, Y + H - lineH), ImVec2(X + W, Y + H), ImGui::GetColorU32(color), thickness);

}


void draw_cornered_box2(int x, int y, int w, int h, ImColor color, int thickness) {
	float line_w = (w / 4);
	float line_h = (h / 4);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + line_h), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y), ImVec2(x + line_w, y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - line_w, y), ImVec2(x + w, y), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y), ImVec2(x + w, y + line_h), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h - line_h), ImVec2(x, y + h), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x, y + h), ImVec2(x + line_w, y + h), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w - line_w, y + h), ImVec2(x + w, y + h), color, thickness);
	ImGui::GetBackgroundDrawList()->AddLine(ImVec2(x + w, y + h - line_h), ImVec2(x + w, y + h), color, thickness);
}



std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];
	ZeroMemory(pwBuf, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr(pBuf);
	delete[]pwBuf;
	delete[]pBuf;
	pwBuf = NULL;
	pBuf = NULL;
	return retStr;
}

bool enemiesarround = true;
int enemyID = 0;
int enemyIDvis = 0;
int CloseRangeDistanceID = 0;
float CloseRangeDistance = 50.f;

void DrawNewTextCustom2(int x, int y, int R, int G, int B, int A, const char* str)
{
	ImGui::PushFont(light);
	std::string utf_8_1 = std::string(str);
	std::string utf_8_2 = string_To_UTF8(utf_8_1);

	ImGui::GetBackgroundDrawList()->AddText(light, 18.0f, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(R / 255.0, G / 255.0, B / 255.0, A / 255.0)), utf_8_2.c_str());
}


#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))

namespace hotkeys
{
	int aimkey;
	int aimkey2;
	int airstuckey;
}

static int keystatus = 0;
static int keystatus2 = 0;
static int realkey = 0;
static int realkey2 = 0;
bool GetKey(int key)
{
	realkey = key;
	return true;
}
void ChangeKey(void* blank)
{
	keystatus = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}


bool GetKey2(int key)
{
	realkey2 = key;
	return true;
}
void ChangeKey2(void* blank)
{
	keystatus2 = 1;
	while (true)
	{
		for (int i = 0; i < 0x87; i++)
		{
			if (GetKeyState(i) & 0x8000)
			{
				hotkeys::aimkey2 = i;
				keystatus2 = 0;
				return;
			}
		}
	}
}


static const char* keyNames2[] =
{
	"No Key Selected",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"No Key Selected",
	"Backspace",
	"Tab",
	"No Key Selected",
	"Clear",
	"Enter",
	"No Key Selected",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"No Key Selected",
	"Escape",
	"No Key Selected",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"No Key Selected",
	"Print",
	"Insert",
	"Delete",
	"No Key Selected",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"No Key Selected",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"No Key Selected",
	"No Key Selected",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"No Key Selected",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

static const char* keyNames[] =
{
	"No Key Selected",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"No Key Selected",
	"Backspace",
	"Tab",
	"No Key Selected",
	"Clear",
	"Enter",
	"No Key Selected",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"No Key Selected",
	"Escape",
	"No Key Selected",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"No Key Selected",
	"Print",
	"Insert",
	"Delete",
	"No Key Selected",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"No Key Selected",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"No Key Selected",
	"No Key Selected",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"No Key Selected",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};

static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
static bool Items_ArrayGetter2(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}
void HotkeyButton(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames))
		Items_ArrayGetter(keyNames, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = "Press the key";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 25)))
	{
		if (status == 0)
		{
			CreateThread_Spoofed(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}


void HotkeyButton2(int aimkey, void* changekey, int status)
{
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(keyNames2))
		Items_ArrayGetter2(keyNames2, aimkey, &preview_value);

	std::string aimkeys;
	if (preview_value == NULL)
		aimkeys = "Select Key";
	else
		aimkeys = preview_value;

	if (status == 1)
	{
		aimkeys = "Press the key";
	}
	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 25)))
	{
		if (status == 0)
		{
			CreateThread_Spoofed(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
		}
	}
}

typedef struct
{
	DWORD R;
	DWORD G;
	DWORD B;
	DWORD A;
}RGBA;


namespace custom
{





	int StringToWString(std::wstring& ws, const std::string& s)
	{
		std::wstring wsTmp(s.begin(), s.end());

		ws = wsTmp;

		return 0;
	}




	std::string to_string(int n)
	{
		int m = n;
		char s[100]; //max
		char ss[100]; //max
		int i = 0, j = 0;
		if (n < 0)
		{
			m = 0 - m;
			j = 1;
			ss[0] = '-';
		}
		while (m > 0)
		{
			s[i++] = m % 10 + '0';
			m /= 10;
		}
		s[i] = '\0';
		i = i - 1;
		while (i >= 0)
		{
			ss[j++] = s[i--];
		}
		ss[j] = '\0';
		return ss;
	}

	const wchar_t* GetWC(const char* c)
	{
		const size_t cSize = strlen(c) + 1;
		wchar_t* wc = new wchar_t[cSize];
		mbstowcs(wc, c, cSize);

		return wc;
	}


}


RGBA red = { 255,0,0,255 };
RGBA Magenta = { 255,0,255,255 };
RGBA yellow = { 255,255,0,255 };
RGBA grayblue = { 128,128,255,255 };
RGBA green = { 128,224,0,255 };
RGBA darkgreen = { 0,224,128,255 };
RGBA brown = { 192,96,0,255 };
RGBA pink = { 255,168,255,255 };
RGBA DarkYellow = { 216,216,0,255 };
RGBA BuffaloPurple = { 94,23,235,255 };
RGBA SilverWhite = { 236,236,236,255 };
RGBA purple = { 129, 47, 212,255 };
RGBA Navy = { 88,48,224,255 };
RGBA skyblue = { 0,136,255,255 };
RGBA graygreen = { 128,160,128,255 };
RGBA blue = { 0,96,192,255 };
RGBA coolcol = { 51, 171, 145, 255 };
RGBA orange = { 255,128,0,255 };
RGBA peachred = { 255,80,128,255 };
RGBA reds = { 255,128,192,255 };
RGBA darkgray = { 96,96,96,255 };
RGBA Navys = { 0,0,128,255 };
RGBA darkgreens = { 0,128,0,255 };
RGBA darkblue = { 0,128,128,255 };
RGBA redbrown = { 128,0,0,255 };
RGBA purplered = { 128,0,128,255 };
RGBA greens = { 0,255,0,255 };
RGBA envy = { 0,255,255,255 };
RGBA black = { 0,0,0,255 };
RGBA gray = { 177, 181, 179,255 };
RGBA white = { 255,255,255,255 };
RGBA blues = { 30,144,255,255 };
RGBA lightblue = { 135,206,250,160 };
RGBA Scarlet = { 220, 20, 60, 160 };
RGBA white_ = { 255,255,255,200 };
RGBA gray_ = { 128,128,128,200 };
RGBA black_ = { 0,0,0,200 };
RGBA red_ = { 255,0,0,200 };
RGBA Magenta_ = { 255,0,255,200 };
RGBA yellow_ = { 255,255,0,200 };
RGBA grayblue_ = { 128,128,255,200 };
RGBA green_ = { 128,224,0,200 };
RGBA darkgreen_ = { 0,224,128,200 };
RGBA brown_ = { 192,96,0,200 };
RGBA pink_ = { 255,168,255,200 };
RGBA darkyellow_ = { 216,216,0,200 };
RGBA silverwhite_ = { 236,236,236,200 };
RGBA purple_ = { 144,0,255,200 };
RGBA Blue_ = { 88,48,224,200 };
RGBA skyblue_ = { 0,136,255,200 };
RGBA graygreen_ = { 128,160,128,200 };
RGBA blue_ = { 0,96,192,200 };
RGBA orange_ = { 255,128,0,200 };
RGBA pinks_ = { 255,80,128,200 };
RGBA Fuhong_ = { 255,128,192,200 };
RGBA darkgray_ = { 96,96,96,200 };
RGBA Navy_ = { 0,0,128,200 };
RGBA darkgreens_ = { 0,128,0,200 };
RGBA darkblue_ = { 0,128,128,200 };
RGBA redbrown_ = { 128,0,0,200 };
RGBA purplered_ = { 128,0,128,200 };
RGBA greens_ = { 0,255,0,200 };
RGBA envy_ = { 0,255,255,200 };

RGBA glassblack = { 0, 0, 0, 160 };
RGBA GlassBlue = { 65,105,225,80 };
RGBA glassyellow = { 255,255,0,160 };
RGBA glass = { 200,200,200,60 };

RGBA filled = { 0, 0, 0, 150 };

RGBA Plum = { 221,160,221,160 };


std::wstring MBytesToWString(const char* lpcszString)
{
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode = new wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_ACP, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	std::wstring wString = (wchar_t*)pUnicode;
	delete[] pUnicode;
	return wString;
}
std::string WStringToUTF8(const wchar_t* lpwcszWString)
{
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}
void DrawString(float fontSize, int x, int y, RGBA* color, bool bCenter, bool stroke, const char* pText, ...)
{
	va_list va_alist;
	char buf[1024] = { 0 };
	va_start(va_alist, pText);
	_vsnprintf_s(buf, sizeof(buf), pText, va_alist);
	va_end(va_alist);
	std::string text = WStringToUTF8(MBytesToWString(buf).c_str());
	if (bCenter)
	{
		ImVec2 textSize = ImGui::CalcTextSize(text.c_str());
		x = x - textSize.x / 2;
		y = y - textSize.y;
	}
	if (stroke)
	{
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x + 1, y - 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
		ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x - 1, y + 1), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), text.c_str());
	}
	ImGui::GetBackgroundDrawList()->AddText(ImGui::GetFont(), fontSize, ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(color->R / 255.0, color->G / 255.0, color->B / 255.0, color->A / 255.0)), text.c_str());
}

void Render_2D_Box(int x, int y, int w, int h, const ImU32& color, int thickness)
{
	ImGui::GetBackgroundDrawList()->AddRect(ImVec2(x, y), ImVec2(w, h), ImGui::GetColorU32(color), 0, 0, thickness);
}



char* drawBuff = (char*)malloc(1024);

char* wchar_to_char(const wchar_t* pwchar)
{
	int currentCharIndex = 0;
	char currentChar = pwchar[currentCharIndex];

	while (currentChar != '\0')
	{
		currentCharIndex++;
		currentChar = pwchar[currentCharIndex];
	}

	const int charCount = currentCharIndex + 1;

	char* filePathC = (char*)malloc(sizeof(char) * charCount);

	for (int i = 0; i < charCount; i++)
	{
		char character = pwchar[i];

		*filePathC = character;

		filePathC += sizeof(char);

	}
	filePathC += '\0';

	filePathC -= (sizeof(char) * charCount);

	return filePathC;
}














bool isVisible(DWORD_PTR mesh)
{
	if (!mesh)
		return false;
	float tik = driver::read<float>(mesh + 0x338);
	float tok = driver::read<float>(mesh + 0x340);
	const float tick = 0.06f;
	return tok + tick >= tik;
}
bool enemyvisible;

float fl_VisibleColor[3];
float fl_InVisibleColor[3];
void draw_esp()
{
	float closestDistance = FLT_MAX;
	DWORD_PTR closestPawn = NULL;
	float closestactor = FLT_MAX;




	//ImGui::PushFont(lightworld);
	/*
	for (LootEntity LEntityList : LootentityList) {
		if (features::enableloot) {
		if (offname::localactorpawn)
		{
			ImGui::PushFont(lightworld);
			uintptr_t ItemRootComponent = driver::read<uintptr_t>(LEntityList.ACurrentItem + 0x190);
			Vector3 ItemPosition = driver::read<Vector3>(ItemRootComponent + 0x128);
			float ItemDist = localactorpos.Distance(ItemPosition) / 100.f;
			std::string null = ("");

			auto IsSearched = driver::read<BYTE>((uintptr_t)LEntityList.ACurrentItem + 0x101a);
			if (IsSearched >> 2 & 1) continue;
			Vector3 ChestPosition;
			ChestPosition = w2s(ItemPosition);
			Vector3 VehiclePosition = w2s(ItemPosition);
			ImGui::PushFont(lightworld);
			if (strstr(LEntityList.GNames.c_str(), ("Tiered_Chest")) && features::ChestESP)
			{
				if (ItemDist < features::VisDistloot) {

					std::string Text = null + ("Chest [") + std::to_string((int)ItemDist) + ("m]");
					DrawString(14, ChestPosition.x, ChestPosition.y, &orange_, true, true, Text.c_str());
				}
			}
			ImGui::PushFont(lightworld);
			if (strstr(LEntityList.GNames.c_str(), ("Tiered_Ammo")) && features::Ammoesp)
			{
				if (ItemDist < features::VisDistloot) {

					std::string Text = null + ("Ammobox [") + std::to_string((int)ItemDist) + ("m]");
					DrawString(14, ChestPosition.x, ChestPosition.y, &darkblue, true, true, Text.c_str());
				}
			}

		
			else if (features::Animalesp)
			{						//NPC_Pawn_Irwin_Predator_Robert_C   NPC_Pawn_Irwin_Prey_Burt_C				NPC_Pawn_Irwin_Simple_Smackie_C			NPC_Pawn_Irwin_Predator_Grandma_C			NPC_Pawn_Irwin_Simple_Avian_Crow_C
				if ((strstr(LEntityList.GNames.c_str(), ("NPC_Pawn_Irwin_Predator_Robert_C"))) || (strstr(LEntityList.GNames.c_str(), ("NPC_Pawn_Irwin_Prey_Burt_C"))) || (strstr(LEntityList.GNames.c_str(), ("NPC_Pawn_Irwin_Simple_Smackie_C"))) || (strstr(LEntityList.GNames.c_str(), ("NPC_Pawn_Irwin_Prey_Nug_C"))) || (strstr(LEntityList.GNames.c_str(), ("NPC_Pawn_Irwin_Predator_Grandma_C")))) {
					if (ItemDist < features::VisDist) {

						std::string Text = null + ("Animal [") + std::to_string((int)ItemDist) + ("m]");
						DrawString(14, VehiclePosition.x, VehiclePosition.y, &white, true, true, Text.c_str());
					}
				}
			}
			ImGui::PushFont(lightworld);

			if (strstr(LEntityList.GNames.c_str(), ("AthenaPlayerMarker_WithCustomization")))
			{
				if (ItemDist < 800) {

					std::string Text = null + ("Marker [") + std::to_string((int)ItemDist) + ("m]");
					DrawString(14, ChestPosition.x, ChestPosition.y, &orange_, true, true, Text.c_str());
				}
			}

			ImGui::PushFont(lightworld);
			if (strstr(LEntityList.GNames.c_str(), ("AthenaSupplyDrop_C")) && features::supplydrop)
			{
				if (ItemDist < 2000) {

					std::string Text = null + ("Supplydrop [") + std::to_string((int)ItemDist) + ("m]");
					DrawString(14, ChestPosition.x, ChestPosition.y, &orange_, true, true, Text.c_str());
				}
			}


		
			else if (features::VehicleEsp)
			{
				ImGui::PushFont(lightworld);
				if ((strstr(LEntityList.GNames.c_str(), ("MeatballVehicle_L_C"))) || (strstr(LEntityList.GNames.c_str(), ("Valet_SportsC"))) || (strstr(LEntityList.GNames.c_str(), ("Valet_BigRig"))) || (strstr(LEntityList.GNames.c_str(), ("Vehicl"))) || (strstr(LEntityList.GNames.c_str(), ("Valet_BasicC"))) || (strstr(LEntityList.GNames.c_str(), ("Valet_BasicTr"))) || (strstr(LEntityList.GNames.c_str(), ("Valet_Taxi")))) {
					if (ItemDist < features::VisDistloot) {

						std::string Text = null + ("Vehicle [") + std::to_string((int)ItemDist) + ("m]");
						DrawString(14, VehiclePosition.x, VehiclePosition.y, &white, true, true, Text.c_str());
					}
				}
			}



			


		}
		
		}
	}

	*/


	for (unsigned long i = 0; i < allplayers.size(); ++i)
	{

		//
	

		actors entity = allplayers[i];

		Vector3 actorpos = driver::read<Vector3>(entity.rootcomp + Offsets::External::RELATIVELOC);
		localactorpos = driver::read<Vector3>(entity.localrootcomp + Offsets::External::RELATIVELOC);
		float distance = localactorpos.Distance(actorpos) / 100.f;
		int MyTeamId = driver::read<int>(offname::actorstate + Offsets::External::TEAMID);




		Vector3 Headpos = bonerota(entity.MESH, 68); // need
		Vector3 Headbox = w2s(Vector3(Headpos.x, Headpos.y, Headpos.z + features::height));
		Vector3 Headbox2 = w2s(Vector3(Headpos.x, Headpos.y, Headpos.z + features::height2));
		Vector3 w2shead = w2s(Headpos);
		Vector3 bone0 = bonerota(entity.MESH, 0);
		Vector3 bottom = w2s(bone0);


	





		float BoxHeight = (float)(Headbox.y - bottom.y);
		float BoxHeighth = (float)(Headbox.y - Headbox.y);
		float BoxHeighth2 = BoxHeighth + 10;
		float BoxWidth = BoxHeight * 0.200;
		float CornerHeight = abs(Headbox.y - bottom.y);
		float CornerWidth = CornerHeight * features::width;
	

		auto CurrentWeapon = driver::read<uintptr_t>(offname::localactorpawn + Offsets::External::CURRWEAPON);
		auto pawnWeaponID = driver::read<uint32_t>(CurrentWeapon + 0x18);
		std::string pObjName = GetNameFromFName(pawnWeaponID);
		std::string null = ("");



		if (MyTeamId != entity.ActorTeamId && offname::localactorpawn)
		{
			if (distance < features::VisDist) {
			enemyID += 1;
			if (distance < CloseRangeDistance)
			{
				CloseRangeDistanceID += 1;
			}

			if (isVisible(entity.MESH)) {
				Color = ImGui::GetColorU32({ fl_VisibleColor[0],fl_VisibleColor[1],fl_VisibleColor[2],  1.0f });
				enemyIDvis += 1;
				enemyvisible = true;
			}
			else {
				Color = ImGui::GetColorU32({ fl_InVisibleColor[0],fl_InVisibleColor[1],fl_InVisibleColor[2],  1.0f });
				enemyvisible = false;
			}



			if (features::boxes) {
			if (features::BoxType == 0)
			{
				draw_cornered_box(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, ImColor(0, 0, 0, 255), features::boxthick);
				draw_cornered_box(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, Color, 0);
			}
			else if (features::BoxType == 1)
			{
				DrawCornerBox(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, Color, features::boxthick);

			}
			else if (features::BoxType == 2)
			{
				draw_cornered_box2(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, ImColor(0, 0, 0, 255), features::boxthick);
				draw_cornered_box2(Headbox.x - (CornerWidth / 2), Headbox.y, CornerWidth, CornerHeight, Color, 0);
			}
			else if (features::BoxType == 3)
			{
				ImGui::GetForegroundDrawList()->AddRect(ImVec2(Headbox.x - (CornerWidth / 4), Headbox.y), ImVec2(bottom.x + (CornerWidth / 4), bottom.y), ImColor(0, 0, 0, 255), 0, 0, 3);
				ImGui::GetForegroundDrawList()->AddRect(ImVec2(Headbox.x - (CornerWidth / 4), Headbox.y), ImVec2(bottom.x + (CornerWidth / 4), bottom.y), Color, 0, 1.f);
				ImGui::GetForegroundDrawList()->AddRect(ImVec2(Headbox.x - (CornerWidth / 4), Headbox.y), ImVec2(bottom.x + (CornerWidth / 4), bottom.y), Color, 0, 0.5f);
			}
			}




		

			std::string DistanceText2 = ("Anonymous Player [") + std::to_string(int(distance)) + (" M]");
			std::string DistanceText3 = ("[") + std::to_string(int(distance)) + (" M]");
			ImVec2 DistanceTextSize2 = ImGui::CalcTextSize(DistanceText2.c_str());
			ImVec2 DistanceTextSize3 = ImGui::CalcTextSize(DistanceText3.c_str());
			if (features::distance) { 
				if (features::disttop) {
					OutlinedText(w2shead.x - DistanceTextSize2.x / 2, Headbox2.y, ImColor(255,255,255), DistanceText2.c_str());
				}
				else if (features::distbottom) {
					OutlinedText(bottom.x - DistanceTextSize3.x / 2, bottom.y, ImColor(255, 255, 255), DistanceText3.c_str());
				}
			}
		

			if (features::lines)
			{
				if (features::LineType == 0)
				{
					if (features::visibleonlys) {
						if (enemyvisible) {
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, 0), ImVec2(bottom.x, bottom.y), Color, 0.f);
						}
					}
					else {
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, 0), ImVec2(bottom.x, bottom.y), Color, 0.f);
					}
				
				}
				if (features::LineType == 1)
				{
					if (features::visibleonlys) {
						if (enemyvisible) {
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(bottom.x, bottom.y), Color, 0.f);
						}
					}
					else {
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(bottom.x, bottom.y), Color, 0.f);
					}
				}
				if (features::LineType == 2)
				{
					if (features::visibleonlys) {
						if (enemyvisible) {
							ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height), ImVec2(bottom.x, bottom.y), Color, 0.f);
						}
					}
					else {
						ImGui::GetBackgroundDrawList()->AddLine(ImVec2(Width / 2, Height), ImVec2(bottom.x, bottom.y), Color, 0.f);
					}
				
				}
			}

			auto dx = w2shead.x - (Width / 2);
			auto dy = w2shead.y - (Height / 2);
			auto dz = w2shead.z - (Depth / 2);
			auto dist = sqrtf(dx * dx + dy * dy + dz * dz) / 100.0f;
			if (features::univaimbot) {
				if (features::fovcirclee)
				{
					fovcircle(Width / 2, Height / 2, features::fov, IM_COL32(255, 255, 255, 50), 60, 0.0f);
				}
				features::aimspeed = features::aimspeed;
				if (enemyvisible) {
					if (dist < features::fov && dist < closestDistance) {

						closestDistance = dist;
						closestPawn = entity.ACTOR;
					}
					
				}
			}
			else {
				
				if (features::weaponaimbot) {

					if (pObjName.find("Assault") != std::string::npos || pObjName.find("Athena_R_Ore") != std::string::npos || pObjName.find("Thermal") != std::string::npos || pObjName.find("Bow") != std::string::npos || pObjName.find("Rifle") != std::string::npos || pObjName.find("Pistol") != std::string::npos) {
						if (features::fovcirclee1)
						{
							fovcircle(Width / 2, Height / 2, features::fov1, IM_COL32(255, 255, 255, 80), 60, 0.0f);
						}
						features::rifleaiming = true;
						features::fov = features::fov1;
						aimbot1::aimspeed = aimbot1::aimspeed;
						if (enemyvisible) {
							if (dist < features::fov1 && dist < closestDistance) {

								closestDistance = dist;
								closestPawn = entity.ACTOR;

							}

						}
					}
					else {
						features::rifleaiming = false;
					}

					if (pObjName.find("Shotgun") != std::string::npos)
					{
						features::shotgunaiming = true;
						if (features::fovcirclee2)
						{
							fovcircle(Width / 2, Height / 2, features::fov2, IM_COL32(255, 255, 255, 80), 60, 0.0f);
						}

						features::fov = features::fov2;
						aimbot2::aimspeed = aimbot2::aimspeed;
						if (enemyvisible) {
							if (dist < features::fov2 && dist < closestDistance) {

								closestDistance = dist;
								closestPawn = entity.ACTOR;

							}

						}

					}
					else {
						features::shotgunaiming = false;

					}
					if (pObjName.find("SMG") != std::string::npos)
					{
						features::smgaiming = true;
						if (features::fovcirclee3)
						{
							fovcircle(Width / 2, Height / 2, features::fov3, IM_COL32(255, 255, 255, 80), 60, 0.0f);
						}
						features::fov = features::fov3;
						aimbot3::aimspeed = aimbot3::aimspeed;
						if (enemyvisible) {
							if (dist < features::fov3 && dist < closestDistance) {

								closestDistance = dist;
								closestPawn = entity.ACTOR;

							}

						}
					}
					else {
						features::smgaiming = false;
					}

					if (pObjName.find("Sniper") != std::string::npos || pObjName.find("DMR") != std::string::npos)
					{
						features::sniperaiming = true;
						if (features::fovcirclee4)
						{
							fovcircle(Width / 2, Height / 2, features::fov4, IM_COL32(255, 255, 255, 80), 60, 0.0f);
						}
						features::fov = features::fov4;
						aimbot4::aimspeed = aimbot4::aimspeed;
						if (enemyvisible) {
							if (dist < features::fov4 && dist < closestDistance) {

								closestDistance = dist;
								closestPawn = entity.ACTOR;

							}

						}
					}
					else {
						features::sniperaiming = false;
					}
				}
				
			}

			


		}
		}
	}



	if (features::enemiesarround && enemyID > 0)
	{
		std::string s = std::to_string(enemyID);
		std::string a = ("[") + s + (" Rendered]");
		std::string z = std::to_string(CloseRangeDistanceID);
		std::string c = ("[") + z + (" CR]");
		auto sizeC = ImGui::CalcTextSize(c.c_str());
		ImGui::PushFont(light);
		DrawNewTextCustom2((float)(Width / 2) - (sizeC.x / 2), 80, 255, 255, 255, 200, c.c_str());
	
		auto sizeA = ImGui::CalcTextSize(a.c_str());

		ImGui::PushFont(light);

		DrawNewTextCustom2((float)(Width / 2) - (sizeA.x / 2), 50, 255, 255, 255, 200, a.c_str());
		std::string b = std::to_string(enemyIDvis);
		std::string d = ("[") + b + (" Visible]");
		ImGui::PushFont(light);
		auto sizeD = ImGui::CalcTextSize(d.c_str());
		DrawNewTextCustom2((float)(Width / 2) - (sizeD.x / 2), 20, 255, 255, 255, 200, d.c_str());

	}

	if (enemyID != 0)
		enemyID = 0;

	if (CloseRangeDistanceID != 0)
		CloseRangeDistanceID = 0;

	if (enemyIDvis != 0)
		enemyIDvis = 0;




	if (features::aimbot)
	{
		if (isVisible)
		{
			if (offname::localactorpawn)
			{
				if (closestPawn != 0)
				{
					if (features::aimbot && GetAsyncKeyState_Spoofed(hotkeys::aimkey) < 0) {
						targetbone(closestPawn);
					}
				}
			}
		}
		else
		{

		}
	}
}



