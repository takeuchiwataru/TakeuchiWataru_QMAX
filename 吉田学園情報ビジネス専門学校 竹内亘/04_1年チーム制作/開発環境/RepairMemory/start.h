//=============================================================================
//
// �e���� [start.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _START_H_
#define _START_H_

#include "main.h"

//=============================================================================
// ��Ԃ̎��	
//=============================================================================
typedef enum
{
	STARTSTRACT_NORMAL = 0,
	STARTSTRACT_ENTER,
	STARTSTRACT_MAX
}STARTSTRACT;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct 
{
	D3DXVECTOR3		pos;					//���S�_
	D3DXCOLOR		col;					//�F
	float			ChangeCol;				//�����x�̕ω���
	STARTSTRACT		Struct;					//��Ԃ̐ݒ�
	bool			bUse;					//�g�p���Ă��邩�ǂ���
}ENTER;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitStart(void);
void UninitStart(void);
void UpdateStart(void);
void DrawStart(void);

void SetEnter(D3DXVECTOR3 pos, D3DXCOLOR col);
void SetPush(STARTSTRACT stract);
void DeleteStart(void);

#endif