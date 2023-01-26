#pragma once
#include "types.h"
#include "Game/Rect.h"

struct Boss
{
    bool cond;
    u16 life;
    u16 shock;
    u8 x6;
    char code_char;
    u16 code_event;
    u16 defeat_event;
    u16 act_wait;
    char act_no;
    char ani_no;
    u16 ani_wait;
    char direct;
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
