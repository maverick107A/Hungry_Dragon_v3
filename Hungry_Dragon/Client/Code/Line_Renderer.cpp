#include "stdafx.h"
#include "Line_Renderer.h"

#include "Export_Function.h"
#include "Ingame_Flow.h"
#include "Bill_Line.h"

USING(Engine)

IMPLEMENT_SINGLETON(CLine_Renderer)

CLine_Renderer::CLine_Renderer()
	: CBase() {

}

CLine_Renderer::~CLine_Renderer(void) {
	for (auto& pLine : m_listLine)
	{
		Safe_Release(pLine);
	}
	for (auto& pLine : m_listSprite)
	{
		Safe_Release(pLine);
	}
	m_listLine.clear();
	m_listSprite.clear();
	Safe_Release(m_pTex);
}

HRESULT CLine_Renderer::Ready_Renderer(LPDIRECT3DDEVICE9 pGraphicDev) {
	m_pGraphicDev = pGraphicDev;
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	D3DXCreateTextureFromFile(m_pGraphicDev, L"../../Asset/Billboard/Dot/dot.png", &m_pTex);

	return S_OK;
}

int CLine_Renderer::Update_Renderer(const float& fTimeDelta) {

	for (auto& iter = m_listLine.begin(); iter != m_listLine.end();)
	{
		if ((*iter)->Update_Object(fTimeDelta) == OBJ_DEAD)
		{
			Safe_Release(*iter);
			iter = m_listLine.erase(iter);
		}
		else
		{
			++iter;
		}

	}
	for (auto& iter = m_listSprite.begin(); iter != m_listSprite.end();)
	{
		if ((*iter)->Update_Object(fTimeDelta) == OBJ_DEAD)
		{
			Safe_Release(*iter);
			iter = m_listSprite.erase(iter);
		}
		else
		{
			++iter;
		}

	}

	// 점점 사라지고 삭제
	//m_vPosOrigin.x += 1000.f * fTimeDelta;


	return 0;
}

void CLine_Renderer::Render_Renderer(void) {

	
	m_pGraphicDev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 0);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	m_pGraphicDev->SetTexture(0, m_pTex);
	for (auto& pLine : m_listLine)
	{
		pLine->Render_Object();
	}
	m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, true);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	m_pGraphicDev->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
}

void CLine_Renderer::Render_SpriteMode()
{
	for (auto& pLine : m_listSprite)
	{
		pLine->Render_Sprite(m_pTex);
	}

}

void CLine_Renderer::Draw_Dot(float _fX, float _fY, float _fZ, float _fSpeed , float _fScale, DWORD _dwColor)
{
	CBill_Line* pLine = CBill_Line::Create(m_pGraphicDev);
	pLine->Set_Pos(_vec3(_fX, _fY, _fZ));
	pLine->Set_Scale(_fScale);
	pLine->Set_Speed(_fSpeed);
	pLine->Set_Color(_dwColor);
	m_listLine.emplace_back(pLine);
}

void CLine_Renderer::Draw_DotSprite(LPD3DXSPRITE _pSprite, float _fX, float _fY, float _fSpeed, float _fScale, DWORD _dwColor)
{
	CBill_Line* pLine = CBill_Line::Create(m_pGraphicDev);
	pLine->Set_Sprite(_pSprite, _dwColor);
	pLine->Set_Pos(_vec3(_fX, _fY, 0.f));
	pLine->Set_Scale(_fScale);
	pLine->Set_Speed(_fSpeed);
	pLine->Set_Color(_dwColor);
	m_listSprite.emplace_back(pLine);
}

void CLine_Renderer::Draw_Line(_vec3 _vSrc, _vec3 _vDest, _uint _uLerp, float _fSpeed, float _fScale)
{
	CBill_Line* pLine = CBill_Line::Create(m_pGraphicDev);
	pLine->Set_Pos(_vSrc);
	pLine->Set_Scale(_fScale);
	pLine->Set_Speed(_fSpeed);
	m_listLine.emplace_back(pLine);

	_vec3 vLerp;
	float fLerp = 1.f / float(_uLerp);
	D3DXVec3Lerp(&vLerp, &_vSrc, &_vDest, fLerp);
	for (_uint i = 1; i < _uLerp; ++i)
	{
		pLine = CBill_Line::Create(m_pGraphicDev);
		pLine->Set_Pos(_vSrc + vLerp);
		pLine->Set_Scale(_fScale);
		pLine->Set_Speed(_fSpeed);
		m_listLine.emplace_back(pLine);
	}

	pLine = CBill_Line::Create(m_pGraphicDev);
	pLine->Set_Pos(_vDest);
	pLine->Set_Scale(_fScale);
	pLine->Set_Speed(_fSpeed);
	m_listLine.emplace_back(pLine);
}

void CLine_Renderer::Free(void) {
	
}


HRESULT CLine_Renderer::Add_Component(void) {
	Engine::CComponent*		pComponent = nullptr;

	// buffer

	return S_OK;
}


