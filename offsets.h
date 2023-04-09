#pragma once
#include <basetsd.h>
#include <stdint.h>

namespace offname
{
	DWORD_PTR uworld;
	DWORD_PTR gameinst;
	DWORD_PTR localactors;
	DWORD_PTR localactor;
	DWORD_PTR controlactor;
	DWORD_PTR localactorpawn;
	DWORD_PTR actorstate;
	DWORD_PTR rootcomp;
	DWORD_PTR perslvl;
	DWORD_PTR levels;
	DWORD_PTR actorcount;
	DWORD_PTR aactors;
	DWORD_PTR relativeloc;
	DWORD_PTR vischeck;
	int localactorid;
}

namespace Offsets
{
	enum External : uint64_t
	{
		UWORLD = 0xef005e0, //GWorld
		GAMEINST = 0x1b8, //UWorld	OwningGameInstance 0x1A8 0x80
		LOCALACTOR = 0x38,
		LEVEL = 0x30, 
		ACTORPAWN = 0x330,  //APlayerController	AcknowledgedPawn
		ACTORSTATE = 0x2A8, //APawn	PlayerState 0x2a8       0x290
		ROOTCOMPONENT = 0x190, //AActor	RootComponent
		ITEMDEF = 0x18, 
		PERSLEVEL = 0x30, //UWorld	PersistentLevel
		LEVELS = 0x160,  //UWorld Levels
		ACTORCOUNT = 0xA0,
		AACTORS = 0x98,
		CURACTOR = 0x8,
		MESH = 0x310, //ACharacter	Mesh 0x5c0 0x310
		CURRWEAPON = 0x8d8,
		RELATIVELOC = 0x128, //USceneComponent	RelativeLocation
		TEAMID = 0x10a0, //AFortPlayerStateAthena	TeamIndex
	};
}