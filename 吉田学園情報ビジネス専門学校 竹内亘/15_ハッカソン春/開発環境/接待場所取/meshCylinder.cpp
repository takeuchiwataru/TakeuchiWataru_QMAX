//=============================================================================
//
// メッシュシリンダー処理 [meshCylinderBG.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "meshCylinder.h"
#include "manager.h"
#include "game.h"
#include "title.h"
#include "model.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHCYLINDERBG_TEXTURENAME	 "data\\TEXTURE\\MODEL\\CanLabel.jpg"	//テクスチャのファイル名
#define MESHCYLINDERBG_TEXTURENAME1	 "data\\TEXTURE\\SKY\\sky001.png"		//テクスチャのファイル名

//------------------------------------------------------
//シーンメッシュシリンダークラス コンストラクタ
//------------------------------------------------------
CSceneMeshCylinder::CSceneMeshCylinder() : CScene(3, CScene::OBJTYPE_MESHCYLINDER)
{
	m_pTexture = NULL;				//テクスチャへのポインタ
	m_pIdxBuff = NULL;				// インデックスバッファへのポインタ
	m_pVtxBuff = NULL;
	D3DXMatrixIdentity(&m_mtxWorld);// ワールドマトリックスの初期化
	m_nNumVerTex = 0;				// 頂点数
	m_nNumIndex = 0;				// インデックス数
	m_nNumPolygon = 0;				// ポリゴン数
	m_nSplitX = 0;					// 分割数
	m_nSplitY = 0;					// 分割数
}

//--------------------------------------------
//シーンメッシュシリンダークラスクラス デストラクタ
//--------------------------------------------
CSceneMeshCylinder::~CSceneMeshCylinder()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CSceneMeshCylinder * CSceneMeshCylinder::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitY,
												CSceneMeshCylinder::CYLINDERTYPE typeInOut)
{
	CSceneMeshCylinder *pMeshCylinder;

	pMeshCylinder = new CSceneMeshCylinder;

	pMeshCylinder->m_pos = pos;
	pMeshCylinder->m_fWidth = fWidth;
	pMeshCylinder->m_fDepth = fDepth;
	pMeshCylinder->m_nSplitX = nSplitX;
	pMeshCylinder->m_nSplitY = nSplitY;
	pMeshCylinder->m_TypeInOut = typeInOut;
	pMeshCylinder->Init();

	return pMeshCylinder;
}



//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneMeshCylinder::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	int nCntVtx = 0;
	float fXpos = -m_fWidth;
	float fYpos = m_fDepth;
	int nCntIdx = 0;
	float fCylinder = 0.0f;
	float fCylinderHight = 0;

	m_nNumVerTex = (m_nSplitX + 1) * (m_nSplitX + 1);
	m_nNumIndex = ((m_nSplitX + 1) * (m_nSplitX + 1) + ((m_nSplitX - 1) * 2) + (m_nSplitX + 1) * (m_nSplitX - 1));

	//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			MESHCYLINDERBG_TEXTURENAME1,
			&m_pTexture);
			// 頂点情報の作成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) *  m_nNumVerTex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,	//2byteのデータ
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);


	VERTEX_3D *pVtx;
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntY = 0; nCntY < m_nSplitY + 1; nCntY++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
		{
			//頂点情報の設定
			if (m_TypeInOut == CSceneMeshCylinder::CYLINDERTYPE_INWARD)
			{
				pVtx[(nCntY + nCntX) + nCntVtx].pos.x = sinf(fCylinder * D3DX_PI) * fXpos;
				pVtx[(nCntY + nCntX) + nCntVtx].pos.y = 0 - fCylinderHight;
				pVtx[(nCntY + nCntX) + nCntVtx].pos.z = cos(fCylinder * D3DX_PI) * fXpos;
			}
			else
			{
				pVtx[(nCntY + nCntX) + nCntVtx].pos.x = sinf(fCylinder * -D3DX_PI) * fXpos;
				pVtx[(nCntY + nCntX) + nCntVtx].pos.y = 42 - fCylinderHight;
				pVtx[(nCntY + nCntX) + nCntVtx].pos.z = cos(fCylinder * -D3DX_PI) * fXpos;
			}
			//法線の設定
			//pVtx[(nCntY + nCntX) + nCntVtx].nor = D3DXVECTOR3(sinf(fCylinder), cosf(-fCylinder), cosf(fCylinder));
			pVtx[(nCntY + nCntX) + nCntVtx].nor = D3DXVECTOR3(0.0f,1.0f, 0.0f);
			//頂点カラー
			pVtx[(nCntY + nCntX) + nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標
			float ftestU = 0 + (nCntX * (1.0f / m_nSplitX));
			float ftestV = 0 + (nCntY * (1.0f / m_nSplitY));
			pVtx[(nCntY + nCntX) + nCntVtx].tex = D3DXVECTOR2(ftestU, ftestV);

			//角度1を上回る
			if (fCylinder >= 1.0f)
			{
				fCylinder = -1.0f;
			}
			//Xの分割数/2で1を割る
			fCylinder += 1.0f / (m_nSplitX / 2);

		}
		//頂点情報の値を保持
		nCntVtx += m_nSplitX;
		fCylinderHight += m_fDepth;
		fCylinder = 0.0f;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//インデックスデータへのポインタ
	WORD *pIdx;
	//インデックスバッファをロック
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxY = 0; nCntIdxY < m_nSplitY; nCntIdxY++)
	{
		for (int nCntIdxX = 0; nCntIdxX < m_nSplitX + 1;nCntIdxX++,nCntIdx++)
		{
			pIdx[0] = nCntIdx + m_nSplitX + 1;
			pIdx[1] = nCntIdx;
			//pIdxを2個分ずらす
			pIdx += 2;
			if (nCntIdxY < m_nSplitX && nCntIdxX == m_nSplitX)
			{
				pIdx[0] = nCntIdx;
				pIdx[1] = nCntIdx + (m_nSplitX + 1) + 1;
				//pIdxを2個分ずらす
				pIdx += 2;
			}
		}
	}

	//インデックスバッファをロックする
	m_pIdxBuff->Unlock();

	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_pos.y += m_fDepth;
	return S_OK;

}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneMeshCylinder::Uninit(void)
{	//テクスチャの破棄

	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// インデックスバッファの開放
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

		//自分を消す(メッシュフィールドを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneMeshCylinder::Update(void)
{
	//現在のモードを取得
	CManager::MODE mode = CManager::GetMode();
	CPlayer *pPlayer = CTitle::GetPlayer();

	switch (mode)
	{
	case CManager::MODE_GAME:
		//プレイヤー取得
		pPlayer = CGame::GetPlayer();
		m_pos.x = pPlayer->GetPos().x;
		m_pos.z = pPlayer->GetPos().z;
		/*m_rot = pPlayer->GetRot();
		m_rot += pPlayer->m_apModel[0]->Getrot();

		m_mtxWorld = pPlayer->m_apModel[0]->GetMtxWorld();*/
		break;
	case CManager::MODE_TITLE:
		//プレイヤー取得
		//pPlayer = CTitle::GetPlayer();
		//m_pos = pPlayer->GetPos();
		break;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CSceneMeshCylinder::Draw(void)
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
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);
	//頂点フォーマットを設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVerTex, 0, m_nNumIndex - 2);
}

//=============================================================================
// 位置設定
//=============================================================================
void CSceneMeshCylinder::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 回転設定
//=============================================================================
void CSceneMeshCylinder::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// テクスチャを設定
//=============================================================================
void CSceneMeshCylinder::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}
