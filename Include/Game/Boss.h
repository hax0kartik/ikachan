#pragma once
#include "types.h"
#include "Game/Rect.h"

struct Boss
{
    bool cond;
    s16 life;
    s16 shock;
    u8 x6;
    char code_char;
    s16 code_event;
    s16 defeat_event;
    s16 act_wait;
    char act_no;
    char ani_no;
    s16 ani_wait;
    u8 direct;
    u8 flag;
    bool airborne;
    int x;
    int y;
    int xm;
    int ym;
    int tgt_x;
    int tgt_y;
    RECT hit;
};

extern Boss gBoss;

void InitBoss();
