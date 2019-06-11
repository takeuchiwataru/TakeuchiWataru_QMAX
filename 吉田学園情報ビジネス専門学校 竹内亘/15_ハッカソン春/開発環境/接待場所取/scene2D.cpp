//---------------------------------------------------------------------
//	シーン2D処理(scene2d.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "scene2D.h"
#include "manager.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLYGON_TEXTURENAME  "data\\TEXTURE\\akira000.png"	//テクスチャのファイル名
#define POLYGON_SIZE		(100)							//頂点座標Xの移動量
#define EXPLOSION_UV_U (1.0f)
#define EXPLOSION_UV_V (0.25f)

//*****************************************************************************
// グローバル
//*****************************************************************************

//--------------------------------------------
//シーン2Dクラス コンストラクタ
//--------------------------------------------
CScene2D::CScene2D(int nPriority) : CScene(nPriority,CScene::OBJTYPE_SCENE2D)
{
	//メンバ変数
	m_pTexture = NULL;		// テクスチャへのポインタ
	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ

	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// シーン2Dの位置

	m_fSpin = 0;			//回転
	m_fLength = 0;			//大きさ
	m_fScale = 0;			//拡大縮小
}

//--------------------------------------------
//シーン2Dクラス デストラクタ
//--------------------------------------------
CScene2D::~CScene2D()
{
}

//--------------------------------------------
//シーン2Dの生成
//--------------------------------------------
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nPriority)
{
	CScene2D *pScene2D;

	pScene2D = new CScene2D(nPriority);

	pScene2D->m_pos = pos;
	pScene2D->m_fWidth = fWidth;
	pScene2D->m_fHeight = fHeight;

	pScene2D->Init();

	return pScene2D;
}

//=============================================================================
// シーン2Dの初期化処理
//=============================================================================
HRESULT CScene2D::Init()
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//拡大の値
	m_fScale = 1.0f;
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報を設定
	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f) * m_fWidth;
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f) * m_fHeight;
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f) * m_fWidth;
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f) * m_fHeight;
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f) * m_fWidth;
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f) * m_fHeight;
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f) * m_fWidth;
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f) * m_fHeight;

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	//頂点
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//値の初期設定
	m_bDraw = true;
	//オブジェクトタイプの設定
	CScene::SetObjType(OBJTYPE_SCENE2D);

	return S_OK;
}

//=============================================================================
// シーン2Dの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//自分を消す(シーン2Dを破棄)
	Release();
}

//=============================================================================
// シーン2Dの更新処理
//=============================================================================
void CScene2D::Update(void)
{
}

//=============================================================================
// シーン2Dの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	if (m_bDraw == true)
	{
		if (GetObjType() == OBJTYPE_PAUSE)
		{
			// αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		//アルファテスト(透明色を描画しないように)
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 90);


		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		// テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);
		// シーン2Dの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			0,	//開始する頂点のインデックス
			2); //描画するプリミティブ数


		if (GetObjType() == OBJTYPE_PAUSE)
		{
			// αブレンディングを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}
	}
}

//=============================================================================
//シーン2Dテクスチャの設定
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}

//=============================================================================
//シーン2D位置設定
//=============================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos, float fSpin, float fScale, D3DXCOLOR col)
{
	m_pos = pos;		//位置
	m_fSpin = fSpin;	//回転
	m_Col = col;		//色
	m_fScale = fScale;	//拡大

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) *  (m_fWidth  + m_fScale);
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f  + m_fSpin) *  (m_fWidth  + m_fScale);
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f  + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  (m_fWidth  + m_fScale);
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f  + m_fSpin) *  (m_fWidth  + m_fScale);
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f  + m_fSpin) *  (m_fHeight + m_fScale);

	//頂点カラー
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//=============================================================================
//シーン2D回転設定
//=============================================================================
void CScene2D::SetRot(float fSpin)
{
	m_fSpin = fSpin;	//回転

	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
#if 1
	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  m_fLength;
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f + m_fSpin) *  m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f + m_fSpin) *  m_fLength;
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  m_fLength;
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f + m_fSpin) *  m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f + m_fSpin) *  m_fLength;
#endif
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//=============================================================================
//シーン2D位置を取得
//=============================================================================
D3DXVECTOR3 CScene2D::Getpos(void)
{
	return m_pos;
}

//=============================================================================
//頂点情報を取得
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 CScene2D::GetVtx(void)
{
	return m_pVtxBuff;
}

//=============================================================================
//描画ブールの切り替え
//=============================================================================
void CScene2D::SetbDraw(bool bDraw)
{
	m_bDraw = bDraw;
}
//=============================================================================
//色の切り替え
//=============================================================================
void CScene2D::SetColor(D3DXCOLOR col)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//頂点カラー
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
//大きさ変更
//=============================================================================
void CScene2D::SetScale(float fScale)
{
	m_fScale = fScale;	//拡大

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[0].pos.y = m_pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI * 0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI * 0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[2].pos.x = m_pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[2].pos.y = m_pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[3].pos.x = m_pos.x + sinf(D3DX_PI * 0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[3].pos.y = m_pos.y + cosf(D3DX_PI * 0.25f + m_fSpin) *  (m_fHeight + m_fScale);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}
//=============================================================================
// 爆発の設定処理
//=============================================================================
void CScene2D::SetExplosion(int m_PatternAnim)
{
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//////テクスチャの座標
	//pVtx[0].tex = D3DXVECTOR2(EXPLOSION_UV_U * m_PatternAnim, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(EXPLOSION_UV_U * m_PatternAnim + EXPLOSION_UV_U, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(EXPLOSION_UV_U * m_PatternAnim,  EXPLOSION_UV_V);
	//pVtx[3].tex = D3DXVECTOR2(EXPLOSION_UV_U * m_PatternAnim + EXPLOSION_UV_U, EXPLOSION_UV_V);

	////テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(EXPLOSION_UV_U, EXPLOSION_UV_V * m_PatternAnim);
	pVtx[1].tex = D3DXVECTOR2(0.0f, EXPLOSION_UV_V * m_PatternAnim);
	pVtx[2].tex = D3DXVECTOR2(EXPLOSION_UV_U, EXPLOSION_UV_V * m_PatternAnim + EXPLOSION_UV_V);
	pVtx[3].tex = D3DXVECTOR2(0.0f, EXPLOSION_UV_V * m_PatternAnim + EXPLOSION_UV_V);

	m_PatternAnim = 0;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 位置の設定
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos, float nSizeX, float nSizeY)
{
	m_pos = pos;

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - nSizeX, m_pos.y - nSizeY, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + nSizeX, m_pos.y - nSizeY, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - nSizeX, m_pos.y + nSizeY, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + nSizeX, m_pos.y + nSizeY, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// 色の設定処理
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	m_Col = col;

	//頂点情報へのポインタ
	VERTEX_2D*pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//色の設定
	pVtx[0].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[1].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[2].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);
	pVtx[3].col = D3DXCOLOR(m_Col.r, m_Col.g, m_Col.b, m_Col.a);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}