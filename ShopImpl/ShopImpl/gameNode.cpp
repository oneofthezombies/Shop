#include "stdafx.h"
#include "gameNode.h"
#include "Events.h"
#include "keyManager.h"
#include "randomFunction.h"

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	//조사숙제
	SetTimer(_hWnd, TimerEvent::k1, FPS::k60, NULL);//타이머 초기화
	KEYMANAGER->init();
	
	setBackbuffer();
	return S_OK;
}

void gameNode::setBackbuffer()
{
	m_backbuffer = new image;
	m_backbuffer->init(WINSIZEX, WINSIZEY);
}

void gameNode::release()
{
	//조사숙제
	KillTimer(_hWnd, TimerEvent::k1);
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();
	RND->releaseSingleton();

	SAFE_DELETE(m_backbuffer);
}

void gameNode::update()
{
	//나중에 고성능 타이머를 만든후에는 사용 ㄴㄴ
	//더블버퍼 이후 사용하지 않음 (true->false)
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render(HDC hdc)
{
}

LRESULT gameNode::MainProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch ( iMessage )
	{
		case WM_TIMER:
			this->update();
			break;
		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			this->render(hdc);
			EndPaint(hwnd, &ps);
			break;
		case WM_MOUSEMOVE:
			ptMouse.x = LOWORD(lParam);
			ptMouse.y = HIWORD(lParam);
			break;
		case WM_KEYDOWN:
	        switch ( wParam )
            {
            case VK_ESCAPE:
            {
                PostQuitMessage(0);
            }
            break;
            }
            break;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return (DefWindowProc(hwnd, iMessage, wParam,lParam));
}
