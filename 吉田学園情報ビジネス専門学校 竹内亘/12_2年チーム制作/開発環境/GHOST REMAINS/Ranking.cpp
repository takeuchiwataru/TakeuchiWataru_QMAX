//=============================================================================
//
// ランキング処理 [Ranking.cpp]
// Author : 竹内亘
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include"Scene.h"
#include "manager.h"
#include "scene.h"
#include "Game.h"
#include "Ranking.h"
#include "Result.h"
#include "sound.h"
#include "Number.h"
#include "SceneModel.h"
#include "light.h"
#include "camera.h"
#include "spotLight.h"
#include "motion.h"
#include "mesh.h"
#include "dungeon.h"
#include "player.h"
#include "enemy.h"

//=============================================================================
// ランキング初期化処理
//=============================================================================
HRESULT CRanking::Init(void)
{
	//CLight *pLight;		Create(pLight);
	CCamera *pCamera;	Create(pCamera);

	CSpotLight *pSpotLight;		Create(pSpotLight);

	CMotion::Load();
	CCharacter::Load();
	CSceneObjct::InitSwitch(true);

	CScene2D * pScene2D;
	if (SceneCreate(pScene2D, 2))
	{// ランキングロゴ
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), 200, 50.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_RankingLogo);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// ランキングランク
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 20, 0.0f), 50.0f, 250.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_RankingRank);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// プレスエンター
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 430, 650.0f, 0.0f), 200.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FLASH, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_PressEnter);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// 分
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 - 18, 0.0f), 50.0f, 250.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_RankingMinute);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// 秒
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 170, SCREEN_HEIGHT / 2 - 18, 0.0f), 50.0f, 250.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_RankingSecond);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	// ナンバー
	CRanking_UI * pRankingUI;
	(Create(pRankingUI));

	// プレイヤー3体
	CPlayer *pPlayer;
	if (SceneCreate(pPlayer, CHAR_PRIORITY)) {
		pPlayer->Set(D3DXVECTOR3(-6700.0f, 950.0f, -7000.0f),
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CMotion::TYPE_BOX_Sword);
		pPlayer->SetCancelMotion(6);
	}
	if (SceneCreate(pPlayer, CHAR_PRIORITY)) {
		pPlayer->Set(D3DXVECTOR3(-6800.0f, 950.0f, -7000.0f),
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CMotion::TYPE_BOX_Sword);
		pPlayer->SetCancelMotion(6);
	}
	if (SceneCreate(pPlayer, CHAR_PRIORITY)) {
		pPlayer->Set(D3DXVECTOR3(-6900.0f, 950.0f, -7000.0f),
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CMotion::TYPE_BOX_Sword);
		pPlayer->SetCancelMotion(6);
	}

	//if (SceneCreate(pPlayer, CHAR_PRIORITY)) {
	//	pPlayer->Set(D3DXVECTOR3(-40.0f, 50.0f, -650.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_BOX_Sword);
	//	pPlayer->SetCancelMotion(6);
	//}
	//if (SceneCreate(pPlayer, CHAR_PRIORITY)) {
	//	pPlayer->Set(D3DXVECTOR3(10.0f, 50.0f, -650.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_BOX_Sword);
	//	pPlayer->SetCancelMotion(6);
	//}
	//if (SceneCreate(pPlayer, CHAR_PRIORITY)) {
	//	pPlayer->Set(D3DXVECTOR3(60.0f, 50.0f, -650.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_BOX_Sword);
	//	pPlayer->SetCancelMotion(6);
	//}


	// 敵
	CEnemy *pEnemy;
	if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
		pEnemy->Set(D3DXVECTOR3(-6860.0f, 1070.0f, -7100.0f),
			D3DXVECTOR3(0.0f, D3DX_PI, D3DX_PI * 0.5f), CMotion::TYPE_ENEMY);
	}

	LoadObject();

	CSceneObjct * pObject;
	if (SceneCreate(pObject, 0))
	{
		pObject->Set(D3DXVECTOR3(-6800.0f, 900.0f, -7300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BROCK, false, CSceneObjct::USE_MAX,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
		pObject->GetDrawType() = CScene::DRAW_TYPE_NO;
		CCamera::GetInfo().pChar = &pObject->GetPosition();
		CCamera::GetInfo().pMove = &pObject->GetPosition();
		CManager::GetCamera()->GetpDistance() = NULL;
		CManager::GetCamera()->GetRot().y = D3DX_PI * 0.0f;
		CManager::GetCamera()->Reset();
	}


	CManager::GetSound()->Play(CSound::LABEL_SE_RANKING);

	CManager::GetSound()->Play(CSound::LABEL_RANKING);
	m_fCntState = 0.0f;
	return S_OK;
}
//=============================================================================
// ランキング更新処理
//=============================================================================
void CRanking::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得

	m_fCntState += 1.0f;
	if (pInputKey->GetPress(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A))
	{
		CManager::SetFade(CManager::MODE_TITLE, 0);
	}
	else if (m_fCntState > 240.0f)
	{
		CManager::SetFade(CManager::MODE_TITLE, 0);
	}
}
//=============================================================================
// ランキング終了処理
//=============================================================================
void CRanking::Uninit(void)
{
	//BGMのストップ
	CManager::GetSound()->Stop(CSound::LABEL_RANKING);
}
//=============================================================================
// ランキング描画処理
//=============================================================================
void CRanking::Draw(void)
{
}
//=============================================================================
// オブジェクトの読み込み生成
//=============================================================================
void CRanking::LoadObject(void)
{
	//変数宣言
	D3DXVECTOR3 plusPos = D3DXVECTOR3((MAP_SIZE) * -CHIP_SIZE + CHIP_SIZE * 2.0f, 0.0f, -CHIP_SIZE * 0.5f);
	int nMaxObj = 0;
	//int nBlockX[256] = {};
	//int nBlockZ[256] = {};
	//int nNumber[255] = {};
	int * nBlockX = NULL;
	int * nBlockZ = NULL;
	float * fPosY = NULL;
	int * nNumber = NULL;
	int * nType = NULL;
	float * fAngle = NULL;
	float * fRot = NULL;
	int * nReflain = NULL;
	int * nStart = NULL;
	float * fSpeedX = NULL;
	float * fSpeedY = NULL;
	float * fSpeedZ = NULL;


	//変数宣言
	FILE *pFile;

	//テキストの読み込み
	pFile = fopen(FILE_NAME, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &nMaxObj);		//読み込むモデル数の読み込み

											//動的確保する
		nBlockX = new int[nMaxObj];
		nBlockZ = new int[nMaxObj];
		fPosY = new float[nMaxObj];
		nNumber = new int[nMaxObj];
		nType = new int[nMaxObj];
		fAngle = new float[nMaxObj];
		fRot = new float[nMaxObj];
		nReflain = new int[nMaxObj];
		nStart = new int[nMaxObj];
		fSpeedX = new float[nMaxObj];
		fSpeedY = new float[nMaxObj];
		fSpeedZ = new float[nMaxObj];

		for (int nCntModel = 0; nCntModel < nMaxObj; nCntModel++)
		{
			fscanf(pFile, "%d", &nBlockX[nCntModel]);	//ブロックX
			fscanf(pFile, "%d", &nBlockZ[nCntModel]);	//ブロックZ
			fscanf(pFile, "%f", &fPosY[nCntModel]);		//高さ
			fscanf(pFile, "%d", &nType[nCntModel]);		//タイプ
			fscanf(pFile, "%d", &nNumber[nCntModel]);	//参照ナンバー
			fscanf(pFile, "%f", &fAngle[nCntModel]);	//回転値
			fscanf(pFile, "%f", &fRot[nCntModel]);		//向き
			fscanf(pFile, "%d", &nReflain[nCntModel]);	//反射率
			fscanf(pFile, "%d", &nStart[nCntModel]);	//スタート値
			fscanf(pFile, "%f", &fSpeedX[nCntModel]);	//移動量-X
			fscanf(pFile, "%f", &fSpeedY[nCntModel]);	//移動量-Y
			fscanf(pFile, "%f", &fSpeedZ[nCntModel]);	//移動量-Z
		}

		//読み込みを終了する
		fclose(pFile);
	}

	//読み込んだオブジェクトを生成する
	CSceneObjct *pObject;
	D3DXVECTOR3 pos;
	for (int nCntModel = 0; nCntModel < nMaxObj; nCntModel++)
	{
		if (SceneCreate(pObject, 0))
		{
			fAngle[nCntModel] *= 0.05f;
			fRot[nCntModel] *= D3DX_PI;
			pos = plusPos + D3DXVECTOR3(nBlockX[nCntModel] * 200.0f - CHIP_SIZE * 4.0f, fPosY[nCntModel], -nBlockZ[nCntModel] * 200.0f);
			if (nType[nCntModel] == 0)	//ブロック
			{
				pObject->Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BROCK, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					0.0f, 0, 0, 0, nNumber[nCntModel]);
			}
			else if (nType[nCntModel] == 1)	//やり
			{
				pObject->Set(pos + D3DXVECTOR3(0.0f, -5.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_SPEAR, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 20.0f, 0.0f), 0.0f, 5, 180, nStart[nCntModel], nNumber[nCntModel]);
			}
			else if (nType[nCntModel] == 2)	//落ちる床
			{
				pObject->Set(pos,
					D3DXVECTOR3(0.0f, fRot[nCntModel], 0.0f), CSceneModel::MODEL_DFIELD, true, CSceneObjct::USE_MAX, D3DXVECTOR3(fSpeedX[nCntModel], fSpeedY[nCntModel], fSpeedZ[nCntModel]), fAngle[nCntModel], nReflain[nCntModel], 0, nStart[nCntModel], nNumber[nCntModel]);
			}
			else if (nType[nCntModel] == 3)	//移動床 - 小
			{
				pObject->Set(pos,
					D3DXVECTOR3(0.0f, fRot[nCntModel], 0.0f), CSceneModel::MODEL_MFIELD, true, CSceneObjct::USE_MAX, D3DXVECTOR3(fSpeedX[nCntModel], fSpeedY[nCntModel], fSpeedZ[nCntModel]), fAngle[nCntModel], nReflain[nCntModel], 60, nStart[nCntModel], nNumber[nCntModel]);
			}
			else if (nType[nCntModel] == 10)	//移動床 - 大
			{
				pObject->Set(pos,
					D3DXVECTOR3(0.0f, fRot[nCntModel], 0.0f), CSceneModel::MODEL_MFIELD2, true, CSceneObjct::USE_MAX, D3DXVECTOR3(fSpeedX[nCntModel], fSpeedY[nCntModel], fSpeedZ[nCntModel]), fAngle[nCntModel], nReflain[nCntModel], 60, nStart[nCntModel], nNumber[nCntModel]);

			}
			else if (nType[nCntModel] == 5)
			{//ボタン
				pObject->Set(pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BUTTONFLOR, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
				if (SceneCreate(pObject, MODEL_PRIORITY))
				{
					pObject->Set(pos,
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BUTTON, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, nNumber[nCntModel]);
				}
			}
			else if (nType[nCntModel] == 6)
			{//落石
				pObject->Set(pos + D3DXVECTOR3(0.0f, 500.0f, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_DROP_STONE, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.05f, 0, 0, 0, 0);
			}
			else if (nType[nCntModel] == 7)
			{//ゴール
				pObject->Set(pos,
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_GOAL, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
			}
			else if (nType[nCntModel] == 8)
			{//プレイヤーの位置
				if (CManager::GetMode() == CManager::MODE_GAME)
				{
					CManager::GetPlayer()->Getpos() = pos;
					CManager::GetCamera()->Reset();

					CEnemy *pEnemy;
					if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
						pEnemy->Set(pos + D3DXVECTOR3(2000.0f, 0.0f, 200.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY);
					}

					if (SceneCreate(pObject, 0))
					{
						pObject->Set(pos + D3DXVECTOR3(-200.0f, -30.0f, 200.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BUTTONFLOR, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
						if (SceneCreate(pObject, MODEL_PRIORITY))
						{
							pObject->Set(pos + D3DXVECTOR3(-200.0f, -30.0f, 200.0f),
								D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_NOLOOK, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, nNumber[nCntModel]);
						}
					}

					if (SceneCreate(pObject, 0))
					{
						pObject->Set(pos + D3DXVECTOR3(-200.0f, -30.0f, -200.0f),
							D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BUTTONFLOR, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
						if (SceneCreate(pObject, MODEL_PRIORITY))
						{
							pObject->Set(pos + D3DXVECTOR3(-200.0f, -30.0f, -200.0f),
								D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_WARP, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, nNumber[nCntModel]);
						}
					}
				}
			}
			else if (nType[nCntModel] == 9)
			{//ゴール
				CSceneAnim3D *pAnim;
				if (SceneCreate(pAnim, 0))
				{
					pAnim->Set(pos,
						D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(100.0f, 400.0f, 0.0f), CScene::TEX_Fire, true,
						CScene::DRAW_TYPE_MULTIPLY, 0, 8, 1, 3, CSceneAnim3D::ANIMATION_LOOP, CScene3D::STATE_FIRE);
				}
			}
		}
	}
	//データを破棄する
	delete[] nBlockX;
	delete[] nBlockZ;
	delete[] fPosY;
	delete[] nNumber;
	delete[] nType;
	delete[] fAngle;
	delete[] fRot;
	delete[] nReflain;
	delete[] nStart;
	delete[] fSpeedX;
	delete[] fSpeedY;
	delete[] fSpeedZ;

	CMesh	*pField;
	CMesh	*pCeiling;
	CMesh *pMesh;
	D3DXVECTOR3 vtx[4];
	int nMax = MAP_SIZE * FIELD_SPLIT;
	if (SceneCreate(pField, MESH_PRIORITY))
	{
		pField->Set(CMesh::TYPE_FIELD, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, -500.0f, -CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, true);
		pField->SetNor();
		pField->BindTexture(CScene::Load(CScene::TEX_Field));
	}
	if (SceneCreate(pField, MESH_PRIORITY))
	{
		pField->Set(CMesh::TYPE_FIELD, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, -300.0f, -CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, true);
		pField->SetNor();
		pField->BindTexture(CScene::Load(CScene::TEX_Field));
		pField->GetDrawType() = CScene::DRAW_TYPE_OVERLAY;
		pField->GetfUV_X() *= 3.0f;
		pField->GetfUV_Y() *= 1.5f;

	}
	if (SceneCreate(pCeiling, MESH_PRIORITY))
	{
		pCeiling->Set(CMesh::TYPE_CEILING, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE, 0.0f, -MAP_SIZE * CHIP_SIZE - CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, false);
		pCeiling->SetNor();
		pCeiling->BindTexture(CScene::Load(CScene::TEX_Wall));
	}

	vtx[0] = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * 0, 0.0f, -FIELD_SIZE * (FIELD_SPLIT - 1) - FIELD_SIZE * (nMax));
	vtx[1] = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * 0, 0.0f, -FIELD_SIZE *(FIELD_SPLIT - 1) - FIELD_SIZE * 0);
	vtx[2] = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * -nMax, 0.0f, -FIELD_SIZE *(FIELD_SPLIT - 1) - FIELD_SIZE * 0);
	vtx[3] = D3DXVECTOR3(-FIELD_SIZE * 2 + FIELD_SIZE * -nMax, 0.0f, -FIELD_SIZE *(FIELD_SPLIT - 1) - FIELD_SIZE * (nMax));

	if (SceneCreate(pMesh, MESH_PRIORITY))
	{
		pMesh->Set(CMesh::TYPE_WALL, D3DXVECTOR3(0.0f, -1000.0f, 0.0f), 10, 4, true);
		pMesh->SetWall(&vtx[0]);
		pMesh->BindTexture(CScene::Load(CScene::TEX_Wall));
		pMesh->SetNor();
	}
}

//=============================================================================
// ランキング初期化処理
//=============================================================================
HRESULT CRanking_UI::Init(void)
{
	int nData[MAX_RANKING];

	FILE *pFile;

	//ロード
	pFile = fopen("data/TEXT/ranking.txt", "r");

	if (pFile != NULL)
	{// ファイルが開けたら
		for (int nCount = 0; nCount < MAX_RANKING; nCount++)
		{
			fscanf(pFile, "%d\n", &nData[nCount]);
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		printf("ファイルが開けません\n");
	}

	int &nRankIn = CManager::GetResult()->GetnRankIn();
	D3DXCOLOR col;
	CNumber::STATE state;
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		if (nRankIn == nCount) { state = CNumber::STATE_RANKING; }
		else { state = CNumber::STATE_SCORE; }
		if (Create(m_apNumber[nCount][0]))
		{// ランキングスコア(分)
			m_apNumber[nCount][0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2 - 200 + nCount * 100.0f, 0.0f), 30.0f, 40.0f, nData[nCount] / 60 / 60, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), state);
		}

		if (Create(m_apNumber[nCount][1]))
		{// ランキングスコア(秒)
			m_apNumber[nCount][1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT / 2 - 200 + nCount * 100.0f, 0.0f), 30.0f, 40.0f, nData[nCount] / 60 % 60, 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), state);
		}
	}
	return S_OK;
}
//=============================================================================
// ランキング更新処理
//=============================================================================
void CRanking_UI::Update(void)
{
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
		{
			m_apNumber[nCount][nCntTime]->Update();
		}
	}
}
//=============================================================================
// ランキング描画処理
//=============================================================================
void CRanking_UI::Draw(void)
{
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
		{
			m_apNumber[nCount][nCntTime]->Draw();
		}
	}
}
//=============================================================================
// ランキング終了処理
//=============================================================================
void CRanking_UI::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_RANKING; nCount++)
	{
		for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
		{
			m_apNumber[nCount][nCntTime]->Uninit();
		}
	}
}
