//=============================================================================
//
// リザルト処理 [Result.cpp]
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
#include "Result.h"
#include "sound.h"
#include "Number.h"
#include "SceneModel.h"
#include "spotLight.h"
#include "camera.h"
#include "motion.h"
#include "enemy.h"
#include "mesh.h"
#include "dungeon.h"
#include "player.h"

//=============================================================================
//	静的メンバ変数定義
//=============================================================================
int CResult::m_nTime;
int CResult::m_nRankIn;

//=============================================================================
// リザルト初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	m_nTimeEnemy = 0;
	m_nCntEnemy = 0;

	CSpotLight *pSpotLight;		Create(pSpotLight);
	CCamera *pCamera;	Create(pCamera);

	CMotion::Load();
	CCharacter::Load();
	CSceneObjct::InitSwitch(true);

	CScene2D *pScene2D;
	m_nRankIn = -1;

	if (SceneCreate(pScene2D, 2))
	{// リザルトロゴ
		pScene2D->Set(D3DXVECTOR3(300.0f, 200.0f, 0.0f), 200.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_ResaltLogo);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// プレスエンター
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 430, 650.0f, 0.0f), 200.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FLASH, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_PressEnter);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// 分
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2 - 20, 0.0f), 80.0f, 80.0f, D3DX_PI, 0, 1, 5, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_RankingMinute);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// 秒
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 250, SCREEN_HEIGHT / 2 - 20, 0.0f), 80.0f, 80.0f, D3DX_PI, 0, 1, 5, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_RankingSecond);
		pScene2D->BindDrawType(CScene::DRAW_TYPE_NORMAL);
	}

	// ナンバー
	CResult_UI * pResultUI;
	Create(pResultUI);

	LoadObject();

	CSceneObjct * pObject;
	if (SceneCreate(pObject, 0))
	{
		pObject->Set(D3DXVECTOR3(-8500.0f, -300.0f, -2100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BROCK, false, CSceneObjct::USE_MAX,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
		pObject->GetDrawType() = CScene::DRAW_TYPE_NO;
		CCamera::GetInfo().pChar = &pObject->GetPosition();
		CCamera::GetInfo().pMove = &pObject->GetPosition();
		CManager::GetCamera()->GetpDistance() = NULL;
		CManager::GetCamera()->GetRot().y = D3DX_PI * 0.0f;
		CManager::GetCamera()->Reset();
	}

	//CSceneObjct * pObject;
	//if (SceneCreate(pObject, 0))
	//{
	//	pObject->Set(D3DXVECTOR3(0.0f, 10.0f, -350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_BROCK, false, CSceneObjct::USE_MAX,
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
	//	CCamera::GetInfo().pChar = &pObject->GetPosition();
	//	CCamera::GetInfo().pMove = &pObject->GetPosition();
	//	CManager::GetCamera()->GetpDistance() = NULL;
	//	CManager::GetCamera()->Reset();
	//}

	// 敵
	CEnemy *pEnemy;
	if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
		pEnemy->Set(D3DXVECTOR3(-8500.0f, -400.0f, -2500.0f),
			D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CMotion::TYPE_ENEMY);
	}

	//if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
	//	pEnemy->Set(D3DXVECTOR3(150.0f, 50.0f, 0.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY);
	//}
	//if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
	//	pEnemy->Set(D3DXVECTOR3(-150.0f, 50.0f, 0.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY);
	//}

	return S_OK;
}
//=============================================================================
// リザルト更新処理
//=============================================================================
void CResult::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKey();	// キーボード情報獲得
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得

	if (CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
	{
		if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A))
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_ENTTER);
			CManager::SetFade(CManager::MODE_RANKING, 0);
		}
	}

	// 敵が時間差で出てくる
	CEnemy *pEnemy;

	if (m_nCntEnemy <= 2)
	{
		m_nTimeEnemy++;
	}

	if (m_nTimeEnemy == 210)
	{
		if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
			pEnemy->Set(D3DXVECTOR3(-8700.0f, -400.0f, -2500.0f),
				D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CMotion::TYPE_ENEMY);
		}
		m_nCntEnemy++;
	}

	if (m_nTimeEnemy == 100)
	{
		if (SceneCreate(pEnemy, CHAR_PRIORITY)) {
			pEnemy->Set(D3DXVECTOR3(-8300.0f, -400.0f, -2500.0f),
				D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), CMotion::TYPE_ENEMY);
		}
		m_nCntEnemy++;
	}

}
//=============================================================================
// リザルト終了処理
//=============================================================================
void CResult::Uninit(void)
{
	CManager::GetSound()->Stop(CSound::LABEL_RESULT);

}
//=============================================================================
// リザルト描画処理
//=============================================================================
void CResult::Draw(void)
{

}
//=============================================================================
// リザルト初期化処理
//=============================================================================
HRESULT CResult_UI::Init(void)
{
	int &nTime = CManager::GetResult()->GetnTime();
	int &nRankIn = CManager::GetResult()->GetnRankIn();
	//int nTime = rand() % 100000;
	int nWKData;
	int nWKRank = 5;
	m_aData[5] = nTime;

	// ロード
	Load();

	// 入れ替え
	for (int nCount = 0; nCount < MAX_DATA; nCount++)
	{
		for (int nNumber = 0; nNumber < MAX_DATA - 1; nNumber++)
		{
			if (m_aData[nNumber] > m_aData[nNumber + 1])
			{
				if (nWKRank == nNumber + 1) { nWKRank--; }
				nWKData = m_aData[nNumber];
				m_aData[nNumber] = m_aData[nNumber + 1];
				m_aData[nNumber + 1] = nWKData;
			}
		}
	}
	nRankIn = nWKRank;

	// セーブ
	Save();

	if (Create(m_pNumber[0]))
	{// リザルトスコア
		m_pNumber[0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 0.0f), 50.0f, 70.0f, nTime / 60 / 60, 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CNumber::STATE_SCORE);
	}
	if (Create(m_pNumber[1]))
	{// リザルトスコア
		m_pNumber[1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150, SCREEN_HEIGHT / 2, 0.0f), 50.0f, 70.0f, nTime / 60 % 60, 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CNumber::STATE_SCORE);
	}
	CManager::GetSound()->Play(CSound::LABEL_RESULT);

	return S_OK;
}
//=============================================================================
// リザルト更新処理
//=============================================================================
void CResult_UI::Update(void)
{
	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		m_pNumber[nCount]->Update();
	}
}
//=============================================================================
// リザルト描画処理
//=============================================================================
void CResult_UI::Draw(void)
{
	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		m_pNumber[nCount]->Draw();
	}
}
//=============================================================================
// リザルト終了処理
//=============================================================================
void CResult_UI::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_TIME; nCount++)
	{
		m_pNumber[nCount]->Uninit();
	}
}
//=============================================================================
// ロード
//=============================================================================
void CResult_UI::Load(void)
{
	FILE *pFile;

	// ファイルオープン
	pFile = fopen("data/TEXT/ranking.txt", "r");

	if (pFile != NULL)
	{// ファイルが開けたら
		for (int nCount = 0; nCount < MAX_RANKINGSCORE; nCount++)
		{
			fscanf(pFile, "%d\n", &m_aData[nCount]);
		}
		// ファイルを閉じる
		fclose(pFile);
	}

	else
	{
		printf("ファイルが開けません\n");
	}
}
//=============================================================================
// セーブ
//=============================================================================
void CResult_UI::Save(void)
{
	FILE *pFile;

	// ファイルオープン
	pFile = fopen("data/TEXT/ranking.txt", "w");

	if (pFile != NULL)
	{// ファイルが開けたら
		for (int nCount = 0; nCount < MAX_RANKINGSCORE; nCount++)
		{
			fprintf(pFile, "%d\n", m_aData[nCount]);
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		printf("ファイルが開けません\n");
	}
}
//=============================================================================
// オブジェクトの読み込み生成
//=============================================================================
void CResult::LoadObject(void)
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
		pField->GetDrawType() = CScene::DRAW_TYPE_ADD;
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
