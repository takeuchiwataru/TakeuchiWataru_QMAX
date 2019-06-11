//---------------------------------------------------------------------
// タイトル処理 [title.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "title.h"
#include "manager.h"
#include "scene.h"
//#include "bg.h"
#include "fade.h"
#include "Logo.h"
#include "input.h"
#include "titlebg.h"
#include "press.h"

//--------------------------------------------
//タイトルクラス コンストラクタ
//--------------------------------------------
CTitle::CTitle()
{
	m_nCntTimer = 0;
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
	//テクスチャやモデルの読み込み
	CLogo::Load();
	CTitleBG::Load();
	CPress::Load();

	//オブジェクトの生成
	CTitleBG::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 1280, 720);

	//オブジェクトの生成
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 300, 0), 500, 300);

	//オブジェクトの生成
	CPress::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 600, 0), 350, 150);

	return S_OK;
}

//=============================================================================
// タイトルクラス 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	//タイトルロゴテクスチャの破棄
	CLogo::UnLoad();

	CTitleBG::UnLoad();

	CScene::ReleaseAll();
}

//=============================================================================
// タイトルクラス 更新処理
//=============================================================================
void CTitle::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	CDirectInput *pInputJoypad = CManager::GetJoypad();

	//サウンド情報を取得
	CSound *pSound = CManager::GetSound();

	//切り替え処理
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_TUTORIAL);
	}

	if (m_nCntTimer >= 300 && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_RANKING);
		m_nCntTimer = 0;
	}


	CDebugProc::Print(1, " タイトル\n");
}

//=============================================================================
// タイトルクラス 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}