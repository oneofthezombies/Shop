#pragma once
#include "image.h"
class gameNode
{
private:
	image * m_backbuffer; // ¹é¹öÆÛ
	void setBackbuffer();

public:
	gameNode();
	virtual~gameNode();

	virtual HRESULT init();
	virtual void  release();
	virtual void update();
	virtual void render(HDC hdc);

	image* getBackBuffer() { return m_backbuffer; };


	LRESULT MainProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

