//=============================================================================
//
// �p�[�e�B�N���̏��� [particle.h]
// Author : �|���j
//
//=============================================================================
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PARTICLE_SIZE (20)				// �G�t�F�N�g�T�C�Y
#define PARTICLE_LIFE (10)				// �G�t�F�N�g���C�t
#define PARTICLE_RADIUS (15)			// �G�t�F�N�g�̔��a

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CParticle : public CScene2D
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	CParticle();
	~CParticle();
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move,int life,int radius);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CParticle * Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int life, int radius);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3				m_move;			// �ړ���
	int						m_nLife;		// �\������
	int					m_nRadius;			// ���a
	D3DXCOLOR				m_col;			// �F
};
#endif