//=============================================================================
//
// ���͏��� [input.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
// �}�N���̒�`
//*****************************************************************************
#define JOYPAD_MAX			(2)		// �W���C�p�b�h�̐ڑ���
#define JOYPAD_MAX_BUTTON	(14)	// �W���C�p�b�h�̃{�^����
#define JOYPAD_MAX_STICK	(2)		// �W���C�p�b�h�̓��͌�
#define LEFT_STICK			(0)		// �W���C�p�b�h��L�X�e�B�b�N�̔ԍ�
#define RIGHT_STICK			(1)		// �W���C�p�b�h��R�X�e�B�b�N�̔ԍ�
#define JOYPAD_MAX_KEY		(JOYPAD_MAX_BUTTON + JOYPAD_MAX_STICK * 4)	// �W���C�p�b�h�̓��͌�
//*****************************************************************************
// �񋓂̒�`
//*****************************************************************************
typedef enum
{//���͏��
	INPUT_UP, INPUT_DOWN, INPUT_LEFT, INPUT_RIGHT,
	INPUT_START, INPUT_BACK,
	INPUT_L2, INPUT_R2, INPUT_L1, INPUT_R1,
	INPUT_A, INPUT_B, INPUT_X, INPUT_Y,
	INPUT_LS_R, INPUT_LS_L, INPUT_LS_U, INPUT_LS_D,
	INPUT_RS_R, INPUT_RS_L, INPUT_RS_U, INPUT_RS_D,
	INPUT_MAX
}JOY_INPUT;
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CInput
{
public:
#define	NUM_KEY_MAX			(256)			// �L�[�̍ő吔
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

protected://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static LPDIRECTINPUT8	m_pInput;				//DIRECTINPUT�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8	m_pDevice;	//���̓f�o�C�X�ւ̃L�[�{�[�h�̃|�C���^
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard() {};
	~CInputKeyboard() {};

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void Skip(void);
	bool GetPressOld(int nKey);
	bool GetPress(int nKey);

	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetQuick(int nKey, bool bUse);
	bool GetRun(int nKey, bool bRun);
	int *GetTrigger(void);
	bool GetTPress(int nKey);
	void GetCount(void);

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	BYTE					m_aKeyState[NUM_KEY_MAX];				//�L�[�{�[�h���͏��(�v���X���)
	BYTE					m_aKeyStateOld[NUM_KEY_MAX];				//�L�[�{�[�h���͏��(�v���X���)
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CInputJoyPad : public CInput
{
public:
	CInputJoyPad();
	~CInputJoyPad();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Skip(void);

	bool GetConnect(void)	 { return m_abConnection; };

	bool GetAllTrigger(void);
	bool GetPress(int input)	 { return m_bButton[input]; };
	bool GetTPress(int input) { if (m_nPress[input] < 30) { return GetTrigger(input); } else if (m_nPress[input] % 2 == 0) { return m_bButton[input]; } else { return false; } return false; };
	bool GetTrigger(int input) { return (m_bButtonOld[input] ? false : (m_bButton[input] ? true : false)); };
	bool GetRelease(int input) { return (m_bButtonOld[input] ? (m_bButton[input] ? false : true) : false); };
	float GetfStickAngle(int nStick) { return m_fStickAngle[nStick]; };
	int &GetnStickX(int nStick) { return m_nStickX[nStick]; };
	int &GetnStickY(int nStick) { return m_nStickY[nStick]; };

	bool GetStickDefeat(int nStick) 
	{
		int nPlus = nStick * 4; 
		if (m_bButton[INPUT_LS_R + nPlus] || m_bButton[INPUT_LS_L + nPlus] || m_bButton[INPUT_LS_U + nPlus] || m_bButton[INPUT_LS_D + nPlus]) { return true; }
		return false;
	};

private:
	bool Connect(void);

	static int m_nNumPad;					//�W���C�p�b�h�̑���
	int  m_nID;								//�W���C�p�b�h�̔ԍ�
	int		m_nStickX[2];
	int		m_nStickY[2];
	bool m_abConnection;					// �W���C�p�b�h�̐ڑ����

	int	 m_nPress[JOYPAD_MAX_KEY];			//���������Ă���F��
	bool m_bButtonOld[JOYPAD_MAX_KEY];		//�O��̃{�^��
	bool m_bButton[JOYPAD_MAX_KEY];			//����̃{�^��
	float m_fStickAngle[JOYPAD_MAX_STICK];	//�X�e�B�b�N�̊p�x
};
#endif
