//=============================================================================
//
// �r���{�[�h�̏��� [billboard.h]
// Author : �|���j
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"

//*****************************************************************************
// �e�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ����
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	int nIdexShadow;			// �e���擾�̂���
	bool bUse;					// �g�p���Ă��邩�ǂ���
}Billboard;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBillboard(void);
void UninitBillboard(void);
void UpdateBillboard(void);
void DrawBillboard(void);
int SetBillboard(D3DXVECTOR3 pos);


#endif
