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
#define ITEMTEXTURENAME000			 "data\\TEXTURE\\guarana.png"			//�e�N�X�`���̃t�@�C����

#define POS_WIDTH		(120)
#define POS_HEIGHT		(15)
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIItem::m_pTexture[1] = {};

//--------------------------------------------
//UI�A�C�e���N���X �R���X�g���N�^
//--------------------------------------------
CUIItem::CUIItem()
{
	m_pos = D3DXVECTOR3(0,0,0);						// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);					// �O��̈ʒu
	m_nItem = 0;
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

	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		m_pScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3((m_pos.x + (m_fWidth + 25)* nCnt), m_pos.y, m_pos.z), m_fWidth, m_fHeight);
		m_pScene2D[nCnt]->BindTexture(m_pTexture[0]);
		//�|���S���̍X�V
		m_pScene2D[nCnt]->SetPos(m_pScene2D[nCnt]->Getpos() , 3.0f, 0, D3DXCOLOR(1,1,1,1));

		//�I�u�W�F�N�g��ނ̐ݒ�
		m_pScene2D[nCnt]->SetObjType(CScene::OBJTYPE_SCENE2D);
	}

	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		m_apNumber[nCnt] = NULL;
	}

	float fWidth = m_fWidth / 2;
	float fHeight = m_fHeight / 2;

	for (int nCnt = 0; nCnt < MAX_ITEMNUM; nCnt++)
	{
		if (m_apNumber[nCnt] == NULL)
		{	//�����̏�����
			m_apNumber[nCnt] = CNumber::Create(D3DXVECTOR3(((m_pos.x + POS_WIDTH)- (fWidth + fWidth)* nCnt)
				, m_pos.y + POS_HEIGHT, m_pos.z),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), fWidth, fHeight);
		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUIItem::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
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

	//����������(�v���C���[��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CUIItem::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CUIItem::Draw(void)
{
	//for (int nCnt = 0; nCnt < MAX_ITEM; nCnt++)
	//{
	//	if (m_pScene2D[nCnt] != NULL)
	//	{
	//		m_pScene2D[nCnt]->Draw();
	//	}
	//}
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
	D3DXCreateTextureFromFile(pDevice, ITEMTEXTURENAME000, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CUIItem::UnLoad(void)
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
