//=============================================================================
//
// UI�Q�[�W���� [UIGauge.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIGauge.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\PAUSE\\soda000.jpg"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME001			 "data\\TEXTURE\\UI\\CANUI.png"			//�e�N�X�`���̃t�@�C����
#define TEXTURENAME002			 "data\\TEXTURE\\UI\\GAUSELOGO.png"			//�e�N�X�`���̃t�@�C����

#define MAX_GAUGECAPA			(400)
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIGauge::m_pTexture[MAX_GAUGE] = {};
float						CUIGauge::m_fVtxHeight = 0;
CUIGauge::GAUGESTATE		CUIGauge::m_State;

//--------------------------------------------
//UI�Q�[�W�N���X �R���X�g���N�^
//--------------------------------------------
CUIGauge::CUIGauge()
{
	m_pos = D3DXVECTOR3(0,0,0);						// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);					// �O��̈ʒu
}

//--------------------------------------------
//UI�Q�[�W�N���X �f�X�g���N�^
//--------------------------------------------
CUIGauge::~CUIGauge()
{
}

//--------------------------------------------
//UI�Q�[�W�̐���
//--------------------------------------------
CUIGauge *CUIGauge::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUIGauge *pScene2D;

	pScene2D = new CUIGauge;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CUIGauge::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//2D�|���S������
	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	//�e�N�X�`����ݒ�
	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//2D�|���S������
	m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y -190, m_pos.z), m_fWidth, m_fHeight + 10);
	//�e�N�X�`����ݒ�
	m_pScene2D[1]->BindTexture(m_pTexture[1]);
	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene2D[1]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//2D�|���S������
	m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 450, m_pos.z),160, 80);
	//�e�N�X�`����ݒ�
	m_pScene2D[2]->BindTexture(m_pTexture[2]);
	m_pScene2D[2]->SetColor(D3DXCOLOR(1.0f, 0.3f, 0.3f, 0.9f));
	//�I�u�W�F�N�g��ނ̐ݒ�
	m_pScene2D[2]->SetObjType(CScene::OBJTYPE_SCENE2D);

	m_fVtxHeight = 0;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@���擾
	m_pVtxBuff = m_pScene2D[0]->GetVtx();
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_�ʒu
	pVtx[0].pos = D3DXVECTOR3(pVtx[0].pos.x, m_pos.y + m_fVtxHeight, pVtx[0].pos.z);
	pVtx[1].pos = D3DXVECTOR3(pVtx[1].pos.x, m_pos.y + m_fVtxHeight, pVtx[1].pos.z);
	pVtx[2].pos = D3DXVECTOR3(pVtx[2].pos.x, m_pos.y, pVtx[2].pos.z);
	pVtx[3].pos = D3DXVECTOR3(pVtx[3].pos.x, m_pos.y, pVtx[3].pos.z);
	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CUIGauge::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
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
void CUIGauge::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

#ifdef  _DEBUG
	if (pInput->GetTrigger(DIK_I) == true)
	{
		m_fVtxHeight += 50;
	}
	if (pInput->GetTrigger(DIK_O) == true)
	{
		m_fVtxHeight -= 50;
	}
#endif
	//�Q�[�W�������Ȃ��悤��
	if (m_fVtxHeight < -MAX_GAUGECAPA)
	{
		m_fVtxHeight = -MAX_GAUGECAPA;
	}
	else if (m_fVtxHeight > 0)
	{
		m_fVtxHeight = 0;
	}

	//��Ԃ̕ω�
	if (m_fVtxHeight == -MAX_GAUGECAPA)
	{
		m_State = GAUGESTATE_MAXGAUGE;
	}
	else if (m_fVtxHeight == 0)
	{
		m_State = GAUGESTATE_NORMAL;
	}

	//m_fVtxHeight = 0;

	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�o�b�t�@���擾
	m_pVtxBuff = m_pScene2D[0]->GetVtx();
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//���_�ʒu
	pVtx[0].pos = D3DXVECTOR3(pVtx[0].pos.x, m_pos.y + m_fVtxHeight, pVtx[0].pos.z);
	pVtx[1].pos = D3DXVECTOR3(pVtx[1].pos.x, m_pos.y + m_fVtxHeight, pVtx[1].pos.z);
	pVtx[2].pos = D3DXVECTOR3(pVtx[2].pos.x, m_pos.y, pVtx[2].pos.z);
	pVtx[3].pos = D3DXVECTOR3(pVtx[3].pos.x, m_pos.y, pVtx[3].pos.z);
	//���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUIGauge::Draw(void)
{

}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CUIGauge::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);
	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME002, &m_pTexture[2]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CUIGauge::UnLoad(void)
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
// �Q�[�W��������
//=============================================================================
void CUIGauge::SetGauge(float fGauge)
{
	m_fVtxHeight -= fGauge;
}

//=============================================================================
// �Q�[�W���
//=============================================================================
CUIGauge::GAUGESTATE CUIGauge::GetGaugeState(void)
{
	return m_State;
}
