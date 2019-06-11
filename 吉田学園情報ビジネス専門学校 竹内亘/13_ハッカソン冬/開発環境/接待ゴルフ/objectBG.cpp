//---------------------------------------------------------------------
//	オブジェクト処理(objectBG.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "objectBG.h"
//#include "manager.h"
#include "game.h"

//#include "scene3D.h"
//#include "model.h"
#include "sceneObject.h"
#include "fade.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define PLAYER_TEXTURENAME000			"data\\TEXTURE\\GAME\\Player000.png"	//テクスチャのファイル名
#define BG_MODEL0000					"data\\MODEL\\MODELBG\\box000.x"
#define BG_MODEL000						"data\\MODEL\\MODELBG\\building102.x"
#define BG_MODEL001						"data\\MODEL\\MODELBG\\building202.x"
#define BG_MODEL002						"data\\MODEL\\MODELBG\\building302.x"
#define BG_MODEL003						"data\\MODEL\\MODELBG\\building402.x"
#define BG_MODEL004						"data\\MODEL\\MODELBG\\fence000.x"
#define BG_MODEL005						"data\\MODEL\\MODELBG\\tree000.x"
#define BG_MODEL006						"data\\MODEL\\MODELBG\\ana.x"


#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(15)		// プレイヤーの幅調整用
#define PLAYER_HEIGHT	(50.0f)		// プレイヤーの背の高さ


//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPD3DXMESH					CObjectBG::m_pMesh[MODELTYPE_MAX] = {};
LPD3DXBUFFER				CObjectBG::m_pBuffMat[MODELTYPE_MAX] = {};
LPDIRECT3DTEXTURE9			CObjectBG::m_pTexture[MODELTYPE_MAX] = {};
DWORD						CObjectBG::m_nNumMat[MODELTYPE_MAX] = {};

//--------------------------------------------
//オブジェクトクラス コンストラクタ
//--------------------------------------------
CObjectBG::CObjectBG() : CScene(3, CScene::OBJTYPE_BGMODEL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//位置
	m_posold = D3DXVECTOR3(0, 0, 0);				//前回の位置
	m_move = D3DXVECTOR3(0, 0, 0);					//移動量
	m_ModelMove = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);					//向き
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_nCollision = 0;
	m_nCount = 0;
	m_Type = CObjectBG::MODELTYPE_BILL000;
	m_nMoveType = MOVETYPE_NONE;
}

//--------------------------------------------
//オブジェクトクラス デストラクタ
//--------------------------------------------
CObjectBG::~CObjectBG()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CObjectBG *CObjectBG::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, MODELTYPE type, MOVETYPE nMovetype, int nCollision)
{
	//オブジェクトポインタ
	CObjectBG *pObjectBG;
	pObjectBG = new CObjectBG;
	//タイプの設定
	pObjectBG->m_Type = type;

	//初期値が入った後 pos代入
	pObjectBG->m_pos = pos;

	//オブジェクトの初期化
	pObjectBG->Init();

	//移動量の設定
	pObjectBG->m_move = move;
	//移動方向の設定
	pObjectBG->m_nMoveType = nMovetype;

	//コリジョンタイプ代入
	pObjectBG->m_nCollision = nCollision;

	//オブジェクトの情報を返す
	return pObjectBG;
}

//=============================================================================
// オブジェクトの初期化処理
//=============================================================================
HRESULT CObjectBG::Init(void)
{
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BGMODEL);

	m_rot = D3DXVECTOR3(0, D3DX_PI * 1.0f, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// 頂点バッファへのポインタ

	//モデルを生成	オフセット設定
	m_pObject = CSceneObject::Create(m_pos, m_rot);
	//モデルを割り当て
	m_pObject->BindModel(m_nNumMat[m_Type], m_pMesh[m_Type], m_pBuffMat[m_Type]);
	//モデルの親を指定
	m_pObject->SetParent(NULL);

	m_pObject->Setpos(m_pos);
	return S_OK;
}

//=============================================================================
// オブジェクトの終了処理
//=============================================================================
void CObjectBG::Uninit(void)
{
	if (m_pObject != NULL)
	{
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = NULL;
	}
	//自分を消す(オブジェクトを破棄)
	Release();
}

//=============================================================================
// オブジェクトの更新処理
//=============================================================================
void CObjectBG::Update(void)
{
#if 1

	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//カメラを取得
	//CCamera *pCamera = CManager::GetCamera();
	//過去の位置を設定
	m_posold = m_pos;


	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//向きの代入
	D3DXVECTOR3 rot = m_pObject->Getrot();

	// MOVETYPEの設定
	MOVETYPE MoveType = m_nMoveType;


	switch (m_nMoveType)
	{
	case MOVETYPE_X_MOVE:
		// X軸移動
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Y_MOVE:
		// Y軸移動
		if (m_nCount <= 120)
		{
			move.y += m_move.y;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.y -= m_move.y;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;
		break;

	case MOVETYPE_Z_MOVE:
		// Z軸移動
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		break;

	case MOVETYPE_ROTATION_X:
		// X軸で回転しながらZ軸移動
		if (m_nCount <= 120)
		{
			move.z += m_move.z;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.z -= m_move.z;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		rot.x += 0.1f;
		//rot.z += 0.01f;

		m_pObject->Setrot(rot);
		break;

	case MOVETYPE_ROTATION_Z:
		// Z軸で回転しながらX軸移動
		if (m_nCount <= 120)
		{
			move.x += m_move.x;
		}
		else if (m_nCount >= 121 && m_nCount <= 240)
		{
			move.x -= m_move.x;
		}
		else if (m_nCount == 241)
		{
			m_nCount = 0;
		}
		m_nCount++;

		//rot.x += 0.01f;
		rot.z += 0.1f;

		m_pObject->Setrot(rot);
		break;
	}


	//向きの慣性
	//m_fDiffAngle = m_fDestAngle - m_rot.y;
	////角度の設定
	//if (m_fDiffAngle > D3DX_PI)
	//{
	//	m_fDiffAngle -= D3DX_PI* 2.0f;
	//}
	//if (m_fDiffAngle < -D3DX_PI)
	//{
	//	m_fDiffAngle += D3DX_PI* 2.0f;
	//}
	//m_rot.y += m_fDiffAngle * 0.1f;
	//if (m_rot.y > D3DX_PI)
	//{
	//	m_rot.y -= D3DX_PI* 2.0f;
	//}
	//if (m_rot.y < -D3DX_PI)
	//{
	//	m_rot.y += D3DX_PI* 2.0f;
	//}

	//減速
	move.x += (0.0f - move.x) * 0.5f;
	move.z += (0.0f - move.z) * 0.5f;
	//位置更新
	m_pos += move;

	m_pObject->Setpos(m_pos);
	m_ModelMove = move;

#endif // 0
}

//=============================================================================
// オブジェクトの描画処理
//=============================================================================
void CObjectBG::Draw(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス
	D3DXMATRIX mtxParent;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//影の描画処理
	D3DXMATRIX	mtxShadow;
	D3DXPLANE	planeField;
	D3DXVECTOR4 VecLight;
	D3DXVECTOR3 pos, normal;

	CLight *pLight = CGame::GetLight();

	// ライトを無効にする
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	//減算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//シャドウマトリックスの初期化
	D3DXMatrixIdentity(&mtxShadow);
	//ライトの設定
	VecLight = D3DXVECTOR4(0.0f, 0.0f, 1.0f,0.0f);
	//影の位置設定
	pos = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
	//法線の設定
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//平面を作成
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
	//影マトリックスの設定
	D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);
	//ワールドマトリックスと掛け合わせる
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);
	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	if (m_pObject != NULL)
	{
		m_pObject->SetbShadow(true);
		m_pObject->Draw();
	}
	//レンダーステイトを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ライトを有効にする
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	if (m_pObject != NULL)
	{
		m_pObject->SetbShadow(false);
		m_pObject->Draw();
	}
}

//=============================================================================
// オブジェクトの位置設定
//=============================================================================
void CObjectBG::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CObjectBG::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

	// Xファイルの読み込み
	D3DXLoadMeshFromX(BG_MODEL000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[0], NULL, &m_nNumMat[0], &m_pMesh[0]);
	D3DXLoadMeshFromX(BG_MODEL001, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[1], NULL, &m_nNumMat[1], &m_pMesh[1]);
	D3DXLoadMeshFromX(BG_MODEL002, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[2], NULL, &m_nNumMat[2], &m_pMesh[2]);
	D3DXLoadMeshFromX(BG_MODEL003, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[3], NULL, &m_nNumMat[3], &m_pMesh[3]);
	D3DXLoadMeshFromX(BG_MODEL004, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[4], NULL, &m_nNumMat[4], &m_pMesh[4]);
	D3DXLoadMeshFromX(BG_MODEL005, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[5], NULL, &m_nNumMat[5], &m_pMesh[5]);
	D3DXLoadMeshFromX(BG_MODEL006, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[6], NULL, &m_nNumMat[6], &m_pMesh[6]);

	//テクスチャの読み込み
	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
	{
		//マテリアル情報からテクスチャの取得
		pMat = (D3DXMATERIAL*)m_pBuffMat[nCnt]->GetBufferPointer();

		//マテリアルの数回す
		for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat[nCnt]; nCntMatTex++)
		{
			if (pMat[nCntMatTex].pTextureFilename != NULL)
			{
				// テクスチャの設定
				D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
					pMat[nCntMatTex].pTextureFilename,	// ファイルの名前
					&m_pTexture[nCnt]);					// テクスチャへのポインタ
			}
		}
	}

	return S_OK;
}

//=============================================================================
// テクスチャの破棄処理
//=============================================================================
void CObjectBG::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MODELTYPE_MAX; nCnt++)
	{
		// メッシュの開放
		if (m_pMesh[nCnt] != NULL)
		{
			m_pMesh[nCnt]->Release();
			m_pMesh[nCnt] = NULL;
		}
		// マテリアルの開放
		if (m_pBuffMat[nCnt] != NULL)
		{
			m_pBuffMat[nCnt]->Release();
			m_pBuffMat[nCnt] = NULL;
		}

		//テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
//=============================================================================
// オブジェクトの位置
//=============================================================================
D3DXVECTOR3 CObjectBG::GetPos(void)
{
	return m_pos;
}


//===============================================================================
// 当たり判定
//===============================================================================
bool CObjectBG::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	//あたっているかあたってないか
	bool bLand = false;
	int nCollision = m_nCollision;
	CManager::MODE pMode = CManager::GetMode();

#if 1
	switch (m_nCollision)
	{
	case 1:

		// 各種情報の取得
		D3DXVECTOR3 ModelPos = m_pos;	// 位置
		D3DXVECTOR3 ModelMove = m_ModelMove;	// 移動量
		MOVETYPE ModelMoveType = m_nMoveType;	// 動きのタイプ

		D3DXVECTOR3 VtxMax = m_pObject->VtxMax();	// モデルの最大値
		D3DXVECTOR3 VtxMin = m_pObject->VtxMin();	// モデルの最小値

		D3DXVECTOR3 ModelMax = m_pObject->GetPos() + m_pObject->VtxMax();	// 位置込みの最大値
		D3DXVECTOR3 ModelMin = m_pObject->GetPos() + m_pObject->VtxMin();	// 位置込みの最小値

		// 移動量の保持
		if (ModelMove.x == 0.0f)
		{
			ModelMove.x = m_ModelMove.x;
		}

		if (ModelMove.y == 0.0f)
		{
			ModelMove.y = m_ModelMove.y;
		}

		if (ModelMove.z == 0.0f)
		{
			ModelMove.z = m_ModelMove.z;
		}

		if (pPos->x >= ModelMin.x - PLAYER_DEPTH && pPos->x <= ModelMax.x + PLAYER_DEPTH)
		{// Zの範囲内にいる
			if (pPos->z >= ModelMin.z - PLAYER_DEPTH && pPos->z <= ModelMax.z + PLAYER_DEPTH)
			{// Xの範囲内にいる
				if (pPosOld->y >= ModelMax.y && pPos->y <= ModelMax.y)
				{// オブジェクトの上から当たる場合
					pPos->y = ModelMax.y + abs(ModelMove.y);
					pMove->y = 0.0f;

					if (ModelMove.x != 0.0f)
					{// X移動同期
						pPos->x += ModelMove.x;
					}

					if (ModelMove.z != 0.0f)
					{// Z移動同期
						pPos->z += ModelMove.z;
					}

					bLand = true;
				}
				else if (pPosOld->y + PLAYER_HEIGHT <= ModelMin.y && pPos->y + PLAYER_HEIGHT >= ModelMin.y)
				{// オブジェクトの下から当たる場合
					pPos->y = ModelMin.y - PLAYER_HEIGHT;
					pMove->y = 0.0f;
				}

				if (!(pPos->y >= ModelMax.y) && !(pPos->y + PLAYER_HEIGHT <= ModelMin.y))
				{// オブジェクト横との当たり判定
				 CDebugProc::Print(1,"モデルの右側 : %.1f\n", ModelMax.x);
				 CDebugProc::Print(1, "モデルの左側 : %.1f\n", ModelMin.x);
				 CDebugProc::Print(1, "モデルの奥側 : %.1f\n", ModelMax.z);
				 CDebugProc::Print(1, "モデルの手前側 : %.1f\n", ModelMin.z);
				 CDebugProc::Print(1, "モデルの頂点側 : %.1f\n", ModelMax.y);
				 CDebugProc::Print(1, "モデルの足元側 : %.1f\n", ModelMin.y);

					if (ModelMoveType == MOVETYPE_X_MOVE || ModelMoveType == MOVETYPE_ROTATION_Z)
					{// X移動オブジェクト
						if (pPosOld->x - (PLAYER_DEPTH - abs(ModelMove.x)) + abs(ModelMove.x) >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// 右から抜けた場合
							pPos->x = ModelMax.x + (PLAYER_DEPTH - abs(ModelMove.x)) + abs(ModelMove.x);
							//CDebugProc::Print("MOVETYPE_X_MOVE 右\n");
						}
						else if (pPosOld->x + (PLAYER_DEPTH - abs(ModelMove.x)) - abs(ModelMove.x) <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// 左から抜けた場合
							pPos->x = ModelMin.x - (PLAYER_DEPTH - abs(ModelMove.x)) - abs(ModelMove.x);
							//CDebugProc::Print("MOVETYPE_X_MOVE 左\n");
						}

						if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// 奥から抜けた場合
							pPos->z = ModelMax.z + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE 奥\n");
						}
						else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// 手前から抜けた場合
							pPos->z = ModelMin.z - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE 手前\n");
						}
					}
					else if (ModelMoveType == MOVETYPE_Z_MOVE || ModelMoveType == MOVETYPE_ROTATION_X)
					{// Z移動オブジェクト
						if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// 右から抜けた場合
							pPos->x = ModelMax.x + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE 右\n");
						}
						else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// 左から抜けた場合
							pPos->x = ModelMin.x - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_X_MOVE 左\n");
						}

						if (pPosOld->z - (PLAYER_DEPTH - abs(ModelMove.z)) + abs(ModelMove.z) >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// 奥から抜けた場合
							pPos->z = ModelMax.z + (PLAYER_DEPTH - abs(ModelMove.z)) + abs(ModelMove.z);
							//CDebugProc::Print("MOVETYPE_X_MOVE 奥\n");
						}
						else if (pPosOld->z + (PLAYER_DEPTH - abs(ModelMove.z)) - abs(ModelMove.z) <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// 手前から抜けた場合
							pPos->z = ModelMin.z - (PLAYER_DEPTH - abs(ModelMove.z)) - abs(ModelMove.z);
							//CDebugProc::Print("MOVETYPE_X_MOVE 手前\n");
						}
					}
					else
					{// 無移動オブジェクト
						if (pPosOld->x - PLAYER_DEPTH >= ModelMax.x && pPos->x - PLAYER_DEPTH < ModelMax.x)
						{// 右から抜けた場合
							pPos->x = ModelMax.x + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT 右\n");
						}
						else if (pPosOld->x + PLAYER_DEPTH <= ModelMin.x && pPos->x + PLAYER_DEPTH > ModelMin.x)
						{// 左から抜けた場合
							pPos->x = ModelMin.x - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT 左\n");
						}

						if (pPosOld->z - PLAYER_DEPTH >= ModelMax.z && pPos->z - PLAYER_DEPTH < ModelMax.z)
						{// 奥から抜けた場合
							pPos->z = ModelMax.z + PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT 奥\n");
						}
						else if (pPosOld->z + PLAYER_DEPTH <= ModelMin.z && pPos->z + PLAYER_DEPTH > ModelMin.z)
						{// 手前から抜けた場合
							pPos->z = ModelMin.z - PLAYER_DEPTH;
							//CDebugProc::Print("MOVETYPE_NOT 手前\n");
						}
					}
				}
			}
		}
		// 位置の代入
		m_pObject->Setpos(ModelPos);
		// 移動量の代入
		m_ModelMove = ModelMove;

		break;
	}
#endif
	return bLand;
}