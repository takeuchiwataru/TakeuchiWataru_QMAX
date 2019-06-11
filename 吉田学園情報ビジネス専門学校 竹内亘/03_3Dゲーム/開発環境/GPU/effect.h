//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : �|���j
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	float fRadius;			// ���a(�傫��)
	int nLife;				// �\������(����)
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	bool bUse;				// �g�p���Ă��邩�ǂ���
} EFFECT;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, float fRadius, int nLife);

#endif
