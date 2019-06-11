//=============================================================================
//
// UI�`���[�g���A������ [2DTUTO.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "2DTuto.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TUTORIALBG000_TEXTURENAME	"data/TEXTURE/TUTORIAL/tutorial.png"	//�e�N�X�`���̃t�@�C����
#define TUTORIALBG001_TEXTURENAME	"data/TEXTURE/TUTORIAL/tutorial001.jpg"	//�e�N�X�`���̃t�@�C����
#define TUTORIALBG002_TEXTURENAME	"data/TEXTURE/TUTORIAL/GameStart000.png"	//�e�N�X�`���̃t�@�C����

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			C2DTUTO::m_pTexture[MAX_2DTUTO] = {};

//--------------------------------------------
//UI�`���[�g���A���N���X �R���X�g���N�^
//--------------------------------------------
C2DTUTO::C2DTUTO()
{
	m_pos = D3DXVECTOR3(0,0,0);						// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);				// �O��̈ʒu

}

//--------------------------------------------
//UI�`���[�g���A���N���X �f�X�g���N�^
//--------------------------------------------
C2DTUTO::~C2DTUTO()
{
}

//--------------------------------------------
//UI�`���[�g���A���̐���
//--------------------------------------------
C2DTUTO *C2DTUTO::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	C2DTUTO *pScene2D;

	pScene2D = new C2DTUTO;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT C2DTUTO::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT /2, m_pos.z), SCREEN_WIDTH / 1.4f,SCREEN_HEIGHT / 1.4f);
	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(230.0f, 470.0f, m_pos.z), 320, 160);
	//m_pScene2D[1]->BindTexture(m_pTexture[1]);
	////�I�u�W�F�N�g��ނ̐ݒ�
	//m_pScene2D[1]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(920.0f, 70.0f, m_pos.z), 500, 100);
	//m_pScene2D[2]->BindTexture(m_pTexture[2]);
	////�I�u�W�F�N�g��ނ̐ݒ�
	//m_pScene2D[2]->SetObjType(CScene::OBJTYPE_SCENE2D);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void C2DTUTO::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_2DTUTO; nCnt++)
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
void C2DTUTO::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void C2DTUTO::Draw(void)
{

}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT C2DTUTO::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < MAX_2DTUTO; nCnt++)
	{
		m_pTexture[nCnt] = NULL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TUTORIALBG000_TEXTURENAME, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TUTORIALBG001_TEXTURENAME, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TUTORIALBG002_TEXTURENAME, &m_pTexture[2]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void C2DTUTO::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_2DTUTO; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
