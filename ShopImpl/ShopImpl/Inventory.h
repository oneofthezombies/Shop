#pragma once
#include "GameObject.h"

class Item;
class PopUp;

class Inventory : public GameObject
{
public:
    Inventory();
    virtual ~Inventory();

    virtual void Init() override;
    virtual void Update(const float deltaTime) override;
    virtual void Render(HDC hdc) override;

    void InsertItem(Item* item);
    Item* SelectedItem();
    void DeleteItem(int id);

    void SetGold(const int gold);
    int GetGold() const;
    void ModifyGold(const int gold);

    bool IsSelected() const;
    int SelectedId() const;

private:
    vector<Item*> _items;
    int _gold;

    GameObject* _bagIcon;
    bool _isOnBagIcon;
    bool _isClickedBagIcon;
    GameObject* _swordIcon;
    bool _isOnSwordIcon;
    bool _isClickedSwordIcon;
    GameObject* _shieldIcon;
    bool _isOnShieldIcon;
    bool _isClickedShieldIcon;
    GameObject* _potionIcon;
    bool _isOnPotionIcon;
    bool _isClickedPotionIcon;
    GameObject* _goldIcon;
    bool isSelected;
    int selectedId;

    PopUp* popUp;
};
