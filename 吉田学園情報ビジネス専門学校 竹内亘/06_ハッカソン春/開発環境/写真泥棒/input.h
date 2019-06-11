//=============================================================================
//
// ���͏��� [input.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define   MAX_JOYPAD  (2)       // �ڑ��ł���p�b�h�̐�

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{
	DIJS_BUTTON_0 = 0,  // X�{�^��
	DIJS_BUTTON_1,      // A�{�^��
	DIJS_BUTTON_2,      // B�{�^��
	DIJS_BUTTON_3,      // Y�{�^�� 
	DIJS_BUTTON_4,      // LB�{�^��
	DIJS_BUTTON_5,      // RB�{�^��
	DIJS_BUTTON_6,      // LT�{�^��
	DIJS_BUTTON_7,      // RT�{�^��
	DIJS_BUTTON_8,      // BACK�{�^��
	DIJS_BUTTON_9,      // START�{�^��
	DIJS_BUTTON_10,     // ���A�i���O�X�e�B�b�N���������
	DIJS_BUTTON_11,     // ���A�i���O�X�e�B�b�N����������
	DIJS_BUTTON_12,     // ���A�i���O�X�e�B�b�N�E��������
	DIJS_BUTTON_13,     // ���A�i���O�X�e�B�b�N����������
	DIJS_BUTTON_14,     // �E�A�i���O�X�e�B�b�N���������
	DIJS_BUTTON_15,     // �E�A�i���O�X�e�B�b�N����������
	DIJS_BUTTON_16,     // �E�A�i���O�X�e�B�b�N�E��������
	DIJS_BUTTON_17,     // �E�A�i���O�X�e�B�b�N����������
	DIJS_BUTTON_18,     // �\���L�[���������
	DIJS_BUTTON_19,     // �\���L�[����������
	DIJS_BUTTON_20,     // �\���L�[�E��������
	DIJS_BUTTON_21,     // �\���L�[����������
						// �ȉ����蓖�ĂȂ�
						DIJS_BUTTON_22,
						DIJS_BUTTON_23,
						DIJS_BUTTON_24,
						DIJS_BUTTON_25,
						DIJS_BUTTON_26,
						DIJS_BUTTON_27,
						DIJS_BUTTON_28,
						DIJS_BUTTON_29,
						DIJS_BUTTON_30,
						DIJS_BUTTON_31,
						DIJS_BUTTON_MAX
}PADBUTTON;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
void UninitInput(void);
void UpdateInput(void);
bool GetKeyboardPress(int nKey);
bool GetKeyboardTrigger(int nKey);
bool GetKeyboardRelease(int nKey);
bool GetKeyboardRepeat(int nKey);
bool GetJoyPadPress(int nButton, int nIdxPad);
bool GetJoyPadTrigger(int nButton, int nIdxPad);
bool GetJoyPadRelease(int nButton, int nIdxPad);
bool GetJoyPadRepeat(int nButton, int nIdxPad);

float GetJotPadRadian(int nIdxPad);
float GetJotPadRightStick(int nIdxPad);

#endif