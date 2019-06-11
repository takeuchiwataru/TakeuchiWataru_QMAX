//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "title.h"

#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "bg.h"
#include "logo.h"
#include "sound.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CTitle::CTitle()
{
	m_nTime = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTitle::Init(void)
{
	m_nTime = 0;

	// 背景のテクスチャ読み込み
	CBg::Load();

	// 背景クラスの生成
	CBg::Create(D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f));

	// タイトルロゴの読み込み
	CTitleLogo::Load();

	// タイトルロゴクラスの生成
	CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));

	// プレスエンターテクスチャ生成
	CPressEnter::Load();

	// プレスエンタークラスの生成
	CPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200, 0.0f),CPressEnter::PRESSENTER_TITLE);
	CPressEnter::DispPressEnter();

	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	// 全て解放
	CScene::ReleseAll();

	// 背景のテクスチャ破棄
	CBg::Unload();

	// タイトルロゴテクスチャ破棄
	CTitleLogo::Unload();

	// プレスエンターテクスチャ破棄
	CPressEnter::Unload();
}
//=============================================================================
// 更新処理
//=============================================================================
void CTitle::Update(void)
{
	m_nTime++;

	// キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();

	// ジョイパッドの取得
	CInputJoyPad *pInputJoyPad = CManager::GetJoyPad();

	// ジョイパッド(XInput)の取得
	CXInputJoyPad *pXInputJoyPad = CManager::GetXInputJoyPad();

	// サウンドの取得
	CSound * pSound = CManager::GetSound();

	// フェードの取得
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_A, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_B, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_X, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_Y, 1) == true ||
		pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 1) == true)

	{// // 何か押されたら
		pFade->Set(CManager::MODE_TUTORIAL,pFade->FADE_OUT);

		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
	}

	if (m_nTime % 300 == 0)
	{// 一定時間たったら
		pFade->Set(CManager::MODE_RANKING, pFade->FADE_OUT);
	}

	///*デバッグ用*/
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::SetMode(CManager::MODE_GAME);
	//}
}
//=============================================================================
// 描画処理
//=============================================================================
void CTitle::Draw(void)
{

}
