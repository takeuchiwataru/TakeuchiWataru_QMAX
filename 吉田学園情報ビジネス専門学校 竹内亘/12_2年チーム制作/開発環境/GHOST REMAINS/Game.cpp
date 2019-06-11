//=============================================================================
//
// ゲーム処理 [Game.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include"Scene.h"
#include "manager.h"
#include "scene.h"
#include "Effect.h"
#include "player.h"
#include "mesh.h"
#include "dungeon.h"
#include "SceneModel.h"
#include "enemy.h"

#include "Game.h"
#include "Result.h"
#include "camera.h"
#include "light.h"
#include "sound.h"
//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
bool	CGame::m_bDuo = false;	//2人プレイかどうか

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME ("data//TEXT//Stage.txt")

//=============================================================================
// ゲームの初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	m_state = STATE_NONE;
	m_fCntState = 0.0f;
	m_nCntTime = 0;
	CMotion::Load();
	CCharacter::Load();
	CSceneObjct::InitSwitch(false);

	CLight *pLight;		Create(pLight);		//ライトの生成
	CCamera *pCamera;	Create(pCamera);	//カメラの生成

	CPlayer *pChar;
	if (SceneCreate(pChar, CHAR_PRIORITY))
	{
		pChar->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE, -100.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f), CMotion::TYPE_BOX_Sword);
	}
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

	//槍、-50
	//if (SceneCreate(pObject, MODEL_PRIORITY))
	//{
	//	pObject->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE, 150.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE + 300.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_DFIELD, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
	//}
	//if (SceneCreate(pObject, MODEL_PRIORITY))
	//{
	//	pObject->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE + 300, 150.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE + 300.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_MFIELD, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
	//}
	//if (SceneCreate(pObject, MODEL_PRIORITY))
	//{
	//	pObject->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE + 600, 150.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE + 300.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), CSceneModel::MODEL_MFIELD2, true, CSceneObjct::USE_MAX, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
	//}


	//CSceneAnim3D *pAnim;
	//if (SceneCreate(pAnim, 3))
	//{
	//	pAnim->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE, 0.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE - 300.0f),
	//		D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(100.0f, 400.0f, 0.0f), CScene::TEX_Fire, true,
	//		CScene::DRAW_TYPE_MULTIPLY, 0, 8, 1, 3, CSceneAnim3D::ANIMATION_LOOP, CScene3D::STATE_FIRE);
	//}
	//CEnemy *pEnemy;
	//if (SceneCreate(pEnemy, CHAR_PRIORITY)) { pEnemy->Set(D3DXVECTOR3((MAP_SIZE / 2) * -CHIP_SIZE, 0.0f, (MAP_SIZE / 2) * -CHIP_SIZE - (CHIP_SIZE / 2) - CHIP_SIZE + 1001.0f), 
	//	D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY); }

	LoadObject();
	CManager::GetSound()->Play(CSound::LABEL_GAME);
	CManager::GetSound()->Play(CSound::LABEL_SE_START);	//心音
	return S_OK;
}
//=============================================================================
// ゲームの更新処理
//=============================================================================
void CGame::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	//if (pInputKey->GetTrigger(DIK_RETURN))
	//{
	//	CManager::SetFade(CManager::MODE_RESULT, 0); 
	//}
	switch (m_state)
	{
	case STATE_NONE:
		Pause();	//ポーズの更新
		break;
	case STATE_CLEAR:
		m_fCntState += 1.0f;

		switch ((int)m_fCntState)
		{
		case 60:
			break;
		case 240:
			CManager::SetFade(CManager::MODE_RESULT, 0);
			break;
		}
		if (m_fCntState > 90 && (
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(0)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(0)->GetTrigger(INPUT_B) ||
			CManager::GetInputJoyPad(1)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_B) ||
			CManager::GetInputKey()->GetTrigger(DIK_RETURN)))
		{
			CManager::SetFade(CManager::MODE_RESULT, 0);
		}
		break;

	case STATE_OVER:
		m_fCntState += 1.0f;
		switch ((int)m_fCntState)
		{
		case 240:
			CManager::SetFade(CManager::MODE_TITLE, 0);
			break;
		}
		if (m_fCntState > 60 && (
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_START) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_START) || 
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_A) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_A) ||
			CManager::GetInputJoyPad(0)->GetTrigger(INPUT_B) || CManager::GetInputJoyPad(1)->GetTrigger(INPUT_B) ||
			CManager::GetInputKey()->GetTrigger(DIK_RETURN)))
		{
			CManager::SetFade(CManager::MODE_TITLE, 0);
		}
		break;
	}
	
}
//=============================================================================
// ゲームの終了処理
//=============================================================================
void	CGame::Uninit(void)
{
	//BGMのストップ
	CManager::GetSound()->Stop();

	for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++)
	{//全ポーズの破棄
		if (m_pScene2D[nCount] != NULL)
		{//生成されていれば削除
			m_pScene2D[nCount]->Uninit();
			m_pScene2D[nCount] = NULL;
		}
	}

	CManager::GetCamera()->Uninit();
	CManager::GetLight()->Uninit();
}
//=============================================================================
// ゲームの状態変更処理
//=============================================================================
void	CGame::SetState(STATE state)
{
	CScene2D *pScene2D;

	if (CManager::GetMode() != CManager::MODE_GAME) { return; }
	if (m_state == STATE_NONE)
	{//通常状態なら
		m_state = state;
		switch (m_state)
		{
		case STATE_CLEAR:
			CManager::GetSound()->Stop();
			CManager::GetSound()->Play(CSound::LABEL_CLEAR);

			m_fCntState = 0.0f;
			CManager::GetResult()->GetnTime() = m_nCntTime;
			if (SceneCreate(pScene2D, S2D_PRIORITY))
			{//画面を暗くする
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FADEIN5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEX_MAX);
			}
			break;
		case STATE_OVER:
			CManager::GetSound()->Stop();
			CManager::GetSound()->Play(CSound::LABEL_OVER);
			CManager::GetSound()->Play(CSound::LABEL_SE_DETH);
			m_fCntState = 0.0f;
			if (SceneCreate(pScene2D, S2D_PRIORITY))
			{//画面を暗くする
				pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
					D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FADEIN5, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), CScene2D::TEX_MAX);
			}
			break;
		}
	}
}
//=============================================================================
// ゲームのポーズ処理
//=============================================================================
void	CGame::Pause(void)
{
	if (CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
	{
		CSound *pSound = CManager::GetSound();					//サウンドのポインタを取得
		CInputKeyboard *pInputKey = CManager::GetInputKey();	//キーボード情報獲得
		CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
		CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//ジョイパッド情報獲得
		bool bSelect = false;
		bool bPause = true;

		if (!CScene::GetbPause())
		{//ポーズでない
			m_nCntTime++;
			if (pInputKey->GetTrigger(DIK_P) || pInputPad0->GetTrigger(INPUT_START) || pInputPad1->GetTrigger(INPUT_START))
			{//ポーズ起動
				CManager::GetSound()->Play(CSound::LABEL_SE_PAUSE);

				CScene::GetbPause() = true;
				bSelect = true;
				m_nSelect = 1;

				if (SceneCreate(m_pScene2D[0], PAUSE_PRIORITY))
				{//画面暗くする
					m_pScene2D[0]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
						D3DX_PI, 0, 1, 1, 0.0f, CScene2D::STATE_NORMAL, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.65f), CScene::TEX_MAX);
				}
				if (SceneCreate(m_pScene2D[1], PAUSE_PRIORITY))
				{//上セレクト　コンテニュー
					m_pScene2D[1]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - GAME_PAUSE_INTERVAL, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 0, 1, 3, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Pause);
				}
				if (SceneCreate(m_pScene2D[2], PAUSE_PRIORITY))
				{//下セレクト　リトライ
					m_pScene2D[2]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 1, 1, 3, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Pause);
				}
				if (SceneCreate(m_pScene2D[3], PAUSE_PRIORITY))
				{//下セレクト　リタイア
					m_pScene2D[3]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + GAME_PAUSE_INTERVAL, 0.0f), GAME_PAUSE_LOGOX, GAME_PAUSE_LOGOY,
						D3DX_PI, 2, 1, 3, 100.0f, CScene2D::STATE_SMALL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_Pause);
				}
				if (SceneCreate(m_pScene2D[4], PAUSE_PRIORITY))
				{//マーカー
					(m_pScene2D[4]->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 - GAME_PAUSE_LOGOX, SCREEN_HEIGHT / 2 + GAME_PAUSE_INTERVAL, 0.0f), 50.0f, 50.0f, D3DX_PI, 0, 1, 1, 100.0f, CScene2D::STATE_FLASH2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_MAX));
				}
			}
		}
		else if (pInputKey->GetTrigger(DIK_P) || pInputPad0->GetTrigger(INPUT_START) || pInputPad1->GetTrigger(INPUT_START)
			|| pInputPad0->GetTrigger(INPUT_B) || pInputPad1->GetTrigger(INPUT_B))
		{//ポーズ止め
			bPause = false;
			CManager::GetSound()->Play(CSound::LABEL_SE_CANCEL);
		}

		if (CScene::GetbPause())
		{//ポーズ中
			if (pInputKey->GetTPress(DIK_UP) || 
				pInputPad0->GetTPress(INPUT_UP) || pInputPad0->GetTPress(INPUT_LS_U) ||
				pInputPad1->GetTPress(INPUT_UP) || pInputPad1->GetTPress(INPUT_LS_U))
			{ m_nSelect = (m_nSelect - 1 + 2) % 3 + 1; bSelect = true; }

			if (pInputKey->GetTPress(DIK_DOWN) || 
				pInputPad0->GetTPress(INPUT_DOWN) || pInputPad0->GetTPress(INPUT_LS_D) ||
				pInputPad1->GetTPress(INPUT_DOWN) || pInputPad1->GetTPress(INPUT_LS_D))
			{ m_nSelect = (m_nSelect - 1 + 1) % 3 + 1;  bSelect = true; }

			if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A) || pInputPad1->GetTrigger(INPUT_A))
			{
				CManager::GetSound()->Play(CSound::LABEL_SE_ENTTER);
				if (m_nSelect == 1) { bPause = false; }
				else if (m_nSelect == 2) { CManager::SetFade(CManager::MODE_GAME, 0); CScene::GetbPause() = false; return; }
				else if (m_nSelect == 3) { CManager::SetFade(CManager::MODE_TITLE, 0); CScene::GetbPause() = false; return; }
			}

			if (!bPause)
			{//ポーズが終了した
				CScene::GetbPause() = false;

				for (int nCount = 0; nCount < MAX_GAME_PAUSE; nCount++)
				{//全ポーズの破棄
					if (m_pScene2D[nCount] != NULL)
					{//生成されていれば削除
						m_pScene2D[nCount]->Uninit();
						m_pScene2D[nCount] = NULL;
					}
				}
			}
			else if (bSelect)
			{//状態の更新
				//CSceneAnim2D *p2DAnim;
				CManager::GetSound()->Play(CSound::LABEL_SE_CURSOR);

				for (int nCount = 1; nCount <= 3; nCount++)
				{
					if (m_nSelect == nCount)
					{ //選択されている
						m_pScene2D[nCount]->GetState()[0] = CScene2D::STATE_BIG;
					}
					else
					{ //選択されてない
						m_pScene2D[nCount]->GetState()[0] = CScene2D::STATE_SMALL;
					}
				}
				m_pScene2D[4]->SetPosition(m_pScene2D[m_nSelect]->GetPosition()[0] + D3DXVECTOR3(-GAME_PAUSE_LOGOX * 1.5f, 0.0f, 0.0f));
				////光エフェクト
				//if (SceneCreate(p2DAnim, PAUSE_PRIORITY))
				//{
				//	p2DAnim->Set(m_pScene2D[m_nSelect]->GetPosition()[0] + D3DXVECTOR3(0.0f, 0.0f, 0.0f), 500.0f, 200.0f, D3DX_PI, 0, 3, 3, 3, 0.0f, CScene2D::STATE_FADEIN,
				//		CSceneAnim3D::ANIMATION_NORMAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_MAX);
				//	p2DAnim->BindDrawType(CScene::DRAW_TYPE_OVERLAY);
				//}
			}
		}
	}//フェード確認

}
//=============================================================================
// オブジェクトの読み込み生成
//=============================================================================
void CGame::LoadObject(void)
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
				CManager::GetPlayer()->Getpos() = pos;
				CManager::GetPlayer()->Getrot().y = D3DX_PI * -0.5f;
				CManager::GetPlayer()->GetfRot() = D3DX_PI * -0.5f;
				CManager::GetCamera()->GetRot().y = D3DX_PI * -0.5f;
				CManager::GetCamera()->Reset();

				CEnemy *pEnemy;
				if (SceneCreate(pEnemy, CHAR_PRIORITY)) { pEnemy->Set(pos + D3DXVECTOR3(2000.0f, 0.0f, 200.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), CMotion::TYPE_ENEMY); }

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
}