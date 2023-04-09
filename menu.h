#pragma once 
#include "include.h"
#include "renderutils.h"
#include "render_esp.h"
#include "Utils\font.h"
#include "Utils\globals.h"
#include "Utils\icons.h"
#include "Utils\imguipp_v2.h"
#include "Utils\includes.h"
#include "streamproof.h"
int MenuTab = 0;
int MenuTabAIM = 0;
int MenuTabVIS = 0;
inline static int menu_animation = 0;
inline static int border_animation = 0;
inline static int menu_slide = 0;
inline static bool small_tab = false;
inline static int do_tab_anim = 0;
bool open = true;
std::string nameud;
std::string onlineuserss;
std::string usernameud;
std::string lastlogin;
std::string versionud;
static bool domenuopen;




void ToggleButton(const char* str_id, bool* v, float sizex, float sizey)
{

	ImVec2 p = ImGui::GetCursorScreenPos();

	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	float height = ImGui::GetFrameHeight();
	float width = height * 1.55f;
	float radius = height * 0.50f;
	if (ImGui::InvisibleButton(str_id, ImVec2(sizex, sizey)))
		*v = !*v;
	ImU32 col_bg;
	if (ImGui::IsItemHovered())
	{
		col_bg = *v ? IM_COL32(0, 162, 232, 255) : ImGuiCol_FrameBgHovered;

	}


	else
		col_bg = *v ? IM_COL32(0, 162, 232, 255) : IM_COL32(14, 14, 14, 255);
	draw_list->AddRectFilled(p, ImVec2(p.x + sizex, p.y + sizey), col_bg, sizey * 0.0f);
	//draw_list->AddCircleFilled(ImVec2(*v ? (p.x + width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
}






void menu()
{ 


	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (GetAsyncKeyState_Spoofed(VK_INSERT) & 1) {

		features::menu = !features::menu;
		if (menu_animation > 0) {
			menu_animation = 1;
		}
		if (menu_animation < 0)
		{
			menu_animation = 1;
		}
	}


	ImGui::PushFont(light);
	draw_esp();

	if (features::b_cross)
	{
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2 - 10, Height / 2), IM_COL32(255, 0, 0, 255), 1);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2 + 10, Height / 2), IM_COL32(255, 0, 0, 255), 1);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2, Height / 2 - 10), IM_COL32(255, 0, 0, 255), 1);
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(Width / 2, Height / 2), ImVec2(Width / 2, Height / 2 + 10), IM_COL32(255, 0, 0, 255), 1);
	}



	if (open)
	{
		menu_animation = menu_animation + 6;
		border_animation = border_animation + 6;
		menu_slide = menu_slide + 10;
	}
	else if (!open)
	{
		menu_animation = menu_animation - 6;
		border_animation = border_animation - 6;
		menu_slide = menu_slide - 10;
	}

	if (menu_animation > 254)
		menu_animation = 255;

	if (border_animation > 3.4)
		border_animation = 3.5;
	if (border_animation < 1)
		border_animation = 0;

	if (menu_slide > 560)
		menu_slide = 561;
	if (menu_slide < 1)
		menu_slide = 0;

	
	
	ImGuiStyle& style = ImGui::GetStyle();
	auto color = style.Colors;

	color[ImGuiCol_WindowBg] = ImColor(40, 40, 40, menu_animation);

	color[ImGuiCol_ChildBg] = ImColor(35, 35, 35, menu_animation);
	color[ImGuiCol_Border] = ImColor(25, 25, 25, menu_animation);
	color[ImGuiCol_BorderShadow] = ImColor(50, 50, 50, menu_animation);
	color[ImGuiCol_Button] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_ButtonActive] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_ButtonHovered] = ImColor(25, 25, 25, menu_animation);
	color[ImGuiCol_ScrollbarBg] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_ScrollbarGrab] = ImColor(95, 75, 113, menu_animation);
	color[ImGuiCol_ScrollbarGrabActive] = ImColor(95, 75, 113, menu_animation);
	color[ImGuiCol_ScrollbarGrabHovered] = ImColor(95, 75, 113, menu_animation);
	color[ImGuiCol_CheckMark] = ImColor(130, 60, 180, menu_animation);
	color[ImGuiCol_FrameBg] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_SliderGrab] = ImColor(95, 75, 113, menu_animation);
	color[ImGuiCol_SliderGrabActive] = ImColor(95, 75, 113, menu_animation);
	color[ImGuiCol_PlotLines] = ImColor(130, 60, 180, menu_animation);
	color[ImGuiCol_PlotLinesHovered] = ImColor(130, 60, 180, menu_animation);
	color[ImGuiCol_PlotHistogram] = ImColor(130, 60, 180, menu_animation);
	color[ImGuiCol_PlotHistogramHovered] = ImColor(130, 60, 180, menu_animation);
	color[ImGuiCol_TabActive] = ImColor(130, 60, 180, menu_animation);
	color[ImGuiCol_TabUnfocusedActive] = ImColor(130, 60, 180, menu_animation);
	color[ImGuiCol_Header] = ImColor(95, 75, 113, menu_animation);
	color[ImGuiCol_HeaderActive] = ImColor(95, 75, 113, menu_animation);
	color[ImGuiCol_HeaderHovered] = ImColor(95, 75, 113, menu_animation);
	color[ImGuiCol_TitleBg] = ImColor(130, 60, 180, menu_animation);
	color[ImGuiCol_FrameBgActive] = ImColor(130, 60, 180, menu_animation);
	color[ImGuiCol_TitleBgActive] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_TitleBgCollapsed] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_PopupBg] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_TextSelectedBg] = ImColor(130, 60, 180, menu_animation);
	color[ImGuiCol_Text] = ImColor(255, 255, 255, menu_animation);
	color[ImGuiCol_TextDisabled] = ImColor(255, 255, 255, menu_animation);
	color[ImGuiCol_NavHighlight] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_NavWindowingHighlight] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_NavWindowingDimBg] = ImColor(40, 40, 40, menu_animation);
	color[ImGuiCol_ModalWindowDimBg] = ImColor(40, 40, 40, menu_animation);

	style.WindowTitleAlign = ImVec2(0.5, 0.5);
	style.WindowBorderSize = 1.0;


	style.ChildRounding = 0;
	style.FrameRounding = 0;
	style.ScrollbarRounding = 0;
	style.GrabRounding = 0;
	style.PopupRounding = 0;
	style.WindowRounding = 0;
	style.FramePadding = ImVec2(3.0f, 3.0f);

	style.AntiAliasedLines = true;
	style.AntiAliasedFill = true;
	static int sub_tab = 0;
	
	if (features::menu)
	{
		ImGui::SetNextWindowSize(ImVec2(menu_slide, 500));
		ImGui::Begin("", nullptr, ImGuiWindowFlags_NoDecoration);

		ImGui::BeginChild("##LeftSide", ImVec2(120, ImGui::GetContentRegionAvail().y), TRUE);
		{
			if (ImGui::Button("COMBAT", ImVec2(110, 40)))
				MenuTab = 1;

			if (ImGui::Button("VISUAL", ImVec2(110, 40)))
				MenuTab = 2;

			if (ImGui::Button("COLOR", ImVec2(110, 40)))
				MenuTab = 3;

			if (ImGui::Button("MISC", ImVec2(110, 40)))
				MenuTab = 4;

			if (ImGui::Button("CONFIG", ImVec2(110, 40)))
				MenuTab = 5;
		}
		ImGui::SetCursorPosY(460);
		ImGui::Text("kejsik#5677 if u sell this ure fucking gay and ill find u");
		ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		{
			if (MenuTab == 1) {
				ImGui::Text("Combat");
				ImGui::Separator();
				if (ImGui::Button("Main", ImVec2(70, 30))) MenuTabAIM = 0; ImGui::SameLine(); if (ImGui::Button("Rifle", ImVec2(70, 30))) MenuTabAIM = 1; ImGui::SameLine(); if (ImGui::Button("Shotgun", ImVec2(70, 30))) MenuTabAIM = 2;	ImGui::SameLine();	if (ImGui::Button("SMG", ImVec2(70, 30))) MenuTabAIM = 3; ImGui::SameLine(); if (ImGui::Button("Sniper", ImVec2(70, 30))) MenuTabAIM = 4;

				if (MenuTabAIM == 0) {
					ImGui::Text("Main");
					ImGui::Separator();

					ImGui::Checkbox("Enable Combat", &features::aimbot);
					ImGui::Checkbox("Enable Custom Weapon Config", &features::weaponaimbot);
					if (features::weaponaimbot) {
						features::univaimbot = 0;
						features::weaponaimbot = 1;
					}
					ImGui::Checkbox("Enable Universal Aim", &features::univaimbot);
					if (features::univaimbot) {
						features::univaimbot = 1;
						features::weaponaimbot = 0;
					}

					ImGui::Text("Assitance Key: ");
					HotkeyButton(hotkeys::aimkey, ChangeKey, keystatus);

					if (features::univaimbot) {
						ImGui::Text("Universal");
						ImGui::Separator();


						ImGui::Checkbox("Show Radius", &features::fovcirclee);
						ImGui::SliderFloat("Smoothness", &features::aimspeed, 1, 40);
						ImGui::SliderFloat("FOV Value", &features::fov, 1, 600);

					}


				}
				if (MenuTabAIM == 1) {
					ImGui::Text("Assault Rifle");
					ImGui::Separator();
					ImGui::Checkbox("Enable AR", &features::aimbot1);
					ImGui::Checkbox("Show Radius", &features::fovcirclee1);
					ImGui::SliderFloat("Smoothness", &aimbot1::aimspeed, 1, 40);
					ImGui::SliderFloat("FOV Value", &features::fov1, 1, 600);

				}
				if (MenuTabAIM == 2) {
					ImGui::Text("Shotgun");
					ImGui::Separator();
					ImGui::Checkbox("Enable Shotgun", &features::aimbot2);
					ImGui::Checkbox("Show Radius", &features::fovcirclee2);
					ImGui::SliderFloat("Smoothness", &aimbot2::aimspeed, 1, 40);
					ImGui::SliderFloat("FOV Value", &features::fov2, 1, 600);


				}
				if (MenuTabAIM == 3) {
					ImGui::Text("SMG");
					ImGui::Separator();
					ImGui::Checkbox("Enable SMG", &features::aimbot3);
					ImGui::Checkbox("Show Radius", &features::fovcirclee3);
					ImGui::SliderFloat("Smoothness", &aimbot3::aimspeed, 1, 40);
					ImGui::SliderFloat("FOV Value", &features::fov3, 1, 600);

				}
				if (MenuTabAIM == 4) {
					ImGui::Text("Sniper");
					ImGui::Separator();
					ImGui::Checkbox("Enable Sniper", &features::aimbot4);
					ImGui::Checkbox("Show Radius", &features::fovcirclee4);
					ImGui::SliderFloat("Smoothness", &aimbot4::aimspeed, 1, 40);
					ImGui::SliderFloat("FOV Value", &features::fov4, 1, 600);


				}

			}
		}
		ImGui::EndChild();
		ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		{

			if (MenuTab == 2) {
				ImGui::Text("Visuals");
				ImGui::Separator();
				if (ImGui::Button("Player", ImVec2(70, 30))) MenuTabVIS = 0; ImGui::SameLine(); if (ImGui::Button("World", ImVec2(70, 30))) MenuTabVIS = 1; ImGui::SameLine(); if (ImGui::Button("Misc", ImVec2(70, 30))) MenuTabVIS = 2;
				if (MenuTabVIS == 0) {
					ImGui::Text("Player");
					ImGui::Separator();

					ImGui::Checkbox("Draw Box", &features::boxes);
					if (features::boxes) {
						ImGui::Combo("Box Type", &features::BoxType, features::BoxTypes, 4);
					}

					ImGui::Checkbox("Draw Snapline", &features::lines);
					if (features::lines) {
						ImGui::Checkbox("Snapline Visible Only", &features::visibleonlys);

						ImGui::Combo("Snapline Type", &features::LineType, features::LineTypes, 3);
					}

					ImGui::Checkbox("Draw Distance", &features::distance);
					if (features::distance) {

						ImGui::Checkbox("Distance Top", &features::disttop);
						ImGui::Checkbox("Distance Bottom", &features::distbottom);
					}
					ImGui::Checkbox("Render Enemies", &features::enemiesarround);

					ImGui::Text("");
					ImGui::SliderFloat("Player Visual Distance", &features::VisDist, 10, 500);
				}
				if (MenuTabVIS == 1) {
					ImGui::Text("World");
					ImGui::Separator();
					ImGui::Checkbox("Enable World (bugged)", &features::enableloot);
					ImGui::Checkbox("Chest", &features::ChestESP);
					ImGui::Checkbox("Ammobox", &features::Ammoesp);
					ImGui::Checkbox("Vehicle", &features::VehicleEsp);
					ImGui::Checkbox("Animals", &features::Animalesp);
					ImGui::Checkbox("Supplydrop", &features::supplydrop);
					ImGui::Checkbox("Marker", &features::Marker);

					ImGui::Text("");


					ImGui::SliderFloat("Loot Delay Time", &features::lootdelay, 1, 30);
					ImGui::SliderFloat("World Visual Distance", &features::VisDistloot, 10, 250);
				}
				if (MenuTabVIS == 2) {
					ImGui::Text("Misc");
					ImGui::Separator();
				
					ImGui::Checkbox("Crosshair", &features::b_cross);
				}
			}
		}
		ImGui::EndChild();
		ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		{
			if (MenuTab == 3) {
				ImGui::Text("Colors");
				ImGui::Separator();
				ImGui::PushItemWidth(130.0f);
				ImGui::ColorPicker3(("Visible Color"), fl_VisibleColor, ImGuiColorEditFlags_NoInputs);
				ImGui::ColorPicker3(("InVisible Color"), fl_InVisibleColor, ImGuiColorEditFlags_NoInputs);


			}
		}
		ImGui::EndChild();

		ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		{
			if (MenuTab == 4) {
				ImGui::Text("Misc");
				ImGui::Separator();
				ImGui::SliderFloat("Close Range Distance", &CloseRangeDistance, 1, 300);

				ImGui::SliderFloat("Box Width", &features::width, 0.1, 3);
				ImGui::SliderInt("Distance Height", &features::height2, 1, 80);
				
				ImGui::SliderInt("Box Height", &features::height, 1, 50);
				ImGui::SliderInt("Box Thickness", &features::boxthick, 1, 8);
				ImGui::Text("");
				ImGui::Text("Panic Key: *F8*");
			}
		}
		ImGui::EndChild();

		ImGui::BeginChild("##RightSide", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		{
			if (MenuTab == 5) {
				ImGui::Text("Config");
				ImGui::Separator();

				ImGui::Text(" Subscription Expiry: ");
				ImGui::SameLine();
				ImGui::Text(nameud.c_str());

				ImGui::Text(" ");

				
				if (ImGui::Button("Save Config", ImVec2(80, 40))) {
					SaveConfig();


				}


				if (ImGui::Button("Load Config", ImVec2(80, 40))) {
					LoadConfig();

				}
				


			}
		}
		ImGui::EndChild();




		ImGui::End();
	}



	ImGui::EndFrame();
	D3dDevice->SetRenderState(D3DRS_ZENABLE, false);
	D3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	D3dDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, false);
	D3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);

	if (D3dDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		D3dDevice->EndScene();
	}
	HRESULT result = D3dDevice->Present(NULL, NULL, NULL, NULL);

	if (result == D3DERR_DEVICELOST && D3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ImGui_ImplDX9_InvalidateDeviceObjects();
		D3dDevice->Reset(&d3dpp);
		ImGui_ImplDX9_CreateDeviceObjects();
	}
}