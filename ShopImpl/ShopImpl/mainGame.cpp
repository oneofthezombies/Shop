#include "stdafx.h"
#include "mainGame.h"
#include "PopUp.h"
#include "Shop.h"
#include "GameObjectManager.h"
#include "Player.h"
#include "Time.h"
#include "keyManager.h"
#include "Item.h"
#include "Inventory.h"
#include "Equipment.h"

mainGame::mainGame() :
    _shop(nullptr),
    _player(nullptr),
    _isLookingShop(false),
    _isLookingEquipment(false),
    _clickPos(POINT()),
    _isClicked(false),
    noMoney(nullptr),
    noMoneyCoolDown(0.0f),
    onceEquip(nullptr),
    onceEquipCoolDown(0.0f)
{
}

mainGame::~mainGame()
{
}

float mainGame::getAngle(float x1, float y1, float x2, float y2)
{
	float x = x2 - x1;
	float y = y2 - y1;
	//두점 사이의 거리를 구하는 공식
	float distance = sqrtf(x*x + y*y);
	//두점 사이의 각도 구하는 공식
	float angle = acosf(x / distance);

	if (y2 > y1)
	{
		angle = -angle;

		if (angle >= 2.0f * PI)
		{
			angle -= 2.0f * PI;
		}
	}

	return angle;
}

HRESULT mainGame::init()
{
	gameNode::init();

	m_bgImage = new image;
	m_bgImage->init("images/image01.bmp", WINSIZEX, WINSIZEY);

    m_bgImage2 = new image;
    m_bgImage2->init("images/image02.bmp", WINSIZEX, WINSIZEY);

	m_apple = new image;
	m_apple->init("images/apple.bmp", 124, 162, true, RGB(255, 0, 255));

    image* noMoneyImage = new image;
    noMoneyImage->init("images/noMoney.bmp", 200, 100);
    noMoney = new PopUp;
    noMoney->RegisterImage(noMoneyImage);
    noMoney->Rect(1400, 0, 1600, 100);
    noMoney->Position(0, 0, 200, 100);
    noMoney->SetScene(this);

    image* onceEquipImage = new image;
    onceEquipImage->init("images/onceEquip.bmp", 200, 100);
    onceEquip = new PopUp;
    onceEquip->RegisterImage(onceEquipImage);
    onceEquip->Rect(1400, 0, 1600, 100);
    onceEquip->Position(0, 0, 200, 100);
    onceEquip->SetScene(this);

    _shop = new Shop;
    _shop->Rect(-400, 0, 400, 700);
    _shop->Position(-400, 0, 400, 700);
    _shop->Subscribe(Event::kShoppingBegin);
    _shop->Subscribe(Event::kShoppingEnd);
    _shop->SetScene(this);
    GameObjectManager::RegisterGameObject(_shop);

    _player = new Player;
    _player->Rect(1400, 0, 1800, 700);
    _player->Position(1400, 0, 1800, 700);
    _player->Subscribe(Event::kShoppingBegin);
    _player->Subscribe(Event::kShoppingEnd);
    _player->Subscribe(Event::kEquipmentBegin);
    _player->Subscribe(Event::kEquipmentEnd);
    _player->SetScene(this);
    GameObjectManager::RegisterGameObject(_player);

    GameObjectManager::Init();
    Time::Init();

	AddFontResourceA("./images/diehl-deco/DIEHLD__.ttf");

	return S_OK; // 함수가 성공적으로 돌아감을 의미함.
}

void mainGame::release()
{
    GameObjectManager::Release();

	gameNode::release();
	SAFE_DELETE(m_bgImage);

	RemoveFontResourceA("./images/diehl-deco/DIEHLD__.ttf");
}

void mainGame::update()
{
    Time::Update();

    if (KEYMANAGER->isOnceKeyDown(static_cast<int>(KeyEvent::kE)))
    {
        if (!_isLookingEquipment)
        {
            if (!_isLookingShop)
            {
                _isLookingShop = !_isLookingShop;
                _shop->ExecuteEvent(Event::kShoppingBegin);
                _player->ExecuteEvent(Event::kShoppingBegin);
            }
            else
            {
                _isLookingShop = !_isLookingShop;
                _shop->ExecuteEvent(Event::kShoppingEnd);
                _player->ExecuteEvent(Event::kShoppingEnd);
            }
        }
    }

    if (KEYMANAGER->isOnceKeyDown(static_cast<int>(KeyEvent::kQ)))
    {
        if (!_isLookingShop)
        {
            if (!_isLookingEquipment)
            {
                _isLookingEquipment = !_isLookingEquipment;
                _player->ExecuteEvent(Event::kEquipmentBegin);
            }
            else
            {
                _isLookingEquipment = !_isLookingEquipment;
                _player->ExecuteEvent(Event::kEquipmentEnd);
            }
        }
    }

    if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        _isClicked = true;
        _clickPos = ptMouse;
    }
    else
    {
        _isClicked = false;
    }

    if (_isLookingShop)
    {
        if (_shop->GetInventory()->IsSelected())
        {
            Item* selectedItem = _shop->GetInventory()->SelectedItem();

            // 산다
            if (_player->GetInventory()->GetGold() >= selectedItem->price)
            {
                _player->GetInventory()->ModifyGold(-selectedItem->price);
                _shop->GetInventory()->ModifyGold(selectedItem->price);

                _shop->GetInventory()->DeleteItem(selectedItem->Id());
                _player->GetInventory()->InsertItem(selectedItem);
            }

            // 못 산다
            else
            {
                // 돈 없어 팝업
                noMoneyCoolDown = 1.5f;
            }
        }

        if (_player->GetInventory()->IsSelected())
        {
            Item* selectedItem = _player->GetInventory()->SelectedItem();

            // 판다
            if (_shop->GetInventory()->GetGold() >= selectedItem->price)
            {
                _shop->GetInventory()->ModifyGold(-selectedItem->price);
                _player->GetInventory()->ModifyGold(selectedItem->price);

                _player->GetInventory()->DeleteItem(selectedItem->Id());
                _shop->GetInventory()->InsertItem(selectedItem);
            }

            // 못 판다
            else
            {
                // 돈 없어 팝업
                noMoneyCoolDown = 1.0f;
            }
        }
    }

    if (_isLookingEquipment)
    {
        if (_player->GetInventory()->IsSelected())
        {
            Item* selectedItem = _player->GetInventory()->SelectedItem();

            switch (selectedItem->kind)
            {
                case ItemKind::kWeapon:
                {
                    // 낀다
                    if (_player->GetEquipment()->GetWeapon() == nullptr)
                    {
                        _player->GetInventory()->DeleteItem(selectedItem->Id());
                        _player->GetEquipment()->SetWeapon(selectedItem);
                    }

                    // 못 낀다
                    else
                    {
                        // 못 낀다 팝업
                        onceEquipCoolDown = 1.0f;
                    }
                }
                break;
                case ItemKind::kArmor:
                {
                    // 낀다
                    if (_player->GetEquipment()->GetArmor() == nullptr)
                    {
                        _player->GetInventory()->DeleteItem(selectedItem->Id());
                        _player->GetEquipment()->SetArmor(selectedItem);
                    }

                    // 못 낀다
                    else
                    {
                        // 못 낀다 팝업
                        onceEquipCoolDown = 1.0f;
                    }
                }
                break;
            }
        }

        if (_player->GetEquipment()->IsSelected())
        {
            Item* selectedItem = _player->GetEquipment()->SelectedItem();

            if (selectedItem != nullptr)
            {
                switch (selectedItem->kind)
                {
                    case ItemKind::kWeapon:
                    {
                        _player->GetEquipment()->SetWeapon(nullptr);
                        _player->GetInventory()->InsertItem(selectedItem);
                    }
                    break;
                    case ItemKind::kArmor:
                    {
                        _player->GetEquipment()->SetArmor(nullptr);
                        _player->GetInventory()->InsertItem(selectedItem);
                    }
                    break;
                }
            }
        }
    }

    if (noMoneyCoolDown > 0.0f)
    {
        noMoneyCoolDown -= Time::DeltaTime();

        RECT rect;
        rect.left = 600;
        rect.top = 300;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 100;
        noMoney->Rect(rect);
    }
    else
    {
        noMoneyCoolDown = 0.0f;

        RECT rect;
        rect.left = 1400;
        rect.top = 0;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 100;
        noMoney->Rect(rect);
    }

    if (onceEquipCoolDown > 0.0f)
    {
        onceEquipCoolDown -= Time::DeltaTime();

        RECT rect;
        rect.left = 600;
        rect.top = 300;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 100;
        onceEquip->Rect(rect);
    }
    else
    {
        onceEquipCoolDown = 0.0f;

        RECT rect;
        rect.left = 1400;
        rect.top = 0;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 100;
        onceEquip->Rect(rect);
    }
    
    GameObjectManager::Update(Time::DeltaTime());

    gameNode::update();
}

void mainGame::render(HDC hdc)
{
	//gameNode::render(hdc);
	//백퍼버에 뿌려줌
	HDC memDC = this->getBackBuffer()->getMemDC();
	//흰색 빈 비트맵
	PatBlt(memDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//===================================================//

    if (!_isLookingShop)
    {
        m_bgImage->render(memDC);
    }
    else
    {
        m_bgImage2->render(memDC);
    }

    //m_apple->render(memDC, 200, 200);

    //HDC memDC2 = CreateCompatibleDC(m_apple->m_imageInfo->hMemDC);
    //HBITMAP hBit2 = (HBITMAP)CreateCompatibleBitmap(m_apple->m_imageInfo->hMemDC, 
    //                                                m_apple->m_imageInfo->width, m_apple->m_imageInfo->height);
    //HBITMAP oldBit2 = (HBITMAP)SelectObject(memDC2, hBit2);
    //BitBlt(memDC2, 
    //       0, 0, m_apple->m_imageInfo->width, m_apple->m_imageInfo->height, 
    //       memDC, 300, 200, 
    //       SRCCOPY);
    //GdiTransparentBlt(memDC2,
    //                  0, 0, m_apple->m_imageInfo->width, m_apple->m_imageInfo->height,
    //                  m_apple->m_imageInfo->hMemDC,
    //                  0, 0, m_apple->m_imageInfo->width, m_apple->m_imageInfo->height,
    //                  RGB(255, 0, 255));
    //BLENDFUNCTION bf;
    //bf.BlendOp = AC_SRC_OVER;
    //bf.BlendFlags = 0;
    //// alpha = 0(trans) ~ 255(opaque) 
    //bf.SourceConstantAlpha = 128;
    //bf.AlphaFormat = 0;
    //AlphaBlend(memDC,
    //           300, 200, m_apple->m_imageInfo->width, m_apple->m_imageInfo->height,
    //           memDC2,
    //           0, 0, m_apple->m_imageInfo->width, m_apple->m_imageInfo->height,
    //           bf);
    //SelectObject(memDC2, oldBit2);
    //DeleteObject(hBit2);
    //DeleteDC(memDC2);


        //HFONT font = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "MALGUN GOTHIC");
        //HFONT oldfont = (HFONT)SelectObject(memDC, font);
        //string text = to_string(ptMouse.x) + " " + to_string(ptMouse.y);
        //TextOut(memDC, 0, 0, text.c_str(), text.size());
        //SelectObject(memDC, oldfont);
        //DeleteObject(font);

    GameObjectManager::Render(memDC);

    if (noMoneyCoolDown > 0.0f)
    {
        noMoney->Render(memDC, 0, 128);

        HFONT myFont = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Diehl Deco");
        HFONT oldFont = (HFONT)SelectObject(memDC, myFont);
        SetTextColor(memDC, RGB(255, 255, 255));
        SetBkMode(memDC, TRANSPARENT);

        string text = "GOLD IS NOT ENOUGH";
        TextOut(memDC, 600, 335, text.c_str(), text.size());

        SelectObject(memDC, oldFont);
        DeleteObject(myFont);
    }

    if (onceEquipCoolDown > 0.0f)
    {
        onceEquip->Render(memDC, 0, 128);

        HFONT myFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Diehl Deco");
        HFONT oldFont = (HFONT)SelectObject(memDC, myFont);
        SetTextColor(memDC, RGB(255, 255, 255));
        SetBkMode(memDC, TRANSPARENT);

        string text = "YOU HAVE EQUIPPED ITEM";
        TextOut(memDC, 610, 337, text.c_str(), text.size());

        SelectObject(memDC, oldFont);
        DeleteObject(myFont);
    }

	//======================================================//
	//백버퍼에 내용을 HDC에 그린다
	this->getBackBuffer()->render(hdc, 0, 0);

}

bool mainGame::IsClicked() const
{
    return _isClicked;
}

POINT mainGame::ClickPos() const
{
    return _clickPos;
}
