//=============================================================================
//
// UI���C�t���� [UILife.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UILife.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\life001.png"			//�e�N�X�`���̃t�@�C����

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUILife::m_pTexture[1] = {};
int							CUILife::m_nLife = 3;
//--------------------------------------------
//UI���C�t�N���X �R���X�g���N�^
//--------------------------------------------
CUILife::CUILife()
{
	m_pos = D3DXVECTOR3(0,0,0);						// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);				// �O��̈ʒu
	m_nLife = 3;
}

//--------------------------------------------
//UI���C�t�N���X �f�X�g���N�^
//--------------------------------------------
CUILife::~CUILife()
{
}

//--------------------------------------------
//UI���C�t�̐���
//--------------------------------------------
CUILife *CUILife::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUILife *pScene2D;

	pScene2D = new CUILife;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUILife::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		m_pScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3((m_pos.x + (m_fWidth + 25)* nCnt), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
		m_pScene2D[nCnt]->BindTexture(m_pTexture[0]);
		//�I�u�W�F�N�g��ނ̐ݒ�
		m_pScene2D[nCnt]->SetObjType(CScene::OBJTYPE_SCENE2D);
	}

	m_nLife = 3;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUILife::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_LIFE; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}
	//����������
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CUILife::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CUILife::Draw(void)
{
}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CUILife::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CUILife::UnLoad(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
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
// ���C�t�擾����
//=============================================================================
int CUILife::GetnLife(void)
{
	return m_nLife;
}

//=============================================================================
// ���C�t���Z����
//=============================================================================
void CUILife::AddLife(int nLife)
{
	m_nLife += nLife;

	if (m_nLife > MAX_LIFE - 1)
	{
		m_nLife = MAX_LIFE - 1;
	}

	m_pScene2D[m_nLife]->SetbDraw(true);
}

//=============================================================================
// ���C�t���Z����
//=============================================================================
void CUILife::MinusLife(int nLife)
{
	m_nLife -= nLife;

	if (m_nLife < 0)
	{
		m_nLife = 0;
	}

	m_pScene2D[m_nLife]->SetbDraw(false);
}
