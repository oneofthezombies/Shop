#pragma once
#include "GameObject.h"

class Inventory;

class Shop : public GameObject
{
public:
    Shop();
    virtual ~Shop();

    virtual void Init() override;
    virtual void Update(const float deltaTime) override;
    virtual void Render(const HDC hdc) override;
    virtual void ExecuteEvent(const Event event) override;

    Inventory* GetInventory();

private:
    Inventory* _inventory;
};
