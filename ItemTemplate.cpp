#include "ItemTemplate.h"

string ItemTemplate::GetDescription( bool bGetLong )
{
    if ( bGetLong )
    {
        return longItemDescription;
    }
    else
    {
        return ItemName;
    }
}
