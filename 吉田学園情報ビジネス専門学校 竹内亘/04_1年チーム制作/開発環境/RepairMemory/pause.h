//=============================================================================
//
// �|�[�Y���� [pouse.h]
// Author : ���������@Sato_Aumi
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//=============================================================================
// �|�[�Y�̏�Ԃ̎��
//=============================================================================
typedef enum
{//�|�[�Y�̏��
	PAUSESTATE_CONTINUE = 0,
	PAUSESTATE_RETRY,
	PAUSESTATE_QUIT,
	PAUSESTATE_MAX,
}PAUSESTATE;

typedef enum
{//�{�^���̏��
	BOTTUNSTATE_NOMAL = 0,
	BOTTUNSTATE_SELECT,
	BOTTUNSTATE_NONE,
	BOTTUNSTATE_MAX,
}BOTTUNSTATE;

//=============================================================================
// �|�[�Y�̍\����
//=============================================================================
typedef struct
{
	int				nTex;		//�e�N�X�`���̔ԍ�
	BOTTUNSTATE		state;		//��Ԑݒ�
}Pause;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

void SetPauseState(PAUSESTATE state);
Pause * GetPause(void);
#endif