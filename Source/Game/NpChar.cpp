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
	npc->act_no = (npc->y + 0x2000) > gMC.y;
	
	//Animate
	if (++npc->ani_wait > 8)
	{
		npc->ani_wait = 0;
		if (++npc->ani_no > 1)
			npc->ani_no = 0;
	}
	
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

typedef void (*NPCACT)(NpChar*);
NPCACT gpNpcActTbl[] = {
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

