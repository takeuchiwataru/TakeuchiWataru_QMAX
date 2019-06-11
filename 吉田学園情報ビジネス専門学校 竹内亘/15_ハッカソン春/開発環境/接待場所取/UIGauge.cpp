//=============================================================================
//
// UIゲージ処理 [UIGauge.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "UIGauge.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			 "data\\TEXTURE\\PAUSE\\soda000.jpg"			//テクスチャのファイル名
#define TEXTURENAME001			 "data\\TEXTURE\\UI\\CANUI.png"			//テクスチャのファイル名
#define TEXTURENAME002			 "data\\TEXTURE\\UI\\GAUSELOGO.png"			//テクスチャのファイル名

#define MAX_GAUGECAPA			(400)
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9			CUIGauge::m_pTexture[MAX_GAUGE] = {};
float						CUIGauge::m_fVtxHeight = 0;
CUIGauge::GAUGESTATE		CUIGauge::m_State;

//--------------------------------------------
//UIゲージクラス コンストラクタ
//--------------------------------------------
CUIGauge::CUIGauge()
{
	m_pos = D3DXVECTOR3(0,0,0);						// 位置
	m_move = D3DXVECTOR3(0, 0, 0);					// 移動量
	m_posold = D3DXVECTOR3(0, 0, 0);					// 前回の位置
}

//--------------------------------------------
//UIゲージクラス デストラクタ
//--------------------------------------------
CUIGauge::~CUIGauge()
{
}

//--------------------------------------------
//UIゲージの生成
//--------------------------------------------
CUIGauge *CUIGauge::Create(D3DXVECTOR3 pos,float fWidth, float fHeight)
{
	CUIGauge *pScene2D;

	pScene2D = new CUIGauge;

	pScene2D->m_pos = pos;
	pScene2D->m_fHeight = fHeight;
	pScene2D->m_fWidth = fWidth;
	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CUIGauge::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//2Dポリゴン生成
	m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), m_fWidth, m_fHeight);
	//テクスチャを設定
	m_pScene2D[0]->BindTexture(m_pTexture[0]);
	//オブジェクト種類の設定
	m_pScene2D[0]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//2Dポリゴン生成
	m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y -190, m_pos.z), m_fWidth, m_fHeight + 10);
	//テクスチャを設定
	m_pScene2D[1]->BindTexture(m_pTexture[1]);
	//オブジェクト種類の設定
	m_pScene2D[1]->SetObjType(CScene::OBJTYPE_SCENE2D);

	//2Dポリゴン生成
	m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 450, m_pos.z),160, 80);
	//テクスチャを設定
	m_pScene2D[2]->BindTexture(m_pTexture[2]);
	m_pScene2D[2]->SetColor(D3DXCOLOR(1.0f, 0.3f, 0.3f, 0.9f));
	//オブジェクト種類の設定
	m_pScene2D[2]->SetObjType(CScene::OBJTYPE_SCENE2D);

	m_fVtxHeight = 0;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファを取得
	m_pVtxBuff = m_pScene2D[0]->GetVtx();
	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点位置
	pVtx[0].pos = D3DXVECTOR3(pVtx[0].pos.x, m_pos.y + m_fVtxHeight, pVtx[0].pos.z);
	pVtx[1].pos = D3DXVECTOR3(pVtx[1].pos.x, m_pos.y + m_fVtxHeight, pVtx[1].pos.z);
	pVtx[2].pos = D3DXVECTOR3(pVtx[2].pos.x, m_pos.y, pVtx[2].pos.z);
	pVtx[3].pos = D3DXVECTOR3(pVtx[3].pos.x, m_pos.y, pVtx[3].pos.z);
	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CUIGauge::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_GAUGE; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}
	//自分を消す
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CUIGauge::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

#ifdef  _DEBUG
	if (pInput->GetTrigger(DIK_I) == true)
	{
		m_fVtxHeight += 50;
	}
	if (pInput->GetTrigger(DIK_O) == true)
	{
		m_fVtxHeight -= 50;
	}
#endif
	//ゲージが超えないように
	if (m_fVtxHeight < -MAX_GAUGECAPA)
	{
		m_fVtxHeight = -MAX_GAUGECAPA;
	}
	else if (m_fVtxHeight > 0)
	{
		m_fVtxHeight = 0;
	}

	//状態の変化
	if (m_fVtxHeight == -MAX_GAUGECAPA)
	{
		m_State = GAUGESTATE_MAXGAUGE;
	}
	else if (m_fVtxHeight == 0)
	{
		m_State = GAUGESTATE_NORMAL;
	}

	//m_fVtxHeight = 0;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファを取得
	m_pVtxBuff = m_pScene2D[0]->GetVtx();
	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点位置
	pVtx[0].pos = D3DXVECTOR3(pVtx[0].pos.x, m_pos.y + m_fVtxHeight, pVtx[0].pos.z);
	pVtx[1].pos = D3DXVECTOR3(pVtx[1].pos.x, m_pos.y + m_fVtxHeight, pVtx[1].pos.z);
	pVtx[2].pos = D3DXVECTOR3(pVtx[2].pos.x, m_pos.y, pVtx[2].pos.z);
	pVtx[3].pos = D3DXVECTOR3(pVtx[3].pos.x, m_pos.y, pVtx[3].pos.z);
	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f);
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void CUIGauge::Draw(void)
{

}
//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CUIGauge::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture[0]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME001, &m_pTexture[1]);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME002, &m_pTexture[2]);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CUIGauge::UnLoad(void)
{
	for (int nCnt = 0; nCnt < 1; nCnt++)
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
// ゲージ増減処理
//=============================================================================
void CUIGauge::SetGauge(float fGauge)
{
	m_fVtxHeight -= fGauge;
}

//=============================================================================
// ゲージ状態
//=============================================================================
CUIGauge::GAUGESTATE CUIGauge::GetGaugeState(void)
{
	return m_State;
}
