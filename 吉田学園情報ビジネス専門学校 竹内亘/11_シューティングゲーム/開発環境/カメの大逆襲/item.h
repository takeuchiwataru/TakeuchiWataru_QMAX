//=============================================================================
//
// �A�C�e������ [item.h]
// Author : �|���j
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ITEMSIZE (25)				// �A�C�e���̑傫��

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CItem : public CScene2D
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	typedef enum
	{// �A�C�e���̎��
		ITEMTYPE_000 = 0,	// �X�R�A
		ITEMTYPE_001,		// 2way
		ITEMTYPE_002,		// �X�s�[�hUP
		ITEMTYPE_003,		// ���g
		ITEMTYPE_MAX,
	}ITEMTYPE;

	CItem();
	~CItem();
	HRESULT Init(D3DXVECTOR3 pos, ITEMTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	ITEMTYPE GetItemType(void);

	// �ÓI�����o�֐�
	static CItem * Create(D3DXVECTOR3 pos, ITEMTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[ITEMTYPE_MAX];	// ���L�e�N�X�`���̃|�C���^

	D3DXVECTOR3				m_pos;			// �ʒu
	D3DXVECTOR3				m_move;			// �ړ���
	int						m_nLife;
	ITEMTYPE				m_nType;		// �A�C�e���̎��
	int						m_nTime;
	//static CScore * m_pScore;

};
#endif
