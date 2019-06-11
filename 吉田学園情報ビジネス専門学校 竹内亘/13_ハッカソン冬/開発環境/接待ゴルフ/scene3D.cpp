//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "scene3D.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLYGON_TEXTURENAME		 "data\\TEXTURE\\field001.jpg"	//テクスチャのファイル名
#define TEX_POS_X_INIT			(1.0f)							//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)							//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)							//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)							//テクスチャ座標U右
#define TEX_TOP					(0.0f)							//テクスチャ座標V上
#define TEX_BOT					(1.0f)							//テクスチャ座標V下

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
//LPDIRECT3DVERTEXBUFFER9		CScene3D::m_pVtxBuffPolygon = NULL;

//--------------------------------------------
//シーン3Dクラス コンストラクタ
//--------------------------------------------
CScene3D::CScene3D() : CScene(4, CScene::OBJTYPE_SCENE3D)
{
	m_pos = D3DXVECTOR3(0,0,0);			//位置
	m_rot = D3DXVECTOR3(0, 0, 0);		//向き
	D3DXMatrixIdentity(&m_mtxWorld);	//ワールドマトリックス
}

//--------------------------------------------
//シーン3Dクラス デストラクタ
//--------------------------------------------
CScene3D::~CScene3D()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CScene3D * CScene3D::Create(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	CScene3D *pScene3D;

	pScene3D = new CScene3D;

	pScene3D->m_pos = pos;
	pScene3D->m_fWidth = fWidth;
	pScene3D->m_fDepth = fDepth;
	pScene3D->Init();

	return pScene3D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//法線用
	D3DXVECTOR3 Vec0, Vec1, nor0, nor1;


	//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			POLYGON_TEXTURENAME,
			&m_pTexturePolygon);
	// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPolygon,
		NULL);


	VERTEX_3D *pVtx;
	//頂点バッファをロック
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);
	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y, m_pos.z + m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y, m_pos.z + m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_fWidth, m_pos.y, m_pos.z - m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_fWidth, m_pos.y, m_pos.z - m_fDepth);

	//pVtx[0].pos = D3DXVECTOR3(-m_pos.x, m_pos.y, m_pos.z);
	//pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z);
	//pVtx[2].pos = D3DXVECTOR3(-m_pos.x, m_pos.y, -m_pos.z);
	//pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, -m_pos.z);


	//法線計算算出
	Vec0 = pVtx[0].pos - pVtx[2].pos;
	Vec1 = pVtx[3].pos - pVtx[2].pos;
	// X,Y,Zの順で↓
	nor0.x = (Vec0.y * Vec1.z) - (Vec0.z * Vec1.y);
	nor0.y = (Vec0.z * Vec1.x) - (Vec0.x * Vec1.z);
	nor0.z = (Vec0.x * Vec1.y) - (Vec0.y * Vec1.x);
	//正規化
	D3DXVec3Normalize(&nor0, &nor0);
	pVtx[2].nor = nor0;

	//法線計算算出
	Vec0 = pVtx[3].pos - pVtx[1].pos;
	Vec1 = pVtx[0].pos - pVtx[1].pos;
	//一行で書ける
	//D3DXVec3Cross(&nor1, &Vec0, &Vec1);

	nor1.x = (Vec0.y * Vec1.z) - (Vec0.z * Vec1.y);
	nor1.y = (Vec0.z * Vec1.x) - (Vec0.x * Vec1.z);
	nor1.z = (Vec0.x * Vec1.y) - (Vec0.y * Vec1.x);
	//正規化しないといけない
	D3DXVec3Normalize(&nor1, &nor1);
	pVtx[3].nor = nor1;

	//nor0とnor1の中間値をとる
	pVtx[0].nor = (nor0 + nor1) / 2;
	pVtx[1].nor = (nor0 + nor1) / 2;

	//for (int nCnt = 0; nCnt < 4; nCnt++)
	//{
	//	m_aNor[nCnt] = pVtx[nCnt].nor;
	//	m_aPos[nCnt] = pVtx[nCnt].pos;
	//}

	//法線の設定
	//法線の設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(TEX_LEFT, TEX_TOP);
	pVtx[1].tex = D3DXVECTOR2(TEX_RIGHT, TEX_TOP);
	pVtx[2].tex = D3DXVECTOR2(TEX_LEFT, TEX_BOT);
	pVtx[3].tex = D3DXVECTOR2(TEX_RIGHT, TEX_BOT);

	//頂点バッファをアンロックする
	m_pVtxBuffPolygon->Unlock();

	//オブジェクトタイプの設定
	CScene::SetObjType(OBJTYPE_SCENE3D);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3D::Uninit(void)
{	//テクスチャの破棄
	if (m_pTexturePolygon != NULL)
	{
		m_pTexturePolygon->Release();
		m_pTexturePolygon = NULL;
	}
	// 頂点バッファの開放
	if (m_pVtxBuffPolygon != NULL)
	{
		m_pVtxBuffPolygon->Release();
		m_pVtxBuffPolygon = NULL;
	}
	//自分を消す(シーン3Dを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	CScene3D::Setpos(m_pos);

}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3D::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);
	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));
	//頂点フォーマットを設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexturePolygon);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,	//開始する頂点のインデックス
		2); //描画するプリミティブ数

}

//=============================================================================
// 位置設定処理
//=============================================================================
void CScene3D::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 頂点取得処理
//=============================================================================
//LPDIRECT3DVERTEXBUFFER9 CScene3D::GetVtx(void)
//{
//	return m_pVtxBuffPolygon;
//}

//=============================================================================
// 地面の高さを返す
//=============================================================================
float CScene3D::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;
	//頂点バッファをロック
	m_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	float fGaiseki;
	//用
	D3DXVECTOR3 VecA, VecB, Vec0, Vec1;
	//右側の三角形
	Vec0 = pVtx[1].pos - pVtx[2].pos;
	Vec1 = pos - pVtx[2].pos;
	fGaiseki = (Vec0.z * Vec1.x) - (Vec0.x * Vec1.z);

	if (fGaiseki < 0)
	{//右
		VecA = pos - pVtx[0].pos;
		//VecAのyを求める
		m_Height = (-(VecA.x * pVtx[0].nor.x) - (VecA.z * pVtx[0].nor.z)) / pVtx[0].nor.y + pVtx[0].pos.y;
	}
	else if (fGaiseki >= 0)
	{//左
		VecB = pos - pVtx[3].pos;
		//VecAのyを求める
		m_Height = (-(VecB.x * pVtx[3].nor.x) - (VecB.z * pVtx[3].nor.z)) / pVtx[3].nor.y + pVtx[3].pos.y;
	}
	//頂点バッファをアンロックする
	m_pVtxBuffPolygon->Unlock();

	return m_Height;
}
