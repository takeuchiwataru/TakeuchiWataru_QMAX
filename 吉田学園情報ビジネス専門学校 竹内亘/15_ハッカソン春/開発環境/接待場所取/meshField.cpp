//=============================================================================
//
// メッシュフィールド処理処理 [meshField.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "meshField.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME	"data\\TEXTURE\\FIELD\\field004.jpg"	// 地面のテクスチャ名
#define MESHFIELD_SIZE_X		(300.0f)								// 地面大きさ
#define MESHFIELD_SIZE_Z		(300.0f)								// 地面大きさ
#define POLYGON_X				(10)									// ポリゴンの数（X）
#define POLYGON_Z				(10)									// ポリゴンの数（Z）
#define FILE_NAME				("高さ.bin")

//グローバル
float g_aHeght[POLYGON_X][POLYGON_Z] = {0};

//--------------------------------------------
//シーンメッシュフィールドクラス コンストラクタ
//--------------------------------------------
CSceneMeshField::CSceneMeshField() : CScene(3, CScene::OBJTYPE_MESHFIELD)
{
	m_pTexture = NULL;						//テクスチャへのポインタ
	m_pIdxBuffMeshField = NULL;				// インデックスバッファへのポインタ
	D3DXMatrixIdentity(&m_mtxWorldMeshField);		//ワールドマトリックス
	m_nNumVerTexMeshField = 0;				// 頂点数
	m_nNumIndexMeshField = 0;				// インデックス数
	m_nNumPolygonMeshField = 0;				// ポリゴン数
	m_nSplitX = 0;
	m_nSplitZ = 0;
}

//--------------------------------------------
//シーンメッシュフィールドクラスクラス デストラクタ
//--------------------------------------------
CSceneMeshField::~CSceneMeshField()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CSceneMeshField * CSceneMeshField::Create(D3DXVECTOR3 pos, float fWidth, float fDepth, int nSplitX, int nSplitZ)
{
	CSceneMeshField *pMeshFiled;

	pMeshFiled = NULL;

	pMeshFiled = new CSceneMeshField;

	pMeshFiled->m_pos = pos;
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
HRESULT CSceneMeshField::Init(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pTexture = NULL;						//テクスチャへのポインタ
	m_pVtxBuff = NULL;
	m_pIdxBuffMeshField = NULL;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	// 頂点情報の作成
	MakeVertexMeshField(pDevice);

	// ポリゴンの情報を設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void  CSceneMeshField::Uninit(void)
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
void  CSceneMeshField::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void  CSceneMeshField::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorldMeshField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorldMeshField, &m_mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
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
void CSceneMeshField::MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	int nVtxCounter = 0;
	int nIdxCounter = 0;
	int nCntIdxZ;
	int nCntIdxX;
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	// 頂点数
	m_nNumVerTexMeshField = (m_nSplitX + 1) * (m_nSplitZ + 1);

	// インデックス数
	m_nNumIndexMeshField = (m_nSplitX + 1) * (m_nSplitZ + 1) + (2 * (m_nSplitZ - 1)) + (m_nSplitX + 1) * (m_nSplitZ - 1);

	// ポリゴン数
	m_nNumPolygonMeshField = m_nNumIndexMeshField - 2;

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

	//変数宣言
	int nCntMeshZ;
	int nCntMeshX;

	//頂点、法線、カラー、テクスチャの頂点設定
	for (nCntMeshZ = 0; nCntMeshZ <= m_nSplitZ; nCntMeshZ++)
	{//縦軸
		for (nCntMeshX = 0; nCntMeshX <= m_nSplitX; nCntMeshX++)
		{//横軸
		 // 頂点の座標
			pVtx[0].pos = D3DXVECTOR3(((nCntMeshX * m_fWidth) / m_nSplitX), 0.0f/*rand() % 100 * 1.0f*/, ((nCntMeshZ * -m_fDepth) / m_nSplitZ));

			// 法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(nCntMeshX * 1.0f, nCntMeshZ * 1.0f);

			pVtx += 1;
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
	// 法線設定
	//NormalSet();

	// インデックスデータへのポインタ
	WORD *pIdx;
	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	m_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxZ = 0; nCntIdxZ < m_nSplitZ; nCntIdxZ++)
	{
		for (nCntIdxX = 0; nCntIdxX < m_nSplitX + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + m_nSplitX + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxZ < m_nSplitZ - 1 && nCntIdxX == m_nSplitX)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (m_nSplitX + 1) + 1;
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
void CSceneMeshField::SetHeight(D3DXVECTOR3 pos, float fValue, float fRange)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0, nCntVtx = 0; nCntZ < m_nSplitZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
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
}

//=============================================================================
// 位置設定処理
//=============================================================================
void CSceneMeshField::Setpos(D3DXVECTOR3 pos)
{
}

//=============================================================================
// 地面の高さを返す(ブールを返す)
//=============================================================================
bool CSceneMeshField::GetHeightbool(D3DXVECTOR3 &pos)
{
#if 1
	//変数宣言
	D3DXVECTOR3 vec0;
	D3DXVECTOR3 vec1;
	D3DXVECTOR3 nor;
	D3DXVECTOR3 VtxPos[3];
	D3DXVECTOR3 VtxNor[6];
	int			nNumber;
	float		fHeight;

	//プレイヤーとメッシュフィールドの位置の差分を出す
	D3DXVECTOR3 posMtx = pos - m_pos;

	int test1, test2;
	test1 = m_nSplitX;
	test2 = m_nSplitZ;
	//現在プレイヤーが何ブロック目にいるかを確認する式
	int			nMeshX = (int)((posMtx.x) / (m_fWidth / m_nSplitX));
	int			nMeshZ = (int)((posMtx.z) / (m_fDepth / m_nSplitZ) * -1);

	if (nMeshX >= m_nSplitX || nMeshX < 0)
	{
		return false;
	}
	if (nMeshZ >= m_nSplitZ || nMeshZ < 0)
	{
		return false;
	}

	//現在の乗っかっているブロックの頂点の出し方
	int			nMeshLU = nMeshX + nMeshZ * (m_nSplitX + 1);					//例　0番目の頂点
	int			nMeshRU = (nMeshX + 1) + nMeshZ * (m_nSplitX + 1);			//例　1番目の頂点
	int			nMeshLD = nMeshX + (nMeshZ + 1) * (m_nSplitX + 1);			//例　3番目の頂点
	int			nMeshRD = (nMeshX + 1) + (nMeshZ + 1) * (m_nSplitX + 1);		//例　4番目の頂点

																			//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (posMtx.x < 0 || posMtx.x > pVtx[m_nSplitX].pos.x)
	{
		return false;
	}
	if (posMtx.z > 0 || posMtx.z > pVtx[m_nSplitX].pos.z)
	{
		return false;
	}

	//CDebugProc::Print(1,"現在のブロック　横に %d　ブロック目\n", nMeshX);
	//CDebugProc::Print(1,"現在のブロック　縦に %d　ブロック目\n", nMeshZ);

	//ベクトル計算式 目的 - 現在
	vec0 = pVtx[nMeshLU].pos - pVtx[nMeshRD].pos;
	//ベクトル計算式 自分の位置　- 現在
	vec1 = posMtx - pVtx[nMeshRD].pos;

	if ((vec0.x * vec1.z) - (vec0.z * vec1.x) <= 0)
	{//三角形より右にいる場合
	//	CDebugProc::Print(1,"MeshField△右範囲 : TURE\n");
		vec0 = (posMtx - pVtx[nMeshLU].pos);

		//各頂点の保管
		VtxPos[0] = pVtx[nMeshRU].pos;
		VtxPos[1] = pVtx[nMeshRD].pos;
		VtxPos[2] = pVtx[nMeshLU].pos;

		nNumber = 3;
	}
	else if ((vec0.x * vec1.z) - (vec0.z * vec1.x) >= 0)
	{//三角形より左にいる場合
	//	CDebugProc::Print(1,"MeshField△左範囲 : TURE\n");
		vec0 = (posMtx - pVtx[nMeshRD].pos);

		//各頂点の保管
		VtxPos[0] = pVtx[nMeshLD].pos;
		VtxPos[1] = pVtx[nMeshLU].pos;
		VtxPos[2] = pVtx[nMeshRD].pos;

		nNumber = 0;
	}

	//引く法線を引く前に保存する
	fHeight = VtxPos[0].y;

	//3頂点に0の値をひいてあげて法線とプレイヤーのベクトルを直交させるため
	VtxPos[2].y -= VtxPos[0].y;
	VtxPos[1].y -= VtxPos[0].y;
	VtxPos[0].y -= VtxPos[0].y;

	//法線の計算
	vec0 = VtxPos[1] - VtxPos[0];
	vec1 = VtxPos[2] - VtxPos[0];

	//外積の計算
	D3DXVec3Cross(&nor, &vec0, &vec1);
	//正規化
	D3DXVec3Normalize(&nor, &nor);
	//プレイヤーへのベクトル
	vec0 = posMtx - VtxPos[0];
	//内積公式
	((vec0.x * pVtx[nNumber].nor.x) + (vec0.y * pVtx[nNumber].nor.y) + (vec0.z * pVtx[nNumber].nor.z));
	//内積計算式
	vec0.y = (-(vec0.x * nor.x) - (vec0.z * nor.z)) / nor.y;
	//プレイヤーのyに入れる
	posMtx.y = vec0.y + fHeight + m_pos.y;
	//頂点バッファのアンロックする
	m_pVtxBuff->Unlock();

	if (pos.y < posMtx.y)
	{// プレイヤーを地面に乗せる
		pos.y = posMtx.y;
		return true;
	}
	return false;
#endif
}

//=============================================================================
// 法線の設定
//=============================================================================
void CSceneMeshField::NormalSet(void)
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

	for (int nCntZ = 0, nCntPolygon = 0, nCntNorPolygon = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 Vec0, Vec1, Vec2;
			D3DXVECTOR3 nor;

			pPos0 = &pVtx[(nCntZ + nCntX + nCntPolygon)].pos;
			pPos1 = &pVtx[(nCntZ + nCntX + nCntPolygon) + m_nSplitX + 1].pos;
			pPos2 = &pVtx[(nCntZ + nCntX + nCntPolygon) + m_nSplitX + 2].pos;
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
		nCntPolygon += m_nSplitX;
		nCntNorPolygon += (m_nSplitX * 2) - 2;
	}

	//確認用変数
	int test, test2, test3, test4, test5, test6,VtxNum;
	//法線の平均
	for (int nCntZ = 0, nCntPolygon = 0; nCntZ < m_nSplitZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
		{

			if (nCntZ == 0)
			{	//上
				if (nCntX == 0)
				{	//左端
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntX > 0 && nCntX < m_nSplitX)
				{	//中 頂点が3重なる
					pVtx[nCntX].nor = (m_aNor[(nCntX * 2) - 1] + m_aNor[(nCntX * 2) - 1 + 1]
						+ m_aNor[(nCntX * 2) - 1 + 2]) / 3;
				}
				else if (nCntX == m_nSplitX)
				{	//右端
					pVtx[m_nSplitX].nor = m_aNor[m_nSplitX * 2 - 1];
				}
			}
			else if (nCntZ > 0 && nCntZ < m_nSplitZ)
			{//中
				if (nCntX == 0)
				{	//左端
					pVtx[((m_nSplitX + 1) * nCntZ)].nor =
						(m_aNor[(nCntZ)*(m_nSplitX * 2) - (m_nSplitX * 2)]
							+ m_aNor[(nCntZ)*(m_nSplitX * 2)]
							+ m_aNor[(nCntZ)*(m_nSplitX * 2) + 1]) / 3;
				}
				else if (nCntX == m_nSplitX)
				{	//右端
					pVtx[((nCntZ + 1) * m_nSplitX) + nCntZ].nor =
						(m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntZ - 1)))]	//2
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntZ - 1))) + 1]		//3
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntZ - 1))) + ((m_nSplitX * 2) + 1)]) / 3;	//7
				}
				else
				{	//中 頂点が6重なる
					pVtx[(m_nSplitX + 1 + nCntX) + ((nCntZ - 1) * (m_nSplitX + 1))].nor = (
						m_aNor[(nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2)]
						+ m_aNor[(nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2) + 2]
						+ m_aNor[(((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2)]
						+ m_aNor[(((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2) + 2]) / 6;

					test  = (nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2);
					test2 = (nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2) + 1;
					test3 = (nCntZ - 1) * (m_nSplitX * 2) + ((nCntX - 1) * 2) + 2;

					test4 = (((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2);
					test5 = (((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2) + 1;
					test6 = (((m_nSplitX * 2) + 1) + (nCntZ - 1) * (m_nSplitX * 2)) + ((nCntX - 1) * 2) + 2;
					VtxNum = (m_nSplitX + 1 + nCntX) + ((nCntZ - 1) * (m_nSplitX + 1));
				}
			}
			else if (nCntZ == m_nSplitZ)
			{//下
				if (nCntX == 0)
				{	//左端
					pVtx[(m_nSplitX + 1) * m_nSplitZ].nor = m_aNor[m_nSplitX * (m_nSplitZ - 1) * 2];
				}
				else if (nCntX > 0 && nCntX < m_nSplitX)
				{	//中 頂点が3重なる
					pVtx[nCntZ * m_nSplitX + nCntX].nor
						= (m_aNor[(m_nSplitX * 2) * (m_nSplitZ - 1) + ((nCntX - 1) * 2)]
						+ m_aNor[(m_nSplitX * 2) * (m_nSplitZ - 1) + ((nCntX - 1) * 2) + 1]
						+ m_aNor[(m_nSplitX * 2) * (m_nSplitZ - 1) + ((nCntX - 1) * 2) + 2]) / 3;
				}
				else if (nCntX == m_nSplitX)
				{	//右端
					pVtx[m_nSplitX * m_nSplitZ + (m_nSplitX + m_nSplitZ)].nor
						= (m_aNor[m_nSplitX * m_nSplitZ * 2 - 2]
							+ m_aNor[m_nSplitX * m_nSplitZ * 2 - 1]) / 2;

					test = m_nSplitX * m_nSplitZ * 2 - 2;
					test2 = m_nSplitX * m_nSplitZ * 2 - 1;
				}
			}
		}
	}
	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

#endif
}

//=============================================================================
// テクスチャの設定
//=============================================================================
void CSceneMeshField::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}