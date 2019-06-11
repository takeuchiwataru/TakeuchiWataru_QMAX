//=========================================================================================================================
//
// �t�B�[���h���� [meshfield.h]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define MESHFIELD_TEXTURE_NAME1		"data\\TEXTURE\\field100.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C��1
#define MESHFIELD_TEXTURE_NAME2		"data\\TEXTURE\\field104.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C��2
#define MESHFIELD_TEXTURE_NAME3		"data\\TEXTURE\\field102.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C��3
#define MESHFIELD_TEXTURE_NAME4		"data\\TEXTURE\\field103.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C��4
#define MESHFIELD_TEXTURE_NAME5		"data\\TEXTURE\\field106.jpg"			// �ǂݍ��ރe�N�X�`���t�@�C��5
#define MESHFIELD_TEXTURE_NAME6		"data\\TEXTURE\\hunsui.jpg"				// �ǂݍ��ރe�N�X�`���t�@�C��6

//*************************************************************************************************************************
// �\���̒�`
//*************************************************************************************************************************
typedef enum
{
	FIELDTEXTURE_FIELD = 0,
	FIELDTEXTURE_PARK,
	FIELDTEXTURE_WALLTOP,
	FIELDTEXTURE_WALLTOP2,
	FIELDTEXTURE_PAZZLE,
	FIELDTEXTURE_HUNSUI,
	FIELDTEXTURE_MAX,
}FIELDTEXTURE;

typedef enum
{
	FIELDTEXT_FIELD_1 = 0,
	FIELDTEXT_FIELD_2,
	FIELDTEXT_FIELD_3,
	FIELDTEXT_FIELD_4,
	FIELDTEXT_FIELD_5,
	FIELDTEXT_FIELD_6,
	FIELDTEXT_FIELD_7,
	FIELDTEXT_FIELD_8,
	FIELDTEXT_FIELD_9,
	FIELDTEXT_FIELD_OTHER_1,
	FIELDTEXT_FIELD_OTHER_2,
	FIELDTEXT_FIELD_OTHER_3,
	FIELDTEXT_FIELD_OTHER_4,
	FIELDTEXT_FIELD_WALL_1,
	FIELDTEXT_FIELD_WALL_2,
	FIELDTEXT_FIELD_WALL_3,
	FIELDTEXT_FIELD_WALL_4,
	FIELDTEXT_FIELD_PAZZLE,
	FIELDTEXT_FIELD_HUNSUI,
	FIELDTEXT_MAX,
}FIELDTEXT;

typedef struct
{
	D3DXVECTOR3	pos;			// �t�B�[���h�̈ʒu
	D3DXVECTOR3	rot;			// �t�B�[���h�̌���
	D3DXVECTOR3	num;			// �t�B�[���h�̐�
	D3DXVECTOR3	fRadius;		// �t�B�[���h�̔��a
	D3DXVECTOR3	tex;			// �t�B�[���h��tex
	int			MaxVtx;			// ���_�̍ő吔
	int			MaxIdx;			// �C���f�b�N�X�̍ő吔
	int			MaxPolygon;		// �|���S���̍ő吔
	int			nTexNum;		// �e�N�X�`���ԍ�
	D3DXMATRIX	mtxWorld;		// ���[���h�}�g���b�N�X
	bool		bUse;			// �g�p���Ă��邩
}MeshField;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitMeshField(void);		// �t�B�[���h�̏���������
void UninitMeshField(void);		// �t�B�[���h�̏I������
void UpdateMeshField(void);		// �t�B�[���h�̍X�V����
void DrawMeshField(void);		// �t�B�[���h�̕`�揈��

void SetMeshField(int SetNum, int nTexNum);		// �t�B�[���h�̐ݒ菈��
MeshField *GetMeshField(void);	// �t�B�[���h�̎擾����
bool CollisionMeshField(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax);		// �t�B�[���h�̏Փˏ���
void DeleteMeshField(void);

#endif
