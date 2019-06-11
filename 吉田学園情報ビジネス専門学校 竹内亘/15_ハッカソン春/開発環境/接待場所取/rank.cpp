//=============================================================================
//
// ロゴ処理 [Rank.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "Rank.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\LOGO\\rank000.png"			//テクスチャのファイル名
#define TEXTURENAME001			 "data\\TEXTURE\\LOGO\\rank001.png"			//テクスチャのファイル名
#define TEXTURENAME002			 "data\\TEXTURE\\LOGO\\rank002.png"			//テクスチャのファイル名
#define TEXTURENAME003			 "data\\TEXTURE\\LOGO\\rank003.png"			//テクスチャのファイル名
#define TEXTURENAME004			 "data\\TEXTURE\\LOGO\\rank004.png"			//テクスチャのファイル名

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CRank::m_pTexture[MAX_RANKTEX] = {};

//--------------------------------------------
//ロゴクラス コンストラクタ
//--------------------------------------------
CRank::CRank()
{
	m_pos = D3DXVECTOR3(0,0,0);						// 位置
	m_move = D3DXVECTOR3(0, 0, 0);					// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);					// 前回の位置
}

//--------------------------------------------
//ロゴクラス デストラクタ
//--------------------------------------------
CRank::~CRank()
{
}

//--------------------------------------------
//ロゴの生成
//--------------------------------------------
CRank *CRank::Create(D3DXVECTOR3 pos,float fWidth, float fHeight, int nType)
{
	CRank *pScene2D;

	pScene2D = new CRank;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->m_nType = nType;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRank::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//生成
	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	m_pScene2D[0]->BindTexture(m_pTexture[m_nType]);
	CManager::MODE pMode = CManager::GetMode();
	//オブジェクト種類の設定
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRank::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_2DRANK; nCnt++)
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
void CRank::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CRank::Draw(void)
{

}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CRank::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME002, &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME003, &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME004, &m_pTexture[4]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CRank::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_RANKTEX; nCnt++)
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
void CRank::SetColor(D3DXCOLOR col)
{
	m_pScene2D[0]->SetColor(col);
}
