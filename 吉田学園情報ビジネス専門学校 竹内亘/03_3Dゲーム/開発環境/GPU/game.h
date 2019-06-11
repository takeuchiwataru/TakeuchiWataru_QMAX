//=============================================================================
//
// �Q�[������ [game.h]
// Author : �|���j
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//*****************************************************************************
// �Q�[���̏��
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,		//�������ĂȂ�
	GAMESTATE_NORMALL,		//�ʏ���
	GAMESTATE_GAMECLEAR,	//�Q�[���N���A���
	GAMESTATE_GAMEOVER,		//�Q�[���I�[�o�[���
	GAMESTATE_END,			//�I�����
	GAMESTATE_MAX
}GAMESTATE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);

#endif