//=============================================================================
//
// ���͏��� [input.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX	     (256)	 // �L�[�̍ő吔
#define DI_JOY_I_INPUT   (1000)  // �X�e�B�b�N�̕������͎�t���s���͈�
#define REPEAT_FRAME     (20)    // ���s�[�g�����N�����n�߂�t���[�����̍��v
#define REPEAT_TRIGGER   (7)     // ���s�[�g�����N������t���[���̊Ԋu

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
BOOL PASCAL EnumJoyDeviceProc(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTINPUT8 g_pInput = NULL;                       // DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;           // ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevJoypad[MAX_JOYPAD] = {};   // ���̓f�o�C�X(�W���C�p�b�h)�ւ̃|�C���^
BYTE g_aKeyState[NUM_KEY_MAX];                        // �L�[�{�[�h�̓��͏��(�v���X���)
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];                 // �L�[�{�[�h�̓��͏��(�g���K�[���)
BYTE g_aKeyStateRelease[NUM_KEY_MAX];                 // �L�[�{�[�h�̓��͏��(�����[�X���)
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];                  // �L�[�{�[�h�̓��͏��(���s�[�g���)
BYTE g_aJoyState[MAX_JOYPAD][DIJS_BUTTON_MAX];        // �W���C�p�b�h�̓��͏��(�v���X���)
BYTE g_aJoyStateTrigger[MAX_JOYPAD][DIJS_BUTTON_MAX]; // �W���C�p�b�h�̓��͏��(�g���K�[���)
BYTE g_aJoyStateRelease[MAX_JOYPAD][DIJS_BUTTON_MAX]; // �W���C�p�b�h�̓��͏��(�����[�X���)
BYTE g_aJoyStateRepeat[MAX_JOYPAD][DIJS_BUTTON_MAX];  // �W���C�p�b�h�̓��͏��(���s�[�g���)
int  g_aKeyboardCounter[NUM_KEY_MAX];                 // �L�[�{�[�h�����͂���Ă�Ԃ𐔂���J�E���^�[
int  g_aJoyCounter[MAX_JOYPAD][DIJS_BUTTON_MAX];      // �W���C�p�b�h�����͂���Ă�Ԃ𐔂���J�E���^�[

int   g_ConnectPad;                          // �ڑ����ꂽ�p�b�h�̐�
float g_Radian[MAX_JOYPAD];                  // �\���L�[�̃��W�A�����i�[����
float g_Xziku[MAX_JOYPAD];                   // ���A�i���O�X�e�B�b�N��X�����i�[����
float g_Yziku[MAX_JOYPAD];                   // ���A�i���O�X�e�B�b�N��Y�����i�[����

//=============================================================================
// ����������
//=============================================================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//======================================
	// �L�[�{�[�h����������
	//======================================
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

	//======================================
	// �W���C�p�b�h����������
	//======================================
	if (FAILED(g_pInput->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyDeviceProc, NULL, DIEDFL_ATTACHEDONLY)))
	{// �����̃f�o�C�X��񋓂���
		return E_FAIL;
	}

	for (int nCntInput = 0; nCntInput < NUM_KEY_MAX; nCntInput++)
	{// �L�[�{�[�h�̃{�^���̐������J��Ԃ�
		g_aKeyboardCounter[nCntInput] = 0;   // �J�E���^�[��������
	}
	for (int nCntPad = 0; nCntPad < g_ConnectPad; nCntPad++)
	{// �ڑ����ꂽ�p�b�h�̐������J��Ԃ�
		for (int nCntInput = 0; nCntInput < DIJS_BUTTON_MAX; nCntInput++)
		{// �W���C�p�b�h�̃{�^���̐������J��Ԃ�
			g_aJoyCounter[nCntPad][nCntInput] = 0;        // �J�E���^�[��������
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitInput(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire(); // �L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// ���̓f�o�C�X(�W���C�p�b�h)�̊J��
	for (int nCntPad = 0; nCntPad < 2; nCntPad++)
	{
		if (g_pDevJoypad[nCntPad] != NULL)
		{
			g_pDevJoypad[nCntPad]->Unacquire();   // �W���C�p�b�h�ւ̃A�N�Z�X�������
			g_pDevJoypad[nCntPad]->Release();
			g_pDevJoypad[nCntPad] = NULL;
		}
	}
	// DirectInput�I�u�W�F�N�g�̊J��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateInput(void)
{
	//======================================
	// �L�[�{�[�h�X�V����
	//======================================
	BYTE aKeyState[NUM_KEY_MAX]; // �L�[�{�[�h�̓��͏��

								 // ���̓f�o�C�X(�L�[�{�[�h)����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];   // �L�[�{�[�h�̓��͏��(�g���K�[���)�ۑ�
			g_aKeyStateRelease[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey]; // �L�[�{�[�h�̓��͏��(�����[�X���)�ۑ�
			if (aKeyState[nCntKey] == 0x80)
			{// �L�[�{�[�h�����͂���Ă���
				g_aKeyboardCounter[nCntKey]++;    // �J�E���^�[��i�߂�
				if (g_aKeyboardCounter[nCntKey] >= REPEAT_FRAME)
				{// 20�t���[�����L�[��������Ă���
					if (g_aKeyboardCounter[nCntKey] % REPEAT_TRIGGER == 0)
					{// 3�t���[������
						g_aKeyStateRepeat[nCntKey] = 0x80;   // �L�[�{�[�h�̓��͏��(���s�[�g���)���N��
					}
					else
					{// ����ȊO�̃t���[��
						g_aKeyStateRepeat[nCntKey] = 0;      // �L�[�{�[�h�̓��͏��(���s�[�g���)���ꎞ��~
					}
				}
			}
			else
			{// �L�[�{�[�h�����͂���Ă��Ȃ� 
				g_aKeyboardCounter[nCntKey] = 0;        // �J�E���^�[��߂�
				g_aKeyStateRepeat[nCntKey] = 0;         // �L�[�{�[�h�̓��͏��(���s�[�g���)���~
			}
			g_aKeyState[nCntKey] = aKeyState[nCntKey];  // �L�[�{�[�h�̓��͏��(�v���X���)�ۑ�
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); // �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}

	//======================================
	// �W���C�p�b�h�X�V����
	//======================================
	for (int nCntPad = 0; nCntPad < g_ConnectPad; nCntPad++)
	{// �p�b�h�̐������J��Ԃ�
		DIJOYSTATE dijs[MAX_JOYPAD];    // �W���C�p�b�h�̓��͏����i�[����
		if (g_pDevJoypad != NULL)
		{// �����ł���
		 // ���̓f�o�C�X(�W���C�p�b�h)����f�[�^���擾
			g_pDevJoypad[nCntPad]->Poll();
			if (SUCCEEDED(g_pDevJoypad[nCntPad]->GetDeviceState(sizeof(DIJOYSTATE), &dijs[nCntPad])))
			{
				g_Yziku[nCntPad] = 0.0f;
				g_Xziku[nCntPad] = 0.0f;

				g_Xziku[nCntPad] = (float)dijs[nCntPad].lX;
				g_Yziku[nCntPad] = (float)dijs[nCntPad].lY;

				//-----------------------------
				// ���A�i���O�X�e�B�b�N
				//-----------------------------
				if (dijs[nCntPad].lY <= -100)
				{// ���A�i���O�X�e�B�b�N����ɓ|���ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_10] = 0x80;
				}
				if (dijs[nCntPad].lY >= 100)
				{// ���A�i���O�X�e�B�b�N�����ɓ|���ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_11] = 0x80;
				}
				if (dijs[nCntPad].lX <= -100)
				{// ���A�i���O�X�e�B�b�N�����ɓ|���ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_13] = 0x80;
				}
				if (dijs[nCntPad].lX >= 100)
				{// ���A�i���O�X�e�B�b�N���E�ɓ|���ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_12] = 0x80;
				}

				//-----------------------------	
				// �E�A�i���O�X�e�B�b�N
				//-----------------------------
				if (dijs[nCntPad].lRz <= -100)
				{// �E�A�i���O�X�e�B�b�N����ɓ|���ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_14] = 0x80;
				}
				if (dijs[nCntPad].lRz >= 100)
				{// �E�A�i���O�X�e�B�b�N�����ɓ|���ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_15] = 0x80;
				}
				if (dijs[nCntPad].lZ <= -100)
				{// �E�A�i���O�X�e�B�b�N�����ɓ|���ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_17] = 0x80;
				}
				if (dijs[nCntPad].lZ >= 100)
				{// �E�A�i���O�X�e�B�b�N���E�ɓ|���ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_16] = 0x80;
				}

				//-----------------------------
				// �\���L�[
				//-----------------------------
				if (dijs[nCntPad].rgdwPOV[0] / 100 == 0)
				{// �\���L�[�̏オ�����ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_18] = 0x80;
					g_Radian[nCntPad] = D3DXToRadian(dijs[nCntPad].rgdwPOV[0]);
				}
				if (dijs[nCntPad].rgdwPOV[0] / 100 == 45)
				{// �\���L�[�̉E�オ�����ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_18] = 0x80;
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_20] = 0x80;
					g_Radian[nCntPad] = D3DXToRadian(dijs[nCntPad].rgdwPOV[0]);
				}
				if (dijs[nCntPad].rgdwPOV[0] / 100 == 90)
				{// �\���L�[�̉��������ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_20] = 0x80;
					g_Radian[nCntPad] = D3DXToRadian(dijs[nCntPad].rgdwPOV[0]);
				}
				if (dijs[nCntPad].rgdwPOV[0] / 100 == 135)
				{// �\���L�[�̉E���������ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_19] = 0x80;
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_20] = 0x80;
					g_Radian[nCntPad] = D3DXToRadian(dijs[nCntPad].rgdwPOV[0]);
				}
				if (dijs[nCntPad].rgdwPOV[0] / 100 == 180)
				{// �\���L�[�̉E�������ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_19] = 0x80;
					g_Radian[nCntPad] = D3DXToRadian(dijs[nCntPad].rgdwPOV[0]);
				}
				if (dijs[nCntPad].rgdwPOV[0] / 100 == 225)
				{// �\���L�[�̍����������ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_19] = 0x80;
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_21] = 0x80;
					g_Radian[nCntPad] = D3DXToRadian(dijs[nCntPad].rgdwPOV[0]);
				}
				if (dijs[nCntPad].rgdwPOV[0] / 100 == 270)
				{// �\���L�[�̍��������ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_21] = 0x80;
					g_Radian[nCntPad] = D3DXToRadian(dijs[nCntPad].rgdwPOV[0]);
				}
				if (dijs[nCntPad].rgdwPOV[0] / 100 == 315)
				{// �\���L�[�̍��オ�����ꂽ
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_18] = 0x80;
					dijs[nCntPad].rgbButtons[DIJS_BUTTON_21] = 0x80;
					g_Radian[nCntPad] = D3DXToRadian(dijs[nCntPad].rgdwPOV[0]);
				}

				for (int nCntJoyButton = 0; nCntJoyButton < DIJS_BUTTON_MAX; nCntJoyButton++)
				{// �W���C�p�b�h�̃{�^���̐������J��Ԃ�
					g_aJoyStateTrigger[nCntPad][nCntJoyButton] = (g_aJoyState[nCntPad][nCntJoyButton] ^ dijs[nCntPad].rgbButtons[nCntJoyButton]) & dijs[nCntPad].rgbButtons[nCntJoyButton];  // �W���C�p�b�h�̓��͏��(�g���K�[���)�ۑ�
					g_aJoyStateRelease[nCntPad][nCntJoyButton] = (g_aJoyState[nCntPad][nCntJoyButton] ^ dijs[nCntPad].rgbButtons[nCntJoyButton]) & g_aJoyState[nCntPad][nCntJoyButton];      // �W���C�p�b�h�̓��͏��(�����[�X���)�ۑ�
					if (dijs[nCntPad].rgbButtons[nCntJoyButton] == 0x80)
					{// �W���C�p�b�h�����͂���Ă���
						g_aJoyCounter[nCntPad][nCntJoyButton]++;    // �J�E���^�[��i�߂�
						if (g_aJoyCounter[nCntPad][nCntJoyButton] >= REPEAT_FRAME)
						{// 20�t���[�����L�[��������Ă���
							if (g_aJoyCounter[nCntPad][nCntJoyButton] % REPEAT_TRIGGER == 0)
							{// 3�t���[������
								g_aJoyStateRepeat[nCntPad][nCntJoyButton] = 0x80;   // �W���C�p�b�h�̓��͏��(���s�[�g���)���N��
							}
							else
							{// ����ȊO�̃t���[��
								g_aJoyStateRepeat[nCntPad][nCntJoyButton] = 0;     // �W���C�p�b�h�̓��͏��(���s�[�g���)���ꎞ��~
							}
						}
					}
					else
					{// �W���C�p�b�h�����͂���Ă��Ȃ� 
						g_aJoyCounter[nCntPad][nCntJoyButton] = 0;          // �J�E���^�[��߂�
						g_aJoyStateRepeat[nCntPad][nCntJoyButton] = 0;      // �W���C�p�b�h�̓��͏��(���s�[�g���)���~
					}
					g_aJoyState[nCntPad][nCntJoyButton] = dijs[nCntPad].rgbButtons[nCntJoyButton];   // �W���C�p�b�h�̓��͏��(�v���X���)�ۑ�
				}
			}
			else
			{
				g_pDevJoypad[nCntPad]->Acquire(); // �W���C�p�b�h�ւ̃A�N�Z�X�����l��
			}
		}
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�����[�X���)���擾
//=============================================================================
bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(���s�[�g���)���擾
//=============================================================================
bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool GetJoyPadPress(int nButton, int nIdxPad)
{
	return (g_aJoyState[nIdxPad][nButton] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool GetJoyPadTrigger(int nButton, int nIdxPad)
{
	return (g_aJoyStateTrigger[nIdxPad][nButton] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̓��͏��(�����[�X���)���擾
//=============================================================================
bool GetJoyPadRelease(int nButton, int nIdxPad)
{
	return (g_aJoyStateRelease[nIdxPad][nButton] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̓��͏��(���s�[�g���)���擾
//=============================================================================
bool GetJoyPadRepeat(int nButton, int nIdxPad)
{
	return (g_aJoyStateRepeat[nIdxPad][nButton] & 0x80) ? true : false;
}
//=============================================================================
// �W���C�p�b�h�̏\���L�[�̃��W�A�����擾
//=============================================================================
float GetJotPadRadian(int nIdxPad)
{
	return g_Radian[nIdxPad] / 100;
}
//=============================================================================
// �W���C�p�b�h�̍��A�i���O�X�e�B�b�N�̎����擾
//=============================================================================
float GetJotPadRightStick(int nIdxPad)
{
	// ���̊p�x�����߂�
	float Ziku = atan2f(g_Xziku[nIdxPad], g_Yziku[nIdxPad]);

	return Ziku;
}
//=============================================================================
// �񋓂��ꂽ�W���C�p�b�h�̕��f�o�C�X�𐶐�����
//=============================================================================
BOOL PASCAL EnumJoyDeviceProc(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	// ���̓f�o�C�X(�W���C�p�b�h)�̐���
	if (FAILED(g_pInput->CreateDevice(lpddi->guidInstance, &g_pDevJoypad[g_ConnectPad], NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevJoypad[g_ConnectPad]->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	//// �������[�h��ݒ�
	//if (FAILED(g_pDevJoypad[g_ConnectPad]->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	//{
	//	return E_FAIL;
	//}

	if (g_pDevJoypad[g_ConnectPad] != NULL)
	{// �����ł���
		DIPROPRANGE diprg;

		// ���̒l�͈̔͂�ݒ�
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin = -DI_JOY_I_INPUT;
		diprg.lMax = DI_JOY_I_INPUT;

		// ���̐ݒ�
		// ���A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_X;
		g_pDevJoypad[g_ConnectPad]->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		g_pDevJoypad[g_ConnectPad]->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		g_pDevJoypad[g_ConnectPad]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �E�A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_RX;
		g_pDevJoypad[g_ConnectPad]->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		g_pDevJoypad[g_ConnectPad]->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		g_pDevJoypad[g_ConnectPad]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �\���L�[(���0�x�Ƃ����v���Ɋp�x * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		g_pDevJoypad[g_ConnectPad]->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �W���C�p�b�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
		g_pDevJoypad[g_ConnectPad]->Acquire();

		g_ConnectPad++;    // �ڑ�����
	}

	// �ŏ���1�݂̂ŏI���
	//return DIENUM_STOP;

	// �����񋓂���
	return DIENUM_CONTINUE;
}