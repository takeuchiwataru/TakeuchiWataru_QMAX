//=============================================================================
//
// �e�̏��� [shadow.h]
// Author : �������� Sato_Asumi
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3				pos;			//���S���W
	D3DXVECTOR3				rot;			//����
	D3DXVECTOR3				Otherpos;		//���S���W
	D3DXMATRIX				mtxWorld;		//���[���h�}�g���b�N�X
	D3DXCOLOR				color;			//�F
	bool					bUse;			//�g�p���Ă��邩�ǂ���
	float					fHight;			//����
	float					fWhidth;		//��
	float					fLength;		//�Ίp���̒���
}Shadow;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHight, float fWhidth);
void SetPostionShadow(int nIdxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 OldPos);
void DeleteShadow(void);
void DeleteShadow(int nIdxShadow);
#endif