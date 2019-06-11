//=========================================================================================================================
// 
// �G�t�F�N�g���� [effect.h]
// Author : Eisuke Sakagawa
// 
//=========================================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// �\���̒�`
//*************************************************************************************************************************
typedef enum
{
	EFFECTTYPE_NONE = 0,
	EFFECTTYPE_BULLET,
	EFFECTTYPE_EXPLOSION,
	EFFECTTYPE_RESURRECTION,
	EFFECTTYPE_RESURRECTIONRAIN,
	EFFECTTYPE_RESURRECTIONHAPPY,		//������
	EFFECTTYPE_RESURRECTIONUSUALLY,		//����
	EFFECTTYPE_RESURRECTIONSAD,			//�߂���
	EFFECTTYPE_RESURRECTIONRIPPLE,		//���s��
	EFFECTTYPE_RESURRECTIONANGRY,		//�{��
	EFFECTTYPE_RESURRECTIONSTAMP,
	EFFECTTYPE_RESURRECTIONWATER,
	EFFECTTYPE_RESURRECTIONWATER_1,


	EFFECTTYPE_MAX
}EFFECTTYPE;

typedef struct
{
	D3DXVECTOR3 pos;			// �ʒu
	D3DXVECTOR3 posR;			// �ʒu
	D3DXVECTOR3 nor;
	D3DXVECTOR3 move;			// �ړ��l
	D3DXCOLOR col;				// �F
	EFFECTTYPE Type;			// ���
	D3DXVECTOR3 rot;			//�@���x�N�g��
	D3DXMATRIX mtxWorld;		// ���_�J���[
	float fRadius;				// ���a(�傫��)
	float fLength;				//����

	int nTypeTx;
	

	int nLife;					// �\������(����)
	bool bUse;					// �g�p���Ă��邩�ǂ���
} EFFECT;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitEffect(void);			// �G�t�F�N�g����������
void UninitEffect(void);		// �G�t�F�N�g�I������
void UpdateEffect(void);		// �G�t�F�N�g�X�V����
void DrawEffect(void);			// �G�t�F�N�g�`�揈��

void SetBulletEffect(D3DXVECTOR3 pos, D3DXCOLOR col, EFFECTTYPE Type, float fRadius, int nLife, int nTypeTx);	// �e�G�t�F�N�g�ݒ菈��
void SetParticleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx);		// �����G�t�F�N�g�ݒ菈��
void SetSmokeEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife,int nTypeTx);			// ���G�t�F�N�g�ݒ菈��
void SetRainEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx);			// ���G�t�F�N�g�ݒ菈��
void SetMagicEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx);			// ���G�t�F�N�g�ݒ菈��

void SetEmotionEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx);			// ����G�t�F�N�g�ݒ菈��
void SetRippleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx);			// ���G�t�F�N�g�ݒ菈��
//void SetAngryEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx);			// ���G�t�F�N�g�ݒ菈��

void DeleteEffect(void);
#endif
