#include "Game/Texture.h"
#include <string.h>

void SwizzleTile8x8(void *dst, const void *src, int size, unsigned char *a4)
{
    int bpp;
    if (a4[0] != 0)
        bpp = (a4[0] == 1) ? 4 : 0;
    else
        bpp = 3;

    if (size == 1)
    {
        memcpy(dst, src, bpp);
        return;
    }

    int half = size >> 1;
    int half_sq = half * half;
    int quad_bytes = bpp * half_sq;
    int stride = bpp * half;

    // Morton order: TL, TR, BL, BR (tail call)
    // TL: dst + 2*quad_bytes, src
    SwizzleTile8x8((char *)dst + 2 * quad_bytes, src, half, a4);

    // TR: dst + 3*quad_bytes, src + stride
    SwizzleTile8x8((char *)dst + 3 * quad_bytes, (const char *)src + stride, half, a4);

    // BL: dst, src + 8*stride
    SwizzleTile8x8(dst, (const char *)src + 8 * stride, half, a4);

    // BR (tail call): dst + quad_bytes, src + 9*stride
    SwizzleTile8x8((char *)dst + quad_bytes, (const char *)src + 9 * stride, half, a4);
}

Texture::Texture()
:	width(0),
	height(0),
	field_C(0),
	texture(),
	uvScaleX(1.0),
	uvScaleY(1.0),
	loaded(false),
	queuedForDraw(false),
	filename(NULL),
	refCount(1),
	batch()
{
}

Texture::~Texture()
{
	Unload();
}

int Texture::Load(const char *filename) { return 0; }
int Texture::Unload() { return 0; }
