#include "Game/Boss.h"
#include "Game/Effect.h"
#include "Game/Sound.h"

Boss gBoss = { 0 };

void InitBoss()
{
    gBoss.cond = true;
    gBoss.life = 15;
    gBoss.shock = 0;
    gBoss.x6 = 0;
    gBoss.code_char = 0;
    gBoss.code_event = 1000;
    gBoss.defeat_event = 1001;
    gBoss.act_wait = 0;
    gBoss.act_no = 0;
    gBoss.ani_no = 0;
    gBoss.ani_wait = 0;
    gBoss.direct = 0;
    gBoss.x = 0x20C000;
    gBoss.y = 0x168000;
    gBoss.xm = 0;
    gBoss.ym = 0;
    gBoss.tgt_x = 0x218000;
    gBoss.tgt_y = 0x16C000;
    gBoss.hit.left = 0x4000;
    gBoss.hit.top = 0x800;
    gBoss.hit.right = 0xC000;
    gBoss.hit.bottom = 0x5800;
}

void DamageBoss(CaretSpawner *caretSpawner, char damage)
{
	if (gBoss.shock == 0)
	{
		//Damage Iron Head
		gBoss.shock = 100;
		gBoss.life -= damage;
		if (gBoss.life < 0)
			gBoss.life = 0;
		
		//Create damage indicator
		int dmg_i = FindCaretSpawner(caretSpawner);
		if (dmg_i != NO_CARET)
		{
			CaretSpawner *caretsp = &caretSpawner[dmg_i];
			caretsp->cond = true;
			caretsp->type = 2;
			caretsp->ani_no = 10 - damage;
			caretsp->num = 1;
			caretsp->x = gBoss.x + 0x2000;
			caretsp->y = gBoss.y - 0x1000;
			caretsp->rand_x = 1;
			caretsp->rand_y = 0;
		}

		PlaySoundObject(16, 1);
	}
}
