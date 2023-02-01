#define STUB(SYMBOL)                                       \
    extern __attribute__((section("stubs"))) void SYMBOL() \
    {                                                      \
        __nop();                                           \
        __nop();                                           \
        __nop();                                           \
    } // filled with nops so linker doesnt nop out bl calls to stub functions

STUB(nnMain)
STUB(nninitCallStaticInitializers)
STUB(nninitLocale)
STUB(nninitRegion)
STUB(nninitSetup)
STUB(nninitSystem)
STUB(_ZN2nn3srv6detail7Service16GetServiceHandleEPNS_6HandleEPKcij)
STUB(sub_127D94)
STUB(_ZN2nn2os18GetUsingMemorySizeEv)
STUB(_Z15PlaySoundObjectii)
#undef STUB
