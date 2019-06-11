//=============================================================================
//
// �u���b�N���� [block.h]
// Author :�@�|���j
//
//=============================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef enum
{// �u���b�N�̎��
	BLOCKTYPE_NOMALL = 0,		//���ʃu���b�N
	BLOCKTYPE_BERUTOKONBEA,		//�x���g�R���x�A�E
	BLOCKTYPE_BERUTOKONBEA2,	//�x���g�R���x�A��
	BLOCKTYPE_PUSH,				//������u���b�N
	BLOCKTYPE_BREAK,			//�󂹂�u���b�N
	BLOCKTYPE_JUMP,				//�W�����v�u���b�N
	BLOCKTYPE_FALL,				//�����u���b�N
	//BLOCKTYPE_YOKOMOVE,			//���ړ��u���b�N
	//BLOCKTYPE_TATEMOVE,			//�c�ړ��u���b�N
	BLOCKTYPE_MAX
} BLOCKTYPE;

typedef struct
{
	D3DXVECTOR3 pos;			//�u���b�N�̈ʒu
	float fWidth;				//��
	float fHeight;				//����
	BLOCKTYPE nType;			//���
	D3DXVECTOR3 move;			//�ړ���
	bool bUse;					//�g�p���Ă邩�ǂ���
	// �ړ����Ǘ�����
}Block;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos,float fWidth,float fHeight, BLOCKTYPE nType);
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove,float * fWidth,float * fHeight,Block **pBlock);

#endif
