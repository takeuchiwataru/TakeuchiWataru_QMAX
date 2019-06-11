//=============================================================================
//
// 影の処理 [polygon.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			"data\\TEXTURE\\EFFECT\\particle000.jpg"	//テクスチャのファイル名
#define TEXTURENAME001			"data\\TEXTURE\\EFFECT\\shadow000.jpg"		//テクスチャのファイル名
#define TEX_POS_X_INIT			(1.0f)		//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)		//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)		//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)		//テクスチャ座標U右
#define TEX_TOP					(0.0f)		//テクスチャ座標V上
#define TEX_BOT					(1.0f)		//テクスチャ座標V下

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CShadow::m_pTexture[SHADOWTYPE_MAX] = {};

//--------------------------------------------
//シーン3Dクラス コンストラクタ
//--------------------------------------------
CShadow::CShadow()
{
	m_pos = D3DXVECTOR3(0,0,0);			//位置
	m_rot = D3DXVECTOR3(0, 0, 0);		//向き
	D3DXMatrixIdentity(&m_mtxWorld);	//ワールドマトリックス
	m_Type = SHADOWTYPE_NORMAL;
}

//--------------------------------------------
//シーン3Dクラス デストラクタ
//--------------------------------------------
CShadow::~CShadow()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CShadow * CShadow::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, D3DXCOLOR col, CShadow::SHADOWTYPE type)
{
	CShadow *pShadow;

	pShadow = new CShadow;

	pShadow->m_pos = pos;
	pShadow->m_fWidth = fWidth;
	pShadow->m_fDepth = fDepth;
	pShadow->m_col = col;
	pShadow->m_Type = type;
	pShadow->Init();

	return pShadow;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShadow::Init(void)
{
	m_pScene3D = CScene3D::Create(m_pos, m_col, m_fWidth, m_fDepth);

	m_pScene3D->BindTexture(m_pTexture[m_Type]);
	//オブジェクト種類の設定
	m_pScene3D->SetObjType(CScene::OBJTYPE_SHADOW);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CShadow::Uninit(void)
{
	if (m_pScene3D != NULL)
	{
		m_pScene3D->Uninit();
		m_pScene3D = NULL;
	}
	//自分を消す(シーン3Dを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CShadow::Update(void)
{
	if (m_pScene3D != NULL)
	{
		m_pScene3D->Setpos(m_pos);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CShadow::Draw(void)
{

}

//=============================================================================
// 位置設定処理
//=============================================================================
void CShadow::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CShadow::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	for (int nCnt = 0; nCnt < SHADOWTYPE_MAX; nCnt++)
	{	// テクスチャの破棄
		m_pTexture[nCnt] = NULL;
	}

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CShadow::UnLoad(void)
{
	for (int nCnt = 0; nCnt < SHADOWTYPE_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
