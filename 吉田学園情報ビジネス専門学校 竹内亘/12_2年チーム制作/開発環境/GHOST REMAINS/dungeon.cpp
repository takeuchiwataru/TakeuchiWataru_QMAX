//==================================================================================================//
//
//    * [dungeon.cpp] *
//    * Author Ryo Sugimoto *
//
//==================================================================================================//
#include <stdlib.h>				//�����h�p
#include <time.h>				//�����������h�p

#include "dungeon.h"
#include "camera.h"
#include "scene.h"

#include "player.h"
#include "enemy.h"
#include "mesh.h"
#include "SceneModel.h"
//==================================================================================================//
//    * �}�N����` *
//==================================================================================================//
#define MAX_ROAD		(4)
#define MAX_ROOM		(MAX_ROAD * 5)
#define MAX_ROAD_INFO	(3)
#define MAX_ROOM_INFO	(4)

//==================================================================================================//
//    * �ÓI�����o�ϐ��錾 *
//==================================================================================================//
bool CDungeon::m_bEnd = false;	//�����_������������I���������ǂ���
//==================================================================================================//
//    * �����֐� *
//==================================================================================================//
HRESULT CDungeon::Init(void)
{
	LPDIRECT3DDEVICE9		pD3DDevice = CManager::GetRenderer()->GetDevice();

	//�ݒ�
	CScene::SetObjType(OBJTYPE_DUNGEON);

	m_BGM = CSound::LABEL_MAX;

	m_nQuake = 0;

	return S_OK;
}
//==================================================================================================//
//    * �����֐� *
//==================================================================================================//
void CDungeon::Uninit(void)
{
	//CManager::GetDungeon() = NULL;
	Release();
}
//==================================================================================================//
//    * �X�V�֐� *
//==================================================================================================//
void CDungeon::Update(void)
{

}
//==================================================================================================//
//    * �`��֐� *
//==================================================================================================//
void CDungeon::Draw(void)
{

}
//==================================================================================================//
//    * �����_���_���W�����̏����� *
//==================================================================================================//
void CDungeon::InitDungeon(void)
{
	m_bEnd = true;
	CScene::BreakObject(CScene::OBJTYPE_MESH);
	CScene::BreakObject(CScene::OBJTYPE_OBJ);
	CScene::BreakObject(CScene::OBJTYPE_ENEMY);
}
//==================================================================================================//
//    * �����_���_���W�����쐬 *
//==================================================================================================//
void CDungeon::SetDungeon_Rand(int nStatge)
{
	CMesh	*pField;
	CMesh	*pCeiling;
	//CMesh *pMesh;
	D3DXVECTOR3 vtx[4];

	if (SceneCreate(pField, MESH_PRIORITY)) { pField->Set(CMesh::TYPE_FIELD, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, 0.0f, -CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, true); }
	if (SceneCreate(pCeiling, MESH_PRIORITY)) { pCeiling->Set(CMesh::TYPE_CEILING, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, 0.0f, -MAP_SIZE * CHIP_SIZE - CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, false); }
	//if (SceneCreate(pMesh, MESH_PRIORITY))
	//{
	//	pMesh->Set(CMesh::TYPE_WALL, D3DXVECTOR3(0.0f, -1000.0f, 0.0f), 10, 4, true);
	//	pMesh->SetWall(&vtx[0]);
	//	pMesh->BindTexture(Load(TEX_Wall));
	//	pMesh->SetNor();
	//}
}
//==================================================================================================//
//    * �}�X���@�� *
//==================================================================================================//
void CDungeon::SetDig(int *nMap, int nPos, int &nRot, int nPlusX, int nPlusZ, int nLengthX, int nLengthZ, float fHeight, float fPHeight, int nChip, CMesh *pField, CMesh *pCeiling)
{//�ϐ� * �ϐ��Ō@��
	int nZPos;
	int nXPos;
	int nDig[100];
	float fSHeight[100];
	int nMaxDig = 0;

	SpinDig(nRot, nPlusX, nPlusZ);
	nPos += nPlusZ + nPlusX;
	for (int nCountZ = 0; nCountZ < nLengthX; nCountZ++)
	{
		for (int nCountX = 0; nCountX < nLengthZ; nCountX++)
		{
			nZPos = nCountZ; nXPos = nCountX;
			SpinDig(nRot, nZPos, nXPos);
			if(nPos + nXPos + nZPos < MAP_SIZE * MAP_SIZE && nPos + nXPos + nZPos >= 0)
			{ 
				nMap[nPos + nXPos + nZPos] = nChip;
				nDig[nMaxDig] = nPos + nXPos + nZPos;	//�ʒu�ۑ�
				fSHeight[nMaxDig] = fHeight + nCountX * fPHeight;
				nMaxDig++;								//�ʕۑ�
			}
		}
	}
	//�N���V���艻
	if (!pField->SetField(&nDig[0], nMaxDig, &fSHeight[0], (fPHeight == 0))) { m_bEnd = false; }
	if (!pCeiling->SetField(&nDig[0], nMaxDig, &fSHeight[0], (fPHeight == 0))) { m_bEnd = false; }
}
//==================================================================================================//
//    * �}�X�����b�V���㉺ *
//==================================================================================================//
void CDungeon::SetMesh(int *nMap, int nPos, int &nRot, int nPlusX, int nPlusZ, int nLength, float fHeight, CMesh *pField, CMesh *pCeiling)
{//�ϐ� * �ϐ��Ō@��
	int nZPos;
	int nXPos;

	SpinDig(nRot, nPlusZ, nPlusX);
	nPos += nPlusZ + nPlusX;
	for (int nCountZ = 0; nCountZ < nLength; nCountZ++)
	{
		for (int nCountX = 0; nCountX < nLength; nCountX++)
		{
			nZPos = nCountZ; nXPos = nCountX;
			SpinDig(nRot, nZPos, nXPos);
			if (nPos + nXPos + nZPos < MAP_SIZE * MAP_SIZE && nPos + nXPos + nZPos >= 0) { nMap[nPos + nXPos + nZPos] = 1; }
		}
	}
}

//==================================================================================================//
//    * �}�X����] *
//==================================================================================================//
void CDungeon::SpinDig(int &nRot, int &nLengthZ, int &nLengthX)
{
	switch (nRot)
	{
	case 0:	//�O
		nLengthZ = nLengthZ * MAP_SIZE;
		nLengthX = nLengthX;
		break;
	case 1:	//�E
		nLengthZ = nLengthZ;
		nLengthX = nLengthX * -MAP_SIZE;
		break;
	case 2:	//���
		nLengthZ = nLengthZ * -MAP_SIZE;
		nLengthX = -nLengthX;
		break;
	case 3:	//��
		nLengthZ = -nLengthZ;
		nLengthX = nLengthX * MAP_SIZE;
		break;
	}
}
//==================================================================================================//
//    * ���[���̍쐬 *
//==================================================================================================//
void CDungeon::SetRoom(int *nMap, float *fRoomC, float *fRoadC, int *nCntRoom, int *nCntRoad, CMesh *pField, CMesh *pCeiling)
{
	int nPlus = nCntRoom[0] * MAX_ROOM_INFO;
	int nPlusX = 0, nPlusZ = 0;
	int nPos = (int)fRoomC[nPlus];
	int nWKPos = nPos;
	int nRot = (int)fRoomC[nPlus + 1];
	int nRoom = rand() % 4 + 1;
	int nWKData;

	//�����m�F
	if(nCntRoom[0] == 0) { nRoom = 0; }
	else if (fRoomC[nPlus + 3] != 0.0f)
	{ nRoom = rand() % 3 + 1; }	//�����[���݂̂ɕϊ�
	switch (nRoom)
	{
	case 0:
		SetDig(nMap, nWKPos, nRot, -1, -1, 1, 3, fRoomC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 0, -3, 1, 6, fRoomC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 1, -2, 1, 2, fRoomC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		//�v���C���[�Z�b�g
		SetPpos(D3DXVECTOR3((nPos % MAP_SIZE) * -CHIP_SIZE, -10000.0f, (nPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		//��������
		nPlusX = 0; nPlusZ = -4; SpinDig(nRot, nPlusX, nPlusZ);
		SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 2) % 4), fRoomC[nPlus + 2], 1.0f);
		break;
	case 1:
		//�@��
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 2, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 2, 5, 7, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -3, 3, 7, 5, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);

		//�I�u�W�F�N�g�ݒu
		nPlusX = 0; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoom(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));

		
		if (fRoomC[nPlus + 3] >= 0.0f)
		{//�ʘH����
			nWKData = rand() % 3 * 10 + rand() % 2;
			if (nWKData % 10 == 0 || (nWKData % 10 + nWKData / 10) % 3 == 0)
			{
				nPlusX = 0; nPlusZ = 9; SpinDig(nRot, nPlusX, nPlusZ);
				SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot) % 4), fRoomC[nPlus + 2]);
			}
			if (nWKData % 10 == 1 || (nWKData % 10 + nWKData / 10) % 3 == 1)
			{
				nPlusX = 4; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
				SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 3) % 4), fRoomC[nPlus + 2]);
			}
			if (nWKData % 10 == 2 || (nWKData % 10 + nWKData / 10) % 3 == 2)
			{
				nPlusX = -4; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
				SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 1) % 4), fRoomC[nPlus + 2]);
			}
		}
		break;
	case 2:
		SetDig(nMap, nWKPos, nRot, -1, 0, 2, 6, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 2, 6, 2, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -1, 3, 5, 4, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		//�I�u�W�F�N�g�ݒu
		nPlusX = 1; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoom(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		if (fRoomC[nPlus + 3] >= 0.0f)
		{//�ʘH����
			nPlusX = 3; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 3) % 4), fRoomC[nPlus + 2]);
			nPlusX = -3; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 1) % 4), fRoomC[nPlus + 2]);
		}
		break;
	case 3:
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 4, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 1, 3, 4, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		//�I�u�W�F�N�g�ݒu
		nPlusX = -1; nPlusZ = 2; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoom(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		if (fRoomC[nPlus + 3] >= 0.0f)
		{//�ʘH����
			nPlusX = 0; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot) % 4), fRoomC[nPlus + 2]);
		}
		break;
	case 4:
		//�@��
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 2, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 2, 9, 11, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -3, 3, 8, 5, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 1, 12, 3, 1, fRoomC[nPlus + 2], 0.0f, 1, pField, pCeiling);

		//�I�u�W�F�N�g�ݒu
		nPlusX = 3; nPlusZ = 7; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoom2(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE), ChangeRot(nRot));

		if (fRoomC[nPlus + 3] >= 0.0f)
		{//�ʘH����
			nPlusX = -4; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 1) % 4), fRoomC[nPlus + 2]);
			nPlusX = 1; nPlusZ = 13; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoad(&fRoadC[0], &nCntRoad[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot) % 4), fRoomC[nPlus + 2]);
			//�B������
			nPlusX = 7; nPlusZ = 6; SpinDig(nRot, nPlusX, nPlusZ);
			SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 3) % 4), fRoomC[nPlus + 2], -1.0f);
		}
		break;
	}
}
//==================================================================================================//
//    * ���[���̍쐬 *
//==================================================================================================//
void CDungeon::SetRoad(int *nMap, float *fRoomC, float *fRoadC, int *nCntRoom, int *nCntRoad, CMesh *pField, CMesh *pCeiling)
{
	int nPlus = nCntRoad[0] * MAX_ROAD_INFO;
	int nPlusX = 0, nPlusZ = 0;
	int nPos = (int)fRoadC[nPlus];
	int nWKPos = nPos;
	int nRot = (int)fRoadC[nPlus + 1];
	int nRoom = rand() % 3;
	float fWKHeight = rand() % 2 * 70.0f - 35.0f;

	if (nCntRoad[0] == MAX_ROAD - 1) { nRoom = 5; }
	switch (nRoom)
	{
	case 0:
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 5, fRoadC[nPlus + 2], fWKHeight, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -1, 3, 1, 3, fRoadC[nPlus + 2] + fWKHeight * 3, fWKHeight, 1, pField, pCeiling);
		//�I�u�W�F
		nPlusX = 0; nPlusZ = 4; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoad(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		nPlusX = -1; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoad(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		//���[��
		nPlusX = -1; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
		SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot) % 4), fRoadC[nPlus + 2] + fWKHeight * 5, 0.0f);
		break;
	case 1:
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 4, fRoadC[nPlus + 2], fWKHeight, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -1, 3, 1, 2, fRoadC[nPlus + 2] + fWKHeight * 3, fWKHeight, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -2, 4, 2, 1, fRoadC[nPlus + 2] + fWKHeight * 4, fWKHeight, 1, pField, pCeiling);
		//�I�u�W�F
		nPlusX = -1; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoad(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		//���[��
		nPlusX = -3; nPlusZ = 4; SpinDig(nRot, nPlusX, nPlusZ);
		SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 1) % 4), fRoadC[nPlus + 2] + fWKHeight * 5, 0.0f);
		break;
	case 2:
		fWKHeight = rand() % 2 * 30.0f - 15.0f;
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 2, fRoadC[nPlus + 2], fWKHeight, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 1, 1, 1, 2, fRoadC[nPlus + 2] + fWKHeight * 1, fWKHeight, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 2, 1, 1, 3, fRoadC[nPlus + 2] + fWKHeight * 1, fWKHeight, 1, pField, pCeiling);
		//�I�u�W�F
		nPlusX = 2; nPlusZ = 1; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		SetObjRoad(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		//���[��
		nPlusX = 2; nPlusZ = 4; SpinDig(nRot, nPlusX, nPlusZ);
		SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot) % 4), fRoadC[nPlus + 2] + fWKHeight * 4, 0.0f);
		break;
	case 3:
		//fWKHeight = rand() % 2 * 100.0f - 50.0f;
		//SetDig(nMap, nWKPos, nRot, 0, 0, 1, 3, fRoadC[nPlus + 2], fWKHeight, 1, pField, pCeiling);
		//SetDig(nMap, nWKPos, nRot, 0, 5, 3, 1, fRoadC[nPlus + 2] + fWKHeight * 3, fWKHeight, 1, pField, pCeiling);
		//SetDig(nMap, nWKPos, nRot, -1, 4, 2, 1, fRoadC[nPlus + 2] + fWKHeight * 3, fWKHeight, 1, pField, pCeiling);
		//SetDig(nMap, nWKPos, nRot, -3, 3, 4, 1, fRoadC[nPlus + 2] + fWKHeight * 3, fWKHeight, 1, pField, pCeiling);
		////�I�u�W�F
		//nPlusX = 2; nPlusZ = 1; SpinDig(nRot, nPlusX, nPlusZ); nWKPos = nPos + nPlusZ + nPlusX;
		//SetObjRoad(D3DXVECTOR3((nWKPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nWKPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE));
		////���[��
		//nPlusX = 3; nPlusZ = 5; SpinDig(nRot, nPlusX, nPlusZ);
		//SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 3) % 4), fRoadC[nPlus + 2] + fWKHeight * 3);
		//nPlusX = -4; nPlusZ = 3; SpinDig(nRot, nPlusX, nPlusZ);
		//SettingRoom(&fRoomC[0], &nCntRoom[0], (float)(nPos + nPlusX + nPlusZ), (float)((nRot + 1) % 4), fRoadC[nPlus + 2] + fWKHeight * 3);
		//break;
	case 5:
		SetDig(nMap, nWKPos, nRot, 0, 0, 1, 5, fRoadC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, 1, 2, 1, 2, fRoadC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		SetDig(nMap, nWKPos, nRot, -1, 2, 1, 2, fRoadC[nPlus + 2], 0.1f, 1, pField, pCeiling);
		break;
	}
}
//==================================================================================================//
//    * �����Z�b�g�������� *
//==================================================================================================//
void CDungeon::SettingRoom(float *fRoomC, int *nCntRoom, float fPos, float fRot, float fHeight, float fState)
{
	if (nCntRoom[1] < MAX_ROOM)
	{
		fRoomC[nCntRoom[1] * MAX_ROOM_INFO + 0] = fPos;
		fRoomC[nCntRoom[1] * MAX_ROOM_INFO + 1] = fRot;
		fRoomC[nCntRoom[1] * MAX_ROOM_INFO + 2] = fHeight;
		//if (fState >= 0.0f) { fRoomC[nCntRoom[1] * MAX_ROOM_INFO + 2] += (rand() % 2 * 100.0f) - 50.0f; }
		fRoomC[nCntRoom[1] * MAX_ROOM_INFO + 3] = fState;
		nCntRoom[1]++;
	}
}
//==================================================================================================//
//    * ���Z�b�g�������� *
//==================================================================================================//
void CDungeon::SettingRoad(float *fRoadC, int *nCntRoad, float fPos, float fRot, float fHeight)
{
	if (nCntRoad[1] < MAX_ROAD)
	{
		fRoadC[nCntRoad[1] * MAX_ROAD_INFO + 0] = fPos;
		fRoadC[nCntRoad[1] * MAX_ROAD_INFO + 1] = fRot;
		fRoadC[nCntRoad[1] * MAX_ROAD_INFO + 2] = fHeight + (rand() % 2 * 100.0f) - 50.0f;
		nCntRoad[1]++;
	}
}
//==================================================================================================//
//    * �Ǎ쐬���̊p�xfloat�� *
//==================================================================================================//
float CDungeon::ChangeRot(int &nRot)
{
	switch (nRot)
	{
	case 2: return 0.0f;
	case 3: return D3DX_PI * 0.5f;
	case 0: return D3DX_PI;
	case 1: return D3DX_PI * -0.5f;
	}
	return 0.0f;
}
//==================================================================================================//
//    * �S�ǂ̍쐬 *
//==================================================================================================//
int CDungeon::SetWall(int *nMap)
{
	int nCntWall = 0;		//���ݒn
	int nPos = -1;		//���ݒn
	int nRot = -1;		//�i�s����
	int nFRot = -1;		//������

	int nBranch = -1;	//���L�@
	int nPosold = -1;	//�O�̌��ݒn
	int nRotold = -1;	//�O�̐i�s����
	int nFRotold = -1;	//�O�̐i�s����

	int nMoveR, nMoveF;	//�i�s�����Ə������ɂ��ړ���
	bool bTop = true;	//�I������p

	int nNumVrx = 0;	//����g�p���_
	float fWKRot = 0.0f;//���_������̊p�x�ϊ��p
	float fWKFRot = 0.0f;//���_������̊p�x�ϊ��p
	D3DXVECTOR3 vtx[MAP_SIZE * MAP_SIZE / 2];

	float fDistance;
	while (1)
	{//�������I���܂Ń��[�v
		int nPos = -1;	//���ݒn�����Z�b�g
		nNumVrx = 0;
		//�������Ă��Ȃ��ǂ�T��
		for (int nCount = 0; nCount < MAP_SIZE * MAP_SIZE; nCount++)
		{//�������Ȃ̂�T�� == 1
			if (nMap[nCount] == 1)
			{//���݂���
				if (nMap[nCount - MAP_SIZE] == 0)
				{//���̏オ�ǂȂ�
					nPos = nCount - MAP_SIZE;	//���ݒn���
					nRot = (bTop ? 1 : 3);
					nFRot = 0;					//�������͏�
					break;
				}
			}
		}

		if (nPos == -1) { break; }	//�����Ȃ���ΏI��
		int nNumVrx = 0;
		nBranch = -1;
		fDistance = (bTop ? (CHIP_SIZE / 2) : (CHIP_SIZE / 6));

		do
		{//�����ꏊ�ɒ����܂Ń��[�v
			//�_��ł�
			fWKFRot = ChangeRot(nFRot);
			vtx[nNumVrx] = D3DXVECTOR3((nPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE)
				+ D3DXVECTOR3(sinf(fWKFRot), 0.0f, cosf(fWKFRot)) * fDistance;

			nNumVrx++;	//���_���̑���

			//�T���菇�Ɠ�����ԂȂ�Ǎ폜
			if ((bTop ? nRot == 1 : nRot == 3) && nFRot == 0) { nMap[nPos] = -1; }

			nPosold = nPos;		//�O�̈ʒu�ɑ��
			nRotold = nRot;		//�O�̐i�s�����ɑ��
			nFRotold = nFRot;	//�O�̏���������

			//�i�s
			nMoveR = 1; nMoveF = 1;
			SpinDig(nRot, nMoveR, nBranch);	//�i�s�����ɂ��ړ��l�v�Z
			SpinDig(nFRot, nMoveF, nBranch);//�������ɂ��ړ��l�v�Z

			if (nMap[nPos + nMoveR + nMoveF] != 1)
			{//�i�s���ɕǂɂԂ������I
				nBranch = 0;				//�Փ˕���̕ۑ�
				nPos = nPos + nMoveR + nMoveF;	//�ʒu�̍X�V
				nRot = (bTop ? nFRot : nFRot);
				nFRot = (bTop ? (nRotold + 2) % 4 : (nRotold + 2) % 4);
			}
			else if (nMap[nPos + nMoveR] == 1)
			{//�i�s���������I
				nBranch = 1;				//�Ȃ���`�񕪊�̕ۑ�
				nRot = (bTop ? (nFRot + 2) % 4 : nFRot);
				nFRot = (bTop ? nRotold : (nRotold + 2) % 4);
			}
			else
			{//�Ȃ���Ȃ�
				nBranch = 2;				//�X�g���[�g����̕ۑ�
				nPos = nPos + nMoveR;			//�ʒu�̍X�V
			}


			if (nBranch == 1)
			{//�Ȃ���`�񕪊�Ȃ�
				fWKRot = ChangeRot(nRotold);	//�O�̓_����O�̐i�s������
				vtx[nNumVrx] = vtx[nNumVrx - 1] + D3DXVECTOR3(sinf(fWKRot), 0.0f, cosf(fWKRot)) * (CHIP_SIZE / 8) * (bTop ? 1.0f : -1.0f);

				fWKFRot = ChangeRot(nFRot);//���̓_����O�̏�������
				fWKRot = ChangeRot(nFRotold);	//�O�̓_����O�̐i�s������
				vtx[nNumVrx + 1] = D3DXVECTOR3((nPos % MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2), 0.0f, (nPos / MAP_SIZE) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE)
					+ D3DXVECTOR3(sinf(fWKFRot), 0.0f, cosf(fWKFRot)) * fDistance
					+ D3DXVECTOR3(sinf(fWKRot), 0.0f, cosf(fWKRot)) * (fDistance / 4);
				nNumVrx += 2;	//���_���̑���
			}
		} while (nMap[nPos] != -1 || nFRot != 0 || nRot != (bTop ? 1 : 3));	//���ɒʂ������Ȃ�

		//���b�V���𐶐������_����
		CMesh *pMesh;
		if (SceneCreate(pMesh, MESH_PRIORITY))
		{
			nCntWall++;
			pMesh->Set(CMesh::TYPE_WALL, D3DXVECTOR3(0.0f, -1000.0f, 0.0f), 10, nNumVrx, (bTop ? true : false));
			pMesh->SetWall(&vtx[0]);
			pMesh->BindTexture(Load(TEX_Wall));
			pMesh->SetNor();
			//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "���b�V���쐬 XZ%d, Y %d %s\n", 20, nNumVrx, (bTop ? "�g�b�v": "NO"));
			bTop = false;
		}
	}
	//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "�� %d\n", nCntWall);
	return nCntWall;
}
//==================================================================================================//
//	* �v���C���[�̈ʒu�ύX *
//==================================================================================================//
void CDungeon::SetPpos(D3DXVECTOR3 pos)
{
	CManager::GetPlayer()->Getpos() = pos;
	CManager::GetPlayer()->Getrot() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CManager::GetPlayer()->Getposold() = CManager::GetPlayer()->Getpos();
	CManager::GetCamera()->GetRot().y = 0.0f;
	CManager::GetCamera()->Reset();
}
//==================================================================================================//
//	* �v���C���[�̈ʒu�ύX *
//==================================================================================================//
void CDungeon::SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type)
{
	CEnemy *pEnemy;
	if (SceneCreate(pEnemy, CHAR_PRIORITY)) { pEnemy->Set(pos, rot, type); }
}
//==================================================================================================//
//    * ���[���I�u�W�F���̍쐬 *
//==================================================================================================//
void CDungeon::SetObjRoom(D3DXVECTOR3 pos)
{
	//CSceneObjct *pObject;
	//float		fRot = (rand() % 8) * (D3DX_PI * 0.25f);
	//CSceneModel::MODEL model = ((CSceneModel::MODEL)(CSceneModel::MODEL_STEEL));

	//if (SceneCreate(pObject, MODEL_PRIORITY)) { pObject->Set(pos, D3DXVECTOR3(0.0f, (rand() % 628) * 0.01f, 0.0f), CSceneModel::MODEL_STEEL_B, true, CSceneObjct::USE_MAX); }
	//
	//for (int nCntObj = 0; nCntObj < 3; nCntObj++)
	//{
	//	fRot += D3DX_PI * 0.1f;
	//	for (int nCount = 0; nCount < 4; nCount++)
	//	{
	//		if (SceneCreate(pObject, MODEL_PRIORITY))
	//		{//�I�u�W�F�̐ݒu
	//			pObject->Set(pos + D3DXVECTOR3(sinf(fRot + nCount * D3DX_PI * 0.5f), 0.0f, cosf(fRot + nCount * D3DX_PI * 0.5f)) * 400.0f,
	//				D3DXVECTOR3(0.0f, fRot + nCount * D3DX_PI * 0.5f + D3DX_PI * 0.5f, 0.0f), model, true, CSceneObjct::USE_MAX);
	//		}
	//		if (nCntObj == 1)
	//		{//�G�̐ݒu
	//			SetEnemy(pos + D3DXVECTOR3(sinf(fRot + nCount * D3DX_PI * 0.5f), 0.0f, cosf(fRot + nCount * D3DX_PI * 0.5f)) * 300.0f,
	//				D3DXVECTOR3(0.0f, fRot + nCount * D3DX_PI * 0.5f + D3DX_PI * 0.5f, 0.0f), CMotion::TYPE_BOX_Sword);
	//		}
	//	}
	//}
}
//==================================================================================================//
//    * ���[���I�u�W�F���̍쐬 *
//==================================================================================================//
void CDungeon::SetObjRoom2(D3DXVECTOR3 pos, float fRot)
{
	//CSceneObjct *pObject;
	//CSceneModel::MODEL model = ((CSceneModel::MODEL)(CSceneModel::MODEL_STEEL));

	//if (SceneCreate(pObject, MODEL_PRIORITY)) { pObject->Set(pos, D3DXVECTOR3(0.0f, (rand() % 628) * 0.01f, 0.0f), CSceneModel::MODEL_STEEL_B, true, CSceneObjct::USE_MAX); }

	//for (int nCntObj = 0; nCntObj < 3; nCntObj++)
	//{
	//	fRot += D3DX_PI * 0.1f;
	//	for (int nCount = 0; nCount < 4; nCount++)
	//	{
	//		if (SceneCreate(pObject, MODEL_PRIORITY))
	//		{
	//			pObject->Set(pos + D3DXVECTOR3(sinf(fRot + nCount * D3DX_PI * 0.5f), 0.0f, cosf(fRot + nCount * D3DX_PI * 0.5f)) * 400.0f,
	//				D3DXVECTOR3(0.0f, fRot + nCount * D3DX_PI * 0.5f + D3DX_PI * 0.5f, 0.0f), model, true, CSceneObjct::USE_MAX);
	//		}
	//	}
	//}

	//for (int nCntObj = 0; nCntObj < 6; nCntObj++)
	//{
	//	fRot += D3DX_PI * 0.05f;
	//	for (int nCount = 0; nCount < 4; nCount++)
	//	{
	//		if (SceneCreate(pObject, MODEL_PRIORITY))
	//		{
	//			pObject->Set(pos + D3DXVECTOR3(sinf(fRot + nCount * D3DX_PI * 0.5f), 0.0f, cosf(fRot + nCount * D3DX_PI * 0.5f)) * 1100.0f,
	//				D3DXVECTOR3(0.0f, fRot + nCount * D3DX_PI * 0.5f + D3DX_PI * 0.5f, 0.0f), CSceneModel::MODEL_STONE, true, CSceneObjct::USE_MAX);
	//		}
	//	}
	//}
}
//==================================================================================================//
//    * ���[�h�I�u�W�F�̍쐬 *
//==================================================================================================//
void CDungeon::SetObjRoad(D3DXVECTOR3 pos)
{
	//CSceneObjct *pObject;
	//float fRand = (rand() % 628) * 0.01f;
	//if (SceneCreate(pObject, MODEL_PRIORITY))
	//{
	//	pObject->Set(pos + D3DXVECTOR3(sinf(fRand), 0.0f, cosf(fRand)) * 50.0f,
	//		D3DXVECTOR3(0.0f, (rand() % 628) * 0.01f, 0.0f), CSceneModel::MODEL_STONE_S, true, CSceneObjct::USE_MAX);
	//}
}
//==================================================================================================//
//    * �G���g�����X�I�u�W�F�̍쐬 *
//==================================================================================================//
void CDungeon::SetObjEntrance(D3DXVECTOR3 pos)
{

}