//=============================================================================
//
// �^�C�g��BG���� [titlebg.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "titlebg.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_BG			 "data\\TEXTURE\\title_bg.png"			//�e�N�X�`���̃t�@�C����

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CTitleBG::m_pTexture[MAX_TEX] = {};

//--------------------------------------------
//���S�N���X �R���X�g���N�^
//--------------------------------------------
CTitleBG::CTitleBG()
{
	m_pos = D3DXVECTOR3(0, 0, 0);						// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);					// �O��̈ʒu
}

//--------------------------------------------
//���S�N���X �f�X�g���N�^
//--------------------------------------------
CTitleBG::~CTitleBG()
{
}

//--------------------------------------------
//���S�̐���
//--------------------------------------------
CTitleBG *CTitleBG::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTitleBG *pScene2D;

	pScene2D = new CTitleBG;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTitleBG::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	m_pScene2D[0]->BindTexture(m_pTexture[0]);


	//CManager::MODE pMode = CManager::GetMode();

	//switch (pMode)
	//{
	//case CManager::MODE_TITLE:
	//	//�^�C�g��
	//	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//	break;
	//case CManager::MODE_TUTORIAL:
	//	//�`���[�g���A��
	//	m_pScene2D[0]->BindTexture(m_pTexture[1]);
	//	break;
	//case CManager::MODE_RESULT:
	//	//���U���g
	//	m_pScene2D[0]->BindTexture(m_pTexture[2]);
	//	break;
	//case CManager::MODE_GAMEOVER:
	//	//�Q�[���I�[�o�[
	//	break;
	//case CManager::MODE_RANKING:
	//	//�����L���O
	//	m_pScene2D[0]->BindTexture(m_pTexture[3]);
	//	break;
	//}

	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTitleBG::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_2DLOGO; nCnt++)
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
void CTitleBG::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CTitleBG::Draw(void)
{

}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CTitleBG::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TITLE_BG, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CTitleBG::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
