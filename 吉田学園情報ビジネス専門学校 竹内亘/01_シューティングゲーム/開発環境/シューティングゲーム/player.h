//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �|���j
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

//*****************************************************************************
// �v���C���[�̍\����
//*****************************************************************************
typedef enum
{// �v���C���[�̏��
	PLAYERSTATE_APPEAR = 0,	//�o�����
	PLAYERSTATE_NORMAL,		//�ʏ���
	PLAYERSTATE_DAMEGE,		//�_���[�W���
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_END,
	PLAYERSTATE_MAX			//�G�̏�Ԃ̎�ނ̑���
} PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nLife;				//�v���C���[�̗̑�
	int nCounterState;		//��ԊǗ��̃J�E���^�[
	PLAYERSTATE state;		//�v���C���[�̏��
	bool bDisp;				//�\�����邩�ǂ���
} Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void HitPlayer(int nDamage);
Player *GetPlayer(void);

#endif