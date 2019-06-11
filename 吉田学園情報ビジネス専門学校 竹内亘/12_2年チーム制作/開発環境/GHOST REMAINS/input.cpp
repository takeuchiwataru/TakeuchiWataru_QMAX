//=============================================================================
//
// ���͏��� [input.cpp]
// Author :Ryo Sugimoto
//
//=============================================================================
#include "input.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
LPDIRECTINPUT8	CInput::m_pInput = NULL;		//DIRECTINPUT�I�u�W�F�N�g�ւ̃|�C���^
int CInputJoyPad::m_nNumPad = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInput::CInput()
{
	m_pDevice = NULL;
}
//=============================================================================
// �f�X�X�g���N�^
//=============================================================================
CInput::~CInput() {}
//=============================================================================
// ����������
//=============================================================================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pInput == NULL)
	{// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8,
			(void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CInput::Uninit(void)
{
	if (m_pInput != NULL)
	{// DirectInput�I�u�W�F�N�g�̊J��
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);
	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard,
		&m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if(FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if(FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	int *nQuick = GetTrigger();
	int nCntKey;
	for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		nQuick[nCntKey] = 0;
	}
	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	if (m_pDevice != NULL)
	{// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState),
		&aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			//m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateOld[nCntKey] = m_aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�{�[�h���͏��ۑ�
			//g_aKeyStateTrigger[nCntKey] = ((g_aKeyState[nCntKey] + 1) * aKeyState[nCntKey]) % 2;
		}
	}
	else
	{
		m_pDevice->Acquire();	//�L�[�{�[�h�ւ̃A�N�Z�X���l��
	}
}
//=============================================================================
// �L�[�{�[�h�̓��͏������ɂ��炷
//=============================================================================
void CInputKeyboard::Skip(void)
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aKeyStateOld[nCntKey] = m_aKeyState[nCntKey];
		m_aKeyState[nCntKey] = false;	//�L�[�{�[�h���͏��ۑ�
	}
}

//=============================================================================
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{	//�L�[�{�[�h�̓��͏��(�v���X���)���l��
		return(m_aKeyState[nKey] & 0x080) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(1F�O�̃v���X���)���擾
//=============================================================================
bool  CInputKeyboard::GetPressOld(int nKey)
{//�L�[�{�[�h�̓��͏��(1F�O�̃v���X���)���l��
	return(m_aKeyStateOld[nKey] & 0x080) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{	//�L�[�{�[�h�̓��͏��(�v���X���)���l��
	if (GetPress(nKey) && !GetPressOld(nKey)) { return true; }
	return false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{	//�L�[�{�[�h�̓��͏��(�v���X���)���l��
	if (!GetPress(nKey) && GetPressOld(nKey)) { return true; }
	return false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(Quick���)���擾
//=============================================================================
bool CInputKeyboard::GetQuick(int nKey, bool bUse)
{
	static int nTime = 0;				//�A�����͐����p
	int nCntKeyboard;
	bool bQuick = false;

	int *nQuick = GetTrigger();
	if (!bUse)
	{//�J�E���g�����͊m�F
		nTime--;
		for (nCntKeyboard = 0; nCntKeyboard < NUM_KEY_MAX; nCntKeyboard++)
		{//���Ԍo�ߗp
			nQuick[nCntKeyboard]--;
		}
	}
	else
	{
		if (GetTrigger(nKey))
		{//Trigger���͊m�F
			if (nQuick[nKey] > 0 && nTime < 0)
			{//2�����
				nQuick[nKey] = 0;
				bQuick = true;
				nTime = 35;	//�A�����͐��� 35F
			}
			else
			{//1�x��
				nQuick[nKey] = 20;
				bQuick = false;
			}
		}
	}

	return bQuick;
}
//=============================================================================
// �_�b�V������
//=============================================================================
bool CInputKeyboard::GetRun(int nKey, bool bRun)
{//�L�[�{�[�h�̓��͏��(�v���X���)���l��
	int *nQuick = GetTrigger();

	if (GetTrigger(nKey) || bRun)
	{//Trigger���͊m�F
		if (bRun == true)
		{
			nQuick[nKey] = 0;
			if (GetPress(nKey) == true)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (nQuick[nKey] > 0) { return true; }
			nQuick[nKey] = 15;
		}
	}
	return false;
}
//=========================================================================================================//
// * �v���C���[�̏��������
//=========================================================================================================//
int *CInputKeyboard::GetTrigger(void)
{
	static int nQuick[NUM_KEY_MAX];		//�S�ẴL�[���擾�̂���

	return &nQuick[0];
}
//=============================================================================
// �_�b�V������
//=============================================================================
bool CInputKeyboard::GetTPress(int nKey)
{
	int *nQuick = GetTrigger();

	if (nQuick[nKey] > 30 && nQuick[nKey] % 3 == 0)
	{//30F�ȏ㉟���Ă���
		return GetPress(nKey);
	}
	else if(nQuick[nKey] <= 30)
	{
		return GetTrigger(nKey);
	}

	return false;
}
//=============================================================================
// �J�E���g
//=============================================================================
void CInputKeyboard::GetCount(void)
{
	int *nQuick = GetTrigger();
	for (int nCount = 0; nCount < NUM_KEY_MAX; nCount++)
	{
		if(GetPress(nCount)){ nQuick[nCount]++; }
		else { nQuick[nCount] = 0; }
	}
}

//=============================================================================
// �W���C�p�b�h�N���X�̃R���X�g���N�^
//=============================================================================
CInputJoyPad::CInputJoyPad()
{
	m_abConnection = false;
	m_nID = m_nNumPad;
	m_nNumPad++;
}

//=============================================================================
// �W���C�p�b�h�N���X�̃f�X�g���N�^
//=============================================================================
CInputJoyPad::~CInputJoyPad()
{

}
//=============================================================================
// �W���C�p�b�h�N���X�̐ڑ����菈��
//=============================================================================
bool CInputJoyPad::Connect(void)
{
	DWORD dwResult;

	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(m_nID, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂�", "", MB_OK );
		// �f�b�h�]�[���̐ݒ�
		if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbLX = 0;
			state.Gamepad.sThumbLY = 0;
		}

		if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbRX = 0;
			state.Gamepad.sThumbRY = 0;
		}

		m_abConnection = true;
	}
	else
	{
		//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂���", "", MB_OK);
		m_abConnection = false;
	}

	return m_abConnection;
}
//=============================================================================
// �W���C�p�b�h�N���X�̏���������
//=============================================================================
void CInputJoyPad::Init(void)
{
	DWORD dwResult;

	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	dwResult = XInputGetState(m_nID, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂�", "", MB_OK );
		// �f�b�h�]�[���̐ݒ�
		if ((state.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
				state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbLX = 0;
			state.Gamepad.sThumbLY = 0;
		}

		if ((state.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
			(state.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
				state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
		{
			state.Gamepad.sThumbRX = 0;
			state.Gamepad.sThumbRY = 0;
		}

		m_abConnection = true;
	}
	else
	{
		//MessageBox(0, "�R���g���[���[���ڑ�����Ă��܂���", "", MB_OK);
		m_abConnection = false;
	}

	//���͏��̏�����
	for (int nCntButton = 0; nCntButton < JOYPAD_MAX_KEY; nCntButton++)
	{//�{�^���̏�����
		m_bButtonOld[nCntButton] = false;
		m_bButton[nCntButton] = false;
	}
	m_nPress[LEFT_STICK] = 0; m_nPress[RIGHT_STICK] = 0;
	m_fStickAngle[LEFT_STICK] = 99.9f; m_fStickAngle[RIGHT_STICK] = 99.9f;
}

//=============================================================================
// �W���C�p�b�h�N���X�̏I������
//=============================================================================
void CInputJoyPad::Uninit(void)
{
	m_nNumPad--;
	XInputEnable(false);
}

//=============================================================================
// �W���C�p�b�h�N���X�̍X�V����
//=============================================================================
void CInputJoyPad::Update(void)
{
	if(Connect())
	{//�q�����Ă����
		// �W���C�p�b�h���̎擾
		XINPUT_STATE state;

		XInputGetState(m_nID, &state);
		for (int nCntButton = 0; nCntButton < JOYPAD_MAX_KEY; nCntButton++)
		{
			m_bButtonOld[nCntButton] = m_bButton[nCntButton];
			m_bButton[nCntButton] = false;
		}
		//�{�^��
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)		{ m_bButton[0] = true;   m_nPress[0]++; }  else { m_nPress[0] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)		{ m_bButton[1] = true;   m_nPress[1]++; }  else { m_nPress[1] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)		{ m_bButton[2] = true;   m_nPress[2]++; }  else { m_nPress[2] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)		{ m_bButton[3] = true;   m_nPress[3]++; }  else { m_nPress[3] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)			{ m_bButton[4] = true;   m_nPress[4]++; }  else { m_nPress[4] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)			{ m_bButton[5] = true;   m_nPress[5]++; }  else { m_nPress[5] = 0; }
		if (state.Gamepad.bLeftTrigger > 0)							{ m_bButton[6] = true;   m_nPress[6]++; }  else { m_nPress[6] = 0; }
		if (state.Gamepad.bRightTrigger > 0)						{ m_bButton[7] = true;   m_nPress[7]++; }  else { m_nPress[7] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)	{ m_bButton[8] = true;   m_nPress[8]++; }  else { m_nPress[8] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) { m_bButton[9] = true;   m_nPress[9]++; }  else { m_nPress[9] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)				{ m_bButton[10] = true;  m_nPress[10]++; } else { m_nPress[10] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)				{ m_bButton[11] = true;  m_nPress[11]++; } else { m_nPress[11] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)				{ m_bButton[12] = true;  m_nPress[12]++; } else { m_nPress[12] = 0; }
		if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)				{ m_bButton[13] = true;  m_nPress[13]++; } else { m_nPress[13] = 0; }
		//L�X�e�B�b�N
		if (state.Gamepad.sThumbLX > 10)							{ m_bButton[14] = true;  m_nPress[14]++; } else { m_nPress[14] = 0; }
		if (state.Gamepad.sThumbLX < -10)							{ m_bButton[15] = true;  m_nPress[15]++; } else { m_nPress[15] = 0; }
		if (state.Gamepad.sThumbLY > 10)							{ m_bButton[16] = true;  m_nPress[16]++; } else { m_nPress[16] = 0; }
		if (state.Gamepad.sThumbLY < -10)							{ m_bButton[17] = true;  m_nPress[17]++; } else { m_nPress[17] = 0; }
		//R�X�e�B�b�N
		if (state.Gamepad.sThumbRX > 10)							{ m_bButton[18] = true;  m_nPress[18]++; } else { m_nPress[18] = 0; }
		if (state.Gamepad.sThumbRX < -10)							{ m_bButton[19] = true;  m_nPress[19]++; } else { m_nPress[19] = 0; }
		if (state.Gamepad.sThumbRY > 10)							{ m_bButton[20] = true;  m_nPress[20]++; } else { m_nPress[20] = 0; }
		if (state.Gamepad.sThumbRY < -10)							{ m_bButton[21] = true;  m_nPress[21]++; } else { m_nPress[21] = 0; }

		m_nStickX[0] = state.Gamepad.sThumbLX;
		m_nStickX[1] = state.Gamepad.sThumbRX;
		m_nStickY[0] = state.Gamepad.sThumbLY;
		m_nStickY[1] = state.Gamepad.sThumbRY;

		m_fStickAngle[LEFT_STICK] = atan2f(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY);
		m_fStickAngle[RIGHT_STICK] = atan2f(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY);
	}
}
//=============================================================================
// �W���C�p�b�h�@�S�{�^���g���K�[����
//=============================================================================
bool CInputJoyPad::GetAllTrigger(void)
{
	for (int nCount = 0; nCount < INPUT_MAX; nCount++)
	{
		if ((m_bButtonOld[nCount] ? false : (m_bButton[nCount] ? true : false)))
		{
			return true;
		}
	}
	return false;
}