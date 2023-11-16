// MyZorkProgram.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

#include "RoomTemplate.h"
#include "RoomManager.h"
#include "ItemManager.h"

ItemManager ItemManager::im; // this is a static data member of the ItemManager class. There is only ONE of these

vector<std::string> GetInputCommands()
{
    char command[256];
    cin.getline(command, 256);
    std::string s(command);
    vector<std::string> words;
    std::string delimiter = " ";

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        words.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    words.push_back(s);
    return words;
}

int main()
{
    RoomManager rm;
    RoomTemplate* pCurrentRoom;

    int fileNorth = 0;
    int fileSouth = 0;
    int fileEast = 0;
    int fileWest = 0;

    ifstream ifsRooms("RoomData.txt", ios::in);
    while (!ifsRooms.eof())
    {
        RoomTemplate* pNewRoom = new RoomTemplate(ifsRooms);
        rm.AddRoom(pNewRoom);
    }

    FloorGrateRoom* pGrateRoom = new FloorGrateRoom( 101 );
    pGrateRoom->m_roomNumber = 101;
    rm.AddRoom( pGrateRoom );

    ifstream ifsItems("ItemData.txt", ios::in);
    while (!ifsItems.eof())
    {
        ItemTemplate* pNewItem = new ItemTemplate(ifsItems);
        ItemManager::im.AddItem(pNewItem);
    }

    pCurrentRoom = rm.FindRoomByID(101);

    RoomTemplate* rtBase = pCurrentRoom;
    string desc = rtBase->GetDescription( true /*long desc*/  );
    cout << desc;

    ItemManager::im.PrintItemsInRoom( pCurrentRoom->m_roomNumber );

    std::string commandLine1;
    std::string commandLine2;

    cin >> commandLine1;
    cin >> commandLine2;
    
    if (commandLine1 == "get" || commandLine1 == "grab")
    {
                
                int itemId = ItemManager::im.GetItemIdFromString(commandLine2);
                if (itemId == -1)
                {
                    std::cout << "I don't know that item." << std::endl;
                }
                else
                {
                    ItemManager::im.PickUpItem(pCurrentRoom->m_roomNumber, itemId);
                }
    }
    if (commandLine1 == "drop")
    {
                
                int itemId = ItemManager::im.GetItemIdFromString(commandLine2);
                if (itemId == -1)
                {
                    std::cout << "I don't know that item." << std::endl;
                }
                else
                {
                    ItemManager::im.DropItem(pCurrentRoom->m_roomNumber, itemId);
                }
    }
    if (commandLine1 == "inven" || commandLine1 == "inventory" || commandLine1 == "i")
    {
               
                ItemManager::im.PrintItemsInInventory();
    }








    //while (true)
    //{
    //    // command look
    //    std::cout << std::endl;
    //    pCurrentRoom->PrintDescription();

    //    // get a command
    //    vector<std::string> cmds = GetInputCommands();

    //    std::string verb = cmds[0];
    //    bool parsed = false;
    //    if (verb == "q" || verb == "quit" || verb == "exit")
    //    {
    //        break;
    //    }

    //    if (verb == "n")
    //    {
    //    }
    //    if (verb == "get")
    //    {
    //        parsed = true;
    //        int itemId = ItemManager::im.GetItemIdFromString(cmds[1]);
    //        if (itemId == -1)
    //        {
    //            std::cout << "I don't know that item." << std::endl;
    //        }
    //        else
    //        {
    //            ItemManager::im.PickUpItem(pCurrentRoom->m_roomNumber, itemId);
    //        }
    //    }
    //    if (verb == "drop")
    //    {
    //        parsed = true;
    //        int itemId = ItemManager::im.GetItemIdFromString(cmds[1]);
    //        if (itemId == -1)
    //        {
    //            std::cout << "I don't know that item." << std::endl;
    //        }
    //        else
    //        {
    //            ItemManager::im.DropItem(pCurrentRoom->m_roomNumber, itemId);
    //        }
    //    }
    //    if (verb == "inven" || verb == "inventory" || verb == "i")
    //    {
    //        parsed = true;
    //        ItemManager::im.PrintItemsInInventory();
    //    }

    //    if (!parsed)
    //    {
    //        std::cout << "I don't know that verb." << std::endl;
    //    }
    //    // parse command
    //}


    // int NewRoomId = pCurrentRoom->westId;
    // RoomTemplate* pNewRoom = rm.FindRoomByID(NewRoomId);
    //pCurrentRoom = pNewRoom;
    // pCurrentRoom->PrintDescription();

}


// problem *: You're gonna need to load the room information off disk. Thus, each Room C++ object should have a method that takes a read stream reference
// as input, and reads in the room data.

// problem *: You should have one structure to hold all rooms, and a function to look up the rooms by ID. Call it "RoomManager"

// problem *: Rooms should "point to" without using a pointer, what room each direction leads to. That means by ID, not by *. And in order to get to that
// room by ID #, you should have one structure that holds all the RoomTemplates, and can look up one by ID. 
