//=============================================================================
//
// UI�t�B�j�b�V������ [UIFinish.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIFinish.h"
#include "manager.h"
#include "number.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\Finish02.png"			//�e�N�X�`���̃t�@�C����

#define POS_WIDTH		(180)
#define POS_HEIGHT		(20)
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIFinish::m_pTexture[MAX_FINISH] = {};

//--------------------------------------------
//UI�t�B�j�b�V���N���X �R���X�g���N�^
//--------------------------------------------
CUIFinish::CUIFinish()
{
	m_pos = D3DXVECTOR3(0,0,0);					// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);				// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);			// �O��̈ʒu
	m_Col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_nItem = 0;
	m_bEnter = false;
	m_fScale = 0;
	m_ScaleCounter = 0;
}

//--------------------------------------------
//UI�t�B�j�b�V���N���X �f�X�g���N�^
//--------------------------------------------
CUIFinish::~CUIFinish()
{
}

//--------------------------------------------
//UI�t�B�j�b�V���̐���
//--------------------------------------------
CUIFinish *CUIFinish::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUIFinish *pScene2D;

	pScene2D = new CUIFinish;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUIFinish::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//NULL����
	for (int nCnt = 0; nCnt < MAX_FINISH; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	//����
	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3((m_pos.x), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//�|���S���̍X�V
	//m_pScene2D[0]->SetPos(m_pScene2D[0]->Getpos(), 3.0f, 0, D3DXCOLOR(1, 1, 1, 1));
	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	float fWidth = m_fWidth / 2;
	float fHeight = m_fHeight / 2;

	//�l�̏�����
	m_bEnter = false;
	m_ScaleCounter = 0;
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pScene2D[0]->SetColor(m_Col);
	m_nColorFlash = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUIFinish::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_FINISH; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			if (m_pScene2D[nCnt]->GetDeath() == false)
			{
				m_pScene2D[nCnt]->Uninit();

				m_pScene2D[nCnt] = NULL;
			}
		}
	}

	//����������(�v���C���[��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CUIFinish::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�W���C�p�b�h�����擾
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();

	m_fScale += 10.0f;
	if (m_fScale > 300)
	{
		m_fScale = 300;
	}

	m_pScene2D[0]->SetScale(m_fScale);

}

//=============================================================================
// �`�揈��
//=============================================================================
void CUIFinish::Draw(void)
{
}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CUIFinish::Load(void)
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
void CUIFinish::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_FINISH; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
