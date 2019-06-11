//=============================================================================
//
// �p�[�e�B�N���̏��� [particle.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"

//*****************************************************************************
// �p�[�e�B�N���̍\����
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3   pos;              // �ʒu(���S)
	D3DXVECTOR3   move;             // �ړ���
	D3DXVECTOR3   rot;              // ����
	D3DXMATRIX    mtxWorld;         // ���[���h�}�g���b�N�X
	D3DXCOLOR     col;              // �F
	float         fRadius;          // ��
	int           nLife;            // ����
	int           nIdxShadow;       // �g�p���Ă���e�̔ԍ�
	bool          bUse;             // �g�p���Ă��邩�ǂ���
}Particle;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define  MAX_PARTICLE   (256)        // �p�[�e�B�N���̑���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitParticle(void);
void UninitParticle(void);
void UpdateParticle(void);
void DrawParticle(void);
void SetParticle(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, float radius, int life);

#endif
