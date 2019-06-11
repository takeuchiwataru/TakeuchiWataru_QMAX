//=============================================================================
//
// �A�C�e������ [item.h]
// Author : �|���j
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_ITEM	        (256)	 // �A�C�e���̍ő吔
#define TEXTURE_ITEM_SIZE   (20)     // �e�N�X�`���𒣂�t����A�C�e���̍����ƕ��̑傫��

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// �A�C�e���̎��
	ITEMTYPE_COIN = 0,		//�R�C��
	ITEMTYPE_COIN2,
	ITEMTYPE_MAX
}ITEMTYPE;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	ITEMTYPE nType;				// ���
	D3DXCOLOR col;			// �F
	bool bUse;				// �g�p���Ă��邩�ǂ���
	int nCounterState;		// ��ԊǗ��̃J�E���^�[
	int nCounterAnim;		// �A�j���[�V�����J�E���^�[
	int nPatternAnim;		// �A�j���[�V�����p�^�[��No.
	float fWidth;			// ��
	float fHeight;			// ����
}Item;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeight, ITEMTYPE nType);
bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, float * fWidth, float * fHeight);
Item *GetItem(void);
int GetCoin(void);


#endif