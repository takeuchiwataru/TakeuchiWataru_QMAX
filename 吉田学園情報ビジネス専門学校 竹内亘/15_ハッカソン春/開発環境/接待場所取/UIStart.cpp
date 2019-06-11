//=============================================================================
//
// UI�X�^�[�g���� [UIStart.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIStart.h"
#include "manager.h"
#include "number.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\Countdown00.png"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME001			 "data\\TEXTURE\\UI\\Countdown01.png"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME002			 "data\\TEXTURE\\UI\\Countdown02.png"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME003			 "data\\TEXTURE\\UI\\Countdown03.png"			//�e�N�X�`���̃t�@�C����

#define POS_WIDTH		(180)
#define POS_HEIGHT		(20)
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIStart::m_pTexture[MAX_START] = {};

//--------------------------------------------
//UI�X�^�[�g�N���X �R���X�g���N�^
//--------------------------------------------
CUIStart::CUIStart()
{
	m_pos = D3DXVECTOR3(0,0,0);					// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);				// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);			// �O��̈ʒu
	m_Col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_nItem = 0;
	m_bCntDown = false;
	m_fScale = 0;
	m_ScaleCounter = 0;
	m_nType = 0;
}

//--------------------------------------------
//UI�X�^�[�g�N���X �f�X�g���N�^
//--------------------------------------------
CUIStart::~CUIStart()
{
}

//--------------------------------------------
//UI�X�^�[�g�̐���
//--------------------------------------------
CUIStart *CUIStart::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUIStart *pScene2D;

	pScene2D = new CUIStart;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUIStart::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//NULL����
	for (int nCnt = 0; nCnt < MAX_START; nCnt++)
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
	m_bCntDown = false;
	m_ScaleCounter = 0;
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pScene2D[0]->SetColor(m_Col);
	m_nColorFlash = 0;
	m_nType = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUIStart::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_START; nCnt++)
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
void CUIStart::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�W���C�p�b�h�����擾
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//�T�E���h
	CSound *pSound = CManager::GetSound(0);

	if (m_bCntDown == true)
	{
		if (m_nType < MAX_START)
		{
			m_pScene2D[0]->BindTexture(m_pTexture[m_nType]);
			if (m_nType < 3)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_START00);
			}
			else if (m_nType == 3)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_START01);
			}
			m_bCntDown = false;
		}
	}

	//�傫���ω�
	m_fScale += 5.0f;
	//�����x�グ
	if (m_fScale > 200 && m_fScale <= 250)
	{
		//�J�E���^�[���Z
		if (m_bCntDown == false)
		{
			m_Col.a -= 0.1f;
		}
	}
	//�傫���ő�
	if (m_fScale > 300)
	{
		m_fScale = 300;
		if (m_nType < 3)
		{
			m_bCntDown = true;
		}
		if (m_nType < MAX_START - 1)
		{
			m_nType += 1;
			m_fScale = 0;
			m_Col.a = 1.0f;
		}
	}
	//�F�E�傫���X�V
	m_pScene2D[0]->SetColor(m_Col);
	m_pScene2D[0]->SetScale(m_fScale);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUIStart::Draw(void)
{
}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CUIStart::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME002, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME003, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CUIStart::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_START; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
