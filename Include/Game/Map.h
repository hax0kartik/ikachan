#pragma once
#include "Game/NpChar.h"

struct Map
{
	u8 unk[260];
	u8 *data;
	u8 fx;
	int width, length;
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
