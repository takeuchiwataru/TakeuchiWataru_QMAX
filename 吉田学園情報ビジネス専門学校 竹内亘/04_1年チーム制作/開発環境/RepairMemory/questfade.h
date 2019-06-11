//=============================================================================
//
// �N�G�X�g�t�F�[�h���� [questfade.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _QUESTFADE_H_
#define _QUESTFADE_H_

#include "main.h"
#include "game.h"

//=============================================================================
//	�}�N����`
//=============================================================================
#define QUESTINTERVAL_TIME		(60 * 10)						//��ʐ؂�ւ��̎���

//=============================================================================
// �t�F�[�h�̏��
//=============================================================================
typedef enum
{
	QUESTFADE_NONE = 0,		// �������Ă��Ȃ����
	QUESTFADE_IN,			// �t�F�[�h�C�����
	QUESTFADE_OUT,			// �t�F�[�h�A�E�g���
	QUESTFADE_MAX
} QUESTFADE;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitQuestFade(QUESTSTATE modeNext);
void UninitQuestFade(void);
void UpdateQuestFade(void);
void DrawQuestFade(void);

void SetQuestFade(QUESTSTATE modeNext);
QUESTFADE GetQuestFade(void);

#endif
