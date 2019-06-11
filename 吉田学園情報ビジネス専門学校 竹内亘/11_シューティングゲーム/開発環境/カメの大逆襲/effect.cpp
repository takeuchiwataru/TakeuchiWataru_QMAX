//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : �|���j
//
//=============================================================================
#include "effect.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "explosion.h"
#include "enemy.h"
#include "score.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect():CScene2D(2)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_EFFECT);

	CScene2D::Init(pos);

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, 10, 10);

	// ���̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = EFFECT_LIFE;
	m_fRadius = EFFECT_RADIUS;
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	CScene2D::SetColor(m_col);

	CScene2D::SetEffect(m_fRadius);

	m_fRadius -= 2.0f;

	m_nLife--;

	if (m_nLife <= 0 ||m_fRadius == 10)
	{
  		Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============================================================================
// �G�t�F�N�g�̐���
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos,D3DXCOLOR col)
{
	CEffect *pEffect = NULL;

	if (pEffect == NULL)
	{
		pEffect = new CEffect;

		if (pEffect != NULL)
		{
			pEffect->Init(pos);
			pEffect->m_col = col;
			pEffect->BindTexture(m_pTexture);
		}
	}
	return pEffect;
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CEffect::Load(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, EFFECT_TEXTURE_000, &m_pTexture);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CEffect::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}