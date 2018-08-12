#include "stdafx.h"
#include "Player.h"
#include "Inventory.h"
#include "Equipment.h"

Player::Player() :
    _inventory(nullptr),
    _equipment(nullptr)
{
}

Player::~Player()
{
}

void Player::Init()
{
    _inventory = new Inventory;
    _inventory->Rect(1400, 0, 1800, 700);
    _inventory->Position(0, 0, 400, 700);
    _inventory->SetGold(400);
    SetChild(_inventory);

    _equipment = new Equipment;
    _equipment->Rect(0, 700, 400, 1400);
    _equipment->Position(0, 0, 400, 700);
    SetChild(_equipment);
}

void Player::Update(const float deltaTime)
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

    float equipmentVelocityY = _equipment->VelocityY();
    if (equipmentVelocityY > 0.0f)
    {
        equipmentVelocityY -= 6.61f;
        if (equipmentVelocityY <= 0.0f)
        {
            equipmentVelocityY = 0.0f;
        }
    }
    else if (equipmentVelocityY < 0.0f)
    {
        equipmentVelocityY += 6.61f;
        if (equipmentVelocityY >= 0.0f)
        {
            equipmentVelocityY = 0.0f;
        }
    }

    _equipment->VelocityY(equipmentVelocityY);
}

void Player::ExecuteEvent(const Event event)
{
    switch (event)
    {
        case Event::kShoppingBegin:
        {
            _inventory->VelocityX(-Constant::kInventorySpeed);
        }
        break;
        case Event::kShoppingEnd:
        {
            _inventory->VelocityX(Constant::kInventorySpeed);
        }
        break;
        case Event::kEquipmentBegin:
        {
            _inventory->VelocityX(-Constant::kInventorySpeed);
            _equipment->VelocityY(-Constant::kEquipmentSpeed);
        }
        break;
        case Event::kEquipmentEnd:
        {
            _inventory->VelocityX(Constant::kInventorySpeed);
            _equipment->VelocityY(Constant::kEquipmentSpeed);
        }
        break;
    }
}

Inventory* Player::GetInventory()
{
    return _inventory;
}

Equipment* Player::GetEquipment()
{
    return _equipment;
}
