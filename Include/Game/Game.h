#pragma once
#include "types.h"
#include "Game/Effect.h"
#include "Game/EventScript.h"
#include "Game/Fade.h"
#include "Game/Item.h"
#include "Game/Map.h"
#include "Game/NpChar.h"
#include "Game/Sound.h"

enum GAMEMODE
{
    GAMEMODE_OPENING,
    GAMEMODE_GAMEPLAY,
    GAMEMODE_EDITOR,
    GAMEMODE_INVENTORY,
    GAMEMODE_INTRO = 5,
    GAMEMODE_LOAD,
    GAMEMODE_STAFF,
    GAMEMODE_EPILOGUE,
};

//The current game mode (GAMEMODE). The IDB shows it as GameState::mode, but it is its own
//global at 0x1559EA (the code reads it through its own literal-pool address).
extern u8 gGameMode;
extern Map gMap;
extern NpChar gNpc[MAX_NPCS];
extern Items gItems;
extern Frame gFrame;
extern EventScr gEventScr;
extern PiyoCont gPiyoCont;
extern CaretSpawner gCaretSpawner[];

extern "C" int *GetTrg();
