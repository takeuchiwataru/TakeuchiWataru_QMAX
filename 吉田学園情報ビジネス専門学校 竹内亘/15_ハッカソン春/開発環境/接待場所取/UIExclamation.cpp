//=============================================================================
//
// UI�r�b�N������ [UIExclamation.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIExclamation.h"
#include "manager.h"
#include "number.h"
#include "fade.h"
#include "enemy.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\Exclamation.png"			//�e�N�X�`���̃t�@�C����

#define POS_WIDTH		(180)
#define POS_HEIGHT		(20)
#define UI_TIMERNORMAL	(10)
#define UI_TIMERRED		(20)

#define ENEMYCREATE_TIMER (120)

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIExclamation::m_pTexture[MAX_EXCLAMATION] = {};

//--------------------------------------------
//UI�r�b�N���N���X �R���X�g���N�^
//--------------------------------------------
CUIExclamation::CUIExclamation()
{
	m_pos = D3DXVECTOR3(0,0,0);					// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);				// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);			// �O��̈ʒu
	m_Col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_nItem = 0;
	m_bEnter = false;
	m_fScale = 0;
	m_nColorFlash = 0;
	m_ScaleCounter = 0;
	m_EnemyCreateCnt = 0;
	m_EnemyPosType = ENEMYPOS_CENTER;
}

//--------------------------------------------
//UI�r�b�N���N���X �f�X�g���N�^
//--------------------------------------------
CUIExclamation::~CUIExclamation()
{
}

//--------------------------------------------
//UI�r�b�N���̐���
//--------------------------------------------
CUIExclamation *CUIExclamation::Create(D3DXVECTOR3 pos,float fWidth, float fHeight, ENEMYPOS type)
{
	CUIExclamation *pScene2D;

	pScene2D = new CUIExclamation;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->m_EnemyPosType = type;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUIExclamation::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//NULL����
	for (int nCnt = 0; nCnt < MAX_EXCLAMATION; nCnt++)
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
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0, 1.0, 1.0, 1.0);
	m_ScaleCounter = 0;
	m_nColorFlash = 0;
	m_EnemyCreateCnt = 0;


	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);

	pSound->PlaySound(pSound->SOUND_LABEL_SE_WARNING);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUIExclamation::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_EXCLAMATION; nCnt++)
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
void CUIExclamation::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�W���C�p�b�h�����擾
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();

	//�J�E���^�[���Z
	m_nColorFlash++;
	if (m_nColorFlash <= UI_TIMERNORMAL)
	{
		m_Col.r = 1.0f;
		m_Col.g = 1.0f;
		m_Col.b = 0.0f;
	}
	else if (m_nColorFlash >= UI_TIMERNORMAL + 1 && m_nColorFlash <= UI_TIMERRED)
	{
		m_Col.g = 0.0f;
		m_Col.b = 0.0f;
	}
	else if (m_nColorFlash > UI_TIMERRED)
	{
		m_nColorFlash = 0;
	}
	m_pScene2D[0]->SetColor(m_Col);

	//�G�̐���
	m_EnemyCreateCnt++;
	if (m_EnemyCreateCnt > ENEMYCREATE_TIMER)
	{
		//�v���C���[���擾
		CPlayer *pPlayer = CGame::GetPlayer();

		switch (m_EnemyPosType)
		{
		case ENEMYPOS_CENTER:
			CEnemy::Create(D3DXVECTOR3(pPlayer->GetPos().x, 0, pPlayer->GetPos().z - 200), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0), 10);
			break;
		case ENEMYPOS_RIGHT:
			CEnemy::Create(D3DXVECTOR3(pPlayer->GetPos().x + 70, 0, pPlayer->GetPos().z - 200), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0), 10);
			break;
		case ENEMYPOS_LEFT:
			CEnemy::Create(D3DXVECTOR3(pPlayer->GetPos().x - 70, 0, pPlayer->GetPos().z - 200), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0), 10);
			break;
		}
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUIExclamation::Draw(void)
{
}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CUIExclamation::Load(void)
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
void CUIExclamation::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_EXCLAMATION; nCnt++)
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
// �r�b�N���̊l���̃t���O�ݒ�
//=============================================================================
void CUIExclamation::SetItemBool(bool bGetItem)
{
	m_bEnter = bGetItem;
}
