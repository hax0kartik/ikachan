#include "Types.h"
#include <nn/os/os_KConfigMemory.h>

u32 s_memorySize;

extern "C" u32 _ZN2nn2os18GetUsingMemorySizeEv();
extern "C" void nninitStartUp() {
    const u32 appMemorySize = nn::os::GetAppMemorySize();
    s_memorySize = appMemorySize - _ZN2nn2os18GetUsingMemorySizeEv();
}
