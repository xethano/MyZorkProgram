#pragma once

// this defines a common method for anybody to get a description out of somebody who implements this 'interface' (class).
// There is no way to create this class directly. it's simply a collection of methods that do a certain thing. This is encapsulation and ADT's at its finest.
#include <string>
using namespace std;

class IGetDescription
{
public:
	virtual string GetDescription( bool bGetLong ) = 0;
};
