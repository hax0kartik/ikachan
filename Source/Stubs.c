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
STUB(sub_127D94)
STUB(nnResultFailureHandler)
STUB(_Z15PlaySoundObjectii)
STUB(FogTexture_SetPixel)
STUB(FogTexture_Flush)
STUB(_Z10BeginFrameP6System)
STUB(_Z16MakeSurface_FilePKci)
STUB(_Z8EndFrameP6System)
STUB(_Z19ProcessSystemEventsv)
#undef STUB

// Data placeholders for objects that aren't decompiled yet (sized like the original)
char __attribute__((section("i.gFogTexture"))) gFogTexture[0xF0]; // RawTexture
