// ObjectTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "MFCTool.h"
#include "ObjectTab.h"
#include "afxdialogex.h"


// CObjectTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CObjectTab, CDialogEx)

CObjectTab::CObjectTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OBJECTTAB, pParent)
{

}

CObjectTab::~CObjectTab()
{
}

void CObjectTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_vertexListBox);
	DDX_Control(pDX, IDC_EDIT1, m_VertexPosX);
	DDX_Control(pDX, IDC_EDIT2, m_VertexPosY);
	DDX_Control(pDX, IDC_EDIT3, m_VertexPosZ);
	DDX_Control(pDX, IDC_EDIT4, m_Index0);
	DDX_Control(pDX, IDC_EDIT5, m_Index1);
	DDX_Control(pDX, IDC_EDIT6, m_Index2);
	DDX_Control(pDX, IDC_LIST2, m_indexListBox);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_colorButton);
	DDX_Control(pDX, IDC_CHECK1, m_bWire);
	DDX_Control(pDX, IDC_CHECK2, m_bCul);
}


BEGIN_MESSAGE_MAP(CObjectTab, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON6, &CObjectTab::OnBnClickedVertexAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CObjectTab::OnLbnSelchangeVertexList)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectTab::OnBnClickedVertexSave)
	ON_BN_CLICKED(IDC_BUTTON7, &CObjectTab::OnBnClickedIndexAdd)
	ON_LBN_SELCHANGE(IDC_LIST2, &CObjectTab::OnLbnSelchangeIndexList)
	ON_BN_CLICKED(IDC_BUTTON3, &CObjectTab::OnBnClickedIndexSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CObjectTab::OnBnClickedIndexDel)
	ON_BN_CLICKED(IDC_BUTTON2, &CObjectTab::OnBnClickedVertexDel)
	ON_BN_CLICKED(IDC_BUTTON5, &CObjectTab::OnBnClickedMeshSave)
	ON_BN_CLICKED(IDC_BUTTON9, &CObjectTab::OnBnClickedMeshLoad)
	ON_BN_CLICKED(IDC_BUTTON8, &CObjectTab::OnBnClickedSetPreview)
	ON_BN_CLICKED(IDC_CHECK1, &CObjectTab::OnBnClickedBtnWire)
	ON_BN_CLICKED(IDC_CHECK2, &CObjectTab::OnBnClickedBtnCul)
END_MESSAGE_MAP()


// CObjectTab �޽��� ó�����Դϴ�.

//���ؽ� ���� �߰�
void CObjectTab::OnBnClickedVertexAdd() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString name;
	name.Format(_T("%d"), m_vertexCount);
	m_vertexListBox.AddString(name);
	++m_vertexCount;

	Engine::VTXCOL tempVertex;
	CString tempString;

	m_VertexPosX.GetWindowTextW(tempString);
	tempVertex.vPosition.x = (float)_ttof(tempString);

	m_VertexPosY.GetWindowTextW(tempString);
	tempVertex.vPosition.y = (float)_ttof(tempString);

	m_VertexPosZ.GetWindowTextW(tempString);
	tempVertex.vPosition.z = (float)_ttof(tempString);

	DWORD temp = m_colorButton.GetColor();

	Change_ColorMFCToDirect(&temp, &tempVertex.dwColor);

	m_listVertex.emplace_back(tempVertex);
}

//����Ʈ�� Ư�� ���ؽ� Ŭ��
void CObjectTab::OnLbnSelchangeVertexList() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = m_vertexListBox.GetCurSel();

	if (index < 0 || index >= m_vertexCount)
		return;

	list<Engine::VTXCOL>::iterator iter_find = m_listVertex.begin();
	int i = 0;
	for (; i != index; ++i, ++iter_find) {
	}

	CString tempString;

	tempString.Format(_T("%f"), (*iter_find).vPosition.x);
	m_VertexPosX.SetWindowTextW(tempString);

	tempString.Format(_T("%f"), (*iter_find).vPosition.y);
	m_VertexPosY.SetWindowTextW(tempString);

	tempString.Format(_T("%f"), (*iter_find).vPosition.z);
	m_VertexPosZ.SetWindowTextW(tempString);

	DWORD temp;
	Change_ColorDirectToMFC(&(*iter_find).dwColor, &temp);
	m_colorButton.SetColor(temp);

	if (m_pickIndex != -1) {
		GiveBack_Color(m_pickIndex);
	}

	m_pickIndex = index;
	m_pickColor = (*iter_find).dwColor;
	(*iter_find).dwColor = (DWORD)16711935;

	OnBnClickedSetPreview();
}

//�̹� �����ϴ� ���ؽ��� ���� �����ϰ� ����
void CObjectTab::OnBnClickedVertexSave() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = m_vertexListBox.GetCurSel();

	if (index < 0 || index >= (int)m_listVertex.size())
		return;

	list<Engine::VTXCOL>::iterator iter_find = m_listVertex.begin();
	int i = 0;
	for (; i != index; ++i, ++iter_find) {
	}

	CString tempString;

	m_VertexPosX.GetWindowTextW(tempString);
	(*iter_find).vPosition.x = (float)_ttof(tempString);

	m_VertexPosY.GetWindowTextW(tempString);
	(*iter_find).vPosition.y = (float)_ttof(tempString);

	m_VertexPosZ.GetWindowTextW(tempString);
	(*iter_find).vPosition.z = (float)_ttof(tempString);

	DWORD temp = m_colorButton.GetColor();
	Change_ColorMFCToDirect(&temp, &m_pickColor);
}


void CObjectTab::OnBnClickedIndexAdd() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index0, index1, index2;

	CString tempString;

	m_Index0.GetWindowTextW(tempString);
	index0 = _wtoi(tempString);

	m_Index1.GetWindowTextW(tempString);
	index1 = _wtoi(tempString);

	m_Index2.GetWindowTextW(tempString);
	index2 = _wtoi(tempString);

	//�ְ��� �ϴ� �ε����� ���� �ߺ��̸� ������
	if (index0 == index1 || index1 == index2 || index0 == index2) {
		return;
	}

	//���� ���ؽ��� �����Ϸ��� �ϸ� ������
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


void CObjectTab::OnLbnSelchangeIndexList() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = m_indexListBox.GetCurSel();

	if (index < 0 || index >= m_indexCount)
		return;

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


void CObjectTab::OnBnClickedIndexSave() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int listIndex = m_indexListBox.GetCurSel();

	if (listIndex < 0 || listIndex >= (int)m_listIndex.size())
		return;

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

	//�ٲٰ��� �ϴ� �ε����� ���� �ߺ��̸� ������
	if (index0 == index1 || index1 == index2 || index0 == index2) {
		return;
	}

	//���� ���ؽ��� �����Ϸ��� �ϸ� ������
	if (index0 >= m_vertexCount || index1 >= m_vertexCount || index2 >= m_vertexCount) {
		return;
	}

	(*iter_find)._0 = index0;

	(*iter_find)._1 = index1;

	(*iter_find)._2 = index2;
}


void CObjectTab::OnBnClickedIndexDel() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = m_indexListBox.GetCurSel();
	if (index >= 0 && index < m_indexCount) {
		Erase_Index(index);
	}
}

void CObjectTab::Erase_Index(int _delIndex) {
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

void CObjectTab::Add_VertexToListBox() {
	int index = 0;
	for (; index != m_vertexCount; ++index) {
		CString tempString;
		tempString.Format(_T("%d"), index);
		m_vertexListBox.AddString(tempString);
	}
}

void CObjectTab::Add_IndexToListBox() {
	int index = 0;
	for (; index != m_indexCount; ++index) {
		CString tempString;
		tempString.Format(_T("%d"), index);
		m_indexListBox.AddString(tempString);
	}
}

void CObjectTab::Set_ToolView(CMFCToolView * _toolView) {
	m_pToolView = _toolView;
}

bool CObjectTab::Check_Index16(Engine::INDEX16 _index, int _vertexNum) {
	Engine::_ushort sVertexNum = (Engine::_ushort)_vertexNum;
	if (_index._0 == sVertexNum)
		return true;

	if (_index._1 == sVertexNum)
		return true;

	if (_index._2 == sVertexNum)
		return true;

	return false;
}

void CObjectTab::Change_ColorMFCToDirect(DWORD * _mfc, DWORD * _direct) {
	DWORD temp = *_mfc;
	*_direct = (DWORD)0;

	DWORD Red = (DWORD)(255);
	DWORD Green = (DWORD)(255);
	DWORD Blue = (DWORD)(255);

	Red = Red & temp;
	temp >>= 8;

	Green = Green&temp;
	temp >>= 8;

	Blue = Blue&temp;

	*_direct |= (DWORD)255;
	*_direct <<= 8;

	*_direct |= Red;
	*_direct <<= 8;

	*_direct |= Green;
	*_direct <<= 8;

	*_direct |= Blue;
}

void CObjectTab::Change_ColorDirectToMFC(DWORD * _direct, DWORD * _mfc) {
	DWORD temp = *_direct;
	*_mfc = (DWORD)0;

	DWORD Red = (DWORD)(255);
	DWORD Green = (DWORD)(255);
	DWORD Blue = (DWORD)(255);

	Blue = Blue&temp;
	temp >>= 8;

	Green = Green&temp;
	temp >>= 8;

	Red = Red&temp;



	*_mfc <<= 8;
	*_mfc |= Blue;

	*_mfc <<= 8;
	*_mfc |= Green;

	*_mfc <<= 8;
	*_mfc |= Red;
}

void CObjectTab::GiveBack_Color(int _index) {
	if (_index >= (int)m_listVertex.size()) {
		return;
	}

	list<Engine::VTXCOL>::iterator iter_vtx = m_listVertex.begin();
	for (int i = 0; i != _index; ++i, ++iter_vtx) {
	}

	(*iter_vtx).dwColor = m_pickColor;
}

list<Engine::VTXCOL> CObjectTab::Get_Vertex() {
	return m_listVertex;
}




void CObjectTab::OnBnClickedVertexDel() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int index = m_vertexListBox.GetCurSel();

	list<Engine::VTXCOL>::iterator iter_find = m_listVertex.begin();

	if (index < 0 || index >= m_vertexCount) {
		return;
	}

	m_pickIndex = -1;

	m_vertexListBox.ResetContent();
	for (int i = 0; i<m_vertexCount; ++i) {
		if (i == index) {
			iter_find = m_listVertex.erase(iter_find);
		}
		else {
			++iter_find;
		}
	}

	--m_vertexCount;

	Add_VertexToListBox();

	list<Engine::INDEX16>::iterator iter_list = m_listIndex.begin();
	m_indexListBox.ResetContent();
	for (int i = 0; i < m_indexCount; ++i) {
		if (Check_Index16((*iter_list), index)) {
			iter_list = m_listIndex.erase(iter_list);
		}
		else {
			if ((*iter_list)._0 > index) {
				--(*iter_list)._0;
			}

			if ((*iter_list)._1 > index) {
				--(*iter_list)._1;
			}

			if ((*iter_list)._2 > index) {
				--(*iter_list)._2;
			}
			++iter_list;
		}
	}

	m_indexCount = (int)m_listIndex.size();
	Add_IndexToListBox();
}


void CObjectTab::OnBnClickedMeshSave() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"Data File(*.dat)|*.dat||", this);
	TCHAR szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal()) {
		CString strPath = Dlg.GetPathName();
		HANDLE hFile = CreateFile(strPath.GetString(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

		if (INVALID_HANDLE_VALUE == hFile) {
			AfxMessageBox(L"���� �߸� ����!");
			return;
		}

		DWORD dwByte = 0;
		WriteFile(hFile, &m_vertexCount, sizeof(int), &dwByte, nullptr);
		for (list<Engine::VTXCOL>::iterator iter = m_listVertex.begin(); iter != m_listVertex.end(); ++iter) {
			WriteFile(hFile, &(*iter), sizeof(Engine::VTXCOL), &dwByte, nullptr);
		}

		WriteFile(hFile, &m_indexCount, sizeof(int), &dwByte, nullptr);
		for (list<Engine::INDEX16>::iterator iter = m_listIndex.begin(); iter != m_listIndex.end(); ++iter) {
			WriteFile(hFile, &(*iter), sizeof(Engine::INDEX16), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}
}


void CObjectTab::OnBnClickedMeshLoad() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	CFileDialog Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"Data File(*.dat)|*.dat||", this);
	TCHAR szPath[MAX_PATH] = L"";
	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath; // ���� ���� ��η� ���� 

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

		for (int i = 0; i < m_vertexCount; ++i) {
			Engine::VTXCOL tempVertex;
			ReadFile(hFile, &tempVertex, sizeof(Engine::VTXCOL), &dwByte, nullptr);
			m_listVertex.emplace_back(tempVertex);
		}

		ReadFile(hFile, &m_indexCount, sizeof(int), &dwByte, nullptr);

		for (int i = 0; i < m_indexCount; ++i) {
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


void CObjectTab::OnBnClickedSetPreview() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_pToolView != nullptr) {
		m_pToolView->Reset_Buffer(m_listVertex, m_listIndex);
	}
}


void CObjectTab::OnBnClickedBtnWire() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_pToolView != nullptr) {
		m_pToolView->Set_Wire(m_bWire.GetCheck() == BST_CHECKED);
	}
}


void CObjectTab::OnBnClickedBtnCul() {
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (m_pToolView != nullptr) {
		m_pToolView->Set_Cull(m_bCul.GetCheck() == BST_CHECKED);
	}
}