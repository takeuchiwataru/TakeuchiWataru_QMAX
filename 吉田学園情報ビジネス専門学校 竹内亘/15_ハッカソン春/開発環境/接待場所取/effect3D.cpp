//---------------------------------------------------------------------
//	3Dエフェクト処理(objectBG.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "effect3D.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"

#include "sceneObject.h"
#include "fade.h"
#include "player.h"
#include "effect.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODEL000						"data\\MODEL\\3DEFFECT\\Hahen000.x"
#define MODEL001						"data\\MODEL\\3DEFFECT\\Hahen100.x"
#define MODEL002						"data\\MODEL\\3DEFFECT\\Hahen200.x"
#define MODEL003						"data\\MODEL\\3DEFFECT\\Hahen300.x"
#define MODEL004						"data\\MODEL\\3DEFFECT\\Hahen400.x"
#define MODEL005						"data\\MODEL\\3DEFFECT\\HahenWood.x"
#define MODEL006						"data\\MODEL\\3DEFFECT\\HahenLeaf.x"
#define MODEL007						"data\\MODEL\\3DEFFECT\\HahenTruck.x"
#define MODEL008						"data\\MODEL\\3DEFFECT\\Hahen500.x"

#define MODEL_SPEED     (5.0f)

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPD3DXMESH					C3DEffect::m_pMesh[EFFECTTYPE_MAX] = {};
LPD3DXBUFFER				C3DEffect::m_pBuffMat[EFFECTTYPE_MAX] = {};
LPDIRECT3DTEXTURE9			C3DEffect::m_pTexture[EFFECTTYPE_MAX] = {};
DWORD						C3DEffect::m_nNumMat[EFFECTTYPE_MAX] = {};

//--------------------------------------------
//3Dエフェクトクラス コンストラクタ
//--------------------------------------------
C3DEffect::C3DEffect() : CScene(3, CScene::OBJTYPE_BGMODEL)
{
	m_pos = D3DXVECTOR3(0, 0, 0);					//位置
	m_posold = D3DXVECTOR3(0, 0, 0);				//前回の位置
	m_move = D3DXVECTOR3(0, 0, 0);					//移動量
	m_ModelMove = D3DXVECTOR3(0, 0, 0);
	m_rot = D3DXVECTOR3(0, 0, 0);					//向き
	D3DXMatrixIdentity(&m_mtxWorld);				//ワールドマトリックス
	m_nCount = 0;
	m_Type = C3DEffect::EFFECTTYPE_BILL000;
}

//--------------------------------------------
//3Dエフェクトクラス デストラクタ
//--------------------------------------------
C3DEffect::~C3DEffect()
{
}

//--------------------------------------------
//3Dエフェクトの生成
//--------------------------------------------
C3DEffect *C3DEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, EFFECTTYPE type, int nLife)
{
	//3Dエフェクトポインタ
	C3DEffect *pEffect3D;
	pEffect3D = new C3DEffect;
	//タイプの設定
	pEffect3D->m_Type = type;

	//初期値が入った後 値を代入
	pEffect3D->m_pos = pos;
	pEffect3D->m_rot = rot;
	pEffect3D->m_nLife = nLife;
	//3Dエフェクトの初期化
	pEffect3D->Init();

	//移動量の設定
	pEffect3D->m_move = move;
	//3Dエフェクトの情報を返す
	return pEffect3D;
}

//=============================================================================
// 3Dエフェクトの初期化処理
//=============================================================================
HRESULT C3DEffect::Init(void)
{
	//3Dエフェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_BGMODEL);

	m_move = D3DXVECTOR3(0, 0, 0);
	m_fDestAngle = D3DX_PI * 1.0f;
	m_fDiffAngle = 0;

	//モデルを生成	オフセット設定
	m_pObject = CSceneObject::Create(m_pos, m_rot);
	//モデルを割り当て
	m_pObject->BindModel(m_nNumMat[m_Type], m_pMesh[m_Type], m_pBuffMat[m_Type]);

	//影を設定
	m_pShadow = NULL;

	switch (m_Type)
	{
	case EFFECTTYPE_BILL000:
	case EFFECTTYPE_BILL001:
	case EFFECTTYPE_BILL002:
	case EFFECTTYPE_BILL003:
		m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 1.0f, m_pos.z - 150.0f +((float)(rand() % 200 ))),
									30, 30, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f), CShadow::SHADOWTYPE_NORMAL);
		break;
	case EFFECTTYPE_FENCE000:
	case EFFECTTYPE_TREE000:
		m_pShadow = CShadow::Create(D3DXVECTOR3(m_pos.x, 1.0f, m_pos.z - 150.0f),
			10, 10, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.2f), CShadow::SHADOWTYPE_NORMAL);
		break;
	}

	return S_OK;
}

//=============================================================================
// 3Dエフェクトの終了処理
//=============================================================================
void C3DEffect::Uninit(void)
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
		m_pShadow = NULL;
	}
	//自分を消す(3Dエフェクトを破棄)
	Release();
}

//=============================================================================
// 3Dエフェクトの更新処理
//=============================================================================
void C3DEffect::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();

	//過去の位置を設定
	m_posold = m_pos;

	//ライフ減少
	m_nLife--;
	//重力
	m_move.y -= cosf(D3DX_PI * 0) * 0.5f;
	//減速
	m_move.x += (0.0f - m_move.x) * 0.2f;
	m_move.z += (0.0f - m_move.z) * 0.5f;
	//位置更新
	m_pos += m_move;
	//地面ではねる
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0;
		m_move.y /= 2;
		m_move *= -1;
	}
	//位置を設定
	m_pObject->Setpos(m_pos);

	//ライフ切れで消滅
	if (m_nLife < 0)
	{
		Uninit();
	}
}

//=============================================================================
// 3Dエフェクトの描画処理
//=============================================================================
void C3DEffect::Draw(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();

	D3DXVECTOR3 Kyori = m_pos - pPlayer->GetPos();

	if (m_pos.z + 200 > pPlayer->GetPos().z)
	{
		Kyori.z = abs(Kyori.z);
		if (Kyori.z < 10000)
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
			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
			// 描画処理
			if (m_pObject != NULL)
			{
				m_pObject->SetbShadow(false);
				m_pObject->Draw();
			}
		}
	}
}

//=============================================================================
// 3Dエフェクトの位置設定
//=============================================================================
void C3DEffect::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT C3DEffect::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATERIAL *pMat;							//マテリアルデータへのポインタ


	for (int nCnt = 0; nCnt < EFFECTTYPE_MAX; nCnt++)
	{
		// メッシュの開放
		m_pMesh[nCnt] = NULL;
		// マテリアルの開放
		m_pBuffMat[nCnt] = NULL;
		//テクスチャの破棄
		m_pTexture[nCnt] = NULL;
	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX(MODEL000, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[0], NULL, &m_nNumMat[0], &m_pMesh[0]);
	D3DXLoadMeshFromX(MODEL001, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[1], NULL, &m_nNumMat[1], &m_pMesh[1]);
	D3DXLoadMeshFromX(MODEL002, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[2], NULL, &m_nNumMat[2], &m_pMesh[2]);
	D3DXLoadMeshFromX(MODEL003, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[3], NULL, &m_nNumMat[3], &m_pMesh[3]);
	D3DXLoadMeshFromX(MODEL005, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[4], NULL, &m_nNumMat[4], &m_pMesh[4]);
	D3DXLoadMeshFromX(MODEL005, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[5], NULL, &m_nNumMat[5], &m_pMesh[5]);
	D3DXLoadMeshFromX(MODEL006, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[6], NULL, &m_nNumMat[6], &m_pMesh[6]);
	D3DXLoadMeshFromX(MODEL007, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[7], NULL, &m_nNumMat[7], &m_pMesh[7]);
	D3DXLoadMeshFromX(MODEL008, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[8], NULL, &m_nNumMat[8], &m_pMesh[8]);

	//テクスチャの読み込み
	for (int nCnt = 0; nCnt < EFFECTTYPE_MAX; nCnt++)
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
void C3DEffect::UnLoad(void)
{
	for (int nCnt = 0; nCnt < EFFECTTYPE_MAX; nCnt++)
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
// 3Dエフェクトの位置
//=============================================================================
D3DXVECTOR3 C3DEffect::GetPos(void)
{
	return m_pos;
}
