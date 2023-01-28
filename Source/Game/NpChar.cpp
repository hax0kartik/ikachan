#include "Game/Rect.h"
#include "Game/NpChar.h"
#include "Game/Player.h"
#include "Game/Map.h"
#include "Game/Draw.h"

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
                return;
		    }
		}
		if (++npc->ani_wait > 5)
		{
			npc->ani_wait = 0;
			if (--npc->ani_no < 0)
				npc->ani_no = 0;
		}
	}
}

void ActNpChar05(NpChar *npc)
{
    //Fall and move
    if (npc->ym < 0x800)
        npc->ym += 20;
    npc->y += npc->ym;
}

typedef void (*NPCACT)(NpChar*);
NPCACT gpNpcActTbl[] = {
    ActNpChar01,
    ActNpChar05,
    ActNpChar01,
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
s8 JudgeHitNpCharBlock(NpChar *npc, int x, int y, u8 flag)
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

