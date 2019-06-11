//=============================================================================
//
// �`���[�g���A��BG���� [tutorialbg.h]
// Author :  �|���j
//
//=============================================================================
#ifndef _TUTORIALBG_H_
#define _TUTORIALBG_H_

#include "main.h"
#include "scene2D.h"

#define MAX_2DLOGO (1)
#define MAX_TEX (1)

//*********************************************************************
// �����L���O���S�N���X�̒�`
//*********************************************************************
class CTutorialBG : public CScene2D  //�h���N���X
{
public:
	CTutorialBG();
	~CTutorialBG();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTutorialBG *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static HRESULT Load(void);
	static void UnLoad(void);

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_TEX];		// �e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3					m_pos;						// �ʒu
	D3DXVECTOR3					m_move;						// �ړ���
	D3DXVECTOR3					m_posold;					// �O��̈ʒu
	float						m_fWidth, m_fHeight;		// �� ����
	D3DXMATRIX					m_mtrxWorld;				// ���[���h�}�g���b�N�X
	CScene2D					*m_pScene2D[MAX_2DLOGO];
};
#endif
