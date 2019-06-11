//=============================================================================
//
// �r���{�[�h�̓G���� [billboardEnemy.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARDENEMY_H_
#define _BILLBOARDENEMY_H_

#include "main.h"
#include "billboard.h"

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CBillBoardEnemy : public CSceneBillBoard //�h���N���X
{
public:
	typedef enum
	{
		ENEMYTEX_HUMAN000 = 0,	//�l��
		ENEMYTEX_MAX			//�e�N�X�`���̑���
	}ENEMYTEX;

	typedef enum
	{
		ENEMYMOVE_NONE = 0,
		ENEMYMOVE_X,			//�ړ�X��
		ENEMYMOVE_Z,			//�ړ�Z��
		ENEMYMOVE_MAX			//��Ԃ̑���
	}ENEMYMOVE;

	CBillBoardEnemy();
	~CBillBoardEnemy();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillBoardEnemy *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, ENEMYTEX TexType, ENEMYMOVE moveType);
	static HRESULT Load(void);
	static void UnLoad(void);

	bool CollisionBillboardEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[ENEMYTEX_MAX];	// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;	//�� ����
	D3DXMATRIX					m_mtrxWorld;			// ���[���h�}�g���b�N�X
	CSceneBillBoard				*m_pBillBoard;

	ENEMYTEX					m_TexType;
	ENEMYMOVE					m_moveType;
};
#endif
