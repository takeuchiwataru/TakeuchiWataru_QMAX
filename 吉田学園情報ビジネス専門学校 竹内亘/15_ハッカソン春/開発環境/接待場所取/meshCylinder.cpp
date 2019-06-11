//=============================================================================
//
// ���b�V���V�����_�[���� [meshCylinderBG.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "meshCylinder.h"
#include "manager.h"
#include "game.h"
#include "title.h"
#include "model.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHCYLINDERBG_TEXTURENAME	 "data\\TEXTURE\\MODEL\\CanLabel.jpg"	//�e�N�X�`���̃t�@�C����
#define MESHCYLINDERBG_TEXTURENAME1	 "data\\TEXTURE\\SKY\\sky001.png"		//�e�N�X�`���̃t�@�C����

//------------------------------------------------------
//�V�[�����b�V���V�����_�[�N���X �R���X�g���N�^
//------------------------------------------------------
CSceneMeshCylinder::CSceneMeshCylinder() : CScene(3, CScene::OBJTYPE_MESHCYLINDER)
{
	m_pTexture = NULL;				//�e�N�X�`���ւ̃|�C���^
	m_pIdxBuff = NULL;				// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff = NULL;
	D3DXMatrixIdentity(&m_mtxWorld);// ���[���h�}�g���b�N�X�̏�����
	m_nNumVerTex = 0;				// ���_��
	m_nNumIndex = 0;				// �C���f�b�N�X��
	m_nNumPolygon = 0;				// �|���S����
	m_nSplitX = 0;					// ������
	m_nSplitY = 0;					// ������
}

//--------------------------------------------
//�V�[�����b�V���V�����_�[�N���X�N���X �f�X�g���N�^
//--------------------------------------------
CSceneMeshCylinder::~CSceneMeshCylinder()
{
}

//=============================================================================
// ��������
//=============================================================================
CSceneMeshCylinder * CSceneMeshCylinder::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitY,
												CSceneMeshCylinder::CYLINDERTYPE typeInOut)
{
	CSceneMeshCylinder *pMeshCylinder;

	pMeshCylinder = new CSceneMeshCylinder;

	pMeshCylinder->m_pos = pos;
	pMeshCylinder->m_fWidth = fWidth;
	pMeshCylinder->m_fDepth = fDepth;
	pMeshCylinder->m_nSplitX = nSplitX;
	pMeshCylinder->m_nSplitY = nSplitY;
	pMeshCylinder->m_TypeInOut = typeInOut;
	pMeshCylinder->Init();

	return pMeshCylinder;
}



//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneMeshCylinder::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	int nCntVtx = 0;
	float fXpos = -m_fWidth;
	float fYpos = m_fDepth;
	int nCntIdx = 0;
	float fCylinder = 0.0f;
	float fCylinderHight = 0;

	m_nNumVerTex = (m_nSplitX + 1) * (m_nSplitX + 1);
	m_nNumIndex = ((m_nSplitX + 1) * (m_nSplitX + 1) + ((m_nSplitX - 1) * 2) + (m_nSplitX + 1) * (m_nSplitX - 1));

	//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			MESHCYLINDERBG_TEXTURENAME1,
			&m_pTexture);
			// ���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *  m_nNumVerTex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,	//2byte�̃f�[�^
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY < m_nSplitY + 1; nCntY++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
		{
			//���_���̐ݒ�
			if (m_TypeInOut == CSceneMeshCylinder::CYLINDERTYPE_INWARD)
			{
				pVtx[(nCntY + nCntX) + nCntVtx].pos.x = sinf(fCylinder * D3DX_PI) * fXpos;
				pVtx[(nCntY + nCntX) + nCntVtx].pos.y = 0 - fCylinderHight;
				pVtx[(nCntY + nCntX) + nCntVtx].pos.z = cos(fCylinder * D3DX_PI) * fXpos;
			}
			else
			{
				pVtx[(nCntY + nCntX) + nCntVtx].pos.x = sinf(fCylinder * -D3DX_PI) * fXpos;
				pVtx[(nCntY + nCntX) + nCntVtx].pos.y = 42 - fCylinderHight;
				pVtx[(nCntY + nCntX) + nCntVtx].pos.z = cos(fCylinder * -D3DX_PI) * fXpos;
			}
			//�@���̐ݒ�
			//pVtx[(nCntY + nCntX) + nCntVtx].nor = D3DXVECTOR3(sinf(fCylinder), cosf(-fCylinder), cosf(fCylinder));
			pVtx[(nCntY + nCntX) + nCntVtx].nor = D3DXVECTOR3(0.0f,1.0f, 0.0f);
			//���_�J���[
			pVtx[(nCntY + nCntX) + nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			float ftestU = 0 + (nCntX * (1.0f / m_nSplitX));
			float ftestV = 0 + (nCntY * (1.0f / m_nSplitY));
			pVtx[(nCntY + nCntX) + nCntVtx].tex = D3DXVECTOR2(ftestU, ftestV);

			//�p�x1������
			if (fCylinder >= 1.0f)
			{
				fCylinder = -1.0f;
			}
			//X�̕�����/2��1������
			fCylinder += 1.0f / (m_nSplitX / 2);

		}
		//���_���̒l��ێ�
		nCntVtx += m_nSplitX;
		fCylinderHight += m_fDepth;
		fCylinder = 0.0f;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD *pIdx;
	//�C���f�b�N�X�o�b�t�@�����b�N
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxY = 0; nCntIdxY < m_nSplitY; nCntIdxY++)
	{
		for (int nCntIdxX = 0; nCntIdxX < m_nSplitX + 1;nCntIdxX++,nCntIdx++)
		{
			pIdx[0] = nCntIdx + m_nSplitX + 1;
			pIdx[1] = nCntIdx;
			//pIdx��2�����炷
			pIdx += 2;
			if (nCntIdxY < m_nSplitX && nCntIdxX == m_nSplitX)
			{
				pIdx[0] = nCntIdx;
				pIdx[1] = nCntIdx + (m_nSplitX + 1) + 1;
				//pIdx��2�����炷
				pIdx += 2;
			}
		}
	}

	//�C���f�b�N�X�o�b�t�@�����b�N����
	m_pIdxBuff->Unlock();

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_pos.y += m_fDepth;
	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void CSceneMeshCylinder::Uninit(void)
{	//�e�N�X�`���̔j��

	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// �C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

		//����������(���b�V���t�B�[���h��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneMeshCylinder::Update(void)
{
	//���݂̃��[�h���擾
	CManager::MODE mode = CManager::GetMode();
	CPlayer *pPlayer = CTitle::GetPlayer();

	switch (mode)
	{
	case CManager::MODE_GAME:
		//�v���C���[�擾
		pPlayer = CGame::GetPlayer();
		m_pos.x = pPlayer->GetPos().x;
		m_pos.z = pPlayer->GetPos().z;
		/*m_rot = pPlayer->GetRot();
		m_rot += pPlayer->m_apModel[0]->Getrot();

		m_mtxWorld = pPlayer->m_apModel[0]->GetMtxWorld();*/
		break;
	case CManager::MODE_TITLE:
		//�v���C���[�擾
		//pPlayer = CTitle::GetPlayer();
		//m_pos = pPlayer->GetPos();
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneMeshCylinder::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X

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

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);
	//���_�t�H�[�}�b�g��ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVerTex, 0, m_nNumIndex - 2);
}

//=============================================================================
// �ʒu�ݒ�
//=============================================================================
void CSceneMeshCylinder::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// ��]�ݒ�
//=============================================================================
void CSceneMeshCylinder::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �e�N�X�`����ݒ�
//=============================================================================
void CSceneMeshCylinder::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}
