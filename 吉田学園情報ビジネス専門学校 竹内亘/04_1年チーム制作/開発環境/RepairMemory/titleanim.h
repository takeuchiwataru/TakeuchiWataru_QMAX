//=============================================================================
//
// �^�C�g������ [titleanim.h]
// Author : ���������@Sato_Aumi
//
//=============================================================================
#ifndef _TITLEANIM_H_
#define _TITLEANIM_H_

#include "main.h"

//=============================================================================
// �\���̒�`
//=============================================================================
typedef struct
{// �^�C�g���A�j���[�V����
	int nCntAnim;
	int nCntAnimNum;
	bool bUse;
}TitleAnim;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitTitleAnim(void);
void UninitTitleAnim(void);
void UpdateTitleAnim(void);
void DrawTitleAnim(void);

void SetTitleAnim(void);
TitleAnim GetTitleAnim(void);
void SetTitleAnimNum(void);

void DeleteTitleAnim(void);
#endif
