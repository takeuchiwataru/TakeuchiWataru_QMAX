//=============================================================================
//
// �p�[�e�B�N���̏��� [particle.cpp]
// Author : �|���j
//
//=============================================================================
#include "particle.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CParticle::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CParticle::CParticle():CScene2D(2)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CParticle::~CParticle()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CParticle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, int life, int radius)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PARTICLE);

	CScene2D::Init(pos);

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, 10, 10);

	// ���̏�����
	m_move = move;
	m_nLife = life;
	m_nRadius = radius;
	m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CParticle::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CParticle::Update(void)
{
	m_nLife--;

	m_nRadius -= m_nRadius / m_nLife;

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CScene2D::GetPosition();

	pos -= m_move;

	CScene2D::SetColor(m_col);

	CScene2D::SetParticle(m_nRadius,pos);

	if (m_nLife <= 0 || m_nRadius == 10)
	{
		Uninit();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CParticle::Draw(void)
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
// �p�[�e�B�N���̐���
//=============================================================================
CParticle * CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, int life, int radius)
{
	CParticle *pParticle = NULL;

	if (pParticle == NULL)
	{
		pParticle = new CParticle;

		if (pParticle != NULL)
		{
			pParticle->Init(pos,move,life,radius);
			//pParticle->m_col = col;
			pParticle->BindTexture(m_pTexture);
		}
	}
	return pParticle;
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CParticle::Load(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, PARTICLE_TEXTURE_000, &m_pTexture);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CParticle::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}