//---------------------------------------------------------------------
//	入力処理(input.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "input.h"

#define DI_JOY_I_INPUT (1000)
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
static CInput *m_pInput;
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//--------------------------------------------
//インプットクラス コンストラクタ
//--------------------------------------------
CInput::CInput()
{
	m_pDevice = NULL;
	m_pInput = NULL;
}

//--------------------------------------------
//インプットクラス デストラクタ
//--------------------------------------------
CInput::~CInput()
{
}

//--------------------------------------------
// インプットクラス初期化
//--------------------------------------------
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInputオブジェクトの生成
	if (m_pInput == NULL)
	{
		if (FAILED(DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_pInput,
			NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//--------------------------------------------
// インプットクラス終了処理
//--------------------------------------------
void CInput::Uninit(void)
{
	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	//消されていなかったときに消す
	// 入力デバイス(キーボード)の開放
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}
//--------------------------------------------
// インプットクラス更新処理
//--------------------------------------------
void CInput::Update(void)
{
}

//*****************************************************************************

//			キーボードクラス

//*****************************************************************************
//=============================================================================
//キーボードクラス コンストラクタ
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//キー情報をクリア
	//m_aKeyState[NUM_KEY_MAX] = {};
	//m_aKeyStateTrigger[NUM_KEY_MAX] = {};
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = 0;
		m_aKeyStateTrigger[nCnt] = 0;
	}
}

//=============================================================================
//キーボードクラス デストラクタ
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// キーボードの初期化
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//初期化してから
	CInput::Init(hInstance, hWnd);

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard,
		&m_pDevice,
		NULL)))
	{
		return E_FAIL;
	}
	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// 入力デバイス(キーボード)の開放
	CInput::Uninit();
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & m_aKeyState[nCntKey];
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//=============================================================================
// キーボードの入力情報(プレス情報)を取得
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}
//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// キーボードの入力情報(リリース情報)を取得
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

HRESULT CDirectInput::Init(HINSTANCE hinstance, HWND hWnd)
{
	//初期化処理
	CInput::Init(hinstance, hWnd);

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	if (m_pDevice != NULL)
	{// 生成できた
		DIPROPRANGE diprg;

		// 軸の値の範囲を設定
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -DI_JOY_I_INPUT;
		diprg.lMax = DI_JOY_I_INPUT;

		// 軸の設定
		// 左アナログスティック
		diprg.diph.dwObj = DIJOFS_X;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 右アナログスティック
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// 十字キー(上を0度とし時計回りに角度 * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ジョイスティックへのアクセス権を獲得(入力制御開始)
		m_pDevice->Acquire();
	}

	return true;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void CDirectInput::Uninit(void)
{
	//終了処理
	CInput::Uninit();

	// 入力デバイス(キーボード)の開放
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	//キーボードのアドレス権を破棄
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// ジョイパッドの更新処理
//=============================================================================
void CDirectInput::Update(void)
{
	DIJOYSTATE dJoystate;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		// 入力デバイスからデータを取得
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(dJoystate), &dJoystate)))
		{
			m_fLeftAxiz_X = (float)dJoystate.lX;
			m_fLeftAxiz_Y = (float)dJoystate.lY;
			m_fRightAxiz_X = (float)dJoystate.lZ;
			m_fRightAxiz_Y = (float)dJoystate.lRz;

			if (dJoystate.lX < -100 || dJoystate.lX > 100 || dJoystate.lY < -100 || dJoystate.lY > 100)
			{//左スティックを倒した時
				m_Stick[0] = 0x80;
			}
			else
			{//左スティックを倒してない時
				m_Stick[0] = 0;
			}

			if (dJoystate.lZ < -100 || dJoystate.lZ > 100 || dJoystate.lRz < -100 || dJoystate.lRz > 100)
			{//右スティックを倒している時
				m_Stick[1] = 0x80;
			}
			else
			{//右スティックを倒してない時
				m_Stick[1] = 0;
			}

			if (dJoystate.rgdwPOV[0] / 100 == 0)
			{//上
				dJoystate.rgbButtons[DIJS_BUTTON_29] = 0x80;
				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 45)
			{//右上
				dJoystate.rgbButtons[DIJS_BUTTON_29] = 0x80;
				dJoystate.rgbButtons[DIJS_BUTTON_30] = 0x80;

				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 90)
			{//右
				dJoystate.rgbButtons[DIJS_BUTTON_30] = 0x80;
				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 135)
			{//右下
				dJoystate.rgbButtons[DIJS_BUTTON_30] = 0x80;
				dJoystate.rgbButtons[DIJS_BUTTON_31] = 0x80;

				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 180)
			{//下
				dJoystate.rgbButtons[DIJS_BUTTON_31] = 0x80;

				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 225)
			{//左下
				dJoystate.rgbButtons[DIJS_BUTTON_28] = 0x80;
				dJoystate.rgbButtons[DIJS_BUTTON_31] = 0x80;
				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 270)
			{//左
				dJoystate.rgbButtons[DIJS_BUTTON_28] = 0x80;
				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 315)
			{//左上
				dJoystate.rgbButtons[DIJS_BUTTON_28] = 0x80;
				dJoystate.rgbButtons[DIJS_BUTTON_29] = 0x80;
				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}

			for (int nCntKey = 0; nCntKey < 32; nCntKey++)
			{
				//トリガー
				m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ dJoystate.rgbButtons[nCntKey]) & dJoystate.rgbButtons[nCntKey];	//コントローラー入力情報保存

																																		//リリー																														//g_aKeyStateRelase[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];	//コントローラー入力情報保存
																																		//プレス
				m_aKeyState[nCntKey] = dJoystate.rgbButtons[nCntKey];   //コントローラー入力情報
			}
		}
		else
		{
			m_pDevice->Acquire();
		}
	}
}

//=============================================================================
// コントローラーの入力情報(プレス情報)を取得
//=============================================================================
bool CDirectInput::GetPress(int nButton)
{
	return(m_aKeyState[nButton] & 0x80) ? true : false;
}

//=============================================================================
// コントローラーの入力情報(トリガー情報)を取得
//=============================================================================
bool CDirectInput::GetTrigger(int nButton)
{
	return(m_aKeyStateTrigger[nButton] & 0x80) ? true : false;
}

//=============================================================================
// コントローラーの入力情報(トリガー情報)を取得
//=============================================================================
bool CDirectInput::GetStick(int nButton)
{
	return(m_Stick[nButton] & 0x80) ? true : false;
}

//=============================================================================
// コントローラーの入力情報(トリガー情報)を取得
//=============================================================================
bool CDirectInput::GetAnyButton(int nNumber)
{
	if (nNumber == 0)
	{
		for (int nCnt = 0; nCnt < DIJS_BUTTON_MAX; nCnt++)
		{
			if (m_aKeyStateTrigger[nCnt] == 0x80)
			{
				return true;
			}
		}
	}
	return false;
}
//=============================================================================
// 左スティックの角度を取得
//=============================================================================
float CDirectInput::GetLeftAxiz(void)
{
	//左スティックの角度を取得
	float Axiz = atan2f(m_fLeftAxiz_X, m_fLeftAxiz_Y);

	return Axiz;
}

//=============================================================================
// 右スティックの角度を取得
//=============================================================================
float CDirectInput::GetRightAxiz(void)
{
	//右スティックの角度
	float Axiz = atan2f(m_fRightAxiz_X, m_fRightAxiz_Y);

	return Axiz;
}

//=============================================================================
// 十字キーの角度を取得
//=============================================================================
float CDirectInput::GetRadian(void)
{
	float fRadian = m_fRadian / 100;
	return fRadian;
}