#include "Game/Controls.h"
#include <nn/os/os_Tick.h>
#include <nn/fnd/fnd_TimeSpan.h>

// I am not sure if these were the ones there but replicate the sti
static nn::os::Tick split(sTick)(-1);
static nn::fnd::TimeSpan split(sTimeSpan);

Controls split(gControls);

void InitializeControls(Controls *controls)
{
    controls->padReader = new nn::hid::CTR::PadReader();
    controls->touchReader = new nn::hid::CTR::TouchPanelReader();
}
