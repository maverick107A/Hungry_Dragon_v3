#ifndef Ingame_Info_h__
#define Ingame_Info_h__

#include "Define.h"
#include "Engine_Define.h"
#include "Transform.h"
#include "Texture.h"

class CBarCon;
class CIconCon;
class CCompassCon;

USING(Engine)

class CIngame_Info
{
	DECLARE_SINGLETON(CIngame_Info)
public:
	enum STAGEID { STAGE_FOREST , STAGE_CAVE_ONE, STAGE_CAVE_TWO, STAGE_CAVE_FINAL, STAGE_SKY , STAGE_LAVA , STAGE_END };

private:
	explicit CIngame_Info(void);
	explicit CIngame_Info(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CIngame_Info(void);

public:			
	void Init_Info(LPDIRECT3DDEVICE9 pGraphicDev);
	void Initialize_LocalInfo() { m_fTimeTick = 0.f; m_bStageClear = false; m_tPlayerGoods.uGame_Point = 0; m_tPlayerStatus.fStage = 0.f; }
	void Update_Info(const Engine::_float& _fTimeDelta);
	void Render_UI();

	void Update_Frame();
	void Render_Frame();

public:
	void Push_EngineEvent(ENGINE_EVENT _tEvent);
	void Push_OnePolygon();
	void Push_EventFont(ENGINE_EVENT _tEvent);
	void Occur_EngineEvent(ENGINE_EVENT _tEvent);
	void Update_BuffPack(const Engine::_float& _fTimeDelta);
	void Update_FontPack(const Engine::_float& _fTimeDelta);
	void Update_PreyPack(const Engine::_float& _fTimeDelta);

public:
	void Draw_Tex(LPDIRECT3DTEXTURE9 _pTex, float _fCenterX, float _fCenterY, float _fScaleX, float _fCenterZ, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Draw_Tex(LPDIRECT3DTEXTURE9 _pTex, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Draw_Tex(LPDIRECT3DTEXTURE9 _pTex, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _RotX, float _RotY, float _RotZ, float _fPosX, float _fPosY, DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Draw_Tex(IDirect3DBaseTexture9* _pTex, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));
	void Draw_TexPart(IDirect3DBaseTexture9* _pTex, int _iPivotX, int _iPivotY, int _iRectX, int _iRectY, float _fScaleX, float _fScaleY, float _fPosX, float _fPosY, DWORD _dwColor = D3DCOLOR_ARGB(255, 255, 255, 255));


public:
	Engine::STATUS * Get_PlayerInfo() { return &m_tPlayerStatus; }
	Engine::GOODS * Get_PlayerGoods() { return &m_tPlayerGoods; }

private:
	// 출력할 글디바.
	LPDIRECT3DDEVICE9	m_pGraphicDev;
private:
	Engine::STATUS 		m_tPlayerStatus;
	Engine::GOODS 		m_tPlayerGoods;
	Engine::_bool		m_bStageClear = false;
	Engine::_bool		m_bChargeReadySp = true;

	IDirect3DTexture9*	m_pTexBar = nullptr;
	IDirect3DTexture9*	m_pIndicator = nullptr;
	IDirect3DTexture9*	m_pMainFrame = nullptr;
	IDirect3DTexture9*	m_pBtnFrame = nullptr;
	IDirect3DTexture9*	m_pBtnFrameFocus = nullptr;
	IDirect3DTexture9*	m_pBubble = nullptr;

	IDirect3DTexture9*	m_pBuffFrame[4];
	IDirect3DTexture9*	m_pBuffBar[4];
	IDirect3DTexture9*	m_pPolygon;
	IDirect3DTexture9*	m_pExpFrame;
	IDirect3DTexture9*	m_pExpFrameCharge;

	IDirect3DTexture9*	m_pPortraitFrame;
	IDirect3DTexture9*	m_pPortrait[11];



	CBarCon*			m_pBarCon = nullptr;
	CIconCon*			m_pIconCon = nullptr;
	CCompassCon*		m_pCompass = nullptr;
	LPD3DXSPRITE		m_pSprite = nullptr;

	_uint				m_uFocusDepth = 0;
	_uint				m_uMainFocus = 0;
	_uint				m_uSubFocus = 0;

	_float				m_fTimeTick = 0.f;
	_float				m_fAcquireAction = 0.f;
	_float				m_fBuffGage[4] = { 0 };

	
	// 자원 상호작용
	_vec3				m_vDestination[5];		// 고정된 5개 자원 회수위치


	typedef struct tagBuffPack
	{
		ENGINE_EVENT	tEvent;
		_vec3			vDest;	// 도착하면 데이터 갱신
		_vec3			vPos;
		_vec3			vScale;
		_vec3			vRot;
		DWORD			dwColor;
		_float			fLerpSpeed;
	} BUFFPACK;
	list<BUFFPACK> m_listBuffPack;


	// 폰트 상호작용 
	typedef struct tagFontPack
	{
		ENGINE_EVENT	tEvent;
		_vec3			vPos;
		_float			fLifeTime;
		D3DXCOLOR		tColor;
	} FONTPACK;
	list<FONTPACK> m_listFontPack;

	// 소화 정보
	typedef struct tagPreyInfo
	{
		_uint uType;
		_uint uPoly;
		_uint uPoint;
		_uint uStage;
		_uint uBuff;
		_float	fLifeTime;
	}PREYINFO;
	list<PREYINFO> m_listPreyInfo;
};


#endif // GameMgr_h__
