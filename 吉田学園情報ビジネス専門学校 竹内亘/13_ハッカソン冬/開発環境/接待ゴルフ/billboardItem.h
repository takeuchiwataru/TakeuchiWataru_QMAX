//=============================================================================
//
// �r���{�[�h�A�C�e������ [billboardItem.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARDITEM_H_
#define _BILLBOARDITEM_H_

#include "main.h"
#include "billboard.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CScene2D;

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CBillBoardItem : public CSceneBillBoard //�h���N���X
{
public:
	typedef enum
	{
		ITEMTEX_NORMAL = 0,	//�ʏ�
		ITEMTEX_MAX			//�e�N�X�`���̑���
	}ITEMTEX;

	typedef enum
	{
		ITEMMOVE_NONE = 0,
		ITEMMOVE_X,				//�ړ�X��
		ITEMMOVE_Z,				//�ړ�Z��
		ITEMMOVE_MAX			//��Ԃ̑���
	}ITEMMOVE;

	CBillBoardItem();
	~CBillBoardItem();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillBoardItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, ITEMTEX TexType, ITEMMOVE moveType);
	static HRESULT Load(void);
	static void UnLoad(void);

	bool CollisionBillboardItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[ITEMTEX_MAX];	// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	float						m_fSpin;					// ��]
	float						m_fScale;					// �g��
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X

	CSceneBillBoard				*m_pBillBoard;
	CScene2D					*m_pScene2D;

	D3DXVECTOR3					m_Scene2DPos;
	D3DXVECTOR3					m_Scene2DPosInit;
	D3DXVECTOR3					m_Scene2DMove;
	D3DXCOLOR					m_Scene2DCol;


	ITEMTEX						m_TexType;
	ITEMMOVE					m_moveType;
	bool						m_bCreate2D;
	bool						m_bGetItem;
};
#endif
