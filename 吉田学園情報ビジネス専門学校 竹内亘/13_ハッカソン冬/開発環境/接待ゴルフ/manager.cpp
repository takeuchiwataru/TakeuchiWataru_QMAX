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
#include "bullet.h"
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
CRenderer		*CManager::m_pRenderer	= NULL;
CInputKeyboard	*CManager::m_pInput		= NULL;
CSound			*CManager::m_pSound		= NULL;
CDebugProc		*CManager::m_pDebugProc = {};
CScene3D        *CManager::m_Scene3D	= NULL;
CSceneMeshField *CManager::m_MeshField	= NULL;

LPD3DXMESH					CManager::m_pMeshModel[MAX_PARTS] = {};
LPD3DXBUFFER				CManager::m_pBuffMatModel[MAX_PARTS] = {};
LPDIRECT3DTEXTURE9			CManager::m_pTextureModel[MAX_PARTS] = {};
DWORD						CManager::m_nNumMatModel[MAX_PARTS] = {};

CManager::MODE	CManager::m_mode = CManager::MODE_TITLE;
CFade			*CManager::m_pFade = NULL;

CTitle			*CManager::m_pTitle = NULL;
CTutorial		*CManager::m_pTutorial = NULL;
CGame			*CManager::m_pGame = NULL;
CResult			*CManager::m_pResult = NULL;
CGameover		*CManager::m_pGameover = NULL;
CRanking		*CManager::m_pRanking = NULL;
CDirectInput    *CManager::m_pJoyPad = NULL;			//ジョイパッド

int				CManager::m_nGameScore = 0;
int CManager::m_aScore[MAX_RANKING] = {};	// 亘追加

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
	//サウンド初期化
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->InitSound(hWnd);
	}

	if (m_pJoyPad == NULL)
	{
		//ジョイパッドのメモリを動的確保
		m_pJoyPad = new CDirectInput;

		if (m_pJoyPad != NULL)
		{
			// 初期化処理
			m_pJoyPad->Init(hInstance, hWnd);
		}
		else
		{
			MessageBox(0, "NULLじゃないです", "警告", MB_OK);
		}
}
	else
	{
		MessageBox(0, "NULLでした", "警告", MB_OK);
	}

#ifdef _DEBUG
	//デバックプロシージャの初期化
	m_pDebugProc->Init();
#endif

	//ここがクラス化される
	//テクスチャのロード
	CBullet::Load();

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
	//オブジェクトクラスの破棄
	CScene::ReleaseAll();

	CPlayer::UnLoad();
	//キーボードクラスの破棄
	if (m_pInput != NULL)
	{	// 終了処理
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;
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
	//サウンドの破棄
	if (m_pSound != NULL)
	{
		m_pSound->UninitSound();
		delete m_pSound;
		m_pSound = NULL;
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

	//ジョイパッドクラスの破棄
	if (m_pJoyPad != NULL)
	{
		// 終了処理
		m_pJoyPad->Uninit();

		//メモリの開放
		delete m_pJoyPad;

		//NULLにする
		m_pJoyPad = NULL;
	}
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
	// フェード更新処理
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	if (m_pJoyPad != NULL)
	{
		//ジョイパッドの更新処理
		m_pJoyPad->Update();
	}

#ifdef _DEBUG
	//デバックプロシージャの更新
	if (m_pDebugProc != NULL)
	{
		m_pDebugProc->Update();
	}
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
// マネージャークラス サウンドを取得
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
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

#ifdef _DEBUG
//=============================================================================
// マネージャークラス 生成処理
//=============================================================================
void CManager::CreateSceneDebug(void)
{

}
#endif

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
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_TITLE);
		m_pTitle->Uninit();
		delete m_pTitle;
		m_pTitle = NULL;	//NULLにする
		break;
	case MODE_TUTORIAL:
		//BGMの停止
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_TUTORIAL);
		//m_pTutorial->UnLoad();
		m_pTutorial->Uninit();
		delete m_pTutorial;
		m_pTutorial = NULL;	//NULLにする
		break;
	case MODE_GAME:
		//BGMの停止
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_GAME);
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;		//NULLにする
		break;
	case MODE_RESULT:
		//BGMの停止
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_RESULT);
		m_pResult->Uninit();
		delete m_pResult;
		m_pResult = NULL;		//NULLにする
		break;
	case MODE_GAMEOVER:
		//BGMの停止
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_GAMEOVER);
		m_pGameover->Uninit();
		delete m_pGameover;
		m_pGameover = NULL;		//NULLにする
		break;
	case MODE_RANKING:
		//BGMの停止
		m_pSound->StopSound(m_pSound->SOUND_LABEL_BGM_RANKING);
		m_nGameScore = 0;
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;		//NULLにする
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
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_TITLE);
			m_nGameScore = 0;
			m_pTitle = CTitle::Create();
		}
		break;
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{//BGMの再生
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_TUTORIAL);
			m_pTutorial->Load();
			m_pTutorial = CTutorial::Create();
		}
		break;
	case MODE_GAME:
		if (m_pGame == NULL)
		{//BGMの再生
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_GAME);
			m_pGame = CGame::Create();
		}
		break;
	case MODE_RESULT:
		if (m_pResult == NULL)
		{//BGMの再生
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_RESULT);
			m_pResult = CResult::Create();
		}
		break;
	case MODE_GAMEOVER:
		if (m_pGameover == NULL)
		{//BGMの再生
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_GAMEOVER);
			m_pGameover = CGameover::Create();
		}
		break;
	case MODE_RANKING:
		if (m_pRanking == NULL)
		{//BGMの再生
			m_pSound->PlaySound(m_pSound->SOUND_LABEL_BGM_RANKING);
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
// ファイル読み込み
//=============================================================================
void CManager::FileLoad(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル読み込み用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

	D3DXVECTOR3 ParentPos;	//親の位置情報を取得
#if 1
							//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME, "r");
	//NULLチェック
	if (pFile != NULL)
	{
		while (true)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("NUM_MODEL = ");
				//文字列の先頭を設定
				strcpy(aStr, pStrcur);
				//文字列抜き出し
				m_nNumModel = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り戻す
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("MODEL_FILENAME = ");

						//文字列を設定
						strcpy(aStr, pStrcur);

						//必要な文字列の最後の文字までの文字数を数える
						int nNullNum = PopString(pStrcur, &aStr[0]);

						//文字列を取り戻す
						strcpy(aStr, pStrcur);

						//最後の文字にNULL文字を入れる
						aStr[nNullNum - 1] = '\0';

						//対象の文字列から抜き出し
						strcpy(&m_aFileNameModel[nCntModel][0], aStr);

						// Xファイルの読み込み
						D3DXLoadMeshFromX(&m_aFileNameModel[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMatModel[nCntModel],
							NULL,
							&m_nNumMatModel[nCntModel],
							&m_pMeshModel[nCntModel]);
					}
				}
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//文字列を取り出す
				strcpy(aStr, pStrcur);
			}

			if (memcmp(pStrcur, "MODELSET", strlen("MODELSET")) == 0)
			{
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//TYPEを読み込み
				if (memcmp(pStrcur, "TYPE = ", strlen("TYPE = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("TYPE = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);
					//文字列抜き出し
					nIndex = atoi(pStrcur);
				}
			}

			//スクリプトの終わり
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}
	else
	{	//ファイルが開けなかった
		printf("ファイルが開けませんでした\n");
	}
	//ファイルを閉じる
	fclose(pFile);
#endif

}

//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CManager::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//１行分読み込み
		fgets(&pDst[0], 256, pFile);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//　ファイル読み込み先頭を排除
//=============================================================================
char *CManager::GetLineTop(char * pStr)
{
	while (1)
	{
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//　文字数を返す
//=============================================================================
int CManager::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//頭出し
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//頭出し
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//文字列の数を返す
	return nWord;
}

//=============================================================================
// 入力の取得
//=============================================================================
CDirectInput *CManager::GetJoypad(void)
{
	return m_pJoyPad;
}

//=============================================================================
// ランキングスコアの取得(亘追加)
//=============================================================================
int CManager::GetRanking(int index)
{
	return m_aScore[index];
}
//=============================================================================
// ランキングスコアの取得(亘追加)
//=============================================================================
void CManager::GetRankingScore(int nScore)
{
	int nData = 0;

	if (m_aScore[MAX_RANKING - 1] <= nScore)
	{
		m_aScore[MAX_RANKING - 1] = nScore;
	}

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		for (int nNumber = 0; nNumber < MAX_RANKING - 1; nNumber++)
		{
			if (m_aScore[nNumber] < m_aScore[nNumber + 1])
			{
				nData = m_aScore[nNumber];
				m_aScore[nNumber] = m_aScore[nNumber + 1];
				m_aScore[nNumber + 1] = nData;
			}
		}
	}
}