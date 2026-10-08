#include "Game/LoadGeneric.h"
#include "Game/Draw.h"
#include "Game/System.h"

void LoadSurfaces()
{
    MakeSurface_File("bitmap/MyChar.bmp", SURFACE_ID_MYCHAR);
    MakeSurface_File("bitmap/MyChar2.bmp", SURFACE_ID_MYCHAR2);
    MakeSurface_File("bitmap/MyChar3.bmp", SURFACE_ID_MYCHAR3);
    MakeSurface_File("bitmap/ProfileBox.bmp", SURFACE_ID_PROFILEBOX);
    MakeSurface_File("bitmap/MsgBox.bmp", SURFACE_ID_MSGBOX);
    MakeSurface_File("bitmap/Status2.bmp", SURFACE_ID_STATUS2);
    MakeSurface_File("bitmap/NextSymbol.bmp", SURFACE_ID_NEXTSYMBOL);
    MakeSurface_File("bitmap/YesNo1.bmp", SURFACE_ID_YESNO1);
    MakeSurface_File("bitmap/QuitResume.bmp", SURFACE_ID_QUITRESUME);
    MakeSurface_File("bitmap/NintendoButtons.bmp", SURFACE_ID_NINTENDOBUTTONS);
    MakeSurface_File("bitmap/FogOfWar1.bmp", SURFACE_ID_FOGOFWAR1);
    MakeSurface_File("bitmap/FogOfWar2.bmp", SURFACE_ID_FOGOFWAR2);
    MakeSurface_File("bitmap/FogOfWar3.bmp", SURFACE_ID_FOGOFWAR3);
    MakeSurface_File("bitmap/Status2f.bmp", SURFACE_ID_STATUS2F);
    MakeSurface_File("bitmap/Numbers.bmp", SURFACE_ID_NUMBERS);
    MakeSurface_File("map/mptIkachan.bmp", SURFACE_ID_PRTBACK);
    MakeSurface_File("bitmap/Back.bmp", SURFACE_ID_BACK);
    MakeSurface_File("bitmap/Copyright.bmp", SURFACE_ID_COPYRIGHT);
    MakeSurface_File("bitmap/Hari.bmp", SURFACE_ID_HARI);
    MakeSurface_File("bitmap/Isogin.bmp", SURFACE_ID_ISOGIN);
    MakeSurface_File("bitmap/Kani.bmp", SURFACE_ID_KANI);
    MakeSurface_File("bitmap/Sleep.bmp", SURFACE_ID_SLEEP);
    MakeSurface_File("bitmap/Chibi.bmp", SURFACE_ID_CHIBI);
    MakeSurface_File("bitmap/Hoshi.bmp", SURFACE_ID_HOSHI);
    MakeSurface_File("bitmap/Dum.bmp", SURFACE_ID_DUM);
    MakeSurface_File("bitmap/Carry.bmp", SURFACE_ID_CARRY);
    MakeSurface_File("bitmap/Juel.bmp", SURFACE_ID_JUEL);
    MakeSurface_File("bitmap/Ufo.bmp", SURFACE_ID_UFO);
    MakeSurface_File("bitmap/Launcher.bmp", SURFACE_ID_LAUNCHER);
    MakeSurface_File("bitmap/Bounder.bmp", SURFACE_ID_BOUNDER);
    MakeSurface_File("bitmap/Stamper.bmp", SURFACE_ID_STAMPER);
    MakeSurface_File("bitmap/Ironhead.bmp", SURFACE_ID_IRONHEAD);
    MakeSurface_File("bitmap/Star.bmp", SURFACE_ID_STAR);
    MakeSurface_File("bitmap/Bubble.bmp", SURFACE_ID_BUBBLE);
    MakeSurface_File("bitmap/Damage.bmp", SURFACE_ID_DAMAGE);
    MakeSurface_File("bitmap/LevelUp.bmp", SURFACE_ID_LEVELUP);
    MakeSurface_File("bitmap/Fade.bmp", SURFACE_ID_FADE);
    MakeSurface_File("bitmap/Font.bmp", SURFACE_ID_FONT);
    MakeSurface_File("bitmap/Fontx2.bmp", SURFACE_ID_FONTX2);
    MakeSurface_File("bitmap/Item.bmp", SURFACE_ID_ITEM);
    MakeSurface_File("bitmap/ItemBox.bmp", SURFACE_ID_ITEMBOX);
    MakeSurface_File("bitmap/Cursor1.bmp", SURFACE_ID_CURSOR1);
    MakeSurface_File("bitmap/Cursor.bmp", SURFACE_ID_CURSOR);
    MakeSurface_File("bitmap/Title_s.bmp", SURFACE_ID_TITLE_S);
    MakeSurface_File("bitmap/Title_1.bmp", SURFACE_ID_TITLE_1);
    MakeSurface_File("bitmap/Title_2.bmp", SURFACE_ID_TITLE_2);
    MakeSurface_File("bitmap/logo.bmp", SURFACE_ID_LOGO);
    MakeSurface_File("bitmap/logo2.bmp", SURFACE_ID_LOGO2);
    MakeSurface_File("bitmap/logo_ika.bmp", SURFACE_ID_LOGOIKA);
    MakeSurface_File("bitmap/ikachanlogo.bmp", SURFACE_ID_IKACHANLOGO);
    MakeSurface_File("bitmap/credits/bg1.bmp", SURFACE_ID_CREDITS_BG1);
    MakeSurface_File("bitmap/credits/bg2.bmp", SURFACE_ID_CREDITS_BG2);
    MakeSurface_File("bitmap/credits/bg3.bmp", SURFACE_ID_CREDITS_BG3);
    MakeSurface_File("bitmap/credits/isogin.bmp", SURFACE_ID_CREDITS_ISOGIN);
    MakeSurface_File("bitmap/credits/fish.bmp", SURFACE_ID_CREDITS_FISH);
    MakeSurface_File("bitmap/credits/ironhead.bmp", SURFACE_ID_CREDITS_IRONHEAD);
    MakeSurface_File("bitmap/credits/bubbles.bmp", SURFACE_ID_CREDITS_BUBBLES);
    MakeSurface_File("bitmap/credits/ikachan.bmp", SURFACE_ID_CREDITS_IKACHAN);
    MakeSurface_File("bitmap/credits/textbg.bmp", SURFACE_ID_CREDITS_TEXTBG);
    MakeSurface_File("bitmap/credits/epilogue.bmp", SURFACE_ID_EPILOGUE);

    for (u32 i = 0; i < 2; ++i )
    {
        ProcessSystemEvents();
        BeginFrame(&gSystem);
        EndFrame(&gSystem);
    }

}