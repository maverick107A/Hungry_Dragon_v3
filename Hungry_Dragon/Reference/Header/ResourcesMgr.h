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
#include "ForestLand.h"
#include "TerrainTex.h"
#include "Texture_Cube.h"
#include "SkyCube.h"
#include "Texture_Plane.h"
#include "Texture_Square.h"

#include "Texture.h"

#include "Atk_Part.h"
//-------------------------------------------------------

//현재 파티클들은 미리 리소스매니저에 원형을 vector의 형태로 등재해 두고, Enum값인 PARTICLEID를 통해 해당 벡터에 접근해 그 파티클을 복사한 새로운 파티클을 리턴해 주는 형식을 채택하고 있다.


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

	//Particle 프리셋에서 클론한 파티클을 리턴하는 함수
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
