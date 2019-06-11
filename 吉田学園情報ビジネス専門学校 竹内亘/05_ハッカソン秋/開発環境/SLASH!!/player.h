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
// �}�N����`
//*****************************************************************************
#define PLAYER_LIFE			(3)									//�v���C���[���C�t
#define PLAYER_REMAIN		(3)									//�v���C���[�̎c�@
#define PLAYER_SHARP		(5)									//�v���C���[�̌��̐ؖ�

//*****************************************************************************
// �v���C���[�̍\����
//*****************************************************************************
typedef enum
{// �v���C���[�̏��
	PLAYERSTATE_APPEAR = 0,	//�o�����
	PLAYERSTATE_NORMAL,		//�ʏ���
	PLAYERSTATE_DAMEGE,		//�_���[�W���
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_GAUGE_MAX,  //�Q�[�W�}�b�N�X���
	PLAYERSTATE_MAX			//�G�̏�Ԃ̎�ނ̑���
} PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//���W
	D3DXVECTOR3 move;		//�ړ���
	D3DXCOLOR	col;		//�F
	PLAYERSTATE state;		//�v���C���[�̏��
	int nCounterState;		//��ԊǗ��̃J�E���^�[
	int nLife;				//�v���C���[�̗̑�
	int nRemain;		    //�c�@
	int nSharp;				//���̐ؖ�
	int nCounterSharp;		//�ؖ��̃J�E���^�[
	int nCounterGauge;		//�Q�[�W�J�E���^�[
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