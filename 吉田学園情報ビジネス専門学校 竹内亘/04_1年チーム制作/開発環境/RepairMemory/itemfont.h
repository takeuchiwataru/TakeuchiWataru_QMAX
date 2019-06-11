//=============================================================================
//
// �A�C�e���t�H���g���� [itemfont.h]
// Author : ���������@Sato_Aumi
//
//=============================================================================
#ifndef _ITEMFONT_H_
#define _ITEMFONT_H_

#include "main.h"

//=============================================================================
// ��Ԃ̐ݒ�
//=============================================================================
typedef enum
{
	TYPEITEMFONT_ITEM = 0,
	TYPEITEMFONT_STORY,
	TYPEITEMFONT_MAX,
}TYPEITEMFONT;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	char			font[256];		//�i�[�ł��镶����
	TYPEITEMFONT	type;			//�t�H���g�̃^�C�v
	bool			bUse;			//�g�p���Ă��邩�ǂ���
}ItemFont;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitItemFont(void);
void UninitItemFont(void);
void UpdateItemFont(void);
void DrawItemFont(void);

void SetItemFont(char font[256], TYPEITEMFONT type);
void DeleteItemFont(void);
bool GetUseItemFont(void);
#endif