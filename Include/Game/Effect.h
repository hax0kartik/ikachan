#pragma once
#include "types.h"

#define MAX_CARETS (120)
#define MAX_CARET_SPAWNERS (10)

#define NO_CARET (0xFFFFFF)

struct Caret
{
    bool cond;
    s8 type;
    int x;
    int y;
    int xm;
    int ym;
    char ani_no;
    u16 x16;
    int ani_wait;
};

struct CaretSpawner
{
    bool cond;
    u8 type;
    char ani_no;
    char num;
    int x;
    int y;
    int rand_moveright;
    int rand_moveleft;
    int rand_movedown;
    int rand_moveup;
    int rand_x;
    int rand_y;
};

struct Map; //prototype;
struct Frame; //prototype

int FindCaret(Caret *caret);
void ProcCaret(Caret *caret, Map *map, Frame *frame);
int FindCaretSpawner(CaretSpawner *caret_spawner);
void ProcCaretSpawner(CaretSpawner *caret_spawner, Caret *caret);
