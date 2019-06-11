//=============================================================================
//
// モーション処理 [motion.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS			//Fire Wall突破
#include <stdio.h>						//インクルドファイル
#include "main.h"
#include "motion.h"
#include "SceneModel.h"
#include "mesh.h"
#include "camera.h"
#include "player.h"
#include "Game.h"
#include "sound.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
CCharacter::MODEL_PARTS		*CCharacter::m_partsAll[CCharParts::PARTS_MAX] = {};	//パーツ情報
int							CMotion::m_nNumMotion = 0;				//モーション数
CMotion						**CMotion::m_pMotion = NULL;				//モーション情報

//=============================================================================
// モーションの初期化
//=============================================================================
void	CMotion::Load(void)
{
	FILE *pFile;
	char aStr[8][32];
	m_nNumMotion = 0;
	int nNumMotion = 0;
	m_pMotion = NULL;

	//モーションの読み込み----------------------------------------------------------
	int nCntMotion[3];
	CKey *pKey;
	CAtkKey *pAtkKey;
	COneMotion *pMotion;

	pFile = fopen("data/TEXT/motion.txt", "r");

	if (pFile != NULL)//Load
	{//成功
		fscanf(pFile, "%d", &nCntMotion[0]);//ファイル数
		m_nNumMotion = nCntMotion[0];
		m_pMotion = new CMotion*[m_nNumMotion];	//モーション全体個数生成
		for (int nCntP = 0; nCntP < m_nNumMotion; nCntP++) { m_pMotion[nCntP] = new CMotion; }

		for (int nCntChar = 0; nCntChar < nCntMotion[0]; nCntChar++)
		{
			fscanf(pFile, "%s", &aStr[nCntChar][0]);//ファイル名
			CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "%s 読み込み\n", &aStr[nCntChar][0]);
		}

		fclose(pFile);
	}
	else
	{//失敗
		MessageBox(0, "モーション", "motion.txt無し！", MB_OK);
	}

	for (int nCntChar = 0; nCntChar < nCntMotion[0]; nCntChar++)
	{
		pFile = fopen(&aStr[nCntChar][0], "r");
		if (pFile != NULL)//Load
		{//モーションファイルLoad
			fscanf(pFile, "%d %d\n", &nNumMotion, &m_pMotion[nCntChar]->m_nMaxParts);//モーション数 パーツ数
			//生成
			m_pMotion[nCntChar]->GetOneMotion() = new COneMotion[nNumMotion];

			for (int nCnt0 = 0; nCnt0 < nNumMotion; nCnt0++)
			{//モーション数回転
				pMotion = &m_pMotion[nCntChar]->GetOneMotion()[nCnt0];
				fscanf(pFile, "%d", &pMotion->GetnMaxKey());

				//キー生成
				pMotion->GetKey() = new CKey*[pMotion->GetnMaxKey()];

				//キーTYPE生成
				pMotion->GetType() = new CKey::TYPE[pMotion->GetnMaxKey()];

				fscanf(pFile, "%d %d %d %d %d %d %d %d\n", 
					&pMotion->GetnNorBranch(),
					&pMotion->GetnLandBranch(),
					&pMotion->GetnStartCancel(0),
					&pMotion->GetnStartCancel(1),
					&pMotion->GetnEndCancel(0),
					&pMotion->GetnEndCancel(1),
					&pMotion->GetnOtherCancel(0),
					&pMotion->GetnOtherCancel(1)
				);

				for (int nCnt1 = 0; nCnt1 < pMotion->GetnMaxKey(); nCnt1++)
				{//キー数回転
					pKey = pMotion->GetKey()[nCnt1];

					fscanf(pFile, "%d", &pMotion->GetType()[nCnt1]);//モーション数 パーツ数

					switch (pMotion->GetType()[nCnt1])
					{//キーTYPE　生成したけど中身入ってない
					case CKey::TYPE_NORMAL: pMotion->GetKey()[nCnt1] = new CKey;  break;
					case CKey::TYPE_ATTACK: pMotion->GetKey()[nCnt1] = new CAtkKey;  break;
					}
					pKey = pMotion->GetKey()[nCnt1];

					fscanf(pFile, "%d %d %d %d %f %f\n",
						&pKey->GetnMoveType(),
						&pKey->GetnFloating(),
						&pKey->GetnFrame(),
						&pKey->GetnMaxEffect(),
						&pKey->GetfMove(),
						&pKey->GetfSlip()
					);//モーション数 パーツ数

					  //エフェクト枠生成
					pKey->GetpEffect() = new int[pKey->GetnMaxEffect()];

					  //角度枠生成
					pKey->GetpRot() = new D3DXVECTOR3[m_pMotion[nCntChar]->m_nMaxParts];

					fscanf(pFile, "%f %f %f\n", &pKey->GetMove().x,
						&pKey->GetMove().y,
						&pKey->GetMove().z);
					for (int nCnt2 = 0; nCnt2 < m_pMotion[nCntChar]->m_nMaxParts; nCnt2++)
					{//パーツ数回転
						fscanf(pFile, "%f %f %f\n", &pKey->GetpRot()[nCnt2].x,
							&pKey->GetpRot()[nCnt2].y,
							&pKey->GetpRot()[nCnt2].z);
					}
					{//パーツ数回転
						fscanf(pFile, "%f %f %f\n", &pKey->GetPos().x,
							&pKey->GetPos().y,
							&pKey->GetPos().z);
					}

					for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
					{//パーツ数回転
						fscanf(pFile, "%d ", &pKey->GetpEffect()[nCount]);
					}

					if (pMotion->GetType()[nCnt1] == CKey::TYPE_ATTACK)
					{
						pAtkKey = (CAtkKey*)pKey;
						fscanf(pFile, "%d %d %d %d %d\n", 
							&pAtkKey->GetnAtkType(),
							&pAtkKey->GetnAtkParts(),
							&pAtkKey->GetnCntAtk(),
							&pAtkKey->GetnHitFrame(0),
							&pAtkKey->GetnHitFrame(1));

						fscanf(pFile, "%f %f\n", &pAtkKey->GetfRange(),
							&pAtkKey->GetfAtkplus()
						);
					}
				}
			}
			fclose(pFile);
		}
		else
		{//失敗
			MessageBox(0, "モーションデータ", "無いよ!?", MB_OK);
		}
	}
	CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "モーション読み込み完了 読み込んだモーション数:%d\n", m_nNumMotion);
}
//=============================================================================
// モーションの全終了
//=============================================================================
void CMotion::UnLoad(void)
{
	if (m_pMotion != NULL)
	{//モーションが読み込まれているなら
		for (int nCount = 0; nCount < m_nNumMotion; nCount++)
		{//生成されたモーション分回転
			if (m_pMotion[nCount] != NULL)
			{//モーションが生成されていれば解放
				m_pMotion[nCount]->Uninit();
			}
		}//初期化
		m_nNumMotion = 0;
		delete[] m_pMotion;
		m_pMotion = NULL;
	}
}
//=============================================================================
// モーションの終了
//=============================================================================
void CMotion::Uninit(void)
{
	if (m_OneMotion != NULL)
	{//モーションのが生成されていれば
		for (int nCount = 0; nCount < m_nMaxMotion; nCount++)
		{//モーション分回転
			m_OneMotion[nCount].Uninit();
		}//初期化
		m_nMaxMotion = 0;
		delete[] m_OneMotion;
		m_OneMotion = NULL;
	}
}
//=============================================================================
// 一つのモーション終了
//=============================================================================
void COneMotion::Uninit(void)
{
	if (m_Key != NULL)
	{//キーが生成されていれば
		for (int nCount = 0; nCount < m_nMaxKey; nCount++)
		{//キー分回転
			if (m_Key[nCount] != NULL)
			{//生成されていれば削除
				m_Key[nCount]->Uninit();
			}
		}//初期化
		m_nMaxKey = 0;
		delete[] m_Key;
		m_Key = NULL;
	}
}
//=============================================================================
// キーの終了
//=============================================================================
void CKey::Uninit(void)
{
	if (m_pRot != NULL)
	{//角度が生成されていれば
		delete[] m_pRot;		//1つだったらやばいかも
		m_pRot = NULL;
	}
	if (m_pEffect != NULL)
	{//効果が生成されていれば
		delete[] m_pEffect;		//1つだったらやばいかも
		m_pEffect = NULL;
	}
}

//=============================================================================
// パーツの読み込み 列挙
//=============================================================================
void CCharacter::Load(CCharParts::PARTS parts)
{
	if (m_partsAll[parts] != NULL)
	{
		int nLength = (int)strlen(&m_partsAll[parts]->aText[0]);		//文字数確認

		if (nLength > 1)
		{
			D3DXLoadMeshFromX(&m_partsAll[parts]->aText[0],
				D3DXMESH_SYSTEMMEM, CManager::GetRenderer()->GetDevice(), NULL, &m_partsAll[parts]->pBuffMatModel, NULL, &m_partsAll[parts]->nNumMatModel, &m_partsAll[parts]->MeshModel);
			strcpy(&m_partsAll[parts]->aText[0], "");

			//テクスチャ確認
			CScene::Load(m_partsAll[parts]->tex);
		}
	}
}
//=============================================================================
// パーツの読み込み 文字列
//=============================================================================
void CCharacter::Load(void)
{
	FILE	*pFile;
	int		nNumParts = 0;
	//int nLength;		//文字数確認

	pFile = fopen("data/TEXT/model.txt", "r");

	if (pFile != NULL)//Load
	{//成功
		for (int nCountData = 0; nCountData < CCharParts::PARTS_MAX; nCountData++)
		{// Xファイルの読み込み
			if (m_partsAll[nCountData] == NULL) { m_partsAll[nCountData] = new CCharacter::MODEL_PARTS; }
			//nLength = (int)strlen(&m_partsAll[nCountData]->aText[0]);
			//if (nLength < 5)
			{
				fscanf(pFile, "%s\n", &m_partsAll[nCountData]->aText[0]);	//ファイル名
				fscanf(pFile, "%d\n", &m_partsAll[nCountData]->tex);		//画像
				fscanf(pFile, "%f %f %f", &m_partsAll[nCountData]->addPos.x, &m_partsAll[nCountData]->addPos.y, &m_partsAll[nCountData]->addPos.z);//場所
				if (m_partsAll[nCountData]->tex != -1) { m_partsAll[nCountData]->tex = (CScene::TEXTURE)((int)TEX_CHAR + (int)m_partsAll[nCountData]->tex); }
			}
		}
		fclose(pFile);
	}
}
//=============================================================================
// パーツの終了
//=============================================================================
void CCharacter::UnLoad(void)
{
	for (int nCount = 0; nCount < CCharParts::PARTS_MAX; nCount++)
	{//パーツ分回る
		if (m_partsAll[nCount] != NULL)
		{//パーツが生成されていれば解放
				// メッシュの開放
			if (m_partsAll[nCount]->MeshModel != NULL)
			{
				m_partsAll[nCount]->MeshModel->Release();
				m_partsAll[nCount]->MeshModel = NULL;
			}

			// マテリアルの開放
			if (m_partsAll[nCount]->pBuffMatModel != NULL)
			{
				m_partsAll[nCount]->pBuffMatModel->Release();
				m_partsAll[nCount]->pBuffMatModel = NULL;
			}
			delete m_partsAll[nCount];
			m_partsAll[nCount] = NULL;
		}
	}
}
//=============================================================================
// キャラクターの初期化
//=============================================================================
HRESULT CCharacter::Init(void)
{
	m_addpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_addPosmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_length = D3DXVECTOR3(30.0f, 85.0f, 30.0f);
	m_FNor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMaxParts = 0;
	m_pParts = NULL;
	m_Type = CMotion::TYPE_MAX;
	m_bJump = false;
	m_DrawType = CScene::DRAW_TYPE_NORMAL;
	m_fFramePlus = 1.0f;
	m_fInitFrame = 0.0f;
	m_fSpeed = 3.0f;
	m_fCola = 1.0f;
	m_fRot = D3DX_PI * -0.5f;
	return S_OK;
}
//=============================================================================
// キャラクターの終了
//=============================================================================
void CCharacter::Uninit(void)
{
	if (m_pParts != NULL) { delete[] m_pParts; m_pParts = NULL; }
	CScene::Uninit();
}
//=============================================================================
// キャラクターの更新
//=============================================================================
void CCharacter::Update(bool bMove)
{
	CScene *pScene = NULL;
	D3DXVECTOR3 Vec2;
	float fTilt;
	float fRot;
	float fFrameP;
	bool bSpin = false;
	bool bLand = false;
	fFrameP = m_fFramePlus + m_fFramePlus2;

	if (m_bJump == true)
	{
		Vec2 = D3DXVECTOR3(sinf(m_rot.y), 0.0f, cosf(m_rot.y));
		fTilt = (m_FNor.x * Vec2.x) + (m_FNor.y * Vec2.y) + (m_FNor.z * Vec2.z) /
			(sqrtf(powf(m_FNor.x, 2) + powf(m_FNor.y, 2) + powf(m_FNor.z, 2)) * sqrtf(powf(Vec2.x, 2) + powf(Vec2.y, 2) + powf(Vec2.z, 2)));
		fRot = acosf(fTilt);
		fTilt = (fTilt * -1.0f) * 2.0f;
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "傾斜 %f\n", fTilt);
		CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "角度 %f\n", fRot);
		//if (fTilt < 0.8f && fTilt < 1.2f) { fTilt = 0.0f; }
		//else { fTilt *= fTilt; }
	}

	if (m_nNumMotion[0] <= MOTION_LAND)
	{//移動方向にモデルの向きを合わせる
		float fRotPoor = m_fRot - m_rot.y;
		if (fRotPoor > D3DX_PI) { fRotPoor -= D3DX_PI * 2.0f; }
		else if (fRotPoor < -D3DX_PI) { fRotPoor += D3DX_PI * 2.0f; }
		m_rot.y += fRotPoor * 0.125f;
		if (m_rot.y > D3DX_PI) { m_rot.y -= D3DX_PI * 2; }
		if (m_rot.y < -D3DX_PI) { m_rot.y += D3DX_PI * 2; }
	}

	//if (CManager::GetInputKey()->GetTrigger(DIK_Z)) { CCharacter::ResetMotion(); }
	//if (CManager::GetInputKey()->GetTrigger(DIK_B)) { m_fFramePlus = 0.0f; }
	//if (CManager::GetInputKey()->GetTrigger(DIK_N)) { SetPlusFrame(1.0f, 120.0f); }

	//モーションキャンセルの更新
	CancelUpdate();
	CMotion		*pMotion = CMotion::GetMotion(m_Type);
	COneMotion	*pOneMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];
	CKey		*pKey = pOneMotion->GetKey()[m_nNumMotion[2]];
	CKey		*pKeyold;

	if (bMove)
	{//移動
		if (m_nNumMotion[1] == -1 && m_bJump)
		{//モーションの予約がない
			COneMotion *pMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];
			if (pMotion->GetnOtherCancel(0) < m_fMotionFrame && m_fMotionFrame < pMotion->GetnOtherCancel(1))
			{
				m_nNumMotion[1] = MOTION_WALK;
			}
		}
		m_move += D3DXVECTOR3(sinf(m_fRot), 0.0f, cosf(m_fRot)) * -((m_fSpeed + (m_bJump ? fTilt : 0.0f)) * pKey->GetfMove() * fFrameP);
	}
	else if (m_nNumMotion[1] == -1)
	{//移動無し
		if (m_nNumMotion[0] == MOTION_WALK)
		{//歩きなら　足に合わせてニュートラルへ
			if (m_nNumMotion[2] % 2 == 0 && m_fFrame <= 1.0f) { m_nNumMotion[1] = MOTION_NEUTRAL; }
		}
	}

	//モーション
	if (m_Type != CMotion::TYPE_MAX)
	{
		D3DXVECTOR3 Move;
		while (1)
		{
			if (m_fFrame < (float)pKey->GetnFrame())
			{//フレームが範囲内なら
				m_move.x += (0.0f - m_move.x) * (0.3f * pKey->GetfSlip());
				m_move.z += (0.0f - m_move.z) * (0.3f * pKey->GetfSlip());
				SetEffect(pKey);	//キー効果

				//移動値加算有効フレームなら
				if (m_fFrame < (float)pKey->GetnMoveType() * fFrameP)
				{
					float fRot = m_rot.y;
					Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					Move += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * -pKey->GetMove().z;
					Move += D3DXVECTOR3(sinf(fRot + D3DX_PI * 0.5f), 0.0f, cosf(fRot + D3DX_PI * 0.5f)) * -pKey->GetMove().x;
					Move += Move * ((fFrameP - 1.0f) * 0.35f);
					float fWKData = (float)pKey->GetnMoveType() / fFrameP;
					if (fWKData < 1.0f) { fWKData = 1.0f; }
					else if (fWKData > fFrameP) { fWKData = fFrameP; }
					Move.y += pKey->GetMove().y * fWKData;

					if (pKey->GetMove().y > 0.0f)
					{
						m_bJump = false;
					}
					m_move += Move;
				}

				m_addpos += m_addPosmove * fFrameP;		//本体の移動
				for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
				{//保存されたmove分動かす
				 //rotの移動値加算
					m_pParts[nCntModel]->Getaddrot() += m_pParts[nCntModel]->GetaddRotmove() * fFrameP;
					//ロット確認
					if (m_pParts[nCntModel]->Getaddrot().x > D3DX_PI) { m_pParts[nCntModel]->Getaddrot().x -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->Getaddrot().x < -D3DX_PI) { m_pParts[nCntModel]->Getaddrot().x += D3DX_PI * 2; }
					if (m_pParts[nCntModel]->Getaddrot().y > D3DX_PI) { m_pParts[nCntModel]->Getaddrot().y -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->Getaddrot().y < -D3DX_PI) { m_pParts[nCntModel]->Getaddrot().y += D3DX_PI * 2; }
					if (m_pParts[nCntModel]->Getaddrot().z > D3DX_PI) { m_pParts[nCntModel]->Getaddrot().z -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->Getaddrot().z < -D3DX_PI) { m_pParts[nCntModel]->Getaddrot().z += D3DX_PI * 2; }
				}
				//進撃のフレーム
				m_fFrame += fFrameP / FRAME_SPEED;//フレームの進行
				m_fMotionFrame += fFrameP / FRAME_SPEED; //モーション全体フレームの進行
				break;
			}
			else
			{//キーの終了
				m_fFrame = 0.0f;	//フレームの初期化
				SetRotMotion();
				m_nNumMotion[2]++;		//キーの進撃

				if (m_nNumMotion[2] >= pOneMotion->GetnMaxKey())
				{//そのモーションが終了
					m_fRot = m_rot.y;	//妙な回転防止
					if (pOneMotion->GetnNorBranch() > -1)
					{
						m_fMotionFrame = 0.0f;		//全フレームの初期化
						m_nNumMotion[2] = 0;		//キーの初期化
						if (m_nNumMotion[0] != pOneMotion->GetnNorBranch())
						{//ループじゃなければ
							m_nNumMotion[0] = pOneMotion->GetnNorBranch();	//次のモーションの付与
							//if (m_nNumMotion[0] == MOTION_NEUTRAL && !GetbJump())
							//{//空中ニュートラルへ
							//	m_nNumMotion[0] = MOTION_S_NEUTRAL;
							//}	//ニュートラルなら
								//if (g_model_Info[nCount].set.nNumMotion[1] == MOTION_GETUP) { g_model_Info[nCount].set.nAirTime = 90; }	//起き上がりなら
						}
						else
						{
							m_nNumMotion[0] = pOneMotion->GetnNorBranch();
							//if (g_model_Info[nCount].set.nNumMotion[1] == 0 || g_model_Info[nCount].set.nNumMotion[1] == MOTION_AIR)
							//{
							//	g_model_Info[nCount].set.state = MODEL_STATE_NONE;
							//}	//ニュートラルなら
						}	//次のモーションの付与}
						m_nNumMotion[3] = m_nNumMotion[0]; //今のモーションに現在のモーションを入れる
					}
					else
					{//次のキー設定がされていないならそのまま放置
						m_fMotionFrame -= pOneMotion->GetKey()[pOneMotion->GetnMaxKey() - 1]->GetnFrame();	//モーションフレームを戻す
						m_nNumMotion[2]--;																	//キーを戻す
						m_fFrame = 0.0f;
					}
				}
				pOneMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];
				pKeyold = pKey;
				pKey = pOneMotion->GetKey()[m_nNumMotion[2]];

				m_addPosmove = (pKey->GetPos() - m_addpos) / (float)pKey->GetnFrame() / FRAME_SPEED;
				for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
				{//moveを計算して代入
					m_pParts[nCntModel]->Getaddrot() = pKeyold->GetpRot()[nCntModel];
					m_pParts[nCntModel]->GetaddRotmove() = (pKey->GetpRot()[nCntModel] - m_pParts[nCntModel]->Getaddrot()) / FRAME_SPEED;

					//角度確認
					if (m_pParts[nCntModel]->GetaddRotmove().x > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().x -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->GetaddRotmove().x < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().x += D3DX_PI * 2; }
					if (m_pParts[nCntModel]->GetaddRotmove().y > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().y -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->GetaddRotmove().y < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().y += D3DX_PI * 2; }
					if (m_pParts[nCntModel]->GetaddRotmove().z > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().z -= D3DX_PI * 2; }
					else if (m_pParts[nCntModel]->GetaddRotmove().z < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().z += D3DX_PI * 2; }

					m_pParts[nCntModel]->GetaddRotmove() /= (float)pKey->GetnFrame();
				}
			}//キー終了
		}//更新while
		m_fFramePlus += (1.0f - m_fFramePlus) * 0.1f;
		m_fInitFrame -= m_fFramePlus / FRAME_SPEED;
		if (m_fInitFrame < 0.0f)
		{//時間経過が完了した
			m_fInitFrame = 0.0f;
			m_fFramePlus2 += (0.0f - m_fFramePlus2) * 0.05f;
		}
	}

	//位置等の更新
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		m_posold = m_pos;
		m_pos += m_move;
		if (pKey->GetnFloating() < 2 && GetObjType() != CScene::OBJTYPE_ENEMY) { m_move.y -= 0.3f; }
	}

	int		nCount = 0;
	//CMesh::MeshCollisionWall(m_pos, m_posold, m_move, m_length, m_FNor, nCount, m_bJump, false);	//メッシュ壁
	
	if (GetObjType() != CScene::OBJTYPE_ENEMY)
	{
		CMesh::MeshCollisionCeiling(m_pos, m_posold, m_length);											//メッシュ屋根
		pScene = CSceneObjct::CollisionAll(m_pos, m_posold, m_move, m_length, m_FNor, nCount, m_bJump, true);	//オブジェクト
		CMesh::MeshCollisionWall(m_pos, m_posold, m_move, m_length, m_FNor, nCount, m_bJump, false);	//メッシュ壁
		//CMesh::MeshCollisionField(m_pos, m_posold, m_move, m_length, m_FNor, bLand);					//メッシュ床
	}
	else { CCharacter::CollisionAll(m_pos, m_posold, m_length.x, this); }

	if (!m_bJump && bLand && pKey->GetnFloating() == 0)
	{//着地
		SetCancelMotion(pOneMotion->GetnLandBranch());
		m_move.y = 0.0f;
		m_bJump = true;
	}

	if (pScene != NULL)
	{//何かに乗っている
		D3DXVECTOR3 move;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		float		fDistance;
		float		fAngle;
		float		fPosY;
		switch (pScene->GetObjType())
		{
		case OBJTYPE_OBJ:
			move = ((CSceneObjct*)pScene)->GetMove();
			pos = ((CSceneObjct*)pScene)->GetPosold();
			rot = ((CSceneObjct*)pScene)->GetRotation() - ((CSceneObjct*)pScene)->GetRotOld();
			if (move.y < 0) { move.y = 0.0f; }
			fDistance = sqrtf(powf(pos.x - m_pos.x, 2) + powf(pos.z - m_pos.z, 2));
			fAngle = atan2f(m_pos.x - pos.x, m_pos.z - pos.z);
			fPosY = m_pos.y;
			m_pos = pos + D3DXVECTOR3(sinf(fAngle + rot.y), 0.0f, cosf(fAngle + rot.y)) * fDistance;
			m_pos.y = fPosY;
			m_pos += move;
			m_rot.y += rot.y;
			if (m_pScene == NULL) 
			{ SetCancelMotion(pOneMotion->GetnLandBranch()); m_bJump = true; }
			m_pScene = pScene;
			break;
		}
	}
	else { m_pScene = NULL; }

	if (m_pShadow != NULL)
	{
		m_pShadow->GetPosition().x = m_pos.x;
		m_pShadow->GetPosition().z = m_pos.z;

		if (m_bJump) { m_pShadow->GetPosition().y = m_pos.y - 2.0f; }
		else
		{
			if (m_pShadow->GetPosition().y > m_pos.y) { m_pShadow->GetPosition().y = m_pos.y - 2.0f; }
		}
		if (GetObjType() == CScene::OBJTYPE_ENEMY) { m_pShadow->GetPosition() = m_pos; }

	}

	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "Pフレーム：%.3f\n", fFrameP);
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "モーション 現在：%d　次：%d キー：%d フレーム：%.1f\n", m_nNumMotion[0], m_nNumMotion[1], m_nNumMotion[2], m_fFrame);
	CManager::GetDLog()->Printf(CDebugLog::MODE_INFO, "法線 %.1f　%.1f　%.1f\n", m_FNor.x, m_FNor.y, m_FNor.z);
}
//=============================================================================
// 着地処理
//=============================================================================
void	CCharacter::Land(void)
{
	if (!m_bJump)
	{
		COneMotion *pOneMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];

		SetCancelMotion(pOneMotion->GetnLandBranch());
		m_bJump = true;
	}
		m_move.y = 0.0f;
}
//=============================================================================
// キャラクターの描画
//=============================================================================
void CCharacter::Draw(void)
{
	if (CManager::GetCamera()->DrawCamera(m_pos, powf(m_length.x, 2) + powf(m_length.z, 2)))
	{
		LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	//デバイスの取得
		D3DXMATRIX			mtxRot, mtxTrans;		//計算用マトリックス
		D3DMATERIAL9		matDef;					//現在のマテリアル保存用
		D3DXMATERIAL		*pMat;					//マテリアルデータへのポインタ
		D3DXVECTOR3			pos, rot;

		if (CScene::DrawPrepare(m_DrawType, pDevice)) { return; };

		for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
		{//パーツ分だけ回転

		 // ワールドマトリックスの初期化
			D3DXMatrixIdentity(&m_pParts[nCntModel]->GetmtxWorld());

			if (m_pParts[nCntModel]->GetnParent() >= 0)
			{//子供なら加算分代入
				pos = m_partsAll[m_pParts[nCntModel]->GetParts()]->addPos;
				rot = m_pParts[nCntModel]->Getaddrot();
			}
			else
			{//親なしなら原点から
				pos = m_pos + m_addpos;
				pos += D3DXVECTOR3(sinf(m_rot.y) * m_partsAll[m_pParts[nCntModel]->GetParts()]->addPos.z
					, m_partsAll[m_pParts[nCntModel]->GetParts()]->addPos.y
					, cosf(m_rot.y) * m_partsAll[m_pParts[nCntModel]->GetParts()]->addPos.z);
				rot = m_pParts[nCntModel]->Getaddrot() + m_rot;
			}

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
			D3DXMatrixMultiply(&m_pParts[nCntModel]->GetmtxWorld(), &m_pParts[nCntModel]->GetmtxWorld(), &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
			D3DXMatrixMultiply(&m_pParts[nCntModel]->GetmtxWorld(), &m_pParts[nCntModel]->GetmtxWorld(), &mtxTrans);

			if (m_pParts[nCntModel]->GetnParent() >= 0)
			{//親の位置と角度をプラス
				D3DXMatrixMultiply(&m_pParts[nCntModel]->GetmtxWorld(), &m_pParts[nCntModel]->GetmtxWorld(), &m_pParts[m_pParts[nCntModel]->GetnParent()]->GetmtxWorld());
			}

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &m_pParts[nCntModel]->GetmtxWorld());

			// 現在のマテリアルを取得
			pDevice->GetMaterial(&matDef);
			pMat = (D3DXMATERIAL*)m_partsAll[m_pParts[nCntModel]->GetParts()]->pBuffMatModel->GetBufferPointer();
			//テクスチャの設定
			//if (GetTexture(m_partsAll[m_pParts[nCntModel]->GetParts()]->tex) != NULL)
			//{//テクスチャの設定
			//	pDevice->SetTexture(0, GetTexture(m_partsAll[m_pParts[nCntModel]->GetParts()]->tex));
			//}//テクスチャ削除

			// マテリアルデータへのポインタを取得
			for (int nCountData = 0; nCountData < (int)m_partsAll[m_pParts[nCntModel]->GetParts()]->nNumMatModel; nCountData++)
			{
				// マテリアルの設定
				pMat = (D3DXMATERIAL*)m_partsAll[m_pParts[nCntModel]->GetParts()]->pBuffMatModel->GetBufferPointer();
				pMat[nCountData].MatD3D.Diffuse.a = m_fCola; //透明度設定

				pDevice->SetMaterial(&pMat[nCountData].MatD3D);

				// モデル(パーツ)の描画
				m_partsAll[m_pParts[nCntModel]->GetParts()]->MeshModel->DrawSubset(nCountData);
			}

			// マテリアルをデフォルトに戻す
			pDevice->SetMaterial(&matDef);
			pDevice->SetTexture(0, NULL);

		}
	}//範囲内なら描画
}
//=============================================================================
// モーションのキャンセル更新
//=============================================================================
void CCharacter::CancelUpdate(void)
{
	if (m_nNumMotion[1] != -1 && m_nNumMotion[0] != m_nNumMotion[1])
	{//予約が入っている && 現在のモーションでない
		COneMotion *pMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];
		bool bCancel = false;
		bool bStart = false;

		if (pMotion->GetnOtherCancel(0) < m_fFrame && m_fFrame < pMotion->GetnOtherCancel(1))
		{//キャンセル可能
			//CManager::GetDLog()->Printf(CDebugLog::MODE_LOG, "キャンセル！\n");

			bCancel = true;
		}
		//else if (MOTION_ATTACK <= m_nNumMotion[1])
		//{//予約が攻撃モーションなら
		//	if ((pMotion->GetnStartCancel(0) < m_fFrame && m_fFrame < pMotion->GetnStartCancel(1)) ||
		//		(pMotion->GetnEndCancel(0) < m_fFrame && m_fFrame < pMotion->GetnEndCancel(1)))
		//	{//キャンセル可能
		//		bCancel = true;
		//		bStart = true;		//スタートキャンセル適用
		//	}
		//}

		if (bCancel)
		{//キャンセルが可能
			SetCancelMotion(m_nNumMotion[1]);	//モーションのキャンセル
			m_nNumMotion[1] = -1;				//次モーション初期化
			m_nCancelFrame = -1;				//モーションキャンセル保持フレーム初期化
		}
	}
	{//一定Ｆ数保持
		m_nCancelFrame--;
		if (m_nCancelFrame < 0) { m_nNumMotion[1] = -1; m_nCancelFrame = 0; }//次モーション初期化
	}
}
//=============================================================================
// モーションのキャンセル設定
//=============================================================================
void CCharacter::SetCancelMotion(int nNumber)
{
	if (m_nNumMotion[0] == MOTION_WALK && m_nNumMotion[1] == MOTION_NEUTRAL) { m_nLeg = m_nNumMotion[2]; }

	m_nNumMotion[3] = m_nNumMotion[0];	//前モーション代入
	m_nNumMotion[0] = nNumber;			//モーションのキャンセル
	m_nNumMotion[2] = 0;
	m_nNumMotion[1] = -1;				//次モーションの初期化
	m_fFrame = 0.0f;			//フレーム数初期化
	m_fMotionFrame = 0.0f;		//モーション全体フレーム数初期化

	if (m_nNumMotion[0] == MOTION_WALK) { m_nNumMotion[2] = m_nLeg; }		//歩きなら前回の途中から

	COneMotion *pMotion = &CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]];
	CKey *pKey = pMotion->GetKey()[0];

	m_addPosmove = (pKey->GetPos() - m_addpos) / (float)pKey->GetnFrame() / FRAME_SPEED;
	for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
	{//moveを計算して代入
		m_pParts[nCntModel]->GetaddRotmove() = (pKey->GetpRot()[nCntModel] - m_pParts[nCntModel]->Getaddrot()) / FRAME_SPEED;

		//角度確認
		if (m_pParts[nCntModel]->GetaddRotmove().x > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().x -= D3DX_PI * 2; }
		else if (m_pParts[nCntModel]->GetaddRotmove().x < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().x += D3DX_PI * 2; }
		if (m_pParts[nCntModel]->GetaddRotmove().y > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().y -= D3DX_PI * 2; }
		else if (m_pParts[nCntModel]->GetaddRotmove().y < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().y += D3DX_PI * 2; }
		if (m_pParts[nCntModel]->GetaddRotmove().z > D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().z -= D3DX_PI * 2; }
		else if (m_pParts[nCntModel]->GetaddRotmove().z < -D3DX_PI) { m_pParts[nCntModel]->GetaddRotmove().z += D3DX_PI * 2; }

		m_pParts[nCntModel]->GetaddRotmove() /= (float)pKey->GetnFrame();
	}
}
//=============================================================================
// モーションのリセット
//=============================================================================
void CCharacter::ResetMotion(void)
{
	m_nNumMotion[0] = 0;
	m_nNumMotion[1] = -1;
	m_nNumMotion[2] = 0;
	m_nNumMotion[3] = 0;
	m_fFrame = 99999.0f;
	SetRotMotion();
}
//=============================================================================
// 現在のキーに角度を完全に合わせる
//=============================================================================
void CCharacter::SetRotMotion(void)
{
	CKey *pKey = CMotion::GetMotion(m_Type)->GetOneMotion()[m_nNumMotion[0]].GetKey()[m_nNumMotion[2]];
	for (int nCntModel = 0; nCntModel < m_nMaxParts; nCntModel++)
	{//moveを計算して代入
		m_pParts[nCntModel]->Getaddrot() = pKey->GetpRot()[nCntModel];
	}
}
//=============================================================================
// フレームの進行速度設定
//=============================================================================
void CCharacter::SetPlusFrame(float fPFrame, float fCount)
{
	m_fFramePlus2 = fPFrame;
	m_fInitFrame = fCount;
}
//=============================================================================
//	キー事の効果
//=============================================================================
void CCharacter::SetEffect(CKey *&pKey)
{
	for (int nCount = 0; nCount < pKey->GetnMaxEffect(); nCount++)
	{
		switch (pKey->GetpEffect()[nCount])
		{
		case 0:	if (m_fFrame == 0.0f) { CManager::GetSound()->Play(CSound::LABEL_SE_WALK); } break;	//
		case 1:	if (m_fFrame == 0.0f) { CManager::GetSound()->Play(CSound::LABEL_SE_JUMP); } break;	//
		case 2:	if (m_fFrame == 0.0f) { CManager::GetSound()->Play(CSound::LABEL_SE_LAND); } break;	//

		}
	}
}
//=============================================================================
//	全キャラのあたり判定
//=============================================================================
void CCharacter::CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, float &fLength, CScene *pChar)	//キャラ同士のあたり判定
{
	if (CManager::GetMode() != CManager::MODE_GAME) { return; }

	CScene *pScene;

	pScene = CScene::GetTop(CHAR_PRIORITY);
	while (pScene != NULL)
	{//終わるまで
		if (pScene->GetObjType() == OBJTYPE_ENEMY || pScene->GetObjType() == OBJTYPE_PLAYER)
		{//メッシュ発見
			if (pChar != pScene)
			{//自分でないなら
				((CCharacter*)pScene)->Collision(pos, posold, fLength);
			}
		}
		pScene = pScene->GetpNext();
	}
}
//=============================================================================
//	キャラ同士のあたり判定
//=============================================================================
void CCharacter::Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, float &fLength)
{
	float fDistance, fAngle;

	//攻撃中ならY無視

	//中心貫通対策

	//円形範囲内なら
	fDistance = powf(m_pos.x - pos.x, 2) + powf(m_pos.z - pos.z, 2);
	if (fDistance < powf(fLength + m_length.x, 2))
	{//自身から見た角度で一定値離す
		fAngle = atan2f(pos.x - m_pos.x, pos.z - m_pos.z);
		pos = D3DXVECTOR3(m_pos.x, pos.y, m_pos.z) + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)) * (fLength + m_length.x);

		float &fRot = CManager::GetPlayer()->Getrot().y;
		fRot = atan2f(pos.x - m_pos.x, pos.z - m_pos.z) + D3DX_PI;
		CManager::GetPlayer()->SetCancelMotion(CCharacter::MOTION_LAND + 1);
		CManager::GetPlayer()->Getmove() += D3DXVECTOR3(sinf(fRot), 0.0f, cosf(fRot)) * 30.0f;
		CManager::GetPlayer()->Getmove().y = 5.0f;
		CManager::GetGame()->SetState(CGame::STATE_OVER);

	}
}
//=============================================================================
// キャラクターの設定
//=============================================================================
void CCharacter::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type)
{
	m_pos = pos; m_posold = pos;
	m_rot = rot;
	m_fRot = rot.y;
	m_Type = type;
	m_pShadow = NULL;
	if (GetObjType() != CScene::OBJTYPE_ENEMY)
	{
		CScene3D *p3D;
		if (SceneCreate(p3D, 6))
		{
			p3D->Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(20.0f, 0.0f, 20.0f),
				CScene::TEX_Shadow, 0, 1, 1, false, CScene::DRAW_TYPE_ZSUBTRACT);
			m_pShadow = p3D;
		}
	}

	switch (type)
	{
	case CMotion::TYPE_BOX_Sword:	CCharParts::SetPlayer(m_pParts, m_nMaxParts);	break;
	case CMotion::TYPE_ENEMY:	CCharParts::SetEnemy(m_pParts, m_nMaxParts);	break;

	}
	
}
//=============================================================================
// パーツの設定
//=============================================================================
void CCharParts::SetParts(PARTS parts, int nPair)
{
	m_type = parts;
	m_nParent = nPair;
	CCharacter::Load(m_type);
}
//=============================================================================
// キャラクターの設定
//=============================================================================
void CCharParts::SetPlayer(CCharParts **&Parts, int &nMaxParts)
{
	nMaxParts = 15;

	if (Parts == NULL) 
	{ 
		Parts = new CCharParts*[nMaxParts];
		for (int nCount = 0; nCount < nMaxParts; nCount++)
		{
			Parts[nCount] = new CCharParts;
		}
	}
	
	for (int nCount = 0; nCount < nMaxParts; nCount++)
	{
		Parts[nCount]->GetaddRotmove() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Parts[nCount]->Getaddrot() = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	}
	Parts[0]->SetParts(PLAYER_hara, -1);
	Parts[1]->SetParts(PLAYER_hip, 0);
	Parts[2]->SetParts(PLAYER_head, 0);
	Parts[3]->SetParts(PLAYER_armUL, 0);
	Parts[4]->SetParts(PLAYER_armDL, 3);
	Parts[5]->SetParts(PLAYER_handL, 4);
	Parts[6]->SetParts(PLAYER_armUR, 0);
	Parts[7]->SetParts(PLAYER_armDR, 6);
	Parts[8]->SetParts(PLAYER_handR, 7);
	Parts[9]->SetParts(PLAYER_legUL, 1);
	Parts[10]->SetParts(PLAYER_legDL, 9);
	Parts[11]->SetParts(PLAYER_footL, 10);
	Parts[12]->SetParts(PLAYER_legUR, 1);
	Parts[13]->SetParts(PLAYER_legDR, 12);
	Parts[14]->SetParts(PLAYER_footR, 13);
}
//=============================================================================
// 敵の設定
//=============================================================================
void CCharParts::SetEnemy(CCharParts **&Parts, int &nMaxParts)
{
	nMaxParts = 1;

	if (Parts == NULL)
	{
		Parts = new CCharParts*[nMaxParts];
		for (int nCount = 0; nCount < nMaxParts; nCount++)
		{
			Parts[nCount] = new CCharParts;
		}
	}

	for (int nCount = 0; nCount < nMaxParts; nCount++)
	{
		Parts[nCount]->GetaddRotmove() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Parts[nCount]->Getaddrot() = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	Parts[0]->SetParts(ENEMY, -1);
}