//=============================================================================
//
// ���b�V���t�B�[���h�������� [meshField.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "meshField.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\FIELD\\field004.jpg"	// �n�ʂ̃e�N�X�`����
#define MESHFIELD_SIZE_X		(300.0f)								// �n�ʑ傫��
#define MESHFIELD_SIZE_Z		(300.0f)								// �n�ʑ傫��
#define POLYGON_X				(10)									// �|���S���̐��iX�j
#define POLYGON_Z				(10)									// �|���S���̐��iZ�j
#define FILE_NAME				("����.bin")

//�O���[�o��
float g_aHeght[POLYGON_X][POLYGON_Z] = {0};

//--------------------------------------------
//�V�[�����b�V���t�B�[���h�N���X �R���X�g���N�^
//--------------------------------------------
CSceneMeshField::CSceneMeshField() : CScene(3, CScene::OBJTYPE_MESHFIELD)
{
	m_pTexture = NULL;						//�e�N�X�`���ւ̃|�C���^
	m_pIdxBuffMeshField = NULL;				// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorldMeshField);		//���[���h�}�g���b�N�X
	m_nNumVerTexMeshField = 0;				// ���_��
	m_nNumIndexMeshField = 0;				// �C���f�b�N�X��
	m_nNumPolygonMeshField = 0;				// �|���S����
	m_nSplitX = 0;
	m_nSplitZ = 0;
}

//--------------------------------------------
//�V�[�����b�V���t�B�[���h�N���X�N���X �f�X�g���N�^
//--------------------------------------------
CSceneMeshField::~CSceneMeshField()
{
}

//=============================================================================
// ��������
//=============================================================================
CSceneMeshField * CSceneMeshField::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitZ)
{
	CSceneMeshField *pMeshFiled;

	pMeshFiled = NULL;

	pMeshFiled = new CSceneMeshField;

	pMeshFiled->m_pos = pos;
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
HRESULT CSceneMeshField::Init(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pTexture = NULL;						//�e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;
	m_pIdxBuffMeshField = NULL;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	// ���_���̍쐬
	MakeVertexMeshField(pDevice);

	// �|���S���̏���ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void  CSceneMeshField::Uninit(void)
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
void  CSceneMeshField::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void  CSceneMeshField::Draw(void)
{
	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorldMeshField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
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
void CSceneMeshField::MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	int nVtxCounter = 0;
	int nIdxCounter = 0;
	int nCntIdxZ;
	int nCntIdxX;
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	// ���_��
	m_nNumVerTexMeshField = (m_nSplitX + 1) * (m_nSplitZ + 1);

	// �C���f�b�N�X��
	m_nNumIndexMeshField = (m_nSplitX + 1) * (m_nSplitZ + 1) + (2 * (m_nSplitZ - 1)) + (m_nSplitX + 1) * (m_nSplitZ - 1);

	// �|���S����
	m_nNumPolygonMeshField = m_nNumIndexMeshField - 2;

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

	//�ϐ��錾
	int nCntMeshZ;
	int nCntMeshX;

	//���_�A�@���A�J���[�A�e�N�X�`���̒��_�ݒ�
	for (nCntMeshZ = 0; nCntMeshZ <= m_nSplitZ; nCntMeshZ++)
	{//�c��
		for (nCntMeshX = 0; nCntMeshX <= m_nSplitX; nCntMeshX++)
		{//����
		 // ���_�̍��W
			pVtx[0].pos = D3DXVECTOR3(((nCntMeshX * m_fWidth) / m_nSplitX), 0.0f/*rand() % 100 * 1.0f*/, ((nCntMeshZ * -m_fDepth) / m_nSplitZ));

			// �@���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(nCntMeshX * 1.0f, nCntMeshZ * 1.0f);

			pVtx += 1;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	// �@���ݒ�
	//NormalSet();

	// �C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD *pIdx;
	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxZ = 0; nCntIdxZ < m_nSplitZ; nCntIdxZ++)
	{
		for (nCntIdxX = 0; nCntIdxX < m_nSplitX + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + m_nSplitX + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxZ < m_nSplitZ - 1 && nCntIdxX == m_nSplitX)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (m_nSplitX + 1) + 1;
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
void CSceneMeshField::SetHeight(D3DXVECTOR3 pos, float fValue, float fRange)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0, nCntVtx = 0; nCntZ < m_nSplitZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
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
}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CSceneMeshField::Setpos(D3DXVECTOR3 pos)
{
}

//=============================================================================
// �n�ʂ̍�����Ԃ�(�u�[����Ԃ�)
//=============================================================================
bool CSceneMeshField::GetHeightbool(D3DXVECTOR3 &pos)
{
#if 1
	//�ϐ��錾
	D3DXVECTOR3 vec0;
	D3DXVECTOR3 vec1;
	D3DXVECTOR3 nor;
	D3DXVECTOR3 VtxPos[3];
	D3DXVECTOR3 VtxNor[6];
	int			nNumber;
	float		fHeight;

	//�v���C���[�ƃ��b�V���t�B�[���h�̈ʒu�̍������o��
	D3DXVECTOR3 posMtx = pos - m_pos;

	int test1, test2;
	test1 = m_nSplitX;
	test2 = m_nSplitZ;
	//���݃v���C���[�����u���b�N�ڂɂ��邩���m�F���鎮
	int			nMeshX = (int)((posMtx.x) / (m_fWidth / m_nSplitX));
	int			nMeshZ = (int)((posMtx.z) / (m_fDepth / m_nSplitZ) * -1);

	if (nMeshX >= m_nSplitX || nMeshX < 0)
	{
		return false;
	}
	if (nMeshZ >= m_nSplitZ || nMeshZ < 0)
	{
		return false;
	}

	//���݂̏�������Ă���u���b�N�̒��_�̏o����
	int			nMeshLU = nMeshX + nMeshZ * (m_nSplitX + 1);					//��@0�Ԗڂ̒��_
	int			nMeshRU = (nMeshX + 1) + nMeshZ * (m_nSplitX + 1);			//��@1�Ԗڂ̒��_
	int			nMeshLD = nMeshX + (nMeshZ + 1) * (m_nSplitX + 1);			//��@3�Ԗڂ̒��_
	int			nMeshRD = (nMeshX + 1) + (nMeshZ + 1) * (m_nSplitX + 1);		//��@4�Ԗڂ̒��_

																			//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (posMtx.x < 0 || posMtx.x > pVtx[m_nSplitX].pos.x)
	{
		return false;
	}
	if (posMtx.z > 0 || posMtx.z > pVtx[m_nSplitX].pos.z)
	{
		return false;
	}

	//CDebugProc::Print(1,"���݂̃u���b�N�@���� %d�@�u���b�N��\n", nMeshX);
	//CDebugProc::Print(1,"���݂̃u���b�N�@�c�� %d�@�u���b�N��\n", nMeshZ);

	//�x�N�g���v�Z�� �ړI - ����
	vec0 = pVtx[nMeshLU].pos - pVtx[nMeshRD].pos;
	//�x�N�g���v�Z�� �����̈ʒu�@- ����
	vec1 = posMtx - pVtx[nMeshRD].pos;

	if ((vec0.x * vec1.z) - (vec0.z * vec1.x) <= 0)
	{//�O�p�`���E�ɂ���ꍇ
	//	CDebugProc::Print(1,"MeshField���E�͈� : TURE\n");
		vec0 = (posMtx - pVtx[nMeshLU].pos);

		//�e���_�̕ۊ�
		VtxPos[0] = pVtx[nMeshRU].pos;
		VtxPos[1] = pVtx[nMeshRD].pos;
		VtxPos[2] = pVtx[nMeshLU].pos;

		nNumber = 3;
	}
	else if ((vec0.x * vec1.z) - (vec0.z * vec1.x) >= 0)
	{//�O�p�`��荶�ɂ���ꍇ
	//	CDebugProc::Print(1,"MeshField�����͈� : TURE\n");
		vec0 = (posMtx - pVtx[nMeshRD].pos);

		//�e���_�̕ۊ�
		VtxPos[0] = pVtx[nMeshLD].pos;
		VtxPos[1] = pVtx[nMeshLU].pos;
		VtxPos[2] = pVtx[nMeshRD].pos;

		nNumber = 0;
	}

	//�����@���������O�ɕۑ�����
	fHeight = VtxPos[0].y;

	//3���_��0�̒l���Ђ��Ă����Ė@���ƃv���C���[�̃x�N�g���𒼌������邽��
	VtxPos[2].y -= VtxPos[0].y;
	VtxPos[1].y -= VtxPos[0].y;
	VtxPos[0].y -= VtxPos[0].y;

	//�@���̌v�Z
	vec0 = VtxPos[1] - VtxPos[0];
	vec1 = VtxPos[2] - VtxPos[0];

	//�O�ς̌v�Z
	D3DXVec3Cross(&nor, &vec0, &vec1);
	//���K��
	D3DXVec3Normalize(&nor, &nor);
	//�v���C���[�ւ̃x�N�g��
	vec0 = posMtx - VtxPos[0];
	//���ό���
	((vec0.x * pVtx[nNumber].nor.x) + (vec0.y * pVtx[nNumber].nor.y) + (vec0.z * pVtx[nNumber].nor.z));
	//���όv�Z��
	vec0.y = (-(vec0.x * nor.x) - (vec0.z * nor.z)) / nor.y;
	//�v���C���[��y�ɓ����
	posMtx.y = vec0.y + fHeight + m_pos.y;
	//���_�o�b�t�@�̃A�����b�N����
	m_pVtxBuff->Unlock();

	if (pos.y < posMtx.y)
	{// �v���C���[��n�ʂɏ悹��
		pos.y = posMtx.y;
		return true;
	}
	return false;
#endif
}

//=============================================================================
// �@���̐ݒ�
//=============================================================================
void CSceneMeshField::NormalSet(void)
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

	for (int nCntZ = 0, nCntPolygon = 0, nCntNorPolygon = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 Vec0, Vec1, Vec2;
			D3DXVECTOR3 nor;

			pPos0 = &pVtx[(nCntZ + nCntX + nCntPolygon)].pos;
			pPos1 = &pVtx[(nCntZ + nCntX + nCntPolygon) + m_nSplitX + 1].pos;
			pPos2 = &pVtx[(nCntZ + nCntX + nCntPolygon) + m_nSplitX + 2].pos;
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
		nCntPolygon += m_nSplitX;
		nCntNorPolygon += (m_nSplitX * 2) - 2;
	}

	//�m�F�p�ϐ�
	int test, test2, test3, test4, test5, test6,VtxNum;
	//�@���̕���
	for (int nCntZ = 0, nCntPolygon = 0; nCntZ < m_nSplitZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
		{

			if (nCntZ == 0)
			{	//��
				if (nCntX == 0)
				{	//���[
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntX > 0 && nCntX < m_nSplitX)
				{	//�� ���_��3�d�Ȃ�
					pVtx[nCntX].nor = (m_aNor[(nCntX * 2) - 1] + m_aNor[(nCntX * 2) - 1 + 1]
						+ m_aNor[(nCntX * 2) - 1 + 2]) / 3;
				}
				else if (nCntX == m_nSplitX)
				{	//�E�[
					pVtx[m_nSplitX].nor = m_aNor[m_nSplitX * 2 - 1];
				}
			}
			else if (nCntZ > 0 && nCntZ < m_nSplitZ)
			{//��
				if (nCntX == 0)
				{	//���[
					pVtx[((m_nSplitX + 1) * nCntZ)].nor =
						(m_aNor[(nCntZ)*(m_nSplitX * 2) - (m_nSplitX * 2)]
							+ m_aNor[(nCntZ)*(m_nSplitX * 2)]
							+ m_aNor[(nCntZ)*(m_nSplitX * 2) + 1]) / 3;
				}
				else if (nCntX == m_nSplitX)
				{	//�E�[
					pVtx[((nCntZ + 1) * m_nSplitX) + nCntZ].nor =
						(m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntZ - 1)))]	//2
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntZ - 1))) + 1]		//3
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntZ - 1))) + ((m_nSplitX * 2) + 1)]) / 3;	//7
				}
				else
				{	//�� ���_��6�d�Ȃ�
					pVtx[(m_nSplitX + 1 + nCntX) + ((nCntZ - 1) * (m_nSplitX + 1))].nor = (
						m_aNor[(nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2)]
						+ m_aNor[(nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2) + 2]
						+ m_aNor[(((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2)]
						+ m_aNor[(((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2) + 2]) / 6;

					test  = (nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2);
					test2 = (nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2) + 1;
					test3 = (nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2) + 2;

					test4 = (((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2);
					test5 = (((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2) + 1;
					test6 = (((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2) + 2;
					VtxNum = (m_nSplitX + 1 + nCntX) + ((nCntZ - 1) * (m_nSplitX + 1));
				}
			}
			else if (nCntZ == m_nSplitZ)
			{//��
				if (nCntX == 0)
				{	//���[
					pVtx[(m_nSplitX + 1) * m_nSplitZ].nor = m_aNor[m_nSplitX * (m_nSplitZ - 1) * 2];
				}
				else if (nCntX > 0 && nCntX < m_nSplitX)
				{	//�� ���_��3�d�Ȃ�
					pVtx[nCntZ * m_nSplitX + nCntX].nor
						= (m_aNor[(m_nSplitX * 2) * (m_nSplitZ - 1) + ((nCntX - 1) * 2)]
						+ m_aNor[(m_nSplitX * 2) * (m_nSplitZ - 1) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(m_nSplitX * 2) * (m_nSplitZ - 1) + ((nCntX - 1) * 2) + 2]) / 3;
				}
				else if (nCntX == m_nSplitX)
				{	//�E�[
					pVtx[m_nSplitX * m_nSplitZ + (m_nSplitX + m_nSplitZ)].nor
						= (m_aNor[m_nSplitX * m_nSplitZ * 2 - 2]
							+ m_aNor[m_nSplitX * m_nSplitZ * 2 - 1]) / 2;

					test = m_nSplitX * m_nSplitZ * 2 - 2;
					test2 = m_nSplitX * m_nSplitZ * 2 - 1;
				}
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

#endif
}

//=============================================================================
// �e�N�X�`���̐ݒ�
//=============================================================================
void CSceneMeshField::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}