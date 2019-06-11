//=============================================================================
//
// UI�G���^�[���� [UIPressEnter.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIPressEnter.h"
#include "manager.h"
#include "number.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\press_enter.png"			//�e�N�X�`���̃t�@�C����

#define POS_WIDTH		(180)
#define POS_HEIGHT		(20)
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIPressEnter::m_pTexture[MAX_PRESSENTER] = {};

//--------------------------------------------
//UI�G���^�[�N���X �R���X�g���N�^
//--------------------------------------------
CUIPressEnter::CUIPressEnter()
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
//UI�G���^�[�N���X �f�X�g���N�^
//--------------------------------------------
CUIPressEnter::~CUIPressEnter()
{
}

//--------------------------------------------
//UI�G���^�[�̐���
//--------------------------------------------
CUIPressEnter *CUIPressEnter::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUIPressEnter *pScene2D;

	pScene2D = new CUIPressEnter;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUIPressEnter::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//NULL����
	for (int nCnt = 0; nCnt < MAX_PRESSENTER; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	//����
	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3((m_pos.x), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	float fWidth = m_fWidth / 2;
	float fHeight = m_fHeight / 2;

	//�l�̏�����
	m_bEnter = false;
	m_ScaleCounter = 0;
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_nColorFlash = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUIPressEnter::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PRESSENTER; nCnt++)
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
void CUIPressEnter::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�W���C�p�b�h�����擾
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();

	//�J�E���^�[���Z
	if (m_bEnter == false)
	{
		m_ScaleCounter++;
		if (m_ScaleCounter <= 40)
		{
			m_Col.a -= 0.015f;
		}
		else if (m_ScaleCounter >= 41 && m_ScaleCounter <= 80)
		{
			m_Col.a += 0.025f;
			if (m_Col.a > 1.0f)
			{
				m_Col.a = 1.0f;
			}
		}
		else if (m_ScaleCounter > 80)
		{
			m_ScaleCounter = 0;
		}
		m_pScene2D[0]->SetColor(m_Col);
	}

	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		m_bEnter = true;
		m_Col.r = 1.0f;
		m_Col.g = 1.0f;
		m_Col.b = 1.0f;
		m_Col.a = 1.0f;

		m_pScene2D[0]->SetColor(m_Col);
	}

	if (m_bEnter == true)
	{
		m_nColorFlash++;
		if (m_nColorFlash <= 5)
		{
			m_Col.r = 1.0f;
			m_Col.g = 1.0f;
			m_Col.b = 1.0f;
		}
		else if (m_nColorFlash >= 6 && m_nColorFlash <= 10)
		{
			m_Col.r = 1.0f;
			m_Col.g = 0.0f;
			m_Col.b = 0.0f;
		}
		else if(m_nColorFlash > 10)
		{
			m_nColorFlash = 0;
		}
		m_pScene2D[0]->SetColor(m_Col);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUIPressEnter::Draw(void)
{
}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CUIPressEnter::Load(void)
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
void CUIPressEnter::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_PRESSENTER; nCnt++)
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
// �G���^�[�̊l���̃t���O�ݒ�
//=============================================================================
void CUIPressEnter::SetItemBool(bool bGetItem)
{
	m_bEnter = bGetItem;
}
