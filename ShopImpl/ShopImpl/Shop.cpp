#include "stdafx.h"
#include "Shop.h"
#include "Inventory.h"
#include "image.h"
#include "Item.h"

Shop::Shop() :
    _inventory(nullptr)
{
}

Shop::~Shop()
{
}

void Shop::Init()
{
    _inventory = new Inventory;
    _inventory->Rect(-400, 0, 0, 700);
    _inventory->Position(0, 0, 400, 700);
    _inventory->SetGold(10000);

    image* item1Image = new image;
    item1Image->init("images/w_sword.bmp", 100, 100);
    image* item1Image2 = new image;
    item1Image2->init("images/itemBackground.bmp", 400, 100);
    Item* item1 = new Item;
    item1->RegisterImage(item1Image);
    item1->RegisterImage(item1Image2);
    item1->Position(0, 0, 400, 100);
    item1->kind = ItemKind::kWeapon;
    item1->name = string("SWORD");
    item1->attack = 10;
    item1->defence = 0;
    item1->description = string("IT'S SWORD.");
    item1->price = 100;
    item1->Id(0);
    _inventory->InsertItem(item1);

    image* item2Image = new image;
    item2Image->init("images/w_shield.bmp", 100, 100);
    image* item2Image2 = new image;
    item2Image2->init("images/itemBackground.bmp", 400, 100);
    Item* item2 = new Item;
    item2->RegisterImage(item2Image);
    item2->RegisterImage(item2Image2);
    item2->Position(0, 0, 400, 100);
    item2->kind = ItemKind::kArmor;
    item2->name = string("SHIELD");
    item2->attack = 0;
    item2->defence = 10;
    item2->description = string("IT'S SHIELD.");
    item2->price = 300;
    item2->Id(1);
    _inventory->InsertItem(item2);

    image* item3Image = new image;
    item3Image->init("images/w_potion.bmp", 100, 100);
    image* item3Image2 = new image;
    item3Image2->init("images/itemBackground.bmp", 400, 100);
    Item* item3 = new Item;
    item3->RegisterImage(item3Image);
    item3->RegisterImage(item3Image2);
    item3->Position(0, 0, 400, 100);
    item3->kind = ItemKind::kPotion;
    item3->name = string("POTION");
    item3->attack = 0;
    item3->defence = 0;
    item3->description = string("IT'S POTION.");
    item3->price = 100;
    item3->Id(2);
    _inventory->InsertItem(item3);

    image* item4Image = new image;
    item4Image->init("images/sword.bmp", 100, 100);
    image* item4Image2 = new image;
    item4Image2->init("images/itemBackground.bmp", 400, 100);
    Item* item4 = new Item;
    item4->RegisterImage(item4Image);
    item4->RegisterImage(item4Image2);
    item4->Position(0, 0, 400, 100);
    item4->kind = ItemKind::kWeapon;
    item4->name = string("SWORD2");
    item4->attack = 20;
    item4->defence = 0;
    item4->description = string("IT'S GOOD SWORD.");
    item4->price = 200;
    item4->Id(3);
    _inventory->InsertItem(item4);

    SetChild(_inventory);
}

void Shop::Update(const float deltaTime)
{
    float inventoryVelocityX = _inventory->VelocityX();
    if (inventoryVelocityX > 0.0f)
    {
        inventoryVelocityX -= 2.89f;
        if (inventoryVelocityX <= 0.0f)
        {
            inventoryVelocityX = 0.0f;
        }
    }
    else if (inventoryVelocityX < 0.0f)
    {
        inventoryVelocityX += 2.89f;
        if (inventoryVelocityX >= 0.0f)
        {
            inventoryVelocityX = 0.0f;
        }
    }

    _inventory->VelocityX(inventoryVelocityX);
}

void Shop::Render(const HDC hdc)
{
}

void Shop::ExecuteEvent(const Event event)
{
    switch (event)
    {
        case Event::kShoppingBegin:
        {
            _inventory->VelocityX(Constant::kInventorySpeed);
        }
        break;
        case Event::kShoppingEnd:
        {
            _inventory->VelocityX(-Constant::kInventorySpeed);
        }
        break;
    }
}

Inventory* Shop::GetInventory()
{
    return _inventory;
}
