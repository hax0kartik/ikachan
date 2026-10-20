#include "Game/Player.h"
#include "Game/Effect.h"
#include "Game/System.h"
#include "Game/Sound.h"
#include "Game/Draw.h"
#include "Game/Map.h"
#include "Game/Game.h"

struct RawTexture;
extern RawTexture gMinimapTexture;
extern "C" void RawTexture_SetPixel(RawTexture *tex, u32 x, int y, u32 color);
extern "C" void RawTexture_Flush(RawTexture *tex);

extern "C" void RebuildMinimap()
{
    for (unsigned y = 0; y < gMap.length; y++)
    {
        for (unsigned x = 0; x < gMap.width; x++)
        {
            u8 atrb = gMap.GetAtrb(gMap.data[x + y * gMap.width]);
            u32 color = 0;
            if (atrb == 0x40)
                color = 0x32;
            else if ((atrb & 0x80) == 0 && atrb != 0)
            {
                if (atrb == 0x41)
                    color = 0xff;
                else if (atrb == 0x43)
                    color = 0x96;
            }
            RawTexture_SetPixel(&gMinimapTexture, x, y, color << 24);
        }
    }
    RawTexture_Flush(&gMinimapTexture);
}
