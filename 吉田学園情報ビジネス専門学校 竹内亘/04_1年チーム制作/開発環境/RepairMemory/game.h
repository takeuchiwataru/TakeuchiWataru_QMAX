//=============================================================================
//
// Game���� [game.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// ��Ԑݒ�
//=============================================================================
typedef enum
{//�Q�[��
	GAMESTATE_NONE = 0,
	GAMESTATE_QUESTSELECT,	//�I�����
	GAMESTATE_QUESTPLAY,	//�Q�[�����
	GAMESTATE_END_CLIA,		//�Q�[���N���A���
	GAMESTATE_END_OVER,		//�Q�[���I�[�o�[���
	GAMESTATE_MAX
}GAMESTATE;

typedef enum
{// �N�G�X�g�I�����
	QUESTTYPE_TUTORIAL = 0,	//�`���[�g���A��
	QUESTTYPE_FIRST,		//�N�G�X�g�P
	QUESTTYPE_SECOND,		//�N�G�X�g�Q
	QUESTTYPE_THIRD,		//�N�G�X�g�R
	QUESTTYPE_TITLE,		//�^�C�g��
	QUESTTYPE_MAX,
}QUESTTYPE;

typedef enum
{// �N�G�X�g��
	QUESTSTATE_NONE = 0,
	QUESTSTATE_MISSTION,	//�˗���������V�[��
	QUESTSTATE_SEARCH,		//�T���V�[��
	QUESTSTATE_PUZZLE,		//�p�Y���V�[��
	QUESTSTATE_REPORT,		//�񍐃V�[��
	QUESTSTATE_CLEAR,		//�N�G�X�g�N���A�V�[��
	QUESTSTATE_OVER,		//�N�G�X�g���s�V�[��
	QUESTSTATE_MAX,
}QUESTSTATE;

typedef struct
{
	int nScore;
	bool bClear;
}QUESTCLEAR;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void SetGameState(GAMESTATE state);
void SetQuestType(QUESTTYPE type);
void SetQuestState(QUESTSTATE state);
GAMESTATE GetGameState(void);
QUESTSTATE GetQuestState(void);
QUESTCLEAR *GetbClearQuest(void);

QUESTTYPE GetQuestType(void);

void SetPause(bool bPause);
bool GetGAMEPause(void);

void SetQuestClearScore(int nScore);

void SetShowTutorial(bool bTutorial);
#endif