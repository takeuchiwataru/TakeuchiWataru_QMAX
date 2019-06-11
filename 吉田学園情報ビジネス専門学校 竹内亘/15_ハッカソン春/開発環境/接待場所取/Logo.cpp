//=============================================================================
//
// ロゴ処理 [Logo.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "Logo.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\LOGO\\title.png"			//テクスチャのファイル名
#define TEXTURENAME001			 "data\\TEXTURE\\LOGO\\Tutorial000.png"			//テクスチャのファイル名
#define TEXTURENAME002			 "data\\TEXTURE\\LOGO\\Result000.png"			//テクスチャのファイル名
#define TEXTURENAME003			 "data\\TEXTURE\\LOGO\\Ranking001.png"			//テクスチャのファイル名

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CLogo::m_pTexture[MAX_LOGOTEX] = {};

//--------------------------------------------
//ロゴクラス コンストラクタ
//--------------------------------------------
CLogo::CLogo()
{
	m_pos = D3DXVECTOR3(0,0,0);						// 位置
	m_move = D3DXVECTOR3(0, 0, 0);					// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);				// 前回の位置
}

//--------------------------------------------
//ロゴクラス デストラクタ
//--------------------------------------------
CLogo::~CLogo()
{
}

//--------------------------------------------
//ロゴの生成
//--------------------------------------------
CLogo *CLogo::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CLogo *pScene2D;

	pScene2D = new CLogo;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLogo::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_fWidth, m_fHeight);


	CManager::MODE pMode = CManager::GetMode();

	switch (pMode)
	{
	case CManager::MODE_TITLE:
		//タイトル
		m_pScene2D[0]->BindTexture(m_pTexture[0]);
		break;
	case CManager::MODE_TUTORIAL:
		//チュートリアル
		m_pScene2D[0]->BindTexture(m_pTexture[1]);
		break;
	case CManager::MODE_RESULT:
		//リザルト
		m_pScene2D[0]->BindTexture(m_pTexture[2]);
		break;
	case CManager::MODE_GAMEOVER:
		//ゲームオーバー
		break;
	case CManager::MODE_RANKING:
		//ランキング
		m_pScene2D[0]->BindTexture(m_pTexture[3]);
		break;
	}

	//オブジェクト種類の設定
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLogo::Uninit(void)
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
void CLogo::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CLogo::Draw(void)
{

}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CLogo::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME002, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME003, &m_pTexture[3]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CLogo::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_LOGOTEX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 色の設定
//=============================================================================
void CLogo::SetColor(D3DXCOLOR col)
{
	m_pScene2D[0]->SetColor(col);
}
