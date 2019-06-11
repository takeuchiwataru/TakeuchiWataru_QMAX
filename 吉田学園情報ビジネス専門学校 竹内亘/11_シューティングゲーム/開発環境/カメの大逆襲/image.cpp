//=============================================================================
//
// �摜���� [image.cpp]
// Author : �|���j
//
//=============================================================================
#include "image.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CImage::m_apTexture[IMAGE_MAX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CImage::CImage() :CLogo(3)
{

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CImage::~CImage()
{

}
//=============================================================================
// �t���[������������
//=============================================================================
HRESULT CImage::Init(D3DXVECTOR3 pos, IMAGE type)
{
	CLogo::Init(pos);

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_IMAGE);

	m_nType = type;

	// �ʒu�̐ݒu
	if (m_nType == IMAGE_TUTORIAL)
	{
		CLogo::SetPosition(pos, 150, 150);
	}
	else if (m_nType == IMAGE_TUTORIAL002)
	{
		CLogo::SetPosition(pos, 170, 50);
	}
	else
	{
		CLogo::SetPosition(pos, 50, 50);
	}

	return S_OK;
}
//=============================================================================
// �t���[���I������
//=============================================================================
void CImage::Uninit(void)
{
	CLogo::Uninit();
}
//=============================================================================
// �t���[���X�V����
//=============================================================================
void CImage::Update(void)
{

}
//=============================================================================
// �t���[���`�揈��
//=============================================================================
void CImage::Draw(void)
{
	CLogo::Draw();
}
////=============================================================================
//// ��ނ̎擾
////=============================================================================
//CImage::IMAGE CImage::GetType(void)
//{
//	return m_nType;
//}

//=============================================================================
// ����
//=============================================================================
CImage * CImage::Create(D3DXVECTOR3 pos, IMAGE type)
{
	CImage *pFrame = NULL;

	if (pFrame == NULL)
	{
		pFrame = new CImage;

		if (pFrame != NULL)
		{
			pFrame->Init(pos, type);
			pFrame->BindTexture(m_apTexture[type]);
		}
	}
	return pFrame;
}
//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CImage::Load(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, IMAGE_TEXTURE000, &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, IMAGE_TEXTURE001, &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, IMAGE_TEXTURE002, &m_apTexture[2]);
	D3DXCreateTextureFromFile(pDevice, IMAGE_TEXTURE003, &m_apTexture[3]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CImage::Unload(void)
{
	for (int nCntTex = 0; nCntTex < IMAGE_MAX; nCntTex++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}
