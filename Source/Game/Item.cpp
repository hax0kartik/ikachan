#include "Game/EventScript.h"
#include "Game/Item.h"
#include "Game/Player.h"

char item_equip[12] = { 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x02, 0x00, 0x00, 0x08 };

bool CheckItem(Items *items, char code)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		//Check if this is the requested item
		if (items->code[i] == code)
			return true;
	}
	return false;
}

bool AddItemData(Items *items, char code)
{
	//Check if we already have this item
	if (CheckItem(items, code) == false)
	{
		for (int i = 0; i < MAX_ITEMS; i++)
		{
			//Check if this is a free item slot
			if (items->code[i] == 0)
			{
				//Fill item slot and equip
				items->code[i] = code;
				gMC.equip |= item_equip[code];
				return true;
			}
		}
	}
	return false;
}

bool SubItemData(Items *items, char code)
{
	//Check if we already have this item
	if (CheckItem(items, code) == true)
	{
		for (int i = 0; i < MAX_ITEMS; i++)
		{
			//Check if this is the requested item to remove
			if (items->code[i] == code)
			{
				//Remove item from inventory and dequip
				items->code[i] = 0;
				gMC.equip &= ~item_equip[code];
				return true;
			}
		}
	}
	return false;
}
