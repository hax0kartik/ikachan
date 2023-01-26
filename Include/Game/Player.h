#pragma once
#include "types.h"

struct MyChar
{
	bool cond; // 0 
	bool dead; // 1
	u8 unit; // 2
	u8 equip; // 3
	int x; // 4
	int y; // 8
	int xm; // C
	int ym; // 10
	char ani_no; // 14
	u16 ani_wait; // 16
	s16 shock; // 18
	u16 no_event; // 1A
	u16 life; // 1C
    u16 unk_1E; // 1E
	u16 exp; // 20
    u16 unk_22; // 22
	char level; // 24
	u16 swim_wait; // 26
	s16 dash_wait; // 28
	u8 direct; // 2A
	bool airborne; // 2B
	u8 flag; // 2C
	char carry; //2D
};

#define MAX_LEVEL 7

void InitMyChar();
extern MyChar gMC;
