//=============================================================================
//
// UI�A�C�e������ [UIItem.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UIITEM_H_
#define _UIITEM_H_

#include "main.h"
#include "scene2D.h"

#define MAX_ITEM (1)
#define MAX_ITEMNUM (3)

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CNumber;

//*********************************************************************
//UI�A�C�e���N���X�̒�`
//*********************************************************************
class CUIItem : public CScene2D  //�h���N���X
{
public:
	CUIItem();
	~CUIItem();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUIItem *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);

	void PlusItem(int nAddItem);
private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[1];				// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_ITEM];
	CNumber						*m_apNumber[MAX_ITEMNUM];	//
	int							m_nItem;
};
#endif
