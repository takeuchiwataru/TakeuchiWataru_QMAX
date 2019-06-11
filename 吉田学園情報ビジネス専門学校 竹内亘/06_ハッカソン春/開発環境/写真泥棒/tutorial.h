//=============================================================================
//
// �`���[�g���A����ʏ��� [tutorial.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

typedef enum
{
	TUTORIAL_STATE_NONE,		//�ʏ���
	TUTORIAL_STATE_MOVE,		//�ړ����
	TUTORIAL_STATE_REMOVE,		//�߂���
	TUTORIAL_STATE_MAX,
}TUTORIAL_STATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);

#endif