//=============================================================================
//
// メッシュオービット処理処理 [meshField.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "meshOrbit.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\gradation000.jpg"	// 地面のテクスチャ名
#define MESHFIELD_SIZE_X		(50.0f)							// 地面大きさ
#define MESHFIELD_SIZE_Z		(50.0f)							// 地面大きさ
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DVERTEXBUFFER9		CMeshOrbit::m_pVtxBuff = NULL;
LPDIRECT3DTEXTURE9			CMeshOrbit::m_pTexture = NULL;

//--------------------------------------------
//シーンメッシュオービットクラス コンストラクタ
//--------------------------------------------
CMeshOrbit::CMeshOrbit() : CScene(4, CScene::OBJTYPE_MESHFIELD)
{
	m_MeshOrbit = {};				//シーン3D構造体
	m_pTexture = NULL;				//テクスチャへのポインタ
	D3DXMatrixIdentity(&m_mtxWorld);
	m_nNumVerTex = 0;				// 頂点数
	m_nNumPolygon = 0;				// ポリゴン数
	m_nAlphaMinus = 0;
	m_fAlpha = 1.0f;
	m_aPosVertex[0] = D3DXVECTOR3(0, 0, 0);
	m_aPosVertex[1] = D3DXVECTOR3(0, 0, 0);
}

//--------------------------------------------
//シーンメッシュオービットクラスクラス デストラクタ
//--------------------------------------------
CMeshOrbit::~CMeshOrbit()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CMeshOrbit * CMeshOrbit::Create(D3DXVECTOR3 pos)
{

	CMeshOrbit *pMeshOrbit;

	pMeshOrbit = new CMeshOrbit;

	pMeshOrbit->m_MeshOrbit.pos = pos;

	pMeshOrbit->Init();

	return pMeshOrbit;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshOrbit::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

												// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	// 頂点情報の作成
	MakeVertexMeshOrbit(pDevice);

	// ポリゴンの情報を設定
	m_MeshOrbit.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MeshOrbit.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//軌跡の初期位置
	m_aPosVertex[0] = m_MeshOrbit.pos;
	m_aPosVertex[1] = m_MeshOrbit.pos;
	//オフセットの設定
	m_offSet[0] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_offSet[1] = D3DXVECTOR3(0.0f, 50.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void  CMeshOrbit::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//自分を消す(メッシュオービットを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void  CMeshOrbit::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtxX = 0, nVtxCounter = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
	{
		// 頂点カラーの設定
		pVtx[nCntVtxX + nVtxCounter].col =		D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fAlpha - (nCntVtxX * 0.03f));
		pVtx[nCntVtxX + nVtxCounter + 1].col =	D3DXCOLOR(1.0f, 0.0f, 0.0f, m_fAlpha - (nCntVtxX * 0.01f));
		nVtxCounter += POLYGON_Z;
	}
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	if (m_nCntAlpha >= 60)
	{
		m_nCntAlpha = 0;
	}

#ifdef _DEBUG
#if 0
	//任意のキー1
	if (pInput->GetPress(DIK_1) == true)
	{
		m_nAlphaMinus += 1;
	}
	//任意のキー2
	if (pInput->GetPress(DIK_2) == true)
	{
		m_nAlphaMinus -= 1;
	}

	//任意のキー1
	if (pInput->GetPress(DIK_3) == true)
	{
		m_fAlpha += 0.01f;
	}
	//任意のキー2
	if (pInput->GetPress(DIK_4) == true)
	{
		m_fAlpha -= 0.01f;
	}

	CDebugProc::Print(1, " 透明度  : ( %d )\n", m_nAlphaMinus);
	CDebugProc::Print(1, " 透明度  : ( %.1f )\n", m_fAlpha);

#if 0
	CDebugProc::Print(1, " オービット[0]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[0].x, m_aPosVertex[0].y, m_aPosVertex[0].z);
	CDebugProc::Print(1, " オービット[1]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[1].x, m_aPosVertex[1].y, m_aPosVertex[1].z);
	CDebugProc::Print(1, " オービット[2]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[2].x, m_aPosVertex[2].y, m_aPosVertex[2].z);
	CDebugProc::Print(1, " オービット[3]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[3].x, m_aPosVertex[3].y, m_aPosVertex[3].z);
	CDebugProc::Print(1, " オービット[4]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[4].x, m_aPosVertex[4].y, m_aPosVertex[4].z);
	CDebugProc::Print(1, " オービット[5]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[5].x, m_aPosVertex[5].y, m_aPosVertex[5].z);
	CDebugProc::Print(1, " オービット[6]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[6].x, m_aPosVertex[6].y, m_aPosVertex[6].z);
	CDebugProc::Print(1, " オービット[7]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[7].x, m_aPosVertex[7].y, m_aPosVertex[7].z);
	CDebugProc::Print(1, " オービット[8]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[8].x, m_aPosVertex[8].y, m_aPosVertex[8].z);
	CDebugProc::Print(1, " オービット[9]  : ( %.1f ,%.1f ,%.1f )\n", m_aPosVertex[9].x, m_aPosVertex[9].y, m_aPosVertex[9].z);
#endif
#endif
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void  CMeshOrbit::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DXMATRIX mtxParent;

	// 頂点情報の設定
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//入れ変え
	for (int nCnt = m_nNumVerTex - 3; nCnt >= 0; nCnt--)
	{
		m_aPosVertex[nCnt + 2] = m_aPosVertex[nCnt];
		pVtx[nCnt + 2].pos = m_aPosVertex[nCnt + 2];
	}

	//マトリックスとかけ合わせる
	D3DXVec3TransformCoord(&m_aPosVertex[0], &m_offSet[0], m_pMtxParent);
	pVtx[0].pos = m_aPosVertex[0];

	D3DXVec3TransformCoord(&m_aPosVertex[1], &m_offSet[1], m_pMtxParent);
	pVtx[1].pos = m_aPosVertex[1];
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//アルファテスト
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//カリングの設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0,m_nNumPolygon);
	//カリングの設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	//デフォルトの場合FALSEになっているからTRUEにする
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void CMeshOrbit::MakeVertexMeshOrbit(LPDIRECT3DDEVICE9 pDevice)
{
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxX;

	// 頂点数
	m_nNumVerTex = (POLYGON_X + 1) * (POLYGON_Z + 1);

	// ポリゴン数
	m_nNumPolygon = (POLYGON_X + 1) * (POLYGON_Z + 1) + (2 * (POLYGON_Z - 1)) + (POLYGON_X + 1) * (POLYGON_Z - 1) - 2;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVerTex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxX = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
	{
		// 頂点座標の設定

		pVtx[nCntVtxX + nVtxCounter].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[nCntVtxX + nVtxCounter + 1].pos = D3DXVECTOR3(0.0f, 50.0f, 0.0f);

		// 法線の設定
		pVtx[nCntVtxX + nVtxCounter].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntVtxX + nVtxCounter + 1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		// 頂点カラーの設定
		pVtx[nCntVtxX + nVtxCounter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[nCntVtxX + nVtxCounter + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		// テクスチャ座標の設定
		pVtx[nCntVtxX + nVtxCounter].tex = D3DXVECTOR2(0.0f + (nCntVtxX * (1.0f / POLYGON_X)), 0.0f);
		pVtx[nCntVtxX + nVtxCounter + 1].tex = D3DXVECTOR2(0.0f + (nCntVtxX * (1.0f / POLYGON_X)), 1.0f);

		nVtxCounter += POLYGON_Z;
	}
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CMeshOrbit::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CMeshOrbit::UnLoad(void)
{
	//テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=============================================================================
// 位置設定処理
//=============================================================================
void CMeshOrbit::Setpos(D3DXVECTOR3 pos)
{
}

//=============================================================================
// 親を設定
//=============================================================================
void CMeshOrbit::SetMtxParent(D3DXMATRIX * pMtx)
{
	m_pMtxParent = pMtx;
}
