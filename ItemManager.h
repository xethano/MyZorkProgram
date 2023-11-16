#pragma once

#include <iostream>
#include <list>

#include "ItemTemplate.h"
#include "CharacterTypeEnum.h"

class ItemManager
{

public:

	static ItemManager im; // there is only ONE of these...

	std::list<ItemTemplate*> ItemList;

	void AddItem( ItemTemplate* item)
	{
		ItemList.push_back(item);
	}

	void PrintItemsInRoom(int roomNumber)
	{
		std::cout << "Items in Room: ";
		for (ItemTemplate* it : ItemList)
		{
			if (it->roomID == roomNumber)
			{
				std::cout << it->GetDescription(false) << ", ";
			}
		}
		std::cout << "." << std::endl;
	}

	void PrintItemsInInventory()
	{
		std::cout << "Inventory:" << std::endl;
		for (ItemTemplate* it : ItemList)
		{
			if (it->roomID == (int) CharacterType::Me)
			{
				std::cout << it->GetDescription(false) << std::endl;
			}
		}
		std::cout << std::endl;
	}

	int GetItemIdFromString(std::string s)
	{
		for (ItemTemplate* it : ItemList)
		{
			if (_stricmp(s.c_str(), it->GetDescription( false ).c_str()) == 0)
			{
				return it->itemID;
			}
		}
		return -1; //not the roomNumber so its just dead
	}

	void PickUpItem(int playerRoomId, int itemId) // user typed "get blah" and we found the item # for blah and it's valid
	{
		for (ItemTemplate* it : ItemList)
		{
			if (it->roomID == playerRoomId && it->itemID == itemId)
			{
				it->roomID = (int)CharacterType::Me;
				std::cout << "Okay, you pick up the " << it->GetDescription( false ) << std::endl;
				return;
			}
		}
		std::cout << "I don't see that in this room." << std::endl;
	}

	void DropItem(int playerRoomId, int itemId)
	{
		// change item's room id from -1, to current room #
		for (ItemTemplate* it : ItemList)
		{
			if (it->roomID == (int)CharacterType::Me && it->itemID == itemId)
			{
				it->roomID = playerRoomId;
				std::cout << "You dropped " << it->GetDescription( false ) << std::endl;
				return;
			}
		}
		std::cout << "Item does not exist in inventory" << std::endl;
	}

	// add these methods in main program:
	// picking up an item would change that item's room id to -1
	// dropping an item that you're carrying, would change it's room # from -1 to the current room #.


};

