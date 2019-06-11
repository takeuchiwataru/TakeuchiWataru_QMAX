//=============================================================================
//
// �C������ [marineplant.h]
// Author : �|���j
//
//=============================================================================
#ifndef _MARINEPLANT_H_
#define _MARINEPLANT_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MARINESIZE (25)				// �C���̑傫��

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CMarinePlant : public CScene2D
{// �h�������鎞�� : public �`�����ɂ��Ă��
public:
	CMarinePlant();
	~CMarinePlant();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CMarinePlant * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture;	// ���L�e�N�X�`���̃|�C���^

	D3DXVECTOR3				m_pos;			// �ʒu
	D3DXVECTOR3				m_move;			// �ړ���
	int						m_nLife;
	int						m_nCounterAnim;	// �A�j���[�V�����J�E���^�[
	int						m_nPatternAnim;	// �A�j���V�����p�^�[��

	CScene2D * m_apScene2D;
};
#endif