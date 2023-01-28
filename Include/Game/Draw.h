#include "Game/Rect.h"
#include "Game/System.h"

#define SURFACE_WIDTH  (400)
#define SURFACE_HEIGHT (240)

enum SURFACE_ID
{
    SURFACE_ID_BACK = 11,
    SURFACE_ID_STAR = 60,
    SURFACE_ID_PRTBACK = 70,
    SURFACE_ID_HARI = 80,
    SURFACE_ID_IRONHEAD = 100
};

extern RECT grcFull;
void PutBitmap3(const RECT *rcView, int x, int y, const RECT *rect, int surf_no, int a6);
