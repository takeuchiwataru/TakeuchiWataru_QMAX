//=============================================================================
//
// ゲーム処理 [Game.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene.h"
#include "manager.h"
#include "scene.h"
#include "Game.h"
#include "Practice.h"
#include "sound.h"
#include "camera.h"
#include "spotLight.h"
#include "mesh.h"
#include "dungeon.h"
#include "SceneModel.h"

//=============================================================================
// ゲームの初期化処理
//=============================================================================
HRESULT CPractice::Init(void)
{
	CScene2D *pScene2D;
	CScene3D *pScene3D;

	CSpotLight *pSpotLight;		Create(pSpotLight);		//ライトの生成
	CCamera *pCamera;	Create(pCamera);	//カメラの生成
	CMesh	*pField;
	CMesh	*pCeiling;
	CMesh *pMesh;
	D3DXVECTOR3 vtx[4];
	int nMax = MAP_SIZE * FIELD_SPLIT;

	if (SceneCreate(pField, MESH_PRIORITY))
	{
		pField->Set(CMesh::TYPE_FIELD, D3DXVECTOR3(-MAP_SIZE * CHIP_SIZE , -500.0f, -CHIP_SIZE * 2), MAP_SIZE * FIELD_SPLIT, MAP_SIZE * FIELD_SPLIT, true);
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

	CSceneObjct * pObject;
	if (SceneCreate(pObject, 3))
	{
		pObject->Set(D3DXVECTOR3(-5000.0f, 0.0f, 40.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), CSceneModel::MODEL_BROCK, false, CSceneObjct::USE_MAX,
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0, 0, 0, 0);
		pObject->GetDrawType() = CScene::DRAW_TYPE_NO;
		CCamera::GetInfo().pChar = &pObject->GetPosition();
		CCamera::GetInfo().pMove = &pObject->GetPosold();
		CManager::GetCamera()->GetpDistance() = NULL;
		CManager::GetCamera()->GetRot().y = 0.0f;
		CManager::GetCamera()->Reset();
	}

	if (SceneCreate(pScene2D, 2))
	{// チュートリアルロゴ
		pScene2D->Set(D3DXVECTOR3(250.0f, 50.0f, 0.0f), 200.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_NORMAL,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_TutorialLogo);
	}

	if (SceneCreate(pScene3D, 2))
	{// チュートリアル
		pScene3D->Set(D3DXVECTOR3(-5000.0f,150.0f,-400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			D3DXVECTOR3(430.0f, 230.0f, 0.0f), CScene::TEX_TUTORIAL, 0, 1, 1, true, CScene::DRAW_TYPE_NORMAL);
	}

	if (SceneCreate(pScene2D, 2))
	{// プレスエンター
		pScene2D->Set(D3DXVECTOR3(SCREEN_WIDTH / 2 + 430.0f, 650.0f, 0.0f), 200.0f, 50.0f, D3DX_PI, 0, 1, 1, 0.03f, CScene2D::STATE_FLASH,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CScene::TEX_PressEnter);
	}

	CManager::GetSound()->Play(CSound::LABEL_TUTORIAL);

	return S_OK;
}
//=============================================================================
// ゲームの更新処理
//=============================================================================
void CPractice::Update(void)
{
	CInputKeyboard	*pInputKey = CManager::GetInputKey();	//キーボード情報獲得
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
	CInputJoyPad	*pInputPad1 = CManager::GetInputJoyPad(1);	//ジョイパッド情報獲得

	if (CManager::GetFade().GetState() == CFade::STATE_FADE_NONE)
	{
		if (pInputKey->GetTrigger(DIK_RETURN) || pInputPad0->GetTrigger(INPUT_A))
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_ENTTER);
			CManager::SetFade(CManager::MODE_GAME, 0);
		}
		else if (pInputKey->GetTrigger(DIK_BACKSPACE))
		{
			CManager::GetSound()->Play(CSound::LABEL_SE_ENTTER);
			CManager::SetFade(CManager::MODE_TITLE, 0);
		}
	}
}
//=============================================================================
// ゲームの終了処理
//=============================================================================
void	CPractice::Uninit(void)
{
	CManager::GetpSpotLight()->Uninit();

	//BGMのストップ
	CManager::GetSound()->Stop(CSound::LABEL_TUTORIAL);
}