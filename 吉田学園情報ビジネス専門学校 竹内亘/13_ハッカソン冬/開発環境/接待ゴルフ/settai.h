//=============================================================================
//
// �^�C�g�����S�̏��� [titleLogo.h]
// Author : ���R���
//
//=============================================================================
#ifndef _SETTAI_H_
#define _SETTAI_H_

#include "main.h"
#include "gameLogo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SETTAI_LOGO_NAME		"data/TEXTURE/�ڑ҂���.png"		// ���U���g���S�̃e�N�X�`����

//=========================
// �`���[�g���A�����S�N���X
//=========================
class CSettai : public CGameLogo
{
public:
	CSettai();															// �R���X�g���N�^
	~CSettai();															// �f�X�g���N�^

	static HRESULT Load(void);													// �e�N�X�`���ǂݍ���
	static void Unload(void);													// �e�N�X�`�����

	static CSettai *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �`���[�g���A�����S����������
	void Uninit(void);															// �`���[�g���A�����S�I������
	void Update(void);															// �`���[�g���A�����S�X�V����
	void Draw(void);															// �`���[�g���A�����S�`x�揈��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
};

#endif