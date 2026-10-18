#pragma once
#include "types.h"
#include "Game/Rect.h"
#include <vector>

struct TitleBgItem
{
    int surf; // 0
    RECT rect; // 4
    int x; // 14
    int y; // 18
    u32 color; // 1C
};

struct TitleBgLayer
{
    float depth; // 0
    float parallaxX; // 4
    float parallaxY; // 8
    std::vector<TitleBgItem> items; // C
};
