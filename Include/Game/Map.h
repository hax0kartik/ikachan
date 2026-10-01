#pragma once
#include "Game/NpChar.h"

struct Map
{
	char filename[256];
	u8 *atrb;
	u8 *data;
	u8 fx;
	int width, length;

	u8 GetTile(int x, int y) { return data[x + y * width]; }
	u8 GetAtrb(int tile) { return ((u32)tile < 0x100) ? atrb[tile] : 0; }
};

enum FRAME_MODE
{
	FRAME_MODE_MYCHAR,
	FRAME_MODE_NPCHAR,
	FRAME_MODE_BOSS,
};

struct Frame
{
	char mode;
	short npc;
	int x, y;
};

void PutBack(Frame *frame);
void PutMapBack(Map *map, int fx, int fy);
void PutMapFront(Map *map, int fx, int fy);
void PutMapVector(Map *map, int fx, int fy);
void MoveFrame(Frame *frame, NpChar *npc, Map *map);
void MoveFrameEditor(Frame *frame, Map *map);
