//=============================================================================
//
// 入力処理 [inout.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define MAX_KEY (256)
//*********************************************************************
//インプットクラスの定義
//*********************************************************************
//基本クラス
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;		//派生先で変わる
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};
//派生クラス
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);

protected:
	BYTE m_aKeyState[NUM_KEY_MAX];					//キーボード入力情報(プレス)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			//キーボード入力情報(トリガー)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//キーボード入力情報(リリース)
};

//*****************************************************************************
//DirectInputクラス
//*****************************************************************************
class CDirectInput : public CInput
{
public:
	typedef enum
	{
		DIJS_BUTTON_1 = 0,	// X
		DIJS_BUTTON_2,		// Y
		DIJS_BUTTON_3,		// B
		DIJS_BUTTON_4,		// A
		DIJS_BUTTON_5,		// LB
		DIJS_BUTTON_6,		// RB
		DIJS_BUTTON_7,		// LT
		DIJS_BUTTON_8,		// RT

		DIJS_BUTTON_9,
		DIJS_BUTTON_10,
		DIJS_BUTTON_11,
		DIJS_BUTTON_12,
		DIJS_BUTTON_13,
		DIJS_BUTTON_14,
		DIJS_BUTTON_15,
		DIJS_BUTTON_16,
		DIJS_BUTTON_17,
		DIJS_BUTTON_18,
		DIJS_BUTTON_19,

		DIJS_BUTTON_20,		// 左スティック←
		DIJS_BUTTON_21,		// 左スティック↑
		DIJS_BUTTON_22,		// 左スティック→
		DIJS_BUTTON_23,		// 左スティック↓

		DIJS_BUTTON_24,		// 右スティック←
		DIJS_BUTTON_25,		// 右スティック↑
		DIJS_BUTTON_26,		// 右スティック→
		DIJS_BUTTON_27,		// 右スティック↓

		DIJS_BUTTON_28,		// 十字キー←
		DIJS_BUTTON_29,		// 十字キー↑
		DIJS_BUTTON_30,		// 十字キー→
		DIJS_BUTTON_31,		// 十字キー↓
		DIJS_BUTTON_MAX,
	}DIJS_BUTTON;
	//CDirectInput();
	//~CDirectInput();

	HRESULT Init(HINSTANCE hinstance, HWND hwnd);
	void Uninit(void);
	void Update(void);

	bool GetPress(int nButton);
	bool GetTrigger(int nButton);
	bool GetStick(int nButton);
	bool GetAnyButton(int nNumber);
	//bool GetKeyboardRelase(int nKey);

	float GetLeftAxiz(void);
	float GetRightAxiz(void);
	float GetRadian(void);

private:
	BYTE m_aKeyState[MAX_KEY];
	BYTE m_aKeyStateTrigger[MAX_KEY];
	BYTE m_Stick[2];
	float m_fLeftAxiz_X;
	float m_fLeftAxiz_Y;
	float m_fRightAxiz_X;
	float m_fRightAxiz_Y;
	float m_fRadian;
};
#endif