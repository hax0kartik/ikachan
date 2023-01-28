#pragma once
#include "types.h"

#define MAX_NPCS (100)

struct NpChar{
    bool cond;
    char type;
    char code_char;
    u16 code_event;
    s16 act_wait;
    char act_no;
    char ani_no;
    short ani_wait;
    u8 direct;
    u8 flag;
    bool airborne;
    int x;
    int y;
    int xm;
    int ym;
    int tgt_x;
    int tgt_y;
};

void InitNpChar(NpChar *chr);