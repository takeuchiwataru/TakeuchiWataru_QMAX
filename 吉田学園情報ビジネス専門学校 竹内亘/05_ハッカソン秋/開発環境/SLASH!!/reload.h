//=============================================================================
//
// �؂ꖡ���� [reload.h]
// Author : Niwa Hodaka
//
//=============================================================================
#ifndef _RELOAD_H_
#define _RELOAD_H_

#include "main.h"

//*****************************************************************************
// �\���̂̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos; // ���W
	int reload;      // �؂ꖡ
	bool bUse;       // �g�p���Ă��邩�ǂ���
}Reload;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitReload(void);
void UninitReload(void);
void UpdateReload(void);
void DrawReload(void);
void SetReload(int reload);
void CutReload(int cut);
void AddReload(void);

#endif