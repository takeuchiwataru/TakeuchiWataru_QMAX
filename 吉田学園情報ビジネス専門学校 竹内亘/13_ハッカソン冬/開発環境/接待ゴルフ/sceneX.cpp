//=============================================================================
//
// ���f������ [sceneX.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "sceneX.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "bullet.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_NAME000		"data\\MODEL\\MODELBG\\box000.x"		//�e�N�X�`���̃t�@�C����
#define MODEL_NAME001		"data\\MODEL\\MODELBG\\box000.x"		//�e�N�X�`���̃t�@�C����
#define TEX_NAME000			"data\\TEXTURE\\exclamation000.jpg"		//�e�N�X�`���̃t�@�C����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//--------------------------------------------
//�V�[��X�N���X �R���X�g���N�^
//--------------------------------------------
CSceneX::CSceneX() : CScene(3, CScene::OBJTYPE_SCENEX)
{
}

//--------------------------------------------
//�V�[��X�N���X �f�X�g���N�^
//--------------------------------------------
CSceneX::~CSceneX()
{
}

//=============================================================================
// ��������
//=============================================================================
CSceneX * CSceneX::Create(D3DXVECTOR3 pos)
{
	CSceneX *pSceneX;

	pSceneX = new CSceneX;

	pSceneX->m_aModel.pos = pos;

	pSceneX->Init();

	return pSceneX;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneX::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx;

	m_aModel.VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
	m_aModel.VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
	m_aModel.nType = 0;
	m_aModel.bUse = false;

	//���_�����擾
	nNumVtex = m_pMeshModel->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF = D3DXGetFVFVertexSize(m_pMeshModel->GetFVF());
	//���_�@���b�N
	m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
	{	//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (m_aModel.VtxMinModel.x > vtx.x)
		{
			m_aModel.VtxMinModel.x = vtx.x;
		}
		if (m_aModel.VtxMinModel.y > vtx.y)
		{
			m_aModel.VtxMinModel.y = vtx.y;
		}
		if (m_aModel.VtxMinModel.z > vtx.z)
		{
			m_aModel.VtxMinModel.z = vtx.z;
		}

		if (m_aModel.VtxMaxModel.x < vtx.x)
		{
			m_aModel.VtxMaxModel.x = vtx.x;
		}
		if (m_aModel.VtxMaxModel.y < vtx.y)
		{
			m_aModel.VtxMaxModel.y = vtx.y;
		}
		if (m_aModel.VtxMaxModel.z < vtx.z)
		{
			m_aModel.VtxMaxModel.z = vtx.z;
		}
		pVtxBuff += sizeFvF;
	}
	//���_�o�b�t�@���A�����b�N
	m_pMeshModel->UnlockVertexBuffer();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEX_NAME000,
		&m_pTextureModel);

	SetModel(m_aModel.pos, 0);

	//�I�u�W�F�N�g�^�C�v�̐ݒ�
	CScene::SetObjType(OBJTYPE_SCENEX);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneX::Uninit(void)
{
		//����������(�V�[��X��j��)
		Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneX::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneX::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

		// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_aModel.mtxWorld);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_aModel.rot.y, m_aModel.rot.x, m_aModel.rot.z);
	D3DXMatrixMultiply(&m_aModel.mtxWorld, &m_aModel.mtxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_aModel.pos.x, m_aModel.pos.y, m_aModel.pos.z);
	D3DXMatrixMultiply(&m_aModel.mtxWorld, &m_aModel.mtxWorld, &mtxTrans);
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_aModel.mtxWorld);
	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		// �e�N�X�`��
		pDevice->SetTexture(0, m_pTextureModel);
		if (m_aModel.bUse == true)	//���f�����g�p����Ă���
		{
			// ���f��(�p�[�c)�̕`��
			m_pMeshModel->DrawSubset(nCntMat);
		}
	}
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);

}

//*****************************************************************************
//���f���ʒu�ݒ菈��
//*****************************************************************************
void CSceneX::Setpos(D3DXVECTOR3 pos)
{
	m_aModel.pos = pos;
}

void CSceneX::Setrot(D3DXVECTOR3 rot)
{
	m_aModel.rot = rot;
}

//*****************************************************************************
//���f���|�C���^����
//*****************************************************************************
CSceneX::MODEL *CSceneX::GetModel(void)
{
	return &m_aModel;
}
//*****************************************************************************
//���f���Ƃ̓����蔻�菈��
//*****************************************************************************
bool CSceneX::CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove,
	D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin)
{
	bool bLand = false;
	if (m_aModel.bUse == true)
	{
		//���f����Y���̒�
		if (pPos->y < m_aModel.pos.y + m_aModel.VtxMaxModel.y
			&& pPos->y > m_aModel.pos.y + m_aModel.VtxMinModel.y)
		{
			//���f����Z���̒�
			if (pPos->z + VtxMin.z < m_aModel.pos.z + m_aModel.VtxMaxModel.z
				&& pPos->z + VtxMax.z > m_aModel.pos.z + m_aModel.VtxMinModel.z)
			{
				//���f����X���̒�
				if (pPos->x + VtxMin.x < m_aModel.pos.x + m_aModel.VtxMaxModel.x
					&& pPos->x + VtxMax.x > m_aModel.pos.x + m_aModel.VtxMinModel.x)
				{

					//X���̓����蔻��
					if (pPosOld->x > m_aModel.pos.x + m_aModel.VtxMaxModel.x)
					{
						pPos->x = m_aModel.pos.x + m_aModel.VtxMaxModel.x + VtxMax.x;
						pPosOld->x = m_aModel.pos.x + m_aModel.VtxMaxModel.x + VtxMax.x;
						//pMove->x = 0;
						bLand = true;
					}
					else if (pPosOld->x < m_aModel.pos.x + m_aModel.VtxMinModel.x)
					{
						pPos->x = m_aModel.pos.x + m_aModel.VtxMinModel.x + VtxMin.x;
						pPosOld->x = m_aModel.pos.x + m_aModel.VtxMinModel.x + VtxMin.x;
						//pMove->x = 0;
						bLand = true;

					}
					//Z���̓����蔻��
					if (pPosOld->z > m_aModel.pos.z + m_aModel.VtxMaxModel.z)
					{
						bLand = true;
						pPos->z = m_aModel.pos.z + m_aModel.VtxMaxModel.z + VtxMax.z;
						pPosOld->z = m_aModel.pos.z + m_aModel.VtxMaxModel.z + VtxMax.z;
						//pMove->z = 0;
					}
					else if (pPosOld->z < m_aModel.pos.z + m_aModel.VtxMinModel.z)
					{
						bLand = true;
						pPos->z = m_aModel.pos.z + m_aModel.VtxMinModel.z + VtxMin.z;
						pPosOld->z = m_aModel.pos.z + m_aModel.VtxMinModel.z + VtxMin.z;
						//pMove->z = 0;
					}
					//Y���̓����蔻��
					if (pPosOld->y >= m_aModel.pos.y + m_aModel.VtxMaxModel.y)
					{
						pPos->y = m_aModel.pos.y + m_aModel.VtxMaxModel.y;
						pPosOld->y = m_aModel.pos.y + m_aModel.VtxMaxModel.y;

					}
					else if (pPosOld->y <= m_aModel.pos.y + m_aModel.VtxMinModel.y)
					{
						pPos->y = m_aModel.pos.y + m_aModel.VtxMinModel.y;
						pPosOld->y = m_aModel.pos.y + m_aModel.VtxMinModel.y;
					}
				}
			}
		}

	}
	return bLand;
}


//=============================================================================
// ���f���̐ݒ菈��
//=============================================================================
void CSceneX::SetModel(D3DXVECTOR3 pos, int nType)
{

	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx;

	//���_�����擾
	nNumVtex = m_pMeshModel->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF = D3DXGetFVFVertexSize(m_pMeshModel->GetFVF());

	//���_�@���b�N
	m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
	{	//���_���W�̑��
		vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (m_aModel.VtxMinModel.x > vtx.x)
		{
			m_aModel.VtxMinModel.x = vtx.x;
		}
		if (m_aModel.VtxMinModel.y > vtx.y)
		{
			m_aModel.VtxMinModel.y = vtx.y;
		}
		if (m_aModel.VtxMinModel.z > vtx.z)
		{
			m_aModel.VtxMinModel.z = vtx.z;
		}

		if (m_aModel.VtxMaxModel.x < vtx.x)
		{
			m_aModel.VtxMaxModel.x = vtx.x;
		}
		if (m_aModel.VtxMaxModel.y < vtx.y)
		{
			m_aModel.VtxMaxModel.y = vtx.y;
		}
		if (m_aModel.VtxMaxModel.z < vtx.z)
		{
			m_aModel.VtxMaxModel.z = vtx.z;
		}
		pVtxBuff += sizeFvF;

		//���_�o�b�t�@���A�����b�N
		m_pMeshModel->UnlockVertexBuffer();
	}
		if (m_aModel.bUse == false)
		{
			// �ʒu�E�����̏����ݒ�
			m_aModel.pos = pos;
			m_aModel.rot = D3DXVECTOR3(0, 0, 0);
			m_aModel.fShadow = 12;
			m_aModel.nType = nType;
			m_aModel.bUse = true;
		}
}

//=============================================================================
// �}�e���A�����蓖�ď���
//=============================================================================
void CSceneX::BindTexture(LPDIRECT3DTEXTURE9 Texture, LPD3DXMESH Mesh, LPD3DXBUFFER Buff)
{
	m_pBuffMatModel = Buff;
	m_pTextureModel = Texture;
	m_pMeshModel = Mesh;
}