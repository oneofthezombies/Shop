#pragma once
#include "GameObject.h"

class Equipment;
class Inventory;

class Player : public GameObject
{
public:
    Player();
    virtual ~Player();

    virtual void Init() override;
    virtual void Update(const float deltaTime) override;
    virtual void ExecuteEvent(const Event event) override;

    Inventory* GetInventory();
    Equipment* GetEquipment();

private:
    Inventory* _inventory;
    Equipment* _equipment;
};

