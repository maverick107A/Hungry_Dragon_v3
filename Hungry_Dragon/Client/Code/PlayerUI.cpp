#include "stdafx.h"
#include "PlayerUI.h"

#include "Export_Function.h"
#include "Terrain.h"
#include "BaseLand.h"

CPlayerUI::CPlayerUI(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CPlayerUI::~CPlayerUI(void)
{

}

HRESULT CPlayerUI::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

void CPlayerUI::Initialize_Object(void)
{

}

int CPlayerUI::Update_Object(const float& fTimeDelta)
{
	//여기서 정보받을거야 ㅋ
	Engine::CGameObject::Update_Object(fTimeDelta);

	return 0;
}

void CPlayerUI::Render_Object(void)
{
	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../Bin/Resource/Texture/Bar/Red.png",
		&m_pRedTex);
	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../Bin/Resource/Texture/Bar/Green.png",
		&m_pGreenTex);
	D3DXCreateTextureFromFile(
		m_pGraphicDev,
		L"../Bin/Resource/Texture/Bar/Yellow.png",
		&m_pYellowTex);

	//if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_pTexInfo->tImageInfo)))
	//{
	//	wstring wstrErrMessage = wstrFilePath + L"Load Failed";
	//	ERR_MSG(wstrErrMessage.c_str());
	//	return E_FAIL;
	//}
	//if (FAILED(D3DXCreateTextureFromFileEx(
	//	CGraphic_Device::Get_Instance()->Get_Device(),
	//	wstrFilePath.c_str(),
	//	m_pTexInfo->tImageInfo.Width,
	//	m_pTexInfo->tImageInfo.Height,
	//	m_pTexInfo->tImageInfo.MipLevels,
	//	0,
	//	m_pTexInfo->tImageInfo.Format,
	//	D3DPOOL_MANAGED,
	//	D3DX_DEFAULT, D3DX_DEFAULT,
	//	0,
	//	&m_pTexInfo->tImageInfo,
	//	nullptr,
	//	&m_pTexInfo->pTexture)))
	//{
	//	wstring wstrErr_Message = wstrFilePath + L"CreateTexture Failed";
	//	ERR_MSG(wstrErr_Message.c_str());
	//	return E_FAIL;
	//}




	//const TEXINFO* pTexInfo = CTexture_Manager::Get_Instance()->Get_TexInfo(L"Player", m_pFrame, m_tFrame.fStartFrame);
	//if (nullptr == pTexInfo)
	//	return;

	//float fCenterX = pTexInfo->tImageInfo.Width*0.5f;
	//float fCenterY = pTexInfo->tImageInfo.Height*0.5f;

	//D3DXMatrixScaling(&matScale, 1000.f / (vTemp.z), 1000.f / (vTemp.z), 0.f);
	//D3DXMatrixTranslation(&matTrans, vTemp.x*1000.f / (vTemp.z) + WINCX*0.5f, vTemp.y*1000.f / (vTemp.z) + WINCY*0.5f, 0.f);

	//m_tInfo.matWorld = matScale*matRotZ*matTrans;

	//CGraphic_Device::Get_Instance()->Get_Sprite()->SetTransform(&m_tInfo.matWorld);
	//CGraphic_Device::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 100, 100, 100));
}

void CPlayerUI::Free(void)
{
	Engine::CGameObject::Free();
}


HRESULT CPlayerUI::Add_Component(void)
{
	Engine::CComponent*		pComponent = nullptr;

	return S_OK;
}

CPlayerUI* CPlayerUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerUI*		pInstance = new CPlayerUI(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
		Engine::Safe_Release(pInstance);

	return pInstance;
}

