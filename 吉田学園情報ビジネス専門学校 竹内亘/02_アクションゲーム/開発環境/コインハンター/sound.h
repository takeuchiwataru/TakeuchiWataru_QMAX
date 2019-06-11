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
	SOUND_LABEL_BGM_TITLE,		// BGM�^�C�g��
	SOUND_LABEL_BGM_GAMEOVER,	// �Q�[���I�[�o�[BGM
	SOUND_LABEL_BGM_GAMECLEAR,	// �Q�[���N���ABGM
	SOUND_LABEL_SE_JUMP000,		// �W�����v
	SOUND_LABEL_SE_JUMP001,		// �W�����v
	SOUND_LABEL_SE_COINOOO,		// �R�C��
	SOUND_LABEL_SE_OSU,			// �����u���b�N�̉�
	SOUND_LABEL_SE_BREAK,		// �u���b�N�̉��鉹
	SOUND_LABEL_SE_DECIDE,		// ���艹
	SOUND_LABEL_SE_SELECT,		// �I����
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
