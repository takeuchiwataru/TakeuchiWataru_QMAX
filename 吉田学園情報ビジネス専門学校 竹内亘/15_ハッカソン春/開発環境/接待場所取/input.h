//=============================================================================
//
// ���͏��� [inout.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔
#define	NUM_BUTTON_MAX		(32)	// �L�[�̍ő吔

//*********************************************************************
//�C���v�b�g�N���X�̒�`
//*********************************************************************
//��{�N���X
class CInput
{
public:
	CInput();
	virtual ~CInput();
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit();
	virtual void Update() = 0;		//�h����ŕς��
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};
 //�h���N���X
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
	BYTE m_aKeyState[NUM_KEY_MAX];					//�L�[�{�[�h���͏��(�v���X)
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];			//�L�[�{�[�h���͏��(�g���K�[)
	BYTE m_aKeyStateRelease[NUM_KEY_MAX];			//�L�[�{�[�h���͏��(�����[�X)
};

//*********************************************************************
//�R���g���[���[�̒�`
//*********************************************************************
//�h���N���X
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
		POV_UP_RIGHT,	//�\���L�[�@�E��
		POV_UP_LEFT,	//�\���L�[�@����
		POV_DOWN_RIGHT,	//�\���L�[�@�E��
		POV_DOWN_LEFT,	//�\���L�[�@����
		POV_UP,			//�\���L�[�@��
		POV_DOWN,		//�\���L�[�@��
		POV_RIGHT,		//�\���L�[�@�E
		POV_LEFT,		//�\���L�[�@��
		STICK_L_UP,		//���X�e�B�b�N�@��
		STICK_L_DOWN,	//���X�e�B�b�N�@��
		STICK_L_RIGHT,	//���X�e�B�b�N�@�E
		STICK_L_LEFT,	//���X�e�B�b�N�@��
		STICK_R_UP,		//�E�X�e�B�b�N�@��
		STICK_R_DOWN,	//�E�X�e�B�b�N�@��
		STICK_R_RIGHT,	//�E�X�e�B�b�N�@�E
		STICK_R_LEFT,	//�E�X�e�B�b�N�@��
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
	BYTE m_aKeyState[NUM_BUTTON_MAX];					//�R���g���[���[�̓��͏��(�v���X)
	BYTE m_aKeyStateTrigger[NUM_BUTTON_MAX];			//�R���g���[���[�̓��͏��(�g���K�[)
	BYTE m_aKeyStateRelease[NUM_BUTTON_MAX];			//�R���g���[���[�̓��͏��(�����[�X)
	float m_LeftAxizX;								//����
	float m_LeftAxizY;								//����
	float m_RightAxizX;								//����
	float m_RightAxizY;								//����
	float m_Radian;									//
};

#endif