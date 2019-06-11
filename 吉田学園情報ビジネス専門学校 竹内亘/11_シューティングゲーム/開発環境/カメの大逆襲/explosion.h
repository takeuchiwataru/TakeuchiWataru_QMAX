//=============================================================================
//
// �����̏��� [explosion.h]
// Author : �|���j
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CExplosion : public CScene2D
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	CExplosion();
	~CExplosion();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CExplosion * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`���̃|�C���^
	D3DXVECTOR3				m_move;			// �ړ���
	int						m_nCounterAnim;	// �A�j���[�V�����J�E���^�[
	int						m_nPatternAnim;	// �A�j���V�����p�^�[��
};
#endif