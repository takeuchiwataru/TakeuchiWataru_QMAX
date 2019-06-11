//=============================================================================
//
// メッシュフィールド処理処理 [meshField.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "meshFieldBG.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\field004.jpg"	// 地面のテクスチャ名
#define MESHFIELD_SIZE_X		(10.0f)							// 地面大きさ
#define MESHFIELD_SIZE_Z		(10.0f)							// 地面大きさ
#define POLYGON_X				(50)							// ポリゴンの数（X）
#define POLYGON_Z				(50)							// ポリゴンの数（Z）
#define FILE_NAME				("data\\高さ.bin")
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
//LPDIRECT3DVERTEXBUFFER9		CSceneMeshFieldBG::m_pVtxBuff = NULL;

//グローバル
//float g_aHeght[10 + 1][1 + 1] = { 0 };
float g_aHeght[POLYGON_X][POLYGON_Z] = { 0 };

//--------------------------------------------
//シーンメッシュフィールドクラス コンストラクタ
//--------------------------------------------
CSceneMeshFieldBG::CSceneMeshFieldBG() : CScene(4, CScene::OBJTYPE_MESHFIELD)
{
	m_MeshFiled = {};						//シーン3D構造体
	m_pTexture = NULL;						//テクスチャへのポインタ
	m_pIdxBuffMeshField = NULL;				// インデックスバッファへのポインタ
	m_mtxWorldMeshField = {};				// ワールドマトリックス
	m_nNumVerTexMeshField = 0;				// 頂点数
	m_nNumIndexMeshField = 0;				// インデックス数
	m_nNumPolygonMeshField = 0;				// ポリゴン数
	m_nSplitX = 0;
	m_nSplitZ = 0;
	m_fWidth = 0;
	m_fDepth = 0;

}

//--------------------------------------------
//シーンメッシュフィールドクラスクラス デストラクタ
//--------------------------------------------
CSceneMeshFieldBG::~CSceneMeshFieldBG()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CSceneMeshFieldBG * CSceneMeshFieldBG::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitZ)
{
	CSceneMeshFieldBG *pMeshFiled;

	pMeshFiled = new CSceneMeshFieldBG;

	pMeshFiled->m_Pos = pos;
	pMeshFiled->m_fWidth = fWidth;
	pMeshFiled->m_fDepth = fDepth;
	pMeshFiled->m_nSplitX = nSplitX;
	pMeshFiled->m_nSplitZ = nSplitZ;
	pMeshFiled->Init();

	return pMeshFiled;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneMeshFieldBG::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

												// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	// 頂点情報の作成
	MakeVertexMeshField(pDevice);

	// ポリゴンの情報を設定
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MeshFiled.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MeshFiled.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//ファイルをロード
	LoadHeight();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void  CSceneMeshFieldBG::Uninit(void)
{
	// テクスチャの破棄
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
	if (m_pIdxBuffMeshField != NULL)
	{
		m_pIdxBuffMeshField->Release();
		m_pIdxBuffMeshField = NULL;
	}

	//自分を消す(メッシュフィールドを破棄)
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void  CSceneMeshFieldBG::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	int nVtxCounter = 0;

	////ファイルにセーブ
	//if (pInput->GetPress(DIK_RSHIFT) == true)
	//{
	//	SaveHeight();
	//}



	////任意のキー1
	//if (pInput->GetTrigger(DIK_2) == true)
	//{
	//	//m_nSelectVtx += 1;
	//}
	////任意のキー2
	//if (pInput->GetTrigger(DIK_1) == true)
	//{
	//	//m_nSelectVtx -= 1;
	//}
//
//	VERTEX_3D *pVtx;
//	//頂点バッファをロック
//	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
//#ifdef  _DEBUG
//	//CDebugProc::Print(1, " pvtx[%d]  : ( %.1f ,%.1f ,%.1f )\n", m_nSelectVtx, pVtx[m_nSelectVtx].nor.x, pVtx[m_nSelectVtx].nor.y, pVtx[m_nSelectVtx].nor.z);
//#endif
//	// 頂点バッファをアンロックする
//	m_pVtxBuff->Unlock();
//
}

//=============================================================================
// 描画処理
//=============================================================================
void  CSceneMeshFieldBG::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldMeshField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_MeshFiled.rot.y, m_MeshFiled.rot.x, m_MeshFiled.rot.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_Pos.x, m_Pos.y, m_Pos.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorldMeshField);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVerTexMeshField, 0, m_nNumPolygonMeshField);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void CSceneMeshFieldBG::MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxZ;
	int nCntVtxX;
	int nCntIdxZ;
	int nCntIdxX;
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	// 頂点数
	m_nNumVerTexMeshField = (POLYGON_X + 1) * (POLYGON_Z + 1);

	// インデックス数
	m_nNumIndexMeshField = (POLYGON_X + 1) * (POLYGON_Z + 1) + (2 * (POLYGON_Z - 1)) + (POLYGON_X + 1) * (POLYGON_Z - 1);

	// ポリゴン数
	m_nNumPolygonMeshField = m_nNumIndexMeshField - 2;


	D3DXVECTOR3 pos[10000];


	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVerTexMeshField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndexMeshField,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,						// 16ビットのデータを確保
		D3DPOOL_MANAGED,
		&m_pIdxBuffMeshField,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxZ = 0; nCntVtxZ < POLYGON_Z + 1; nCntVtxZ++)
	{
		for (nCntVtxX = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
		{
			// 頂点座標の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].pos = D3DXVECTOR3(m_Pos.x + (nCntVtxX * m_fWidth), m_Pos.y, m_Pos.z - (nCntVtxZ * m_fDepth));
			// 法線の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// 頂点カラーの設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ座標の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].tex = D3DXVECTOR2(0.0f + (nCntVtxX/* * (1.0f / POLYGON_X)*/), 0.0f + (nCntVtxZ /** (1.0f / POLYGON_Z)*/));
		}
		nVtxCounter += POLYGON_X;
	}

#if 0
	//法線用
	D3DXVECTOR3 Vec0, Vec1, nor0, nor1;
	int nVtx = 0;

	for (int nCntZ = 0, nCntPolygon = 0, nCntVtx = 0; nCntZ < POLYGON_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 Vec0, Vec1, Vec2;
			D3DXVECTOR3 nor;

			pPos0 = &pVtx[(nCntZ + nCntX + nCntVtx)].pos;
			pPos1 = &pVtx[(nCntZ + nCntX + nCntVtx) + POLYGON_Z + 1].pos;
			pPos2 = &pVtx[(nCntZ + nCntX + nCntVtx) + POLYGON_Z + 2].pos;
			pPos3 = &pVtx[(nCntZ + nCntX + nCntVtx) + 1].pos;

			//一方のポリゴンの2つのベクトルから法線を算出
			Vec0 = *pPos1 - *pPos0;
			Vec1 = *pPos2 - *pPos0;
			// X,Y,Zの順で↓
			D3DXVec3Cross(&nor, &Vec1, &Vec0);
			//正規化
			D3DXVec3Normalize(&nor, &nor);
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntPolygon)] = nor;

			//もう一方のポリゴンのベクトルから法線を算出
			Vec1 = *pPos2 - *pPos0;
			Vec2 = *pPos3 - *pPos0;
			// X,Y,Zの順で↓
			D3DXVec3Cross(&nor, &Vec2, &Vec1);
			//正規化
			D3DXVec3Normalize(&nor, &nor);
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntPolygon) + 1] = nor;
		}
		nCntPolygon += POLYGON_X * 2 - 2;
		nCntVtx += POLYGON_X;
	}

	//法線の平均
	for (int nCntZ = 0, nCntPolygon = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{
			if (nCntZ == 0)
			{	//上
				if (nCntX == 0)
				{	//左端
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntX > 0 && nCntX < POLYGON_X)
				{	//中 頂点が3重なる
					pVtx[nCntX].nor = (m_aNor[(nCntX * 2) - 1] + m_aNor[(nCntX * 2) - 1 + 1]
						+ m_aNor[(nCntX * 2) - 1 + 2]) / 3;
				}
				else if (nCntX == POLYGON_X)
				{	//右端
					pVtx[POLYGON_X].nor = m_aNor[POLYGON_X * 2 - 1];
				}
			}
			else if (nCntZ > 0 && nCntZ < POLYGON_Z)
			{//中
				if (nCntX == 0)
				{	//左端
					pVtx[((POLYGON_X + 1) * nCntZ)].nor =
						(m_aNor[(nCntZ)*(POLYGON_X * 2) - (POLYGON_X * 2)]
							+ m_aNor[(nCntZ)*(POLYGON_X * 2)]
							+ m_aNor[(nCntZ)*(POLYGON_X * 2) + 1]) / 3;
				}
				else if (nCntX == POLYGON_X)
				{	//右端
					pVtx[((nCntZ + 1) * POLYGON_X) + nCntZ].nor =
						(m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1)))]	//2
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1))) + 1]		//3
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1))) + ((POLYGON_X * 2) + 1)]) / 3;	//7
				}
				else
				{	//中 頂点が6重なる
					pVtx[(POLYGON_X + 1 + nCntX) + ((nCntZ - 1) * (POLYGON_X + 1))].nor = (
						m_aNor[(nCntZ - 1) * (POLYGON_X * 2)]
						+ m_aNor[(nCntZ - 1) * (POLYGON_X * 2) + 1]
						+ m_aNor[(nCntZ - 1) * (POLYGON_X * 2) + 2]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2))]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + 1]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + 2]) / 6;
				}
			}
			else if (nCntZ == POLYGON_Z)
			{//下
				if (nCntX == 0)
				{	//左端
					pVtx[(POLYGON_X + 1) * POLYGON_Z].nor = m_aNor[POLYGON_X * (POLYGON_Z - 1) * 2];
				}
				else if (nCntX > 0 && nCntX < POLYGON_X)
				{	//中 頂点が3重なる
					pVtx[nCntZ * POLYGON_X + nCntX].nor = (m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + nCntX]
						+ m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + nCntX + 1]
						+ m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + nCntX + 2]) / 3;
				}
				else if (nCntX == POLYGON_X)
				{	//右端
					pVtx[POLYGON_X * POLYGON_Z + (POLYGON_X + POLYGON_Z)].nor
						= (m_aNor[POLYGON_X * POLYGON_Z * 2 - 2] + m_aNor[POLYGON_X * POLYGON_Z * 2 - 1]) / 2;;
				}
			}
		}
	}

#endif

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	NormalSet();


	// インデックスデータへのポインタ
	WORD *pIdx;
	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	m_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxZ = 0; nCntIdxZ < POLYGON_Z; nCntIdxZ++)
	{
		for (nCntIdxX = 0; nCntIdxX < POLYGON_X + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + POLYGON_X + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxZ < POLYGON_Z - 1 && nCntIdxX == POLYGON_X)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (POLYGON_X + 1) + 1;
				pIdx += 2;
			}
		}
	}
	// インデックスバッファをアンロック
	m_pIdxBuffMeshField->Unlock();
}

//=============================================================================
// メッシュフィールドの変更処理
//=============================================================================
void CSceneMeshFieldBG::SetHeight(D3DXVECTOR3 pos, float fValue, float fRange)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0, nCntVtx = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{
			//POSから対象の頂点までの距離
			float fLength = sqrtf(
				//Xの距離を求める　Xの距離の2乗
				(pos.x - pVtx->pos.x) * (pos.x - pVtx->pos.x)
				//Zの距離を求める　Zの距離の2乗
				+ (pos.z - pVtx->pos.z) * (pos.z - pVtx->pos.z));
			if (fLength <= fRange)
			{	//範囲内での距離の応じた高さ
				//			コサインカーブ上の部分 * 比率(%)
				float fHeight = cosf((D3DX_PI * 0.5f) * (fLength / fRange)) * fValue;
				pVtx->pos.y += fHeight;
			}
			//保存
			g_aHeght[nCntZ][nCntX] = pVtx->pos.y;
			pVtx++;
		}
	}
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	NormalSet();
}

//=============================================================================
// セーブ処理
//=============================================================================
void CSceneMeshFieldBG::SaveHeight(void)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//ファイル
	FILE *pFile;

	//書き込み
	pFile = fopen(FILE_NAME, "wb");
	//NULLチェック
	if (pFile != NULL)
	{	//ファイル読み込み
		fwrite(&g_aHeght[0][0], sizeof(float), POLYGON_X * POLYGON_Z, pFile);
	}
	else
	{	//ファイルが開けなかった
		printf("ファイルが開けませんでした\n");
	}
	//ファイルを閉じる
	fclose(pFile);
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
//=============================================================================
// ロード処理
//=============================================================================
void CSceneMeshFieldBG::LoadHeight(void)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//ファイル
	FILE *pFile;

	//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME, "rb");
	//NULLチェック
	if (pFile != NULL)
	{	//ファイル読み込み
		fread(&g_aHeght[0][0], sizeof(float), POLYGON_X * POLYGON_Z, pFile);
	}
	else
	{	//ファイルが開けなかった
		printf("ファイルが開けませんでした\n");
	}
	//ファイルを閉じる
	fclose(pFile);
	//高さを代入

	for (int nCntZ = 0, nCntVtx = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{
			//保存
			 pVtx->pos.y = g_aHeght[nCntZ][nCntX];
			pVtx++;
		}
	}
	//for (int nCntZ = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	//{
	//	for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
	//	{
	//		pVtx->pos.y = g_aHeght[nCntZ][nCntX];
	//		pVtx++;
	//	}
	//}
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	//法線の更新
	NormalSet();
}

//=============================================================================
// 位置設定処理
//=============================================================================
void CSceneMeshFieldBG::Setpos(D3DXVECTOR3 pos)
{
}

//=============================================================================
// 頂点取得処理
//=============================================================================
//LPDIRECT3DVERTEXBUFFER9 CSceneMeshFieldBG::GetVtx(void)
//{
//	return m_pVtxBuff;
//}

//=============================================================================
// 地面の高さを返す
//=============================================================================
float CSceneMeshFieldBG::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;

#if 1
	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fGaiseki;
	int nVtx[4];
	int nPolyNumX, nPolyNumZ;

	//三角形用
	D3DXVECTOR3 nor0, nor1, Vec0, Vec1,Vec2,Vec3;

	//どのポリゴンに乗っているか求める
	nPolyNumX = ((int)(pos.x / m_fWidth));
	nPolyNumZ = ((int)(pos.z / m_fDepth));

	nPolyNumZ *= -1;

	//プレイヤーがどこの頂点をつかっているか
	nVtx[0] = nPolyNumX + (nPolyNumZ + 1) * (POLYGON_X + 1);		//左下
	nVtx[1] = nPolyNumX + (nPolyNumZ * (POLYGON_X + 1));			//左上
	nVtx[2] = (nPolyNumX + 1) + (nPolyNumZ + 1) * (POLYGON_X + 1);	//右下
	nVtx[3] = (nPolyNumX + 1) + (nPolyNumZ * (POLYGON_X + 1));		//右上

	//ポリゴンの真ん中斜め
	Vec0 = pVtx[nVtx[1]].pos - pVtx[nVtx[2]].pos;
	//プレイヤーがどっちに乗っているか
	Vec1 = pos - pVtx[nVtx[2]].pos;
	//外積
	fGaiseki = (Vec0.z * Vec1.x) - (Vec0.x * Vec1.z);
	//三角形の範囲格納用
	D3DXVECTOR3 sankaku[3];;

	if (fGaiseki <= 0)
	{	//範囲（左側）
		sankaku[0] = pVtx[nVtx[0]].pos;
		sankaku[1] = pVtx[nVtx[1]].pos;
		sankaku[2] = pVtx[nVtx[2]].pos;
	}
	else
	{	//範囲（右側）
		sankaku[0] = pVtx[nVtx[3]].pos;
		sankaku[1] = pVtx[nVtx[2]].pos;
		sankaku[2] = pVtx[nVtx[1]].pos;
	}

	float fPosY;
	//Y座標を０に 斜めの上り幅
	fPosY = sankaku[0].y;

	sankaku[0].y -= fPosY;
	sankaku[1].y -= fPosY;
	sankaku[2].y -= fPosY;

	//法線を求める
	Vec2 = sankaku[1] - sankaku[0];
	Vec3 = sankaku[2] - sankaku[0];
	//正規化する
	D3DXVec3Cross(&nor0, &Vec2, &Vec3);
	D3DXVec3Normalize(&nor0, &nor0);
	//プレイヤーの位置を求める
	D3DXVECTOR3 PlayerPos = pos - sankaku[0];

	//内積の計算
	m_Height = (-(nor0.x * PlayerPos.x) - (nor0.z * PlayerPos.z)) / nor0.y + fPosY;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
#endif
	return m_Height;
}

//=============================================================================
// 法線の設定
//=============================================================================
void CSceneMeshFieldBG::NormalSet(void)
{
#if 1
	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ
						// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//法線を求める

	//法線用
	D3DXVECTOR3 Vec0, Vec1, nor0, nor1;
	int Testvec0, Testvec1;

	for (int nCntZ = 0, nCntPolygon = 0, nCntNorPolygon = 0; nCntZ < POLYGON_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 Vec0, Vec1, Vec2;
			D3DXVECTOR3 nor;

			pPos0 = &pVtx[(nCntZ + nCntX + nCntPolygon)].pos;
			pPos1 = &pVtx[(nCntZ + nCntX + nCntPolygon) + POLYGON_X + 1].pos;
			pPos2 = &pVtx[(nCntZ + nCntX + nCntPolygon) + POLYGON_X + 2].pos;
			pPos3 = &pVtx[(nCntZ + nCntX + nCntPolygon) + 1].pos;

			//一方のポリゴンの2つのベクトルから法線を算出
			Vec0 = *pPos1 - *pPos0;
			Vec1 = *pPos2 - *pPos0;
			Vec2 = *pPos3 - *pPos0;

			// X,Y,Zの順で↓
			D3DXVec3Cross(&nor, &Vec1, &Vec0);
			//正規化
			D3DXVec3Normalize(&nor, &nor);
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntNorPolygon)] = nor;
			Testvec0 = ((nCntZ * 2) + (nCntX * 2) + nCntNorPolygon);

			// X,Y,Zの順で↓
			D3DXVec3Cross(&nor, &Vec2, &Vec1);
			//正規化
			D3DXVec3Normalize(&nor, &nor);
			m_aNor[((nCntZ * 2) + (nCntX * 2) + nCntNorPolygon) + 1] = nor;
			Testvec1 = ((nCntZ * 2) + (nCntX * 2) + nCntNorPolygon) + 1;
		}
		nCntPolygon += POLYGON_X;
		nCntNorPolygon += (POLYGON_X * 2) - 2;
	}

	//確認用変数
	int test, test2, test3, test4, test5, test6,VtxNum;
	//法線の平均
	for (int nCntZ = 0, nCntPolygon = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{

			if (nCntZ == 0)
			{	//上
				if (nCntX == 0)
				{	//左端
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntX > 0 && nCntX < POLYGON_X)
				{	//中 頂点が3重なる
					pVtx[nCntX].nor = (m_aNor[(nCntX * 2) - 1] + m_aNor[(nCntX * 2) - 1 + 1]
						+ m_aNor[(nCntX * 2) - 1 + 2]) / 3;
				}
				else if (nCntX == POLYGON_X)
				{	//右端
					pVtx[POLYGON_X].nor = m_aNor[POLYGON_X * 2 - 1];
				}
			}
			else if (nCntZ > 0 && nCntZ < POLYGON_Z)
			{//中
				if (nCntX == 0)
				{	//左端
					pVtx[((POLYGON_X + 1) * nCntZ)].nor =
						(m_aNor[(nCntZ)*(POLYGON_X * 2) - (POLYGON_X * 2)]
							+ m_aNor[(nCntZ)*(POLYGON_X * 2)]
							+ m_aNor[(nCntZ)*(POLYGON_X * 2) + 1]) / 3;
				}
				else if (nCntX == POLYGON_X)
				{	//右端
					pVtx[((nCntZ + 1) * POLYGON_X) + nCntZ].nor =
						(m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1)))]	//2
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1))) + 1]		//3
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntZ - 1))) + ((POLYGON_X * 2) + 1)]) / 3;	//7
				}
				else
				{	//中 頂点が6重なる
					pVtx[(POLYGON_X + 1 + nCntX) + ((nCntZ - 1) * (POLYGON_X + 1))].nor = (
						m_aNor[(nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2)]
						+ m_aNor[(nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2) + 2]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2)]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2) + 2]) / 6;

					test  = (nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2);
					test2 = (nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2) + 1;
					test3 = (nCntZ - 1) * (POLYGON_X * 2) + ((nCntX - 1) * 2) + 2;

					test4 = (((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2);
					test5 = (((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2) + 1;
					test6 = (((POLYGON_X * 2) + 1) + (nCntZ - 1) * (POLYGON_X * 2)) + ((nCntX - 1) * 2) + 2;
					VtxNum = (POLYGON_X + 1 + nCntX) + ((nCntZ - 1) * (POLYGON_X + 1));
				}
			}
			else if (nCntZ == POLYGON_Z)
			{//下
				if (nCntX == 0)
				{	//左端
					pVtx[(POLYGON_X + 1) * POLYGON_Z].nor = m_aNor[POLYGON_X * (POLYGON_Z - 1) * 2];
				}
				else if (nCntX > 0 && nCntX < POLYGON_X)
				{	//中 頂点が3重なる
					pVtx[nCntZ * POLYGON_X + nCntX].nor
						= (m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2)]
						+ m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2) + 2]) / 3;

					///test = (POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2);
					//test2 = (POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2) + 1;
					//test3 = (POLYGON_X * 2) * (POLYGON_Z - 1) + ((nCntX - 1) * 2) + 2;
				}
				else if (nCntX == POLYGON_X)
				{	//右端
					pVtx[POLYGON_X * POLYGON_Z + (POLYGON_X + POLYGON_Z)].nor
						= (m_aNor[POLYGON_X * POLYGON_Z * 2 - 2]
							+ m_aNor[POLYGON_X * POLYGON_Z * 2 - 1]) / 2;

					test = POLYGON_X * POLYGON_Z * 2 - 2;
					test2 = POLYGON_X * POLYGON_Z * 2 - 1;
				}
			}
		}
	}
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

#endif
}
