//---------------------------------------------------------------------
// ゲーム処理 [game.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "game.h"
#include "scene.h"
#include "scene2D.h"

#include "meshField.h"
#include "field.h"
#include "UICircle.h"
#include "meshOrbit.h"

#include "player.h"
#include "bullet.h"
#include "ball.h"
#include "syatyou.h"

#include "number.h"
#include "UIScore.h"
#include "UITime.h"
#include "UILife.h"
#include "UIItem.h"

#include "objectBG.h"
#include "billboardEnemy.h"
#include "billboardItem.h"

#include "sound.h"
#include "input.h"
#include "manager.h"
#include "fade.h"

#include "Logo.h"
//
//#include "effect.h"
//#include "pressenter.h"
//#include "pause.h"
#include "ball.h"
#include "settai.h"

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
static		CRenderer *m_pRenderer;
CPlayer		*CGame::m_pPlayer = NULL;
CCamera		*CGame::m_pCamera = NULL;
CBall		*CGame::m_pBall = NULL;
CLight		*CGame::m_pLight = NULL;
CSound		*CGame::m_pSound = NULL;
CScore		*CGame::m_pScore = NULL;
CUIItem		*CGame::m_pItem = NULL;
//CSceneMeshField *CGame::m_MeshField = NULL;
CSceneMeshFieldBG *CGame::m_MeshField = NULL;


//--------------------------------------------
//ゲームクラス コンストラクタ
//--------------------------------------------
CGame::CGame()
{
	m_nFadeCnt = 0;
	m_nCntSpawn = 0;
	m_bSpawnBoss = false;
}

//--------------------------------------------
//ゲームクラス デストラクタ
//--------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CGame *CGame::Create(void)
{
	//タイトルのポインタ
	CGame *pGame;
	pGame = new CGame;
	//タイトルの初期化
	pGame->Init();
	//タイトルの情報を返す
	return pGame;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGame::Init(void)
{
	//カメラ初期化
	m_pCamera = new CCamera;
	if (m_pCamera != NULL)
	{
		m_pCamera->Init();
	}
	//ライト初期化
	m_pLight = new CLight;
	if (m_pLight != NULL)
	{
		m_pLight->Init();
	}


	//テクスチャやモデルの読み込み
	CObjectBG::Load();
	CBillBoardEnemy::Load();
	CBillBoardItem::Load();
	CField::Load();
	CUILife::Load();
	CUIItem::Load();
	CNumber::Load();
	CCircle::Load();
	CSyatyou::Load();
	CBall::Load();
	CSettai::Load();


	//メッシュフィールド生成
	CSceneMeshField::Create(D3DXVECTOR3(-100, 0, 100), 200.0f,200.0f, 10, 10);
	//CSceneMeshField::Create(D3DXVECTOR3(-500, 0, 1900), 1000.0f, 1000.0f, 10, 10);
	//CSceneMeshField::Create(D3DXVECTOR3(-500, 0, 2900), 1000.0f, 1000.0f, 10, 10);
	CSceneMeshField::Create(D3DXVECTOR3(-800, 5.0, 11500), 1800.0f, 1800.0f,10,10);

	m_pBall = CBall::Create(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CBall::MODELTYPE_BALL, 1);
	CSettai::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 200.0f, 100.0f);

	m_MeshField = CSceneMeshFieldBG::Create(D3DXVECTOR3(-1200, -0.3f, 2000), 50.0f, 50.0f, 10, 1);
	CSceneMeshFieldBG::Create(D3DXVECTOR3(-1200, -0.3f, 4500), 50.0f, 50.0f, 10, 1);
	CSceneMeshFieldBG::Create(D3DXVECTOR3(-1200, -0.3f, 7000), 50.0f, 50.0f, 10, 1);
	CSceneMeshFieldBG::Create(D3DXVECTOR3(-1200, -0.3f, 9500), 50.0f, 50.0f, 10, 1);
	CSceneMeshFieldBG::Create(D3DXVECTOR3(-1200, -0.3f, 12000), 50.0f, 50.0f, 10, 1);
	CSceneMeshFieldBG::Create(D3DXVECTOR3(-1200, -0.3f, 14500), 50.0f, 50.0f, 10, 1);
	CSceneMeshFieldBG::Create(D3DXVECTOR3(-1200, -0.3f, 17000), 50.0f, 50.0f, 10, 1);

	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0,0, 10500),10);
	CSyatyou::Create(D3DXVECTOR3(-25, 0, -10), 10);

	//オブジェクト
	//ビル

	//道
	//CField::Create(D3DXVECTOR3(-100, 0.1f, 100), 500, 500, CField::FIELDTEX_GARDEN,1,1);

	CCircle::Create(D3DXVECTOR3(300, 15.0f, 100), 300, 300,D3DXCOLOR(1,1,0,1), CCircle::CIRCLETEX_NORMAL, 1, 1);

	//ビルボード 木
	//CSceneBillBoard::Create(D3DXVECTOR3(300, 0, 3400), 100, 200);

	//2D UI
//	CUILife::Create(D3DXVECTOR3(300, 80, 0), 40, 40);
//	m_pItem = CUIItem::Create(D3DXVECTOR3(80, 80, 0), 40, 60);

	//スコアUIの生成
	//スコアUIの生成
	m_pScore = CScore::Create(D3DXVECTOR3(1100, 50, 0), 15, 15);
	CTime::Create(D3DXVECTOR3(670, 60, 0), 20, 20);

	return S_OK;
}

//=============================================================================
// ゲームクラス 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	//テクスチャやモデルの破棄
	CObjectBG::UnLoad();
	CBillBoardEnemy::UnLoad();
	CBillBoardItem::UnLoad();
	CField::UnLoad();
	CUILife::UnLoad();
	CUIItem::UnLoad();
	CNumber::UnLoad();
	CCircle::UnLoad();
	CSyatyou::UnLoad();
	CBall::UnLoad();
	CSettai::Unload();

	//カメラ終了処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;
	}
	//ライト終了処理
	if (m_pLight != NULL)
	{
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;
	}

	//オブジェクトクラスの破棄
	CScene::ReleaseAll();
}

//=============================================================================
// ゲームクラス 更新処理
//=============================================================================
void CGame::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	//カメラ更新処理
	if (m_pCamera != NULL)
	{
		m_pCamera->Update();
	}
	//ライト更新処理
	if (m_pLight != NULL)
	{
		m_pLight->Update();
	}

	CDebugProc::Print(1, "	ゲーム\n");

}
//=============================================================================
// ゲームクラス 描画処理
//=============================================================================
void CGame::Draw(void)
{
	//カメラを設定
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}
}


#if 1
//=============================================================================
// マネージャークラス カメラを取得
//=============================================================================
CCamera *CGame::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// マネージャークラス ライトを取得
//=============================================================================
CLight *CGame::GetLight(void)
{
	return m_pLight;
}

#endif
//=============================================================================
// ゲームクラス プレイヤーを取得
//=============================================================================
CPlayer *CGame::GetPlayer(void)
{
	return m_pPlayer;
}

//=============================================================================
// ゲームクラス サウンドを取得
//=============================================================================
CSound *CGame::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// ゲームクラス アイテムを取得
//=============================================================================
CUIItem * CGame::GetUIItem(void)
{
	return m_pItem;
}

//=============================================================================
// ゲームクラス スコアを取得
//=============================================================================
//CScore *CGame::GetScore(void)
//{
//	return m_pScore;
//}

//=============================================================================
// ゲームクラス エネミー配置
//=============================================================================
void CGame::SetEnemySpawn(int nCntSpawn)
{

}
//=============================================================================
// ゲームクラス ボールを取得
//=============================================================================
CBall *CGame::GetBall(void)
{
	return m_pBall;
}
//=============================================================================
// マネージャークラス メッシュフィールドを取得
//=============================================================================
CSceneMeshFieldBG * CGame::GetSceneMeshField(void)
{
	return m_MeshField;
}
CScore * CGame::GetScore(void)
{
	return m_pScore;
}

