#ifndef KeyMgr_h__
#define KeyMgr_h__

#include "Engine_Define.h"
#include "Base.h"

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

//#define KM_TAB		0x00000200
//#define KM_TAB		0x00000400
//#define KM_TAB		0x00000800
//#define KM_TAB		0x00001000
//#define KM_TAB		0x00002000
//#define KM_TAB		0x00004000
//#define KM_TAB		0x00008000
//#define KM_TAB		0x00010000
//#define KM_TAB		0x00020000
//#define KM_TAB		0x00040000
//#define KM_TAB		0x00080000

#define KM_F1		0x00100000
#define KM_F2		0x00200000
#define KM_F3		0x00400000
#define KM_F4		0x00800000
#define KM_F5		0x01000000
#define KM_F6		0x02000000
#define KM_F7		0x04000000
#define KM_F8		0x08000000
#define KM_F9		0x10000000
#define KM_F10		0x20000000
#define KM_F11		0x40000000
#define KM_F12		0x80000000
#define KM_ALLKEY	0xffffffff

USING(Engine)

class ENGINE_DLL CKeyMgr : public CBase
{
	DECLARE_SINGLETON(CKeyMgr)
private:
	CKeyMgr();
	~CKeyMgr();
public:
	void Key_Update();
	void Key_UpdateByDinput();
	
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


	// CBase을(를) 통해 상속됨
	virtual void Free(void) override;
};


#endif