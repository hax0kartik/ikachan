#pragma once
#include "types.h"

struct EventScr
{
	char mode; //x0
	//alignment x1
	//alignment x2
	//alignment x3
	u8* data; //x4
	bool msg_box; //x8
	//alignment x9
	//alignment xA
	//alignment xB
	u32 size; //xC
	int event_no; //x10
	u32 p_read; //x14
	u8 ani_cursor; //x18
	//alignment x19
	u8 wait; //x1A
	u16 x1C; //x1C
	char line; //x1E
	char ypos_line[2]; //x1F, x20
	char p_write; //x21
	bool select; //x22
};

