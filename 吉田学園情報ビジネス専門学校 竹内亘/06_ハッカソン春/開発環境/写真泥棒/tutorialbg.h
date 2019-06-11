//=============================================================================
//
// �`���[�g���A���w�i�̏��� [tutorialbg.h]
// Author : Jukiya Hayakawa
//
//=============================================================================
#ifndef _TUTORIALBG_H_
#define _TUTORIALBG_H_

#include "main.h"

//*****************************************************************************
// �|���S���̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 move;			// �ړ���
	bool		bUse;			// �g�p���Ă��邩�ǂ���
	D3DXMATRIX	mtxWorldTutorialBG;
} TUTORIALBG;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTutorialBG(void);
void UninitTutorialBG(void);
void UpdateTutorialBG(void);
void DrawTutorialBG(void);
void SetTutorialBG(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif