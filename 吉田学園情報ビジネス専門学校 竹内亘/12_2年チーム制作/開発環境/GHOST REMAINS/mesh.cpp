//=============================================================================
//
// mesh���� [mesh.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "camera.h"
#include "mesh.h"
#include "dungeon.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME		"data\\TEXTURE\\�s�X�n02.jpg"						//�ǂݍ��ރe�N�X�`���t�@�C��
#define BULOCK_X					(20.0f)											//�u���b�N�̉��s
#define BULOCK_Y					(400.0f)											//�u���b�N�̉��s
#define BULOCK_Z					(20.0f)											//�u���b�N�̉��s
#define VERTEX						((VERTICAL + 1) * (CORSS + 1))						//�w�肵���c�Ɖ�+�P�̒l
#define IDX							((VERTICAL * CORSS) * 2 + (VERTICAL - 1) * 4 + 2)	//�C���f�b�N�X�̎�
#define POLYGON						((VERTICAL * CORSS) * 2 + (VERTICAL - 1) * 4)		//�|���S�����̎�
#define WALL_CURVE					(3.0f)		//�ǂ̋Ȃ���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//==================================================================================================//
//    * ���b�V���̃Z�b�g�֐� *
//==================================================================================================//
void CMesh::Set(TYPE type, D3DXVECTOR3 pos, int nVertical, int nCorss, bool bMesh)	//�Q�[�W�Z�b�g����
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	m_Type = type;
	m_pos = pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nVertical = nVertical;
	m_nCross = nCorss;
	m_bMesh = bMesh;
	m_nNumVertex = (nVertical + 1) * (nCorss + 1);		//���_��
	m_nNumIdx = (nVertical * nCorss) * 2 + (nVertical - 1) * 4 + 2;				//�C���f�b�N�X��
	m_nNumPolygon = (nVertical * nCorss) * 2 + (nVertical - 1) * 4;		//�|���S����

	//���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL );

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer ( sizeof(WORD) * m_nNumIdx, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIdxBuff, NULL );
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
	WORD * pIdx;		//�C���f�b�N�X�f�[�^�ւ̃|�C���^

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	//���_�A�@���A�J���[�A�e�N�X�`���̒��_�ݒ�
	for (int nCntVertical = 0; nCntVertical < nVertical + 1; nCntVertical++)
	{//�c��
		for (int nCntCorss = 0; nCntCorss < nCorss + 1; nCntCorss++)
		{//����
		 //���_���W
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[0].tex = D3DXVECTOR2(nCntCorss*0.5f, nCntVertical*0.5f);
			switch (type)
			{
			case TYPE_FIELD: 
				pVtx[0].pos = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * nCntCorss, 0.0f, FIELD_SIZE * 2 - FIELD_SIZE * nCntVertical);
				//CScene3D *p3D;
				//if (SceneCreate(p3D, 3))
				//{
				//	p3D->Set(pVtx[0].pos + m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f),
				//		D3DXVECTOR3(2.0f, 2.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
				//}
				break;
			case TYPE_WALL:		
				pVtx[0].pos = D3DXVECTOR3(-FIELD_SIZE * nCntCorss, FIELD_SIZE * nCntVertical, FIELD_SIZE * nCntCorss);
				pVtx[0].tex = D3DXVECTOR2(nCntCorss*2.0f, nCntVertical*0.5f);
				break;
			case TYPE_CEILING:
				pVtx[0].pos = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * nCntCorss, 2000.0f, FIELD_SIZE * 2 + FIELD_SIZE * nCntVertical);
				break;
			}
			
			pVtx += 1;
		}
	}

	m_pVtxBuff->Unlock();	//���_�o�b�t�@�̃A�����b�N����

	//�C���f�b�N�X�o�b�t�@�̃��b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X�̐ݒ�
	for (int nCount_yz = 0; nCount_yz < nVertical; nCount_yz++)
	{// yz���J�E���g
		for (int nCount_x = 0; nCount_x < nCorss + 1; nCount_x++)
		{// x���J�E���g
		 // �C���f�b�N�X���̐ݒ�
			pIdx[0] = (WORD)(((nCount_yz + 1) * (nCorss + 1)) + nCount_x);
			pIdx[1] = (WORD)(((nCount_yz) * (nCorss + 1)) + nCount_x);

			pIdx += 2;			// �C���f�b�N�X�o�b�t�@��i�߂�

			if (nVertical > 1 && nCount_yz != nVertical - 1 && nCount_x == nCorss)
			{// ���[�ɓ��B������
			 // �C���f�b�N�X���̐ݒ�i�k�ރ|���S���j
				pIdx[0] = (WORD)(((nCount_yz) * (nCorss + 1)) + nCount_x);
				pIdx[1] = (WORD)(((nCount_yz + 2) * (nCorss + 1)));

				pIdx += 2;		// �C���f�b�N�X�o�b�t�@��i�߂�
			}
		}
	}
	//�C���f�b�N�X�̃o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}
//==================================================================================================//
//    * �@���̃Z�b�g���� *
//==================================================================================================//
void	CMesh::SetNor(void)
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
	D3DXVECTOR3 vec0, vec1;
	D3DXVECTOR3 nor[2];
	int		nCntHit = 0;
	int nCntVertical, nCntCorss;
	VERTEX_3D *pVtxLU, *pVtxLD, *pVtxRU, *pVtxRD;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	for (nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++)
	{//�c��
		for (nCntCorss = 0; nCntCorss < m_nCross + 1; nCntCorss++)
		{//����
			pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	for (int nCntVertical = 0; nCntVertical < m_nVertical; nCntVertical++)
	{//�c��
		for (int nCntCorss = 0; nCntCorss < m_nCross; nCntCorss++)
		{//����
			//���_�擾
			pVtxLU = &pVtx[(nCntVertical) * (m_nCross + 1) + nCntCorss];
			pVtxLD = &pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCorss];
			pVtxRU = &pVtx[(nCntVertical) * (m_nCross + 1) + nCntCorss + 1];
			pVtxRD = &pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCorss + 1];
			//�@�����Z
			PlusNor(pVtxLD, pVtxLU, pVtxRD);
			PlusNor(pVtxRD, pVtxRD, pVtxLU);
		}
	}

	for (nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++)
	{//�c��
		for (nCntCorss = 0; nCntCorss < m_nCross + 1; nCntCorss++)
		{//����
			if (nCntVertical == 0)
			{//��[
				if (nCntCorss == 0 || nCntCorss == m_nCross) { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 2.0f - (nCntCorss / m_nCross); }
				else { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 3.0f; }
			}
			else if (nCntVertical == m_nVertical)
			{//���[
				if (nCntCorss == 0 || nCntCorss == m_nCross) { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 1.0f + (nCntCorss / m_nCross); }
				else { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 3.0f; }
			}
			else
			{//����
				if (nCntCorss == 0 || nCntCorss == m_nCross) { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 3.0f; }
				else { pVtx[nCntVertical * (m_nCross + 1) + nCntCorss].nor /= 6.0f; }
			}
		}
	}
	m_pVtxBuff->Unlock();	//���_�o�b�t�@�̃A�����b�N����
}
//==================================================================================================//
//    * �@���̉��Z���� *
//==================================================================================================//
void CMesh::PlusNor(VERTEX_3D *pVtx, VERTEX_3D *pVtxL, VERTEX_3D *pVtxR)	//�@���̃Z�b�g����
{
	D3DXVECTOR3 vec0, vec1;
	D3DXVECTOR3 nor;

	//�@���v�Z
	vec0 = pVtxL->pos - pVtx->pos;
	vec1 = pVtxR->pos - pVtx->pos;
	D3DXVec3Cross(&nor, (m_bMesh ? &vec0 : &vec1), (m_bMesh ? &vec1 : &vec0));	//�O�όv�Z
	D3DXVec3Normalize(&nor, &nor);												//���K���ɂ���

	//���Z
	pVtx->nor += nor;
	pVtxL->nor += nor;
	pVtxR->nor += nor;
}
//==================================================================================================//
//    * ���_�̃Z�b�g�֐� *
//==================================================================================================//
void CMesh::SetWall(D3DXVECTOR3 *vtx)	//�Q�[�W�Z�b�g����
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
	float *fCurve;

	fCurve = new float[m_nCross];

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	for (int nCountX = 0; nCountX < m_nVertical + 1; nCountX++)
	{
		for (int nCountY = 0; nCountY < m_nCross + 1; nCountY++)
		{
			if (nCountX == 0)
			{
				if (nCountY == m_nCross)
				{//�n�߂̒��_�ɂȂ���
					pVtx[nCountX * (m_nCross + 1) + nCountY].pos = pVtx[nCountX * (m_nCross + 1)].pos;
				}
				else
				{//�����̒��_����
					fCurve[nCountY] = (rand() % 628) * 0.01f;
					pVtx[nCountX * (m_nCross + 1) + nCountY].pos
						= vtx[nCountY] + D3DXVECTOR3(sinf(fCurve[nCountY]) * WALL_CURVE, BULOCK_Y * nCountX, cosf(fCurve[nCountY]) * WALL_CURVE);
				}
			}
			else
			{
				if (nCountY == m_nCross)
				{//����̎n�߂̒��_���� + Y
					pVtx[nCountX * (m_nCross + 1) + nCountY].pos = pVtx[nCountX * (m_nCross + 1)].pos;
				}
				else
				{//����̒��_���� + Y
					fCurve[nCountY] += (rand() % 10) * 0.05f;
					pVtx[nCountX * (m_nCross + 1) + nCountY].pos
						= vtx[nCountY]
						+ D3DXVECTOR3(sinf(fCurve[nCountY]) * WALL_CURVE, BULOCK_Y * nCountX, cosf(fCurve[nCountY]) * WALL_CURVE);
				}
			}

			if(nCountX == 0)
			{
				//CScene3D *p3D;
				//if (SceneCreate(p3D, 0))
				//{
				//	p3D->Set(vtx[nCountY], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f),
				//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
				//}
			}
		}
	}

	delete[] fCurve;

	m_pVtxBuff->Unlock();	//���_�o�b�t�@�̃A�����b�N����
}
//==================================================================================================//
//���Z�b�g����
//==================================================================================================//
bool CMesh::SetField(int *nDig, int nMaxDig, float *fHeight, bool bRoom)
{
	int nPosX, nPosZ, nType;
	float fPHeight;
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾

	nType = 1;
	if (bRoom) { fPHeight = 500.0f; }
	else { fPHeight = 350.0f; }
	for (int nCount = 0; nCount < nMaxDig; nCount++)
	{//�@��������]
		nPosX = nDig[nCount] % MAP_SIZE;
		nPosZ = (nDig[nCount] / MAP_SIZE);
		if (nPosX == 0 || nPosX == MAP_SIZE - 1 || nPosZ == 0 || nPosZ == MAP_SIZE - 1) { return false; }
		nPosX = nPosX * FIELD_SPLIT;
		nPosX = m_nCross - nPosX + 2 - FIELD_SPLIT;
		nPosZ = nPosZ* FIELD_SPLIT;
		if (nPosZ > 1) { nPosZ--; }
		if (m_Type == TYPE_CEILING)
		{
			nPosZ = m_nVertical - nPosZ; 
			nType = -1;
		}
		nPosZ = (nPosZ) * (m_nCross + 1);
		for (int nCntZ = 0; nCntZ < FIELD_SPLIT + 1; nCntZ++)
		{//������X
			for (int nCntX = 0; nCntX < FIELD_SPLIT + 1; nCntX++)
			{//������Z �\���Ƀt�B�[���h�Z�b�g
				pVtx[nPosZ + nPosX + nCntZ * (m_nCross + 1) * nType + nCntX].pos.y = fHeight[nCount] + (m_bMesh ? rand() % 10 * -2.0f : fPHeight - rand() % 10 * 10.0f);
				pVtx[nPosZ + nPosX + nCntZ * (m_nCross + 1) * nType + nCntX + 1].pos.y = fHeight[nCount] + (m_bMesh ? rand() % 10 * -2.0f : fPHeight - rand() % 10 * 10.0f);
				pVtx[nPosZ + nPosX + nCntZ * (m_nCross + 1) * nType + nCntX - 1].pos.y = fHeight[nCount] + (m_bMesh ? rand() % 10 * -2.0f : fPHeight - rand() % 10 * 10.0f);
				pVtx[nPosZ + nPosX + (nCntZ + 1) * (m_nCross + 1) * nType + nCntX].pos.y = fHeight[nCount] + (m_bMesh ? rand() % 10 * -2.0f : fPHeight - rand() % 10 * 10.0f);
				pVtx[nPosZ + nPosX + (nCntZ - 1) * (m_nCross + 1) * nType + nCntX].pos.y = fHeight[nCount] + (m_bMesh ? rand() % 10 * -2.0f : fPHeight - rand() % 10 * 10.0f);
				//CScene3D *p3D;
				//if (SceneCreate(p3D, 4))
				//{
				//	p3D->Set(pVtx[nPosZ + nPosX + nCntZ * (m_nCross + 1) * nType + nCntX].pos + m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
				//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
				//}
			}//������Z
		}//������X
	}//�@��������]

	m_pVtxBuff->Unlock();	//���_�o�b�t�@�̃A�����b�N����

	return true;
}
//==================================================================================================//
//���v���X����
//==================================================================================================//
void CMesh::UpField(int *nMap, float fHeight)	//���v���X����
{
	bool bDown = false;
	int nWKZ, nWKX;
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
	for (int nCntDown = FIELD_STRDOWN; nCntDown < FIELD_NUMDOWN; nCntDown++)
	{
		for (int nCntZ = nCntDown; nCntZ < m_nVertical - nCntDown; nCntZ++)
		{//������X
			for (int nCntX = nCntDown; nCntX < m_nCross - nCntDown; nCntX++)
			{//������Z
				if (nMap[(nCntZ / FIELD_SPLIT) * MAP_SIZE + (nCntX / FIELD_SPLIT)] == 1)
				{//���Ȃ�
					bDown = true;
					for (int nCntZ2 = -nCntDown - 1; nCntZ2 < nCntDown; nCntZ2++)
					{//	Z�m�F����]
						for (int nCntX2 = -nCntDown + 1; nCntX2 < nCntDown - 1; nCntX2++)
						{//X�m�F����]
							if (nMap[((nCntZ + nCntZ2) / FIELD_SPLIT) * MAP_SIZE + ((nCntX + nCntX2) / FIELD_SPLIT)] == 0) 
							{ bDown = false; nCntZ2 = nCntDown; break; }
						}
					}
					if (bDown)
					{//��}�X���ƂɃ_�E��
						nWKZ = (m_bMesh ? nCntZ + (3 - FIELD_SPLIT) : m_nVertical - nCntZ - (3 - FIELD_SPLIT));
						nWKX = (m_nCross + 1) - nCntX;
						//if (nCntX == nCntDown && nCntZ == nCntDown) { pVtx[nWKZ * (m_nCross + 1) + nWKX].pos.y += fHeight; }
						//if (nCntZ == nCntDown) { pVtx[nWKZ * (m_nCross + 1) + nWKX + 1].pos.y += fHeight; }
						//if (nCntX == nCntDown) { pVtx[(nWKZ + (m_bMesh ? 1 : -1)) * (m_nCross + 1) + nWKX].pos.y += fHeight; }
						pVtx[(nWKZ) * (m_nCross + 1) + nWKX + 1].pos.y += fHeight / (((nCntDown - FIELD_STRDOWN) * 2 + 1));
						//CScene3D *p3D;
						//if (SceneCreate(p3D, 4))
						//{
						//	p3D->Set(pVtx[(nWKZ) * (m_nCross + 1) + nWKX + 1].pos + m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
						//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
						//}
					}
				}
			}//������Z
		}//������X
	}//�_�E����
	m_pVtxBuff->Unlock();	//���_�o�b�t�@�̃A�����b�N����
}
//=============================================================================
// ���b�V���̏���������
//=============================================================================
HRESULT  CMesh::Init(void)
{
	SetObjType(OBJTYPE_MESH);
	m_pTex = NULL;
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_bMesh = true;
	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_fUV_X = 0.0003f;
	m_fUV_Y = 0.0003f;
	return S_OK;
}
//=============================================================================
// ���b�V���̍X�V����
//=============================================================================
void	CMesh::Update(void)
{
	if (m_Type == TYPE_FIELD)
	{
		VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾
		for (int nCntVertical = 0; nCntVertical < m_nVertical + 1; nCntVertical++)
		{//�c��
			for (int nCntCorss = 0; nCntCorss < m_nCross + 1; nCntCorss++)
			{//����
				pVtx[0].tex.x += m_fUV_X;
				pVtx[0].tex.y += m_fUV_Y;
				pVtx++;
			}
		}
		m_pVtxBuff->Unlock();	//���_�o�b�t�@�̃A�����b�N����

	}
}

//=============================================================================
// ���b�V���̏I������
//=============================================================================
void  CMesh::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//�C���f�b�N�X�o�b�t�@�̉��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	CScene::Uninit();
}
//=============================================================================
// ���b�V���̕`�揈��
//=============================================================================
void  CMesh ::Draw (void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;				//�v�Z�p�}�g���b�N�X
	D3DXMATRIX			mtxWorld;		//���[���h�}�g���b�N�X

	if (CScene::DrawPrepare(m_DrawType, pDevice)) { return; }

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@�f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	if (m_pTex != NULL) { pDevice->SetTexture(0, m_pTex); }

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);

	pDevice->SetTexture(0, NULL);
}
//=============================================================================
//���b�V���S�����̂����蔻��
//=============================================================================
void CMesh::MeshCollisionCeiling(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &length)
{
	CScene *pScene;

	pScene = CScene::GetTop(MESH_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_MESH)
		{//���b�V������
			if (((CMesh*)pScene)->m_Type == TYPE_CEILING) { ((CMesh*)pScene)->MeshCeling(pos, posold, length.y); }
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//���b�V���S���̂����蔻��
//=============================================================================
bool CMesh::MeshCollisionField(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, bool &bJump)
{
	CScene *pScene;
	bool bLand = false;

	pScene = CScene::GetTop(MESH_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_MESH)
		{//���b�V������
			if (((CMesh*)pScene)->m_Type == TYPE_FIELD) { bLand = ((CMesh*)pScene)->MeshField(pos, posold, move, FNor, length.x, bJump); }
		}
		pScene = pScene->GetpNext();
	}

	return bLand;
}
//=============================================================================
//���b�V���S�ǂ̂����蔻��
//=============================================================================
void CMesh::MeshCollisionWall(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &length, D3DXVECTOR3 &FNor, int &nCntHit, bool &bJump, bool bReflection)
{
	CScene *pScene;

	pScene = CScene::GetTop(MESH_PRIORITY);
	while (pScene != NULL)
	{//�I���܂�
		if (pScene->GetObjType() == OBJTYPE_MESH)
		{//���b�V������
			if (((CMesh*)pScene)->m_Type == TYPE_WALL) { ((CMesh*)pScene)->MeshWall(pos, posold, move, length.x, nCntHit, bReflection); }
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//���b�V���V��̂����蔻��
//=============================================================================
void CMesh::MeshCeling(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, float& fLength)
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
	bool		bHit = true;
	D3DXVECTOR3 WKpos = pos - m_pos;
	D3DXVECTOR3 WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 Vec[8];

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾

	if (FieldCheck(pVtx[m_nCross].pos, pVtx[0].pos, pVtx[m_nVertical * (m_nCross + 1) + m_nCross].pos, pVtx[m_nVertical * (m_nCross + 1)].pos, WKpos))
	{//�l�p�͈͓��Ȃ�
		WKpos = pos - m_pos;
		int	nField = 0;
		//float	fRotCross;										//�ʂ̊p�xX
		//float	fRotVertical;									//�ʂ̊p�xZ
		int		nCntCross;
		int		nCntVertical;

		nCntCross = (int)((WKpos.x - pVtx[0].pos.x) / FIELD_SIZE);		//���̒��_�̗���Z�o
		nCntVertical = (int)((pVtx[0].pos.z - WKpos.z) / FIELD_SIZE);	//�c�̒��_�̗���Z�o
		if (nCntCross < 0) { nCntCross *= -1; }
		if (nCntVertical < 0) { nCntVertical *= -1; }
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�V�� %d�@%d\n", nCntCross, nCntVertical);
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, " ����@%d��%d", nCntVertical * (m_nCross + 1) + nCntCross, (nCntVertical + 1) * (m_nCross + 1) + nCntCross + 1);

		WKpos.y = FieldCollision(
			pVtx[nCntVertical * (m_nCross + 1) + nCntCross + 1].pos, pVtx[nCntVertical * (m_nCross + 1) + nCntCross].pos, 
			pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCross].pos, pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCross].pos,
			pos - m_pos, pos, WKnor);

		if (WKpos.y < pos.y + fLength)
		{//�ђʂ��Ă�����
			pos.y = WKpos.y - fLength;
		}
	}

	m_pVtxBuff->Unlock();	//���_�o�b�t�@�̃A�����b�N����
}
//=============================================================================
//���b�V�����̂����蔻��
//=============================================================================
bool CMesh::MeshField(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, D3DXVECTOR3 &FNor, float& fLength, bool &bJump)
{
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
	bool		bLand = false;
	D3DXVECTOR3 WKnor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 WKpos = pos - m_pos;
	D3DXVECTOR3 Vec[8];

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾

	if(FieldCheck(pVtx[0].pos, pVtx[m_nCross].pos, pVtx[m_nVertical * (m_nCross + 1)].pos, pVtx[m_nVertical * (m_nCross + 1) + m_nCross].pos, WKpos))
	{//�l�p�͈͓��Ȃ�
		WKpos = pos - m_pos;
		int		nCntCross;
		int		nCntVertical;

		nCntCross = (int)((WKpos.x - pVtx[0].pos.x) / FIELD_SIZE);		//���̒��_�̗���Z�o
		nCntVertical = (int)((pVtx[0].pos.z - WKpos.z) / FIELD_SIZE);	//�c�̒��_�̗���Z�o
		if (nCntCross < 0) { nCntCross *= -1; }
		if (nCntVertical < 0) { nCntVertical *= -1; }
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�t�B�[���h %d�@%d\n", nCntCross, nCntVertical);
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, " ����@%d��%d", nCntVertical * (m_nCross + 1) + nCntCross, (nCntVertical + 1) * (m_nCross + 1) + nCntCross + 1);
		
		WKpos.y = FieldCollision(
			pVtx[nCntVertical * (m_nCross + 1) + nCntCross].pos, pVtx[nCntVertical * (m_nCross + 1) + nCntCross + 1].pos,
			pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCross].pos, pVtx[(nCntVertical + 1) * (m_nCross + 1) + nCntCross + 1].pos,
			pos - m_pos, pos, WKnor) + m_pos.y;

		if (WKpos.y >= pos.y - (bJump ?  10.0f : 0.0f))
		{//�ђʂ��Ă�����
			pos.y = WKpos.y;
			move.y = 0.0f;
			FNor = WKnor;
			if (!bJump) { bLand = true; }//�OF���󒆂Ȃ�
			bJump = true;
		}
	}

	m_pVtxBuff->Unlock();	//���_�o�b�t�@�̃A�����b�N����
	return bLand;
}
//=============================================================================
//���b�V���ǂ̂����蔻��
//=============================================================================
void CMesh::MeshWall(D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float& fLength, int &nCntHit, bool &bReflection)
{
	//��̂݌���(2���_�̂���)
	int nVtxY = 0;	//��r���钸�_���擾

	bool		bEnd = true;	//�I������

	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);	//���_�o�b�t�@�����b�N�����_�f�[�^�ւ̃|�C���^���擾

	do
	{
		for (int nCount = 0; nCount < m_nCross; nCount++)
		{//���b�V��Wall��XZ�݂̂�����
			
			if (WallCollision(pVtx[nVtxY * (m_nCross + 1) + nCount].pos, pVtx[nVtxY * (m_nCross + 1) + nCount + 1].pos, pos, posold, move, fLength, nCntHit, bReflection) == 2)
			{bEnd = true; break; }
		}
	} while (!bEnd);
	m_pVtxBuff->Unlock();	//���_�o�b�t�@�̃A�����b�N����
}
//=============================================================================
// �O�ϕǂ̂����蔻����L�������傫������
//=============================================================================
void CMesh::WallPlus(D3DXVECTOR3& pos0, D3DXVECTOR3 &pos1, float& fLengthX, float& fLengthZ)
{
	if (pos0.x - pos1.x < 0)
	{//�L�������ǂ̉E��
		if (pos0.x - pos1.x < fLengthX) { pos0.x += pos0.x - pos1.x; }
		else { pos0.x += fLengthX; }
	}
	else
	{//�L�������ǂ̍���
		if (pos0.x - pos1.x < -fLengthX) { pos0.x -= pos0.x - pos1.x; }
		else { pos0.x -= fLengthX; }
	}

	if (pos0.z - pos1.z < 0)
	{//�L�������ǂ̉E��
		if (pos0.z - pos1.z < fLengthZ) { pos0.z += pos0.z - pos1.z; }
		else { pos0.z += fLengthZ; }
	}
	else
	{//�L�������ǂ̍���
		if (pos0.z - pos1.z < -fLengthZ) { pos0.z -= pos0.z - pos1.z; }
		else { pos0.z -= fLengthZ; }
	}
}
//=============================================================================
//�p�x�Ɗp�x�̃`�F�b�N����
//=============================================================================
int CMesh::AngleCheck(float fAngle0, float fAngle1)
{
	float fWKRot = fAngle0;
	fAngle0 = 0.0f;
	fAngle1 -= fWKRot;

	if (fAngle1 > D3DX_PI) { fAngle1 -= D3DX_PI * 2.0f; }
	if (fAngle1 < -D3DX_PI) { fAngle1 += D3DX_PI * 2.0f; }

	if (fAngle0 > fAngle1) { return 1; }
	else if (fAngle0 < fAngle1) { return -1; }
	return 0;
}
//=============================================================================
//�����O���̃`�F�b�N����
//=============================================================================
bool CMesh::FieldCheck(D3DXVECTOR3 &FposUL, D3DXVECTOR3 &FposUR, D3DXVECTOR3 &FposDL, D3DXVECTOR3 &FposDR, D3DXVECTOR3& pos)
{
	D3DXVECTOR3 Vec[8];

	Vec[0] = FposUL - FposUR;
	Vec[1] = pos - FposUR;
	Vec[2] = FposUR - FposDR;
	Vec[3] = pos - FposDR;
	Vec[4] = FposDR - FposDL;
	Vec[5] = pos - FposDL;
	Vec[6] = FposDL - FposUL;
	Vec[7] = pos - FposUL;

	if ((Vec[0].z * Vec[1].x) - (Vec[0].x * Vec[1].z) <= 0 &&
		(Vec[2].z * Vec[3].x) - (Vec[2].x * Vec[3].z) <= 0 &&
		(Vec[4].z * Vec[5].x) - (Vec[4].x * Vec[5].z) <= 0 &&
		(Vec[6].z * Vec[7].x) - (Vec[6].x * Vec[7].z) <= 0
		)
	{//�l�p�͈͓��Ȃ�
		return true;
	}
	return false;
}
//=============================================================================
//�N������
//=============================================================================
float CMesh::FieldCollision(D3DXVECTOR3 &FposUL, D3DXVECTOR3 &FposUR, D3DXVECTOR3 &FposDL, D3DXVECTOR3 &FposDR, D3DXVECTOR3 WKpos, D3DXVECTOR3& pos, D3DXVECTOR3 &FNor)
{
	bool bLand = false;
	D3DXVECTOR3 Vtx[4];
	D3DXVECTOR3 vec0, vec1;
	float		fData;
	D3DXVECTOR3 nor;
	vec0 = FposDR - FposUL;
	vec1 = WKpos - FposUL;

	if ((vec0.z * vec1.x) - (vec0.x * vec1.z) <= 0)
	{//�O�p�`�敪�ŉE�㑤
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�E��\n");
		Vtx[0] = FposUR;
		Vtx[1] = FposUL;
		Vtx[2] = FposDR;
	}
	else
	{//�O�p�`�敪�ō�����
		//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "����\n");
		Vtx[0] = FposDL;
		Vtx[1] = FposDR;
		Vtx[2] = FposUL;
	}
	fData = Vtx[0].y; Vtx[0].y -= fData; Vtx[1].y -= fData; Vtx[2].y -= fData;

	vec0 = Vtx[2] - Vtx[0];
	vec1 = Vtx[1] - Vtx[0];
	D3DXVec3Cross(&nor, &vec0, &vec1);	//�O�όv�Z
	D3DXVec3Normalize(&nor, &nor);		//���K���ɂ���
	D3DXVECTOR3 vec;
	vec = WKpos - Vtx[0];

	if (nor.y != 0)
	{
		//WKpos.y = ((nor.x * vec.x) + (nor.z * vec.z)) / -nor.y;
		WKpos.y = ((nor.x * vec.x) + (nor.z * vec.z)) / -nor.y;
	}
	else
	{
		//WKpos.y = 0.0f;
		WKpos.y = 0.0f;
	}
	FNor = nor;
	WKpos.y += fData;

	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "���_0�@%.1f�@%.1f�@%.1f\n", Vtx[0].x, Vtx[0].y, Vtx[0].z);
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "���_1�@%.1f�@%.1f�@%.1f\n", Vtx[1].x, Vtx[1].y, Vtx[1].z);
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "���_2�@%.1f�@%.1f�@%.1f\n", Vtx[2].x, Vtx[2].y, Vtx[2].z);
	//CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�␳�l�@%.1f\n", fData);
	//if (SceneCreate(p3D, 5))
	//{
	//	p3D->Set(Vtx[0], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),
	//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
	//	p3D->GetState() = CScene3D::STATE_FADEOUT;
	//	p3D->GetfCntState() = 0.3f;
	//}
	//if (SceneCreate(p3D, 5))
	//{
	//	p3D->Set(Vtx[1], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f),
	//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
	//	p3D->GetState() = CScene3D::STATE_FADEOUT;
	//	p3D->GetfCntState() = 0.3f;
	//}
	//if (SceneCreate(p3D, 5))
	//{
	//	p3D->Set(Vtx[2], D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f),
	//		D3DXVECTOR3(10.0f, 10.0f, 0.0f), CScene::TEX_MAX, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
	//	p3D->GetState() = CScene3D::STATE_FADEOUT;
	//	p3D->GetfCntState() = 0.3f;
	//}
	return WKpos.y;
}
//=============================================================================
//���Ɛ��̂����蔻��(��)����
//=============================================================================
int CMesh::WallCollision(D3DXVECTOR3 Wpos0, D3DXVECTOR3 Wpos1, D3DXVECTOR3& pos, D3DXVECTOR3 &posold, D3DXVECTOR3 &move, float& fLength, int &nCntHit, bool &bReflection)
{
	D3DXVECTOR3 Wpos2;			//�����k�߂�p
	D3DXVECTOR3 Wpos3;			//�����k�߂�p
	float		fDistance;		//�߂荞�񂾋���
	float		fCntZ;
	float		fWKrot = 0.0f;
	float		fAngle[5];
	D3DXVECTOR3 Vec;
	int		nEnd = 0;	//�I������

	//�p�x�v�Z
	fAngle[0] = atan2f(Wpos1.x - Wpos0.x, Wpos1.z - Wpos0.z);
	Wpos2 = pos;
	Wpos0 += D3DXVECTOR3(sinf(fAngle[0] - D3DX_PI * 0.75f), 0.0f, cosf(fAngle[0] - D3DX_PI * 0.75f)) * fLength;
	Wpos1 += D3DXVECTOR3(sinf(fAngle[0] - D3DX_PI * 0.25f), 0.0f, cosf(fAngle[0] - D3DX_PI * 0.25f)) * fLength;
	fAngle[1] = atan2f(Wpos2.x - Wpos0.x, Wpos2.z - Wpos0.z);
	fAngle[2] = atan2f(Wpos0.x - posold.x, Wpos0.z - posold.z);
	fAngle[3] = atan2f(Wpos2.x - posold.x, Wpos2.z - posold.z);
	fAngle[4] = atan2f(Wpos1.x - posold.x, Wpos1.z - posold.z);

	if (AngleCheck(fAngle[0], fAngle[1]) <= 0 &&	//���݂̈ʒu���ǂ̌�������
		AngleCheck(fAngle[0], fAngle[2]) <= 0 &&	//�O�̈ʒu���ǂ̎�O��
		AngleCheck(fAngle[3], fAngle[2]) <= 0 &&	//�ړ��������ǎ��v����O���_�̓���
		AngleCheck(fAngle[3], fAngle[4]) >= 0		//�ړ��������ǎ��v���u�����_�̓���
		)
	{//�����`�F�b�N
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�q�b�g�I\n");
		//nCntHit++;
		if (nCntHit < 3)
		{//2��ȏ�q�b�g
		 //��_�����߂�
			fDistance = sqrtf(powf((Wpos2.x - Wpos0.x), 2) + powf((Wpos2.z - Wpos0.z), 2));
			nEnd = 1;

			if (fLength > 5.0f)
			{
				//���ˌv�Z
				fWKrot = fAngle[0] - fAngle[3]; //�Ǌp�x����v���C���[�̈ړ������������Ĕ��]
				if (fWKrot > D3DX_PI) { fWKrot -= D3DX_PI * 2.0f; }
				if (fWKrot < -D3DX_PI) { fWKrot += D3DX_PI * 2.0f; }
				fAngle[3] += fWKrot * 2.0f;	//�s�������p�x
				if (fAngle[3] > D3DX_PI) { fAngle[3] -= D3DX_PI * 2.0f; }
				if (fAngle[3] < -D3DX_PI) { fAngle[3] += D3DX_PI * 2.0f; }
			}
			else
			{
				nEnd = 2;
				//��_�����炳�Ȃ�
				fAngle[3] = atan2f(posold.x - Wpos2.x, posold.z - Wpos2.z);

				fAngle[1] = atan2f(pos.x - Wpos0.x, pos.z - Wpos0.z);	//posold�ƕǌ��_�̊p�x�����
				fWKrot = D3DX_PI * -0.5f - fAngle[1];					//�����-1.57�̍��������߂�
				if (fWKrot > D3DX_PI) { fWKrot -= D3DX_PI * 2.0f; }
				if (fWKrot < -D3DX_PI) { fWKrot += D3DX_PI * 2.0f; }
				//���p�x�v�Z�͍s�������p�x�ƕǊp�x
				//������������p�x�ŐL�΂�1.0�x�����擾
				Wpos1 = D3DXVECTOR3(sinf(fWKrot + fAngle[0]), 0.0f, cosf(fWKrot + fAngle[0])) * 1.0f;
				Wpos2 = D3DXVECTOR3(sinf(fWKrot + fAngle[3]), 0.0f, cosf(fWKrot + fAngle[3])) * 1.0f;
				Wpos1.x = Wpos1.x / Wpos1.z;
				Wpos2.x = Wpos2.x / Wpos2.z;
				fCntZ = fDistance / (-Wpos1.x + Wpos2.x);
				//(���� / �w�̘a) = �� = ���߂�������
				Wpos3 = D3DXVECTOR3(fCntZ * Wpos1.x, 0.0f, fCntZ);
				fDistance = sqrtf(powf((Wpos3.x), 2) + powf((Wpos3.z), 2));
			}
			//�l���
			Wpos0 = D3DXVECTOR3(Wpos0.x, pos.y, Wpos0.z) + D3DXVECTOR3(sinf(fAngle[0]), 0.0f, cosf(fAngle[0])) * fDistance;
			if (bReflection) { pos = Wpos0 + D3DXVECTOR3(sinf(fAngle[3]), 0.0f, cosf(fAngle[3])) * (WALL_PLUS); }
			else { pos = Wpos0 + D3DXVECTOR3(sinf(fAngle[0] - D3DX_PI * 0.5f), 0.0f, cosf(fAngle[0] - D3DX_PI * 0.5f)) * (0.1f); }

			CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "�ǂ̊p�x : %f\n", fAngle[0]);

		}
		else
		{
			nEnd = 2;
			//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "�߂����I\n");
			pos = posold;
		}


	}

	return nEnd;
}
