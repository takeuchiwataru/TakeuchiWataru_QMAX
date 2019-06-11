//=============================================================================
//
// �w�i���� [bg.cpp]
// Author : �|���j
//
//=============================================================================
#include "bg.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG_TEXTURE] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBg::CBg():CScene(1)
{
	m_apScene2D[0] = NULL;
	m_apScene2D[1] = NULL;
	m_apScene2D[2] = NULL;
	m_slideSpeed = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBg::~CBg()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		pVtxBuff = m_apScene2D[nCountBg]->GetVtxBuff();

		// ���_�o�b�t�@�����b�N
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

		// ���_�o�b�t�@���A�����b�N
		pVtxBuff->Unlock();
	}
	return S_OK;
}
//=============================================================================
// ����������(�Q�[��)
//=============================================================================
HRESULT CBg::InitGame(D3DXVECTOR3 pos)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		pVtxBuff = m_apScene2D[nCountBg]->GetVtxBuff();

		// ���_�o�b�t�@�����b�N
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X000, BG_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BG_POS_X001, BG_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X000, BG_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BG_POS_X001, BG_HEIGHT, 0.0f);

		// ���_�o�b�t�@���A�����b�N
		pVtxBuff->Unlock();
	}
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		m_apScene2D[nCountBg]->Uninit();
		m_apScene2D[nCountBg] = NULL;
	}

	Release();
}
//=============================================================================
// �X�V����
//=============================================================================
void CBg::Update(void)
{
	m_slideSpeed++;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	// ���_����ݒ�
	VERTEX_2D * pVtx;					// ���_���ւ̃|�C���^

	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		pVtxBuff = m_apScene2D[nCountBg]->GetVtxBuff();

		// ���_�o�b�t�@�����b�N
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		if (m_apScene2D[nCountBg] == m_apScene2D[0])
		{// �w�i1
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_000));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_000));
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_000));
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_000));
		}

		else if (m_apScene2D[nCountBg] == m_apScene2D[1])
		{// �w�i2
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_100));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_100));
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_100));
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_100));
		}

		else if (m_apScene2D[nCountBg] == m_apScene2D[2])
		{// �w�i3
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_200));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_200));
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_200));
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_200));
		}

		// ���_�o�b�t�@���A�����b�N
		pVtxBuff->Unlock();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void CBg::Draw(void)
{

}
//=============================================================================
// ����
//=============================================================================
CBg * CBg::Create(D3DXVECTOR3 pos)
{
	CBg *pBg = NULL;

	if (pBg == NULL)
	{
		pBg = new CBg;
		
		for (int nCntScene2D = 0; nCntScene2D < MAX_BG; nCntScene2D++)
		{// CScene2D�̌J��Ԃ�
			pBg->m_apScene2D[nCntScene2D] = new CScene2D(1);
			if (pBg != NULL)
			{
				pBg->m_apScene2D[nCntScene2D]->Init(pos);
				pBg->m_apScene2D[nCntScene2D]->BindTexture(m_apTexture[nCntScene2D]);
			}
		}
		pBg->Init(pos);
	}
	return pBg;
}
//=============================================================================
// ����(�Q�[��)
//=============================================================================
CBg * CBg::Create2(D3DXVECTOR3 pos)
{
	CBg *pBg = NULL;

	if (pBg == NULL)
	{
		pBg = new CBg;

		for (int nCntScene2D = 0; nCntScene2D < MAX_BG; nCntScene2D++)
		{// CScene2D�̌J��Ԃ�
			pBg->m_apScene2D[nCntScene2D] = new CScene2D(1);
			if (pBg != NULL)
			{
				pBg->m_apScene2D[nCntScene2D]->Init(pos);
				pBg->m_apScene2D[nCntScene2D]->BindTexture(m_apTexture[nCntScene2D]);
			}
		}
		pBg->InitGame(pos);
	}
	return pBg;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CBg::Load(void)
{
	CManager manager;	// �C���X�^���X

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_000, &m_apTexture[0]);	// �w�i1
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_001, &m_apTexture[1]);	// �w�i2
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_002, &m_apTexture[2]);	// �w�i3

	return S_OK;
}
//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CBg::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_apTexture[MAX_BG_TEXTURE] != NULL)
	{
		m_apTexture[MAX_BG_TEXTURE]->Release();
		m_apTexture[MAX_BG_TEXTURE] = {};
	}
}
