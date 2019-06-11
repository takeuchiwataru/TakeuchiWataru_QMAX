//=============================================================================
//
// �����L���OBG���� [rankingbg.h]
// Author :  �|���j
//
//=============================================================================
#ifndef _RANKINGBG_H_
#define _RANKINGBG_H_

#include "main.h"
#include "scene2D.h"

#define MAX_2DLOGO (1)
#define MAX_TEX (1)

//*********************************************************************
// �����L���O���S�N���X�̒�`
//*********************************************************************
class CRankingBG : public CScene2D  //�h���N���X
{
public:
	CRankingBG();
	~CRankingBG();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CRankingBG *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
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
