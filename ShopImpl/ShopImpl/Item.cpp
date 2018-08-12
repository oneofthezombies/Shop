#include "stdafx.h"
#include "Item.h"

Item::Item() :
    name(string()),
    attack(0),
    defence(0),
    description(string()),
    kind(ItemKind::kIdleItemKind),
    price(0)
{
}

Item::~Item()
{
}

