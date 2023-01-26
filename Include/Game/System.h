#pragma once
#include "types.h"
//Keys
#define KEY_LEFT  (0x00000001)
#define KEY_RIGHT (0x00000002)
#define KEY_UP    (0x00000004)
#define KEY_DOWN  (0x00000008)
#define KEY_SPACE (0x00000010)
#define KEY_X     (0x00000020)
#define KEY_Z     (0x00000040)
#define KEY_S     (0x00000080)

extern u32 gKey, gKeyTrg;

//Window size
enum WND_SIZE
{
	WS_FULLSCREEN,
	WS_320x240,
};

int Random(int min, int max);