//=============================================================================
//
// �{�^������ [Bottun.h]
// Author : ���������@Sato_Aumi
//
//=============================================================================
#ifndef _BOTTUN_H_
#define _BOTTUN_H_

#include "main.h"

//=============================================================================
// ��Ԃ̐ݒ�
//=============================================================================
typedef enum
{
	BOTTUNTYPE_NOMAL = 0,
	BOTTUNTYPE_SELECT,
	BOTTUNTYPE_ENTER,
	BOTTUNTYPE_MAX,
}BOTTUNTYPE;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	int				nTex;		//�e�N�X�`���̖��O
	BOTTUNTYPE		type;		//�{�^���̏��
	bool			bUse;		//�g�p���Ă��邩�ǂ���
}Bottun;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitBottun(void);
void UninitBottun(void);
void UpdateBottun(void);
void DrawBottun(void);

void SetBottunType(BOTTUNTYPE type);
void SetBottun(void);
void DeleteBottun(void);
#endif

