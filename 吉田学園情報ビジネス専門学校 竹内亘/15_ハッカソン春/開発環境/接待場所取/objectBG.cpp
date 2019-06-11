//---------------------------------------------------------------------
//	オブジェクト処理(objectBG.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "objectBG.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"

#include "sceneObject.h"
#include "fade.h"
#include "player.h"
#include "effect.h"
#include "effect3D.h"
#include "shadow.h"
#include "billboardItem.h"

#include "UILife.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BG_MODEL0000					"data\\MODEL\\MODELBG\\Truck00.x"
#define BG_MODEL000						"data\\MODEL\\MODELBG\\bluesheet.x"
#define BG_MODEL001						"data\\MODEL\\MODELBG\\sakuratree.x"
#define BG_MODEL002						"data\\MODEL\\MODELBG\\sakuratree001.x"
#define BG_MODEL003						"data\\MODEL\\MODELBG\\sakuratree002.x"
#define BG_MODEL004						"data\\MODEL\\MODELBG\\fence000.x"
#define BG_MODEL005						"data\\MODEL\\MODELBG\\tree000.x"
#define BG_MODEL006						"data\\MODEL\\MODELBG\\Truck01.x"
#define BG_MODEL007						"data\\MODEL\\MODELBG\\Finish00.x"

#define MODEL_SPEED     (5.0f)
#define PLAYER_DEPTH	(18)		// プレイヤーの幅調整用
#define PLAYER_HEIGHT	(50.0f)		// プレイヤーの背の高さ

#define MAX_EFFECT_BILL  (15)
#define MAX_EFFECT_FENCE (5)
#define MAX_EFFECT_TREE  (7)
#define MAX_EFFECT_TRUCK (10)
#define MAX_ITEM_DROP	 (30)

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

	//影を設定
	m_pShadow = NULL;

	switch (m_Type)
	{
	case MODELTYPE_BILL000:
		break;
	case MODELTYPE_BILL001:
		break;
	case MODELTYPE_BILL002:
		break;
	case MODELTYPE_BILL003:
		//m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x - 50, 1.0f, m_pos.z + 50), 100, 120, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f),CShadow::SHADOWTYPE_BILL);
		break;
	case MODELTYPE_FENCE000:
		m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 0.5f, m_pos.z), 50, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), CShadow::SHADOWTYPE_NORMAL);
		break;
	case MODELTYPE_TREE000:
		m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 0.5f, m_pos.z), 50, 50, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), CShadow::SHADOWTYPE_NORMAL);
		break;
	case MODELTYPE_TRUCK000:
		m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 0.5f, m_pos.z), 50, 100, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), CShadow::SHADOWTYPE_NORMAL);
		break;
	}



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
	if (m_pShadow != NULL)
	{
		m_pShadow->Uninit();
		//delete m_pShadow;
		m_pShadow = NULL;
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
		rot.z += 0.1f;

		m_pObject->Setrot(rot);
		break;
	}

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
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 Kyori = m_pos - pPlayer->GetPos();

	//if (m_pos.z + 200 > pPlayer->GetPos().z)
	//{
	//	Kyori.z = abs(Kyori.z);
	//	if (Kyori.z < 10000)
	//	{
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
			////影の描画処理
			//D3DXMATRIX	mtxShadow;
			//D3DXPLANE	planeField;
			//D3DXVECTOR4 VecLight;
			//D3DXVECTOR3 pos, normal;
			////ライトを取得
			//CLight *pLight = CManager::GetLight();

			//// ライトを無効にする
			//pDevice->LightEnable(0, FALSE);
			//pDevice->LightEnable(1, FALSE);
			//pDevice->LightEnable(2, FALSE);
			//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
			////減算合成
			//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

			////シャドウマトリックスの初期化
			//D3DXMatrixIdentity(&mtxShadow);
			////ライトの設定
			//VecLight = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0f);
			////影の位置設定
			//pos = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
			////法線の設定
			//normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			////平面を作成
			//D3DXPlaneFromPointNormal(&planeField, &pos, &normal);
			////影マトリックスの設定
			//D3DXMatrixShadow(&mtxShadow, &VecLight, &planeField);
			////ワールドマトリックスと掛け合わせる
			//D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);
			////ワールドマトリックスの設定
			//pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

			//if (m_pObject != NULL)
			//{
			//	m_pObject->SetbShadow(true);
			//	m_pObject->Draw();
			//}
			////レンダーステイトを元に戻す
			//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//// ライトを有効にする
			//pDevice->LightEnable(0, TRUE);
			//pDevice->LightEnable(1, TRUE);
			//pDevice->LightEnable(2, TRUE);
			//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


			if (m_pObject != NULL)
			{
				m_pObject->SetbShadow(false);
				m_pObject->Draw();
			}
		//}
	//}
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
	D3DXLoadMeshFromX(BG_MODEL007, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[7], NULL, &m_nNumMat[7], &m_pMesh[7]);

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
	CPlayer *pPlayer = CGame::GetPlayer();

	//エフェクト用関数
	D3DXVECTOR3 RotRand;
	D3DXVECTOR3 PosRand;
	D3DXVECTOR3 effectmove;

	//サウンド
	CSound *pSound = CManager::GetSound(0);
	float fPlayerDepth; //プレイヤーの大きさ
	fPlayerDepth = 0;

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

		//回転時に当たり判定を横に拡大
		if (pPlayer->GetMotionState() == CPlayer::MOTIONSTATE_TUMBLE)
		{
			fPlayerDepth = 20;
		}

		if (m_Type == MODELTYPE_TREE000)
		{
			ModelMax.x -= 30.0f;
			ModelMax.z -= 30.0f;

			ModelMin.x += 30.0f;
			ModelMin.z += 30.0f;
		}

		if (pPos->x >= ModelMin.x - PLAYER_DEPTH - fPlayerDepth && pPos->x <= ModelMax.x + PLAYER_DEPTH + fPlayerDepth)
		{// Xの範囲内にいる
			if (pPos->z >= ModelMin.z - PLAYER_DEPTH && pPos->z <= ModelMax.z + PLAYER_DEPTH)
			{// Zの範囲内にいる
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

				// Yの範囲内にいる
				if (!(pPos->y >= ModelMax.y) && !(pPos->y + PLAYER_HEIGHT <= ModelMin.y))
				{
					//モーションの状態が走りとジャンプの時
					if (pPlayer->GetMotionState() == pPlayer->MOTIONSTATE_RUN
						|| pPlayer->GetMotionState() == pPlayer->MOTIONSTATE_JUMP)
					{	//無敵以外の時
						if (pPlayer->GetPlayerState() != CPlayer::PLAYERSTATE_APPEAR)
						{
							CUILife *pLife = CGame::GetUILife();
							pLife->MinusLife(1);
							pPlayer->SetMotionState(CPlayer::MOTIONSTATE_DAMAGE);
						}
					}
					//プレイヤーが転がりかジェットなら破壊
					//ビル
					if (m_Type == CObjectBG::MODELTYPE_BILL000 || m_Type == CObjectBG::MODELTYPE_BILL001
						|| m_Type == CObjectBG::MODELTYPE_BILL002 || m_Type == CObjectBG::MODELTYPE_BILL003)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_HIT00);

						for (int nCnt = 0; nCnt < MAX_EFFECT_BILL; nCnt++)
						{
							//ランダムな値
							RotRand.x = (float)(rand() % 50 - 25);
							RotRand.y = (float)(rand() % 100 + 50);
							PosRand.x = (float)(rand() % 100 - 50);
							//移動量の設定
							effectmove.x = (float)(rand() % 20 - 10);
							effectmove.y = (float)(rand() % 20 - 10);
							effectmove.z = (float)(rand() % 20 - 10);

							//エフェクトを生成
							CEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y, m_pos.z + 150), effectmove, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
								40, 40, 1, 50, CEffect::EFFECTTEX_HAHEN000);

							PosRand.x = (float)(rand() % 200 - 100);
							C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + RotRand.y, m_pos.z + 150), effectmove,
								D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), (C3DEffect::EFFECTTYPE)m_Type, 60);
						}
					}
					//フェンス
					if (m_Type == CObjectBG::MODELTYPE_FENCE000)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_HIT02);


						if (pPlayer->GetMotionState() == pPlayer->MOTIONSTATE_JET)
						{
							for (int nCnt = 0; nCnt < MAX_EFFECT_FENCE; nCnt++)
							{
								//ランダムな値
								RotRand.x = (float)(rand() % 20 - 10);
								PosRand.y = (float)(rand() % 20);
								PosRand.x = (float)(rand() % 50 - 25);
								//移動量の設定
								effectmove.x = (float)(rand() % 20 - 10);
								effectmove.y = (float)(rand() % 20 - 10);
								effectmove.z = (float)(rand() % 20 - 10);
								//エフェクトを生成
								C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 150), effectmove,
									D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), (C3DEffect::EFFECTTYPE)m_Type, 30);
							}
						}
						else
						{
							//無敵以外の時
							if (pPlayer->GetPlayerState() != CPlayer::PLAYERSTATE_APPEAR)
							{
								if (pPlayer->GetPlayerState() != CPlayer::PLAYERSTATE_DAMAGE)
								{
									CUILife *pLife = CGame::GetUILife();
									pLife->MinusLife(1);
									pPlayer->SetMotionState(CPlayer::MOTIONSTATE_DAMAGE);
								}
								for (int nCnt = 0; nCnt < MAX_EFFECT_FENCE; nCnt++)
								{
									//ランダムな値
									RotRand.x = (float)(rand() % 20 - 10);
									PosRand.y = (float)(rand() % 20);
									PosRand.x = (float)(rand() % 50 - 25);
									//移動量の設定
									effectmove.x = (float)(rand() % 20 - 10);
									effectmove.y = (float)(rand() % 20 - 10);
									effectmove.z = (float)(rand() % 20 - 10);
									//エフェクトを生成
									C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 150), effectmove,
										D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), (C3DEffect::EFFECTTYPE)m_Type, 30);
								}
							}
						}
					}
					//木
					if (m_Type == CObjectBG::MODELTYPE_TREE000)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_HIT01);
						for (int nCnt = 0; nCnt < MAX_EFFECT_TREE; nCnt++)
						{
							//ランダムな値
							RotRand.x = (float)(rand() % 20 - 10);
							PosRand.y = (float)(rand() % 20 + 20);
							PosRand.x = (float)(rand() % 50 - 25);
							//移動量の設定
							effectmove.x = (float)(rand() % 10 - 5);
							effectmove.y = (float)(rand() % 10);
							effectmove.z = (float)(rand() % 20 - 10);
							//エフェクトを生成
							C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 150), effectmove,
								D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), (C3DEffect::EFFECTTYPE)m_Type, 30);

							//ランダムな値
							RotRand.x = (float)(rand() % 20 - 10);
							PosRand.y = (float)(rand() % 50 + 100);
							PosRand.x = (float)(rand() % 50 - 25);

							effectmove.y = (float)(rand() % 50 + 10) / 10.0f;

							//エフェクトを生成
							C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 150), effectmove,
								D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), C3DEffect::EFFECTTYPE_LEAF000, 30);
						}
					}
					//トラック
					if (m_Type == CObjectBG::MODELTYPE_TRUCK000)
					{
						pSound->PlaySound(pSound->SOUND_LABEL_SE_HIT00);
						for (int nCnt = 0; nCnt < MAX_EFFECT_TRUCK; nCnt++)
						{
							//ランダムな値
							RotRand.x = (float)(rand() % 50 - 25);
							PosRand.y = (float)(rand() % 20 + 20);
							PosRand.x = (float)(rand() % 50 - 25);
							//移動量の設定
							effectmove.x = (float)(rand() % 50 - 25);
							effectmove.y = (float)(rand() % 10);
							effectmove.z = (float)(rand() % 20 - 10);
							//ランダムな値
							RotRand.x = (float)(rand() % 20 - 10);
							PosRand.y = (float)(rand() % 50 + 100);
							PosRand.x = (float)(rand() % 50 - 25);
							effectmove.y = (float)(rand() % 50 + 10) / 10.0f;
							//エフェクトを生成
							C3DEffect::Create(D3DXVECTOR3(m_pos.x + PosRand.x, m_pos.y + PosRand.y, m_pos.z + 150), effectmove,
								D3DXVECTOR3(sinf(RotRand.x), sinf(RotRand.x), sinf(RotRand.x)), C3DEffect::EFFECTTYPE_TRUCK000, 30);
						}
						//アイテムの個数
						for (int nCnt = 0; nCnt < MAX_ITEM_DROP; nCnt++)
						{
							//ランダムな値
							RotRand.x = (float)(rand() % 50 - 25);

							//アイテム
							CBillBoardItem::Create(D3DXVECTOR3(m_pos.x + RotRand.x, m_pos.y, (m_pos.z - 100) + (15 * nCnt)), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10, 30, CBillBoardItem::ITEMTEX_NORMAL);
						}
					}

					Uninit();
					break;
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