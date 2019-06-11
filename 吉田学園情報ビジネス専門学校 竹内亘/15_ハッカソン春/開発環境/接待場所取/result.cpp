//---------------------------------------------------------------------
// リザルト処理 [result.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "result.h"
#include "manager.h"
#include "scene.h"
#include "Logo.h"

#include "fade.h"
#include "number.h"
#include "scene2D.h"
#include "game.h"
#include "objectBG.h"
#include "UIPressEnter.h"
#include "enemy.h"
#include "meshCylinder.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\UI\\ITEMLOGO.png"		//テクスチャのファイル名
#define TEXTURENAME001			 "data\\TEXTURE\\UI\\LIMITLOGO.png"		//テクスチャのファイル名


//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
CScore *CResult::m_pScore[1] = {};
D3DXVECTOR3 CResult::m_bluePos = D3DXVECTOR3(0, 0, 0);

//--------------------------------------------
//リザルトクラス コンストラクタ
//--------------------------------------------
CResult::CResult()
{
	m_nCntTimer = 0;
	m_nSoundCnt = 0;

	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		m_apTime[nCnt] = NULL;
		m_apItem[nCnt] = NULL;
	}
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
	//カメラ ライトの初期化
	CManager::GetCamera()->Init();
	CManager::GetLight()->Init();

	//テクスチャやモデルの読み込み
	CObjectBG::Load();
	CUIPressEnter::Load();

	CEnemy::Load();

	//メッシュフィールド生成
	CSceneMeshField::Create(D3DXVECTOR3(-1000, 0, 2900), 7000.0f,3000.0f, 50, 10);
	//空の生成
	CSceneMeshCylinder::Create(D3DXVECTOR3(0, 18000, 0), 8000.0f, 28000.0f, 10, 1, CSceneMeshCylinder::CYLINDERTYPE_INWARD);

	int nNumEnemy = LoadNumEnemy();

	m_bluePos = D3DXVECTOR3((3000.0f / 100) * (nNumEnemy), 1, 200);

	CObjectBG::Create(m_bluePos, D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL000, CObjectBG::MOVETYPE_NONE, 0);

	if (nNumEnemy > 0)
	{
		for (int nCntEnemy = 0; nCntEnemy < (int)(nNumEnemy / 2); nCntEnemy++)
		{
			CEnemy::Create(D3DXVECTOR3(-20.0f + (nCntEnemy * 63.0f), 10, 100.0f + (rand() % 30)), D3DXVECTOR3(D3DX_PI * -0.5f, D3DX_PI * 0.0f, (rand() % 628) / 100.0f), 10);
		}
	}

	// 桜の木
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(-100.0f + (nCnt * 300.0f), 0, 400.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL003, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(0.0f + (nCnt * 300.0f), 0, 300.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL003, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(100.0f + (nCnt * 300.0f), 0, 350.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL003, CObjectBG::MOVETYPE_NONE, 0);
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(1200.0f + (nCnt * 300.0f), 0, 400.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL002, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(1300.0f + (nCnt * 300.0f), 0, 300.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL002, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(1400.0f + (nCnt * 300.0f), 0, 350.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL002, CObjectBG::MOVETYPE_NONE, 0);
	}

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		CObjectBG::Create(D3DXVECTOR3(2400.0f + (nCnt * 300.0f), 0, 400.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL001, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(2500.0f + (nCnt * 300.0f), 0, 300.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL001, CObjectBG::MOVETYPE_NONE, 0);
		CObjectBG::Create(D3DXVECTOR3(2600.0f + (nCnt * 300.0f), 0, 350.0f), D3DXVECTOR3(0, 0, 0), CObjectBG::MODELTYPE_BILL001, CObjectBG::MOVETYPE_NONE, 0);
	}

	// プレスエンター
	CUIPressEnter::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30, SCREEN_HEIGHT / 2 + 250, 0.0f), 400, 100);

	return S_OK;
}

//=============================================================================
// リザルトクラス 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	CObjectBG::UnLoad();
	CUIPressEnter::UnLoad();
	CEnemy::UnLoad();

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
	CInputJoypad *pInputJoypad = CManager::GetCInputJoypad();
	//サウンド情報を取得
	//CSound *pSound = CManager::GetSound();
	CSound *pSound = CManager::GetSound(0);

	//切り替え処理
	if (pInput->GetTrigger(DIK_RETURN) == true && CFade::GetFade() == CFade::FADE_NONE
		|| pInputJoypad->GetAnyButton(0) == true && CFade::GetFade() == CFade::FADE_NONE)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_TITLE);
	}

#ifdef  _DEBUG
	//切り替え処理
	if (pInput->GetTrigger(DIK_BACK) == true && CFade::GetFade() == CFade::FADE_NONE
		/*	|| pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A) == true && CFade::GetFade() == CFade::FADE_NONE*/)
	{
		pSound->PlaySound(pSound->SOUND_LABEL_SE_DECIDE);
		CFade::SetFade(CManager::MODE_GAME);
	}
#endif


	CDebugProc::Print(1, "	リザルト\n");

}

//=============================================================================
// リザルトクラス 描画処理
//=============================================================================
void CResult::Draw(void)
{

}

//=============================================================================
// ブルーシートの位置取得
//=============================================================================
D3DXVECTOR3 CResult::GetBluePos(void)
{
	return m_bluePos;
}

//=============================================================================
// 倒した敵の数のロード
//=============================================================================
int CResult::LoadNumEnemy(void)
{
	FILE *pFile = NULL;

	int nNumEnemy = 0;

	pFile = fopen(NUMENEMY_FILE, "r");

	if (pFile != NULL)
	{
		fscanf(pFile, "%d", &nNumEnemy);

		fclose(pFile);
	}

	return nNumEnemy;
}

//=============================================================================
// アイテム獲得数用の数字設定処理
//=============================================================================
void CResult::AddItem(int nValue)
{
	int nAnswer = 0;
	int nDigit = 1;
	//タイム加算
	m_nItem = nValue;

	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		//桁数の計算
		nAnswer = m_nItem % (nDigit * 10) / nDigit;
		//その桁の数字をセット
		if (m_apItem[nCnt] != NULL)
		{
			m_apItem[nCnt]->SetNumber(nAnswer);
		}
		//次の桁へ
		nDigit *= 10;
	}
}

//=============================================================================
// タイム表示用の数字設定処理
//=============================================================================
void CResult::AddTime(int nValue)
{
	int nAnswer = 0;
	int nDigit = 1;
	//タイム加算
	m_nTime = nValue;

	for (int nCnt = 0; nCnt < MAX_NUM; nCnt++)
	{
		//桁数の計算
		nAnswer = m_nTime % (nDigit * 10) / nDigit;
		//その桁の数字をセット
		if (m_apTime[nCnt] != NULL)
		{
			m_apTime[nCnt]->SetNumber(nAnswer);
		}
		//次の桁へ
		nDigit *= 10;
	}
}


