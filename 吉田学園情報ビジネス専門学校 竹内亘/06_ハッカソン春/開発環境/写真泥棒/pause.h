//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
//*************************************
// ���ڂ̏��
//*************************************
typedef enum
{
	PAUSESELECT_NONE = 0,   // �I������Ă��Ȃ����
	PAUSESELECT_SELECT,     // �I������Ă�����
	PAUSESELECT_PUSH,       // ������Ă�����
	PAUSESELECT_MAX
}PAUSESELECT;

typedef enum
{
	RESTART_CONTINUE,  // �R���e�B�j���[
	RESTART_RETRY,     // �Q�[�����g���C
	RESTART_QUIT,      // �^�C�g���J��
	RESTART_MAX
}RESTART;

//*************************************
// ���ڂ̍\����
//*************************************
typedef struct
{
	D3DXCOLOR col;       // �F
	PAUSESELECT select;  // �I������Ă��邩�ǂ���
	int nCounter;        // �`�悷��^�C�~���O���v��J�E���^�[
}PAUSE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//----------------
// ����ʗp
//----------------
void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);

//----------------
// ���S�p
//----------------
void InitPauseLogo(void);
void UninitPauseLogo(void);
void UpdatePauseLogo(void);
void DrawPauseLogo(void);

//----------------
// �I�����ڗp
//----------------
void InitPauseSelect(void);
void UninitPauseSelect(void);
void UpdatePauseSelect(void);
void DrawPauseSelect(void);
RESTART GetRestart(void);

#endif