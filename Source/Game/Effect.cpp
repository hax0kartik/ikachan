#include "Game/Effect.h"
#include "Game/Draw.h"
#include "Game/Map.h"

//Find free caret slot
int FindCaret(Caret *caret)
{
    //Return index of first free caret or 0xFFFFFF
    for (int i = 0; i < MAX_CARETS; i++, caret++)
    {
        if (caret->cond == false)
            return i;
    }
    return NO_CARET;
}

//Caret process
RECT rcCaret[20] =
{
    {  0, 0,  8,  8 },
    {  8, 0, 16,  8 },
    { 16, 0, 24,  8 },
    { 24, 0, 32,  8 },
    { 32, 0, 40,  8 },
    { 40, 0, 48,  8 },
    { 48, 0, 56,  8 },
    { 56, 0, 64,  8 },
    { 64, 0, 72,  8 },
    { 72, 0, 80,  8 },
    {  0, 8,  8, 16 },
    {  8, 8, 16, 16 },
    { 16, 8, 24, 16 },
    { 24, 8, 32, 16 },
    { 32, 8, 40, 16 },
    { 40, 8, 48, 16 },
    { 48, 8, 56, 16 },
    { 56, 8, 64, 16 },
    { 64, 8, 72, 16 },
    { 72, 8, 80, 16 }
};

void ProcCaret00(Caret *caret, Map *map, Frame *frame)
{
    //Fall and move
    caret->ym += 32;
    caret->x += caret->xm;
    caret->y += caret->ym;

    //Delete if out of bounds
    if (caret->x > (map->width << 14) || caret->x < 0 || caret->y > (map->length << 14) || caret->y < 0)
        caret->cond = false;
    
    //Animate
    if (++caret->ani_wait > 8)
    {
        caret->ani_wait = 0;
        caret->ani_no++;
        if (caret->ani_no > 5)
            caret->cond = false;
    }

    //Draw
    if (caret->cond)
        PutBitmap3(&grcFull,
                   (caret->x - frame->x) / 0x400 - 4,
                   (caret->y - frame->y) / 0x400 - 4,
                   &rcCaret[caret->ani_no],
                   SURFACE_ID_STAR + caret->type, -1);
}


void ProcCaret01(Caret *caret, Map *map, Frame *frame)
{
    //Float upwards
    caret->ym -= 16;
    caret->x += caret->xm;
    caret->y += caret->ym;
    
    //Delete if out of bounds
    if (caret->x > (map->width << 14) || caret->x < 0 || caret->y > (map->length << 14) || caret->y < 0)
        caret->cond = false;
    
    //Animate
    if (++caret->ani_wait > 32)
    {
        caret->ani_wait = 0;
        if (++caret->ani_no > 5)
            caret->cond = false;
    }
    
    //Draw
    if (caret->cond)
        PutBitmap3(&grcFull,
                   (caret->x - frame->x) / 0x400 - 4,
                   (caret->y - frame->y) / 0x400 - 4,
                   &rcCaret[caret->ani_no],
                   SURFACE_ID_STAR + caret->type, -1);
}

void ProcCaret02(Caret *caret, Map *map, Frame *frame)
{
    //Move up
    caret->y -= 341;
    
    //Delete if out of bounds
    if (caret->x > (map->width << 14) || caret->x < 0 || caret->y > (map->length << 14) || caret->y < 0)
        caret->cond = false;
    
    //Delete after 72 frames
    if (++caret->ani_wait > 72)
        caret->cond = false;
    
    //Draw
    if (caret->cond)
        PutBitmap3(&grcFull,
                   (caret->x - frame->x) / 0x400 - 4,
                   (caret->y - frame->y) / 0x400 - 4,
                   &rcCaret[caret->ani_no],
                   SURFACE_ID_STAR + caret->type, -1);
}

void ProcCaret03(Caret *caret, Map *map, Frame *frame)
{
    RECT rcLevelUp[2] = {
        { 0,  0, 64, 16 },
        { 0, 16, 64, 32 },
    };
    
    //Move up
    caret->y -= 341;
    
    //Delete if out of bounds
    if (caret->x > (map->width << 14) || caret->x < 0 || caret->y > (map->length << 14) || caret->y < 0)
        caret->cond = false;
    
    //Animate
    caret->ani_wait++;
    if (caret->ani_wait > 3)
    {
        caret->ani_wait = 0;
        caret->ani_no++;
        if (caret->ani_no > 24)
            caret->cond = false;
    }
    
    //Draw
    if (caret->cond)
        PutBitmap3(&grcFull,
                   (caret->x - frame->x) / 0x400 - 32,
                   (caret->y - frame->y) / 0x400 - 4,
                   &rcLevelUp[caret->ani_no % 2],
                   SURFACE_ID_STAR + caret->type, -1);
}

typedef void (*CARETPROC)(Caret*, Map*, Frame*);
CARETPROC gpCaretProcTbl[] = {
    ProcCaret00,
    ProcCaret01,
    ProcCaret02,
    ProcCaret03,
};

void ProcCaret(Caret *caret, Map *map, Frame *frame)
{
    for (int i = 0; i < MAX_CARETS; i++, caret++)
        if (caret->cond)
            gpCaretProcTbl[caret->type](caret, map, frame);
}

int FindCaretSpawner(CaretSpawner *caretSpawner)
{
    //Return index of first free caret spawner or 0xFFFFFF
    for (int i = 0; i < MAX_CARETS; i++, caretSpawner++) //This should be MAX_Caret_SPAWNERS
    {
        if (caretSpawner->cond == false)
            return i;
    }
    return NO_CARET;
}
