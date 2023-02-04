#include "Game/Flags.h"

char gFlagNPC[FLAG_BYTES];

void InitFlags()
{
	for (int i = 0; i < FLAG_BYTES; i++)
		gFlagNPC[i] = 0;
}

bool SetNPCFlag(int a)
{
	if (a > (FLAG_BYTES * 8))
		return false;
	gFlagNPC[a / 8] |= 1 << a % 8;
	return true;
}

bool CutNPCFlag(int a)
{
	if (a > (FLAG_BYTES * 8))
		return false;
	gFlagNPC[a / 8] &= ~(1 << a % 8);
	return true;
}

bool GetNPCFlag(int a)
{
	if (a > (FLAG_BYTES * 8))
		return false;
	if (gFlagNPC[a / 8] & (1 << (a % 8)))
		return true;
	else
		return false;
}
