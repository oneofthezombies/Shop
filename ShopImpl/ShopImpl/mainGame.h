/* ���� 1. �Ѿ��� �ٱ����� ���� ���� ����! �Ի簢 �ݻ簢 ���ؾߵ�!, �Ѿ˳��� �ε����� ���� ƨ�� ����!*/


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
	image* m_bgImage;	//��׶���
    image* m_bgImage2;  //���� ��׶��� �̹���
	image* m_apple;		//��� �̹���
	RECT m_rc;			//��������� ��Ʈ

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

