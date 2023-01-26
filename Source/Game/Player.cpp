#include "Game/Player.h"
#include "Game/Effect.h"
#include "Game/System.h"

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


int dashXm[3] = { -0xC00, 0xC00, 0 };
int dashYm[3] = { 0, 0, -0xC00 };

void ActMyCharDash(Caret *caret, CaretSpawner *caretSpawner)
{
    //Decrease dash timer and stop dashing when depleted
    if (--gMC.dash_wait <= 0)
        gMC.unit = 0;
    
    //Dash bubble
    if ((gMC.dash_wait % 4) == 0)
    {
        int caret_i = FindCaret(caret);
        if (caret_i != NO_CARET)
        {
            Caret *caretp = &caret[caret_i];
            caretp->type = 1;
            caretp->xm = Random(-0x200, 0x200) - (dashXm[gMC.direct] / 8);
            caretp->ym = Random(-0x200, 0x200) - (dashYm[gMC.direct] / 8);
            caretp->cond = true;
            caretp->ani_no = 0;
            caretp->ani_wait = 0;
            caretp->x = gMC.x + 0x2000;
            caretp->y = gMC.y + 0x2000;
        }
    }
    
    //Move and use dash animation
    gMC.x += gMC.xm;
    gMC.y += gMC.ym;
    gMC.ani_no = 3;

    //Decrement timers
    if (gMC.shock)
        --gMC.shock;
}

void ActMyCharShip(Caret *caret, CaretSpawner *caretSpawner)
{
    //Create effect
    int caretsp_i = FindCaretSpawner(caretSpawner);
    if (caretsp_i != NO_CARET)
    {
        CaretSpawner *caretsp = &caretSpawner[caretsp_i];
        caretsp->cond = true;
        caretsp->type = 0;
        caretsp->ani_no = 0;
        caretsp->num = 1;
        caretsp->x = gMC.x + 0x2000;
        caretsp->y = gMC.y + 0x6000;
        caretsp->rand_moveright = 0xC00;
        caretsp->rand_moveleft = -0xC00;
        caretsp->rand_movedown = 0xC00;
        caretsp->rand_moveup = 0;
        caretsp->rand_x = 1;
        caretsp->rand_y = 0;
    }
    
    //Fly up
    gMC.xm = 0;
    gMC.ym -= 16;
    gMC.y += gMC.ym;
    gMC.ani_no = 3;
    if (gMC.shock != 0)
        gMC.shock = 0;
}

typedef void (*MyCharAct)(Caret*, CaretSpawner*);
MyCharAct act[3] = {ActMyCharDash, ActMyCharShip};

void ActMyChar(Caret *caret, CaretSpawner *caretSpawner)
{
    act[gMC.unit](caret, caretSpawner);
}