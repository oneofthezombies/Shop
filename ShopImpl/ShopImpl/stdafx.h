// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <memory>
#include <vector>
#include <map>
#include <string>
#include <chrono>
using namespace std;

#define WINNAME (LPTSTR)(TEXT("API"))
#define WINSTARTX 100
#define WINSTARTY 30
#define WINSIZEX 1400
#define WINSIZEY 700
#define WINSTYLE WS_CAPTION | WS_SYSMENU


#define SAFE_DELETE(p)				{if(p) {delete	 (p);   (p)=NULL;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[] (p);   (p)=NULL;}}
#define SAFE_RELEASE(p)				{if(p)  {(p)->release();(p)=NULL;}}


//////////////////extern//////////////
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT ptMouse;
// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#pragma comment(lib,"msimg32")