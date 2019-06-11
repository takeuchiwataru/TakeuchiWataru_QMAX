//=============================================================================
//
// �|���S������ [meshWall.h]
// Author : �|���j  
//
//=============================================================================
#ifndef _MESHWALL_H_
#define _MESHWALL_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;					// �ʒu
	D3DXVECTOR3 rot;					// ����
	D3DXMATRIX	mtrxWorld;				// ���[���h�}�g���b�N�X
	float fHeght;						// ����
	float fWidth;						// ��
	int nVtxIndex = 0;
	int nIdxIndex = 0;
	float fPos_X = 0;
	float fPos_Y = 0;
	float fXpos = 0;
	float fYpos = 0;
	bool bUse;							// �g�p���Ă��邩�ǂ���
} MeshWall;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitMeshWall(int nIdxMeshWall, D3DXVECTOR3 pos , D3DXVECTOR3 rot);
void UninitMeshWall(void);
void UpdateMeshWall(void);
void DrawMeshWall(void);
MeshWall *GetMeshWall(void);

#endif
