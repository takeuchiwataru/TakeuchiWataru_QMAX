//=============================================================================
//
// �����L���O���� [ranking.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_RANKINGSCORE        (5)             // �����L���O�X�R�A�̐�

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{
	RANKINGOLD_TITLE = 0,
	RANKINGOLD_SELECT,
	RANKINGOLD_MAX
}RANKINGOLD;

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
	D3DXCOLOR colStd;        // ���̐F
	D3DXCOLOR col;           // ���݂̐F
	RANKINGSCORESTATE state; // ���
	int score;               // �X�R�A
	int nCounterCol;         // �F��؂�ւ���^�C�~���O
}RANKINGSCORE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitRanking(void);
void UninitRanking(void);
void UpdateRanking(void);
void DrawRanking(void);
void SetRankingOld(RANKINGOLD rankold);

//------------------
//  ���S�p
//------------------
void InitRankingLogo(void);
void UninitRankingLogo(void);
void UpdateRankingLogo(void);
void DrawRankingLogo(void);

//------------------
//  ���ʗp
//------------------
void InitRankingRank(void);
void UninitRankingRank(void);
void UpdateRankingRank(void);
void DrawRankingRank(void);

//------------------
//  �X�R�A�p
//------------------
void InitRankingScore(void);
void UninitRankingScore(void);
void UpdateRankingScore(void);
void DrawRankingScore(void);
void SetRankingScore(int nScore);
RANKINGSCORE *GetRankingScore(void);

#endif