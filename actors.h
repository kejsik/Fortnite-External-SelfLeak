#pragma once 
#include "driver\general.h"
void CacheLevels()
{

	if (offname::localactorpawn)
	{
		std::vector<LootEntity> tmpList;
		uintptr_t ItemLevels = driver::read<uintptr_t>(offname::uworld + 0x160);

		for (int i = 0; i < driver::read<DWORD>(offname::uworld + (0x160 + sizeof(PVOID))); ++i) {

			uintptr_t ItemLevel = driver::read<uintptr_t>(ItemLevels + (i * sizeof(uintptr_t)));

			for (int i = 0; i < driver::read<DWORD>(ItemLevel + (0x98 + sizeof(PVOID))); ++i) {
				uintptr_t ItemsPawns = driver::read<uintptr_t>(ItemLevel + 0x98);
				uintptr_t CurrentItemPawn = driver::read<uintptr_t>(ItemsPawns + (i * sizeof(uintptr_t)));
				uintptr_t ItemRootComponent = driver::read<uintptr_t>(CurrentItemPawn + 0x190);
				Vector3 ItemPosition = driver::read<Vector3>(ItemRootComponent + 0x128); //0xF0 
				float ItemDist = localactorpos.Distance(ItemPosition) / 100.f;

				if (ItemDist < features::VisDist) {

					int ItemIndex = driver::read<int>(CurrentItemPawn + 0x18);//
					auto CurrentItemPawnName = GetNameFromFName(ItemIndex);

					if ((features::LootESP && strstr(CurrentItemPawnName.c_str(), (("AthenaPlayerMarker_WithCustomization")))) || strstr(CurrentItemPawnName.c_str(), (("Tiered_Chest"))) || strstr(CurrentItemPawnName.c_str(), (("AthenaSupplyDrop_C"))) || strstr(CurrentItemPawnName.c_str(), (("NPC_Pawn_Irwin_Prey_Nug_C"))) || strstr(CurrentItemPawnName.c_str(), (("NPC_Pawn_Irwin_Predator_Robert_C"))) || strstr(CurrentItemPawnName.c_str(), (("NPC_Pawn_Irwin_Prey_Burt_C"))) || strstr(CurrentItemPawnName.c_str(), (("NPC_Pawn_Irwin_Simple_Smackie_C"))) || strstr(CurrentItemPawnName.c_str(), (("NPC_Pawn_Irwin_Predator_Grandma_C"))) ||
						(features::VehicleEsp && strstr(CurrentItemPawnName.c_str(), ("Vehicl")) || strstr(CurrentItemPawnName.c_str(), ("Valet_Taxi")) ||
							strstr(CurrentItemPawnName.c_str(), ("Valet_BigRig")) || strstr(CurrentItemPawnName.c_str(), ("Valet_BasicTr")) ||
							strstr(CurrentItemPawnName.c_str(), ("Valet_SportsC")) || strstr(CurrentItemPawnName.c_str(), ("Valet_BasicC")) ||
							strstr(CurrentItemPawnName.c_str(), ("Tiered_Ammo")) || strstr(CurrentItemPawnName.c_str(), ("MeatballVehicle_L_C"))))
					{
						LootEntity LevelObjects{ };
						LevelObjects.ACurrentItem = CurrentItemPawn;
						LevelObjects.GNames = CurrentItemPawnName;
						tmpList.push_back(LevelObjects);
					}
				}
			}
		}
		LootentityList.clear();
		LootentityList = tmpList;
		Sleep(5000);
	}

}
bool IsVec3Valid(Vector3 vec3)
{
	return !(vec3.x == 0 && vec3.y == 0 && vec3.z == 0);
}
void world()
{
	while (true)
	{
		offname::uworld = driver::read<DWORD_PTR>(Identifier::ADDRESS + Offsets::External::UWORLD);
		offname::gameinst = driver::read<DWORD_PTR>(offname::uworld + Offsets::External::GAMEINST);
		offname::localactors = driver::read<DWORD_PTR>(offname::gameinst + Offsets::External::LOCALACTOR);
		offname::localactor = driver::read<DWORD_PTR>(offname::localactors);
		offname::controlactor = driver::read<DWORD_PTR>(offname::localactor + Offsets::External::LEVEL);
		offname::localactorpawn = driver::read<DWORD_PTR>(offname::controlactor + Offsets::External::ACTORPAWN);

		offname::actorstate = driver::read<DWORD_PTR>(offname::localactorpawn + Offsets::External::ACTORSTATE);
		offname::rootcomp = driver::read<DWORD_PTR>(offname::localactorpawn + Offsets::External::ROOTCOMPONENT);
		if (offname::localactorpawn != 0) {
			offname::localactorid = driver::read<int>(offname::localactorpawn + Offsets::External::ITEMDEF);//
		}
		offname::perslvl = driver::read<DWORD_PTR>(offname::uworld + Offsets::External::PERSLEVEL);
		offname::levels = driver::read<DWORD_PTR>(offname::uworld + Offsets::External::LEVELS);
		offname::actorcount = driver::read<DWORD>(offname::perslvl + Offsets::External::ACTORCOUNT);
		offname::aactors = driver::read<DWORD_PTR>(offname::perslvl + Offsets::External::AACTORS);

		std::vector<actors> actorlist;

		for (int i = 0; i < offname::actorcount; i++)
		{
			uint64_t curactor = driver::read<uint64_t>(offname::aactors + i * 0x8);

			int playerid = driver::read<int>(curactor + Offsets::External::ITEMDEF);

			std::string FName = GetNameFromFName(playerid);

			if (!curactor || curactor == offname::localactorpawn) continue;
			actors actorsgroup;
			if (driver::read<float>(curactor + 0x44a0) == 10  != 0x0 && playerid != 0x0 && curactor != 0x0)
			{
				uintptr_t entitymesh = driver::read<uintptr_t>(curactor + Offsets::External::MESH);
		
				DWORD64 otherPlayerState = driver::read<uint64_t>(curactor + Offsets::External::ACTORSTATE);
			
				uintptr_t localroot = driver::read<uintptr_t>(offname::localactorpawn + Offsets::External::ROOTCOMPONENT);
		
				uint64_t rootcomp = driver::read<uint64_t>(curactor + Offsets::External::ROOTCOMPONENT);
				

				int ActorTeamId = driver::read<int>(curactor + Offsets::External::TEAMID);
			

				actorsgroup.ACTOR = curactor;
				actorsgroup.PlayerState = otherPlayerState;
				actorsgroup.MESH = entitymesh;
				actorsgroup.localrootcomp = localroot;
				actorsgroup.rootcomp = rootcomp;
				actorsgroup.ActorTeamId = ActorTeamId;
				actorlist.push_back(actorsgroup);
			}
		}
		allplayers.clear();
		allplayers = actorlist;
		Sleep(1500);
	}
}
