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

#define MAX_ITEM2D (2)
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
	int GetItemNum(void);
	void SetItemBool(bool bGetItem);
private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_ITEM2D];		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_ITEM2D];	// 2D�|���S���ւ̃|�C���^
	CNumber						*m_apNumber[MAX_ITEMNUM];	// �����ւ̃|�C���^
	int							m_nItem;					// �l����
	bool						m_bGetItem;					// �擾���
	float						m_fScale;					// �g��k����
	int							m_ScaleCounter;				// �g��k���̃J�E���^�[
};
#endif
