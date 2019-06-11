//=============================================================================
//
// �v���C���[���� (�e�q�֌W�Ȃ�) [player2.h]
// Author : �|���j
//
//=============================================================================
#ifndef _PLAYER2_H_
#define _PLAYER2_H_

#include "main.h"

//*****************************************************************************
// �}�N�����
//*****************************************************************************
#define MAX_PLAYERMODEL (10)		// �v���C���[�̃��f����

//*****************************************************************************
// �v���C���[�̍\����
//*****************************************************************************
typedef enum
{// �v���C���[�̏��
	PLAYERSTATE2_APPEAR = 0,	// �o�����
	PLAYERSTATE2_NORMAL,		// �ʏ���
	PLAYERSTATE2_DAMEGE,			// �_���[�W���
	PLAYERSTATE2_DEATH,			// ���S���
	PLAYERSTATE2_MAX			// �v���C���[�̏�Ԃ̎�ނ̑���
} PLAYERSTATE2;

typedef struct
{// �v���C���[�̍\����
	D3DXVECTOR3 pos;						// �ʒu
	D3DXVECTOR3 rot;						// ����
	D3DXVECTOR3 move;						// �ړ�
	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	int nIdexShadow;						// �e�̎擾�����邽��
	int nLife;								// ���C�t
	PLAYERSTATE2 state;						// �v���C���[�̏��
	int nCounterState;						// ��ԊǗ��̃J�E���^�[
	D3DXVECTOR3 posOld;						// �ʒu
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	// ���f���̍ŏ��l�A�ő�l
	bool bDisp;								// �\�����邩�ǂ���
}Player2;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitPlayer2(void);
void UninitPlayer2(void);
void UpdatePlayer2(void);
void DrawPlayer2(void);
void HitPlayer(int nDamage);
bool CollisionPlayer(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
Player2 *GetPlayer2(void);

#endif
