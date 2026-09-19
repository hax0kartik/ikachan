#include "Game/Rect.h"
#include "Game/Map.h"
#include "Game/Player.h"
#include "Game/System.h"
#include "Game/Draw.h"
#include "Game/Boss.h"

//Background drawing
#define BACK_WIDTH (((SURFACE_WIDTH + 63) / 64) * 2 + 3)
#define BACK_HEIGHT (((SURFACE_HEIGHT + 63) / 64) * 2 + 3)

extern "C" void sub_127D94(u32*, float);
extern u32 stereocamera;

RECT rcBack[2] = {
		{ 0, 0, 32, 32 },
		{ 32, 0, 64, 32 },
};

void PutBack(Frame *frame)
{
	RECT rcBacktmp[2];
	sub_127D94(&stereocamera, 1.0f);
	rcBacktmp[0] = rcBack[0];
	rcBacktmp[1] = rcBack[1];
	for (int i = 0; i < (BACK_WIDTH * BACK_HEIGHT); i++)
	{
		PutBitmap3(&grcFull, 
			((i % BACK_WIDTH) * 32) - ((2 * (frame->x / 0x400)) / 3 % 64),
			((i / BACK_WIDTH) * 32) - ((2 * (frame->y / 0x400)) / 3 % 64),
			&rcBacktmp[i % 2],
			SURFACE_ID_BACK, -1);
	}
	sub_127D94(&stereocamera, 0.0f);
}

#define MAP_WIDTH ((SURFACE_WIDTH + 15) / 16 + 1)
#define MAP_HEIGHT ((SURFACE_HEIGHT + 15) / 16 + 1)

RECT rcParts[8] = {
	{   0, 0,  16, 16},
	{  16, 0,  32, 16},
	{  32, 0,  48, 16},
	{  48, 0,  64, 16},
	{  64, 0,  80, 16},
	{  80, 0,  96, 16},
	{  96, 0, 112, 16},
	{ 112, 0, 128, 16},
};

void PutMapBack(Map *map, int fx, int fy)
{
	//Draw tiles
	for (int y = (fy / 0x400) / 16; y < ((fy / 0x400) / 16 + MAP_HEIGHT); y++)
	{
		for (int x = (fx / 0x400) / 16; x < ((fx / 0x400) / 16 + MAP_WIDTH); x++)
		{
			//Check if this is a back tile
			u8 tile = map->data[x + map->width * y];
			if (tile != 0 && (
				(tile >> 5) == 0 ||
				(tile >> 5) == 2 ||
				(tile >> 5) == 4 ||
				(tile >> 5) == 5 ||
				(tile >> 5) == 7
				))
			{
				//Draw tile
				PutBitmap3(&grcFull,
					(x * 16) - (fx / 0x400),
					(y * 16) - (fy / 0x400),
					&rcParts[tile % 32],
					SURFACE_ID_PRTBACK + (tile >> 5), -1);
			}
		}
	}
}

void PutMapFront(Map *map, int fx, int fy)
{
	
}

void PutMapVector(Map *map, int fx, int fy)
{

}

void MoveFrame(Frame *frame, NpChar *npc, Map *map)
{
	//Get target position
	int tx, ty;

	switch (frame->mode)
	{
		case FRAME_MODE_MYCHAR:
			tx = gMC.x;
			ty = gMC.y;
			break;
		case FRAME_MODE_NPCHAR:
			tx = npc[frame->npc].x;
			ty = npc[frame->npc].y;
			break;
		case FRAME_MODE_BOSS:
			tx = gBoss.x;
			ty = gBoss.y;
			break;
	}

	//Move frame towards target
    int old_fx = frame->x;    
	if ((frame->x + (SURFACE_WIDTH << 9) - 0x2000) > tx)
		frame->x = old_fx + (tx - (frame->x + (SURFACE_WIDTH << 9) - 0x2000)) / 16;
	if ((frame->x + (SURFACE_WIDTH << 9) - 0x2000) < tx)
		frame->x += (tx - (frame->x + (SURFACE_WIDTH << 9) - 0x2000)) / 16;

    int old_fy = frame->y;  
	if ((frame->y + (SURFACE_HEIGHT2 << 9) - 0x2000) > ty)
		frame->y = old_fy + (ty - (frame->y + (SURFACE_HEIGHT2 << 9) - 0x2000)) / 16;
	if ((frame->y + (SURFACE_HEIGHT2 << 9) - 0x2000) < ty)
		frame->y += (ty - (frame->y + (SURFACE_HEIGHT2 << 9) - 0x2000)) / 16;

	if (frame->x < 0)
		frame->x = 0;
    if (frame->x > ((map->width - (SURFACE_WIDTH / 16)) << 14))
		frame->x = ((map->width - (SURFACE_WIDTH / 16)) << 14);

	if (frame->y < 0)
		frame->y = 0;
    if (frame->y > ((map->length - (SURFACE_HEIGHT / 16)) << 14))
		frame->y = ((map->length - (SURFACE_HEIGHT / 16)) << 14);
}