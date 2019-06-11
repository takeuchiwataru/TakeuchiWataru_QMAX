//=========================================================================================================================
// 
// ���͏��� [input.h]
// Author : Eisuke Sakagawa
// 
//=========================================================================================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd);			// �L�[�{�[�h����������
void UpdateKeyboard(void);										// �L�[�{�[�h�X�V����

bool GetKeyboardPress(int Key);									// �L�[�{�[�h�v���X
bool GetKeyboardTrigger(int Key);								// �L�[�{�[�h�g���K�[
bool GetKeyboardRelease(int Key);								// �L�[�{�[�h�����[�X

HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd);				// �}�E�X����������
void UpdateMouse(void);											// �}�E�X�X�V����

bool GetMousePress(int Key);									// �}�E�X�v���X
bool GetMouseTrigger(int Key);									// �}�E�X�g���K�[
bool GetMouseRelease(int Key);									// �}�E�X�����[�X
DIMOUSESTATE2 GetMousePointer(void);							// �}�E�X�|�C���^�[

HRESULT InitJoystick(HINSTANCE hInstance, HWND hWnd);			// �W���C�X�e�B�b�N����������
void UpdateJoystick(void);										// �W���C�X�e�B�b�N�X�V����

bool GetButtonPress(int Key);									// �{�^���v���X
bool GetButtonTrigger(int Key);									// �{�^���g���K�[
bool GetButtonRelease(int Key);									// �{�^�������[�X
bool GetCrossPress(int Key);									// �\���L�[�v���X
bool GetCrossTrigger(int Key);									// �\���L�[�g���K�[
bool GetCrossRelease(int Key);									// �\���L�[�����[�X
DIJOYSTATE GetStick(void);										// �X�e�B�b�N

void UninitInput(void);											// ���͏I������

#endif