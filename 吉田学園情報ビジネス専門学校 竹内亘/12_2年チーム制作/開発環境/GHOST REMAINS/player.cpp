//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include "main.h"
#include "Game.h"
#include "motion.h"
#include "player.h"
#include "bullet.h"
#include "sound.h"
#include "camera.h"
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

//==================================================================================================//
//    * プレイヤーのセット関数 *
//==================================================================================================//
void CPlayer::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type)	//ゲージセット処理
{
	m_fDistance = 450.0f;
	CCharacter::Set(pos, rot, type);

	CCamera::GetInfo().pChar = &Getpos();
	CCamera::GetInfo().pMove = &Getposold();
	//CManager::GetCamera()->GetRot().y = rot.y + D3DX_PI * -0.5f;

	CManager::GetCamera()->GetpDistance() = &m_fDistance;
	CManager::GetCamera()->Reset();
}
//=============================================================================
// プレイヤーの初期化処理
//=============================================================================
HRESULT  CPlayer::Init(void)
{
	CCharacter::Init();
	CManager::GetPlayer() = this;
	m_bDrop = false;
	SetObjType(CScene::OBJTYPE_PLAYER);
	m_fStop = 0.0f;
	m_fHeart = 0.0f;
	return S_OK;
}
//=============================================================================
// プレイヤーの終了処理
//=============================================================================
void  CPlayer::Uninit(void)
{
	CManager::GetPlayer() = NULL;
	CCharacter::Uninit();
}
//=============================================================================
// プレイヤーの更新処理
//=============================================================================
void CPlayer::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKey();
	CInputJoyPad	*pInputPad0 = CManager::GetInputJoyPad(0);	//ジョイパッド情報獲得
	float	fMoveX = 0.0f, fMoveZ = 0.0f;	//移動方向計算用
	bool bMove = false;

	if (m_fStop == 0.0f)
	{
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			if (pInputKey->GetPress(DIK_W)) { fMoveZ = -1.0f; }
			if (pInputKey->GetPress(DIK_S)) { fMoveZ = 1.0f; }
			if (pInputKey->GetPress(DIK_A)) { fMoveX = 1.0f; }
			if (pInputKey->GetPress(DIK_D)) { fMoveX = -1.0f; }

			if (fMoveX != 0.0f || fMoveZ != 0.0f)
			{//動いているなら
				float &fRot = GetfRot();
				bMove = true;
				fRot = atan2f(fMoveX, fMoveZ) + CManager::GetCamera()->GetRot().y + D3DX_PI;	//移動方向計算
				if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2; }
				if (fRot < -D3DX_PI) { fRot += D3DX_PI * 2; }
			}
			else if (pInputPad0->GetStickDefeat(0))
			{
				float &fRot = GetfRot();
				bMove = true;
				fRot = pInputPad0->GetfStickAngle(0) + CManager::GetCamera()->GetRot().y;	//移動方向計算
				if (fRot > D3DX_PI) { fRot -= D3DX_PI * 2; }
				if (fRot < -D3DX_PI) { fRot += D3DX_PI * 2; }
			}

			//if (CManager::GetInputKey()->GetTrigger(DIK_T)) { Getpos().y += 200.0f; Getmove().y = 0.0f; }

			if ((CManager::GetInputKey()->GetTrigger(DIK_SPACE) || pInputPad0->GetTrigger(INPUT_A)) && GetbJump())
			{
				if (GetnNumMotion(0) <= MOTION_LAND) { SetCancelMotion(MOTION_JUMP); }
			}
		}
		CCharacter::Update(bMove);

		if (Getpos().y < -50.0f && !m_bDrop && CManager::GetMode() == CManager::MODE_GAME)
		{
			float fDrot = CManager::GetCamera()->GetRot().y + D3DX_PI;
			m_bDrop = true;
			m_fDistance = 50.0f;
			if (fDrot > D3DX_PI) { fDrot -= D3DX_PI * 2; }
			if (fDrot < -D3DX_PI) { fDrot += D3DX_PI * 2; }
			CManager::GetCamera()->GetfDRot() = fDrot;
			CManager::GetGame()->SetState(CGame::STATE_OVER);
		}
		else if(!m_bDrop && CManager::GetMode() == CManager::MODE_GAME)
		{
			m_fHeart += 1.0f;
			if (m_fHeart > 120)
			{
				m_fHeart = 0.0f;
				CManager::GetSound()->Play(CSound::LABEL_SE_HEARTBEAT);	//心音
			}
		}
	}
	else 
	{
		m_fStop -= 1.0f;
		if (m_fStop < 0.0f)
		{
			m_fStop = 0.0f;
		}
	}
}

