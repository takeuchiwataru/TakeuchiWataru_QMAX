//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "effect.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\EFFECT\\effect001.png"		//�e�N�X�`���̃t�@�C����
#define TEXTURENAME001			 "data\\TEXTURE\\EFFECT\\effect002.png"		//�e�N�X�`���̃t�@�C����
#define TEXTURENAME002			 "data\\TEXTURE\\EFFECT\\effect003.png"		//�e�N�X�`���̃t�@�C����
#define TEXTURENAME003			 "data\\TEXTURE\\EFFECT\\effect004.png"		//�e�N�X�`���̃t�@�C����
#define TEXTURENAME004			 "data\\TEXTURE\\EFFECT\\effect005.png"		//�e�N�X�`���̃t�@�C����

#define TEX_POS_X_INIT			(1.0f)									//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT			(1.0f)									//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT				(0.0f)									//�e�N�X�`�����WU��
#define TEX_RIGHT				(1.0f)									//�e�N�X�`�����WU�E
#define TEX_TOP					(0.0f)									//�e�N�X�`�����WV��
#define TEX_BOT					(1.0f)									//�e�N�X�`�����WV��

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CEffect::m_pTexture[EFFECTTEX_MAX] = {};

//--------------------------------------------
//�G�t�F�N�g�N���X �R���X�g���N�^
//--------------------------------------------
CEffect::CEffect()
{
	m_pos = D3DXVECTOR3(0,0,0);						// �ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					// �ړ���
	m_posold = D3DXVECTOR3(0, 0, 0);				// �O��̈ʒu


	m_TexType = EFFECTTEX_NORMAL000;
}

//--------------------------------------------
//�G�t�F�N�g�N���X �f�X�g���N�^
//--------------------------------------------
CEffect::~CEffect()
{
}

//--------------------------------------------
//�G�t�F�N�g�̐���
//--------------------------------------------
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col,
	float fWidth, float fHeight, int nNumMax, int nLife, EFFECTTEX TexType)
{
	CEffect *pEffect;

	pEffect = new CEffect;

	pEffect->m_pos = pos;
	pEffect->m_move = move;
	pEffect->m_Col = col;
	pEffect->m_fHeight = fHeight;
	pEffect->m_fWidth = fWidth;
	pEffect->m_nNumMax = nNumMax;
	pEffect->m_nLife = nLife;
	pEffect->m_TexType = TexType;

	pEffect->Init();

	return pEffect;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pBillBoard = CSceneBillBoard::Create(m_pos, m_move, m_fWidth, m_fHeight);
	m_pBillBoard->BindTexture(m_pTexture[m_TexType]);
	m_pBillBoard->Setpos(m_pos);
	m_pBillBoard->SetCol(m_Col);

	//�I�u�W�F�N�g��ނ̐ݒ�
	if (m_TexType == EFFECTTEX_NORMAL000 || m_TexType == EFFECTTEX_SMOKE)
	{
		CScene::SetObjType(CScene::OBJTYPE_EFFECTADD);
		m_pBillBoard->SetObjType(CScene::OBJTYPE_EFFECTADD);
	}
	else
	{
		CScene::SetObjType(CScene::OBJTYPE_EFFECT);
		m_pBillBoard->SetObjType(CScene::OBJTYPE_EFFECT);
	}
	m_fAlpha = 1.0f / (float)m_nLife;
	//m_fAlpha = m_fAlpha / 60;
	m_nCntTimer = 0;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	if (m_pBillBoard != NULL)
	{
		m_pBillBoard->Uninit();
		m_pBillBoard = NULL;
	}
	//����������(�j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	m_nCntTimer++;

	if (m_nLife > 0)
	{
		m_nLife--;

		//�d��
		m_move.y -= cosf(D3DX_PI * 0) * 0.3f;
		//�ʒu���X�V
		m_pos = m_pBillBoard->GetPos();
		m_pos.y += m_move.y;
		//�n�ʂł͂˂�
		if (m_pos.y < 0.0f)
		{
			m_move *= -1;
		}

		//���X�ɓ����ɂ��Ă���
		m_Col.a = m_Col.a - m_fAlpha;
		//���ȉ��ɂȂ�����0��
		if (m_Col.a < 0.01f)
		{
			m_Col.a = 0;
		}
		//�F��ݒ�
		m_pBillBoard->SetCol(m_Col);

		//�ݒ菈��
		m_pBillBoard->SetBillboard(m_pos, m_fHeight, m_fWidth);
	}
	else if (m_nLife == 0)
	{
		if (m_pBillBoard != NULL)
		{
			m_pBillBoard->Uninit();
			m_pBillBoard = NULL;
		}
		//����������(�j��)
		Release();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{

}
//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CEffect::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < EFFECTTEX_MAX; nCnt++)
	{
		m_pTexture[nCnt] = NULL;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME002, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME003, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME004, &m_pTexture[4]);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CEffect::UnLoad(void)
{
	for (int nCnt = 0; nCnt < EFFECTTEX_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
