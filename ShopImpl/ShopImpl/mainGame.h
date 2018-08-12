/* 숙제 1. 총알은 바깥으로 벗어 나지 않음! 입사각 반사각 잘해야됨!, 총알끼리 부딪히면 서로 튕겨 나감!*/


#pragma once
#include"gameNode.h"

#define PI 3.141592654

#define BULLETMAX 100

class Shop;
class Player;
class PopUp;

class mainGame :  public gameNode
{

private:
	image* m_bgImage;	//백그라운드
    image* m_bgImage2;  //쇼핑 백그라운드 이미지
	image* m_apple;		//사과 이미지
	RECT m_rc;			//사과움직일 렉트

    bool _isLookingShop;
    bool _isLookingEquipment;

    Shop* _shop;
    Player* _player;
    POINT _clickPos;
    bool _isClicked;

    PopUp* noMoney;
    float noMoneyCoolDown;

    PopUp* onceEquip;
    float onceEquipCoolDown;

public:
	mainGame();
	~mainGame();

	float getAngle(float x1, float y1, float x2, float y2);
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

    bool IsClicked() const;
    POINT ClickPos() const;
};

