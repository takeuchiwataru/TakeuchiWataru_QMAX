//=========================================================================================================================
// 
// ���͏��� [input.cpp]
// Author : Eisuke Sakagawa
// 
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#define INITGUID
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "input.h"
#include "dinputex.h"

#include "camera.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	NUM_KEY_MAX			(256)									// �L�[�̍ő吔
#define	NUM_MOUSE_MAX		(8)										// �}�E�X�̍ő吔
#define	NUM_BUTTON_MAX		(32)									// �{�^���̍ő吔

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECTINPUT8				g_pInput = NULL;					// DirerctInput�I�u�W�F�N�g�ւ̃|�C���^

LPDIRECTINPUTDEVICE8		g_pDevKeyboard = NULL;					// ���̓f�o�C�X�i�L�[�{�[�h�j�ւ̃|�C���^
BYTE						g_aKeyStatePress[NUM_KEY_MAX];			// �L�[�{�[�h�̓��͏��i�v���X���j
BYTE						g_aKeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̓��͏��i�g���K�[���j
BYTE						g_aKeyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̓��͏��i�����[�X���j

LPDIRECTINPUTDEVICE8		g_pDevMouse = NULL;						// ���̓f�o�C�X�i�}�E�X�j�ւ̃|�C���^
POINT					    Pos, WPos;
DIMOUSESTATE2				g_MouseState;
DIMOUSESTATE2				g_aMouseStatePress;						// �}�E�X�̓��͏��i�v���X���j
DIMOUSESTATE2				g_aMouseStateTrigger;					// �}�E�X�̓��͏��i�g���K�[���j
DIMOUSESTATE2				g_aMouseStateRelease;					// �}�E�X�̓��͏��i�����[�X���


LPDIRECTINPUTDEVICE8		g_pDevJoystick = NULL;					// ���̓f�o�C�X�i�W���C�X�e�B�b�N�j�ւ̃|�C���^
DIDEVCAPS			        g_pDevCaps;								// ���̓f�o�C�X�i�W���C�X�e�B�b�N�j�ւ̃|�C���^
DIJOYSTATE					g_aButtonStatePress;					// �{�^���̓��͏��i�v���X���j
DIJOYSTATE					g_aButtonStateTrigger;					// �{�^���̓��͏��i�g���K�[���j
DIJOYSTATE					g_aButtonStateRelease;					// �{�^���̓��͏��i�����[�X���j
DIJOYSTATE					g_aStickState = {};						// �W���C�R���̓��͏��i�X�e�B�b�N�j
bool						g_bUseJoycon = false;

BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE*, VOID*);
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE*, VOID*);

//=========================================================================================================================
// �L�[�{�[�h�̏�����
//=========================================================================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//=========================================================================================================================
// �L�[�{�[�h�̍X�V����
//=========================================================================================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateRelease[nCntKey] = (g_aKeyStatePress[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyStatePress[nCntKey];
			g_aKeyStateTrigger[nCntKey] = (g_aKeyStatePress[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			g_aKeyStatePress[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		g_pDevKeyboard->Acquire();		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=========================================================================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyStatePress[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=========================================================================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �L�[�{�[�h�̓��͏��(�����[�X���)���擾
//=========================================================================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �}�E�X�̏�����
//=========================================================================================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	// �����[�h��ݒ�i���Βl���[�h�ɐݒ�j
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;
	//diprop.dwData = DIPROPAXISMODE_ABS; // ��Βl���[�h�̏ꍇ
	if (FAILED(g_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return E_FAIL;
	}

	// �}�E�X�ւ̃A�N�Z�X�����l��(���͐���J�n)
	g_pDevMouse->Acquire();

	return S_OK;
}

//=========================================================================================================================
// �}�E�X�̍X�V����
//=========================================================================================================================
void UpdateMouse(void)
{
	int nCntMouse;

	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(g_MouseState), &g_MouseState)))
	{
		for (nCntMouse = 0; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
		{
			g_aMouseStateRelease.rgbButtons[nCntMouse] = (g_aMouseStatePress.rgbButtons[nCntMouse] ^ g_MouseState.rgbButtons[nCntMouse]) & g_aMouseStatePress.rgbButtons[nCntMouse];
			g_aMouseStateTrigger.rgbButtons[nCntMouse] = (g_aMouseStatePress.rgbButtons[nCntMouse] ^ g_MouseState.rgbButtons[nCntMouse]) & g_MouseState.rgbButtons[nCntMouse];
			g_aMouseStatePress.rgbButtons[nCntMouse] = g_MouseState.rgbButtons[nCntMouse];
		}
	}
	else
	{
		g_pDevMouse->Acquire();
	}
}

//=========================================================================================================================
// �}�E�X�̓��͏��(�v���X���)���擾
//=========================================================================================================================
bool GetMousePress(int nKey)
{
	return (g_aMouseStatePress.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �}�E�X�̓��͏��(�g���K�[���)���擾
//=========================================================================================================================
bool GetMouseTrigger(int nKey)
{
	return (g_aMouseStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �}�E�X�̓��͏��(�����[�X���)���擾
//=========================================================================================================================
bool GetMouseRelease(int nKey)
{
	return (g_aMouseStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
}

//=========================================================================================================================
// �}�E�X�̓��͏��(�|�C���^�[)���擾
//=========================================================================================================================
DIMOUSESTATE2 GetMousePointer(void)
{
	return g_MouseState;
}

//=========================================================================================================================
// �W���C�X�e�B�b�N�̏�����
//=========================================================================================================================
HRESULT InitJoystick(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	// 
	if (FAILED(g_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoysticksCallback, NULL, DIEDFL_ATTACHEDONLY)))
	{
		return E_FAIL;
	}

	if (g_pDevJoystick != NULL)
	{
		// �f�[�^�t�H�[�}�b�g��ݒ�
		if (FAILED(g_pDevJoystick->SetDataFormat(&c_dfDIJoystick)))
		{
			return E_FAIL;
		}

		// �������[�h��ݒ�
		if (FAILED(g_pDevJoystick->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
		{
			return E_FAIL;
		}

		// 
		g_pDevCaps.dwSize = sizeof(DIDEVCAPS);

		// �f�o�C�X�̔\�͂��擾
		if (FAILED(g_pDevJoystick->GetCapabilities(&g_pDevCaps)))
		{
			return E_FAIL;
		}

		// �\���L�[�͈͓̔����w��
		if (FAILED(g_pDevJoystick->EnumObjects(EnumAxesCallback, (VOID*)hWnd, DIDFT_AXIS)))
		{
			return E_FAIL;
		}

		// �f�o�C�X����f�[�^���擾
		g_pDevJoystick->Acquire();
	}
	else
	{
		g_aStickState.rgdwPOV[0] = 9999;
		g_bUseJoycon = true;
	}

	return S_OK;
}

//=========================================================================================================================
// �W���C�X�e�B�b�N�̍X�V����
//=========================================================================================================================
void UpdateJoystick(void)
{
	if (g_bUseJoycon != true)
	{
		DIJOYSTATE aButtonState;
		int nCntButton;

		g_pDevJoystick->Poll();

		if (SUCCEEDED(g_pDevJoystick->GetDeviceState(sizeof(aButtonState), &aButtonState)))
		{
			for (nCntButton = 0; nCntButton < NUM_BUTTON_MAX; nCntButton++)
			{
				g_aButtonStateRelease.rgbButtons[nCntButton] = (g_aButtonStatePress.rgbButtons[nCntButton] ^ aButtonState.rgbButtons[nCntButton]) & g_aButtonStatePress.rgbButtons[nCntButton];
				g_aButtonStateTrigger.rgbButtons[nCntButton] = (g_aButtonStatePress.rgbButtons[nCntButton] ^ aButtonState.rgbButtons[nCntButton]) & aButtonState.rgbButtons[nCntButton];
				g_aButtonStatePress.rgbButtons[nCntButton] = aButtonState.rgbButtons[nCntButton];
			}

			g_aButtonStateRelease.rgdwPOV[0] = (g_aButtonStatePress.rgdwPOV[0] ^ aButtonState.rgdwPOV[0]) & g_aButtonStatePress.rgdwPOV[0];
			g_aButtonStateTrigger.rgdwPOV[0] = (g_aButtonStatePress.rgdwPOV[0] ^ aButtonState.rgdwPOV[0]) & aButtonState.rgdwPOV[0];
			g_aButtonStatePress.rgdwPOV[0] = aButtonState.rgdwPOV[0];
		}
		else
		{
			g_pDevJoystick->Acquire();
		}
	}
}

//------------------------------------------------------------------------------
//    Joysticks Callback.
//------------------------------------------------------------------------------
BOOL CALLBACK EnumJoysticksCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext)
{
	if (FAILED(g_pInput->CreateDevice(pdidInstance->guidInstance, &g_pDevJoystick, NULL))) return DIENUM_CONTINUE;

	return DIENUM_STOP;
}

//------------------------------------------------------------------------------
//    Axes Callback.
//------------------------------------------------------------------------------
BOOL CALLBACK EnumAxesCallback(const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext)
{
	DIPROPRANGE diprg;

	diprg.diph.dwSize = sizeof(DIPROPRANGE);
	diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	diprg.diph.dwHow = DIPH_BYID;
	diprg.diph.dwObj = pdidoi->dwType;
	diprg.lMin = 0 - 1000;		// �W���C�X�e�B�b�N�̏\���L�[�̍ŏ��l�i��A���j
	diprg.lMax = 0 + 1000;		// �W���C�X�e�B�b�N�̏\���L�[�̍ő�l�i���A�E�j

	if (FAILED(g_pDevJoystick->SetProperty(DIPROP_RANGE, &diprg.diph))) return DIENUM_STOP;

	return DIENUM_CONTINUE;
}

//=========================================================================================================================
// �{�^���̓��͏��(�v���X���)���擾
//=========================================================================================================================
bool GetButtonPress(int nKey)
{
	if (g_bUseJoycon != true)
	{
		return (g_aButtonStatePress.rgbButtons[nKey] & 0x80) ? true : false;
	}
	else
	{
		return 0;
	}
}

//=========================================================================================================================
// �{�^���̓��͏��(�g���K�[���)���擾
//=========================================================================================================================
bool GetButtonTrigger(int nKey)
{
	if (g_bUseJoycon != true)
	{
		return (g_aButtonStateTrigger.rgbButtons[nKey] & 0x80) ? true : false;
	}
	else
	{
		return 0;
	}
}

//=========================================================================================================================
// �{�^���̓��͏��(�����[�X���)���擾
//=========================================================================================================================
bool GetButtonRelease(int nKey)
{
	if (g_bUseJoycon != true)
	{
		return (g_aButtonStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
	}
	else
	{
		return 0;
	}
}

//=========================================================================================================================
// �\���L�[�̓��͏��(�v���X���)���擾
//=========================================================================================================================
bool GetCrossPress(int nKey)
{
	if (g_bUseJoycon != true)
	{
		return (g_aButtonStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
	}
	else
	{
		return 0;
	}
}

//=========================================================================================================================
// �\���L�[�̓��͏��(�g���K�[���)���擾
//=========================================================================================================================
bool GetCrossTrigger(int nKey)
{
	if (g_bUseJoycon != true)
	{
		return (g_aButtonStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
	}
	else
	{
		return 0;
	}
}

//=========================================================================================================================
// �\���L�[�̓��͏��(�����[�X���)���擾
//=========================================================================================================================
bool GetCrossRelease(int nKey)
{
	if (g_bUseJoycon != true)
	{
		return (g_aButtonStateRelease.rgbButtons[nKey] & 0x80) ? true : false;
	}
	else
	{
		return 0;
	}
}

//=========================================================================================================================
// �W���C�R���̓��͏��(�A�i���O�X�e�B�b�N)���擾
//=========================================================================================================================
DIJOYSTATE GetStick(void)
{
	if (g_bUseJoycon != true)
	{
		g_pDevJoystick->GetDeviceState(sizeof(DIJOYSTATE), &g_aStickState);

		return g_aStickState;
	}
	else
	{
		return g_aStickState;
	}
}

//=========================================================================================================================
// ���͂̏I������
//=========================================================================================================================
void UninitInput(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// ���̓f�o�C�X(�}�E�X)�̊J��
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();	// �}�E�X�ւ̃A�N�Z�X�������
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	// ���̓f�o�C�X(�W���C�X�e�B�b�N)�̊J��
	if (g_pDevJoystick != NULL)
	{
		g_pDevJoystick->Unacquire();	// �W���C�X�e�B�b�N�ւ̃A�N�Z�X�������
		g_pDevJoystick->Release();
		g_pDevJoystick = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}