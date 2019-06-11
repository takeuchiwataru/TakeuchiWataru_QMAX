//=============================================================================
//
// �V�[���I�u�W�F�N�g���� [sceneObject.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "sceneObject.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

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
//�I�u�W�F�N�g�N���X �R���X�g���N�^
//--------------------------------------------
CSceneObject::CSceneObject()
{
	m_pMeshModel = NULL;		//���b�V�����ւ̃|�C���^
	m_pBuffMatModel = NULL;		//�}�e���A�����ւ̃|�C���^
	m_pTextureModel = NULL;		//�e�N�X�`���ւ̃|�C���^
	m_nNumMatModel = 0;			//�}�e���A�����̐�
	//m_aModel = {};
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	m_bShadow = false;			//�V���h�E�t���O
	m_pParent = NULL;			//�e�I�u�W�F�N�g�ւ̃|�C���^
}

//--------------------------------------------
//�I�u�W�F�N�g�N���X �f�X�g���N�^
//--------------------------------------------
CSceneObject::~CSceneObject()
{
}

//=============================================================================
// ��������
//=============================================================================
CSceneObject * CSceneObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSceneObject *pModel;

	pModel = new CSceneObject;

	pModel->Init();

	pModel->m_pos = pos;
	pModel->m_rot = rot;

	return pModel;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneObject::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = D3DXVECTOR3(0,0,0);			//�ʒu
	m_rot = D3DXVECTOR3(0, 0, 0);		//����
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneObject::Uninit(void)
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

}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneObject::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneObject::Draw(void)
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
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

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

			if (m_bShadow == false)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//�e�N�X�`��������ꍇ
					pDevice->SetTexture(0, m_pTextureModel[nCntMat]);
				}
				else
				{	// �e�N�X�`�����g���Ă��Ȃ�
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
//�I�u�W�F�N�g�ʒu�ݒ菈��
//*****************************************************************************
void CSceneObject::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//*****************************************************************************
//�I�u�W�F�N�g��]�ݒ菈��
//*****************************************************************************
void CSceneObject::Setrot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �}�e���A�����蓖�ď���
//=============================================================================
void CSceneObject::BindModel(DWORD nNumMat, LPD3DXMESH Mesh, LPD3DXBUFFER Buff)
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

	//�傫����ݒ�
	VtxMinMaxSet();
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void CSceneObject::SetParent(CSceneObject * pModel)
{
	m_pParent = pModel;
}
//=============================================================================
// ���[���h�}�g���b�N�X�̎擾����
//=============================================================================
D3DXMATRIX CSceneObject::GetMtxWorld(void)
{
	return m_mtxWorld;
}
//=============================================================================
// ���[���h�}�g���b�N�X�̐ݒ菈��
//=============================================================================
void CSceneObject::SetMtxWorld(D3DXMATRIX MtxWorld)
{
	m_mtxWorld = MtxWorld;
}

//=============================================================================
// �I�u�W�F�N�g�̑傫������
//=============================================================================
void CSceneObject::VtxMinMaxSet(void)
{
	int nNumVtex;	//���_��
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx;

	m_VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
	m_VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);

	//���_�����擾
	nNumVtex = m_pMeshModel->GetNumVertices();
	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF = D3DXGetFVFVertexSize(m_pMeshModel->GetFVF());
	//���_�@���b�N
	m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
	{	//���_���W�̑��
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
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
	}
	//���_�o�b�t�@���A�����b�N
	m_pMeshModel->UnlockVertexBuffer();
}

//=============================================================================
// ��]�̐ݒ菈��
//=============================================================================
D3DXVECTOR3 CSceneObject::Getrot(void)
{
	return m_rot;
}

//=============================================================================
// �ʒu�̐ݒ菈��
//=============================================================================
D3DXVECTOR3 CSceneObject::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void CSceneObject::SetbShadow(bool bShadow)
{
	m_bShadow = bShadow;
}
