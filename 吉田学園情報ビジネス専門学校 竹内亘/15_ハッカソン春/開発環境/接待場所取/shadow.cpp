//=============================================================================
//
// �e�̏��� [polygon.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			"data\\TEXTURE\\EFFECT\\particle000.jpg"	//�e�N�X�`���̃t�@�C����
#define TEXTURENAME001			"data\\TEXTURE\\EFFECT\\shadow000.jpg"		//�e�N�X�`���̃t�@�C����
#define TEX_POS_X_INIT			(1.0f)		//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)		//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)		//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)		//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)		//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)		//�e�N�X�`�����WV��

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CShadow::m_pTexture[SHADOWTYPE_MAX] = {};

//--------------------------------------------
//�V�[��3D�N���X �R���X�g���N�^
//--------------------------------------------
CShadow::CShadow()
{
	m_pos = D3DXVECTOR3(0,0,0);			//�ʒu
	m_rot = D3DXVECTOR3(0, 0, 0);		//����
	D3DXMatrixIdentity(&m_mtxWorld);	//���[���h�}�g���b�N�X
	m_Type = SHADOWTYPE_NORMAL;
}

//--------------------------------------------
//�V�[��3D�N���X �f�X�g���N�^
//--------------------------------------------
CShadow::~CShadow()
{
}

//=============================================================================
// ��������
//=============================================================================
CShadow * CShadow::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, D3DXCOLOR col, CShadow::SHADOWTYPE type)
{
	CShadow *pShadow;

	pShadow = new CShadow;

	pShadow->m_pos = pos;
	pShadow->m_fWidth = fWidth;
	pShadow->m_fDepth = fDepth;
	pShadow->m_col = col;
	pShadow->m_Type = type;
	pShadow->Init();

	return pShadow;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShadow::Init(void)
{
	m_pScene3D = CScene3D::Create(m_pos, m_col, m_fWidth, m_fDepth);

	m_pScene3D->BindTexture(m_pTexture[m_Type]);
	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene3D->SetObjType(CScene::OBJTYPE_SHADOW);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShadow::Uninit(void)
{
	if (m_pScene3D != NULL)
	{
		m_pScene3D->Uninit();
		m_pScene3D = NULL;
	}
	//����������(�V�[��3D��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CShadow::Update(void)
{
	if (m_pScene3D != NULL)
	{
		m_pScene3D->Setpos(m_pos);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CShadow::Draw(void)
{

}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CShadow::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CShadow::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < SHADOWTYPE_MAX; nCnt++)
	{	// �e�N�X�`���̔j��
		m_pTexture[nCnt] = NULL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CShadow::UnLoad(void)
{
	for (int nCnt = 0; nCnt < SHADOWTYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
