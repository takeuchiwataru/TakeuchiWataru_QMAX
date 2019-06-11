//=============================================================================
//
// �����N���� [Rank.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _RANK_H_
#define _RANK_H_

#include "main.h"
#include "scene2D.h"

#define MAX_2DRANK (1)
#define MAX_RANKTEX (5)

//*********************************************************************
//UI���C�t�N���X�̒�`
//*********************************************************************
class CRank : public CScene2D  //�h���N���X
{
public:
	CRank();
	~CRank();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRank *Create(D3DXVECTOR3 pos,float fWidth, float fHeight,int nType);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetColor(D3DXCOLOR col);
private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_RANKTEX];	// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_2DRANK];
	D3DXCOLOR					m_Col;
	int							m_nType;
};
#endif
