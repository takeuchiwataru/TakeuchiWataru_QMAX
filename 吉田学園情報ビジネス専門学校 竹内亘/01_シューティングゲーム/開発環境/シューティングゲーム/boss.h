//=============================================================================
//
// �{�X���� [boss.h]
// Author :�@�|���j
//
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ENEMY	(256)		//�G�̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// �G�̏��
	BOSSSTATE_NORMAL = 0,		//�ʏ���
	BOSSSTATE_DAMEGE,			//�_���[�W���
	BOSSSTATE_DEATH,			//���S���
	BOSSSTATE_END,
	BOSSSTATE_MAX				//�{�X�̏�Ԃ̎�ނ̑���
} BOSSSTATE;

typedef struct
{// �G�̍\����
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 move;			//�ړ���
	int nType;					//���
	BOSSSTATE state;			//�G�̏��
	int nCounterState;			//��ԊǗ��̃J�E���^�[
	int nLife;					//�G�̗̑�
	int nCounterAnimBoss;		//�A�j���[�V�����J�E���^�[
	int nPartternAnimBoss;		//�A�j���[�V�����p�^�[���X�V
	bool bUse;					//�g�p���Ă��邩�ǂ���
} Boss;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBoss(void);
void UninitBoss(void);
void UpdateBoss(void);
void DrawBoss(void);
void SetBoss(D3DXVECTOR3 pos, int nType);
void HitBoss(int nCntBoss, int nDamage);
Boss *GetBoss(void);

#endif
