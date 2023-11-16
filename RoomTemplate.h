#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "ItemManager.h"
#include "IGetDescription.h"


class RoomTemplate : public IGetDescription
{

public:
	RoomTemplate(std::ifstream& ifs)
	{
		// read in the stuff here
		char comma;
		ifs >> m_roomNumber;
		ifs >> comma;
		ifs >> northId;
		ifs >> comma;
		ifs >> southId;
		ifs >> comma;
		ifs >> eastId;
		ifs >> comma;
		ifs >> westId;
		// end of line will be skipped automagically by ifstream
		ifs.ignore();
		char desc[256];
		ifs.getline(desc, 256);
		m_description = desc;
		// are we done? :-)
	}

	RoomTemplate( int roomid )
	{
		cout << "Constructor for room template" << endl;
		westId = 0;
		eastId = 0;
		northId = 0;
		southId = 0;
		m_roomNumber = roomid;
	}

	virtual ~RoomTemplate( )
	{
		if ( m_roomNumber == 101 )
		{
			cout << "Destructor for FloorGrRoomTemplateate" << endl;
		}
	}

	string GetDescription( bool bGetLong ) override
	{
		// IGetDescription::GetDescription( bGetLong ); // can't do this, there is no implementation since it's "pure"

		string desc;
		stringstream buf( desc );
		visitedRoomCounter++;
		if ( visitedRoomCounter < 10 )
		{
			buf << m_longDescription << " Room Number: " << m_roomNumber << std::endl;
		}
		else
		{
			buf << m_description << " Room Number: " << m_roomNumber << std::endl;
		}
		return desc;
	}

	virtual bool ParseCommand( string szCommand )
	{
		return false;
	}

	int westId;
	int eastId;
	int northId;
	int southId;
	int visitedRoomCounter;

	friend class RoomManager;

	int m_roomNumber;
	std::string m_description;
	std::string m_longDescription; // shown the first few times you enter a room
};

class FloorGrateRoom : public RoomTemplate // room id = 101, this room has a floor grate in it
{
private:
	bool m_bOpenedGrate = false;
	int someOtherNumber = 0;

public:

	FloorGrateRoom( int roomid ) // this is automatically going to also call its base class. The order is: this constructor first, base constructor second
		: RoomTemplate( roomid )
	{
		cout << "Floor grate constructor" << endl;
	}

	~FloorGrateRoom( ) // this is going to ... ??? 
	{
		cout << "Destructor for FloorGrate" << endl;
	}

	string GetDescription( bool bGetLong ) override
	{
		string baseDescription = RoomTemplate::GetDescription( bGetLong );

		// RoomTemplate::PrintDescription( ); if you want to call the base
		string desc;
		stringstream buf( desc );

		visitedRoomCounter++;

		if ( !m_bOpenedGrate )
		{
			if ( visitedRoomCounter < 10 )
			{
				buf << "You are in a dank, dingy room with a stinky hole in the floor. A grate is coverting it. It looks like it could be budged with some kind of explosive." << endl;
			}
			else
			{
				buf << "You are smelly room with a solid-looking grate in the floor." << endl;
			}
		}
		else
		{
			if ( visitedRoomCounter < 10 )
			{
				buf << "You are in a dank, dingy room with a stinky hole in the floor. A melted, busted grate is sitting nearby. It's still smoking..." << endl;
			}
			else
			{
				buf << "You are smelly room with a blown up grate in the floor." << endl;
			}
		}
		return desc;
	}

	bool ParseCommand( string szCommand )
	{
		if ( szCommand == "throw dynamite" )
		{
			// if you even HAVE dynamite... (let's pretend)
			if ( m_bOpenedGrate )
			{
				cout << "Meh, you better save that dynamite for later..." << endl;
				return true;
			}

			m_bOpenedGrate = true;
			cout << "KABOOOOOM! You duck from the debris, nearly get blown to bits, but after the smoke clears, you can see you blew up the grate.";
			return true;
		}
	}

};

