#pragma once
#include <string>

namespace features
{
	bool supplydrop;
	bool ChestESP;
	bool enableloot;
	bool Marker;
	bool Animalesp;
	int BoxType = 3;
	const char* BoxTypes[4] = { "2D Box","CornerBox","Outline CornerBox","Internal Box"};
	int LineType = 3;
	bool weaponaimbot;
	bool univaimbot = true;
	bool flickbot;
	const char* LineTypes[3] = { "Top","Center","Bottom"};
	float lootdelay = 2;
	bool boxes2 = false;
	bool boxes = true;
	bool boxesc = false;
	bool disttop = true;
	bool distbottom = false;
	float aimspeed = 4.5;
	bool enemiesarround = true;
	bool target_lines = false;
	bool Ammoesp;
	bool randaim;
	float valueflick = 3.0f;
	bool chest = true;
	float fontsize = 14;
	bool backtrack;
	bool backtrack1;
	bool instrev;
	bool streamproof;
	bool backtrack2;
	bool backtrack3;
	bool backtrack4;
	bool visibleonlys;
	bool ammo = true;
	bool lines = true;
	bool Weapon = false;;
	bool BoxeFilled = false;
	bool distance = true;
	bool aimbot = true;
	bool LobbyEsp;
	bool b_cross = true;
	float VisDist = 450.f;
	bool LootESP;
	bool aimline;

	bool common{ true };
	bool uncommon{ true };
	bool rare{ true };
	bool epic{ true };
	bool legendary{ true };
	bool mythic{ true };



	bool rifleaiming;
	bool shotgunaiming;
	bool smgaiming;
	bool sniperaiming;
	float VisDistloot = 50.f;
	bool aimbot1 = false;
	bool aimbot2 = false;
	bool aimbot3 = false;
	bool aimbot4 = false;
	bool crosshair = false;
	bool headdot;
	int height = 15;
	int height2 = 30;
	bool fovcirclee = true;
	bool fovcirclee1;
	bool fovcirclee2;
	bool fovcirclee3;
	bool fovcirclee4;
	bool threedbox;
	bool randomaim = false;
	bool ads = false;
	bool infinitejump = false;
	bool menu = true;
	bool pfly = false;
	bool VehicleEsp;
	bool fovchanger = false;
	bool bigplayers = false;
	bool allan = false;
	bool aimpred = false;
	bool debug = false;
	static float smoothness = 9.5;
	static float smoothness1 = 9.5;
	static float smoothness2 = 9.5;
	static float smoothness3 = 9.5;
	static float smoothness4 = 9.5;
	static float Aimo = 250;
	static float fov = 125;
	static float fov1 = 100;
	static float fov2 = 100;
	static float fov3 = 100;
	static float fov4 = 100;
	float crossthick = 1.0f;
	static float randomspeed = 1000;
	float boxwidthlol = 0.5f;
	float width = 0.5f;
	int boxthick = 3;
	float fovvalue = 90.0f;
	bool curweapon;
	static int max_options = 1;
	static int aimkey = 1;
	std::string aimkeystr;
	static int hitbox = 68;
	static int aimkeypos = 1;
	static int lineesppos = 2;
	std::string lineespposstr;
	static int hitboxpos = 0;
	std::string hitboxposstr;

	float fov_valueX;
	float fov_valueY;
	float fov_valueZ;
}
namespace aimbot
{
	float aimspeed = 10.0f;
}
namespace aimbot1
{
	float aimspeed = 10.0f;
}
namespace aimbot2
{
	float aimspeed = 10.0f;
}
namespace aimbot3
{
	float aimspeed = 10.0f;
}
namespace aimbot4
{
	float aimspeed = 10.0f;
}
bool PositiveCurve;
bool nobloom;
bool rapidfire;
bool aiminair;
bool backtrackar;
bool backtrack;
bool backtrackshot;
bool backtracksmg;
bool backtracksnip;