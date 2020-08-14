#ifndef Define_h__
#define Define_h__

extern HWND			g_hWnd;
extern HINSTANCE	g_hInst;

enum RESOURCEID { RESOURCE_STATIC, RESOURCE_LOGO, RESOURCE_STAGE, RESOURCE_END };
namespace SCENENUM
{
	enum ID { SCENE_LOGO, SCENE_FOREST, SCENE_CAVE, SCENE_CLOUD, SCENE_VOLCANO, SCENE_ICELAND, SCENE_PROTO, SCENE_END };
}
#define TILECX 100
#define TILECZ 100
#define VERTEXSIZE 129
#define Pi 3.141592f
#define INVERSETILESIZE 0.01f


//#define DEBUG_WITHOUT_TREE 0		// 트리 리소스 디버깅
#define DEBUG_WITHOUT_TREE 1		// 이러면 나무 리소스 로딩 안하고 빠르게 씬 불러옴


#endif // Define_h__
