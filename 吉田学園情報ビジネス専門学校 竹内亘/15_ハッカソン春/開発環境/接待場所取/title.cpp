//---------------------------------------------------------------------
// タイトル処理 [title.cpp]
// Author : 竹内亘
//---------------------------------------------------------------------
#include "title.h"
#include "manager.h"
#include "scene.h"

#include "fade.h"
#include "Logo.h"
#include "meshField.h"
#include "field.h"
#include "meshOrbit.h"
#include "meshCylinder.h"
#include "billboard.h"
#include "billboardObject.h"
#include "player.h"
#include "shadow.h"
#include "effect.h"
#include "UIPressEnter.h"
#include "titleobject.h"
#include "explosion.h"

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
CPlayer		*CTitle::m_pPlayer = NULL;

//--------------------------------------------
//タイトルクラス コンストラクタ
//--------------------------------------------
CTitle::CTitle()
{
	m_nCntTimer = 0;
	m_pPlayer = NULL;
}

//--------------------------------------------
//タイトルクラス デストラクタ
//--------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CTitle *CTitle::Create(void)
{
	//タイトルのポインタ
	CTitle *pTitle;
	pTitle = new CTitle;
	//タイトルの初期化
	pTitle->Init();

	//タイトルの情報を返す
	return pTitle;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	//カメラ ライトの初期化
	CManager::GetCamera()->Init();
	CManager::GetLight()->Init();

	//テクスチャやモデルの読み込み
	CLogo::Load();
	CField::Load();
	CBillBoardObject::Load();
	CShadow::Load();
	CEffect::Load();
	CUIPressEnter::Load();
	
	// タイトルオブジェクトの読み込み
	CTitleObject::LoadModel();
	CTitleObject::LoadMat();

	// 桜ひらひらの読み込み
	CExplosion::Load();

	//空の生成
	CSceneMeshCylinder::Create(D3DXVECTOR3(0, 18000, 0), 8000.0f, 28000.0f, 10, 1, CSceneMeshCylinder::CYLINDERTYPE_INWARD);

	CField::Create(D3DXVECTOR3(-500, 0.1f, 3000), 1000, 5000, CField::FIELDTEX_GARDEN,10, 300);
	//CBillBoardObject::Create(D3DXVECTOR3(0, 10, -2520), D3DXVECTOR3(0, 0, 0), 200, 200, CBillBoardObject::TEXTYPE_TITLE);

	// タイトルオブジェクトの生成
	CTitleObject::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// 桜ひらひら
	CExplosion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));

	// プレスエンター
	CUIPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 + 250, 0.0f),400,100);

	// タイトルロゴ
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 - 200, 0.0f), 600, 350);

	m_nCntTimer = 0;

	return S_OK;
}

//=============================================================================
// タイトルクラス 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	//タイトルロゴテクスチャの破棄
	CLogo::UnLoad();
	CField::UnLoad();
	CBillBoardObject::UnLoad();
	CShadow::UnLoad();
	CEffect::UnLoad();
	CUIPressEnter::UnLoad();

	// タイトルオブジェクトの破棄
	CTitleObject::UnloadModel(); 
	CTitleObject::UnloadMat();

	// 桜ひらひらの破棄
	CExplosion::Unload();

	if (m_pPlayer != NULL)
	{
		//m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	CScene::ReleaseAll();
}
//=============================================================================
// タイトルクラス 更新処理
//=============================================================================
void CTitle::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//サウンド情報を取得
	CSound *pSound = CManager::GetSound(0);


	//CFade::SetFade(CManager::MODE_TITLE);


	//切り替え処理
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_TUTORIAL);
	}

	if (pInput->GetTrigger(DIK_R) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_TITLE);
	}

#ifdef  _DEBUG
	//切り替え処理
	if (pInput->GetTrigger(DIK_BACKSPACE) == true && CFade::GetFade() == CFade::FADE_NONE)
	{

		CFade::SetFade(CManager::MODE_RANKING);
	}
	if (pInput->GetTrigger(DIK_G) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_GAME);
	}
#endif

	CDebugProc::Print(1, " タイトル\n");
}

//=============================================================================
// タイトルクラス 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}

//=============================================================================
// タイトルクラス プレイヤーを取得
//=============================================================================
CPlayer *CTitle::GetPlayer(void)
{
	return m_pPlayer;
}