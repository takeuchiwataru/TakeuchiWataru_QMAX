//---------------------------------------------------------------------
// ゲームオーバー処理 [result.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "gameover.h"
#include "manager.h"
#include "scene.h"
#include "fade.h"
//--------------------------------------------
//ゲームオーバークラス コンストラクタ
//--------------------------------------------
CGameover::CGameover()
{
	m_nCntTimer = 0;
}

//--------------------------------------------
//ゲームオーバークラス デストラクタ
//--------------------------------------------
CGameover::~CGameover()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CGameover *CGameover::Create(void)
{
	//ゲームオーバーのポインタ
	CGameover *pGameover;
	pGameover = new CGameover;
	//ゲームオーバーの初期化
	pGameover->Init();
	//ゲームオーバーの情報を返す
	return pGameover;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CGameover::Init(void)
{
	return S_OK;
}

//=============================================================================
// ゲームオーバークラス 終了処理
//=============================================================================
void CGameover::Uninit(void)
{
	CScene::ReleaseAll();
}

//=============================================================================
// ゲームオーバークラス 更新処理
//=============================================================================
void CGameover::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//コントローラー情報を取得
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//サウンド情報を取得
	CSound *pSound = CManager::GetSound(0);

	//切り替え処理
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_RANKING);
	}

	//切り替え処理(タイマー)
	m_nCntTimer++;
	if (m_nCntTimer >= 600 && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_RANKING);
		m_nCntTimer = 0;
	}
}

//=============================================================================
// ゲームオーバークラス 描画処理
//=============================================================================
void CGameover::Draw(void)
{

}