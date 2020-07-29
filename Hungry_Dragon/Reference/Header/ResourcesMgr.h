#ifndef ResourcesMgr_h__
#define ResourcesMgr_h__

//-------------------------------------------------------
//매니저 헤더********************************************
//-------------------------------------------------------
//여기에 매니저 헤더 추가
#include "TimerMgr.h"		//파티클용 타이머 추가를 위함.

//-------------------------------------------------------
//기타 헤더**********************************************
//-------------------------------------------------------
//여기에 기타 헤더 추가
#include "Terrain.h"
#include "CubeDra.h"
#include "CubeCol.h"

#include "Texture.h"
#include "TerrainTex.h"
#include "CubeTex.h"

#include "AtkPart.h"		//임시. 파티클 종류별로 생성하면 추가하고 지울 것.
//-------------------------------------------------------




BEGIN(Engine)

class ENGINE_DLL CResourcesMgr : public CBase
{
	DECLARE_SINGLETON(CResourcesMgr)

private:
	explicit CResourcesMgr(void);
	virtual ~CResourcesMgr(void);

public:
	HRESULT	Reserve_ContainerSize(const _ushort& wSize);
	
	HRESULT	Ready_Buffer(LPDIRECT3DDEVICE9 pGraphicDev,
						const _ushort& wContainerIdx,
						const _tchar* pBufferTag,
						BUFFERID eID,
						const _ulong& dwCntX = 1,
						const _ulong& dwCntZ = 1,
						const _ulong& dwVtxItv = 1);

	HRESULT	Ready_Texture(LPDIRECT3DDEVICE9 pGraphicDev,
							const _ushort& wContainerIdx,
							const _tchar* pTextureTag,
							TEXTURETYPE eType, 
							const _tchar* pPath, 
							const _uint& iCnt = 1);

	//미리 벡터 공간 m_vecParticle에 모든 파티클 효과를 생성해 적재해 놓는 함수
	void	Load_Particle(LPDIRECT3DDEVICE9 pGraphicDev);

	//Particle 프리셋에서 클론한 파티클을 Layer에 삽입하는 함수
	CResources*	Get_Particle(LPDIRECT3DDEVICE9 pGraphicDev,
							PARTICLEID _ePartID,
							BoundingBox _boundingBox,
							_vec3 m_vOrigin);

	void	Render_Buffer(const _ushort& wContainerIdx,
							const _tchar* pBufferTag);

	
	
	CResources*		Clone(const _ushort& wContainerIdx, 
							const _tchar* pResourceTag);
	
	

private:
	CResources*		Find_Resources(const _ushort& wContainerIdx, const _tchar* pResourceTag);

private:
	map<const _tchar*, CResources*>*		m_pmapResource = nullptr;
	vector<CParticle*>						m_vecParticle;
	_ushort									m_sMaxContainer;

public:
	virtual void Free(void);
};

END
#endif // ResourcesMgr_h__
