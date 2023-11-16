#pragma once

#include <list>
#include "RoomTemplate.h"
#include "ItemTemplate.h"

using namespace std;

class RoomManager
{
public:

	list<RoomTemplate*> m_Rooms;

	void AddRoom(RoomTemplate* rt)
	{
		m_Rooms.push_back(rt);
	}

	RoomTemplate* FindRoomByID(int id)
	{
		for (RoomTemplate* rt : m_Rooms)
		{
			if (rt->m_roomNumber == id)
			{
				return rt;
			}
		}
		return nullptr;
	}

	friend ostream& operator << ( ostream& os, const RoomManager& rm )
	{
		for ( RoomTemplate* pRoom : rm.m_Rooms )
		{

		}
	}

};

