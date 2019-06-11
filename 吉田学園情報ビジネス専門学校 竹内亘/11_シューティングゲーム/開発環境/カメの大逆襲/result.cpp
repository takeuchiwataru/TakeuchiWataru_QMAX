//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "result.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "logo.h"
#include "bg.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{

}
//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
void CResult::Init(void)
{
	// リザルトロゴの読み込み
	CResultLogo::Load();

	// 背景のテクスチャ読み込み
	CBg::Load();

	// リザルトロゴクラスの生成
	CResultLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), CResultLogo::RESULTTYPE_OVER);

	// 背景クラスの生成
	CBg::Create(D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f));

}
//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	// 全て解放
	CScene::ReleseAll();

	// リザルトロゴの破棄
	CResultLogo::Unload();

	// 背景のテクスチャ破棄
	CBg::Unload();
}
//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// ジョイパッド(XInput)の取得
	CXInputJoyPad *pXInputJoyPad = CManager::GetXInputJoyPad();

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 1) == true && pFade->FADE_NONE)
	{// 何か押されたら
		pFade->Set(CManager::MODE_RANKING, pFade->FADE_OUT);
	}

	///*デバッグ用*/
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::SetMode(CManager::MODE_TITLE);
	//}
}
//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{

}
