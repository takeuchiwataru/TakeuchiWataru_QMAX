//=============================================================================
//
// �G2���� [enemy2.h]
// Author : �|���j
//
//=============================================================================
#ifndef _ENEMY2_H_
#define _ENEMY2_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// �G�̎��
	ENEMYTYPE2_NORMAL = 0,			// ���ʂ̃J���X
	ENEMYTYPE2_MAX
} ENEMYTYPE2;

typedef struct
{
	DWORD nNumMat = 0;						// �}�e���A�����̐�
	D3DXVECTOR3 pos;						// �ʒu
	D3DXVECTOR3 posOld;						// �ʒu
	D3DXVECTOR3 rot;						// ����
	D3DXVECTOR3 move;						// ����
	D3DXMATRIX	mtxWorld;					// ���[���h�}�g���b�N�X
	int nIdxShadow;							// �e�̃C���f�b�N�X
	ENEMYTYPE2 nType;						// ���f���̎��
	int nIdexShadow;						// �e�̎擾�����邽��
	//bool bUse;								// �g�p���Ă��邩
	bool bDisp;								// �\�����邩�ǂ���
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	// ���f���̍ŏ��l�A�ő�l
} ENEMY2;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitEnemy2(void);
void UninitEnemy2(void);
void UpdateEnemy2(void);
void DrawEnemy2(void);
//bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin);
void SetEnemy2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ENEMYTYPE2 nType);
bool CollisionEnemy2(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
ENEMY2 *GetEnemy2(void);

#endif