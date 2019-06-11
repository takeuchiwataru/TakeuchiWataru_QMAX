//=============================================================================
//
// プレスエンター処理 [press.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "press.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PRESS_TEX			 "data\\TEXTURE\\press_enter.png"			//テクスチャのファイル名

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CPress::m_pTexture[MAX_TEX] = {};

//--------------------------------------------
//ロゴクラス コンストラクタ
//--------------------------------------------
CPress::CPress()
{
	m_pos = D3DXVECTOR3(0, 0, 0);						// 位置
	m_move = D3DXVECTOR3(0, 0, 0);					// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);					// 前回の位置
}

//--------------------------------------------
//ロゴクラス デストラクタ
//--------------------------------------------
CPress::~CPress()
{
}

//--------------------------------------------
//ロゴの生成
//--------------------------------------------
CPress *CPress::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CPress *pScene2D;

	pScene2D = new CPress;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPress::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	m_pScene2D[0]->BindTexture(m_pTexture[0]);

	//CManager::MODE pMode = CManager::GetMode();

	//switch (pMode)
	//{
	//case CManager::MODE_TITLE:
	//	//タイトル
	//	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//	break;
	//case CManager::MODE_TUTORIAL:
	//	//チュートリアル
	//	m_pScene2D[0]->BindTexture(m_pTexture[1]);
	//	break;
	//case CManager::MODE_RESULT:
	//	//リザルト
	//	m_pScene2D[0]->BindTexture(m_pTexture[2]);
	//	break;
	//case CManager::MODE_GAMEOVER:
	//	//ゲームオーバー
	//	break;
	//case CManager::MODE_RANKING:
	//	//ランキング
	//	m_pScene2D[0]->BindTexture(m_pTexture[3]);
	//	break;
	//}

	//オブジェクト種類の設定
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPress::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_2DLOGO; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}
	//自分を消す(プレイヤーを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPress::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CPress::Draw(void)
{
	D3DXVECTOR3 pos;

	m_nTime++;

	if (m_nTime % 90 == 0)
	{
		m_nTime = 0;
	}

	if (m_nTime < 40)
	{
		m_fColor = 1.0f;
	}
	else
	{
		m_fColor = 0.0f;
	}
	//プレスエンターの画像
	m_pScene2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColor));

}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CPress::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, PRESS_TEX, &m_pTexture[0]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CPress::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
