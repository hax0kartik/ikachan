#include "Game/Epilogue.h"
#include "Game/System.h"
#include "Game/Draw.h"
#include "Game/Rect.h"

extern "C" void sub_127D94(u32*, float);
extern u32 stereocamera;

EpilogueBubble split(gEpilogueBubbles)[MAX_EPILOGUE_BUBBLES];

void InitEpilogueBubbles()
{
    for (unsigned int i = 0; i < MAX_EPILOGUE_BUBBLES; i++)
    {
        gEpilogueBubbles[i].x = Random(-20, 420);
        gEpilogueBubbles[i].y = Random(-20, 260);

        int roll = Random(0, 100);
        if (roll < 50)
            gEpilogueBubbles[i].type = 0;
        else if (roll < 75)
            gEpilogueBubbles[i].type = 1;
        else if (roll < 95)
            gEpilogueBubbles[i].type = 3;
        else
            gEpilogueBubbles[i].type = 4;

        // seems to increase the depth based on the type of bubble(?),
        // 0 = closest, 4 = farthest
        switch (gEpilogueBubbles[i].type)
        {
            case 0:
                gEpilogueBubbles[i].depth = Random(800, 1000) * 0.001f;
                break;
            case 1:
                gEpilogueBubbles[i].depth = Random(700, 900) * 0.001f;
                break;
            case 3:
                gEpilogueBubbles[i].depth = Random(600, 800) * 0.001f;
                break;
            case 4:
                gEpilogueBubbles[i].depth = Random(500, 700) * 0.001f;
                break;
        }

        int alpha = Random(100, 255);
        gEpilogueBubbles[i].alpha = alpha;
        gEpilogueBubbles[i].alphaBase = alpha;
        gEpilogueBubbles[i].alphaRange = Random(150, 200);
        gEpilogueBubbles[i].fadeIn = Random(0, 1) != 0;

        int wait = Random(0, 5);
        gEpilogueBubbles[i].waitMax = wait;
        gEpilogueBubbles[i].wait = wait;
    }
}

void PutEpilogueBubbles()
{
    static RECT split(rcBubble)[5] =
    {
        { 228, 0, 241, 13 },
        { 241, 0, 254, 13 },
        { 254, 0, 267, 13 },
        { 267, 0, 280, 13 },
        { 280, 0, 293, 13 },
    };

    for (unsigned int i = 0; i < MAX_EPILOGUE_BUBBLES; i++)
    {

        // only update alpha once wait reaches 0
        if (--gEpilogueBubbles[i].wait <= 0)
        {
            gEpilogueBubbles[i].wait = gEpilogueBubbles[i].waitMax;

            if (gEpilogueBubbles[i].fadeIn) // fade in
            {
                gEpilogueBubbles[i].alpha++;

                if (gEpilogueBubbles[i].alpha >= gEpilogueBubbles[i].alphaBase + gEpilogueBubbles[i].alphaRange)
                    gEpilogueBubbles[i].fadeIn = false;

                if (gEpilogueBubbles[i].alpha > 255)
                {
                    gEpilogueBubbles[i].alpha = 255;
                    gEpilogueBubbles[i].fadeIn = false;
                }
            }
            else // fade out
            {
                gEpilogueBubbles[i].alpha--;

                if (gEpilogueBubbles[i].alpha <= gEpilogueBubbles[i].alphaBase - gEpilogueBubbles[i].alphaRange)
                    gEpilogueBubbles[i].fadeIn = true;

                if (gEpilogueBubbles[i].alpha < 0)
                {
                    gEpilogueBubbles[i].alpha = 0;
                    gEpilogueBubbles[i].fadeIn = true;
                }
            }
        }

        //depth is calcualted based on the type of bubble
        sub_127D94(&stereocamera, gEpilogueBubbles[i].depth);
        PutBitmap3(&grcFull, gEpilogueBubbles[i].x, gEpilogueBubbles[i].y, &rcBubble[gEpilogueBubbles[i].type], SURFACE_ID_EPILOGUE, (gEpilogueBubbles[i].alpha << 24) | 0xFFFFFF);
    }

    sub_127D94(&stereocamera, 0.0f);
}
