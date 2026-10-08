#include "Game/Rect.h"
#include "Game/NpChar.h"
#include "Game/Player.h"
#include "Game/Map.h"
#include "Game/Draw.h"
#include "Game/EventScript.h"
#include "Game/Effect.h"
#include "Game/Sound.h"

void InitNpChar(NpChar *npc)
{
    for (int i = 0; i < 100; i++) {
        npc[i].cond = false;
        npc[i].type = 0;
        npc[i].code_char = 0;
        npc[i].code_event = 0;
        npc[i].act_wait = 0;
        npc[i].act_no = 0;
        npc[i].ani_no = 0;
        npc[i].ani_wait = 0;
        npc[i].direct = 0;
        npc[i].x = 0;
        npc[i].y = 0;
        npc[i].xm = 0;
        npc[i].ym = 0;
        npc[i].tgt_x = 0;
        npc[i].tgt_y = 0;
    }
}

void PutNpChar00(NpChar *npc, Frame *frame)
{
    static RECT rcNpc00[8] = {
        {  0,  0, 16, 16 },
        { 16,  0, 32, 16 },
        { 32,  0, 48, 16 },
        { 48,  0, 64, 16 },
        {  0, 16, 16, 32 },
        { 16, 16, 32, 32 },
        { 32, 16, 48, 32 },
        { 48, 16, 64, 32 },
    };
    
    if (npc->cond != false)
    {
        char rectIdx = npc->direct * 4 + npc->ani_no;
        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400),
                   (npc->y / 0x400) - (frame->y / 0x400),
                   &rcNpc00[rectIdx],
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

void PutNpChar01(NpChar *npc, Frame *frame)
{
    static RECT rcNpc01[4] = {
        { 0,  0, 16, 16 },
        { 0, 16, 16, 32 },
        { 0, 32, 16, 48 },
        { 0, 48, 16, 64 },
    };

    if (npc->cond != false)
    {
        char rectIdx = npc->direct * 2 + npc->ani_no;
        RECT rect = rcNpc01[rectIdx];
        int incBy = ((npc->tgt_x - npc->x) / 0x4000);
        rect.left += 16 * incBy;
        rect.right = rect.left + 16;

        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400),
                   (npc->y / 0x400) - (frame->y / 0x400),
                   &rect,
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

void PutNpChar02(NpChar *npc, Frame *frame)
{
    static RECT rcNpc02[8] = {
        {  0,  0, 16, 16 },
        { 16,  0, 32, 16 },
        {  0, 16, 16, 32 },
        { 16, 16, 32, 32 },
        {  0,  0, 16, 16 },
        { 16,  0, 32, 16 },
        {  0, 16, 16, 32 },
        { 16, 16, 32, 32 },
    };

    if (npc->cond != false)
    {
        char rectIdx = npc->direct * 4 + npc->ani_no;
        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400),
                   (npc->y / 0x400) - (frame->y / 0x400),
                   &rcNpc02[rectIdx],
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

void PutNpChar03(NpChar *npc, Frame *frame)
{
    static RECT rcNpc03[4] = {
        {  0,  0, 20, 20 },
        { 20,  0, 40, 20 },
        {  0, 20, 20, 40 },
        { 20, 20, 40, 40 },
    };

    if (npc->cond != false)
    {
        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400) - 2,
                   (npc->y / 0x400) - (frame->y / 0x400) - 4,
                   &rcNpc03[npc->ani_no],
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

void PutNpChar04(NpChar *npc, Frame *frame)
{
    static RECT rcNpc04[6] = {
        {  0, 0,  8,  8 },
        {  0, 8,  8, 16 },
        {  8, 0, 16,  8 },
        {  8, 8, 16, 16 },
        { 16, 0, 24,  8 },
        { 16, 8, 24, 16 },
    };

    if (npc->cond != false)
    {
        char rectIdx = npc->direct * 2 + npc->ani_no;
        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400) + 4,
                   (npc->y / 0x400) - (frame->y / 0x400) + 4,
                   &rcNpc04[rectIdx],
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

void PutNpChar05(NpChar *npc, Frame *frame)
{
    static RECT rcNpc05[6] = {
        {  0,  0, 16, 16 },
        {  0, 16, 16, 32 },
        { 16,  0, 32, 16 },
        { 16, 16, 32, 32 },
        { 32,  0, 48, 16 },
        { 32, 16, 48, 32 },
    };

    if (npc->cond != false)
    {
        char rectIdx = npc->direct * 2 + npc->ani_no;
        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400),
                   (npc->y / 0x400) - (frame->y / 0x400),
                   &rcNpc05[rectIdx],
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

void PutNpChar06(NpChar *npc, Frame *frame)
{
    static RECT rcNpc06[4] = {
        {  0,  0, 30, 20 },
        {  0, 20, 30, 40 },
        { 30,  0, 60, 20 },
        { 30, 20, 60, 40 },
    };
    
    if (npc->cond != false)
    {
        char rectIdx = npc->direct * 2 + npc->ani_no;
        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400) - 6,
                   (npc->y / 0x400) - (frame->y / 0x400) - 2,
                   &rcNpc06[rectIdx],
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

void PutNpChar07(NpChar *npc, Frame *frame)
{
    static RECT rcNpc07 = { 0, 0, 32, 32 };
    
    if (npc->cond != false)
    {
        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400) - 8,
                   (npc->y / 0x400) - (frame->y / 0x400) - 16,
                   &rcNpc07,
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

void PutNpChar08(NpChar *npc, Frame *frame)
{
    static RECT rcNpc08[9] = {
        {  0,  0, 16, 16 },
        {  0, 16, 16, 32 },
        { 16,  0, 32, 16 },
        { 32,  0, 48, 16 },
        { 32, 16, 48, 32 },
        { 48,  0, 64, 16 },
        { 48, 16, 64, 32 },
        { 48, 32, 64, 48 },
        { 48, 48, 64, 64 },
    };

    if (npc->cond != false)
    {
        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400),
                   (npc->y / 0x400) - (frame->y / 0x400) + 1,
                   &rcNpc08[npc->ani_no],
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

void PutNpChar09(NpChar *npc, Frame *frame)
{
    static RECT rcNpc09[6] = {
        {  0,  0, 16, 16 },
        {  0, 16, 16, 32 },
        {  0, 32, 16, 48 },
        { 16,  0, 32, 16 },
        { 16, 16, 32, 32 },
        { 16, 32, 32, 48 },
    };

    if (npc->cond != false)
    {
        char rectIdx = npc->ani_no + npc->direct * 3;
        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400),
                   (npc->y / 0x400) - (frame->y / 0x400),
                   &rcNpc09[rectIdx],
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

void PutNpChar10(NpChar *npc, Frame *frame)
{
    static RECT rcNpc10[4] = {
        {  0,  0, 16, 16 },
        {  0, 16, 16, 32 },
        { 16,  0, 32, 16 },
        { 16, 16, 32, 32 },
    };

    if (npc->cond != false)
    {
        char rectIdx = npc->direct * 2 + npc->ani_no;
        PutBitmap3(&grcFull,
                   (npc->x / 0x400) - (frame->x / 0x400),
                   (npc->y / 0x400) - (frame->y / 0x400),
                   &rcNpc10[rectIdx],
                   SURFACE_ID_HARI + npc->code_char, -1);
    }
}

typedef void (*NPCPUT)(NpChar*, Frame*);
NPCPUT split(gpNpcPutTbl)[] = {
    PutNpChar00,
    PutNpChar01,
    PutNpChar02,
    PutNpChar03,
    PutNpChar04,
    PutNpChar05,
    PutNpChar01,
    PutNpChar06,
    PutNpChar00,
    PutNpChar07,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PutNpChar08,
    PutNpChar09,
    PutNpChar10,
};

extern "C" void sub_127D94(u32*, float);
extern u32 stereocamera;

void PutNpChar(NpChar *npc, Frame *frame)
{
    sub_127D94(&stereocamera, 0.5f);

    for (int i = 0; i < MAX_NPCS; i++, npc++)
    {
        if (npc->cond)
        {
            NPCPUT put = gpNpcPutTbl[npc->code_char];
            if (put)
                put(npc, frame);
        }
    }

    sub_127D94(&stereocamera, 0.0f);
}

void ActNpChar00(NpChar *npc)
{
    MyChar *mc = &gMC;
    switch (npc->act_no)
    {
        case 0:
            //Move towards target
            if (npc->x > npc->tgt_x)
                npc->xm -= 6;
            if (npc->x < npc->tgt_x)
                npc->xm += 6;
            if (npc->y > npc->tgt_y)
                npc->ym -= 4;
            if (npc->y < npc->tgt_y)
                npc->ym += 4;

            //Face direction moving
            if (npc->xm < 0)
                npc->direct = 0;
            if (npc->xm > 0)
                npc->direct = 1;

            //Animate
            if (++npc->ani_wait > 60)
            {
                npc->ani_wait = 0;
                if (++npc->ani_no > 1)
                    npc->ani_no = 0;
            }

            //Limit speed
            if (npc->xm > 0x800)
                npc->xm = 0x800;
            if (npc->xm < -0x800)
                npc->xm = -0x800;
            if (npc->ym > 0x800)
                npc->ym = 0x800;
            if (npc->ym < -0x800)
                npc->ym = -0x800;

            //Move
            npc->x += npc->xm;
            npc->y += npc->ym;

            //Puff up if Ikachan is nearby (and doesn't have a pearl)
            if (npc->act_wait > 0)
                npc->act_wait--;
            if (npc->act_wait == 0 && !(mc->equip & 4) &&
                npc->x - 0xA000 < mc->x && npc->x + 0xA000 > mc->x &&
                npc->y - 0xA000 < mc->y && npc->y + 0xA000 > mc->y)
            {
                if (npc->type == 2)
                    npc->act_no = 1;
                npc->act_wait = 300;
            }
            break;

        case 1:
            //Face towards Ikachan
            if (npc->x > mc->x)
                npc->direct = 0;
            if (npc->x < mc->x)
                npc->direct = 1;

            //Animate
            if (++npc->ani_wait > 2)
            {
                npc->ani_wait = 0;
                if (++npc->ani_no > 3)
                    npc->ani_no = 2;
            }

            //Stop puffing up after 100 frames
            if (--npc->act_wait <= 200)
            {
                npc->act_no = 0;
                npc->ani_no = 0;
            }
            break;
    }
}

void ActNpChar01(NpChar *npc)
{
    //Increment animation timer
    npc->ani_wait++;
    
    //Fall and move
    if (npc->ym < 0x800)
        npc->ym += 20;
    npc->y += npc->ym;
    
    //Face towards Ikachan
    if (npc->x < gMC.x)
        npc->direct = 1;
    if (npc->x > gMC.x)
        npc->direct = 0;
    
    //Animate
    if (npc->ani_wait > 40)
    {
        npc->ani_wait = 0;
        if (++npc->ani_no > 1)
            npc->ani_no = 0;
    }
}

void ActNpChar02(NpChar *npc)
{
    if (npc->act_no == 0) {
        //Turn around if too far from home
        if (npc->x < npc->tgt_x - 0x10000)
            npc->direct = 1;
        if (npc->x > npc->tgt_x + 0x10000)
            npc->direct = 0;
        
        //Move in facing direction
        if (npc->direct == 0 && npc->xm > -0x200 )
            npc->xm -= 16;
        if (npc->direct == 1 && npc->xm < 0x200 )
            npc->xm += 16;
        
        //Jump after we've been on the ground for 80 frames
        if (npc->airborne == false)
            npc->act_wait++;
        
        if (npc->act_wait > 80)
        {
            npc->act_wait = 0;
            if (npc->type == 2 && (gMC.equip & 4) == 0)
            {
                //Attacking jump
                npc->ym = -1536;
                npc->act_no = 1;

            }
            else
            {
                //Jump
                npc->ym = -1024;
            }
        }
        
        //Animate
        if (++npc->ani_wait > 10)
        {
            npc->ani_wait = 0;
            if (++npc->ani_no > 1)
                npc->ani_no = 0;
        }
        
        //Fall and move
        if (npc->ym < 0x800)
            npc->ym += 20;
        npc->x += npc->xm;
        npc->y += npc->ym;
        
        //Do falling animation if airborne
        if (npc->airborne == true)
            npc->ani_no = 2;
    } else if (npc->act_no == 1) {
        //Animate
        if (++npc->ani_wait > 2)
        {
            npc->ani_wait = 0;
            if (++npc->ani_no > 3)
                npc->ani_no = 2;
        }
        
        //Turn around if too far from home
        if (npc->x < npc->tgt_x - 0x10000)
            npc->direct = 1;
        if (npc->x > npc->tgt_x + 0x10000)
            npc->direct = 0;
        
        //Move in facing direction
        if (npc->direct == 0 && npc->xm > -0x200 )
            npc->xm -= 16;
        if (npc->direct == 1 && npc->xm < 0x200 )
            npc->xm += 16;
        
        //Fall and move
        if (npc->ym < 0x800)
            npc->ym += 20;
        npc->x += npc->xm;
        npc->y += npc->ym;
        
        //Stop attacking once moving down
        if (npc->ym > 0)
            npc->act_no = 0;
    }
}

void ActNpChar03(NpChar *npc)
{
    //Fall and move
    if (npc->ym < 0x800)
        npc->ym += 20;
    npc->y += npc->ym;
    
    //Animate
    if (npc->act_no == 0)
    {
        if (npc->act_wait > 0)
            npc->act_wait--;
        if ((npc->x - 0x8000) < gMC.x && (npc->x + 0x8000) > gMC.x && (npc->y - 0x8000) < gMC.y && npc->y > gMC.y)
        {
            if (++npc->ani_wait > 2)
            {
                npc->ani_wait = 0;
                if (++npc->ani_no > 3)
                    npc->ani_no = 3;
            }
        }
        else if (++npc->ani_wait > 5)
        {
            npc->ani_wait = 0;
            char ani_no = --npc->ani_no;
            if (ani_no < 0)
                npc->ani_no = 0;
        }
    }
}

void ActNpChar04(NpChar *npc)
{
    //Move towards Ikachan
    if (npc->x > gMC.x)
        npc->xm -= 24;
    if (npc->x < gMC.x)
        npc->xm += 24;
    if (npc->y > gMC.y)
        npc->ym -= 16;
    if (npc->y < gMC.y)
        npc->ym += 16;
    
    //Face towards Ikachan
    if (npc->x > gMC.x)
        npc->direct = 0;
    if (npc->x < gMC.x)
        npc->direct = 1;
    if ((npc->x - 0x8000) < gMC.x && (npc->x + 0x8000) > gMC.x && (npc->y - 0x8000) < gMC.y && (npc->y + 0x8000) > gMC.y)
        npc->direct = 2;
    if ((npc->y + 0x2000) > gMC.y)
        npc->act_no = 1;
    else
        npc->act_no = 0;
    
    //Animate
    if (++npc->ani_wait > 8)
    {
        npc->ani_wait = 0;
        if (++npc->ani_no > 1)
            npc->ani_no = 0;
    }
    
    //Limit speed
    if (npc->xm > 0x400)
        npc->xm = 0x400;
    if (npc->xm < -0x400)
        npc->xm = -0x400;
    if (npc->ym > 0x400)
        npc->ym = 0x400;
    if (npc->ym < -0x400)
        npc->ym = -0x400;
    
    //Move
    npc->x += npc->xm;
    npc->y += npc->ym;
}

void ActNpChar05(NpChar *npc)
{
    //Fall and move
    if (npc->ym < 0x800)
        npc->ym += 20;
    npc->y += npc->ym;
}

void ActNpChar06(NpChar *npc)
{
    if (npc->act_no == 0)
    {
        //Move towards target
        if (npc->x > npc->tgt_x)
            npc->xm -= 12;
        if (npc->x < npc->tgt_x)
            npc->xm += 12;
        if (npc->y > npc->tgt_y)
            npc->ym -= 8;
        if (npc->y < npc->tgt_y)
            npc->ym += 8;
        
        //Face in moving direction
        if (npc->xm < 0)
            npc->direct = 0;
        if (npc->xm > 0)
            npc->direct = 1;
        
        //Animate
        if (++npc->ani_wait > 30)
        {
            npc->ani_wait = 0;
            if (++npc->ani_no > 1)
                npc->ani_no = 0;
        }
        
        //Limit speed
        if (npc->xm > 0x800)
            npc->xm = 0x800;
        if (npc->xm < -0x800)
            npc->xm = -0x800;
        if (npc->ym > 0x800)
            npc->ym = 0x800;
        if (npc->ym < -0x800)
            npc->ym = -0x800;
        
        //Move
        npc->x += npc->xm;
        npc->y += npc->ym;
    }
}

void ActNpChar08(NpChar *npc)
{
    //Move
    npc->x += npc->xm;
    if (npc->ym < 0x800)
        npc->ym += 20;
    npc->y += npc->ym;
    if ((npc->y + 0x2000) > gMC.y)
        npc->act_no = 1;
    else
        npc->act_no = 0;

    switch (npc->act_wait)
    {
        case 0:
            //Wait, then jump
            if (++npc->ani_wait > 30)
            {
                npc->ani_wait = 0;
                npc->ani_no = 1;
                npc->act_wait = 1;
                npc->ym = -0x76D;
                if (!npc->direct)
                {
                    npc->xm = 0x200;
                    npc->xm = -npc->xm;
                }
                else
                {
                    npc->xm = 0x200;
                }
            }
            break;
        case 1:
            //Falling frame
            if (npc->ym > 0)
                npc->ani_no = 2;

            //Hit ceiling
            if ((npc->flag & 2) && npc->ym < 0)
                npc->ym = 0;

            //Bounce off walls
            if ((npc->flag & 4) && npc->direct == 1)
            {
                npc->direct = 0;
                npc->xm = -0x200;
            }
            if ((npc->flag & 1) && npc->direct == 0)
            {
                npc->direct = 1;
                npc->xm = 0x200;
            }

            //Land
            if ((npc->flag & 8) && npc->ym > 0)
            {
                npc->xm = 0;
                npc->act_wait = 0;
                npc->ani_no = 0;
            }
            break;
    }
}

void ActNpChar07(NpChar *npc)
{
    int wait = npc->act_wait;
    switch (wait)
    {
        case 0:
            //Wait for Ikachan to come close
            npc->act_no = 0;
            if (npc->ym < 0x800)
                npc->ym += 20;
            npc->y += npc->ym;
            ++npc->ani_wait;
            if (npc->ani_wait > 15)
            {
                npc->ani_wait = 0;
                if (++npc->ani_no > 1)
                    npc->ani_no = 0;
            }
            MyChar *mc = &gMC;
            int mcx = mc->x;
            int x = npc->x;
            if (x <= mcx + 0x7000 && mcx <= x + 0x7000 && npc->y - mc->y - 0x4000 < 0x40000)
            {
                npc->ani_wait = 0;
                npc->ani_no = 2;
                npc->act_wait = 1;
            }
            break;
        case 1:
            //Crouch, then jump
            npc->act_no = 1;
            if (++npc->ani_wait > 30)
            {
                npc->ani_wait = 0;
                npc->ani_no = 3;
                npc->act_wait = 2;
                npc->ym = -0x400;
            }
            break;
        case 2:
            //Rise until hitting the ceiling
            npc->act_no = 1;
            npc->y += npc->ym;
            ++npc->ani_wait;
            if (npc->ani_wait > 8)
            {
                npc->ani_wait = 0;
                if (++npc->ani_no > 4)
                    npc->ani_no = 3;
            }
            if (npc->flag & 2)
            {
                npc->ani_wait = 0;
                npc->ani_no = 5;
                npc->act_wait = 3;
            }
            break;
        case 3:
            //Fall until landing
            npc->act_no = 0;
            if (npc->ym < 0x800)
                npc->ym += 20;
            npc->y += npc->ym;
            if (++npc->ani_wait > 8)
            {
                npc->ani_wait = 0;
                if (++npc->ani_no > 8)
                    npc->ani_no = 5;
            }
            if ((npc->flag & 8) && (npc->ani_no == 5 || npc->ani_no == 6))
            {
                npc->ani_wait = 0;
                npc->ani_no = 5;
                npc->act_wait = 4;
            }
            break;
        case 4:
            //Land
            npc->act_no = 0;
            if (npc->ym < 0x800)
                npc->ym += 20;
            npc->y += npc->ym;
            if (++npc->ani_wait > 15)
            {
                npc->ani_wait = 0;
                npc->ani_no = 0;
                npc->act_wait = 0;
            }
            break;
    }
}

void ActNpChar09(NpChar *npc)
{
    if ((npc->y + 0x2000) > gMC.y)
        npc->act_no = 1;
    else
        npc->act_no = 0;

    switch (npc->act_wait)
    {
        case 0:
            //Wait, then dash
            npc->xm = 0;
            if (++npc->ani_wait > 30)
            {
                npc->ani_wait = 0;
                npc->ani_no = 1;
                npc->act_wait = 1;
                npc->xm = npc->direct == 1 ? 0x400 : -0x400;
            }
            break;
        case 1:
            //Dash, bouncing off walls, and slow down
            if (npc->direct == 1 && (npc->flag & 4))
            {
                npc->direct = 0;
                npc->xm = -npc->tgt_x;
            }
            else if (npc->direct == 0 && (npc->flag & 1))
            {
                npc->direct = 1;
                npc->xm = -npc->tgt_x;
            }
            else
            {
                if (npc->direct == 1)
                {
                    npc->xm -= 15;
                    if (npc->xm <= 0)
                    {
                        npc->ani_no = 0;
                        npc->act_wait = 0;
                    }
                }
                else
                {
                    npc->xm += 15;
                    if (npc->xm >= 0)
                    {
                        npc->ani_no = 0;
                        npc->act_wait = 0;
                    }
                }
                npc->tgt_x = npc->xm;
            }
            break;
    }

    npc->x += npc->xm;
}

void HitMyCharNpChar(NpChar *npc, EventScr *event_scr, CaretSpawner *caret_spawner)
{
    bool touch;
    for (int i = 0; i < MAX_NPCS; i++, npc++)
    {
        touch = false;
        if (npc->cond == false)
            continue;

        if (npc->type == 3 || (npc->type == 2 && gMC.shock == 0))
        {
            //Solid contact
            if (gMC.x < npc->x + 0x3400 && gMC.x > npc->x + 0x2000 && gMC.y < npc->y + 0x3000 && gMC.y > npc->y - 0x3000)
            {
                gMC.x = npc->x + 0x3400;
                gMC.xm = 0;
                gMC.flag |= 1;
                touch = true;
            }
            if (gMC.y < npc->y + 0x3400 && gMC.y > npc->y + 0x2000 && gMC.x < npc->x + 0x3000 && gMC.x > npc->x - 0x3000)
            {
                if (gMC.ym < -100)
                    PlaySoundObject(SOUND_ID_HITHEAD, SOUND_MODE_PLAY);
                gMC.y = npc->y + 0x3400;
                gMC.ym = 0;
                gMC.flag |= 2;
                touch = true;
            }
            if (gMC.x > npc->x - 0x3400 && gMC.x + 0x3FF < npc->x - 0x2000 && gMC.y < npc->y + 0x3000 && gMC.y > npc->y - 0x3000)
            {
                gMC.x = npc->x - 0x3400;
                gMC.xm = 0;
                gMC.flag |= 4;
                touch = true;
            }
            if (gMC.y >= npc->y - 0x3400 && gMC.y < npc->y - 0x2000 && gMC.x > npc->x - 0x3000 && gMC.x < npc->x + 0x3000)
            {
                gMC.airborne = false;
                gMC.y = npc->y - 0x3400;
                if (gMC.ym > 0)
                    gMC.ym = 0;
                gMC.flag |= 8;
                touch = true;
            }
        }
        else
        {
            //Non-solid contact
            if (npc->type == 0 &&
                gMC.no_event == 0 &&
                gMC.x < npc->x + 0x1000 &&
                npc->x - 0x1000 < gMC.x &&
                gMC.y < npc->y + 0x1000 &&
                npc->y - 0x1000 < gMC.y)
            {
                //Start NPC's event
                event_scr->mode = 1;
                event_scr->x1C = 4;
                event_scr->event_no = npc->code_event;
                gMC.no_event = 100;
                continue;
            }
        }

        if (touch && gMC.no_event == 0)
        {
            static char npc_damage[] = { 1, 0, 2, 4, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1 };
            static char npc_defense[] = { 1, 4, 2, 9, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 };
            static char npc_exp[] = { 1, 0, 3, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 };

            switch (npc->type)
            {
                case 2:
                    //Hurt Ikachan
                    if (npc->act_no == 1)
                    {
                        if (gMC.x < npc->x)
                            gMC.xm = -0x400;
                        if (gMC.x > npc->x)
                            gMC.xm = 0x400;
                        DamageMyChar(caret_spawner, npc_damage[npc->code_char]);
                    }

                    //Check if we should hurt the NPC
                    if (gMC.flag != 0 && gMC.unit == 1 && gMC.flag != 8 || (gMC.flag & 2) && (gMC.equip & 1))
                    {
                        if (npc_defense[npc->code_char] <= gMC.level)
                        {
                            //Award us experience
                            PlaySoundObject(SOUND_ID_WIN, SOUND_MODE_PLAY);
                            gMC.exp += npc_exp[npc->code_char];
                            gMC.exp_wait = 20;
                            int exp_i = FindCaretSpawner(caret_spawner);
                            if (exp_i != 0xFFFFFF)
                            {
                                CaretSpawner *caretsp = &caret_spawner[exp_i];
                                caretsp->cond = true;
                                caretsp->type = 2;
                                caretsp->ani_no = npc_exp[npc->code_char] + 10;
                                caretsp->num = 1;
                                caretsp->x = npc->x + 0x2000;
                                caretsp->y = npc->y - 0x1000;
                                caretsp->rand_x = 1;
                                caretsp->rand_y = 0;
                            }

                            //Destroy the NPC
                            npc->cond = false;
                            int dead_i = FindCaretSpawner(caret_spawner);
                            if (dead_i != 0xFFFFFF)
                            {
                                CaretSpawner *caretsp = &caret_spawner[dead_i];
                                caretsp->cond = true;
                                caretsp->type = 0;
                                caretsp->ani_no = 0;
                                caretsp->num = 6;
                                caretsp->x = npc->x + 0x2000;
                                caretsp->y = npc->y + 0x2000;
                                caretsp->rand_moveright = 0x800;
                                caretsp->rand_moveleft = -0x800;
                                caretsp->rand_movedown = -0x200;
                                caretsp->rand_moveup = -0x800;
                                caretsp->rand_x = 8;
                                caretsp->rand_y = 8;
                            }

                            //Start NPC's event
                            event_scr->mode = 1;
                            event_scr->x1C = 4;
                            event_scr->event_no = npc->code_event;
                            gMC.no_event = 100;
                            continue;
                        }
                        else
                        {
                            //The NPC was too strong
                            if (gMC.no_event == 0)
                                PlaySoundObject(SOUND_ID_NODMG, SOUND_MODE_PLAY);
                            gMC.no_event = 100;
                        }
                    }
                    break;

                case 3:
                    //Start NPC's event
                    event_scr->mode = 1;
                    event_scr->x1C = 4;
                    event_scr->event_no = npc->code_event;
                    gMC.no_event = 100;
                    break;
            }
        }
    }
}

typedef void (*NPCACT)(NpChar*);
NPCACT gpNpcActTbl[] = {
    ActNpChar00,
    ActNpChar01,
    ActNpChar02,
    ActNpChar03,
    ActNpChar04,
    ActNpChar04,
    ActNpChar05,
    ActNpChar01,
    ActNpChar06,
    ActNpChar05,
};

void ActNpChar(NpChar *npc)
{
    for (int i = 0; i < MAX_NPCS; i++){
        if (npc->cond){
            NPCACT act = gpNpcActTbl[npc->code_char];
            if(act)
                act(npc);
        }
        npc++;
    }
}

//NPC collision
char JudgeHitNpCharBlock(NpChar *npc, int x, int y, char flag)
{
    if ((flag & 1) && (flag & 2))
    {
        if ((npc->x / 0x400) < (x * 16 + 15) && (npc->y / 0x400) < (y * 16 + 12))
        {
            npc->x = (x * 16 + 15) << 10;
            npc->xm = 0;
            npc->flag |= 1;
        }
        if ((npc->y / 0x400) < (y * 16 + 15) && (npc->x / 0x400) < (x * 16 + 12))
        {
            npc->y = (y * 16 + 16) << 10;
            npc->ym = 0;
            npc->flag |= 2;
        }
    }
    
    if ((flag & 4) && (flag & 2))
    {
        if (((npc->x + 0x3FF) / 0x400) > (x * 16 - 14) && (npc->y / 0x400) < (y * 16 + 12))
        {
            npc->x = (x * 16 - 14) << 10;
            npc->xm = 0;
            npc->flag |= 4;
        }
        if ((npc->y / 0x400) < (y * 16 + 15) && (npc->x / 0x400) > (x * 16 - 12))
        {
            npc->y = (y * 16 + 16) << 10;
            npc->ym = 0;
            npc->flag |= 2;
        }
    }
    
    if ((flag & 1) && (flag & 8))
    {
        if ((npc->x / 0x400) < (x * 16 + 15) && (npc->y / 0x400) > (y * 16 - 12))
        {
            npc->x = (x * 16 + 15) << 10;
            npc->xm = 0;
            npc->flag |= 1;
        }
        if ((npc->y / 0x400) >= (y * 16 - 16) && (npc->x / 0x400) < (x * 16 + 12))
        {
            npc->airborne = false;
            npc->y = (y * 16 - 16) << 10;
            if (npc->ym > 0)
                npc->ym = 0;
            npc->flag |= 8;
        }
    }
    
    if ((flag & 4) && (flag & 8))
    {
        if (((npc->x + 0x3FF) / 0x400) > (x * 16 - 14) && (npc->y / 0x400) > (y * 16 - 12))
        {
            npc->x = (x * 16 - 14) << 10;
            npc->xm = 0;
            npc->flag |= 4;
        }
        if ((npc->y / 0x400) >= (y * 16 - 16) && (npc->x / 0x400) > (x * 16 - 12))
        {
            npc->airborne = false;
            npc->y = (y * 16 - 16) << 10;
            if (npc->ym > 0)
                npc->ym = 0;
            npc->flag |= 8;
        }
    }
    
    return npc->flag;
}

void HitNpCharMap(NpChar *npc, Map *map)
{
    //Collision offsets and flags
    char offx[4] = { 0, 1, 0, 1 };
    char offy[4] = { 0, 0, 1, 1 };
    u8 flag1[4] = { 0, 0, 1, 1 };
    char flag2[4] = { 1 | 2, 4 | 2, 8 | 1, 8 | 4 };
    int i, j;

    for (i = 0; i < MAX_NPCS; i++, npc++)
    {
        if (npc->cond == false)
            continue;

        //Get collision position and reset state
        int x = npc->x / 0x400 / 16;
        int y = npc->y / 0x400 / 16;
        char v4 = 2;
        npc->flag = 0;

        for (j = 0; j < 4; j++)
        {
            //Get the attribute of the tile to check
            u8 atrb = map->GetAtrb(map->data[(x + offx[j]) + (y + offy[j]) * map->width]);

            //Block collision
            if (atrb == 0x41 || atrb == 0x43 || atrb == 0x44)
            {
                if ((JudgeHitNpCharBlock(npc, x + offx[j], y + offy[j], flag2[j]) & 8) == 0)
                    v4 -= flag1[j];
            }
            else
            {
                v4 -= flag1[j];
            }
        }

        //Set airborne flag
        if (v4 < 1)
            npc->airborne = true;
    }
}

