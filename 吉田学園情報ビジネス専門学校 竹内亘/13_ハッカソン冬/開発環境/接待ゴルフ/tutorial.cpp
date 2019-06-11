//---------------------------------------------------------------------
// チュートリアル処理 [result.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "tutorial.h"
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "Logo.h"

//#include "bg.h"
#include "fade.h"
#include "tutorialbg.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TUTORIALBG000_TEXTURENAME	"data/TEXTURE/TUTORIAL/tutorial000.png"	//テクスチャのファイル名
#define TUTORIALBG001_TEXTURENAME	"data/TEXTURE/TUTORIAL/tutorial001.png"	//テクスチャのファイル名
#define TUTORIALBG002_TEXTURENAME	"data/TEXTURE/TUTORIAL/tutorial002.png"	//テクスチャのファイル名

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9 CTutorial::m_pTexture[MAX_TUTORIALBG] = {};

//--------------------------------------------
//チュートリアルクラス コンストラクタ
//--------------------------------------------
CTutorial::CTutorial()
{
	m_nType = 0;
}

//--------------------------------------------
//チュートリアルクラス デストラクタ
//--------------------------------------------
CTutorial::~CTutorial()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CTutorial *CTutorial::Create(void)
{
	//チュートリアルのポインタ
	CTutorial *pTutorial;
	pTutorial = new CTutorial;
	//チュートリアルの初期化
	//pTutorial->Load();
	pTutorial->Init();
	//チュートリアルの情報を返す
	return pTutorial;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//テクスチャやモデルの読み込み
	CLogo::Load();
	CTutorialBG::Load();

	//オブジェクトの生成
	CTutorialBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 1000, 300);

	//オブジェクトの生成
	CLogo::Create(D3DXVECTOR3(250, 100, 0), 350, 150);

	//CSceneMeshField::Create(D3DXVECTOR3(-500, 10, 0),300.0f,300.0f,10,10);

	return S_OK;
}

//=============================================================================
// チュートリアルクラス 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	//テクスチャやモデルの破棄
	CLogo::UnLoad();

	CTutorialBG::UnLoad();
	CScene::ReleaseAll();
}

//=============================================================================
// チュートリアルクラス 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//コントローラー情報を取得
	CDirectInput *pInputJoypad = CManager::GetJoypad();
	//サウンド情報を取得
	CSound *pSound = CManager::GetSound();
	//シーン2Dを取得
	//CScene2D *Scene2D;
	//Scene2D = pBg->GetScene2DBG(0);


	//切り替え処理

		if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
			|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
			CFade::SetFade(CManager::MODE_GAME);
		}

		CDebugProc::Print(1, " チュートリアル\n");
}

//=============================================================================
// チュートリアルクラス 描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}
//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CTutorial::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		TUTORIALBG000_TEXTURENAME,
		&m_pTexture[0]);

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		TUTORIALBG001_TEXTURENAME,
		&m_pTexture[1]);

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice,
		TUTORIALBG002_TEXTURENAME,
		&m_pTexture[2]);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄処理
//=============================================================================
void CTutorial::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TUTORIALBG; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}