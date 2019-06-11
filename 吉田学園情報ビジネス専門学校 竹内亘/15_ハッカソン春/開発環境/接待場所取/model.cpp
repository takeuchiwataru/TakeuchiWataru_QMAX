//=============================================================================
//
// ���f������ [model.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "model.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//--------------------------------------------
//���f���N���X �R���X�g���N�^
//--------------------------------------------
CModel::CModel()
{
	m_pMeshModel = NULL;		//���b�V�����ւ̃|�C���^
	m_pBuffMatModel = NULL;		//�}�e���A�����ւ̃|�C���^
	m_pTextureModel = NULL;		//�e�N�X�`���ւ̃|�C���^
	m_nNumMatModel = 0;			//�}�e���A�����̐�
	m_aModel = {};
	m_bShadow = false;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	m_pParent = NULL;			//�e���f���ւ̃|�C���^
}

//--------------------------------------------
//���f���N���X �f�X�g���N�^
//--------------------------------------------
CModel::~CModel()
{
}

//=============================================================================
// ��������
//=============================================================================
CModel * CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CModel *pModel;

	pModel = new CModel;

	pModel->m_aModel.pos = pos;
	pModel->m_aModel.rot = rot;

	pModel->Init();

	return pModel;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CModel::Init(void)
{
	m_VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
	m_VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
	m_aModel.nType = 0;
	m_aModel.bUse = false;
	m_bShadow = false;

	//�t�B�[���h��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_MODEL);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CModel::Uninit(void)
{
	//�|�C���^��NULL�`�F�b�N (��)
	if (m_pTextureModel != NULL)
	{
		for (int nCnt = 0; nCnt < (int)m_nNumMatModel; nCnt++)
		{
			//�|�C���^���̃|�C���^��NULL�`�F�b�N (�Ƌ�)
			if (m_pTextureModel[nCnt] != NULL)
			{
				//�e�N�X�`���j��
				m_pTextureModel[nCnt]->Release();
				m_pTextureModel[nCnt] = NULL;
			}
		}
		//���������J�� (���)
		delete[] m_pTextureModel;
		//NULL������ (�X�n)
		m_pTextureModel = NULL;
	}

	if (m_pMeshModel != NULL)
	{
		//���b�V���j��
		m_pMeshModel = NULL;
	}

	if (m_pBuffMatModel != NULL)
	{
		//�}�e���A���j��
		m_pBuffMatModel = NULL;
	}

	if (m_pParent != NULL)
	{
		//�}�e���A���j��
		m_pParent = NULL;
	}

	//����������(MODEL��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CModel::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CModel::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxParent;

	D3DMATERIAL9 matDef;						//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_aModel.rot.y, m_aModel.rot.x, m_aModel.rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_aModel.pos.x, m_aModel.pos.y, m_aModel.pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//�e�̃}�g���b�N�X���擾
	if (m_pParent != NULL)
	{
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{	//Draw�ŌĂ΂ꂽ�Ƃ��ŐV��mtx��pDevice����擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}
	//�e�̏�������	�|�����킹�Ă���
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxParent);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);
	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		if (pMat != NULL)
		{
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (pMat[nCntMat].pTextureFilename != NULL)
			{
				if (m_bShadow == false)
				{
					// �e�N�X�`��
					pDevice->SetTexture(0, m_pTextureModel[nCntMat]);
				}
				else
				{
					// �e�N�X�`��
					pDevice->SetTexture(0, NULL);
				}
			}
			else
			{	// �e�N�X�`�����g���Ă��Ȃ�
				pDevice->SetTexture(0, NULL);
			}
		}
		//�I�u�W�F�N�g(�p�[�c)�̕`��
		m_pMeshModel->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//*****************************************************************************
//���f���ʒu�ݒ菈��
//*****************************************************************************
void CModel::Setpos(D3DXVECTOR3 pos)
{
	m_aModel.pos = pos;
}
//*****************************************************************************
//���f����]�ݒ菈��
//*****************************************************************************
void CModel::Setrot(D3DXVECTOR3 rot)
{
	m_aModel.rot = rot;
}

//*****************************************************************************
//���f���|�C���^����
//*****************************************************************************
CModel::MODEL *CModel::GetModel(void)
{
	return &m_aModel;
}

//=============================================================================
// ���f���̐ݒ菈��
//=============================================================================
void CModel::SetModel(D3DXVECTOR3 pos, int nType)
{
#if 1
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
		if (m_VtxMinModel.x > vtx.x)
		{
			m_VtxMinModel.x = vtx.x;
		}
		if (m_VtxMinModel.y > vtx.y)
		{
			m_VtxMinModel.y = vtx.y;
		}
		if (m_VtxMinModel.z > vtx.z)
		{
			m_VtxMinModel.z = vtx.z;
		}

		if (m_VtxMaxModel.x < vtx.x)
		{
			m_VtxMaxModel.x = vtx.x;
		}
		if (m_VtxMaxModel.y < vtx.y)
		{
			m_VtxMaxModel.y = vtx.y;
		}
		if (m_VtxMaxModel.z < vtx.z)
		{
			m_VtxMaxModel.z = vtx.z;
		}
		pVtxBuff += sizeFvF;

		//���_�o�b�t�@���A�����b�N
		m_pMeshModel->UnlockVertexBuffer();
	}

#endif
}

//=============================================================================
// �}�e���A�����蓖�ď���
//=============================================================================
void CModel::BindModel(DWORD nNumMat, LPD3DXMESH Mesh, LPD3DXBUFFER Buff)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^

	m_pBuffMatModel = Buff;
	m_nNumMatModel = nNumMat;
	m_pMeshModel = Mesh;

	//�}�e���A����񂩂�e�N�X�`���̎擾
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
	//�e�N�X�`�����}�e���A���̐������I�m��
	m_pTextureModel = new LPDIRECT3DTEXTURE9[m_nNumMatModel];
	//�}�e���A���̐���
	for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMatModel; nCntMatTex++)
	{
		//NULL������ ���g�����
		m_pTextureModel[nCntMatTex] = NULL;

		if (pMat[nCntMatTex].pTextureFilename != NULL)
		{
			// �e�N�X�`���̐ݒ�
			D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
				pMat[nCntMatTex].pTextureFilename,	// �t�@�C���̖��O
				&m_pTextureModel[nCntMatTex]);		// �e�N�X�`���ւ̃|�C���^
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void CModel::SetParent(CModel * pModel)
{
	m_pParent = pModel;
}
//=============================================================================
// ���[���h�}�g���b�N�X�̎擾����
//=============================================================================
D3DXMATRIX CModel::GetMtxWorld(void)
{
	return m_mtxWorld;
}
//=============================================================================
// ���[���h�}�g���b�N�X�̐ݒ菈��
//=============================================================================
void CModel::SetMtxWorld(D3DXMATRIX MtxWorld)
{
	m_mtxWorld = MtxWorld;
}

//=============================================================================
// ��]�̐ݒ菈��
//=============================================================================
D3DXVECTOR3 CModel::Getrot(void)
{
	return m_aModel.rot;
}
