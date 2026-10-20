#pragma once
#include "types.h"

#define MAX_EPILOGUE_BUBBLES (100)

struct EpilogueBubble
{
    int x; // 0
    int y; // 4
    int type; // 8
    int alpha; // C
    int alphaBase; // 10
    int alphaRange; // 14
    bool fadeIn; // 18
    int waitMax; // 1C
    int wait; // 20
    float depth; // 24
};

void InitEpilogueBubbles();
void PutEpilogueBubbles();
int EpilogueScreen();
