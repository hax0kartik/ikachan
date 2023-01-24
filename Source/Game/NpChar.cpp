#include "Game/NpChar.h"
#include "Game/Player.h"

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
