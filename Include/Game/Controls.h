#pragma once
#include "types.h"
#include <nn/hid/CTR/hid_PadReader.h>
#include <nn/hid/CTR/hid_TouchPanelReader.h>

struct Controls
{
    nn::hid::CTR::PadReader *padReader; // 0
    nn::hid::CTR::PadStatus pad; // 4
    bool padReadOk; // 14
    nn::hid::CTR::TouchPanelReader *touchReader; // 18
    nn::hid::CTR::TouchPanelStatus touch; // 1C
    u8 touchState; // 24
    bool touchReadOk; // 25
    bool stickAsDpad; // 26

    Controls() : padReader(0), padReadOk(false), touchReader(0), touchState(0), touchReadOk(false), stickAsDpad(true)
    {
    }

    ~Controls()
    {
        if (padReader)
        {
            delete padReader;
            padReader = 0;
        }
        if (touchReader)
        {
            delete touchReader;
            touchReader = 0;
        }
    }
};

extern Controls gControls;

void InitializeControls(Controls *controls);
