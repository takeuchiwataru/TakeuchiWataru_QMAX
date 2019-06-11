//=============================================================================
//
// �G���� [enemy.h]
// Author : �|���j
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

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
	ENEMYSTATE_NORMAL = 0,		//�ʏ���
	ENEMYSTATE_DAMEGE,			//�_���[�W���
	ENEMYSTATE_MAX				//�G�̏�Ԃ̎�ނ̑���
} ENEMYSTATE;

typedef struct
{// �G�̍\����
	D3DXVECTOR3 pos;			//�ʒu
	D3DXVECTOR3 move;			//�ړ���
	int nType;					//���
	ENEMYSTATE state;			//�G�̏��
	int nCounterState;			//��ԊǗ��̃J�E���^�[
	int nLife;					//�G�̗̑�
	int nCounterAnimEnemy;		//�A�j���[�V�����J�E���^�[
	int nPartternAnimEnemy;		//�A�j���[�V�����p�^�[���X�V
	bool bUse;					//�g�p���Ă��邩�ǂ���
} Enemy;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, int nType);
void HitEnemy(int nCntEnemy, int nDamage);
Enemy *GetEnemy(void);

#endif
