//---------------------------------------------------------------------
// ゲーム処理 [game.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "game.h"
#include "scene.h"
#include "scene2D.h"

#include "meshField.h"
#include "field.h"
#include "meshOrbit.h"
#include "meshCylinder.h"

#include "player.h"
#include "enemy.h"

#include "number.h"
#include "UIScore.h"
#include "UITime.h"
#include "UILife.h"
#include "UIItem.h"
#include "UIGauge.h"
#include "UIFinish.h"
#include "UIStart.h"
#include "UIExclamation.h"
#include "UIEnemy.h"

#include "objectBG.h"
#include "billboardEnemy.h"
#include "billboardItem.h"
#include "effect.h"
#include "effect3D.h"
#include "shadow.h"

#include "sound.h"
#include "input.h"
#include "manager.h"
#include "fade.h"

#include "Logo.h"
#include "pause.h"
#include "billboardObject.h"
#include "explosion.h"

#include "block.h"
#include "bullet.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define UIPOS_RIGHT		(1000)
#define UIPOS_LEFT		(280)

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
CPlayer		*CGame::m_pPlayer = NULL;
CUIItem		*CGame::m_pItem = NULL;
CUILife		*CGame::m_pLife = NULL;
CTime		*CGame::m_pTime = NULL;
CUIEnemy	*CGame::m_pUIEnemy = NULL;;

//--------------------------------------------
//ゲームクラス コンストラクタ
//--------------------------------------------
CGame::CGame()
{
	m_nFadeCnt = 0;
	m_EnemyCreateCnt = 0;
	m_EnemyNum = 0;
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
	//カメラ ライトの初期化
	CManager::GetCamera()->Init();
	CManager::GetLight()->Init();

	//テクスチャやモデルの読み込み
	CObjectBG::Load();
	CBillBoardEnemy::Load();
	CBillBoardItem::Load();
	CField::Load();
	CUILife::Load();
	CUIItem::Load();
	CNumber::Load();
	CEffect::Load();
	C3DEffect::Load();
	CPause::Load();
	CUIGauge::Load();
	CShadow::Load();
	CBillBoardObject::Load();
	CUIFinish::Load();
	CUIStart::Load();
	CUIExclamation::Load();
	CEnemy::Load();
	// ブロックのモデルの読み込み
	CBlock::LoadModel();
	CBlock::LoadMat();
	// 弾
	CBullet::LoadModel();
	CUIEnemy::Load();

	// 桜ひらひらの読み込み
	CExplosion::Load();
	//空の生成
	CSceneMeshCylinder::Create(D3DXVECTOR3(0, 18000, 0), 8000.0f, 28000.0f, 10, 1,CSceneMeshCylinder::CYLINDERTYPE_INWARD);

	//ポーズ生成
	CPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 150);
	//メッシュフィールド生成
	CSceneMeshField::Create(D3DXVECTOR3(0, 0, 99900), 1000.0f, 100000.0f, 10, 1000);
	CSceneMeshField::Create(D3DXVECTOR3(-1000, 0, 99900), 1000.0f, 100000.0f, 10, 1000);

	//道
	//CField::Create(D3DXVECTOR3(-100, 0.3f, 100000), 200, 101000, CField::FIELDTEX_ROADWAY, 1, 1000);
	//草
	//CField::Create(D3DXVECTOR3(-2000, 0.3f, 100000), 1000, 101000, CField::FIELDTEX_GARDEN, 10, 1000);
	//CField::Create(D3DXVECTOR3(1000, 0.3f, 100000), 1000, 101000, CField::FIELDTEX_GARDEN, 10, 1000);
	//プレイヤーを生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0,0,0), D3DXVECTOR3(0, D3DX_PI * 1.0f, 0),10);
	//3Dオブジェクト

	for (int nCnt = 1; nCnt < 30; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(-550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL003, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL003, CObjectBG::MOVETYPE_NONE, 0);
	}

	for (int nCnt = 30; nCnt < 60; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(-550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL002, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL002, CObjectBG::MOVETYPE_NONE, 0);
	}

	for (int nCnt = 60; nCnt < 90; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(-550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL001, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(550.0f, 0, (nCnt * 400.0f)), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL001, CObjectBG::MOVETYPE_NONE, 0);
	}

	//2D UI
	if (m_pLife != NULL)
	{
		m_pLife = NULL;
	}
	//ライフのUIを生成
	//m_pLife = CUILife::Create(D3DXVECTOR3(900, 70, 0), 50, 50);

	if (m_pItem != NULL)
	{
		m_pItem = NULL;
	}
	//アイテム獲得数のUIを生成
	//m_pItem = CUIItem::Create(D3DXVECTOR3(80, 150, 0), 90, 100);
	//ゲージを生成
	//CUIGauge::Create(D3DXVECTOR3(1100, 680, 0), 100, 300);

	//スコアUIの生成
	if (m_pTime != NULL)
	{
		m_pTime = NULL;
	}
	//m_pTime = CTime::Create(D3DXVECTOR3(728, 90, 0), 80, 80);

	//値の初期化
	m_EnemyCreateCnt = 0;

	m_pUIEnemy = CUIEnemy::Create(D3DXVECTOR3(1000, 90, 0), 100, 100);

	return S_OK;
}

//=============================================================================
// ゲームクラス 終了処理
//=============================================================================
void CGame::Uninit(void)
{
	// 倒した敵の数を書き出す
	SaveNumEnemy();
	//テクスチャやモデルの破棄
	CObjectBG::UnLoad();
	CBillBoardEnemy::UnLoad();
	CBillBoardItem::UnLoad();
	CField::UnLoad();
	CUILife::UnLoad();
	CUIItem::UnLoad();
	CNumber::UnLoad();
	CEffect::UnLoad();
	C3DEffect::UnLoad();
	CPause::UnLoad();
	CUIGauge::UnLoad();
	CShadow::UnLoad();
	CBillBoardObject::UnLoad();
	CUIFinish::UnLoad();
	CUIStart::UnLoad();
	CUIExclamation::UnLoad();
	CEnemy::UnLoad();
	CUIEnemy::UnLoad();

	// 弾
	CBullet::UnloadModel();

	CBlock::UnloadModel();		// ブロック
								// マテリアルの解放
	CBlock::UnloadMat();		// ブロック

								// 桜ひらひらの破棄
	CExplosion::Unload();


	if (m_pLife != NULL)
	{
		//m_pLife->Uninit();
		m_pLife = NULL;
	}
	if (m_pItem != NULL)
	{
		//m_pItem->Uninit();
		m_pItem = NULL;
	}
	if (m_pTime != NULL)
	{
		//m_pTime->Uninit();
		m_pTime = NULL;
	}

	m_pUIEnemy = NULL;

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

		//m_nFadeCnt++;
		//切り替え処理
		//if (m_nFadeCnt > 20 && CFade::GetFade() == CFade::FADE_NONE)
		//{
		//	CFade::SetFade(CManager::MODE_GAME);
		//}
		//CFade::SetFade(CManager::MODE_RESULT);

	//敵の生成
	bool m_bPause = CPause::GetPauseBool();

	if (m_bPause == false)
	{
		m_EnemyCreateCnt++;
		SetEnemySpawn();
	}



#ifdef  _DEBUG
		if (pInput->GetTrigger(DIK_E) == true && CFade::GetFade() == CFade::FADE_NONE
			/*|| pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true && CFade::GetFade() == CFade::FADE_NONE*/)
		{
			//アイテムの数をセット
			//int *pnItem = CManager::GetGameItem();
			//*pnItem = m_pItem->GetItemNum();

			//アイテムの数をセット
			//int *pnTime = CManager::GetGameTime();
			//*pnTime = m_pTime->GetTime();

			//CFade::SetFade(CManager::MODE_RESULT);
		}

		//CFade::SetFade(CManager::MODE_GAME);

	CDebugProc::Print(1, "	ゲーム\n");
#endif

#ifdef  _DEBUG
	CDebugProc::Print(1, " Numキー  : (%d)\n", m_EnemyNum);
#endif


}
//=============================================================================
// ゲームクラス 描画処理
//=============================================================================
void CGame::Draw(void)
{
}


#if 1
//=============================================================================
// マネージャークラス カメラを取得
//=============================================================================
//CCamera *CGame::GetCamera(void)
//{
//	return m_pCamera;
//}

//=============================================================================
// マネージャークラス ライトを取得
//=============================================================================
//CLight *CGame::GetLight(void)
//{
//	return m_pLight;
//}

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
//CSound *CGame::GetSound(void)
//{
//	return m_pSound;
//}

//=============================================================================
// ゲームクラス アイテムを取得
//=============================================================================
CUIItem * CGame::GetUIItem(void)
{
	return m_pItem;
}

//=============================================================================
// ゲームクラス タイムを取得
//=============================================================================
CTime * CGame::GetUITime(void)
{
	return m_pTime;
}

//=============================================================================
// 倒した敵の数をセーブ
//=============================================================================
void CGame::SaveNumEnemy(void)
{
	FILE *pFile;

	// ファイルを開く
	pFile = fopen(NUMENEMY_FILE, "w");

	if (pFile != NULL)
	{// ファイルが開けたら
	 // モデルの総数
		fprintf(pFile, "%d\n", m_pUIEnemy->GetEnemyNum());
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{// ファイルが開けなかったら
		printf("開けませんでした\n");
	}
}

//=============================================================================
// ゲームクラス ライフを取得
//=============================================================================
CUILife * CGame::GetUILife(void)
{
	return m_pLife;
}

//=============================================================================
// ゲームクラス ライフを取得
//=============================================================================
CUIEnemy * CGame::GetUIEnemy(void)
{
	return m_pUIEnemy;
}

//=============================================================================
// ゲームクラス エネミー配置
//=============================================================================
void CGame::SetEnemySpawn()
{

	if (m_EnemyCreateCnt == 250)
	{
		//エネミーの生成
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		m_EnemyNum++;
	}
	else if (m_EnemyCreateCnt == 370)
	{
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		m_EnemyNum++;
	}
	else if (m_EnemyCreateCnt == 490)
	{
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
		m_EnemyNum++;
	}
	else if (m_EnemyCreateCnt == 570)
	{
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		m_EnemyNum++;
	}
	else if (m_EnemyCreateCnt == 660)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 780)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 880)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 1080)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 1180)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 1280)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 1380)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 1580)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 1650)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 1700)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}

	else if (m_EnemyCreateCnt == 1880)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 2180)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 2250)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 2350)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 2380)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 2420)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 2580)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}
	else if (m_EnemyCreateCnt == 2650)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 2720)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 2850)
	{
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
	}

	else if (m_EnemyCreateCnt == 2950)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3020)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3030)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3050)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}

	else if (m_EnemyCreateCnt == 3090)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3130)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3210)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3190)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3250)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3280)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3300)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3310)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3340)
	{
		m_EnemyNum++;
		m_EnemyNum++;
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3360)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3370)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3400)
	{
		// 桜ひらひら
		CExplosion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3410)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3430)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3450)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}

	else if (m_EnemyCreateCnt == 3460)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3490)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3520)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3540)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3560)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3580)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3660)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3680)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3700)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3720)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3740)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3760)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3780)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3800)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3820)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3840)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3860)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3880)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3900)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
	else if (m_EnemyCreateCnt == 3920)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3940)
	{
		m_EnemyNum++;
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(UIPOS_LEFT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_LEFT);
		CUIExclamation::Create(D3DXVECTOR3(UIPOS_RIGHT, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_RIGHT);
	}
	else if (m_EnemyCreateCnt == 3960)
	{
		m_EnemyNum++;

		CUIExclamation::Create(D3DXVECTOR3(640, 600, 0), 200, 230, CUIExclamation::ENEMYPOS_CENTER);
	}
}
