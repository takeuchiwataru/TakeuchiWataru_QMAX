//---------------------------------------------------------------------
//	3D�G�t�F�N�g����(objectBG.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "effect3D.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"

#include "sceneObject.h"
#include "fade.h"
#include "player.h"
#include "effect.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL000						"data\\MODEL\\3DEFFECT\\Hahen000.x"
#define MODEL001						"data\\MODEL\\3DEFFECT\\Hahen100.x"
#define MODEL002						"data\\MODEL\\3DEFFECT\\Hahen200.x"
#define MODEL003						"data\\MODEL\\3DEFFECT\\Hahen300.x"
#define MODEL004						"data\\MODEL\\3DEFFECT\\Hahen400.x"
#define MODEL005						"data\\MODEL\\3DEFFECT\\HahenWood.x"
#define MODEL006						"data\\MODEL\\3DEFFECT\\HahenLeaf.x"
#define MODEL007						"data\\MODEL\\3DEFFECT\\HahenTruck.x"
#define MODEL008						"data\\MODEL\\3DEFFECT\\Hahen500.x"

#define MODEL_SPEED     (5.0f)

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPD3DXMESH					C3DEffect::m_pMesh[EFFECTTYPE_MAX] = {};
LPD3DXBUFFER				C3DEffect::m_pBuffMat[EFFECTTYPE_MAX] = {};
LPDIRECT3DTEXTURE9			C3DEffect::m_pTexture[EFFECTTYPE_MAX] = {};
DWORD						C3DEffect::m_nNumMat[EFFECTTYPE_MAX] = {};

//--------------------------------------------
//3D�G�t�F�N�g�N���X �R���X�g���N�^
//--------------------------------------------
C3DEffect::C3DEffect() : CScene(3, CScene::OBJTYPE_BGMODEL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//�ʒu
	m_posold = D3DXVECTOR3(0, 0, 0);				//�O��̈ʒu
	m_move = D3DXVECTOR3(0, 0, 0);					//�ړ���
	m_ModelMove = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);					//����
	D3DXMatrixIdentity(&m_mtxWorld);				//���[���h�}�g���b�N�X
	m_nCount = 0;
	m_Type = C3DEffect::EFFECTTYPE_BILL000;
}

//--------------------------------------------
//3D�G�t�F�N�g�N���X �f�X�g���N�^
//--------------------------------------------
C3DEffect::~C3DEffect()
{
}

//--------------------------------------------
//3D�G�t�F�N�g�̐���
//--------------------------------------------
C3DEffect *C3DEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, EFFECTTYPE type, int nLife)
{
	//3D�G�t�F�N�g�|�C���^
	C3DEffect *pEffect3D;
	pEffect3D = new C3DEffect;
	//�^�C�v�̐ݒ�
	pEffect3D->m_Type = type;

	//�����l���������� �l����
	pEffect3D->m_pos = pos;
	pEffect3D->m_rot = rot;
	pEffect3D->m_nLife = nLife;
	//3D�G�t�F�N�g�̏�����
	pEffect3D->Init();

	//�ړ��ʂ̐ݒ�
	pEffect3D->m_move = move;
	//3D�G�t�F�N�g�̏���Ԃ�
	return pEffect3D;
}

//=============================================================================
// 3D�G�t�F�N�g�̏���������
//=============================================================================
HRESULT C3DEffect::Init(void)
{
	//3D�G�t�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_BGMODEL);

	m_move = D3DXVECTOR3(0, 0, 0);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;

	//���f���𐶐�	�I�t�Z�b�g�ݒ�
	m_pObject = CSceneObject::Create(m_pos, m_rot);
	//���f�������蓖��
	m_pObject->BindModel(m_nNumMat[m_Type], m_pMesh[m_Type], m_pBuffMat[m_Type]);

	//�e��ݒ�
	m_pShadow = NULL;

	switch (m_Type)
	{
	case EFFECTTYPE_BILL000:
	case EFFECTTYPE_BILL001:
	case EFFECTTYPE_BILL002:
	case EFFECTTYPE_BILL003:
		m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 1.0f, m_pos.z - 150.0f +((float)(rand() % 200 ))),
									30, 30, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), CShadow::SHADOWTYPE_NORMAL);
		break;
	case EFFECTTYPE_FENCE000:
	case EFFECTTYPE_TREE000:
		m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 1.0f, m_pos.z - 150.0f),
			10, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f), CShadow::SHADOWTYPE_NORMAL);
		break;
	}

	return S_OK;
}

//=============================================================================
// 3D�G�t�F�N�g�̏I������
//=============================================================================
void C3DEffect::Uninit(void)
{
	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}

	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		m_pShadow = NULL;
	}
	//����������(3D�G�t�F�N�g��j��)
	Release();
}

//=============================================================================
// 3D�G�t�F�N�g�̍X�V����
//=============================================================================
void C3DEffect::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	//�ߋ��̈ʒu��ݒ�
	m_posold = m_pos;

	//���C�t����
	m_nLife--;
	//�d��
	m_move.y -= cosf(D3DX_PI * 0) * 0.5f;
	//����
	m_move.x += (0.0f - m_move.x) * 0.2f;
	m_move.z += (0.0f - m_move.z) * 0.5f;
	//�ʒu�X�V
	m_pos += m_move;
	//�n�ʂł͂˂�
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0;
		m_move.y /= 2;
		m_move *= -1;
	}
	//�ʒu��ݒ�
	m_pObject->Setpos(m_pos);

	//���C�t�؂�ŏ���
	if (m_nLife < 0)
	{
		Uninit();
	}
}

//=============================================================================
// 3D�G�t�F�N�g�̕`�揈��
//=============================================================================
void C3DEffect::Draw(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 Kyori = m_pos - pPlayer->GetPos();

	if (m_pos.z + 200 > pPlayer->GetPos().z)
	{
		Kyori.z = abs(Kyori.z);
		if (Kyori.z < 10000)
		{
			//�f�o�C�X���擾
			CRenderer *pRenderer = CManager::GetRenderer();
			LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
			D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
			D3DXMATRIX mtxParent;

			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_mtxWorld);
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
			D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
			// �`�揈��
			if (m_pObject != NULL)
			{
				m_pObject->SetbShadow(false);
				m_pObject->Draw();
			}
		}
	}
}

//=============================================================================
// 3D�G�t�F�N�g�̈ʒu�ݒ�
//=============================================================================
void C3DEffect::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT C3DEffect::Load(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATERIAL *pMat;							//�}�e���A���f�[�^�ւ̃|�C���^


	for (int nCnt = 0; nCnt < EFFECTTYPE_MAX; nCnt++)
	{
		// ���b�V���̊J��
		m_pMesh[nCnt] = NULL;
		// �}�e���A���̊J��
		m_pBuffMat[nCnt] = NULL;
		//�e�N�X�`���̔j��
		m_pTexture[nCnt] = NULL;
	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[0], NULL, &m_nNumMat[0], &m_pMesh[0]);
	D3DXLoadMeshFromX(MODEL001, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[1], NULL, &m_nNumMat[1], &m_pMesh[1]);
	D3DXLoadMeshFromX(MODEL002, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[2], NULL, &m_nNumMat[2], &m_pMesh[2]);
	D3DXLoadMeshFromX(MODEL003, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[3], NULL, &m_nNumMat[3], &m_pMesh[3]);
	D3DXLoadMeshFromX(MODEL005, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[4], NULL, &m_nNumMat[4], &m_pMesh[4]);
	D3DXLoadMeshFromX(MODEL005, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[5], NULL, &m_nNumMat[5], &m_pMesh[5]);
	D3DXLoadMeshFromX(MODEL006, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[6], NULL, &m_nNumMat[6], &m_pMesh[6]);
	D3DXLoadMeshFromX(MODEL007, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[7], NULL, &m_nNumMat[7], &m_pMesh[7]);
	D3DXLoadMeshFromX(MODEL008, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[8], NULL, &m_nNumMat[8], &m_pMesh[8]);

	//�e�N�X�`���̓ǂݍ���
	for (int nCnt = 0; nCnt < EFFECTTYPE_MAX; nCnt++)
	{
		//�}�e���A����񂩂�e�N�X�`���̎擾
		pMat = (D3DXMATERIAL*)m_pBuffMat[nCnt]->GetBufferPointer();
		//�}�e���A���̐���
		for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nCnt]; nCntMatTex++)
		{
			if (pMat[nCntMatTex].pTextureFilename != NULL)
			{
				// �e�N�X�`���̐ݒ�
				D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�ւ̃|�C���^
					pMat[nCntMatTex].pTextureFilename,	// �t�@�C���̖��O
					&m_pTexture[nCnt]);					// �e�N�X�`���ւ̃|�C���^
			}
		}
	}
	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void C3DEffect::UnLoad(void)
{
	for (int nCnt = 0; nCnt < EFFECTTYPE_MAX; nCnt++)
	{
		// ���b�V���̊J��
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// �}�e���A���̊J��
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}

		//�e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// 3D�G�t�F�N�g�̈ʒu
//=============================================================================
D3DXVECTOR3 C3DEffect::GetPos(void)
{
	return m_pos;
}
