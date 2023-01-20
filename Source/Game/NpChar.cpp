#include "Game/NpChar.h"

void InitNpChar(NpChar *npc)
{
    for (int i = 0; i < 100; i++) {
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
        npc[i].cond = false;
    }
}

void ActNpChar(NpChar *npc)
{

}