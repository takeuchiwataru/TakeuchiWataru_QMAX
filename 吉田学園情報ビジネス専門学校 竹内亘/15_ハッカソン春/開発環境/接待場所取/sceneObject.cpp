//=============================================================================
//
// シーンオブジェクト処理 [sceneObject.cpp]
// Author : Meguro Mikiya
//
//=============================================================================
#include "sceneObject.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

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
//オブジェクトクラス コンストラクタ
//--------------------------------------------
CSceneObject::CSceneObject()
{
	m_pMeshModel = NULL;		//メッシュ情報へのポインタ
	m_pBuffMatModel = NULL;		//マテリアル情報へのポインタ
	m_pTextureModel = NULL;		//テクスチャへのポインタ
	m_nNumMatModel = 0;			//マテリアル情報の数
	//m_aModel = {};
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	m_bShadow = false;			//シャドウフラグ
	m_pParent = NULL;			//親オブジェクトへのポインタ
}

//--------------------------------------------
//オブジェクトクラス デストラクタ
//--------------------------------------------
CSceneObject::~CSceneObject()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CSceneObject * CSceneObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSceneObject *pModel;

	pModel = new CSceneObject;

	pModel->Init();

	pModel->m_pos = pos;
	pModel->m_rot = rot;

	return pModel;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneObject::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = D3DXVECTOR3(0,0,0);			//位置
	m_rot = D3DXVECTOR3(0, 0, 0);		//向き
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneObject::Uninit(void)
{
	//ポインタのNULLチェック (家)
	if (m_pTextureModel != NULL)
	{
		for (int nCnt = 0; nCnt < (int)m_nNumMatModel; nCnt++)
		{
			//ポインタ内のポインタのNULLチェック (家具)
			if (m_pTextureModel[nCnt] != NULL)
			{
				//テクスチャ破棄
				m_pTextureModel[nCnt]->Release();
				m_pTextureModel[nCnt] = NULL;
			}
		}
		//メモリを開放 (解体)
		delete[] m_pTextureModel;
		//NULLを入れる (更地)
		m_pTextureModel = NULL;
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneObject::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CSceneObject::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス
	D3DXMATRIX mtxParent;

	D3DMATERIAL9 matDef;						//現在のマテリアル保存用
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);
	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		if (pMat != NULL)
		{
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (m_bShadow == false)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					//テクスチャがある場合
					pDevice->SetTexture(0, m_pTextureModel[nCntMat]);
				}
				else
				{	// テクスチャを使っていない
					pDevice->SetTexture(0, NULL);
				}
			}
			else
			{	// テクスチャを使っていない
				pDevice->SetTexture(0, NULL);
			}
		}
		//オブジェクト(パーツ)の描画
		m_pMeshModel->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//*****************************************************************************
//オブジェクト位置設定処理
//*****************************************************************************
void CSceneObject::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//*****************************************************************************
//オブジェクト回転設定処理
//*****************************************************************************
void CSceneObject::Setrot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// マテリアル割り当て処理
//=============================================================================
void CSceneObject::BindModel(DWORD nNumMat, LPD3DXMESH Mesh, LPD3DXBUFFER Buff)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	m_pBuffMatModel = Buff;
	m_nNumMatModel = nNumMat;
	m_pMeshModel = Mesh;

	//マテリアル情報からテクスチャの取得
	pMat = (D3DXMATERIAL*)m_pBuffMatModel->GetBufferPointer();

	//テクスチャをマテリアルの数分動的確保
	m_pTextureModel = new LPDIRECT3DTEXTURE9[m_nNumMatModel];

	//マテリアルの数回す
	for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMatModel; nCntMatTex++)
	{
		//NULLを入れる 中身を空に
		m_pTextureModel[nCntMatTex] = NULL;

		if (pMat[nCntMatTex].pTextureFilename != NULL)
		{
			// テクスチャの設定
			D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
				pMat[nCntMatTex].pTextureFilename,	// ファイルの名前
				&m_pTextureModel[nCntMatTex]);		// テクスチャへのポインタ
		}
	}

	//大きさを設定
	VtxMinMaxSet();
}

//=============================================================================
// 親の設定処理
//=============================================================================
void CSceneObject::SetParent(CSceneObject * pModel)
{
	m_pParent = pModel;
}
//=============================================================================
// ワールドマトリックスの取得処理
//=============================================================================
D3DXMATRIX CSceneObject::GetMtxWorld(void)
{
	return m_mtxWorld;
}
//=============================================================================
// ワールドマトリックスの設定処理
//=============================================================================
void CSceneObject::SetMtxWorld(D3DXMATRIX MtxWorld)
{
	m_mtxWorld = MtxWorld;
}

//=============================================================================
// オブジェクトの大きさ処理
//=============================================================================
void CSceneObject::VtxMinMaxSet(void)
{
	int nNumVtex;	//頂点数
	DWORD sizeFvF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ
	D3DXVECTOR3 vtx;

	m_VtxMinModel = D3DXVECTOR3(10000, 0, 10000);
	m_VtxMaxModel = D3DXVECTOR3(-10000, 0, -10000);

	//頂点数を取得
	nNumVtex = m_pMeshModel->GetNumVertices();
	//頂点フォーマットのサイズを取得
	sizeFvF = D3DXGetFVFVertexSize(m_pMeshModel->GetFVF());
	//頂点　ロック
	m_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);
	for (int nCntVtx = 0; nCntVtx < nNumVtex; nCntVtx++)
	{	//頂点座標の代入
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;
		if (m_VtxMinModel.x > vtx.x)
		{
			m_VtxMinModel.x = vtx.x;
		}
		if (m_VtxMinModel.y > vtx.y)
		{
			m_VtxMinModel.y = vtx.y;
		}
		if (m_VtxMinModel.z > vtx.z)
		{
			m_VtxMinModel.z = vtx.z;
		}

		if (m_VtxMaxModel.x < vtx.x)
		{
			m_VtxMaxModel.x = vtx.x;
		}
		if (m_VtxMaxModel.y < vtx.y)
		{
			m_VtxMaxModel.y = vtx.y;
		}
		if (m_VtxMaxModel.z < vtx.z)
		{
			m_VtxMaxModel.z = vtx.z;
		}
		pVtxBuff += sizeFvF;
	}
	//頂点バッファをアンロック
	m_pMeshModel->UnlockVertexBuffer();
}

//=============================================================================
// 回転の設定処理
//=============================================================================
D3DXVECTOR3 CSceneObject::Getrot(void)
{
	return m_rot;
}

//=============================================================================
// 位置の設定処理
//=============================================================================
D3DXVECTOR3 CSceneObject::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 影の設定処理
//=============================================================================
void CSceneObject::SetbShadow(bool bShadow)
{
	m_bShadow = bShadow;
}
