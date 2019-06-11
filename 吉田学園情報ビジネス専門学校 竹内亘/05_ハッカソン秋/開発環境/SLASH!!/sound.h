//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Meguro Mikiya
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
	SOUND_LABEL_BGM_TITLE = 0,	// BGM�^�C�g��
	SOUND_LABEL_BGM_TUTORIAL,	// BGM�`���[�g���A��
	SOUND_LABEL_BGM_GAME,		// BGM�Q�[��
	SOUND_LABEL_BGM_RESULT,		// BGM���U���g
	SOUND_LABEL_BGM_RANKING,	// BGM�����L���O
	SOUND_LABEL_SE_ZANGEKI,		// �a��
	SOUND_LABEL_SE_ZANKIKAIHUKU,// �c�@��
	SOUND_LABEL_SE_LIFEKAIHUKU,	// ���C�t��
	SOUND_LABEL_SE_KENMA,		// ����
	SOUND_LABEL_SE_KEN,			// �������[�h
	SOUND_LABEL_SE_KAMINARI,	// �K�E�Z
	SOUND_LABEL_SE_BOMB000,		// ������
	SOUND_LABEL_SE_DECIDE,		// ���艹
	SOUND_LABEL_SE_SELECT,
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
