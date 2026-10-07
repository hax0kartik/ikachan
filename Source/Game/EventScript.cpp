#include "Game/EventScript.h"

void InitEventScript(EventScr *ptx)
{
    ptx->mode = 0;
    ptx->msg_box = false;
    ptx->event_no = 0;
    ptx->ani_cursor = 0;
    ptx->wait = 0;
    ptx->x1C = 4;
    ptx->line = 0;
    ptx->ypos_line[0] = 0;
    ptx->ypos_line[1] = 20;
    ptx->p_write = 0;
    ptx->item_show = false;
    ptx->item_no = 0;
    ptx->item_ypos = 0;
}

short GetEventScriptNo(EventScr *ptx)
{
    short b = (ptx->data[ptx->p_read] - '0') * 1000;
    ptx->p_read++;
    b += (ptx->data[ptx->p_read] - '0') * 100;
    ptx->p_read++;
    b += (ptx->data[ptx->p_read] - '0') * 10;
    ptx->p_read++;
    b += ptx->data[ptx->p_read] - '0';
    ptx->p_read++;
    return b;
}
