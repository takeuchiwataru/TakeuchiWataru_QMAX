//=============================================================================
//
// �A�C�e������ [item.h]
// Author : ��������	Sato_Asumi
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"

//=============================================================================
// ��Ԑݒ�
//=============================================================================
typedef enum
{
	ITEMTYPE_GIAR_00 = 0,
	ITEMTYPE_GIAR_01,
	ITEMTYPE_GIAR_02,
	ITEMTYPE_GIAR_03,
	ITEMTYPE_WATCH_00,
	ITEMTYPE_WATCH_01,
	ITEMTYPE_WATCH_02,
	ITEMTYPE_ORUGORU_00,
	ITEMTYPE_ORUGORU_01,
	ITEMTYPE_ORUGORU_02,
	ITEMTYPE_MAX,
}ITEMTYPE;

//=============================================================================
// �\���̂̒�`
//=============================================================================
typedef struct
{
	LPD3DXMESH			pMeshItem = NULL;		//���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		pBuffMatItem = NULL;	//�}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9	*pTextureItem = NULL;	// �e�N�X�`���ւ̃|�C���^
	DWORD				nNumMatItem = NULL;		//�}�e���A�����̐�
	D3DXVECTOR3			vtxMinItem;				//���f���̍ŏ��l
	D3DXVECTOR3			vtxMaxItem;				//���f���̍ő�l
	D3DXVECTOR3			pos;					//���S���W
	D3DXVECTOR3			OldPos;					//�O��̍��W
	D3DXVECTOR3			rot;					//����			
	D3DXMATRIX			mtxWorld;				//���[���h�}�g���b�N�X
	D3DXVECTOR3			Rot;					//��]��
	D3DXVECTOR3			CircleMax;				//�A�C�e���̍ő�l�͈̔͐ݒ�
	D3DXVECTOR3			CircleMin;				//�A�C�e���̍ŏ��l�͈̔͐ݒ�
	ITEMTYPE			type;					//�A�C�e���̎��
	int					nIdxMark;				//�e�̎g�p�ԍ�
	int					nIdxFlontPolygon[2];	//�t�����g�|���S���̎g�p�ԍ�
	int					nCntTimer;
	bool				bInPlayer;				//�͈͓��ɓ����Ă��邩�ǂ���
	bool				bUse;					//�g�p���Ă��邩�ǂ���
}Item;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);

void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEMTYPE type);
bool CollsionItem(D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax, D3DXVECTOR3 * pPos, D3DXVECTOR3 * pOldPos);
void DeleteItem(int nCntItem, ITEMTYPE type);
void AllDeleteItem(void);
int GetItem(void);
#endif
