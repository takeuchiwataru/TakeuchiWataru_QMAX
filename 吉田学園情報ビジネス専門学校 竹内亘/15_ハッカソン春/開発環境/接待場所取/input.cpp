//---------------------------------------------------------------------
//	���͏���(input.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "input.h"

//--------------------------------------------
//�}�N���錾
//--------------------------------------------
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


//*****************************************************************************

//			�R���g���[���[�N���X

//*****************************************************************************
//=============================================================================
//�R���g���[���[�N���X �R���X�g���N�^
//=============================================================================
CInputJoypad::CInputJoypad()
{
	//�L�[�����N���A
	for (int nCnt = 0; nCnt < NUM_BUTTON_MAX; nCnt++)
	{
		m_aKeyState[nCnt] = 0;
		m_aKeyStateTrigger[nCnt] = 0;
	}
}

//=============================================================================
//�R���g���[���[�N���X �f�X�g���N�^
//=============================================================================
CInputJoypad::~CInputJoypad()
{
}

//=============================================================================
// �R���g���[���[�N���X������
//=============================================================================
HRESULT CInputJoypad::Init(HINSTANCE hInstance, HWND hWnd)
{
	//HWND = �E�B���h�E���A�N�e�B�u�̎��ɂ���
	//���������Ă���
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X(�R���g���[���[)�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_Joystick,
		&m_pDevice,
		NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIJoystick)))
	{
		return E_FAIL;
	}
	// �������[�h��ݒ�	 *���͂��Ƃ���Ȃ�������ς��Ȃ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �R���g���[���[�̃A�N�Z�X�����l��(���͐���J�n)
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
		//X��
		diprg.diph.dwObj = DIJOFS_X;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		//Y��
		diprg.diph.dwObj = DIJOFS_Y;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		//Z��
		diprg.diph.dwObj = DIJOFS_Z;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �E�A�i���O�X�e�B�b�N
		//RX��
		diprg.diph.dwObj = DIJOFS_RX;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		//RY��
		diprg.diph.dwObj = DIJOFS_RY;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
		//RZ��
		diprg.diph.dwObj = DIJOFS_RZ;
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �\���L�[(���0�x�Ƃ����v���Ɋp�x * 100)
		diprg.diph.dwObj = DIJOFS_POV(0);
		m_pDevice->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �W���C�X�e�B�b�N�ւ̃A�N�Z�X�����l��(���͐���J�n)
		m_pDevice->Acquire();
	}

	return S_OK;
}

//=============================================================================
// �R���g���[���[�N���X�I������
//=============================================================================
void CInputJoypad::Uninit(void)
{
	// ���̓f�o�C�X(�R���g���[���[)�̊J��
	CInput::Uninit();

	//������Ă��Ȃ������Ƃ��ɏ���
	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//=============================================================================
// �R���g���[���[�N���X�X�V����
//=============================================================================
void CInputJoypad::Update(void)
{
	DIJOYSTATE dijs;

	if (m_pDevice != NULL)
	{
		m_pDevice->Poll();

		if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(dijs), &dijs)))
		{
			// ���̓f�o�C�X����f�[�^(��)���擾
			m_LeftAxizX = (float)dijs.lX;
			m_LeftAxizY = (float)dijs.lY;
			m_RightAxizX = (float)dijs.lZ;
			m_RightAxizY = (float)dijs.lRz;
			//���X�e�B�b�N�����ɓ|���ꂽ
			if (m_LeftAxizY > 100)
			{
				dijs.rgbButtons[STICK_L_DOWN] = 0x80;
			}
			//���X�e�B�b�N����ɓ|���ꂽ
			if (m_LeftAxizY < -100)
			{
				dijs.rgbButtons[STICK_L_UP] = 0x80;
			}
			//���X�e�B�b�N���E�ɓ|���ꂽ
			if (m_LeftAxizX > 100)
			{
				dijs.rgbButtons[STICK_L_RIGHT] = 0x80;
			}
			//���X�e�B�b�N�����ɓ|���ꂽ
			if (m_LeftAxizX < -100)
			{
				dijs.rgbButtons[STICK_L_LEFT] = 0x80;
			}
			//�E�X�e�B�b�N����ɓ|���ꂽ
			if (m_LeftAxizY > 100)
			{
				dijs.rgbButtons[STICK_R_UP] = 0x80;
			}
			//�E�X�e�B�b�N�����ɓ|���ꂽ
			if (m_LeftAxizY < -100)
			{
				dijs.rgbButtons[STICK_R_DOWN] = 0x80;
			}
			//�E�X�e�B�b�N���E�ɓ|���ꂽ
			if (m_LeftAxizX > 100)
			{
				dijs.rgbButtons[STICK_R_RIGHT] = 0x80;
			}
			//�E�X�e�B�b�N�����ɓ|���ꂽ
			if (m_LeftAxizX < -100)
			{
				dijs.rgbButtons[STICK_R_LEFT] = 0x80;
			}
			//�\���L�[����ɓ|���ꂽ
			if (dijs.rgdwPOV[0] == 0)
			{
				dijs.rgbButtons[POV_UP] = 0x80;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			//�\���L�[�����ɓ|���ꂽ
			if (dijs.rgdwPOV[0] == 18000)
			{
				dijs.rgbButtons[POV_DOWN] = 0x80;
				dijs.rgdwPOV[0] /= 100;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			//�\���L�[���E�ɓ|���ꂽ
			if (dijs.rgdwPOV[0] == 9000)
			{
				dijs.rgbButtons[POV_RIGHT] = 0x80;
				dijs.rgdwPOV[0] /= 100;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			//�\���L�[�����ɓ|���ꂽ
			if (dijs.rgdwPOV[0] == 27000)
			{
				dijs.rgbButtons[POV_LEFT] = 0x80;
				dijs.rgdwPOV[0] /= 100;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}


			//�\���L�[���E��ɓ|���ꂽ
			if (dijs.rgdwPOV[0] == 4500)
			{
				dijs.rgbButtons[POV_UP_RIGHT] = 0x80;
				dijs.rgdwPOV[0] /= 100;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			//�\���L�[���E���ɓ|���ꂽ
			if (dijs.rgdwPOV[0] == 13500)
			{
				dijs.rgbButtons[POV_DOWN_RIGHT] = 0x80;
				dijs.rgdwPOV[0] /= 100;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			//�\���L�[�������ɓ|���ꂽ
			if (dijs.rgdwPOV[0] == 22500)
			{
				dijs.rgbButtons[POV_DOWN_LEFT] = 0x80;
				dijs.rgdwPOV[0] /= 100;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}
			//�\���L�[�������ɓ|���ꂽ
			if (dijs.rgdwPOV[0] == 31500)
			{
				dijs.rgbButtons[POV_UP_LEFT] = 0x80;
				dijs.rgdwPOV[0] /= 100;
				m_Radian = D3DXToRadian(dijs.rgdwPOV[0]);
			}

			for (int nCntKey = 0; nCntKey < NUM_BUTTON_MAX; nCntKey++)
			{
				m_aKeyStateRelease[nCntKey] = (m_aKeyState[nCntKey] ^ dijs.rgbButtons[nCntKey]) & m_aKeyState[nCntKey];
				m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ dijs.rgbButtons[nCntKey]) & dijs.rgbButtons[nCntKey];
				m_aKeyState[nCntKey] = dijs.rgbButtons[nCntKey];
			}
		}
		else
		{
			// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
			m_pDevice->Acquire();
		}
	}
}

//=============================================================================
// �R���g���[���[�N���X���͏��(�v���X���)���擾
//=============================================================================
bool CInputJoypad::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �R���g���[���[�N���X���͏��(�g���K�[���)���擾
//=============================================================================
bool CInputJoypad::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
//=============================================================================
// �R���g���[���[�N���X���͏��(�����[�X���)���擾
//=============================================================================
bool CInputJoypad::GetRelease(int nKey)
{
	return(m_aKeyStateRelease[nKey] & 0x80) ? true : false;
}

//=============================================================================
// �R���g���[���[�̓��͏��(�g���K�[���)���擾
//=============================================================================
bool CInputJoypad::GetAnyButton(int nNumber)
{
	if (nNumber == 0)
	{
		for (int nCnt = 0; nCnt < NUM_BUTTON_MAX; nCnt++)
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
// �R���g���[���[�̍��X�e�B�b�N�̌���
//=============================================================================
float CInputJoypad::GetLeftAxiz(void)
{
	float Axiz = atan2f(m_LeftAxizX, m_LeftAxizY);
	return Axiz;
}

//=============================================================================
// �R���g���[���[�̉E�X�e�B�b�N�̌������擾
//=============================================================================
float CInputJoypad::GetRightAxiz(void)
{
	float Axiz = atan2f(m_RightAxizX, m_RightAxizY);
	return Axiz;
}

//=============================================================================
// �R���g���[���[�� �\���L�[�擾
//=============================================================================
float CInputJoypad::GetRadian(void)
{
	return m_Radian;
}
