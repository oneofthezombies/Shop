#pragma once
#include "GameObject.h"

struct Item : public GameObject
{
    Item();
    virtual ~Item();

    string name;
    int attack;
    int defence;
    string description;
    ItemKind kind;
    int price;
};
