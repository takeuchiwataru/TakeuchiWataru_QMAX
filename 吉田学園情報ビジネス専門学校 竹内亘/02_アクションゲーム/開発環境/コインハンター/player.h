//=============================================================================
//
// �v���C���[���� [player.h]
// Author : �|���j
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "block.h"

//*****************************************************************************
// �v���C���[�̍\����
//*****************************************************************************
typedef enum
{// �v���C���[�̏��
	PLAYERSTATE_APPEAR = 0,	//�o�����
	PLAYERSTATE_NORMALL,	//�ʏ���
	PLAYERSTATE_DAMEGE,		//�_���[�W���
	PLAYERSTATE_DEATH,		//���S���
	PLAYERSTATE_END,
	PLAYERSTATE_MAX			//��Ԃ̎�ނ̑���
} PLAYERSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posold;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	int nCounterAnim;		//�A�j���[�V�����J�E���^�[
	int nPatternAnim;		//�A�j���[�V�����p�^�[��No.
	int nDirectionMove;		//0���E�A1����
	D3DXCOLOR	col;		//�F
	PLAYERSTATE state;		//�v���C���[�̏��
	int nCounterState;		//��ԊǗ��̃J�E���^�[
	float fWidth;			//��
	float fHeight;			//����
	//int nLife;				//�v���C���[�̗̑�
	//int Remain;				//�c�@
	//int nSharp;				//���̐ؖ�
	//int nCounterSharp;		//�ؖ��̃J�E���^�[
	//int nCounterGauge;		//�Q�[�W�J�E���^�[
	bool bDisp;				//�\�����邩�ǂ���
	bool bJump;				//�W�����v���Ă邩�ǂ���
	Block *pBlock;			//�Ώۂ̃u���b�N�ւ̃|�C���^
} Player;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
//void HitPlayer(int nDamage);
Player *GetPlayer(void);

#endif