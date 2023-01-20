#pragma once
#include "types.h"

struct NpChar{
    bool cond;
    u8 type;
    char code_char;
    u16 code_event;
    u16 act_wait;
    char act_no;
    char ani_no;
    short ani_wait;
    char direct;
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