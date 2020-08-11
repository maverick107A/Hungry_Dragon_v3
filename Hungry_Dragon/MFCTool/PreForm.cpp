// PreForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "PreForm.h"

using namespace std;

// CPreForm

IMPLEMENT_DYNCREATE(CPreForm, CFormView)

CPreForm::CPreForm()
	: CFormView(IDD_PREFORM)
{

}

CPreForm::~CPreForm()
{
}

void CPreForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_vertexListBox);
	DDX_Control(pDX, IDC_EDIT1, m_VertexPosX);
	DDX_Control(pDX, IDC_EDIT2, m_VertexPosY);
	DDX_Control(pDX, IDC_EDIT3, m_VertexPosZ);
	DDX_Control(pDX, IDC_EDIT4, m_Index0);
	DDX_Control(pDX, IDC_EDIT5, m_Index1);
	DDX_Control(pDX, IDC_EDIT6, m_Index2);
	DDX_Control(pDX, IDC_LIST2, m_indexListBox);
}

BEGIN_MESSAGE_MAP(CPreForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON6, &CPreForm::OnBnClickedVertexAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CPreForm::OnLbnSelchangeVertexList)
	ON_BN_CLICKED(IDC_BUTTON1, &CPreForm::OnBnClickedVertexSave)
	ON_BN_CLICKED(IDC_BUTTON7, &CPreForm::OnBnClickedIndexAdd)
	ON_LBN_SELCHANGE(IDC_LIST2, &CPreForm::OnLbnSelchangeIndexList)
	ON_BN_CLICKED(IDC_BUTTON3, &CPreForm::OnBnClickedIndexSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CPreForm::OnBnClickedIndexDel)
	ON_BN_CLICKED(IDC_BUTTON2, &CPreForm::OnBnClickedVertexDel)
	ON_BN_CLICKED(IDC_BUTTON5, &CPreForm::OnBnClickedMeshSave)
	ON_BN_CLICKED(IDC_BUTTON9, &CPreForm::OnBnClickedMeshLoad)
END_MESSAGE_MAP()


// CPreForm 진단입니다.

#ifdef _DEBUG
void CPreForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPreForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPreForm 메시지 처리기입니다.

//버텍스 새로 추가
void CPreForm::OnBnClickedVertexAdd() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString name;
	name.Format(_T("%d"), m_vertexCount);
	m_vertexListBox.AddString(name);
	++m_vertexCount;

	Engine::VTXCOL tempVertex;
	CString tempString;

	m_VertexPosX.GetWindowTextW(tempString);
	tempVertex.vPosition.x=(float)_wtoi(tempString);

	m_VertexPosY.GetWindowTextW(tempString);
	tempVertex.vPosition.y = (float)_wtoi(tempString);

	m_VertexPosZ.GetWindowTextW(tempString);
	tempVertex.vPosition.z = (float)_wtoi(tempString);

	tempVertex.dwColor = D3DXCOLOR(255.f, 255.f, 255.f, 255.f);

	m_listVertex.emplace_back(tempVertex);
}

//리스트의 특정 버텍스 클릭
void CPreForm::OnLbnSelchangeVertexList() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_vertexListBox.GetCurSel();
	list<Engine::VTXCOL>::iterator iter_find = m_listVertex.begin();
	int i = 0;
	for (; i != index; ++i, ++iter_find) {
	}

	CString tempString;

	tempString.Format(_T("%d"), (int)(*iter_find).vPosition.x);
	m_VertexPosX.SetWindowTextW(tempString);

	tempString.Format(_T("%d"), (int)(*iter_find).vPosition.y);
	m_VertexPosY.SetWindowTextW(tempString);

	tempString.Format(_T("%d"), (int)(*iter_find).vPosition.z);
	m_VertexPosZ.SetWindowTextW(tempString);

	//해당 버텍스에 선택됐음을 표기하는 것도 필요할 듯
}

//이미 존재하는 버텍스의 값을 변경하고 저장
void CPreForm::OnBnClickedVertexSave() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_vertexListBox.GetCurSel();
	list<Engine::VTXCOL>::iterator iter_find = m_listVertex.begin();
	int i = 0;
	for (; i != index; ++i, ++iter_find) {
	}

	CString tempString;

	m_VertexPosX.GetWindowTextW(tempString);
	(*iter_find).vPosition.x = (float)_wtoi(tempString);

	m_VertexPosY.GetWindowTextW(tempString);
	(*iter_find).vPosition.y = (float)_wtoi(tempString);

	m_VertexPosZ.GetWindowTextW(tempString);
	(*iter_find).vPosition.z = (float)_wtoi(tempString);
}


void CPreForm::OnBnClickedIndexAdd() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index0, index1, index2;

	CString tempString;
	
	m_Index0.GetWindowTextW(tempString);
	index0 = _wtoi(tempString);

	m_Index1.GetWindowTextW(tempString);
	index1 = _wtoi(tempString);

	m_Index2.GetWindowTextW(tempString);
	index2 = _wtoi(tempString);

	//넣고자 하는 인덱스가 서로 중복이면 무시함
	if (index0 == index1 || index1 == index2 || index0 == index2) {
		return;
	}

	//없는 버텍스를 참조하려고 하면 무시함
	if (index0 >= m_vertexCount || index1 >= m_vertexCount || index2 >= m_vertexCount) {
		return;
	}

	CString name;
	name.Format(_T("%d"), m_indexCount);
	m_indexListBox.AddString(name);
	++m_indexCount;

	Engine::INDEX16 tempIdx;
	tempIdx._0 = (Engine::_ushort)index0;
	tempIdx._1 = (Engine::_ushort)index1;
	tempIdx._2 = (Engine::_ushort)index2;

	m_listIndex.emplace_back(tempIdx);


	return;
}


void CPreForm::OnLbnSelchangeIndexList() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_indexListBox.GetCurSel();
	list<Engine::INDEX16>::iterator iter_find = m_listIndex.begin();
	int i = 0;
	for (; i != index; ++i, ++iter_find) {
	}

	CString tempString;

	tempString.Format(_T("%d"), (int)(*iter_find)._0);
	m_Index0.SetWindowTextW(tempString);

	tempString.Format(_T("%d"), (int)(*iter_find)._1);
	m_Index1.SetWindowTextW(tempString);

	tempString.Format(_T("%d"), (int)(*iter_find)._2);
	m_Index2.SetWindowTextW(tempString);
}


void CPreForm::OnBnClickedIndexSave() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int listIndex = m_indexListBox.GetCurSel();
	list<Engine::INDEX16>::iterator iter_find = m_listIndex.begin();
	int i = 0;
	for (; i != listIndex; ++i, ++iter_find) {
	}

	int index0, index1, index2;

	CString tempString;

	m_Index0.GetWindowTextW(tempString);
	index0 = _wtoi(tempString);

	m_Index1.GetWindowTextW(tempString);
	index1 = _wtoi(tempString);

	m_Index2.GetWindowTextW(tempString);
	index2 = _wtoi(tempString);

	//바꾸고자 하는 인덱스가 서로 중복이면 무시함
	if (index0 == index1 || index1 == index2 || index0 == index2) {
		return;
	}

	//없는 버텍스를 참조하려고 하면 무시함
	if (index0 >= m_vertexCount || index1 >= m_vertexCount || index2 >= m_vertexCount) {
		return;
	}

	(*iter_find)._0 = index0;

	(*iter_find)._1 = index1;

	(*iter_find)._2 = index2;
}


void CPreForm::OnBnClickedIndexDel() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_indexListBox.GetCurSel();
	if (index >= 0 && index < m_indexCount)
	{
		Erase_Index(index);
	}
}

void CPreForm::Erase_Index(int _delIndex) {
	list<Engine::INDEX16>::iterator iter_find = m_listIndex.begin();

	for (int i = 0; i != _delIndex; ++i, ++iter_find) {
	}

	iter_find = m_listIndex.erase(iter_find);

	--m_indexCount;
	for (int i = m_indexCount; i >= 0; --i) {
		m_indexListBox.DeleteString(i);
	}

	Add_IndexToListBox();
}

void CPreForm::Add_VertexToListBox() {
	int index = 0;
	for (; index != m_vertexCount; ++index) {
		CString tempString;
		tempString.Format(_T("%d"), index);
		m_vertexListBox.AddString(tempString);
	}
}

void CPreForm::Add_IndexToListBox() {
	int index = 0;
	for (; index != m_indexCount; ++index) {
		CString tempString;
		tempString.Format(_T("%d"), index);
		m_indexListBox.AddString(tempString);
	}
}

bool CPreForm::Check_Index16(Engine::INDEX16 _index, int _vertexNum)
{
	Engine::_ushort sVertexNum=(Engine::_ushort)_vertexNum;
	if (_index._0 == sVertexNum)
		return true;

	if (_index._1 == sVertexNum)
		return true;

	if (_index._2 == sVertexNum)
		return true;

	return false;
}




void CPreForm::OnBnClickedVertexDel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int index = m_vertexListBox.GetCurSel();
	list<Engine::VTXCOL>::iterator iter_find = m_listVertex.begin();

	if (index < 0 || index >= m_vertexCount)
	{
		return;
	}

	for (int i = m_vertexCount-1; i >= 0; --i)
	{
		m_vertexListBox.DeleteString(i);

		if (i == index)
		{
			iter_find=m_listVertex.erase(iter_find);
		}
		else
		{
			++iter_find;
		}	
	}

	--m_vertexCount;
	
	Add_VertexToListBox();

	list<Engine::INDEX16>::iterator iter_list = m_listIndex.begin();
	m_indexListBox.ResetContent();
	for (int i = 0; i < m_indexCount; ++i)
	{
		if (Check_Index16((*iter_list), index))
		{
			iter_list = m_listIndex.erase(iter_list);
		}
		else
		{
			if ((*iter_list)._0 > index)
			{
				--(*iter_list)._0;
			}

			if ((*iter_list)._1 > index)
			{
				--(*iter_list)._1;
			}

			if ((*iter_list)._2 > index)
			{
				--(*iter_list)._2;
			}
			++iter_list;
		}
	}

	m_indexCount = (int)m_listIndex.size();
	Add_IndexToListBox();
}


void CPreForm::OnBnClickedMeshSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"Data File(*.dat)|*.dat||", this);
	TCHAR szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		CString strPath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strPath.GetString(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile)
		{
			AfxMessageBox(L"파일 잘못 열음!");
			return;
		}

		DWORD dwByte = 0;
		WriteFile(hFile, &m_vertexCount, sizeof(int), &dwByte, nullptr);
		for (list<Engine::VTXCOL>::iterator iter = m_listVertex.begin(); iter != m_listVertex.end(); ++iter)
		{
			WriteFile(hFile, &(*iter), sizeof(Engine::VTXCOL), &dwByte, nullptr);
		}

		WriteFile(hFile, &m_indexCount, sizeof(int), &dwByte, nullptr);
		for (list<Engine::INDEX16>::iterator iter = m_listIndex.begin(); iter != m_listIndex.end(); ++iter)
		{
			WriteFile(hFile, &(*iter), sizeof(Engine::INDEX16), &dwByte, nullptr);
		}
	
		CloseHandle(hFile);
	}
}


void CPreForm::OnBnClickedMeshLoad() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"Data File(*.dat)|*.dat||", this);
	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath; // 내가 만든 경로로 ㄱㄱ 

	if (IDOK == Dlg.DoModal()) {
		m_vertexCount = 0;
		m_listVertex.clear();
		m_vertexListBox.ResetContent();
		m_indexCount = 0;
		m_listIndex.clear();
		m_indexListBox.ResetContent();


		CString strPath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strPath.GetString(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile) {
			return;
		}

		DWORD dwByte = 0;

		ReadFile(hFile, &m_vertexCount, sizeof(int), &dwByte, nullptr);

		for (int i = 0; i < m_vertexCount; ++i) 
		{
			Engine::VTXCOL tempVertex;
			ReadFile(hFile, &tempVertex, sizeof(Engine::VTXCOL), &dwByte, nullptr);
			m_listVertex.emplace_back(tempVertex);
		}

		ReadFile(hFile, &m_indexCount, sizeof(int), &dwByte, nullptr);

		for (int i = 0; i < m_indexCount; ++i)
		{
			Engine::INDEX16 tempIndex;
			ReadFile(hFile, &tempIndex, sizeof(Engine::INDEX16), &dwByte, nullptr);
			m_listIndex.emplace_back(tempIndex);
		}

		CloseHandle(hFile);

		Add_VertexToListBox();
		Add_IndexToListBox();
	}
	UpdateData(FALSE);
}

