//=============================================================================
//
// �����̏��� [exsplosion.h]
// Author : Yamashita
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"
#include "scene2D.h"

//�}�N����`
#define MAX_COUNTER (5)
#define MAX_PATTERN (4)
//#define EXPLOSION_UV_U (1.0f)
//#define EXPLOSION_UV_V (0.25f)

class Manager;

//�G�N�X�v���[�W�����N���X�i�V�[��2D�h���j
class CExplosion : public CScene2D
{
public:
	CExplosion();
	~CExplosion();

	HRESULT Init(D3DXVECTOR3 pos,D3DXCOLOR col);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	//�ÓI�����o�֐�
	static CExplosion *Create(D3DXVECTOR3 pos,D3DXCOLOR col);
	static HRESULT Load(void);						//�e�N�X�`���ǂݍ���
	static void Unload(void);
	
private:
//	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXCOLOR m_col;								//�F
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture;

	int m_nCounterAnim;								//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;								//�A�j���[�V�����p�^�[��NO
	D3DXVECTOR3 m_pos;

	
};
#endif
