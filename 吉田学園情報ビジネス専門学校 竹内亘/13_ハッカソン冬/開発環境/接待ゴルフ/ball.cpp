//---------------------------------------------------------------------
//	オブジェクト処理(objectBG.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "ball.h"
//#include "manager.h"
#include "game.h"

//#include "scene3D.h"
//#include "model.h"
#include "sceneObject.h"
#include "fade.h"
#include "meshOrbit.h"
#include "UICircle.h"
#include "UIScore.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//#define PLAYER_TEXTURENAME000			"data\\TEXTURE\\GAME\\Player000.png"	//テクスチャのファイル名
#define BG_MODEL0000						"data\\MODEL\\golfboal.x"

#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(15)		// プレイヤーの幅調整用
#define PLAYER_HEIGHT	(50.0f)		// プレイヤーの背の高さ


//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPD3DXMESH					CBall::m_pMesh[MODELTYPE_MAX] = {};
LPD3DXBUFFER				CBall::m_pBuffMat[MODELTYPE_MAX] = {};
LPDIRECT3DTEXTURE9			CBall::m_pTexture[MODELTYPE_MAX] = {};
DWORD						CBall::m_nNumMat[MODELTYPE_MAX] = {};

//--------------------------------------------
//オブジェクトクラス コンストラクタ
//--------------------------------------------
CBall::CBall() : CScene(3, CScene::OBJTYPE_BGMODEL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//位置
	m_posold = D3DXVECTOR3(0, 0, 0);				//前回の位置
	m_move = D3DXVECTOR3(0, 0, 0);					//移動量
	m_ModelMove = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);					//向き
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_nCollision = 0;
	m_nCount = 0;
	m_Type = CBall::MODELTYPE_BALL;
	m_nTimer = 0;
	m_nTryTimer = 0;
	m_nPlusX = 0;
	m_nPlusZ = 0;
	m_bHit = false;
	m_bendBall = false;
}

//--------------------------------------------
//オブジェクトクラス デストラクタ
//--------------------------------------------
CBall::~CBall()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CBall *CBall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, MODELTYPE type, int nCollision)
{
	//オブジェクトポインタ
	CBall *pObjectBG;
	pObjectBG = new CBall;
	//タイプの設定
	pObjectBG->m_Type = type;

	//初期値が入った後 pos代入
	pObjectBG->m_pos = pos;

	//オブジェクトの初期化
	pObjectBG->Init();

	//移動量の設定
	pObjectBG->m_move = move;

	//コリジョンタイプ代入
	pObjectBG->m_nCollision = nCollision;

	//オブジェクトの情報を返す
	return pObjectBG;
}

//=============================================================================
// オブジェクトの初期化処理
//=============================================================================
HRESULT CBall::Init(void)
{
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BGMODEL);

	m_rot = D3DXVECTOR3(0, D3DX_PI * 1.0f, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// 頂点バッファへのポインタ
	m_bJump = false;
	m_nTimer = 0;
	m_nPlusX = 0;
	m_nPlusZ = 0;
	m_nTryTimer = 0;
	m_bHit = false;
	m_bendBall = false;


	//モデルを生成	オフセット設定
	m_pObject = CSceneObject::Create(m_pos, m_rot);
	//モデルを割り当て
	m_pObject->BindModel(m_nNumMat[m_Type], m_pMesh[m_Type], m_pBuffMat[m_Type]);
	//モデルの親を指定
	m_pObject->SetParent(NULL);

	m_pObject->Setpos(m_pos);

	//軌跡
	m_pMeshOrbit = CMeshOrbit::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 5.0f, m_pos.z));
	m_pMeshOrbit->SetMtxParent(&m_mtxWorld);

	return S_OK;
}

//=============================================================================
// オブジェクトの終了処理
//=============================================================================
void CBall::Uninit(void)
{
	m_pMeshOrbit = NULL;
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
void CBall::Update(void)
{
#if 1
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//コントローラー情報を取得
	CDirectInput *pInputJoypad = CManager::GetJoypad();

	//カメラを取得
	CCamera *pCamera = CGame::GetCamera();

	// プレイヤーの状態を取得
	CCamera::STATE CameraState;
	CameraState = pCamera->GetState();

	//過去の位置を設定
	m_posold = m_pos;


	// 移動量の初期化
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//向きの代入
	D3DXVECTOR3 rot = m_pObject->Getrot();

	//ジャンプ
	if (pInput->GetTrigger(DIK_SPACE) == true && m_bJump == false && CameraState == pCamera->STATE_NORMAL)
	{
		m_move.y += 25.0f;
		//ジャンプフラグをtrueに
		m_bJump = true;

		m_nPlusX = rand() % 2;
		m_nPlusZ = rand() % 2;
	}

	else if (pInputJoypad->GetTrigger(pInputJoypad->DIJS_BUTTON_2) == true && m_bJump == false && CameraState == pCamera->STATE_NORMAL)
	{//打った時のボタン
		m_move.y += 25.0f;
		//ジャンプフラグをtrueに
		m_bJump = true;

		m_nPlusX = rand() % 2;
		m_nPlusZ = rand() % 2;
	}

 	if (m_bJump == true)
	{
		m_move.x += sinf(pCamera->GetCamera().rotCamera.y) * 30.0f;
		m_move.z += cosf(pCamera->GetCamera().rotCamera.y) * 30.0f;
		m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 1.0f);
	}

	if (m_nTryTimer > 300)
	{
		m_nTryTimer = 0;
		m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_bHit = false;
		m_bendBall = false;
		pCamera->SetState(CCamera::STATE_NORMAL);
	}

	if (CameraState != pCamera->STATE_FALL && m_bJump == true)
	{
		m_nTimer++;
	}

	if (m_nTimer > 250 && m_nTimer <= 350 && CameraState == pCamera->STATE_NORMAL)
	{
		pCamera->SetState(CCamera::STATE_NORMAL2);
	}

	if (m_nTimer > 350 && CameraState == pCamera->STATE_NORMAL2)
	{
		m_nTimer = 0;
		pCamera->SetState(CCamera::STATE_FALL);
		m_pos.y += 400.0f;

		if (m_nPlusX == 0)
		{
			m_pos.x += rand() % 300;
		}
		else
		{
			m_pos.x -= rand() % 300;
		}

		if (m_nPlusZ == 0)
		{
			m_pos.z += rand() % 300;
		}
		else
		{
			m_pos.z -= rand() % 150;
		}
	}

	if (CameraState == pCamera->STATE_FALL)
	{
		m_bJump = false;
		m_nTryTimer++;
	}

	//向きの慣性
	m_fDiffAngle = m_fDestAngle - m_rot.y;
	//角度の設定
	if (m_fDiffAngle > D3DX_PI)
	{
		m_fDiffAngle -= D3DX_PI* 2.0f;
	}
	if (m_fDiffAngle < -D3DX_PI)
	{
		m_fDiffAngle += D3DX_PI* 2.0f;
	}
	m_rot.y += m_fDiffAngle * 0.05f;
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI* 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI* 2.0f;
	}

	//重力
	m_move.y -= cosf(D3DX_PI * 0) * 0.1f;

	//減速
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;
	//位置更新
	m_pos += m_move;

	//地面との当たり判定
	CollisitionGround();

	//m_pObject->Setpos(m_pos);
	//m_ModelMove = move;

	if (m_bHit == true && m_bendBall == false)
	{
		m_bendBall = true;
		CScore *pScore = CGame::GetScore();
		pScore->AddScore(1);

	}

#ifdef  _DEBUG
	CDebugProc::Print(1, " ボールの位置  : ( %.1f ,%.1f ,%.1f )\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print(1, " ボールのタイマー  : ( %d )\n", m_nTimer);
	CDebugProc::Print(1, " トライタイマー  : ( %d )\n", m_nTryTimer);
#endif
#endif // 0
}

//=============================================================================
// オブジェクトの描画処理
//=============================================================================
void CBall::Draw(void)
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
	VecLight = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f);
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
void CBall::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CBall::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ

												// Xファイルの読み込み
	D3DXLoadMeshFromX(BG_MODEL0000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[0], NULL, &m_nNumMat[0], &m_pMesh[0]);

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
void CBall::UnLoad(void)
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
//	床の当たり判定
//=============================================================================
void CBall::CollisitionGround(void)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(3);

	//ジャンプをfalseに
	//m_bJump = false;

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがメッシュだったら
			if (pScene->GetObjType() == OBJTYPE_MESHFIELD)
			{
				//プレイヤーのHightを入れる
				if (((CSceneMeshField*)pScene)->GetHeightbool(m_pos))
				{
					//当たり判定
					//m_pos.y = ((CSceneMeshField*)pScene)->GetHeight(m_pos);

					//ジャンプしていない状態にする
					m_bJump = false;
					//着地
					//m_bLand = true;
					//落ちたときにmoveを初期化する
					m_move.y = 0.0f;

					//if (m_bJump == true)
					{
						//CShadow::SetPositionShadow(m_pos);
					}
				}
			}
		}
		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}

//=============================================================================
// オブジェクトの位置
//=============================================================================
D3DXVECTOR3 CBall::GetPos(void)
{
	return m_pos;
}
//=============================================================================
// オブジェクトの位置
//=============================================================================
D3DXVECTOR3 CBall::GetMove(void)
{
	return m_move;
}
//=============================================================================
// オブジェクトの位置
//=============================================================================
D3DXVECTOR3 CBall::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// オブジェクトの位置
//=============================================================================
int CBall::GetTryTimer(void)
{
	return m_nTryTimer;
}
//===============================================================================
// 当たり判定
//===============================================================================
bool CBall::CollisionObject(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
//	//あたっているかあたってないか
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
				if (m_pos.y < 10)
				{
					m_bHit = true;
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