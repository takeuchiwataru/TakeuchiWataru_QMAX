//=============================================================================
//
// �u���b�N���� [block.cpp]
// Author : ���R���
//
//=============================================================================
#include "block.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BLOCK_NAME	"data\\MODEL\\woodBox.x"	// �u���b�N�̃��f����
#define BLOCKSIZE	(15.0f)					// �u���b�N�̃T�C�Y

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH CBlock::m_pMesh = NULL;		// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CBlock::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CBlock::m_nNumMat = 0;			// �}�e���A�����̐�
LPDIRECT3DTEXTURE9 *CBlock::m_pTexture = 0;			// �e�N�X�`�����

//=============================================================================
// �v���C���[�N���X�̃R���X�g���N�^
//=============================================================================
CBlock::CBlock()
{
	// �l���N���A
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorld);		// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bFall = true;
	m_nCntFall = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBlock::~CBlock()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock *pBlock = NULL;

	if (pBlock == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pBlock = new CBlock;

		if (pBlock != NULL)
		{
			pBlock->SetPosition(pos);
			pBlock->m_pos = pos;
			pBlock->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pBlock->BindMat(m_pTexture);
			pBlock->Init();
		}
	}

	return pBlock;
}

//=============================================================================
// �u���b�N����������
//=============================================================================
HRESULT CBlock::Init(void)
{
	// ����������
	CSceneX::Init();

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_ENEMY);

	// �g�嗦�̐ݒ�
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_bFall = true;

	m_nCntFall = 0;

	return S_OK;
}

//=============================================================================
// �u���b�N�I������
//=============================================================================
void CBlock::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �u���b�N�X�V����
//=============================================================================
void CBlock::Update(void)
{
	m_pos.z += 3.0f;

	CSceneX::SetPosition(m_pos);
}

//=============================================================================
// �u���b�N�`�揈��
//=============================================================================
void CBlock::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}


	// ���_�@���̎������K��	�J�n
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CSceneX::Draw();

	// ���_�@���̎������K��	�I��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

}

//=============================================================================
// �u���b�N�Ƃ̓����蔻�菈��
//=============================================================================
bool CBlock::Collision(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// �������Ă��Ȃ����

	// ���S�ƒ��S�̍������߂�
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - m_pos.x, pos->y - m_pos.y - 20.0f, pos->z - m_pos.z);

	// ���S���璆�S�̃x�N�g���̒������Z�o
	float distance = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (distance < fRadius + m_VtxMax.x && distance < fRadius + m_VtxMax.y && distance < fRadius + m_VtxMax.z)
	{// ���������a�̘a��菬������Γ������Ă���
		bHit = true;
	}

	return bHit;	// �u���b�N�ɓ������Ă��邩�ǂ�����Ԃ�
}

//=============================================================================
// �u���b�N�̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CBlock::LoadModel(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(BLOCK_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=============================================================================
// �u���b�N�̃��f���������
//=============================================================================
void CBlock::UnloadModel(void)
{
	// ���b�V���̊J��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̊J��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// �u���b�N�̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CBlock::LoadMat(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �}�e���A���̐����e�N�X�`����������̂𓮓I�Ɋm��
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �����O�ɋ�ɂ���
		m_pTexture[nCntMat] = NULL;

		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// �e�N�X�`���̐���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntMat]);
		}
	}

	return S_OK;
}

//=============================================================================
// �u���b�N�̃��f���������
//=============================================================================
void CBlock::UnloadMat(void)
{
	if (m_pTexture != NULL)
	{// �e�N�X�`���̃|�C���^��NULL�`�F�b�N(��)
		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			if (m_pTexture[nCntMat] != NULL)
			{// �|�C���^�̒���NULL�`�F�b�N(�Ƌ�)
				m_pTexture[nCntMat]->Release();
				m_pTexture[nCntMat] = NULL;
			}
		}

		// �������̊J��(���)
		delete[] m_pTexture;
		// NULL�ɂ���(�X�n)
		m_pTexture = NULL;
	}
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CBlock::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CBlock::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �����Ă��邩�ǂ����̎擾
//=============================================================================
bool CBlock::GetFall(void)
{
	return m_bFall;
}

//=============================================================================
// �����Ă��邩�ǂ����̐ݒ�
//=============================================================================
void CBlock::SetFall(bool bFall)
{
	m_bFall = bFall;
}