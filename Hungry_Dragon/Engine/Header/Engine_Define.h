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

#define TILECX 200
#define TILECZ 200
#define VERTEXSIZE 129
#define Pi 3.141592f
#define GRAVITY 3.5f
#define INVERSETILESIZE 0.005f

#endif // Engine_Define_h__
