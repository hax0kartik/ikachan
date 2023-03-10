#include "Game/Rect.h"
#include "Game/Map.h"
#include "Game/Player.h"
#include "Game/System.h"
#include "Game/Draw.h"

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
