//=========================================================================================================================
//
// �I�u�W�F�N�g���� [xobjectr.h]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================
#ifndef _XOBJECT_H_
#define _XOBJECT_H_

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define XOBJECT_TEXT_NAME			(255)				
#define XOBJECT_TEXT_INFO			"data\\TEXT\\objectdata.ini"

//*************************************************************************************************************************
// �\���̒�`
//*************************************************************************************************************************
typedef enum
{
	TEXTTYPE_SEARCH_HOUSE_0 = 0,
	TEXTTYPE_SEARCH_HOUSE_1,
	TEXTTYPE_SEARCH_HOUSE_2,
	TEXTTYPE_SEARCH_HOUSE_3,
	TEXTTYPE_SEARCH_HOUSE_4,
	TEXTTYPE_SEARCH_HOUSE_5,
	TEXTTYPE_SEARCH_HOUSE_6,
	TEXTTYPE_SEARCH_HOUSE_7,
	TEXTTYPE_SEARCH_HOUSE_8,
	TEXTTYPE_PUZZLE_1,
	TEXTTYPE_PUZZLE_1_A,
	TEXTTYPE_PUZZLE_1_W,
	TEXTTYPE_PUZZLE_2,
	TEXTTYPE_PUZZLE_2_A,
	TEXTTYPE_PUZZLE_2_W,
	TEXTTYPE_PUZZLE_3,
	TEXTTYPE_PUZZLE_3_A,
	TEXTTYPE_PUZZLE_3_W,
	TEXTTYPE_MAX
}TEXTTYPE;

typedef struct
{
	int modelNum[8];
}PAZZLENUM;


typedef struct
{
	char						FileName[XOBJECT_TEXT_NAME];	// X�t�@�C����
	LPDIRECT3DTEXTURE9			*pTexture = NULL;				// �e�N�X�`�����ւ̃|�C���^
	LPD3DXMESH					pMesh = NULL;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER				pBuffMat = NULL;				// �}�e���A�����ւ̃|�C���^
	DWORD						nNumMat = NULL;					// �}�e���A�����̐�
	int							nMaxModel;						// ���f���̍ő吔
	int							nOya;							// �e�q�֌W
	D3DXVECTOR3					Initpos;						// �����ʒu
	D3DXVECTOR3					pos;							// ���݈ʒu
	D3DXVECTOR3					posOld;							// ���݈ʒu
	D3DXVECTOR3					move;							// �ړ�
	D3DXVECTOR3					Initrot;						// ��������
	D3DXVECTOR3					rotDest;						// �ڕW����
	D3DXVECTOR3					rot;							// ���݌���
	D3DXVECTOR3					vtxMin;							// ���_�̍ŏ��l
	D3DXVECTOR3					vtxMax;							// ���_�̍ő�l
	D3DXCOLOR					col;							// �F
	D3DXMATRIX					mtxWorld;						// ���[���h�}�g���b�N�X
	int							nIdxShadow;						// �e�ԍ�
	bool						bUse;							// �g�p���Ă��邩
}XOBJECT;

typedef struct
{
	char						FileName[XOBJECT_TEXT_NAME];	// X�t�@�C����
}XOBJECTINI;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitXObject(void);				// �I�u�W�F�N�g����������
void UninitXObject(void);			// �I�u�W�F�N�g�I������
void UpdateXObject(void);			// �I�u�W�F�N�g�X�V����
void DrawXObject(void);				// �I�u�W�F�N�g�`�揈��

void SetXObject(TEXTTYPE type);		// �I�u�W�F�N�g�ݒ菈��
XOBJECT *GetXObject(void);			// �I�u�W�F�N�g�擾����
bool CollisionXObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax);
bool PuzzleSeting(char *pName, D3DXVECTOR3 *pPos, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax);
void SetMovePazzelObj(int nNum);
PAZZLENUM *GetPazzleNum(void);
void DeleteXObject(void);
void DeleteXObject(int nCntXObject, int nCntXObjectModel);
#endif
