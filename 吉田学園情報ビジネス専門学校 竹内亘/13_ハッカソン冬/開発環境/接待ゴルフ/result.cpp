//---------------------------------------------------------------------
// リザルト処理 [result.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "result.h"
#include "manager.h"
#include "scene.h"
#include "Logo.h"

//#include "bg.h"
#include "fade.h"
//#include "resultlogo.h"
//--------------------------------------------
//リザルトクラス コンストラクタ
//--------------------------------------------
CResult::CResult()
{
	m_nCntTimer = 0;
}

//--------------------------------------------
//リザルトクラス デストラクタ
//--------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CResult *CResult::Create(void)
{
	//リザルトのポインタ
	CResult *pResult;
	pResult = new CResult;
	//リザルトの初期化
	pResult->Init();
	//リザルトの情報を返す
	return pResult;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	//テクスチャやモデルの読み込み
	CLogo::Load();

	//オブジェクトの生成
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200, 0), 400, 200);

	//プレスエンターの生成
	//CPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650, 0), 150);

	return S_OK;
}

//=============================================================================
// リザルトクラス 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	//テクスチャやモデルの破棄
	CLogo::UnLoad();

	CScene::ReleaseAll();
}

//=============================================================================
// リザルトクラス 更新処理
//=============================================================================
void CResult::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//コントローラー情報を取得
	CDirectInput *pInputJoypad = CManager::GetJoypad();

	//サウンド情報を取得
	CSound *pSound = CManager::GetSound();
	//切り替え処理
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_RANKING);
	}

	//切り替え処理(タイマー)
	m_nCntTimer++;
	if (m_nCntTimer >= 420 && CFade::GetFade() == CFade::FADE_NONE)
	{
		CFade::SetFade(CManager::MODE_RANKING);
		m_nCntTimer = 0;
	}

	CDebugProc::Print(1, "	リザルト\n");

}

//=============================================================================
// リザルトクラス 描画処理
//=============================================================================
void CResult::Draw(void)
{

}