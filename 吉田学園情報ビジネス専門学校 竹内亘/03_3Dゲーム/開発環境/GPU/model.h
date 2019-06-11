//=============================================================================
//
// ���f������ [model.h]
// Author : �|���j
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef enum
{// ���f���̎��
	MODELTYPE_BENCH = 0,		// �x���`1
	MODELTYPE_BENCH2,			// �x���`2
	MODELTYPE_BURANKO,			// �u�����R
	MODELTYPE_SLIDE,			// �����
	MODELTYPE_TAIYA,			// �^�C��
	MODELTYPE_JG,				// �W�����O���W��
	MODELTYPE_SEESAW,			// �V�[�\�[
	MODELTYPE_TAIYA2,			// �^�C��2
	MODELTYPE_MAX
} MODELTYPE;

typedef struct
{
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	// ���f���̍ŏ��l�A�ő�l
} VTXMODEL;

typedef struct
{
	DWORD nNumMat = 0;						// �}�e���A�����̐�
	D3DXVECTOR3 pos;						// �ʒu
	D3DXVECTOR3 rot;						// ����
	D3DXVECTOR3 move;						// ����
	D3DXMATRIX	mtxWorld;					// ���[���h�}�g���b�N�X
	int nIdxShadow;							// �e�̃C���f�b�N�X
	MODELTYPE nType;						// ���f���̎��
	bool bUse;								// �g�p���Ă��邩
	D3DXVECTOR3 VtxMinModel, VtxMaxModel;	// ���f���̍ŏ��l�A�ő�l
} MODEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
//bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin);
void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODELTYPE nType);
bool CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove);
MODEL *GetModel(void);

#endif