#pragma once
#include "types.h"

enum FADE_MODE
{
    FADE_MODE_NONE,
    FADE_MODE_QUAKE,
    FADE_MODE_FADEOUT,
    FADE_MODE_FADEIN,
    FADE_MODE_QUAKE2,
};

struct Fade
{
    bool mask; // 0
    u8 mode; // 1
    //alignment 2, 3
    int wait; // 4
};

struct Frame;
struct CaretSpawner;

extern Fade gFade;

extern "C" int ProcFade(Fade *fade, Frame *frame, CaretSpawner *caret_spawner, int advance);
