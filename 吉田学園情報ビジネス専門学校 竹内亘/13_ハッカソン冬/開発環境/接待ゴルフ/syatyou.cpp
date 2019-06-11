//---------------------------------------------------------------------
//	プレイヤー処理(player.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "syatyou.h"
#include "manager.h"
#include "game.h"
#include "camera.h"
#include "fade.h"
#include "scene3D.h"
#include "meshField.h"
#include "model.h"
#include "meshOrbit.h"
#include "objectBG.h"
#include "billboardEnemy.h"
#include "billboardItem.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_TEXTURENAME000			"data\\TEXTURE\\GAME\\Player000.png"	//テクスチャのファイル名
#define PLAYER_MODEL000					"data\\MODEL\\00_body.x"
#define PLAYER_MODEL001					"data\\MODEL\\01_head.x"
#define PLAYER_MODEL002					"data\\MODEL\\02_armR.x"
#define PLAYER_MODEL003					"data\\MODEL\\03_handR.x"
#define PLAYER_MODEL004					"data\\MODEL\\04_armL.x"
#define PLAYER_MODEL005					"data\\MODEL\\05_handL.x"
#define PLAYER_MODEL006					"data\\MODEL\\06_legR.x"
#define PLAYER_MODEL007					"data\\MODEL\\07_footR.x"
#define PLAYER_MODEL008					"data\\MODEL\\08_legL.x"
#define PLAYER_MODEL009					"data\\MODEL\\09_footL.x"
#define MOVE_PLAYER						(7.0f)
#define FIELD_SIZE						(100.0f)
#define FILE_NAME						("data\\TEXT\\motion社長.txt")

#define TIMER_JUMP						(60)

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
CSyatyou::SYATYOUSTATE		CSyatyou::m_State = CSyatyou::SYATYOUSTATE_NONE;
D3DXVECTOR3					CSyatyou::m_pos = D3DXVECTOR3(0, 0, 0);
D3DXVECTOR3					CSyatyou::m_rot = D3DXVECTOR3(0, 0, 0);
D3DXVECTOR3					CSyatyou::m_move = D3DXVECTOR3(0, 0, 0);

LPD3DXMESH					CSyatyou::m_pMeshModel[MAX_PARTS] = {};
LPD3DXBUFFER				CSyatyou::m_pBuffMatModel[MAX_PARTS] = {};
LPDIRECT3DTEXTURE9			CSyatyou::m_pTextureModel[MAX_PARTS] = {};
DWORD						CSyatyou::m_nNumMatModel[MAX_PARTS] = {};

//--------------------------------------------
//グローバル変数
//--------------------------------------------
int g_nNumModelSyatyou;
char g_aFileNameModelSyatyou[MAX_PARTS][256];

//--------------------------------------------
//プレイヤークラス コンストラクタ
//--------------------------------------------
CSyatyou::CSyatyou() : CScene(4, CScene::OBJTYPE_MESHFIELD)
{
	m_bJump = false;
	m_pos = D3DXVECTOR3(0, 0, 0);					//位置
	m_posold = D3DXVECTOR3(0, 0, 0);				//前回の位置
	m_move = D3DXVECTOR3(0, 0, 0);					//移動量
	m_rot = D3DXVECTOR3(0, 0, 0);					//向き
	m_State = SYATYOUSTATE_NONE;						//状態
	m_nGameEndCnt = 0;								//カウント
	m_nJumpEndTimer = 0;

	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス

	m_pMeshModel[MAX_PARTS] = {};
	m_pBuffMatModel[MAX_PARTS] = {};
	m_pTextureModel[MAX_PARTS] = {};
	m_nNumMatModel[MAX_PARTS] = {};

	m_pKeyInfo[MAX_MOTION] = {};		//キー情報へのポインタ
	m_nKey = {};						//現在のキーナンバー
	m_nCountFlame = 0;					//フレーム数
	m_nSwingCnt = 0;
	m_bMotionEnd = false;
}

//--------------------------------------------
//プレイヤークラス デストラクタ
//--------------------------------------------
CSyatyou::~CSyatyou()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CSyatyou *CSyatyou::Create(D3DXVECTOR3 pos, float fLength)
{
	//プレイヤーポインタ
	CSyatyou *pPlayer;
	pPlayer = new CSyatyou;
	//プレイヤーの初期化
	pPlayer->Init();
	//初期値が入った後
	pPlayer->m_pos = pos;
	//プレイヤーの情報を返す
	return pPlayer;
}

//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT CSyatyou::Init(void)
{
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_SCENEX);

	m_rot = D3DXVECTOR3(0, D3DX_PI * -0.5f, 0);
	m_move = D3DXVECTOR3(0, 0, 0);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;
	m_bJump = false;
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = NULL;		// 頂点バッファへのポインタ
	m_State = SYATYOUSTATE_NORMAL;
	m_nGameEndCnt = 0;
	m_nJumpEndTimer = 0;
	m_nSwingCnt = 0;
	//モーション用変数
	m_nKey = 0;			//現在のキー
	m_nCountFlame = 0;	//現在のフレーム
	m_nMotionType = 0;	//現在のモーションタイプ

	//プレイヤー情報の読み込み
	FileLoad();

	m_pHole = CObjectBG::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 10.0f, m_pos.z), m_move, CObjectBG::MODELTYPE_HOLE, CObjectBG::MOVETYPE_NONE, 1);

	//軌跡
	m_pMeshOrbit = CMeshOrbit::Create(m_apModel[0]->GetPos());
	m_pMeshOrbit->SetMtxParent(&m_mtxWorld);

	return S_OK;
}

//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void CSyatyou::Uninit(void)
{
	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = NULL;
		}
	}
	//自分を消す(プレイヤーを破棄)
	Release();
}

//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CSyatyou::Update(void)
{
#if 1
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	CSound *pSound = CManager::GetSound();

	CDirectInput *pInputJoypad = CManager::GetJoypad();
	float Rot = pInputJoypad->GetLeftAxiz();

	//モード
	CCamera *pCamera = CGame::GetCamera();

	//前回の位置を保存
	m_posold = m_pos;

#if 1
	if (m_State == SYATYOUSTATE_NORMAL)
	{
		//移動していない ジャンプしていない　ニュートラル状態
		if (pInput->GetTrigger(DIK_SPACE) == true)
		{
			//モーション切り替え
			pSound->PlaySound(pSound->SOUND_LABEL_SE_SHOT);
			m_nMotionType = 1;
			m_State = SYATYOUSTATE_SWING;
		}
		else if (pInputJoypad->GetTrigger(pInputJoypad->DIJS_BUTTON_2) == true)
		{//打った時のボタン
			pSound->PlaySound(pSound->SOUND_LABEL_SE_SHOT);
			//モーション切り替え
			m_nMotionType = 1;
			m_State = SYATYOUSTATE_SWING;
		}
	}

	if (m_State == SYATYOUSTATE_SWING)
	{
		m_nSwingCnt++;
		if (m_nSwingCnt > 60)
		{
			m_nSwingCnt = 0;
			m_State = SYATYOUSTATE_NORMAL;
			//モーション切り替え
			m_nMotionType = 0;
		}
	}

	//モーション更新
	UpdateMotion();

#endif

	//減速
	m_move.x += (0.0f - m_move.x) * 0.5f;
	m_move.z += (0.0f - m_move.z) * 0.5f;
	//位置更新
	m_pos += m_move;

	//地面との当たり判定
	CollisitionGround();
	// オブジェクトの当たり判定
	//CollisitionObject3D(&m_pos, &m_posold, &m_move);
	// 敵 ビルボードの当たり判定
	//CollisitionBillBoardEnemy(&m_pos, &m_posold, &m_move);
	// アイテム ビルボードの当たり判定
	//CollisitionBillBoardItem(&m_pos, &m_posold, &m_move);


#ifdef  _DEBUG
	CDebugProc::Print(1, " プレイヤーの位置  : ( %.1f ,%.1f ,%.1f )\n", m_pos.x, m_pos.y, m_pos.z);
	CDebugProc::Print(1, " Numキー  : (%d)\n", m_nKey);
	CDebugProc::Print(1, " m_nCountFlame  : (%d)\n", m_nCountFlame);

	if (pInput->GetPress(DIK_0) == true && pInput->GetPress(DIK_1) == true)
	{
		m_move.x += sinf(pCamera->GetCamera().rotCamera.y) * 50.0f;
		m_move.z += cosf(pCamera->GetCamera().rotCamera.y) * 50.0f;
		m_fDestAngle = (pCamera->GetCamera().rotCamera.y + D3DX_PI * 1.0f);

	}
#endif

#endif // 0
}

//=============================================================================
// プレイヤーの描画処理
//=============================================================================
void CSyatyou::Draw(void)
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
	VecLight = D3DXVECTOR4(0.0f, 1.0f, -1.0f, 0.0f);
	//影の位置設定
	pos = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
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

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			//m_apModel[nCnt]->m_bShadow = true;
			m_apModel[nCnt]->Draw();
		}
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

	for (int nCnt = 0; nCnt < m_nNumParts; nCnt++)
	{
		if (m_apModel[nCnt] != NULL)
		{
			m_apModel[nCnt]->Draw();
		}
	}
}

//=============================================================================
// プレイヤーの位置設定
//=============================================================================
void CSyatyou::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CSyatyou::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	return S_OK;
}

//=============================================================================
// テクスチャの破棄処理
//=============================================================================
void CSyatyou::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_PARTS; nCnt++)
	{
		// メッシュの開放
		if (m_pMeshModel[nCnt] != NULL)
		{
			m_pMeshModel[nCnt]->Release();
			m_pMeshModel[nCnt] = NULL;
		}
		// マテリアルの開放
		if (m_pBuffMatModel[nCnt] != NULL)
		{
			m_pBuffMatModel[nCnt]->Release();
			m_pBuffMatModel[nCnt] = NULL;
		}

		//テクスチャの破棄
		if (m_pTextureModel[nCnt] != NULL)
		{
			m_pTextureModel[nCnt]->Release();
			m_pTextureModel[nCnt] = NULL;
		}
	}

}

//=============================================================================
// プレイヤーのダメージ
//=============================================================================
void CSyatyou::HitDamage(int nDamage)
{

}
//=============================================================================
// プレイヤーの位置
//=============================================================================
D3DXVECTOR3 CSyatyou::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// プレイヤーの回転
//=============================================================================
D3DXVECTOR3 CSyatyou::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// プレイヤーの移動
//=============================================================================
D3DXVECTOR3 CSyatyou::GetMove(void)
{
	return m_move;
}

//=============================================================================
//	床の当たり判定
//=============================================================================
void CSyatyou::CollisitionGround(void)
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

					if (m_bJump == true)
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
//	オブジェクトの当たり判定
//=============================================================================
void CSyatyou::CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(3);

	//変数宣言
	bool bLand = false;

	//bLandの初期化処理
	m_bLand = false;

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがオブジェクトだったら
			if (pScene->GetObjType() == OBJTYPE_BGMODEL)
			{
				//オブジェクトのあたる判定
				bLand = ((CObjectBG*)pScene)->CollisionObject(pPos, pPosOld, pMove);
				//着地を共有する
				if (bLand)
				{
					m_bJump = false;
					m_bLand = bLand;
				}
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}
}

//=============================================================================
//	敵ビルボードの当たり判定
//=============================================================================
void CSyatyou::CollisitionBillBoardEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(5);

	//変数宣言
	bool bLand = false;

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがオブジェクトだったら
			if (pScene->GetObjType() == OBJTYPE_BILLBOARDENEMY)
			{
				//オブジェクトのあたる判定
				bLand = ((CBillBoardEnemy*)pScene)->CollisionBillboardEnemy(pPos, pPosOld, pMove);
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}

}

//=============================================================================
//	アイテムビルボードの当たり判定
//=============================================================================
void CSyatyou::CollisitionBillBoardItem(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pPosOld, D3DXVECTOR3 * pMove)
{
	CScene *pScene;

	//プライオリティーチェック
	pScene = CScene::GetTop(5);

	//変数宣言
	bool bLand = false;

	//NULLチェック
	while (pScene != NULL)
	{
		//UpdateでUninitされてしまう場合　Nextが消える可能性があるからNextにデータを残しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{
			//タイプがオブジェクトだったら
			if (pScene->GetObjType() == OBJTYPE_BILLBOARDITEM)
			{
				//オブジェクトのあたる判定
				bLand = ((CBillBoardItem*)pScene)->CollisionBillboardItem(pPos, pPosOld, pMove);
			}
		}

		//Nextに次のSceneを入れる
		pScene = pSceneNext;
	}

}


//=============================================================================
// プレイヤーのモーション
//=============================================================================
void CSyatyou::UpdateMotion(void)
{
	//モーション
	KEY *pKey, *pNextKey;
	float fRateMotion;
	float fDiffMotion;
	D3DXVECTOR3 rotmotion;
	D3DXVECTOR3 posmotion;


	//キーが最大数を上回らないように
	if (m_aMotionInfo[m_nMotionType].nNumKey <= m_nKey)
	{
		m_nKey = 0;
	}

	//モーション更新
	for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
	{
		if (m_apModel[nCntParts] != NULL)
		{
			//現在のキーを取得
			pKey = &m_pKeyInfo[m_nMotionType][m_nKey].aKey[nCntParts];
			//次のキーを取得
			pNextKey = &m_pKeyInfo[m_nMotionType][(m_nKey + 1) % m_aMotionInfo[m_nMotionType].nNumKey].aKey[nCntParts];

			//現在のキーから次のキーへの再生フレーム数におけるモーションカウンターの相対値を算出
			fRateMotion = (float)m_nCountFlame / (float)m_pKeyInfo[m_nMotionType][m_nKey].nFrame;

			//ROT
			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->frotX - pKey->frotX;
			//相対値を差分を使って各要素の値を算出
			rotmotion.x = pKey->frotX + (fDiffMotion * fRateMotion);

			//POS
			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->fposX - pKey->fposX;
			//相対値を差分を使って各要素の値を算出
			posmotion.x = pKey->fposX + (fDiffMotion * fRateMotion);


			//ROT
			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->frotY - pKey->frotY;
			//相対値を差分を使って各要素の値を算出
			rotmotion.y = pKey->frotY + (fDiffMotion * fRateMotion);

			//POS
			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->fposY - pKey->fposY;
			//相対値を差分を使って各要素の値を算出
			posmotion.y = pKey->fposY + (fDiffMotion * fRateMotion);

			//ROT
			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->frotZ - pKey->frotZ;
			//相対値を差分を使って各要素の値を算出
			rotmotion.z = pKey->frotZ + (fDiffMotion * fRateMotion);
			//POS
			//現在のキーと次のキーの各要素の差分を算出
			fDiffMotion = pNextKey->fposZ - pKey->fposZ;
			//相対値を差分を使って各要素の値を算出
			posmotion.z = pKey->fposZ + (fDiffMotion * fRateMotion);

			//パーツを動かす
			m_apModel[nCntParts]->Setrot(rotmotion);

			//POS
			m_apModel[nCntParts]->Setpos(D3DXVECTOR3(m_OffSetPos[nCntParts].x + posmotion.x,
				m_OffSetPos[nCntParts].y + posmotion.y,
				m_OffSetPos[nCntParts].z + posmotion.z));

		}
	}

	//ループの判定
	switch (m_aMotionInfo[m_nMotionType].bLoop)
	{
	case true:
		//ループする
		//フレームを進める
		m_nCountFlame++;
		//キーの更新
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{
			if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
			{
				m_nKey = 0;
			}
			else
			{
				m_nKey += 1;
			}
			m_nCountFlame = 0;
		}

		break;
	case false:
		//ループしない
		if (m_aMotionInfo[m_nMotionType].nNumKey - 1 > m_nKey)
		{//フレームを進める
			m_nCountFlame++;
		}
		else if (m_aMotionInfo[m_nMotionType].nNumKey - 1 == m_nKey)
		{
			m_bMotionEnd = true;
		}
		//キーの更新
		if (m_nCountFlame >= m_pKeyInfo[m_nMotionType][m_nKey].nFrame)
		{
			if (m_aMotionInfo[m_nMotionType].nNumKey > m_nKey)
			{
				m_nKey += 1;
			}
			m_nCountFlame = 0;
		}
		break;
	}

}

//=============================================================================
// ファイル読み込み
//=============================================================================
void CSyatyou::FileLoad(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル読み込み用変数
	FILE *pFile;		//ファイルポインタ
	char *pStrcur;		//現在の先頭の文字列
	char aLine[256];	//文字列
	char aStr[256];		//一時保存文字列
	int nIndex = 0;		//現在のインデックス
	int nWord = 0;		//ポップで返された値を保持

	D3DXVECTOR3 ParentPos;	//親の位置情報を取得
#if 1
	//ファイルを開く 読み込み
	pFile = fopen(FILE_NAME, "r");
	//NULLチェック
	if (pFile != NULL)
	{
		for (int nCntMotion = 0; nCntMotion < MAX_MOTION; nCntMotion++)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("NUM_MODEL = ");
				//文字列の先頭を設定
				strcpy(aStr, pStrcur);
				//文字列抜き出し
				g_nNumModelSyatyou = atoi(pStrcur);

				for (int nCntModel = 0; nCntModel < g_nNumModelSyatyou; nCntModel++)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り戻す
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "MODEL_FILENAME = ", strlen("MODEL_FILENAME = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("MODEL_FILENAME = ");

						//文字列を設定
						strcpy(aStr, pStrcur);

						//必要な文字列の最後の文字までの文字数を数える
						int nNullNum = PopString(pStrcur, &aStr[0]);

						//文字列を取り戻す
						strcpy(aStr, pStrcur);

						//最後の文字にNULL文字を入れる
						aStr[nNullNum - 1] = '\0';

						//対象の文字列から抜き出し
						strcpy(&g_aFileNameModelSyatyou[nCntModel][0], aStr);

						// Xファイルの読み込み
						D3DXLoadMeshFromX(&g_aFileNameModelSyatyou[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMatModel[nCntModel],
							NULL,
							&m_nNumMatModel[nCntModel],
							&m_pMeshModel[nCntModel]);
					}
				}
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//文字列を取り出す
				strcpy(aStr, pStrcur);
			}


			//文字列のデータ 比較する文字列 比較する文字数
			if (memcmp(pStrcur, "CHARACTERSET", 12) == 0)
			{
				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り出す
					strcpy(aStr, pStrcur);
					if (memcmp(pStrcur, "NUM_PARTS = ", strlen("NUM_PARTS = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("NUM_PARTS = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_nNumParts = atoi(pStrcur);
					}
					if (memcmp(pStrcur, "PARTSSET", strlen("PARTSSET")) == 0)
					{
						while (1)
						{
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);

							//INDEXを読み込み
							if (memcmp(pStrcur, "INDEX = ", strlen("INDEX = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("INDEX = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列抜き出し
								nIndex = atoi(pStrcur);
							}
							//PARENTを読み込み
							if (memcmp(pStrcur, "PARENT = ", strlen("PARENT = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("PARENT = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列抜き出し
								m_aIndexParent[nIndex] = atoi(pStrcur);
							}
							//POSを読み込み
							if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("POS = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposX = (float)atof(pStrcur);
								//文字数分進める
								pStrcur += nWord;

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposY = (float)atof(pStrcur);
								//文字数分進める
								pStrcur += nWord;

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].fposZ = (float)atof(pStrcur);

							}
							//ROTを読み込み
							if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("ROT = ");
								//文字列の先頭を設定
								strcpy(aStr, pStrcur);

								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].frotX = (float)atof(pStrcur);

								//文字数分進める
								pStrcur += nWord;
								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								m_aKayOffset[nIndex].frotY = (float)atof(pStrcur);

								//文字数分進める
								pStrcur += nWord;
								//文字数を返してもらう
								nWord = PopString(pStrcur, &aStr[0]);
								//文字列変換
								//rotFile[nIndex].z = (float)atof(pStrcur);
								m_aKayOffset[nIndex].frotZ = (float)atof(pStrcur);


							}
							//パーツセット終了
							else if (memcmp(pStrcur, "END_PARTSSET", strlen("END_PARTSSET")) == 0)
							{

								//モデルを生成	オフセット設定
								m_apModel[nIndex] = CModel::Create(
									D3DXVECTOR3(m_pos.x + m_aKayOffset[nIndex].fposX,
										m_pos.y + m_aKayOffset[nIndex].fposY,
										m_pos.z + m_aKayOffset[nIndex].fposZ),
									D3DXVECTOR3(m_rot.x + m_aKayOffset[nIndex].frotX,
										m_rot.y + m_aKayOffset[nIndex].frotY,
										m_rot.z + m_aKayOffset[nIndex].frotZ));

								//posを代入
								m_OffSetPos[nIndex] = m_apModel[nIndex]->GetPos();

								//モデルを割り当て
								m_apModel[nIndex]->BindModel(m_nNumMatModel[nIndex], m_pMeshModel[nIndex], m_pBuffMatModel[nIndex]);

								if (m_aIndexParent[nIndex] == -1)
								{
									//モデルの親を指定
									m_apModel[nIndex]->SetParent(NULL);
								}
								else
								{
									//モデルの親を指定
									m_apModel[nIndex]->SetParent(m_apModel[m_aIndexParent[nIndex]]);
								}

								break;
							}
						}
					}
					//キャラクターセット終了
					else if (memcmp(pStrcur, "END_CHARACTERSET", strlen("END_CHARACTERSET")) == 0)
					{
						break;
					}
				}
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//文字列を取り出す
				strcpy(aStr, pStrcur);
			}

			//モーション読み込み
			if (memcmp(pStrcur, "MOTIONSET", strlen("MOTIONSET")) == 0)
			{
				//頭出し
				pStrcur += strlen("MOTIONSET");

				while (1)
				{
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);
					//文字列を取り出す
					strcpy(aStr, pStrcur);

					if (memcmp(pStrcur, "LOOP = ", strlen("LOOP = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("LOOP = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);

						switch (atoi(pStrcur))
						{
						case 0:
							//文字列抜き出し
							m_aMotionInfo[nCntMotion].bLoop = false;
							break;
						case 1:
							//文字列抜き出し
							m_aMotionInfo[nCntMotion].bLoop = true;
							break;
						}
						//文字列の先頭を設定
						pStrcur = ReadLine(pFile, &aLine[0]);
					}

					if (memcmp(pStrcur, "NUM_KEY = ", strlen("NUM_KEY = ")) == 0)
					{
						//頭出し
						pStrcur += strlen("NUM_KEY = ");
						//文字列の先頭を設定
						strcpy(aStr, pStrcur);
						//文字列抜き出し
						m_aMotionInfo[nCntMotion].nNumKey = atoi(pStrcur);

						//文字列の先頭を設定
						pStrcur = ReadLine(pFile, &aLine[0]);
						//文字列を取り出す
						strcpy(aStr, pStrcur);
					}

					//キーの設定
					for (int nCntKey = 0; nCntKey < m_aMotionInfo[nCntMotion].nNumKey;)
					{
						if (memcmp(pStrcur, "KEYSET", strlen("KEYSET")) == 0)
						{
							//頭出し
							pStrcur += strlen("KEYSET");
							//文字列の先頭を設定
							strcpy(aStr, pStrcur);
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);

							if (memcmp(pStrcur, "FRAME = ", strlen("FRAME = ")) == 0)
							{
								//頭出し
								pStrcur += strlen("FRAME = ");

								m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].nFrame = atoi(pStrcur);

								//文字列の先頭を設定
								strcpy(aStr, pStrcur);
								//文字列の先頭を設定
								pStrcur = ReadLine(pFile, &aLine[0]);
							}

							//パーツ分回す
							for (int nCntParts = 0; nCntParts < m_nNumParts;)
							{
								if (memcmp(pStrcur, "KEY", strlen("KEY")) == 0)
								{
									//文字列の先頭を設定
									pStrcur = ReadLine(pFile, &aLine[0]);

									if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
									{
										//頭出し
										pStrcur += strlen("POS = ");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.X代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposX = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Y代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposY = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//POS.Z代入
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].fposZ = (float)atof(pStrcur);
										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									//ROTを読み込み
									if (memcmp(pStrcur, "ROT = ", strlen("ROT = ")) == 0)
									{
										//頭出し
										pStrcur += strlen("ROT = ");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotX
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotX = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotY
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotY = (float)atof(pStrcur);
										//文字数分進める
										pStrcur += nWord;

										//文字数を返してもらう
										nWord = PopString(pStrcur, &aStr[0]);
										//RotZ
										m_aMotionInfo[nCntMotion].aKayInfo[nCntKey].aKey[nCntParts].frotZ = (float)atof(pStrcur);

										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
									}
									if (memcmp(pStrcur, "END_KEY", strlen("END_KEY")) == 0)
									{
										//頭出し
										pStrcur += strlen("END_KEY");
										//文字列の先頭を設定
										strcpy(aStr, pStrcur);
										//文字列の先頭を設定
										pStrcur = ReadLine(pFile, &aLine[0]);
										//パーツのカウントを進める
										nCntParts++;
									}
								}
								else
								{
									//文字列の先頭を設定
									pStrcur = ReadLine(pFile, &aLine[0]);
								}
							}
							if (memcmp(pStrcur, "END_KEYSET", strlen("END_KEYSET")) == 0)
							{
								//文字列の先頭を設定
								pStrcur = ReadLine(pFile, &aLine[0]);
								//カウントを進める
								nCntKey++;
							}
						}
						else
						{
							//文字列の先頭を設定
							pStrcur = ReadLine(pFile, &aLine[0]);
						}

					}
					if (memcmp(pStrcur, "END_MOTIONSET", strlen("END_MOTIONSET")) == 0)
					{
						//モーションの情報をセット
						m_pKeyInfo[nCntMotion] = &m_aMotionInfo[nCntMotion].aKayInfo[0];
						break;
					}
				}
			}
			//スクリプトの終わり
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}
	else
	{	//ファイルが開けなかった
		printf("ファイルが開けませんでした\n");
	}
	//ファイルを閉じる
	fclose(pFile);
#endif

}

//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CSyatyou::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//１行分読み込み
		fgets(&pDst[0], 256, pFile);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//　ファイル読み込み先頭を排除
//=============================================================================
char * CSyatyou::GetLineTop(char * pStr)
{
	while (1)
	{
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//　文字数を返す
//=============================================================================
int CSyatyou::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//頭出し
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//頭出し
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//文字列の数を返す
	return nWord;
}
