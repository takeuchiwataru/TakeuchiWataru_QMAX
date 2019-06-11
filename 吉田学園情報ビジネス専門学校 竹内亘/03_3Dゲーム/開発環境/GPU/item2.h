//=============================================================================
//
// �A�C�e��(���f��ver)���� [item2.h]
// Author : �|���j
//
//=============================================================================
#ifndef _ITEM2_H_
#define _ITEM2_H_

#include "main.h"

//*****************************************************************************
// �}�N�����
//*****************************************************************************

//*****************************************************************************
// �A�C�e���̍\����
//*****************************************************************************
typedef enum
{// �A�C�e���̎��
	ITEMTYPE2_GOMI = 0,			// �S�~
	ITEMTYPE2_PB,				// PB
	ITEMTYPE2_KAN,				// ��
	ITEMTYPE2_BOOK,				// �{
	ITEMTYPE2_MAX
}ITEMTYPE2;

typedef struct
{
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 rot;				// ����
	D3DXVECTOR3 move;				// �ړ�
	D3DXMATRIX mtxWorld;			// ���[���h�}�g���b�N�X
	D3DXVECTOR3 VtxMinModel;		// ���f���̍ŏ��l
	D3DXVECTOR3 VtxMaxModel;		// ���f���̍ő�l
	int nIdexShadow;				// �e�̎擾�����邽��
	ITEMTYPE2 nType;				// �A�C�e���̎��
	int nNumItem;					// �A�C�e���̑���
	bool bUse;						// �g�p���Ă��邩�ǂ���
}ITEM2;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItem2(void);
void UninitItem2(void);
void UpdateItem2(void);
void DrawItem2(void);
void SetItem2(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, ITEMTYPE2 nType);
bool CollisionItem2(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
ITEM2 *GetItem2(void);
int GetITEM(void);

#endif
