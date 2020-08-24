#ifndef Engine_Define_h__
#define Engine_Define_h__

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <functional>
#include <ctime>
#include <fstream>

#include "Engine_Macro.h"
#include "Engine_Function.h"
#include "Engine_Enum.h"
#include "Engine_Struct.h"
#include "Engine_Typedef.h"

#pragma warning(disable : 4251)

#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>


using namespace std;

const D3DXCOLOR BLACK(255, 255, 255, 255);
const D3DXCOLOR WHITE (255, 0, 0, 0);
const D3DXCOLOR TRANSCOLOR (0, 255, 255, 255);
const D3DXCOLOR RED (255, 255, 0, 0);
const D3DXCOLOR GREEN  (255, 0, 255, 0);
const D3DXCOLOR BLUE (255, 0, 0, 255);
const D3DXCOLOR YELLOW  (255,255,255,0);
const D3DXCOLOR CYAN  (255,0,255,255);
const D3DXCOLOR MAGENTA  (255,255,0,255);

#define TILECX 100
#define TILECZ 100
#define VERTEXSIZE 129
#define Pi 3.141592f
#define GRAVITY 5.f
#define INVERSETILESIZE 0.01f

// =========================== 키매니저 =================================
#define KM_DEFAULT	0x00000000
#define KM_LEFT		0x00000001
#define KM_RIGHT	0x00000002
#define KM_DOWN		0x00000004
#define KM_UP		0x00000008
#define KM_LBUTTON	0x00000010
#define KM_RBUTTON	0x00000020
#define KM_SPACE	0x00000040
#define KM_ENTER	0x00000080
#define KM_TAB		0x00000100

//#define KM_TAB		0x00000200
//#define KM_TAB		0x00000400
//#define KM_TAB		0x00000800
//#define KM_TAB		0x00001000
//#define KM_TAB		0x00002000
//#define KM_TAB		0x00004000
//#define KM_TAB		0x00008000
//#define KM_TAB		0x00010000
//#define KM_TAB		0x00020000
//#define KM_TAB		0x00040000
//#define KM_TAB		0x00080000

#define KM_F1		0x00100000
#define KM_F2		0x00200000
#define KM_F3		0x00400000
#define KM_F4		0x00800000
#define KM_F5		0x01000000
#define KM_F6		0x02000000
#define KM_F7		0x04000000
#define KM_F8		0x08000000
#define KM_F9		0x10000000
#define KM_F10		0x20000000
#define KM_F11		0x40000000
#define KM_F12		0x80000000
#define KM_ALLKEY	0xffffffff
//==========================================================

#endif // Engine_Define_h__
