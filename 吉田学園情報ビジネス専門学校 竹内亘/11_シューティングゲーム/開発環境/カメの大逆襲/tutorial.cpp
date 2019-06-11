//=============================================================================
//
// チュートリアル処理 [tutorial.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "logo.h"

#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "bullet.h"
#include "explosion.h"
#include "bg.h"
#include "enemy.h"
#include "number.h"
#include "score.h"
#include "life.h"
#include "remain.h"
#include "polygon.h"
#include "effect.h"
#include "particle.h"
#include "item.h"
#include "marineplant.h"
#include "pausemat.h"
#include "pauseselect.h"
#include "frame.h"
#include "image.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CScore * CTutorial::m_pScore = NULL;
CPlayer *CTutorial::m_pPlayer[2] = {};
CRemain *CTutorial::m_pRemain[2] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CTutorial::CTutorial()
{
	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;

	m_pRemain[0] = NULL;
	m_pRemain[1] = NULL;
}
//=============================================================================
// デストラクタ
//=============================================================================
CTutorial::~CTutorial()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
void CTutorial::Init(void)
{
	//// チュートリアルロゴの読み込み
	//CTutorialLogo::Load();

	// プレスエンターテクスチャ生成
	CPressEnter::Load();

	// 背景のテクスチャ読み込み
	CBg::Load();

	// プレイヤーのテクスチャ読み込み
	CPlayer::Load();

	// 弾のテクスチャ読み込み
	CBullet::Load();

	// 爆発のテクスチャ読み込み
	CExplosion::Load();

	//// 敵のテクスチャ読み込み
	//CEnemy::Load();

	// ナンバーテクスチャの読み込み
	CNumber::Load();

	// エフェクトテクスチャの読み込み
	CEffect::Load();

	// パーティクルテクスチャの読み込み
	CParticle::Load();

	// アイテムテクスチャの読み込み
	CItem::Load();

	// 海藻テクスチャの読み込み
	CMarinePlant::Load();

	// フレームの読み込み
	CFrame::Load();

	// 画像の読み込み
	CImage::Load();

	//// チュートリアルロゴの生成
	//CTutorialLogo::Create(D3DXVECTOR3(100, 100, 0.0f));

	// プレスエンタークラスの生成
	CPressEnter::Create(D3DXVECTOR3(1120, 700, 0.0f),CPressEnter::PRESSENTER_TUTORIAL);
	CPressEnter::DispPressEnter();

	// 背景クラスの生成
	CBg::Create2(D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f));

	// プレイヤーの生成
	for (int nCntPlayer = 0; nCntPlayer < 2; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] == NULL)
		{
			m_pPlayer[0] = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 100, SCREEN_HEIGHT / 2.0f + 200, 0.0f), CPlayer::PLAYERTYPE_000);
			m_pPlayer[1] = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100, SCREEN_HEIGHT / 2.0f + 200, 0.0f), CPlayer::PLAYERTYPE_001);
		}
		if (m_pRemain[nCntPlayer] == NULL)
		{// 残機の生成
			m_pRemain[0] = CRemain::Create(D3DXVECTOR3(200, 80, 0));
			m_pRemain[1] = CRemain::Create(D3DXVECTOR3(200, 160, 0));
		}
	}

	//// 敵の生成
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f - 500, 0.0f), CEnemy::ENEMYTYPE_TEST);
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f + 100, SCREEN_HEIGHT / 2.0f - 500, 0.0f), CEnemy::ENEMYTYPE_TEST);
	//CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f - 100, SCREEN_HEIGHT / 2.0f - 500, 0.0f), CEnemy::ENEMYTYPE_TEST);

	// スコアクラスの生成
	if (m_pScore == NULL)
	{
		m_pScore = CScore::Create(D3DXVECTOR3(1250, 80, 0));
	}

	// スコアフレームの生成
	CFrame::Create(D3DXVECTOR3(1120, 80, 0), CFrame::FRAME_SCORE);

	// 残機1画像の生成
	CImage::Create(D3DXVECTOR3(90, 65, 0), CImage::IMAGE_REMAIN000);

	// 残機2画像の生成
	CImage::Create(D3DXVECTOR3(90, 145, 0), CImage::IMAGE_REMAIN001);

	// コントローラーの説明
	CImage::Create(D3DXVECTOR3(1100, 550, 0), CImage::IMAGE_TUTORIAL);

	// PS説明
	CImage::Create(D3DXVECTOR3(1100, 400, 0), CImage::IMAGE_TUTORIAL002);

}
//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	// 全て解放
	CScene::ReleseAll();

	//// チュートリアルロゴの破棄
	//CTutorialLogo::Unload();

	// プレスエンターテクスチャ破棄
	CPressEnter::Unload();

	// 背景のテクスチャ破棄
	CBg::Unload();

	// プレイヤーのテクスチャ破棄
	CPlayer::Unload();

	// 弾のテクスチャ破棄
	CBullet::Unload();

	// 爆発のテクスチャ破棄
	CExplosion::Unload();

	//// 敵のテクスチャ破棄
	//CEnemy::Unload();

	// ナンバーのテクスチャ破棄
	CNumber::Unload();

	// エフェクトのテクスチャの破棄
	CEffect::Unload();

	// パーティクルのテクスチャの破棄
	CParticle::Unload();

	// アイテムのテクスチャの破棄
	CItem::Unload();

	// 海藻のテクスチャの破棄
	CMarinePlant::Unload();

	// 画像のテクスチャの破棄
	CImage::Unload();

	m_pPlayer[0] = NULL;
	m_pPlayer[1] = NULL;

	m_pRemain[0] = NULL;
	m_pRemain[1] = NULL;

	m_pScore = NULL;
}
//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
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

	if (pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 0) == true || pXInputJoyPad->GetPress(XINPUT_GAMEPAD_START, 1) == true ||
		pInputKeyboard->GetTrigger(DIK_1) == true)
	{// 何か押されたら
		pFade->Set(CManager::MODE_GAME, pFade->FADE_OUT);

		pSound->PlaySound(CSound::SOUND_LABEL_SE_EXPLOSION);
	}

	//if (pInputJoyPad->GetTrigger(CInputJoyPad::DIJS_BUTTON_4))
	//{// ジョイパッド
	//	pFade->Set(CManager::MODE_GAME, pFade->FADE_OUT);
	//}

	///*デバッグ用*/
	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	//{
	//	CManager::SetMode(CManager::MODE_TITLE);
	//}
}
//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}
