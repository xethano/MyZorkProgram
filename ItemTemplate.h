#pragma once

#include <iostream>
#include <fstream>
#include "IGetDescription.h"

class ItemTemplate : public IGetDescription
{
	std::string longItemDescription;
	std::string ItemName;

public:
	int weight;
	int roomID;
	int itemID;
	bool isWeapon;
	double damageScalar;
	int durability;


	ItemTemplate(std::ifstream& itemFile)
	{
		char dummyload;
		itemFile >> itemID;
		itemFile >> dummyload;
		itemFile >> roomID;
		itemFile >> dummyload;
		itemFile >> weight;
		itemFile >> dummyload;
		itemFile >> durability;
		itemFile >> dummyload;
		itemFile >> damageScalar;
		itemFile >> dummyload;
		itemFile >> isWeapon;
		itemFile.ignore();
		char desc[256];
		itemFile.getline(desc, 256);
		ItemName = desc;
		itemFile.ignore();
		itemFile.getline(desc, 256);
		longItemDescription = desc;
	}

	// Inherited via IGetDescription
	virtual string GetDescription( bool bGetLong ) override;
};

