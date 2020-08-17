#pragma once

#define KM_DEFAULT	0x00000000
#define KM_LEFT		0x00000001
#define KM_RIGHT	0x00000002
#define KM_DOWN		0x00000004
#define KM_UP		0x00000008
#define KM_LBUTTON	0x00000010
#define KM_RBUTTON	0x00000020
#define KM_SPACE	0x00000040
#define KM_ENTER	0x00000080
#define KM_TAB		0x00000100
#define KM_F11		0x10000000

#define KM_ALLKEY	0xffffffff


class CKeyMgr
{
	DECLARE_SINGLETON(CKeyMgr)
private:
	CKey_Manager();
	~CKey_Manager();
public:
	void Key_Update();
	
	void Pressed_Update()	// 이전에 눌린 상태를 저장
	{
		m_dwPressed = m_dwPress;
	}
	bool Key_Down(DWORD dwKey)
	{
		if (m_dwDown & dwKey)
		{
			return true;
		}
		return false;
	}
	bool Key_Press(DWORD dwKey)
	{
		if (m_dwPress & dwKey)
		{
			return true;
		}
		return false;
	}
	bool Key_Up(DWORD dwKey)
	{
		if (m_dwUp & dwKey)
		{
			return true;
		}
		return false;
	}
	bool Key_Combine(DWORD dwKeyPreceding, DWORD dwKeyCommand)
	{
		return Key_Press(dwKeyPreceding) && Key_Down(dwKeyCommand);
	}
private:
	DWORD m_dwChanged = 0;
	DWORD m_dwPress = 0;
	DWORD m_dwPressed = 0;
	DWORD m_dwUp=0;
	DWORD m_dwDown=0;

};

