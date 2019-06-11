//=============================================================================
//
// ���f������ [model.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef enum
{
	MODELSET_POS = 0,
	MODELSET_ROT,
	MODELSET_MAX
}MODELSET;

typedef struct
{
	D3DXMATRIX mtxWorld;    // ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;        // ���W
	D3DXVECTOR3 rot;        // ����
}Vertex_Model;

typedef struct
{
	D3DXVECTOR3  pos;                       // �ʒu
	D3DXVECTOR3  rot;                       // ����
	D3DXVECTOR3  move;                      // �ړ���
	D3DXMATRIX   mtxWorld;                  // ���[���h�}�g���b�N�X
	D3DXVECTOR3	vtxMinObstacle, vtxMaxObstacle;	// ���f���̍ŏ��l�A�ő�l
	Vertex_Model Vertex[4];                 // ���_�̃��[���h�}�g���b�N�X
}Model;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
void CollisionShutterModel(D3DXVECTOR3 pos, D3DXVECTOR3 radius);
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 radius);

#endif