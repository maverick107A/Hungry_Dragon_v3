#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum WINMODE { MODE_FULL, MODE_WIN };
	enum BUFFERID{ BUFFER_RCCOL, BUFFER_TERRAIN, BUFFER_FACE, BUFFER_TWINFACE, BUFFER_JAW, BUFFER_BODY, BUFFER_WING, BUFFER_LWING, BUFFER_TEXCUBE,BUFFER_TEXSQUARE,
		BUFFER_TERRAINTEX, BUFFER_LANDTEX, BUFFER_FOREST, BUFFER_KOREA, BUFFER_RIFT, BUFFER_VOLCANO, BUFFER_ICEAGE,
		BUFFER_SKYSPHERE, BUFFER_CAVECYLINDER, BUFFER_VENTCUBE, BUFFER_OBSTACLECUBE, SPRITE_ANIM, BUFFER_CUSTOMMESH,
		BUFFER_ROCKMESH, BUFFER_DIAMESH, BUFFER_TREEMESH, BUFFER_STUMPMESH, BUFFER_CHRYSTAL, BUFFER_DIAMOB_UPPER,BUFFER_DIAMOB_UNDER,
		BUFFER_RIGHTHAND , BUFFER_LEFTHAND, BUFFER_GOLEMBODY ,  BUFFER_END
	};

	enum ANIMATION { ANI_IDLE, ANI_EAT, ANI_FLY, ANI_BREATHIDLE, ANI_BREATHFLY, ANI_END };

	enum PARTICLEID { PART_ATK, PART_WIND, PART_FRAGILE, PART_LEAF, PART_END };	//파티클 클래스별 enum
	enum INFO { INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum ROTATION { ROT_Z, ROT_X, ROT_Y, ROT_END };

	// DYNAMIC의 경우 매 프레임마다 갱신이 필요한 컴포넌트
	enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END};
	enum TEXTURETYPE { TEX_NORMAL, TEX_CUBE, TEX_END };
	enum RENDERID { RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_STENCIL,RENDER_PARTICLE,RENDER_END };

	// 오브젝트풀용 구분 아이디
	enum OBJID { JUMP_MONSTER, STAND_MONSTER, RUN_MONSTER, CHASE_MONSTER, NORMAL_BULLET, HORIZON_MONSTER, OBJ_END };

	// 로딩씬 ID
	enum LOADINGID { LOADING_STAGE, LOADING_BOSS, LOADING_END };

	//Direct Input
	enum MOUSEKEYSTATE {DIM_LB,DIM_RB,DIR_MB,DIM_END};
	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	// 프래자일 파티클 방향 구분용
	enum PARTICLEDIR{ DIR_N, DIR_S, DIR_E, DIR_W, DIR_NE, DIR_SW, DIR_NW, DIR_SE, DIR_END};

}


#endif // Engine_Enum_h__
