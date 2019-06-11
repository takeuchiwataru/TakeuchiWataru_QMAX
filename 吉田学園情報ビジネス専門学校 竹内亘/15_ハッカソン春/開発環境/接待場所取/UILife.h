//=============================================================================
//
// UI���C�t���� [UILife.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _UILIFE_H_
#define _UILIFE_H_

#include "main.h"
#include "scene2D.h"

#define MAX_LIFE (3)
//*********************************************************************
//UI���C�t�N���X�̒�`
//*********************************************************************
class CUILife : public CScene2D  //�h���N���X
{
public:
	CUILife();
	~CUILife();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CUILife *Create(D3DXVECTOR3 pos,float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);
	static int GetnLife(void);
	void AddLife(int nLife);
	void MinusLife(int nLife);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[1];				// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_LIFE];
	static int					m_nLife;
};
#endif
