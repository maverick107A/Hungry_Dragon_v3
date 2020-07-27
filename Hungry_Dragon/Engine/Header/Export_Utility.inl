// Management
// Get
CComponent*			Get_Component(const _tchar* pLayerTag, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID)
{
	return CManagement::GetInstance()->Get_Component(pLayerTag, pObjTag, pComponentTag, eID);
}
// Set
// General
HRESULT	Create_Management(CManagement** ppManagement)
{
	CManagement*	pManagement = CManagement::GetInstance();

	if (nullptr == pManagement)
		return E_FAIL;

	*ppManagement = pManagement;

	return S_OK;
}


//Object_Pool

HRESULT		Add_Object_Layer(OBJID _Type, _int iCnt)
{
	return CObjectPool::GetInstance()->Add_Object_Layer(_Type, iCnt);
}

HRESULT Set_Bullet_LayerMap(OBJID _Type, _int iCnt, _vec3 _Pos)
{
	return CObjectPool::GetInstance()->Set_Bullet_LayerMap(_Type, iCnt, _Pos);
}

void		Set_Object_LayerMap(CLayer *  _Layer)
{
	return CObjectPool::GetInstance()->Set_Object_LayerMap(_Layer);
}

// Release
void		Release_Utility(void)
{
	CManagement::GetInstance()->DestroyInstance();
	CObjectPool::GetInstance()->DestroyInstance();
}