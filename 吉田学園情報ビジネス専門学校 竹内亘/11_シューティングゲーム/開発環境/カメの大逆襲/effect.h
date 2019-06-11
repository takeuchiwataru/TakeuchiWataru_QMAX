//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.h]
// Author : �|���j
//
//=============================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define EFFECT_SIZE (20)				// �G�t�F�N�g�T�C�Y
#define EFFECT_LIFE (10)				// �G�t�F�N�g���C�t
#define EFFECT_RADIUS (15.0f)			// �G�t�F�N�g�̔��a

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CEffect : public CScene2D
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	CEffect();
	~CEffect();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CEffect * Create(D3DXVECTOR3 pos, D3DXCOLOR col);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3				m_move;			// �ړ���
	int						m_nLife;		// �\������
	float					m_fRadius;		// ���a
	D3DXCOLOR				m_col;			// �F
};
#endif