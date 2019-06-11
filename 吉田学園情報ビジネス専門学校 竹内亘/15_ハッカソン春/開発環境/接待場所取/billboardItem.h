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
#include "shadow.h"

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

	CBillBoardItem();
	~CBillBoardItem();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillBoardItem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, ITEMTEX TexType);
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
	CSceneBillBoard				*m_pBillBoard;				// �r���{�[�h�ւ̃|�C���^
	CScene2D					*m_pScene2D;				// 2D�|���S���ւ̃|�C���^
	D3DXVECTOR3					m_Scene2DPos;				// 2D�|���S���̈ʒu
	D3DXVECTOR3					m_Scene2DPosInit;			// 2D�|���S���̏����ʒu
	D3DXVECTOR3					m_Scene2DMove;				// 2D�|���S���̈ړ���
	D3DXCOLOR					m_Scene2DCol;				// 2D�|���S���̐F
	ITEMTEX						m_TexType;					// �e�N�X�`���̎��
	bool						m_bCreate2D;				// 2D���N���G�C�g���ꂽ���̃t���O
	bool						m_bGetItem;					// �A�C�e���擾��Ԃ̃t���O
	CShadow						*m_pShadow;					// �e�ւ̃|�C���^
};
#endif
