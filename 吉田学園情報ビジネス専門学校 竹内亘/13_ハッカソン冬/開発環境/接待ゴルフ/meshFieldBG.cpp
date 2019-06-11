//=============================================================================
//
// ���b�V���t�B�[���h�������� [meshField.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "meshFieldBG.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\field004.jpg"	// �n�ʂ̃e�N�X�`����
#define MESHFIELD_SIZE_X		(10.0f)							// �n�ʑ傫��
#define MESHFIELD_SIZE_Z		(10.0f)							// �n�ʑ傫��
#define POLYGON_X				(50)							// �|���S���̐��iX�j
#define POLYGON_Z				(50)							// �|���S���̐��iZ�j
#define FILE_NAME				("data\\����.bin")
//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
//LPDIRECT3DVERTEXBUFFER9		CSceneMeshFieldBG::m_pVtxBuff = NULL;

//�O���[�o��
//float g_aHeght[10 + 1][1 + 1] = { 0 };
float g_aHeght[POLYGON_X][POLYGON_Z] = { 0 };

//--------------------------------------------
//�V�[�����b�V���t�B�[���h�N���X �R���X�g���N�^
//--------------------------------------------
CSceneMeshFieldBG::CSceneMeshFieldBG() : CScene(4, CScene::OBJTYPE_MESHFIELD)
{
	m_MeshFiled = {};						//�V�[��3D�\����
	m_pTexture = NULL;						//�e�N�X�`���ւ̃|�C���^
	m_pIdxBuffMeshField = NULL;				// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	m_mtxWorldMeshField = {};				// ���[���h�}�g���b�N�X
	m_nNumVerTexMeshField = 0;				// ���_��
	m_nNumIndexMeshField = 0;				// �C���f�b�N�X��
	m_nNumPolygonMeshField = 0;				// �|���S����
	m_nSplitX = 0;
	m_nSplitZ = 0;
	m_fWidth = 0;
	m_fDepth = 0;

}

//--------------------------------------------
//�V�[�����b�V���t�B�[���h�N���X�N���X �f�X�g���N�^
//--------------------------------------------
CSceneMeshFieldBG::~CSceneMeshFieldBG()
{
}

//=============================================================================
// ��������
//=============================================================================
CSceneMeshFieldBG * CSceneMeshFieldBG::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitZ)
{
	CSceneMeshFieldBG *pMeshFiled;

	pMeshFiled = new CSceneMeshFieldBG;

	pMeshFiled->m_Pos = pos;
	pMeshFiled->m_fWidth = fWidth;
	pMeshFiled->m_fDepth = fDepth;
	pMeshFiled->m_nSplitX = nSplitX;
	pMeshFiled->m_nSplitZ = nSplitZ;
	pMeshFiled->Init();

	return pMeshFiled;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneMeshFieldBG::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

												// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	// ���_���̍쐬
	MakeVertexMeshField(pDevice);

	// �|���S���̏���ݒ�
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MeshFiled.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MeshFiled.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�t�@�C�������[�h
	LoadHeight();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void  CSceneMeshFieldBG::Uninit(void)
{
	// �e�N�X�`���̔j��
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
	if (m_pIdxBuffMeshField != NULL)
	{
		m_pIdxBuffMeshField->Release();
		m_pIdxBuffMeshField = NULL;
	}

	//����������(���b�V���t�B�[���h��j��)
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void  CSceneMeshFieldBG::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	int nVtxCounter = 0;

	////�t�@�C���ɃZ�[�u
	//if (pInput->GetPress(DIK_RSHIFT) == true)
	//{
	//	SaveHeight();
	//}



	////�C�ӂ̃L�[1
	//if (pInput->GetTrigger(DIK_2) == true)
	//{
	//	//m_nSelectVtx += 1;
	//}
	////�C�ӂ̃L�[2
	//if (pInput->GetTrigger(DIK_1) == true)
	//{
	//	//m_nSelectVtx -= 1;
	//}
//
//	VERTEX_3D *pVtx;
//	//���_�o�b�t�@�����b�N
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//#ifdef  _DEBUG
//	//CDebugProc::Print(1, " pvtx[%d]  : ( %.1f ,%.1f ,%.1f )\n", m_nSelectVtx, pVtx[m_nSelectVtx].nor.x, pVtx[m_nSelectVtx].nor.y, pVtx[m_nSelectVtx].nor.z);
//#endif
//	// ���_�o�b�t�@���A�����b�N����
//	m_pVtxBuff->Unlock();
//
}

//=============================================================================
// �`�揈��
//=============================================================================
void  CSceneMeshFieldBG::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_MeshFiled.rot.y, m_MeshFiled.rot.x, m_MeshFiled.rot.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshField);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuffMeshField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVerTexMeshField, 0, m_nNumPolygonMeshField);

}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void CSceneMeshFieldBG::MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxZ;
	int nCntVtxX;
	int nCntIdxZ;
	int nCntIdxX;
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	// ���_��
	m_nNumVerTexMeshField = (POLYGON_X + 1) * (POLYGON_Z + 1);

	// �C���f�b�N�X��
	m_nNumIndexMeshField = (POLYGON_X + 1) * (POLYGON_Z + 1) + (2 * (POLYGON_Z - 1)) + (POLYGON_X + 1) * (POLYGON_Z - 1);

	// �|���S����
	m_nNumPolygonMeshField = m_nNumIndexMeshField - 2;


	D3DXVECTOR3 pos[10000];


	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVerTexMeshField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndexMeshField,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,						// 16�r�b�g�̃f�[�^���m��
		D3DPOOL_MANAGED,
		&m_pIdxBuffMeshField,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxZ = 0; nCntVtxZ < POLYGON_Z + 1; nCntVtxZ++)
	{
		for (nCntVtxX = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
		{
			// ���_���W�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].pos = D3DXVECTOR3(m_Pos.x + (nCntVtxX * m_fWidth), m_Pos.y, m_Pos.z - (nCntVtxZ * m_fDepth));
			// �@���̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// �e�N�X�`�����W�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].tex = D3DXVECTOR2(0.0f + (nCntVtxX/* * (1.0f / POLYGON_X)*/), 0.0f + (nCntVtxZ /** (1.0f / POLYGON_Z)*/));
		}
		nVtxCounter += POLYGON_X;
	}

#if 0
	//�@���p
	D3DXVECTOR3 Vec0, Vec1, nor0, nor1;
	int nVtx = 0;

	for (int nCntZ = 0, nCntPolygon = 0, nCntVtx = 0; nCntZ < POLYGON_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 Vec0, Vec1, Vec2;
			D3DXVECTOR3 nor;

			pPos0 = &pVtx[(nCntZ + nCntX + nCntVtx)].pos;
			pPos1 = &pVtx[(nCntZ + nCntX + nCntVtx) + POLYGON_Z + 1].pos;
			pPos2 = &pVtx[(nCntZ + nCntX + nCntVtx) + POLYGON_Z + 2].pos;
			pPos3 = &pVtx[(nCntZ + nCntX + nCntVtx) + 1].pos;

			//����̃|���S����2�̃x�N�g������@�����Z�o
			Vec0 = *pPos1 - *pPos0;
			Vec1 = *pPos2 - *pPos0;
			// X,Y,Z�̏��Ł�
			D3DXVec3Cross(&nor, &Vec1, &Vec0);
			//���K��
			D3DXVec3Normalize(&nor, &nor);
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntPolygon)] = nor;

			//��������̃|���S���̃x�N�g������@�����Z�o
			Vec1 = *pPos2 - *pPos0;
			Vec2 = *pPos3 - *pPos0;
			// X,Y,Z�̏��Ł�
			D3DXVec3Cross(&nor, &Vec2, &Vec1);
			//���K��
			D3DXVec3Normalize(&nor, &nor);
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntPolygon) + 1] = nor;
		}
		nCntPolygon += POLYGON_X * 2 - 2;
		nCntVtx += POLYGON_X;
	}

	//�@���̕���
	for (int nCntZ = 0, nCntPolygon = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{
			if (nCntZ == 0)
			{	//��
				if (nCntX == 0)
				{	//���[
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntX > 0 && nCntX < POLYGON_X)
				{	//�� ���_��3�d�Ȃ�
					pVtx[nCntX].nor = (m_aNor[(nCntX * 2) - 1] + m_aNor[(nCntX * 2) - 1 + 1]
						+ m_aNor[(nCntX * 2) - 1 + 2]) / 3;
				}
				else if (nCntX == POLYGON_X)
				{	//�E�[
					pVtx[POLYGON_X].nor = m_aNor[POLYGON_X * 2 - 1];
				}
			}
			else if (nCntZ > 0 && nCntZ < POLYGON_Z)
			{//��
				if (nCntX == 0)
				{	//���[
					pVtx[((POLYGON_X + 1) * nCntZ)].nor =
						(m_aNor[(nCntZ)*(POLYGON_X * 2) - (POLYGON_X * 2)]
							+ m_aNor[(nCntZ)*(POLYGON_X * 2)]
							+ m_aNor[(nCntZ)*(POLYGON_X * 2) + 1]) / 3;
				}
				else if (nCntX == POLYGON_X)
				{	//�E�[
					pVtx[((nCntZ + 1) * POLYGON_X) + nCntZ].nor =
						(m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1)))]	//2
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1))) + 1]		//3
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1))) + ((POLYGON_X * 2) + 1)]) / 3;	//7
				}
				else
				{	//�� ���_��6�d�Ȃ�
					pVtx[(POLYGON_X + 1 + nCntX) + ((nCntZ - 1) * (POLYGON_X + 1))].nor = (
						m_aNor[(nCntZ - 1) * (POLYGON_X * 2)]
						+ m_aNor[(nCntZ - 1) * (POLYGON_X * 2) + 1]
						+ m_aNor[(nCntZ - 1) * (POLYGON_X * 2) + 2]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2))]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + 1]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + 2]) / 6;
				}
			}
			else if (nCntZ == POLYGON_Z)
			{//��
				if (nCntX == 0)
				{	//���[
					pVtx[(POLYGON_X + 1) * POLYGON_Z].nor = m_aNor[POLYGON_X * (POLYGON_Z - 1) * 2];
				}
				else if (nCntX > 0 && nCntX < POLYGON_X)
				{	//�� ���_��3�d�Ȃ�
					pVtx[nCntZ * POLYGON_X + nCntX].nor = (m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + nCntX]
						+ m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + nCntX + 1]
						+ m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + nCntX + 2]) / 3;
				}
				else if (nCntX == POLYGON_X)
				{	//�E�[
					pVtx[POLYGON_X * POLYGON_Z + (POLYGON_X + POLYGON_Z)].nor
						= (m_aNor[POLYGON_X * POLYGON_Z * 2 - 2] + m_aNor[POLYGON_X * POLYGON_Z * 2 - 1]) / 2;;
				}
			}
		}
	}

#endif

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	NormalSet();


	// �C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD *pIdx;
	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxZ = 0; nCntIdxZ < POLYGON_Z; nCntIdxZ++)
	{
		for (nCntIdxX = 0; nCntIdxX < POLYGON_X + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + POLYGON_X + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxZ < POLYGON_Z - 1 && nCntIdxX == POLYGON_X)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (POLYGON_X + 1) + 1;
				pIdx += 2;
			}
		}
	}
	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuffMeshField->Unlock();
}

//=============================================================================
// ���b�V���t�B�[���h�̕ύX����
//=============================================================================
void CSceneMeshFieldBG::SetHeight(D3DXVECTOR3 pos, float fValue, float fRange)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0, nCntVtx = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{
			//POS����Ώۂ̒��_�܂ł̋���
			float fLength = sqrtf(
				//X�̋��������߂�@X�̋�����2��
				(pos.x - pVtx->pos.x) * (pos.x - pVtx->pos.x)
				//Z�̋��������߂�@Z�̋�����2��
				+ (pos.z - pVtx->pos.z) * (pos.z - pVtx->pos.z));
			if (fLength <= fRange)
			{	//�͈͓��ł̋����̉���������
				//			�R�T�C���J�[�u��̕��� * �䗦(%)
				float fHeight = cosf((D3DX_PI * 0.5f) * (fLength / fRange)) * fValue;
				pVtx->pos.y += fHeight;
			}
			//�ۑ�
			g_aHeght[nCntZ][nCntX] = pVtx->pos.y;
			pVtx++;
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	NormalSet();
}

//=============================================================================
// �Z�[�u����
//=============================================================================
void CSceneMeshFieldBG::SaveHeight(void)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�t�@�C��
	FILE *pFile;

	//��������
	pFile = fopen(FILE_NAME, "wb");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{	//�t�@�C���ǂݍ���
		fwrite(&g_aHeght[0][0], sizeof(float), POLYGON_X * POLYGON_Z, pFile);
	}
	else
	{	//�t�@�C�����J���Ȃ�����
		printf("�t�@�C�����J���܂���ł���\n");
	}
	//�t�@�C�������
	fclose(pFile);
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ���[�h����
//=============================================================================
void CSceneMeshFieldBG::LoadHeight(void)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�t�@�C��
	FILE *pFile;

	//�t�@�C�����J�� �ǂݍ���
	pFile = fopen(FILE_NAME, "rb");
	//NULL�`�F�b�N
	if (pFile != NULL)
	{	//�t�@�C���ǂݍ���
		fread(&g_aHeght[0][0], sizeof(float), POLYGON_X * POLYGON_Z, pFile);
	}
	else
	{	//�t�@�C�����J���Ȃ�����
		printf("�t�@�C�����J���܂���ł���\n");
	}
	//�t�@�C�������
	fclose(pFile);
	//��������

	for (int nCntZ = 0, nCntVtx = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{
			//�ۑ�
			 pVtx->pos.y = g_aHeght[nCntZ][nCntX];
			pVtx++;
		}
	}
	//for (int nCntZ = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	//{
	//	for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
	//	{
	//		pVtx->pos.y = g_aHeght[nCntZ][nCntX];
	//		pVtx++;
	//	}
	//}
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	//�@���̍X�V
	NormalSet();
}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CSceneMeshFieldBG::Setpos(D3DXVECTOR3 pos)
{
}

//=============================================================================
// ���_�擾����
//=============================================================================
//LPDIRECT3DVERTEXBUFFER9 CSceneMeshFieldBG::GetVtx(void)
//{
//	return m_pVtxBuff;
//}

//=============================================================================
// �n�ʂ̍�����Ԃ�
//=============================================================================
float CSceneMeshFieldBG::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;

#if 1
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fGaiseki;
	int nVtx[4];
	int nPolyNumX, nPolyNumZ;

	//�O�p�`�p
	D3DXVECTOR3 nor0, nor1, Vec0, Vec1,Vec2,Vec3;

	//�ǂ̃|���S���ɏ���Ă��邩���߂�
	nPolyNumX = ((int)(pos.x / m_fWidth));
	nPolyNumZ = ((int)(pos.z / m_fDepth));

	nPolyNumZ *= -1;

	//�v���C���[���ǂ��̒��_�������Ă��邩
	nVtx[0] = nPolyNumX + (nPolyNumZ + 1) * (POLYGON_X + 1);		//����
	nVtx[1] = nPolyNumX + (nPolyNumZ * (POLYGON_X + 1));			//����
	nVtx[2] = (nPolyNumX + 1) + (nPolyNumZ + 1) * (POLYGON_X + 1);	//�E��
	nVtx[3] = (nPolyNumX + 1) + (nPolyNumZ * (POLYGON_X + 1));		//�E��

	//�|���S���̐^�񒆎΂�
	Vec0 = pVtx[nVtx[1]].pos - pVtx[nVtx[2]].pos;
	//�v���C���[���ǂ����ɏ���Ă��邩
	Vec1 = pos - pVtx[nVtx[2]].pos;
	//�O��
	fGaiseki = (Vec0.z * Vec1.x) - (Vec0.x * Vec1.z);
	//�O�p�`�͈̔͊i�[�p
	D3DXVECTOR3 sankaku[3];;

	if (fGaiseki <= 0)
	{	//�͈́i�����j
		sankaku[0] = pVtx[nVtx[0]].pos;
		sankaku[1] = pVtx[nVtx[1]].pos;
		sankaku[2] = pVtx[nVtx[2]].pos;
	}
	else
	{	//�͈́i�E���j
		sankaku[0] = pVtx[nVtx[3]].pos;
		sankaku[1] = pVtx[nVtx[2]].pos;
		sankaku[2] = pVtx[nVtx[1]].pos;
	}

	float fPosY;
	//Y���W���O�� �΂߂̏�蕝
	fPosY = sankaku[0].y;

	sankaku[0].y -= fPosY;
	sankaku[1].y -= fPosY;
	sankaku[2].y -= fPosY;

	//�@�������߂�
	Vec2 = sankaku[1] - sankaku[0];
	Vec3 = sankaku[2] - sankaku[0];
	//���K������
	D3DXVec3Cross(&nor0, &Vec2, &Vec3);
	D3DXVec3Normalize(&nor0, &nor0);
	//�v���C���[�̈ʒu�����߂�
	D3DXVECTOR3 PlayerPos = pos - sankaku[0];

	//���ς̌v�Z
	m_Height = (-(nor0.x * PlayerPos.x) - (nor0.z * PlayerPos.z)) / nor0.y + fPosY;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
#endif
	return m_Height;
}

//=============================================================================
// �@���̐ݒ�
//=============================================================================
void CSceneMeshFieldBG::NormalSet(void)
{
#if 1
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^
						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�@�������߂�

	//�@���p
	D3DXVECTOR3 Vec0, Vec1, nor0, nor1;
	int Testvec0, Testvec1;

	for (int nCntZ = 0, nCntPolygon = 0, nCntNorPolygon = 0; nCntZ < POLYGON_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 Vec0, Vec1, Vec2;
			D3DXVECTOR3 nor;

			pPos0 = &pVtx[(nCntZ + nCntX + nCntPolygon)].pos;
			pPos1 = &pVtx[(nCntZ + nCntX + nCntPolygon) + POLYGON_X + 1].pos;
			pPos2 = &pVtx[(nCntZ + nCntX + nCntPolygon) + POLYGON_X + 2].pos;
			pPos3 = &pVtx[(nCntZ + nCntX + nCntPolygon) + 1].pos;

			//����̃|���S����2�̃x�N�g������@�����Z�o
			Vec0 = *pPos1 - *pPos0;
			Vec1 = *pPos2 - *pPos0;
			Vec2 = *pPos3 - *pPos0;

			// X,Y,Z�̏��Ł�
			D3DXVec3Cross(&nor, &Vec1, &Vec0);
			//���K��
			D3DXVec3Normalize(&nor, &nor);
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntNorPolygon)] = nor;
			Testvec0 = ((nCntZ * 2) + (nCntX * 2) + nCntNorPolygon);

			// X,Y,Z�̏��Ł�
			D3DXVec3Cross(&nor, &Vec2, &Vec1);
			//���K��
			D3DXVec3Normalize(&nor, &nor);
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntNorPolygon) + 1] = nor;
			Testvec1 = ((nCntZ * 2) + (nCntX * 2) + nCntNorPolygon) + 1;
		}
		nCntPolygon += POLYGON_X;
		nCntNorPolygon += (POLYGON_X * 2) - 2;
	}

	//�m�F�p�ϐ�
	int test, test2, test3, test4, test5, test6,VtxNum;
	//�@���̕���
	for (int nCntZ = 0, nCntPolygon = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{

			if (nCntZ == 0)
			{	//��
				if (nCntX == 0)
				{	//���[
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntX > 0 && nCntX < POLYGON_X)
				{	//�� ���_��3�d�Ȃ�
					pVtx[nCntX].nor = (m_aNor[(nCntX * 2) - 1] + m_aNor[(nCntX * 2) - 1 + 1]
						+ m_aNor[(nCntX * 2) - 1 + 2]) / 3;
				}
				else if (nCntX == POLYGON_X)
				{	//�E�[
					pVtx[POLYGON_X].nor = m_aNor[POLYGON_X * 2 - 1];
				}
			}
			else if (nCntZ > 0 && nCntZ < POLYGON_Z)
			{//��
				if (nCntX == 0)
				{	//���[
					pVtx[((POLYGON_X + 1) * nCntZ)].nor =
						(m_aNor[(nCntZ)*(POLYGON_X * 2) - (POLYGON_X * 2)]
							+ m_aNor[(nCntZ)*(POLYGON_X * 2)]
							+ m_aNor[(nCntZ)*(POLYGON_X * 2) + 1]) / 3;
				}
				else if (nCntX == POLYGON_X)
				{	//�E�[
					pVtx[((nCntZ + 1) * POLYGON_X) + nCntZ].nor =
						(m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1)))]	//2
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1))) + 1]		//3
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1))) + ((POLYGON_X * 2) + 1)]) / 3;	//7
				}
				else
				{	//�� ���_��6�d�Ȃ�
					pVtx[(POLYGON_X + 1 + nCntX) + ((nCntZ - 1) * (POLYGON_X + 1))].nor = (
						m_aNor[(nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2)]
						+ m_aNor[(nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2) + 2]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2)]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2) + 2]) / 6;

					test  = (nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2);
					test2 = (nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2) + 1;
					test3 = (nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2) + 2;

					test4 = (((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2);
					test5 = (((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2) + 1;
					test6 = (((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2) + 2;
					VtxNum = (POLYGON_X + 1 + nCntX) + ((nCntZ - 1) * (POLYGON_X + 1));
				}
			}
			else if (nCntZ == POLYGON_Z)
			{//��
				if (nCntX == 0)
				{	//���[
					pVtx[(POLYGON_X + 1) * POLYGON_Z].nor = m_aNor[POLYGON_X * (POLYGON_Z - 1) * 2];
				}
				else if (nCntX > 0 && nCntX < POLYGON_X)
				{	//�� ���_��3�d�Ȃ�
					pVtx[nCntZ * POLYGON_X + nCntX].nor
						= (m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2)]
						+ m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2) + 2]) / 3;

					///test = (POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2);
					//test2 = (POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2) + 1;
					//test3 = (POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2) + 2;
				}
				else if (nCntX == POLYGON_X)
				{	//�E�[
					pVtx[POLYGON_X * POLYGON_Z + (POLYGON_X + POLYGON_Z)].nor
						= (m_aNor[POLYGON_X * POLYGON_Z * 2 - 2]
							+ m_aNor[POLYGON_X * POLYGON_Z * 2 - 1]) / 2;

					test = POLYGON_X * POLYGON_Z * 2 - 2;
					test2 = POLYGON_X * POLYGON_Z * 2 - 1;
				}
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

#endif
}
