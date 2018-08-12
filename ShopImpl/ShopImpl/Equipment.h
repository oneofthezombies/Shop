#pragma once
#include "GameObject.h"

class Item;

class Equipment : public GameObject
{
public:
    Equipment();
    virtual ~Equipment();

    virtual void Init() override;
    virtual void Update(const float deltaTime) override;
    virtual void Render(const HDC hdc) override;

    void SetWeapon(Item* item);
    Item* GetWeapon();
    void SetArmor(Item* item);
    Item* GetArmor();

    bool IsSelected();
    int SelectedId();
    Item* SelectedItem();

private:
    float _alpha;
    float _alpha2;

    Item* _weapon;
    Item* _armor;
    int _attack;
    int _defence;

    bool isSelected;
    int selectedId;
};

