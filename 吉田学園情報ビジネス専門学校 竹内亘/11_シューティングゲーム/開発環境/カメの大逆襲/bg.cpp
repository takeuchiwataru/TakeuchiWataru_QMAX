//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "bg.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG_TEXTURE] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CBg::CBg():CScene(1)
{
	m_apScene2D[0] = NULL;
	m_apScene2D[1] = NULL;
	m_apScene2D[2] = NULL;
	m_slideSpeed = 0;
}
//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{

}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	// 頂点情報を設定
	VERTEX_2D * pVtx;					// 頂点情報へのポインタ

	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		pVtxBuff = m_apScene2D[nCountBg]->GetVtxBuff();

		// 頂点バッファをロック
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);

		// 頂点バッファをアンロック
		pVtxBuff->Unlock();
	}
	return S_OK;
}
//=============================================================================
// 初期化処理(ゲーム)
//=============================================================================
HRESULT CBg::InitGame(D3DXVECTOR3 pos)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	// 頂点情報を設定
	VERTEX_2D * pVtx;					// 頂点情報へのポインタ

	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		pVtxBuff = m_apScene2D[nCountBg]->GetVtxBuff();

		// 頂点バッファをロック
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(BG_POS_X000, BG_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BG_POS_X001, BG_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(BG_POS_X000, BG_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BG_POS_X001, BG_HEIGHT, 0.0f);

		// 頂点バッファをアンロック
		pVtxBuff->Unlock();
	}
	return S_OK;
}
//=============================================================================
// 終了処理
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		m_apScene2D[nCountBg]->Uninit();
		m_apScene2D[nCountBg] = NULL;
	}

	Release();
}
//=============================================================================
// 更新処理
//=============================================================================
void CBg::Update(void)
{
	m_slideSpeed++;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	// 頂点情報を設定
	VERTEX_2D * pVtx;					// 頂点情報へのポインタ

	for (int nCountBg = 0; nCountBg < MAX_BG; nCountBg++)
	{
		pVtxBuff = m_apScene2D[nCountBg]->GetVtxBuff();

		// 頂点バッファをロック
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		if (m_apScene2D[nCountBg] == m_apScene2D[0])
		{// 背景1
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_000));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_000));
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_000));
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_000));
		}

		else if (m_apScene2D[nCountBg] == m_apScene2D[1])
		{// 背景2
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_100));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_100));
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_100));
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_100));
		}

		else if (m_apScene2D[nCountBg] == m_apScene2D[2])
		{// 背景3
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_200));
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f - (m_slideSpeed * BG_MOVESPEED_200));
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_200));
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f - (m_slideSpeed * BG_MOVESPEED_200));
		}

		// 頂点バッファをアンロック
		pVtxBuff->Unlock();
	}
}
//=============================================================================
// 描画処理
//=============================================================================
void CBg::Draw(void)
{

}
//=============================================================================
// 生成
//=============================================================================
CBg * CBg::Create(D3DXVECTOR3 pos)
{
	CBg *pBg = NULL;

	if (pBg == NULL)
	{
		pBg = new CBg;
		
		for (int nCntScene2D = 0; nCntScene2D < MAX_BG; nCntScene2D++)
		{// CScene2Dの繰り返し
			pBg->m_apScene2D[nCntScene2D] = new CScene2D(1);
			if (pBg != NULL)
			{
				pBg->m_apScene2D[nCntScene2D]->Init(pos);
				pBg->m_apScene2D[nCntScene2D]->BindTexture(m_apTexture[nCntScene2D]);
			}
		}
		pBg->Init(pos);
	}
	return pBg;
}
//=============================================================================
// 生成(ゲーム)
//=============================================================================
CBg * CBg::Create2(D3DXVECTOR3 pos)
{
	CBg *pBg = NULL;

	if (pBg == NULL)
	{
		pBg = new CBg;

		for (int nCntScene2D = 0; nCntScene2D < MAX_BG; nCntScene2D++)
		{// CScene2Dの繰り返し
			pBg->m_apScene2D[nCntScene2D] = new CScene2D(1);
			if (pBg != NULL)
			{
				pBg->m_apScene2D[nCntScene2D]->Init(pos);
				pBg->m_apScene2D[nCntScene2D]->BindTexture(m_apTexture[nCntScene2D]);
			}
		}
		pBg->InitGame(pos);
	}
	return pBg;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CBg::Load(void)
{
	CManager manager;	// インスタンス

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = manager.GetRenderer()->GetDevice();

	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_000, &m_apTexture[0]);	// 背景1
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_001, &m_apTexture[1]);	// 背景2
	D3DXCreateTextureFromFile(pDevice, BG_TEXTURE_002, &m_apTexture[2]);	// 背景3

	return S_OK;
}
//=============================================================================
// テクスチャの破棄
//=============================================================================
void CBg::Unload(void)
{
	// テクスチャの破棄
	if (m_apTexture[MAX_BG_TEXTURE] != NULL)
	{
		m_apTexture[MAX_BG_TEXTURE]->Release();
		m_apTexture[MAX_BG_TEXTURE] = {};
	}
}
