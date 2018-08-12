#include "stdafx.h"
#include "Equipment.h"
#include "image.h"
#include "Item.h"
#include "mainGame.h"

Equipment::Equipment() :
    _alpha(0.0f),
    _alpha2(0.0f),
    _weapon(nullptr),
    _armor(nullptr),
    _attack(0),
    _defence(0),
    isSelected(false),
    selectedId(-1)
{
}

Equipment::~Equipment()
{
}

void Equipment::Init()
{
    image* equipmentBackgroundImage = new image;
    equipmentBackgroundImage->init("images/inventory.bmp", 400, 700);
    RegisterImage(equipmentBackgroundImage);

    image* equipmentImage = new image;
    equipmentImage->init("images/equipment.bmp", 400, 400);
    RegisterImage(equipmentImage);
}

void Equipment::Update(const float deltaTime)
{
    Move();

    if (_rect.top >= 700)
    {
        _alpha = 0.0f;
        _alpha2 = 0.0f;
    }
    else
    {
        _alpha += 8.5f;
        _alpha2 += 12.0f;
    }

    if (_alpha >= 192.0f)
    {
        _alpha = 192.0f;
    }

    if (_alpha2 >= 255.0f)
    {
        _alpha2 = 255.0f;
    }

    isSelected = false;
    selectedId = -1;

    _attack = 0;
    if (_weapon != nullptr)
    {
        RECT rect = _weapon->Rect();
        rect.left = _rect.left + 30;
        rect.right = rect.left + 100;
        rect.top = _rect.top + 150;
        rect.bottom = rect.top + 100;
        _weapon->Rect(rect);

        if (PtInRect(&_weapon->Rect(), ptMouse))
        {
            if (_mainGame->IsClicked())
            {
                isSelected = true;
                selectedId = _weapon->Id();
            }
        }

        _attack += _weapon->attack;
    }

    _defence = 0;
    if (_armor != nullptr)
    {
        RECT rect = _armor->Rect();
        rect.left = _rect.left + 260;
        rect.right = rect.left + 100;
        rect.top = _rect.top + 150;
        rect.bottom = rect.top + 100;
        _armor->Rect(rect);

        if (PtInRect(&_armor->Rect(), ptMouse))
        {
            if (_mainGame->IsClicked())
            {
                isSelected = true;
                selectedId = _armor->Id();
            }
        }

        _defence += _armor->defence;
    }
}

void Equipment::Render(const HDC hdc)
{
    for (auto& image : _images)
    {
        image->render(hdc, _rect.left, _rect.top, static_cast<BYTE>(_alpha));
    }

    if (_weapon != nullptr)
    {
        _weapon->Render(hdc, 0, _alpha2);
    }

    if (_armor != nullptr)
    {
        _armor->Render(hdc, 0, _alpha2);
    }

    HFONT myFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Diehl Deco");
    HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
    SetTextColor(hdc, RGB(255, 255, 255));
    SetBkMode(hdc, TRANSPARENT);

    string attackText = "ATTACK";
    TextOut(hdc, _rect.left + 100, _rect.bottom - 200, attackText.c_str(), attackText.size());
    attackText = to_string(_attack);
    TextOut(hdc, _rect.left + 250, _rect.bottom - 200, attackText.c_str(), attackText.size());

    string defenceText = "DEFENCE";
    TextOut(hdc, _rect.left + 100, _rect.bottom - 170, defenceText.c_str(), defenceText.size());
    defenceText = to_string(_defence);
    TextOut(hdc, _rect.left + 250, _rect.bottom - 170, defenceText.c_str(), defenceText.size());

    SelectObject(hdc, oldFont);
    DeleteObject(myFont);
}

void Equipment::SetWeapon(Item* item)
{
    _weapon = item;
}

Item* Equipment::GetWeapon()
{
    return _weapon;
}

void Equipment::SetArmor(Item* item)
{
    _armor = item;
}

Item* Equipment::GetArmor()
{
    return _armor;
}

bool Equipment::IsSelected()
{
    return isSelected;
}

int Equipment::SelectedId()
{
    return selectedId;
}

Item* Equipment::SelectedItem()
{
    if (_weapon != nullptr)
    {
        if (_weapon->Id() == selectedId)
        {
            return _weapon;
        }
    }

    if (_armor != nullptr)
    {
        if (_armor->Id() == selectedId)
        {
            return _armor;
        }
    }

    return nullptr;
}
