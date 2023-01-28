#include "Game/Draw.h"
#include "png.h"

//Global cliprect
RECT grcFull = { 0, 0, SURFACE_WIDTH, SURFACE_HEIGHT };

void PutBitmap3(const RECT *rcView, int x, int y, const RECT *rect, int surf_no, int a6){
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_create_info_struct(png);
}