//=============================================================================
//
// UI���C�t���� [Logo.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"
#include "scene2D.h"

#define MAX_2DLOGO (1)
#define MAX_LOGOTEX (4)

//*********************************************************************
//UI���C�t�N���X�̒�`
//*********************************************************************
class CLogo : public CScene2D  //�h���N���X
{
public:
	CLogo();
	~CLogo();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CLogo *Create(D3DXVECTOR3 pos,float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);
	void SetColor(D3DXCOLOR col);
private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_LOGOTEX];	// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		//�� ����
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_2DLOGO];
	D3DXCOLOR					m_Col;
};
#endif
