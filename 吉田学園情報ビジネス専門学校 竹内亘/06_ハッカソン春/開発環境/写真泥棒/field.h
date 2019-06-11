//=============================================================================
//
// �n�ʂ̏��� [field.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"

//*****************************************************************************
// �t�B�[���h�̍\����
//*****************************************************************************
typedef enum
{
	FIELDSET_TEXTYPE = 0,
	FIELDSET_POS,
	FIELDSET_ROT,
	FIELDSET_SIDE,
	FIELDSET_DEPTH,
	FIELDSET_XBLOCK,
	FIELDSET_ZBLOCK
}FIELDSET;

typedef struct
{
	D3DXVECTOR3 pos;        // ���W
	D3DXVECTOR3 rot;        // ����
	D3DXMATRIX  mtxWorld;   // ���[���h�}�g���b�N�X
	float       Depth;      // ���s�̒���
	float       Side;       // ���̒���
	int         XBlock;     // ���̕�����
	int         ZBlock;     // �c�̕�����
	int         nNumVertex; // ���_��
	int         nNumIndex;  // �C���f�b�N�X��
	int         nNumPolygon;// �|���S����
	int         TexType;    // �e�N�X�`���̎��
}Field;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);

#endif