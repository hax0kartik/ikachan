#include "Game/Player.h"

MyChar gMC;
u16 gMycLife[MAX_LEVEL + 1] = { 8, 12, 16, 20, 24, 28, 32 };

void InitMyChar()
{
    gMC.cond = true;
    gMC.equip = 0;
    gMC.dead = 0;
    gMC.level = 0;
    gMC.life = gMycLife[0];
    gMC.unk_1E = 0;
    gMC.exp = 0;
    gMC.unk_22 = 0;
    gMC.x = 0xA0000;
    gMC.y = 0x1A0000;
    gMC.ym = 0;
    gMC.xm = 0;
    gMC.airborne = 1;
    gMC.ani_wait = 0;
    gMC.ani_no = 0;
    gMC.direct = 0;
    gMC.flag = 0;
    gMC.unit = 0;
    gMC.shock = 0;
    gMC.no_event = 100;
    gMC.dash_wait = 0;
    gMC.swim_wait = 0;
    gMC.carry = 0;
}
