//=============================================================================
//
// UI�A�C�e������ [UIItem.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIItem.h"
#include "manager.h"
#include "number.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\CAN2D.png"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME001			 "data\\TEXTURE\\UI\\ITEMLOGO.png"		//�e�N�X�`���̃t�@�C����

#define POS_WIDTH		(180)
#define POS_HEIGHT		(20)
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIItem::m_pTexture[MAX_ITEM2D] = {};

//--------------------------------------------
//UI�A�C�e���N���X �R���X�g���N�^
//--------------------------------------------
CUIItem::CUIItem()
{
	m_pos = D3DXVECTOR3(0,0,0);						// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);				// �O��̈ʒu
	m_nItem = 0;
	m_bGetItem = false;
	m_fScale = 0;
	m_ScaleCounter = 0;
}

//--------------------------------------------
//UI�A�C�e���N���X �f�X�g���N�^
//--------------------------------------------
CUIItem::~CUIItem()
{
}

//--------------------------------------------
//UI�A�C�e���̐���
//--------------------------------------------
CUIItem *CUIItem::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUIItem *pScene2D;

	pScene2D = new CUIItem;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUIItem::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//NULL����
	for (int nCnt = 0; nCnt < MAX_ITEM2D; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	//����
	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3((m_pos.x), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//�|���S���̍X�V
	m_pScene2D[0]->SetPos(m_pScene2D[0]->Getpos(), 3.0f, 0, D3DXCOLOR(1, 1, 1, 1));
	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//����
	m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(m_pos.x + 120, m_pos.y - 80, m_pos.z), 160, 80,5);
	m_pScene2D[1]->BindTexture(m_pTexture[1]);
	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene2D[1]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//NULL����
	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	float fWidth = m_fWidth / 2;
	float fHeight = m_fHeight / 2;

	//����
	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{	//�����̏�����
			m_apNumber[nCnt] = CNumber::Create(
				D3DXVECTOR3(((m_pos.x + POS_WIDTH) - (fWidth + fWidth / 5)* nCnt), m_pos.y + POS_HEIGHT, m_pos.z),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fWidth, fHeight);
		}
	}

	//�l�̏�����
	m_bGetItem = false;
	m_ScaleCounter = 0;
	m_fScale = 0;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUIItem::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_ITEM2D; nCnt++)
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

	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		if (m_apNumber[nCnt] != NULL)
		{
			if (m_apNumber[nCnt]->GetDeath() == false)
			{
				//UI�A�C�e����������i���o�[������
				m_apNumber[nCnt]->Uninit();
				m_apNumber[nCnt] = NULL;
			}
		}
	}
	//����������(2D��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CUIItem::Update(void)
{
	//�A�C�e���l������
	if (m_bGetItem == true)
	{	//�J�E���^�[���Z
		m_ScaleCounter++;
		if (m_ScaleCounter <= 5)
		{
			//�g��
			m_fScale += 15;
			m_pScene2D[0]->SetScale(m_fScale);
			//m_pScene2D[1]->SetScale(m_fScale);
			for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
			{
				if (m_apNumber[nCnt] != NULL)
				{
					m_apNumber[nCnt]->SetScale(m_fScale);
				}
			}
		}
		else if (m_ScaleCounter >= 6 && m_ScaleCounter < 10)
		{
			//�k��
			m_fScale -= 15;
			m_pScene2D[0]->SetScale(m_fScale);
			//m_pScene2D[1]->SetScale(m_fScale);
			for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
			{
				if (m_apNumber[nCnt] != NULL)
				{
					m_apNumber[nCnt]->SetScale(m_fScale);
				}
			}
		}
		else if (m_ScaleCounter == 10)
		{
			//������
			m_fScale = 0;
			m_pScene2D[0]->SetScale(m_fScale);
			//m_pScene2D[1]->SetScale(m_fScale);
			for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
			{
				if (m_apNumber[nCnt] != NULL)
				{
					m_apNumber[nCnt]->SetScale(m_fScale);
				}
			}
			m_ScaleCounter = 0;
			m_bGetItem = false;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUIItem::Draw(void)
{
}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CUIItem::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CUIItem::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_ITEM2D; nCnt++)
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
// ���Z����
//=============================================================================
void CUIItem::PlusItem(int nAddItem)
{
	int nAnswer = 0;
	int nDigit = 1;

	m_nItem += nAddItem;

	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		//�����̌v�Z
		nAnswer = m_nItem % (nDigit * 10) / nDigit;
		//���̌��̐������Z�b�g
		if (m_apNumber[nCnt] != NULL)
		{
			m_apNumber[nCnt]->SetNumber(nAnswer);
		}
		//���̌���
		nDigit *= 10;
	}
}

//=============================================================================
// �A�C�e���̐���Ԃ�����
//=============================================================================
int CUIItem::GetItemNum(void)
{
	return m_nItem;
}
//=============================================================================
// �A�C�e���̊l���̃t���O�ݒ�
//=============================================================================
void CUIItem::SetItemBool(bool bGetItem)
{
	m_bGetItem = bGetItem;
}
