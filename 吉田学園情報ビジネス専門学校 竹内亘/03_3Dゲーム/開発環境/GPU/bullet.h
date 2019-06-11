//=============================================================================
//
// �e���� [bullet.h]
// Author : �|���j
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// �e�̍\����
//*****************************************************************************
typedef enum
{// �e�̎��
	BULLETTYPE_PLAYER = 0,	//�v���C���[�̒e
	BULLETTYPE_ENEMY,		//�G�̒e
	BULLETTYPE_MAX
} BULLETTYPE;

typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 move;			// �ړ���
	D3DXMATRIX mtxWorld;		// ���[���h�}�g���b�N�X
	int nIdexShadow;			// �e���擾�̂���
	int nLife;					// �e�̃��C�t
	BULLETTYPE nType;			// �e�̎��
	D3DXVECTOR3 vecA;			// �x�N�g��A
	D3DXVECTOR3 vecB;			// �x�N�g��B
	D3DXVECTOR3 vecC;			// �x�N�g��C
	bool bUse;					// �g�p���Ă��邩�ǂ���
}Bullet;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);
//void SetPositionBillboard(int nIdexBillboard, D3DXVECTOR3 pos);




#endif
