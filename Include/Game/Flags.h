#pragma once
#include "types.h"

#define FLAG_BYTES (32)
extern char gFlagNPC[FLAG_BYTES];

void InitFlags();
bool SetNPCFlag(u32 a);
bool CutNPCFlag(u32 a);
bool GetNPCFlag(u32 a);
