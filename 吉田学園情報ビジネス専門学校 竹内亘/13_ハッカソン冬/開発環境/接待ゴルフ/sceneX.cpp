//=============================================================================
//
// モデル処理 [sceneX.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "sceneX.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "bullet.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL_NAME000		"data\\MODEL\\MODELBG\\box000.x"		//テクスチャのファイル名
#define MODEL_NAME001		"data\\MODEL\\MODELBG\\box000.x"		//テクスチャのファイル名
#define TEX_NAME000			"data\\TEXTURE\\exclamation000.jpg"		//テクスチャのファイル名

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//--------------------------------------------
//シーンXクラス コンストラクタ
//--------------------------------------------
CSceneX::CSceneX() : CScene(3, CScene::OBJTYPE_SCENEX)
{
}

//--------------------------------------------
//シーンXクラス デストラクタ
//--------------------------------------------
CSceneX::~CSceneX()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CSceneX * CSceneX::Create(D3DXVECTOR3 pos)
{
	CSceneX *pSceneX;

	pSceneX = new CSceneX;

	pSceneX->m_aModel.pos = pos;

	pSceneX->Init();

	return pSceneX;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneX::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL_NAME000,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMatModel,
		NULL,
		&m_nNumMatModel,
		&m_pMeshModel);

	int nNumVtex;	//頂点数
	DWORD sizeFvF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	D3DXVECTOR3 vtx;

	m_aModel.VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
	m_aModel.VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);
	m_aModel.nType = 0;
	m_aModel.bUse = false;

	//頂点数を取得
	nNumVtex = m_pMeshModel->GetNumVertices();
	//頂点フォーマットのサイズを取得
	sizeFvF = D3DXGetFVFVertexSize(m_pMeshModel->GetFVF());
	//頂点　ロック
	m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
	{	//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (m_aModel.VtxMinModel.x > vtx.x)
		{
			m_aModel.VtxMinModel.x = vtx.x;
		}
		if (m_aModel.VtxMinModel.y > vtx.y)
		{
			m_aModel.VtxMinModel.y = vtx.y;
		}
		if (m_aModel.VtxMinModel.z > vtx.z)
		{
			m_aModel.VtxMinModel.z = vtx.z;
		}

		if (m_aModel.VtxMaxModel.x < vtx.x)
		{
			m_aModel.VtxMaxModel.x = vtx.x;
		}
		if (m_aModel.VtxMaxModel.y < vtx.y)
		{
			m_aModel.VtxMaxModel.y = vtx.y;
		}
		if (m_aModel.VtxMaxModel.z < vtx.z)
		{
			m_aModel.VtxMaxModel.z = vtx.z;
		}
		pVtxBuff += sizeFvF;
	}
	//頂点バッファをアンロック
	m_pMeshModel->UnlockVertexBuffer();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEX_NAME000,
		&m_pTextureModel);

	SetModel(m_aModel.pos, 0);

	//オブジェクトタイプの設定
	CScene::SetObjType(OBJTYPE_SCENEX);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneX::Uninit(void)
{
		//自分を消す(シーンXを破棄)
		Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneX::Update(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void CSceneX::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

		// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_aModel.mtxWorld);
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_aModel.rot.y, m_aModel.rot.x, m_aModel.rot.z);
	D3DXMatrixMultiply(&m_aModel.mtxWorld, &m_aModel.mtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_aModel.pos.x, m_aModel.pos.y, m_aModel.pos.z);
	D3DXMatrixMultiply(&m_aModel.mtxWorld, &m_aModel.mtxWorld, &mtxTrans);
	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_aModel.mtxWorld);
	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();
	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
		// テクスチャ
		pDevice->SetTexture(0, m_pTextureModel);
		if (m_aModel.bUse == true)	//モデルが使用されている
		{
			// モデル(パーツ)の描画
			m_pMeshModel->DrawSubset(nCntMat);
		}
	}
	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);

}

//*****************************************************************************
//モデル位置設定処理
//*****************************************************************************
void CSceneX::Setpos(D3DXVECTOR3 pos)
{
	m_aModel.pos = pos;
}

void CSceneX::Setrot(D3DXVECTOR3 rot)
{
	m_aModel.rot = rot;
}

//*****************************************************************************
//モデルポインタ処理
//*****************************************************************************
CSceneX::MODEL *CSceneX::GetModel(void)
{
	return &m_aModel;
}
//*****************************************************************************
//モデルとの当たり判定処理
//*****************************************************************************
bool CSceneX::CollisionModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove,
	D3DXVECTOR3 VtxMax, D3DXVECTOR3 VtxMin)
{
	bool bLand = false;
	if (m_aModel.bUse == true)
	{
		//モデルのY幅の中
		if (pPos->y < m_aModel.pos.y + m_aModel.VtxMaxModel.y
			&& pPos->y > m_aModel.pos.y + m_aModel.VtxMinModel.y)
		{
			//モデルのZ幅の中
			if (pPos->z + VtxMin.z < m_aModel.pos.z + m_aModel.VtxMaxModel.z
				&& pPos->z + VtxMax.z > m_aModel.pos.z + m_aModel.VtxMinModel.z)
			{
				//モデルのX幅の中
				if (pPos->x + VtxMin.x < m_aModel.pos.x + m_aModel.VtxMaxModel.x
					&& pPos->x + VtxMax.x > m_aModel.pos.x + m_aModel.VtxMinModel.x)
				{

					//X幅の当たり判定
					if (pPosOld->x > m_aModel.pos.x + m_aModel.VtxMaxModel.x)
					{
						pPos->x = m_aModel.pos.x + m_aModel.VtxMaxModel.x + VtxMax.x;
						pPosOld->x = m_aModel.pos.x + m_aModel.VtxMaxModel.x + VtxMax.x;
						//pMove->x = 0;
						bLand = true;
					}
					else if (pPosOld->x < m_aModel.pos.x + m_aModel.VtxMinModel.x)
					{
						pPos->x = m_aModel.pos.x + m_aModel.VtxMinModel.x + VtxMin.x;
						pPosOld->x = m_aModel.pos.x + m_aModel.VtxMinModel.x + VtxMin.x;
						//pMove->x = 0;
						bLand = true;

					}
					//Z幅の当たり判定
					if (pPosOld->z > m_aModel.pos.z + m_aModel.VtxMaxModel.z)
					{
						bLand = true;
						pPos->z = m_aModel.pos.z + m_aModel.VtxMaxModel.z + VtxMax.z;
						pPosOld->z = m_aModel.pos.z + m_aModel.VtxMaxModel.z + VtxMax.z;
						//pMove->z = 0;
					}
					else if (pPosOld->z < m_aModel.pos.z + m_aModel.VtxMinModel.z)
					{
						bLand = true;
						pPos->z = m_aModel.pos.z + m_aModel.VtxMinModel.z + VtxMin.z;
						pPosOld->z = m_aModel.pos.z + m_aModel.VtxMinModel.z + VtxMin.z;
						//pMove->z = 0;
					}
					//Y幅の当たり判定
					if (pPosOld->y >= m_aModel.pos.y + m_aModel.VtxMaxModel.y)
					{
						pPos->y = m_aModel.pos.y + m_aModel.VtxMaxModel.y;
						pPosOld->y = m_aModel.pos.y + m_aModel.VtxMaxModel.y;

					}
					else if (pPosOld->y <= m_aModel.pos.y + m_aModel.VtxMinModel.y)
					{
						pPos->y = m_aModel.pos.y + m_aModel.VtxMinModel.y;
						pPosOld->y = m_aModel.pos.y + m_aModel.VtxMinModel.y;
					}
				}
			}
		}

	}
	return bLand;
}


//=============================================================================
// モデルの設定処理
//=============================================================================
void CSceneX::SetModel(D3DXVECTOR3 pos, int nType)
{

	int nNumVtex;	//頂点数
	DWORD sizeFvF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	D3DXVECTOR3 vtx;

	//頂点数を取得
	nNumVtex = m_pMeshModel->GetNumVertices();
	//頂点フォーマットのサイズを取得
	sizeFvF = D3DXGetFVFVertexSize(m_pMeshModel->GetFVF());

	//頂点　ロック
	m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
	{	//頂点座標の代入
		vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (m_aModel.VtxMinModel.x > vtx.x)
		{
			m_aModel.VtxMinModel.x = vtx.x;
		}
		if (m_aModel.VtxMinModel.y > vtx.y)
		{
			m_aModel.VtxMinModel.y = vtx.y;
		}
		if (m_aModel.VtxMinModel.z > vtx.z)
		{
			m_aModel.VtxMinModel.z = vtx.z;
		}

		if (m_aModel.VtxMaxModel.x < vtx.x)
		{
			m_aModel.VtxMaxModel.x = vtx.x;
		}
		if (m_aModel.VtxMaxModel.y < vtx.y)
		{
			m_aModel.VtxMaxModel.y = vtx.y;
		}
		if (m_aModel.VtxMaxModel.z < vtx.z)
		{
			m_aModel.VtxMaxModel.z = vtx.z;
		}
		pVtxBuff += sizeFvF;

		//頂点バッファをアンロック
		m_pMeshModel->UnlockVertexBuffer();
	}
		if (m_aModel.bUse == false)
		{
			// 位置・向きの初期設定
			m_aModel.pos = pos;
			m_aModel.rot = D3DXVECTOR3(0, 0, 0);
			m_aModel.fShadow = 12;
			m_aModel.nType = nType;
			m_aModel.bUse = true;
		}
}

//=============================================================================
// マテリアル割り当て処理
//=============================================================================
void CSceneX::BindTexture(LPDIRECT3DTEXTURE9 Texture, LPD3DXMESH Mesh, LPD3DXBUFFER Buff)
{
	m_pBuffMatModel = Buff;
	m_pTextureModel = Texture;
	m_pMeshModel = Mesh;
}