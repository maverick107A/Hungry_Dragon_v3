#include "stdafx.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(CKeyMgr)
CKeyMgr::CKeyMgr()
{
}


CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::Key_Update()
{
	m_dwPress = 0;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwPress |= KM_LBUTTON;

	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwPress |= KM_RBUTTON;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwPress |= KM_LEFT;

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwPress |= KM_RIGHT;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwPress |= KM_UP;

	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwPress |= KM_DOWN;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwPress |= KM_SPACE;

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwPress |= KM_ENTER;
	
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
		m_dwPress |= KM_TAB;

	if (GetAsyncKeyState(VK_F11) & 0x8000)
		m_dwPress |= KM_F11;

	m_dwChanged = (m_dwPressed^m_dwPress);		// 0101 ^ 0011 = 0110	// 변화된 부위를 나타냄 
	m_dwDown = (m_dwPress&m_dwChanged);			// 0011 & 0110	= 0010			// 1로 변화된 곳은 Down 스위치를 켜기
	m_dwUp = ((~m_dwPress)&m_dwChanged);			// 1100 & 0110	= 0100		// 0으로 변화된 곳은 Up 스위치를 켜기
	m_dwPressed = m_dwPress;					// 다음 프레임 준비
}
