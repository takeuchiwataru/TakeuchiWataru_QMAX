//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// �T�E���h�t�@�C��
//*************************************
typedef enum
{
	SOUND_LABEL_BGM_GAME = 0,	// �Q�[������BGM
	SOUND_LABEL_BGM_TITLE,		// �^�C�g��BGM
	SOUND_LABEL_BGM_GAMEOVER,	// �Q�[���I�[�o�[BGM
	SOUND_LABEL_BGM_GAMECLEAR,	// �Q�[���N���ABGM
	SOUND_LABEL_BGM_TUTORIAL,	// �`���[�g���A��BGM
	SOUND_LABEL_SE_GEAR,		// ���Ԃ��͂߂鉹
	SOUND_LABEL_SE_MISS,		// ���s��
	SOUND_LABEL_SE_RUN,			// ���鉹
	SOUND_LABEL_SE_WALK,		// ������
	SOUND_LABEL_SE_PICKUP,		// �E����
	SOUND_LABEL_SE_DECIDE,		// ���艹
	SOUND_LABEL_SE_SELECT,		// �I����
	SOUND_LABEL_SE_PAUSE,		// 
	SOUND_LABEL_SE_PAZZLEIN,	// 
	SOUND_LABEL_SE_PAZZLEEND,	// 
	SOUND_LABEL_SE_RESULT00,	// 
	SOUND_LABEL_SE_RESULT01,	// 
	SOUND_LABEL_SE_RESULT02,	// 
	SOUND_LABEL_SE_RESULT03,	// 
	SOUND_LABEL_MAX
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
