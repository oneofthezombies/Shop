#include "stdafx.h"
#include "Inventory.h"
#include "image.h"
#include "mainGame.h"
#include "PopUp.h"
#include "commonMacroFunction.h"
#include "Item.h"
#include "PopUpYesNo.h"

Inventory::Inventory() :
    _gold(0),
    _bagIcon(nullptr),
    _swordIcon(nullptr),
    _shieldIcon(nullptr),
    _potionIcon(nullptr),
    _isOnBagIcon(false),
    _isOnSwordIcon(false),
    _isOnShieldIcon(false),
    _isOnPotionIcon(false),
    _isClickedBagIcon(false),
    _isClickedSwordIcon(false),
    _isClickedShieldIcon(false),
    _isClickedPotionIcon(false),
    selectedId(0),
    isSelected(false),
    popUp(nullptr)
{
}

Inventory::~Inventory()
{
}

void Inventory::Init()
{
    image* inventoryBackgroundImage = new image;
    inventoryBackgroundImage->init("images/inventory.bmp", 400, 700);
    RegisterImage(inventoryBackgroundImage);

    _bagIcon = new GameObject;
    _bagIcon->Rect(-400, 0, -300, 100);
    _bagIcon->Position(0, 0, 100, 100);
    image* bagOnImage = new image;
    bagOnImage->init("images/w_bag.bmp", 100, 100);
    _bagIcon->RegisterImage(bagOnImage);
    image* bagOffImage = new image;
    bagOffImage->init("images/bag.bmp", 100, 100);
    _bagIcon->RegisterImage(bagOffImage);
    image* bagBackgroundImage = new image;
    bagBackgroundImage->init("images/iconBackground.bmp", 100, 100);
    _bagIcon->RegisterImage(bagBackgroundImage);

    _swordIcon = new GameObject;
    _swordIcon->Rect(-300, 0, -200, 100);
    _swordIcon->Position(100, 0, 100, 100);
    image* swordOnImage = new image;
    swordOnImage->init("images/w_sword.bmp", 100, 100);
    _swordIcon->RegisterImage(swordOnImage);
    image* swordOffImage = new image;
    swordOffImage->init("images/sword.bmp", 100, 100);
    _swordIcon->RegisterImage(swordOffImage);
    image* swordBackgroundImage = new image;
    swordBackgroundImage->init("images/iconBackground.bmp", 100, 100);
    _swordIcon->RegisterImage(swordBackgroundImage);

    _shieldIcon = new GameObject;
    _shieldIcon->Rect(-200, 0, -100, 100);
    _shieldIcon->Position(200, 0, 100, 100);
    image* shieldOnImage = new image;
    shieldOnImage->init("images/w_shield.bmp", 100, 100);
    _shieldIcon->RegisterImage(shieldOnImage);
    image* shieldOffImage = new image;
    shieldOffImage->init("images/shield.bmp", 100, 100);
    _shieldIcon->RegisterImage(shieldOffImage);
    image* shieldBackgroundImage = new image;
    shieldBackgroundImage->init("images/iconBackground.bmp", 100, 100);
    _shieldIcon->RegisterImage(shieldBackgroundImage);

    _potionIcon = new GameObject;
    _potionIcon->Rect(-100, 0, 0, 100);
    _potionIcon->Position(300, 0, 100, 100);
    image* potionOnImage = new image;
    potionOnImage->init("images/w_potion.bmp", 100, 100);
    _potionIcon->RegisterImage(potionOnImage);
    image* potionOffImage = new image;
    potionOffImage->init("images/potion.bmp", 100, 100);
    _potionIcon->RegisterImage(potionOffImage);
    image* potionBackgroundImage = new image;
    potionBackgroundImage->init("images/iconBackground.bmp", 100, 100);
    _potionIcon->RegisterImage(potionBackgroundImage);

    _goldIcon = new GameObject;
    _goldIcon->Rect(-400, 600, -300, 700);
    _goldIcon->Position(0, 600, 100, 100);
    image* goldImage = new image;
    goldImage->init("images/gold.bmp", 100, 100);
    _goldIcon->RegisterImage(goldImage);
}

void Inventory::Update(const float deltaTime)
{
    auto bagPos = _bagIcon->Position();
    LONG bagX = _rect.left + bagPos.left;
    LONG bagY = _rect.top + bagPos.top;
    _bagIcon->Rect(bagX, bagY, bagX + bagPos.right, bagY + bagPos.bottom);
    _bagIcon->Velocity(Velocity());

    auto swordPos = _swordIcon->Position();
    LONG swordX = _rect.left + swordPos.left;
    LONG swordY = _rect.top + swordPos.top;
    _swordIcon->Rect(swordX, swordY, swordX + swordPos.right, swordY + swordPos.bottom);
    _swordIcon->Velocity(Velocity());

    auto shieldPos = _shieldIcon->Position();
    LONG shieldX = _rect.left + shieldPos.left;
    LONG shieldY = _rect.top + shieldPos.top;
    _shieldIcon->Rect(shieldX, shieldY, shieldX + shieldPos.right, shieldY + shieldPos.bottom);
    _shieldIcon->Velocity(Velocity());

    auto potionPos = _potionIcon->Position();
    LONG potionX = _rect.left + potionPos.left;
    LONG potionY = _rect.top + potionPos.top;
    _potionIcon->Rect(potionX, potionY, potionX + potionPos.right, potionY + potionPos.bottom);
    _potionIcon->Velocity(Velocity());

    auto goldPos = _goldIcon->Position();
    LONG goldX = _rect.left + goldPos.left;
    LONG goldY = _rect.top + goldPos.top;
    _goldIcon->Rect(goldX, goldY, goldX + goldPos.right, goldY + goldPos.bottom);
    _goldIcon->Velocity(Velocity());

    Move();
    _bagIcon->Move();
    _swordIcon->Move();
    _shieldIcon->Move();
    _potionIcon->Move();
    _goldIcon->Move();

    if (PtInRect(&_bagIcon->Rect(), ptMouse))
    {
        _isOnBagIcon = true;

        if (_mainGame->IsClicked())
        {
            if (!_isClickedBagIcon)
            {
                _isClickedBagIcon = true;
                _isClickedSwordIcon = false;
                _isClickedShieldIcon = false;
                _isClickedPotionIcon = false;
            }
            else
            {
                _isClickedBagIcon = false;
            }
        }
    }
    else
    {
        _isOnBagIcon = false;
    }

    if (PtInRect(&_swordIcon->Rect(), ptMouse))
    {
        _isOnSwordIcon = true;

        if (_mainGame->IsClicked())
        {
            if (!_isClickedSwordIcon)
            {
                _isClickedSwordIcon = true;
                _isClickedBagIcon = false;
            }
            else
            {
                _isClickedSwordIcon = false;
            }
        }
    }
    else
    {
        _isOnSwordIcon = false;
    }

    if (PtInRect(&_shieldIcon->Rect(), ptMouse))
    {
        _isOnShieldIcon = true;

        if (_mainGame->IsClicked())
        {
            if (!_isClickedShieldIcon)
            {
                _isClickedShieldIcon = true;
                _isClickedBagIcon = false;
            }
            else
            {
                _isClickedShieldIcon = false;
            }
        }
    }
    else
    {
        _isOnShieldIcon = false;
    }

    if (PtInRect(&_potionIcon->Rect(), ptMouse))
    {
        _isOnPotionIcon = true;

        if (_mainGame->IsClicked())
        {
            if (!_isClickedPotionIcon)
            {
                _isClickedPotionIcon = true;
                _isClickedBagIcon = false;
            }
            else
            {
                _isClickedPotionIcon = false;
            }
        }
    }
    else
    {
        _isOnPotionIcon = false;
    }
}

void Inventory::Render(HDC hdc)
{
    for (auto& image : Images())
    {
        image->render(hdc, Rect().left, Rect().top, 192);
    }

    if (_isOnBagIcon)
    {
        _bagIcon->Render(hdc, 2, 128);
    }

    if (_isClickedBagIcon)
    {
        _bagIcon->Render(hdc, 0, 192);
    }
    else
    {
        _bagIcon->Render(hdc, 1, 128);
    }

    if (_isOnSwordIcon)
    {
        _swordIcon->Render(hdc, 2, 128);
    }

    if (_isClickedSwordIcon)
    {
        _swordIcon->Render(hdc, 0, 192);
    }
    else
    {
        _swordIcon->Render(hdc, 1, 128);
    }

    if (_isOnShieldIcon)
    {
        _shieldIcon->Render(hdc, 2, 128);
    }

    if (_isClickedShieldIcon)
    {
        _shieldIcon->Render(hdc, 0, 192);
    }
    else
    {
        _shieldIcon->Render(hdc, 1, 128);
    }

    if (_isOnPotionIcon)
    {
        _potionIcon->Render(hdc, 2, 128);
    }

    if (_isClickedPotionIcon)
    {
        _potionIcon->Render(hdc, 0, 192);
    }
    else
    {
        _potionIcon->Render(hdc, 1, 128);
    }

    HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Diehl Deco");
    HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkMode(hdc, TRANSPARENT);

    RECT rect;
    rect.left = _rect.left;
    rect.top = _rect.top + 100;
    rect.right = _rect.right;
    rect.bottom = _rect.top + 200;

    selectedId = -1;
    isSelected = false;
    for (auto& item : _items)
    {
        bool isShow = false;

        if (_isClickedBagIcon)
        {
            isShow = true;
        }
        else
        {
            if (_isClickedSwordIcon)
            {
                if (item->kind == ItemKind::kWeapon)
                {
                    isShow = true;
                }
            }

            if (_isClickedShieldIcon)
            {
                if (item->kind == ItemKind::kArmor)
                {
                    isShow = true;
                }
            }

            if (_isClickedPotionIcon)
            {
                if (item->kind == ItemKind::kPotion)
                {
                    isShow = true;
                }
            }
        }

        if (isShow)
        {
            item->Rect(rect);

            if (PtInRect(&item->Rect(), ptMouse))
            {
                item->Render(hdc, 1, 128);

                if (_mainGame->IsClicked())
                {
                    // popup yes no
                    selectedId = item->Id();
                    isSelected = true;
                }
            }

            item->Render(hdc, 0, 255);

            string nameText = item->name;
            int x = item->Rect().left + 120;
            int y = (item->Rect().bottom + item->Rect().top) / 2 - 15;
            TextOut(hdc, x, y, nameText.c_str(), nameText.size());

            string priceText = "PRICE   " + to_string(item->price);
            x = item->Rect().left + 250;
            TextOut(hdc, x, y, priceText.c_str(), priceText.size());

            if (PtInRect(&item->Rect(), ptMouse))
            {
                image* popUpbackground = new image;
                popUpbackground->init("images/popUpBackground.bmp", 250, 200);
                popUp = new PopUp;
                popUp->RegisterImage(popUpbackground);
                popUp->Rect(ptMouse.x, ptMouse.y, 250, 200);
                popUp->Id(item->Id());
            }

            rect.top += 100;
            rect.bottom += 100;
        }
    }

    _goldIcon->Render(hdc, 0, 128);

    string goldText = "GOLD          " + to_string(_gold);
    int x = _goldIcon->Rect().left + 150;
    int y = (_goldIcon->Rect().top + _goldIcon->Rect().bottom) / 2;
    TextOut(hdc, x, y, goldText.c_str(), goldText.size());

    if (popUp != nullptr)
    {
        popUp->Render(hdc, 0, 192);

        string text;
        for (auto& item : _items)
        {
            if (item->Id() == popUp->Id())
            {
                text = "NAME : " + item->name;
                TextOut(hdc, popUp->Rect().left + 10, popUp->Rect().top + 10, text.c_str(), text.size());
                text = "ATTACK : " + to_string(item->attack);
                TextOut(hdc, popUp->Rect().left + 10, popUp->Rect().top + 45, text.c_str(), text.size());
                text = "DEFENCE : " + to_string(item->defence);
                TextOut(hdc, popUp->Rect().left + 10, popUp->Rect().top + 75, text.c_str(), text.size());
                text = "DESCRIPTION : ";
                TextOut(hdc, popUp->Rect().left + 10, popUp->Rect().top + 105, text.c_str(), text.size());
                text = item->description;
                TextOut(hdc, popUp->Rect().left + 10, popUp->Rect().top + 135, text.c_str(), text.size());
                text = "PRICE : " + to_string(item->price);
                TextOut(hdc, popUp->Rect().left + 10, popUp->Rect().top + 165, text.c_str(), text.size());
            }
        }
    }

    SelectObject(hdc, oldFont);
    DeleteObject(myFont);

    SAFE_DELETE(popUp);
}

void Inventory::InsertItem(Item* item)
{
    _items.push_back(item);
}

Item* Inventory::SelectedItem()
{
    for (auto& item : _items)
    {
        if (item->Id() == selectedId)
        {
            return item;
        }
    }

    return nullptr;
}

void Inventory::DeleteItem(int id)
{
    for (auto it = _items.begin(); it != _items.end();)
    {
        if ((*it)->Id() == id)
        {
            it = _items.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Inventory::SetGold(const int gold)
{
    _gold = gold;
}

int Inventory::GetGold() const
{
    return _gold;
}

void Inventory::ModifyGold(const int gold)
{
    _gold += gold;
}

bool Inventory::IsSelected() const
{
    return isSelected;
}

int Inventory::SelectedId() const
{
    return selectedId;
}
