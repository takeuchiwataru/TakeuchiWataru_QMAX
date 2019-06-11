//=============================================================================
//
// �|�[�Y���ڏ��� [pauseselect.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _PAUSESELECT_H_
#define _PAUSESELECT_H_

#include "main.h"

//*************************************
// ���ڂ̏��
//*************************************
typedef enum
{
	PAUSESELECT_NONE = 0,   // �I������Ă��Ȃ����
	PAUSESELECT_SELECT,     // �I������Ă�����
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
}PAUSE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPauseSelect(void);
void UninitPauseSelect(void);
void UpdatePauseSelect(void);
void DrawPauseSelect(void);

RESTART GetRestart(void);

#endif
