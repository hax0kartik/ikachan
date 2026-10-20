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
STUB(RawTexture_SetPixel)
STUB(RawTexture_Flush)
STUB(_Z10BeginFrameP6System)
STUB(_Z16MakeSurface_FilePKci)
STUB(_Z8EndFrameP6System)
STUB(_Z19ProcessSystemEventsv)
STUB(SetClearColor)
STUB(SetRenderTarget)
STUB(FinishFrame)
STUB(PiyoPiyoControl)
STUB(GetTrg)
STUB(ProcFade)
STUB(_Z9PutMsgBoxP8EventScr)
STUB(_ZN2nn3hid3CTR13GetTouchPanelEv)
STUB(_ZN2nn3hid3CTR6GetPadEv)
STUB(_ZN2nn3hid3CTR9PadReaderC1ERNS1_3PadE)
STUB(EventScriptProc)
#undef STUB

// Data placeholders for objects that aren't decompiled yet (sized like the original)
char __attribute__((section("i.gMinimapTexture"))) gMinimapTexture[0xF0]; // RawTexture
char __attribute__((section("i.gFade"))) gFade[8]; // Fade
char __attribute__((section("i.gGame"))) gGameHead[2]; // two bytes before gGameMode
unsigned char __attribute__((section("i.gGame"))) gGameMode; // GAMEMODE
char __attribute__((section("i.gItems"))) gItems[8]; // Items
char __attribute__((section("i.gMap"))) gMap[276]; // Map
char __attribute__((section("i.gEventScr"))) gEventScr[40]; // EventScr
char __attribute__((section("i.gNpc"))) gNpc[4000]; // NpChar[100]
char __attribute__((section("i.gFrame"))) gFrame[12]; // Frame
char __attribute__((section("i.gPiyoCont"))) gPiyoCont[6]; // PiyoCont
char __attribute__((section("i.gCaretSpawner"))) gCaretSpawner[36]; // CaretSpawner[]
int __attribute__((section("i.gGame"))) gProfileNo; // profile slot, at +4 of the section (gGameHead, gGameMode, padding)
