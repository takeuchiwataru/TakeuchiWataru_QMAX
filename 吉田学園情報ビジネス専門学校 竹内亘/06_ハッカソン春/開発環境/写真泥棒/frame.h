//=============================================================================
//
// �t���[������ [frame.h]
// Author : �|���j
//
//=============================================================================
#ifndef _FRAME_H_
#define _FRAME_H_

#include "main.h"

//*****************************************************************************
// �t���[���̍\���̒�`
//*****************************************************************************
typedef enum
{// �t���[���̎��
	FRAME_TIMER = 0,
	FRAME_SCORE,
	FRAME_LIFE,
	FRAME_MAX
}FRAME;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXCOLOR col;			// �F
	float fWidth;			// ��
	float fHeight;			// ����
	FRAME nType;			// ���
	bool bUse;				// �g�p���Ă��邩�ǂ���
}Frame;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitFrame(void);
void UninitFrame(void);
void UpdateFrame(void);
void DrawFrame(void);

#endif

