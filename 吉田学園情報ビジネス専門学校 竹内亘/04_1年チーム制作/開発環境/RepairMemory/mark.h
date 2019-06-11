//=============================================================================
//
// �}�[�N�̏��� [mark.h]
// Author : �������� Sato_Asumi
//
//=============================================================================
#ifndef _MARK_H_
#define _MARK_H_

#include "main.h"

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	D3DXVECTOR3		pos;			//���S���W
	D3DXVECTOR3		move;			//�ړ���
	D3DXVECTOR3		Oldpos;			//�O��̍��W
	D3DXMATRIX		mtxWorld;		//���[���h�}�g���b�N�X
	float			ChangeMove;		//�ω���
	int				nCntMove;		//�ω��ʂ̃J�E���^�[
	bool			bUse;			//�g�p���Ă��邩�ǂ���		
}Mark;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitMark(void);
void UninitMark(void);
void UpdateMark(void);
void DrawMark(void);

int SetMark(D3DXVECTOR3 pos);
void DeleteMark(void);
void DeleteMark(int nIdxMark);

#endif
