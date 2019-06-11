//=============================================================================
//
// ���S���� [Rank.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "Rank.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\LOGO\\rank000.png"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME001			 "data\\TEXTURE\\LOGO\\rank001.png"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME002			 "data\\TEXTURE\\LOGO\\rank002.png"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME003			 "data\\TEXTURE\\LOGO\\rank003.png"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME004			 "data\\TEXTURE\\LOGO\\rank004.png"			//�e�N�X�`���̃t�@�C����

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CRank::m_pTexture[MAX_RANKTEX] = {};

//--------------------------------------------
//���S�N���X �R���X�g���N�^
//--------------------------------------------
CRank::CRank()
{
	m_pos = D3DXVECTOR3(0,0,0);						// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);					// �O��̈ʒu
}

//--------------------------------------------
//���S�N���X �f�X�g���N�^
//--------------------------------------------
CRank::~CRank()
{
}

//--------------------------------------------
//���S�̐���
//--------------------------------------------
CRank *CRank::Create(D3DXVECTOR3 pos,float fWidth, float fHeight, int nType)
{
	CRank *pScene2D;

	pScene2D = new CRank;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->m_nType = nType;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRank::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//����
	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	m_pScene2D[0]->BindTexture(m_pTexture[m_nType]);
	CManager::MODE pMode = CManager::GetMode();
	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRank::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_2DRANK; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}
	//����������(�v���C���[��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CRank::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CRank::Draw(void)
{

}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CRank::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME002, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME003, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME004, &m_pTexture[4]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CRank::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_RANKTEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CRank::SetColor(D3DXCOLOR col)
{
	m_pScene2D[0]->SetColor(col);
}
