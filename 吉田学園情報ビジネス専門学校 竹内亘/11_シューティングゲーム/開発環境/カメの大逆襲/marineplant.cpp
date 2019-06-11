//=============================================================================
//
// �C������ [marineplant.cpp]
// Author : �|���j
//
//=============================================================================
#include "marineplant.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "explosion.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CMarinePlant::m_apTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMarinePlant::CMarinePlant():CScene2D(4)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMarinePlant::~CMarinePlant()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CMarinePlant::Init(D3DXVECTOR3 pos)
{
	CScene2D::InitAnim(pos);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_MAEINAPLANT);

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, MARINESIZE, MARINESIZE);

	// ���̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 3;

	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CMarinePlant::Uninit(void)
{
	CScene2D::Uninit();
}
//=============================================================================
// �X�V����
//=============================================================================
void CMarinePlant::Update(void)
{
	D3DXVECTOR3 pos;		// �ʒu

	// �L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// �ʒu�̎擾
	pos = CScene2D::GetPosition();

	pos += m_move;
	m_move.y = 1 * 1;

	// �C���̃A�j���[�V����
	m_nCounterAnim++;

	if ((m_nCounterAnim % 30) == 0)
	{// �p�^�[��No.�X�V
		m_nPatternAnim = (m_nPatternAnim + 1) % 2;

		SetPattern2(m_nPatternAnim);
	}

	// �ʒu�̐ݒu
	CScene2D::SetPosition(pos, MARINESIZE, MARINESIZE);
}
//=============================================================================
// �`�揈��
//=============================================================================
void CMarinePlant::Draw(void)
{
	CScene2D::Draw();
}
//=============================================================================
// �G�̐���
//=============================================================================
CMarinePlant * CMarinePlant::Create(D3DXVECTOR3 pos)
{
	CMarinePlant *pMarinePlant = NULL;

	if (pMarinePlant == NULL)
	{
		pMarinePlant = new CMarinePlant;

		if (pMarinePlant != NULL)
		{
			pMarinePlant->Init(pos);
			pMarinePlant->BindTexture(m_apTexture);
		}
	}
	return pMarinePlant;
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CMarinePlant::Load(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, MARINE_TEXTURE_000, &m_apTexture);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CMarinePlant::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_apTexture != NULL)
	{
		m_apTexture->Release();
		m_apTexture = NULL;
	}
}
