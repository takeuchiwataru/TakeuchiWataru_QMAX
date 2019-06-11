//=============================================================================
//
// �e�̏��� [shadow.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define  MAX_SHADOW   (3000)       // �e�̑���

//*****************************************************************************
// �e�̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3  pos;          // �ʒu(���S)
	D3DXVECTOR3  rot;          // ����
	D3DXMATRIX   mtxWorld;     // ���[���h�}�g���b�N�X
	D3DXCOLOR    col;          // ���_�J���[
	float        width;        // ��
	float        depth;        // ���s
	bool         bUse;         // �g�p���Ă��邩�ǂ���
}Shadow;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, float width, float depth);
void SetPositionShadow(int IdxShadow, D3DXVECTOR3 pos);
void SetColShadow(int IdxShadow, D3DXCOLOR col);
void SetSizeShadow(int IdxShadow, float width, float depth);
void DeleteShadow(int IdxShadow);

#endif