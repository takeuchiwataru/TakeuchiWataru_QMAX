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
#define	NUM_BUTTON_MAX		(32)	// キーの最大数

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

//*********************************************************************
//コントローラーの定義
//*********************************************************************
//派生クラス
class CInputJoypad : public CInput
{
public:
	typedef enum
	{
		BUTTON_X = 0,
		BUTTON_A,
		BUTTON_B,
		BUTTON_Y,
		BUTTON_LB,
		BUTTON_RB,
		BUTTON_LT,
		BUTTON_RT,
		BUTTON_BACK,
		BUTTON_START,
		BUTTON_10,
		BUTTON_11,
		BUTTON_12,
		BUTTON_13,
		BUTTON_14,
		BUTTON_15,
		POV_UP_RIGHT,	//十字キー　右上
		POV_UP_LEFT,	//十字キー　左上
		POV_DOWN_RIGHT,	//十字キー　右下
		POV_DOWN_LEFT,	//十字キー　左下
		POV_UP,			//十字キー　上
		POV_DOWN,		//十字キー　下
		POV_RIGHT,		//十字キー　右
		POV_LEFT,		//十字キー　左
		STICK_L_UP,		//左スティック　上
		STICK_L_DOWN,	//左スティック　下
		STICK_L_RIGHT,	//左スティック　右
		STICK_L_LEFT,	//左スティック　左
		STICK_R_UP,		//右スティック　上
		STICK_R_DOWN,	//右スティック　下
		STICK_R_RIGHT,	//右スティック　右
		STICK_R_LEFT,	//右スティック　左
		MAX_BUTTON,
	}DIJS_BUTTON;
	CInputJoypad();
	~CInputJoypad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit();
	void Update();
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetAnyButton(int nNumber);

	float GetLeftAxiz(void);
	float GetRightAxiz(void);
	float GetRadian(void);

protected:
	BYTE m_aKeyState[NUM_BUTTON_MAX];					//コントローラーの入力情報(プレス)
	BYTE m_aKeyStateTrigger[NUM_BUTTON_MAX];			//コントローラーの入力情報(トリガー)
	BYTE m_aKeyStateRelease[NUM_BUTTON_MAX];			//コントローラーの入力情報(リリース)
	float m_LeftAxizX;								//向き
	float m_LeftAxizY;								//向き
	float m_RightAxizX;								//向き
	float m_RightAxizY;								//向き
	float m_Radian;									//
};

#endif