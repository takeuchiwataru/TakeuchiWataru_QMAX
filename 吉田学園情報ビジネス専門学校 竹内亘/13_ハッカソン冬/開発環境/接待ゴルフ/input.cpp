//---------------------------------------------------------------------
//	���͏���(input.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "input.h"

#define DI_JOY_I_INPUT (1000)
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
static CInput *m_pInput;
LPDIRECTINPUT8 CInput::m_pInput = NULL;

//--------------------------------------------
//�C���v�b�g�N���X �R���X�g���N�^
//--------------------------------------------
CInput::CInput()
{
	m_pDevice = NULL;
	m_pInput = NULL;
}

//--------------------------------------------
//�C���v�b�g�N���X �f�X�g���N�^
//--------------------------------------------
CInput::~CInput()
{
}

//--------------------------------------------
// �C���v�b�g�N���X������
//--------------------------------------------
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
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
// �C���v�b�g�N���X�I������
//--------------------------------------------
void CInput::Uninit(void)
{
	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}

	//������Ă��Ȃ������Ƃ��ɏ���
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}
//--------------------------------------------
// �C���v�b�g�N���X�X�V����
//--------------------------------------------
void CInput::Update(void)
{
}

//*****************************************************************************

//			�L�[�{�[�h�N���X

//*****************************************************************************
//=============================================================================
//�L�[�{�[�h�N���X �R���X�g���N�^
//=============================================================================
CInputKeyboard::CInputKeyboard()
{
	//�L�[�����N���A
	//m_aKeyState[NUM_KEY_MAX] = {};
	//m_aKeyStateTrigger[NUM_KEY_MAX] = {};
	for (int nCnt = 0; nCnt < NUM_KEY_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = 0;
		m_aKeyStateTrigger[nCnt] = 0;
	}
}

//=============================================================================
//�L�[�{�[�h�N���X �f�X�g���N�^
//=============================================================================
CInputKeyboard::~CInputKeyboard()
{
}

//=============================================================================
// �L�[�{�[�h�̏�����
//=============================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//���������Ă���
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard,
		&m_pDevice,
		NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevice->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CInputKeyboard::Uninit(void)
{
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	CInput::Uninit();
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];

	// ���̓f�o�C�X����f�[�^���擾
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
// �L�[�{�[�h�̓��͏��(�v���X���)���擾
//=============================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �L�[�{�[�h�̓��͏��(�����[�X���)���擾
//=============================================================================
bool CInputKeyboard::GetRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

HRESULT CDirectInput::Init(HINSTANCE hinstance, HWND hWnd)
{
	//����������
	CInput::Init(hinstance, hWnd);

	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	if (m_pDevice != NULL)
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
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �E�A�i���O�X�e�B�b�N
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// ?
		//diprg.diph.dwObj = DIJOFS_SLIDER(0);
		//g_pDevJoypad->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �\���L�[(���0�x�Ƃ����v���Ɋp�x * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �W���C�X�e�B�b�N�ւ̃A�N�Z�X�����l��(���͐���J�n)
		m_pDevice->Acquire();
	}

	return true;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void CDirectInput::Uninit(void)
{
	//�I������
	CInput::Uninit();

	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	//�L�[�{�[�h�̃A�h���X����j��
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}

//=============================================================================
// �W���C�p�b�h�̍X�V����
//=============================================================================
void CDirectInput::Update(void)
{
	DIJOYSTATE dJoystate;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		// ���̓f�o�C�X����f�[�^���擾
		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(dJoystate), &dJoystate)))
		{
			m_fLeftAxiz_X = (float)dJoystate.lX;
			m_fLeftAxiz_Y = (float)dJoystate.lY;
			m_fRightAxiz_X = (float)dJoystate.lZ;
			m_fRightAxiz_Y = (float)dJoystate.lRz;

			if (dJoystate.lX < -100 || dJoystate.lX > 100 || dJoystate.lY < -100 || dJoystate.lY > 100)
			{//���X�e�B�b�N��|������
				m_Stick[0] = 0x80;
			}
			else
			{//���X�e�B�b�N��|���ĂȂ���
				m_Stick[0] = 0;
			}

			if (dJoystate.lZ < -100 || dJoystate.lZ > 100 || dJoystate.lRz < -100 || dJoystate.lRz > 100)
			{//�E�X�e�B�b�N��|���Ă��鎞
				m_Stick[1] = 0x80;
			}
			else
			{//�E�X�e�B�b�N��|���ĂȂ���
				m_Stick[1] = 0;
			}

			if (dJoystate.rgdwPOV[0] / 100 == 0)
			{//��
				dJoystate.rgbButtons[DIJS_BUTTON_29] = 0x80;
				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 45)
			{//�E��
				dJoystate.rgbButtons[DIJS_BUTTON_29] = 0x80;
				dJoystate.rgbButtons[DIJS_BUTTON_30] = 0x80;

				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 90)
			{//�E
				dJoystate.rgbButtons[DIJS_BUTTON_30] = 0x80;
				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 135)
			{//�E��
				dJoystate.rgbButtons[DIJS_BUTTON_30] = 0x80;
				dJoystate.rgbButtons[DIJS_BUTTON_31] = 0x80;

				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 180)
			{//��
				dJoystate.rgbButtons[DIJS_BUTTON_31] = 0x80;

				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 225)
			{//����
				dJoystate.rgbButtons[DIJS_BUTTON_28] = 0x80;
				dJoystate.rgbButtons[DIJS_BUTTON_31] = 0x80;
				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 270)
			{//��
				dJoystate.rgbButtons[DIJS_BUTTON_28] = 0x80;
				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}
			if (dJoystate.rgdwPOV[0] / 100 == 315)
			{//����
				dJoystate.rgbButtons[DIJS_BUTTON_28] = 0x80;
				dJoystate.rgbButtons[DIJS_BUTTON_29] = 0x80;
				m_fRadian = D3DXToRadian(dJoystate.rgdwPOV[0]);
			}

			for (int nCntKey = 0; nCntKey < 32; nCntKey++)
			{
				//�g���K�[
				m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ dJoystate.rgbButtons[nCntKey]) & dJoystate.rgbButtons[nCntKey];	//�R���g���[���[���͏��ۑ�

																																		//�����[																														//g_aKeyStateRelase[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & g_aKeyState[nCntKey];	//�R���g���[���[���͏��ۑ�
																																		//�v���X
				m_aKeyState[nCntKey] = dJoystate.rgbButtons[nCntKey];   //�R���g���[���[���͏��
			}
		}
		else
		{
			m_pDevice->Acquire();
		}
	}
}

//=============================================================================
// �R���g���[���[�̓��͏��(�v���X���)���擾
//=============================================================================
bool CDirectInput::GetPress(int nButton)
{
	return(m_aKeyState[nButton] & 0x80) ? true : false;
}

//=============================================================================
// �R���g���[���[�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CDirectInput::GetTrigger(int nButton)
{
	return(m_aKeyStateTrigger[nButton] & 0x80) ? true : false;
}

//=============================================================================
// �R���g���[���[�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CDirectInput::GetStick(int nButton)
{
	return(m_Stick[nButton] & 0x80) ? true : false;
}

//=============================================================================
// �R���g���[���[�̓��͏��(�g���K�[���)���擾
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
// ���X�e�B�b�N�̊p�x���擾
//=============================================================================
float CDirectInput::GetLeftAxiz(void)
{
	//���X�e�B�b�N�̊p�x���擾
	float Axiz = atan2f(m_fLeftAxiz_X, m_fLeftAxiz_Y);

	return Axiz;
}

//=============================================================================
// �E�X�e�B�b�N�̊p�x���擾
//=============================================================================
float CDirectInput::GetRightAxiz(void)
{
	//�E�X�e�B�b�N�̊p�x
	float Axiz = atan2f(m_fRightAxiz_X, m_fRightAxiz_Y);

	return Axiz;
}

//=============================================================================
// �\���L�[�̊p�x���擾
//=============================================================================
float CDirectInput::GetRadian(void)
{
	float fRadian = m_fRadian / 100;
	return fRadian;
}