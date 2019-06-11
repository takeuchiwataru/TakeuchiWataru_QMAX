//=============================================================================
//
// �X�R�A���� [score.h]
// Author : 
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void SetScore(int nValue);
void AddScore(int nValue);
int GetScore(void);
void ReSetScore(void);
void SetScore(D3DXVECTOR3 pos, float fWidth, float fHeight);

#endif
