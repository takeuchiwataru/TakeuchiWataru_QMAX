//=============================================================================
//
// �A�C�e���J�E���^�[���� [itemCnt.h]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#ifndef _ITEMCNT_H_
#define _ITEMCNT_H_

#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_SCORE			(2)		//�X�R�A�̌���

//=============================================================================
// ��Ԃ̐ݒ�
//=============================================================================
typedef enum
{
	SCORETYPE_WOOD = 0,
	SCORETYPE_GLASS,
	SCORETYPE_CHAIN,
	SCORETYPE_IRON,
	SCORETYPE_POT,
	SCORETYPE_RUBBER,
	SCORETYPE_CLOSS,
	SCORETYPE_MAX,
}SCORETYPE;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	int	aNum[NUM_SCORE];		// �P���ɐ������i�[����ϐ�
}ItemCnt;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitItemCnt(void);
void UninitItemCnt(void);
void UpdateItemCnt(void);
void DrawItemCnt(void);

void AddItemCnt(int nValue);
int GetItemCnt(void);
void ResetItemCnt(void);

void DeleteItemCnt(void);
#endif
