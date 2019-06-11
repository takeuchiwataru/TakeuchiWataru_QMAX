//=============================================================================
//
// �r���{�[�h�I�u�W�F�N�g���� [billboardObject.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARDOBJECT_H_
#define _BILLBOARDOBJECT_H_

#include "main.h"
#include "billboard.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CScene2D;

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CBillBoardObject : public CSceneBillBoard //�h���N���X
{
public:
	typedef enum
	{
		TEXTYPE_TREE = 0,	//�ʏ�
		TEXTYPE_TITLE,		//�^�C�g�����S
		TEXTYPE_MAX			//�e�N�X�`���̑���
	}TEXTYPE;


	CBillBoardObject();
	~CBillBoardObject();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CBillBoardObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, TEXTYPE TexType);
	static HRESULT Load(void);
	static void UnLoad(void);

	bool CollisionBillboardObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[TEXTYPE_MAX];		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	float						m_fSpin;					// ��]
	float						m_fScale;					// �g��
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X

	CSceneBillBoard				*m_pBillBoard;

	TEXTYPE					m_TexType;
};
#endif
