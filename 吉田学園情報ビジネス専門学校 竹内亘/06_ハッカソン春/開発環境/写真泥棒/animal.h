//=============================================================================
//
// �����̏��� [obstacle.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include "main.h"

//*****************************************************************************
// ���f���̍\����
//*****************************************************************************
typedef enum
{
	ANIMALTYPE_CAT = 0,    // �L
	ANIMALTYPE_DOG,        // ��
	ANIMALTYPE_CROW,       // �J���X
	ANIMALTYPE_MAX
}ANIMALTYPE;

typedef struct
{
	D3DXVECTOR3 pos;	              // ���݂̈ʒu
	D3DXVECTOR3 posold;	              // �O��̈ʒu
	D3DXVECTOR3 rot;	              // ���݂̌���
	D3DXVECTOR3 DestRot;              // �ړI�̌���
	D3DXVECTOR3 DiffRot;              // �����̌���
	D3DXVECTOR3 move;	              // �ړ���
	int         nMoveCounter;         // �ړ��Ǘ��J�E���^�[
	int			nInxShadow;           // �e
	ANIMALTYPE	Type;                 // ���
	D3DXMATRIX	mtxWorld;	          // ���[���h�}�g���b�N�X
	bool		bUse;                 // �g�p���Ă��邩�ǂ���
	D3DXVECTOR3	vtxMinObstacle, vtxMaxObstacle;	// ���f���̍ŏ��l�A�ő�l
}ANIMAL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitAnimal(void);
void UninitAnimal(void);
void UpdateAnimal(void);
void DrawAnimal(void);
void SetAnimal(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, ANIMALTYPE type);
void CollisionShutterAnimal(D3DXVECTOR3 pos, D3DXVECTOR3 radius);

#endif