#include "Game/Epilogue.h"
#include "Game/System.h"
#include "Game/Draw.h"
#include "Game/Rect.h"
#include "Game/Game.h"
#include "Game/Sound.h"

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

int EpilogueScreen()
{
    int result;
    int started;

    gFade.mode = FADE_MODE_FADEIN;
    gFade.wait = 0;
    gFade.mask = false;
    gMap.width = 16;
    gMap.length = 12;

    RECT rcPicture = { 0, 0, 228, 209 };
    RECT rcIkachan = { 228, 35, 373, 209 };
    RECT rcTrail[4] =
    {
        { 420, 94, 512, 209 },
        { 445, 0, 512, 93 },
        { 373, 77, 420, 144 },
        { 384, 31, 414, 76 },
    };

    InitEpilogueBubbles();

    u32 trailColor[5] = { 0xFF252B5F, 0xFF485293, 0xFF7F82CD, 0xFFE7E4E0, 0xFFFFFFFF };

    int pictureX = 0;
    int pictureY = 0x1F00;
    int ikachanX = 0;
    int ikachanY = 0x15400;
    float depth = 0.4f;
    int trailFrame = 0;

    SetClearColor(&gSystem, 0.0f, 0.0f, 0.0627451f);
    gEventScr.msg_box = false;

    //Wait before the picture appears
    bool playedSound = false;
    unsigned int timer;
    for (timer = 1; timer < 120; timer++)
    {
        if (timer > 60 && !playedSound)
        {
            PlaySoundObject(17, -1);
            playedSound = true;
        }

        ProcessSystemEvents();
        BeginFrame(&gSystem);
        SetRenderTarget(&gSystem, 2);
        FinishFrame();
    }

    started = 0;
    SetClearColor(&gSystem, 0.0f, 0.0f, 0.0f);
    int eventStarted = 0;

    while (gGameMode == GAMEMODE_EPILOGUE)
    {
        if (++timer > 320 && started == 0)
            started = 1;

        ProcessSystemEvents();
        BeginFrame(&gSystem);
        PiyoPiyoControl(&gPiyoCont);
        GetTrg();
        PutEpilogueBubbles();

        //Scroll the picture
        depth += 0.0002f;
        pictureX -= 7;
        pictureY += 10;
        sub_127D94(&stereocamera, depth);
        int bgY = pictureY >> 8;
        PutBitmap3(&grcFull, pictureX >> 8, bgY, &rcPicture, SURFACE_ID_EPILOGUE, 0xFFFFFFFF);

        ikachanX += 115;
        ikachanY -= 160;
        sub_127D94(&stereocamera, 0.0f);
        unsigned int x = Random(-1, 1) + (ikachanX >> 8);
        int y = Random(-1, 1) + (ikachanY >> 8);

        //Animate the trail
        unsigned int phase = ++trailFrame & 3;
        PutBitmap3(&grcFull, x - 36, y + 145, &rcTrail[0], SURFACE_ID_EPILOGUE, trailColor[phase < 2]);
        PutBitmap3(&grcFull, x - 20, y + 145, &rcTrail[1], SURFACE_ID_EPILOGUE, trailColor[phase < 2 ? 2 : 1]);
        PutBitmap3(&grcFull, x - 3, y + 145, &rcTrail[2], SURFACE_ID_EPILOGUE, trailColor[phase < 2 ? 3 : 2]);
        PutBitmap3(&grcFull, x + 10, y + 145, &rcTrail[3], SURFACE_ID_EPILOGUE, trailColor[phase < 2 ? 4 : 3]);
        PutBitmap3(&grcFull, x, y, &rcIkachan, SURFACE_ID_EPILOGUE, 0xFFFFFFFF);

        if (x > 400)
        {
            if (gFade.mode == 0)
            {
                if (eventStarted == 0)
                {
                    gEventScr.event_no = 4001;
                    eventStarted = 1;
                    gEventScr.mode = 1;
                }
            }
        }

        ProcFade(&gFade, &gFrame, gCaretSpawner, 1);
        if (EventScriptProc(&gEventScr, &gItems, gNpc, &gMap, &gPiyoCont, &gFade, &gFrame) == 1)
        {
            gGameMode = GAMEMODE_OPENING;
            gFade.mode = FADE_MODE_FADEIN;
            gFade.wait = 0;
        }
        PutMsgBox(&gEventScr);
        SetRenderTarget(&gSystem, 2);
        PutEpilogueBubbles();
        ProcFade(&gFade, &gFrame, gCaretSpawner, 0);
        FinishFrame();
    }

    gFade.mask = true;
    result = 1;
    return result;
}
