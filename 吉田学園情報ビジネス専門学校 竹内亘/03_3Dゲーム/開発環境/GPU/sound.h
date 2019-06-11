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
typedef enum //���x���Ɛ��ƕ��т𑵂���
{
	SOUND_LABEL_BGM_GAME = 0,	// �Q�[������BGM
	SOUND_LABEL_BGM_TITLE,		// �^�C�g��BGM
	SOUND_LABEL_BGM_RANKING,	// �����L���OBGM
	SOUND_LABEL_BGM_GAMECLEAR,	// �Q�[���N���ABGM
	SOUND_LABEL_BGM_GAMEOVER,	// �Q�[���I�[�o�[BGM
	SOUND_LABEL_SE_KARASU,		// �J���X�̖���
	SOUND_LABEL_SE_PAUSE000,	// �|�[�Y�J��
	SOUND_LABEL_SE_PAUSE001,	// �|�[�Y����
	SOUND_LABEL_SE_SELECT000,	// �I����
	SOUND_LABEL_SE_ENTER000,	// ���艹
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
