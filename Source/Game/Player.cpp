#include <stdlib.h>
#include "Game/Player.h"
#include "Game/Effect.h"
#include "Game/System.h"
#include "Game/Sound.h"
#include "Game/Draw.h"
#include "Game/Map.h"

MyChar split(gMC);
s16 split(gMycLife)[MAX_LEVEL + 1] = { 8, 12, 16, 20, 24, 28, 32 };

void InitMyChar()
{
    gMC.cond = true;
    gMC.equip = 0;
    gMC.dead = 0;
    gMC.level = 0;
    gMC.life = gMycLife[0];
    gMC.heal_wait = 0;
    gMC.exp = 0;
    gMC.exp_wait = 0;
    gMC.x = 0xA0000;
    gMC.y = 0x1A0000;
    gMC.ym = 0;
    gMC.xm = 0;
    gMC.airborne = 1;
    gMC.ani_wait = 0;
    gMC.ani_no = 0;
    gMC.direct = 0;
    gMC.flag = 0;
    gMC.unit = 0;
    gMC.shock = 0;
    gMC.no_event = 100;
    gMC.dash_wait = 0;
    gMC.swim_wait = 0;
    gMC.carry = 0;
}

void DamageMyChar(CaretSpawner *caret_spawner, char damage)
{
	//Check if we're invulnerable
	if (gMC.shock == 0)
	{
		//Take damage
		gMC.shock = 100;

		u16 newLife = gMC.life - 2 * damage;
		gMC.life = newLife;

		if (gMC.life < 0)
			gMC.life = 0;

		//Show us how much damage we took
		int damage_i = FindCaretSpawner(caret_spawner);
		if (damage_i != NO_CARET)
		{
			CaretSpawner *caretsp = &caret_spawner[damage_i];
			caretsp->cond = true;
			caretsp->type = 2;
			caretsp->ani_no = 10 - damage;
			caretsp->num = 1;
			caretsp->x = gMC.x + 0x2000;
			caretsp->y = gMC.y - 0x1000;
			caretsp->rand_x = 1;
			caretsp->rand_y = 0;
		}
		
		if (gMC.life != 0)
		{
			//Play hurt sound
			PlaySoundObject(2, 1);
		}
		else
		{
			//Die
			PlaySoundObject(9, 1);
			gMC.cond = false;
			gMC.dead = true;
			
			//Create death effect
			int dead_i = FindCaretSpawner(caret_spawner);
			if (dead_i != NO_CARET)
			{
				CaretSpawner *caretsp = &caret_spawner[dead_i];
				caretsp->cond = true;
				caretsp->type = 0;
				caretsp->ani_no = 0;
				caretsp->num = 30;
				caretsp->x = gMC.x + 0x2000;
				caretsp->y = gMC.y + 0x2000;
				caretsp->rand_moveright = 0xC00;
				caretsp->rand_moveleft = -0xC00;
				caretsp->rand_movedown = 0x200;
				caretsp->rand_moveup = -0xC00;
				caretsp->rand_x = 1;
				caretsp->rand_y = 0;
			}
		}
	}
}

int dashXm[3] = { -0xC00, 0xC00, 0 };
int dashYm[3] = { 0, 0, -0xC00 };

void ActMyCharDash(Caret *caret, CaretSpawner *caretSpawner)
{
    //Decrease dash timer and stop dashing when depleted
    if (--gMC.dash_wait <= 0)
        gMC.unit = 0;
    
    //Dash bubble
    if ((gMC.dash_wait % 4) == 0)
    {
        int caret_i = FindCaret(caret);
        if (caret_i != NO_CARET)
        {
            Caret *caretp = &caret[caret_i];
            caretp->type = 1;
            caretp->xm = Random(-0x200, 0x200) - (dashXm[gMC.direct] / 8);
            caretp->ym = Random(-0x200, 0x200) - (dashYm[gMC.direct] / 8);
            caretp->cond = true;
            caretp->ani_no = 0;
            caretp->ani_wait = 0;
            caretp->x = gMC.x + 0x2000;
            caretp->y = gMC.y + 0x2000;
        }
    }
    
    //Move and use dash animation
    gMC.x += gMC.xm;
    gMC.y += gMC.ym;
    gMC.ani_no = 3;

    //Decrement timers
    if (gMC.shock)
        --gMC.shock;
}

void ActMyCharShip(Caret *caret, CaretSpawner *caretSpawner)
{
    //Create effect
    int caretsp_i = FindCaretSpawner(caretSpawner);
    if (caretsp_i != NO_CARET)
    {
        CaretSpawner *caretsp = &caretSpawner[caretsp_i];
        caretsp->cond = true;
        caretsp->type = 0;
        caretsp->ani_no = 0;
        caretsp->num = 1;
        caretsp->x = gMC.x + 0x2000;
        caretsp->y = gMC.y + 0x6000;
        caretsp->rand_moveright = 0xC00;
        caretsp->rand_moveleft = -0xC00;
        caretsp->rand_movedown = 0xC00;
        caretsp->rand_moveup = 0;
        caretsp->rand_x = 1;
        caretsp->rand_y = 0;
    }
    
    //Fly up
    gMC.xm = 0;
    gMC.ym -= 16;
    gMC.y += gMC.ym;
    gMC.ani_no = 3;
    if (gMC.shock != 0)
        gMC.shock = 0;
}

char JudgeHitMyCharBlock(int x, int y, char flag)
{
	//Collide with block
	int dx = 0;
	int dy = 0;

	if ((flag & 1) && (flag & 2))
	{
		if ((gMC.x / 0x400) < (x * 16 + 15) && (gMC.y / 0x400) < (y * 16 + 12))
			dx = ((x * 16 + 15) << 10) - gMC.x;
		if ((gMC.y / 0x400) < (y * 16 + 15) && (gMC.x / 0x400) < (x * 16 + 12))
			dy = ((y * 16 + 16) << 10) - gMC.y;

		if (dx != 0 || dy != 0)
		{
			if ((dx != 0 && abs(dx) < abs(dy)) || dy == 0)
			{
				if (gMC.xm < -0x400)
					PlaySoundObject(SOUND_ID_HITHEAD, SOUND_MODE_PLAY);
				gMC.x = (x * 16 + 15) << 10;
				gMC.xm = 0;
				gMC.flag |= 1;
			}
			else
			{
				if (gMC.ym < -0x400)
					PlaySoundObject(SOUND_ID_HITHEAD, SOUND_MODE_PLAY);
				gMC.y = (y * 16 + 16) << 10;
				gMC.ym = 0;
				gMC.flag |= 2;
			}
		}
	}
	else if ((flag & 4) && (flag & 2))
	{
		if (((gMC.x + 0x3FF) / 0x400) > (x * 16 - 14) && (gMC.y / 0x400) < (y * 16 + 12))
			dx = ((x * 16 - 14) << 10) - gMC.x;
		if ((gMC.y / 0x400) < (y * 16 + 15) && (gMC.x / 0x400) > (x * 16 - 12))
			dy = ((y * 16 + 16) << 10) - gMC.y;

		if (dx != 0 || dy != 0)
		{
			if ((dx != 0 && abs(dx) < abs(dy)) || dy == 0)
			{
				if (gMC.xm > 0x400)
					PlaySoundObject(SOUND_ID_HITHEAD, SOUND_MODE_PLAY);
				gMC.x = (x * 16 - 14) << 10;
				gMC.xm = 0;
				gMC.flag |= 4;
			}
			else
			{
				if (gMC.ym < -0x400)
					PlaySoundObject(SOUND_ID_HITHEAD, SOUND_MODE_PLAY);
				gMC.y = (y * 16 + 16) << 10;
				gMC.ym = 0;
				gMC.flag |= 2;
			}
		}
	}
	else if ((flag & 1) && (flag & 8))
	{
		if ((gMC.x / 0x400) < (x * 16 + 15) && (gMC.y / 0x400) > (y * 16 - 12))
			dx = ((x * 16 + 15) << 10) - gMC.x;
		if ((gMC.y / 0x400) >= (y * 16 - 16) && (gMC.x / 0x400) < (x * 16 + 12))
			dy = ((y * 16 - 16) << 10) - gMC.y;

		if (dx != 0 || dy != 0)
		{
			if ((dx != 0 && abs(dx) < abs(dy)) || dy == 0)
			{
				if (gMC.xm < -0x400)
					PlaySoundObject(SOUND_ID_HITHEAD, SOUND_MODE_PLAY);
				gMC.x = (x * 16 + 15) << 10;
				gMC.xm = 0;
				gMC.flag |= 1;
			}
			else
			{
				gMC.airborne = false;
				gMC.y = (y * 16 - 16) << 10;
				if (gMC.ym > 0)
					gMC.ym = 0;
				gMC.flag |= 8;
			}
		}
	}
	else if ((flag & 4) && (flag & 8))
	{
		if (((gMC.x + 0x3FF) / 0x400) > (x * 16 - 14) && (gMC.y / 0x400) > (y * 16 - 12))
			dx = ((x * 16 - 14) << 10) - gMC.x;
		if ((gMC.y / 0x400) >= (y * 16 - 16) && (gMC.x / 0x400) > (x * 16 - 12))
			dy = ((y * 16 - 16) << 10) - gMC.y;

		if (dx != 0 || dy != 0)
		{
			if ((dx != 0 && abs(dx) < abs(dy)) || dy == 0)
			{
				if (gMC.xm > 0x400)
					PlaySoundObject(SOUND_ID_HITHEAD, SOUND_MODE_PLAY);
				gMC.x = (x * 16 - 14) << 10;
				gMC.xm = 0;
				gMC.flag |= 4;
			}
			else
			{
				gMC.airborne = false;
				gMC.y = (y * 16 - 16) << 10;
				if (gMC.ym > 0)
					gMC.ym = 0;
				gMC.flag |= 8;
			}
		}
	}

	return gMC.flag;
}

struct RawTexture;
extern RawTexture gFogTexture;
extern "C" void FogTexture_SetPixel(RawTexture *tex, u32 x, int y, u32 color);
extern "C" void FogTexture_Flush(RawTexture *tex);

void JudgeHitMyCharItem(int x, int y, CaretSpawner *caretSpawner, Map *map)
{
    if ((gMC.x / 0x400) < (x * 16 + 8) &&
        (gMC.x / 0x400) > (x * 16 - 8) &&
        (gMC.y / 0x400) < (y * 16 + 8) &&
        (gMC.y / 0x400) > (y * 16 - 8))
    {
        //Remove item and reveal it on the fog map
        map->data[x + y * map->width] = 0;
        FogTexture_SetPixel(&gFogTexture, x, y, 0);
        FogTexture_Flush(&gFogTexture);

        //Play item sound, add exp and life
        PlaySoundObject(SOUND_ID_ITEM, SOUND_MODE_PLAY);
        if (gMC.life < gMycLife[gMC.level])
        {
            gMC.life++;
            gMC.heal_wait = 12;
        }
        gMC.exp++;
        gMC.exp_wait = 20;
        if (gMC.life > gMycLife[gMC.level])
            gMC.life = gMycLife[gMC.level];

        //Create '+1' experience indicator
        int exp_i = FindCaretSpawner(caretSpawner);
        if (exp_i != NO_CARET)
        {
            CaretSpawner *caretsp = &caretSpawner[exp_i];
            caretsp->cond = true;
            caretsp->type = 2;
            caretsp->ani_no = 11;
            caretsp->num = 1;
            caretsp->x = gMC.x + 0x2000;
            caretsp->y = gMC.y - 0x1000;
            caretsp->rand_x = 1;
            caretsp->rand_y = 0;
        }

        //Create stars
        int star_i = FindCaretSpawner(caretSpawner);
        if (star_i != NO_CARET)
        {
            CaretSpawner *caretsp = &caretSpawner[star_i];
            caretsp->cond = true;
            caretsp->type = 0;
            caretsp->ani_no = 0;
            caretsp->num = 4;
            caretsp->x = gMC.x + 0x2000;
            caretsp->y = gMC.y + 0x2000;
            caretsp->rand_moveright = 0x800;
            caretsp->rand_moveleft = -0x800;
            caretsp->rand_movedown = 0;
            caretsp->rand_moveup = -0x800;
            caretsp->rand_x = 1;
            caretsp->rand_y = 0;
        }
    }
}

extern "C" void sub_127D94(u32*, float);
extern u32 stereocamera;

void PutMyChar(Frame *frame)
{
	static RECT split(rcMyChar)[12] = {
		{  0,  0, 16, 16 },
		{ 16,  0, 32, 16 },
		{ 32,  0, 48, 16 },
		{ 48,  0, 64, 16 },

		{  0, 16, 16, 32 },
		{ 16, 16, 32, 32 },
		{ 32, 16, 48, 32 },
		{ 48, 16, 64, 32 },

		{  0, 32, 16, 48 },
		{ 16, 32, 32, 48 },
		{ 32, 32, 48, 48 },
		{ 48, 32, 64, 48 },
	};

	static RECT split(rcMyCharShip)[12] = {
		{   0,  0,  40,  40 },
		{  40,  0,  80,  40 },
		{  80,  0, 120,  40 },
		{ 120,  0, 160,  40 },

		{   0, 40,  40,  80 },
		{  40, 40,  80,  80 },
		{  80, 40, 120,  80 },
		{ 120, 40, 160,  80 },

		{   0, 80,  40, 120 },
		{  40, 80,  80, 120 },
		{  80, 80, 120, 120 },
		{ 120, 80, 160, 120 },
	};

	sub_127D94(&stereocamera, 0.5f);

	char frame_no = (gMC.direct * 4) + gMC.ani_no;
	if (gMC.equip & 8)
		PutBitmap3(&grcFull, (gMC.x / 0x400) - (frame->x / 0x400) - 12, (gMC.y / 0x400) - (frame->y / 0x400) - 12, &rcMyCharShip[frame_no], SURFACE_ID_MYCHAR3, -1);
	else if (gMC.equip & 1)
		PutBitmap3(&grcFull, (gMC.x / 0x400) - (frame->x / 0x400), (gMC.y / 0x400) - (frame->y / 0x400), &rcMyChar[frame_no], SURFACE_ID_MYCHAR, -1);
	else
		PutBitmap3(&grcFull, (gMC.x / 0x400) - (frame->x / 0x400), (gMC.y / 0x400) - (frame->y / 0x400), &rcMyChar[frame_no], SURFACE_ID_MYCHAR2, -1);

	sub_127D94(&stereocamera, 0.0f);
}

typedef void (*MyCharAct)(Caret*, CaretSpawner*);
MyCharAct act[3] = {ActMyCharDash, ActMyCharShip};

void ActMyChar(Caret *caret, CaretSpawner *caretSpawner)
{
    act[gMC.unit](caret, caretSpawner);
}