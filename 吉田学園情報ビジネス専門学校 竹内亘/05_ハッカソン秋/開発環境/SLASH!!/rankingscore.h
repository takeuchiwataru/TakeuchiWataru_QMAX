//=============================================================================
//
// �����L���O�X�R�A���� [rankingscore.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _RANKINGSCORE_H_
#define _RANKINGSCORE_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_RANKINGSCORE        (5)             // �����L���O�X�R�A�̐�

//*************************************
// �����L���O�X�R�A�̏��
//*************************************
typedef enum
{
	RANKINGSCORESTATE_NONE = 0, // �X�V����Ă��Ȃ����
	RANKINGSCORESTATE_UPDATE,   // �X�V���ꂽ���
	RANKINGSCORESTATE_MAX
}RANKINGSCORESTATE;

//*************************************
// �����L���O�X�R�A�̍\����
//*************************************
typedef struct
{
	D3DXVECTOR3 pos;         // ���W
	D3DXCOLOR col;           // �F
	RANKINGSCORESTATE state; // ���
	int score;               // �X�R�A
	int nCounterCol;         // �F��؂�ւ���^�C�~���O
}RANKINGSCORE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRankingScore(void);
void UninitRankingScore(void);
void UpdateRankingScore(void);
void DrawRankingScore(void);
void SetRankingScore(int nScore);
RANKINGSCORE *GetRankingScore(void);

#endif