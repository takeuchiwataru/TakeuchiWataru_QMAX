//=============================================================================
//
// UI�`���[�g���A������ [2DTUTO.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _2DTUTO_H_
#define _2DTUTO_H_

#include "main.h"
#include "scene2D.h"

#define MAX_2DTUTO (1)
//*********************************************************************
//UI�`���[�g���A���N���X�̒�`
//*********************************************************************
class C2DTUTO : public CScene2D  //�h���N���X
{
public:
	C2DTUTO();
	~C2DTUTO();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static C2DTUTO *Create(D3DXVECTOR3 pos,float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_2DTUTO];		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_2DTUTO];
};
#endif
