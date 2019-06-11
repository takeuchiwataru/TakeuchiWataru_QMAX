//---------------------------------------------------------------------
// マネージャー処理 [manager.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "billboard.h"
#include "player.h"
#include "input.h"
#include "meshField.h"
#include "meshOrbit.h"

#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "gameover.h"
#include "ranking.h"

#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FILE_NAME						("model.txt")

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
static CRenderer *m_pRenderer;
CRenderer		*CManager::m_pRenderer			= NULL;
CInputKeyboard	*CManager::m_pInput				= NULL;
CInputJoypad	*CManager::m_pInputJoypad		= NULL;
CSound			*CManager::m_pSound[MAX_SOUND] = {};
CDebugProc		*CManager::m_pDebugProc			= {};
CScene3D        *CManager::m_Scene3D			= NULL;
CSceneMeshField *CManager::m_MeshField			= NULL;

LPD3DXMESH					CManager::m_pMeshModel[MAX_PARTS] = {};
LPD3DXBUFFER				CManager::m_pBuffMatModel[MAX_PARTS] = {};
LPDIRECT3DTEXTURE9			CManager::m_pTextureModel[MAX_PARTS] = {};
DWORD						CManager::m_nNumMatModel[MAX_PARTS] = {};

CManager::MODE	CManager::m_mode = CManager::MODE_TITLE;
CFade			*CManager::m_pFade = NULL;

CTitle			*CManager::m_pTitle			= NULL;
CTutorial		*CManager::m_pTutorial		= NULL;
CGame			*CManager::m_pGame			= NULL;
CResult			*CManager::m_pResult		= NULL;
CGameover		*CManager::m_pGameover		= NULL;
CRanking		*CManager::m_pRanking		= NULL;
CCamera			*CManager::m_pCamera		= NULL;
CLight			*CManager::m_pLight			= NULL;
int				CManager::m_nScore[MAX_RANKING] = {};
int				CManager::m_nGameScore = 0;
int				CManager::m_nItemNum = 0;
int				CManager::m_nTime = 0;
int				CManager::m_nTitle = 0;
//--------------------------------------------
//マネージャークラス コンストラクタ
//--------------------------------------------
CManager::CManager()
{
}

//--------------------------------------------
//マネージャークラス デストラクタ
//--------------------------------------------
CManager::~CManager()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance,HWND hWnd, bool bWindow)
{
	//ReleaseAllで消えないものはnewで書くcreateではなく
	//レンダリング初期化
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{	// 初期化処理
		m_pRenderer->Init(hWnd, bWindow);
	}

	// 入力情報初期化
	m_pInput = new CInputKeyboard;
	if (m_pInput != NULL)
	{	// 初期化処理
		m_pInput->Init(hInstance,hWnd);
	}
	//ゲームパッド
	m_pInputJoypad = new CInputJoypad;
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Init(hInstance, hWnd);
	}

	for (int nCnt = 0; nCnt < MAX_SOUND; nCnt++)
	{
		m_pSound[nCnt] = new CSound;
		if (m_pSound[nCnt] != NULL)
		{
			m_pSound[nCnt]->InitSound(hWnd);
		}
	}

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

#ifdef _DEBUG
	//デバックプロシージャの初期化
	m_pDebugProc->Init();
#endif

	//ランキングの初期化
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_nScore[nCnt] = 5000 - (nCnt * 1000);
	}

	m_nTitle = 0;

	//最初のモードを設定
	m_mode = MODE_TITLE;
	//フェードの設定
	m_pFade = CFade::Create(m_mode);
	//現在のモードの設定
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// マネージャークラス 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//キーボードクラスの破棄
	if (m_pInput != NULL)
	{	// 終了処理
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;
	}
	//ゲームパッド
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Uninit();
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}
	//レンダリングクラスの破棄
	if (m_pRenderer != NULL)
	{	// 終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	//フェードクラスの破棄
	if (m_pFade != NULL)
	{	// 終了処理
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}


	for (int nCnt = 0; nCnt < MAX_SOUND; nCnt++)
	{
		if (m_pSound[nCnt] != NULL)
		{
			m_pSound[nCnt]->UninitSound();
			delete m_pSound[nCnt];
			m_pSound[nCnt] = NULL;
		}
	}

	//タイトルクラスの破棄
	if (m_pTitle != NULL)
	{	// 終了処理
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;
	}
	//チュートリアルクラスの破棄
	if (m_pTutorial != NULL)
	{	// 終了処理
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = NULL;
	}
	//ゲームクラスの破棄
	if (m_pGame != NULL)
	{	// 終了処理
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;
	}
	//リザルトクラスの破棄
	if (m_pResult != NULL)
	{	// 終了処理
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = NULL;
	}
	//ゲームオーバークラスの破棄
	if (m_pGameover != NULL)
	{	// 終了処理
		m_pGameover->Uninit();
		delete m_pGameover;
		m_pGameover = NULL;
	}
	//ランキングクラスの破棄
	if (m_pRanking != NULL)
	{	// 終了処理
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;
	}

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
// マネージャークラス 更新処理
//=============================================================================
void CManager::Update(void)
{
	// レンダリング更新処理
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// キーボード更新処理
	if (m_pInput != NULL)
	{
		m_pInput->Update();
	}
	// ゲームパッド更新処理
	if (m_pInputJoypad != NULL)
	{
		m_pInputJoypad->Update();
	}
	// フェード更新処理
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

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

#ifdef _DEBUG
	//デバックプロシージャの更新
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Update();
	}

	CDebugProc::Print(1, " タイトル %d \n", m_nTitle);

#endif

	//モードごとの更新処理
	switch (m_mode)
	{
	case MODE_TITLE:
		//タイトルの更新処理
		m_pTitle->Update();
		break;
	case MODE_TUTORIAL:
		//チュートリアルの更新処理
		m_pTutorial->Update();
		break;
	case MODE_GAME:
		//ゲームの更新処理
		m_pGame->Update();
		break;
	case MODE_RESULT:
		//リザルトの更新処理
		m_pResult->Update();
		break;
	case MODE_GAMEOVER:
		//ゲームオーバーの更新処理
		m_pGameover->Update();
		break;
	case MODE_RANKING:
		//ランキングの更新処理
		m_pRanking->Update();
		break;
	}
}

//=============================================================================
// マネージャークラス 描画処理
//=============================================================================
void CManager::Draw(void)
{
	//レンダリングを設定
	if (m_pRenderer != NULL)
	{	// 描画処理
		m_pRenderer->Draw();
	}

	//カメラを設定
	if (m_pCamera != NULL)
	{
		m_pCamera->SetCamera();
	}

	//モードごとの更新処理
	switch (m_mode)
	{
	case MODE_TITLE:
		//タイトルの描画処理
		m_pTitle->Draw();
		break;
	case MODE_TUTORIAL:
		//チュートリアルの描画処理
		m_pTutorial->Draw();
		break;
	case MODE_GAME:
		//ゲームの描画処理
		m_pGame->Draw();
		break;
	case MODE_RESULT:
		//リザルトの描画処理
		m_pResult->Draw();
		break;
	case MODE_GAMEOVER:
		//ゲームオーバーの描画処理
		m_pGameover->Draw();
		break;
	case MODE_RANKING:
		//ランキングの描画処理
		m_pRanking->Draw();
		break;
	}
}
//=============================================================================
// マネージャークラス レンダリングを取得
//=============================================================================
CRenderer *CManager::GetRenderer (void)
{
	return m_pRenderer;
}

//=============================================================================
// マネージャークラス キーボードを取得
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInput;
}
//=============================================================================
// マネージャークラス ジョイスティックを取得
//=============================================================================
CInputJoypad *CManager::GetCInputJoypad(void)
{
	return m_pInputJoypad;
}
//=============================================================================
// マネージャークラス サウンドを取得
//=============================================================================
CSound *CManager::GetSound(int nNum)
{
	return m_pSound[nNum];
}

//=============================================================================
// マネージャークラス シーン3Dを取得
//=============================================================================
CScene3D * CManager::GetScene3D(void)
{
	return m_Scene3D;
}

//=============================================================================
// マネージャークラス メッシュフィールドを取得
//=============================================================================
CSceneMeshField * CManager::GetSceneMeshField(void)
{
	return m_MeshField;
}

//=============================================================================
// マネージャークラス フェードを取得
//=============================================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// モードの設定処理
//=============================================================================
void CManager::SetMode(MODE mode)
{
	//現在のモード
	switch (m_mode)
	{
	case MODE_TITLE:
		//BGMの停止
		if (m_pTitle != NULL)
		{
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_TITLE);
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;	//NULLにする
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			//BGMの停止
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_TUTORIAL);
			m_pTutorial->Uninit();
			delete m_pTutorial;
			m_pTutorial = NULL;	//NULLにする
		}
		break;
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			//BGMの停止
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_GAME);
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;		//NULLにする
		}
		break;
	case MODE_RESULT:
		if (m_pResult != NULL)
		{
			//BGMの停止
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_RESULT);
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;		//NULLにする
		}
		break;
	case MODE_GAMEOVER:
		if (m_pGameover != NULL)
		{
			//BGMの停止
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_GAMEOVER);
			m_pGameover->Uninit();
			delete m_pGameover;
			m_pGameover = NULL;		//NULLにする
		}
		break;
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			//BGMの停止
			m_pSound[0]->StopSound(m_pSound[0]->SOUND_LABEL_BGM_RANKING);
			m_nGameScore = 0;
			m_pRanking->Uninit();
			delete m_pRanking;
			m_pRanking = NULL;		//NULLにする
		}
		break;
	}

	//現在のモードを切り替え
	m_mode = mode;

	//新しい画面のモード
	switch (mode)
	{
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{//BGMの再生
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_TITLE);
			m_nGameScore = 0;
			m_nTitle++;
			m_pTitle = CTitle::Create();
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{//BGMの再生
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_TUTORIAL);
			m_pTutorial->Load();
			m_pTutorial = CTutorial::Create();
		}
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{//BGMの再生
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_GAME);
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{//BGMの再生
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_RESULT);
			m_pResult = CResult::Create();
		}
		break;
	case MODE_GAMEOVER:
		if (m_pGameover == NULL)
		{//BGMの再生
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_GAMEOVER);
			m_pGameover = CGameover::Create();
		}
		break;
	case MODE_RANKING:
		if (m_pRanking == NULL)
		{//BGMの再生
			m_pSound[0]->PlaySound(m_pSound[0]->SOUND_LABEL_BGM_RANKING);
			m_pRanking = CRanking::Create();
		}
		break;
	}
}

//=============================================================================
// モードの取得処理
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// マネージャークラス カメラを取得
//=============================================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// マネージャークラス ライトを取得
//=============================================================================
CLight *CManager::GetLight(void)
{
	return m_pLight;
}



//=============================================================================
// ランキング並び替えセット
//=============================================================================
void CManager::RankingScore(int nScore)
{
	int nSaveScore = 0;

	//スコア更新
	if (m_nScore[MAX_RANKING - 1] < nScore)
	{//新しいスコアが高い時入れ替え
		m_nScore[MAX_RANKING - 1] = nScore;
		//break;
	}
	//ソート処理 大きい順
	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		for (int nCnt2 = 0; nCnt2 < MAX_RANKING - 1; nCnt2++)
		{
			if (m_nScore[nCnt2] < m_nScore[nCnt2 + 1])
			{//次と比べて自分が小さい時入れ替え
				nSaveScore = m_nScore[nCnt2];			//一時保存
				m_nScore[nCnt2] = m_nScore[nCnt2 + 1];	//数字を入れ替え
				m_nScore[nCnt2 + 1] = nSaveScore;		//保存した数字を入れる
			}
		}
	}
}
//=============================================================================
//ランキングを取得
//=============================================================================
int *CManager::GetRankingScore(int nidx)
{
	return &m_nScore[nidx];
}
//=============================================================================
//ゲームのスコアをセット
//=============================================================================
void CManager::SetGameScore(int nScore)
{
	m_nGameScore = nScore;
}
//=============================================================================
//ゲームのスコアを取得
//=============================================================================
int * CManager::GetGameScore()
{
	return &m_nGameScore;
}

//=============================================================================
//ゲームのアイテム数を取得
//=============================================================================
int * CManager::GetGameItem()
{
	return &m_nItemNum;
}

//=============================================================================
//ゲームのタイムを取得
//=============================================================================
int * CManager::GetGameTime()
{
	return &m_nTime;
}
