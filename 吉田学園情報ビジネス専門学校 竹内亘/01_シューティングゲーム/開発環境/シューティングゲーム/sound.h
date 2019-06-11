//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �|���j
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
	SOUND_LABEL_BGM000 = 0,			// BGM0
	SOUND_LABEL_BGM001,				// BGM1
	SOUND_LABEL_BGM002,				// BGM2
	SOUND_LABEL_BGM003,				// BGM3(�{�X)
	SOUND_LABEL_SE_SHOT,			// �e���ˉ�0
	SOUND_LABEL_SE_SHOT001,			// �e���ˉ�1
	SOUND_LABEL_SE_SHOT002,			// �e���ˉ�2
	SOUND_LABEL_SE_HIT000,			// �q�b�g��0
	SOUND_LABEL_SE_HIT001,			// �q�b�g��1
	SOUND_LABEL_SE_HIT002,			// �q�b�g��2
	SOUND_LABEL_SE_EXPLOSION,		// ������0
	SOUND_LABEL_SE_EXPLOSION001,	// ������1
	SOUND_LABEL_SE_GAMECLEAR,		// �Q�[���N���A
	SOUND_LABEL_SE_GAMEOVER,		// �Q�[���I�[�o�[
	SOUND_LABEL_SE_DECIDE,			// ���艹
	SOUND_LABEL_MAX,
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
