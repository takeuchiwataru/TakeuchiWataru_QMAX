//=============================================================================
//
// ポリゴン処理 [SceneAnim3D.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#include"Scene3D.h"
#include"SceneAnim3D.h"
#include"player.h"
#include"Renderer.h"
#include "manager.h"
#include "camera.h"
#include "Game.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneAnim3D::Init(void)
{
	CScene3D::Init();
	m_animation = ANIMATION_NORMAL;
	m_nCntAnim = -1;
	m_nPtnAnim = 0;
	m_nPtnWide = 1;
	m_nPtnHeight = 1;
	m_nPtnSpeed = 1;
	return S_OK;
}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneAnim3D::Update(void)
{//アニメーション
	VERTEX_3D *pVtx;
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	D3DXVECTOR3 &pos = GetPosition();	D3DXVECTOR3 &rot = GetRotation();	D3DXCOLOR	&col = GetColor();
	D3DXVECTOR3 &length = GetLength();
	D3DXVECTOR3 *PlayerPos;
	STATE &state = GetState();			float &fCntState = GetfCntState();
	float fLength;
	float fDistance;

 //頂点バッファをロックし、頂点データへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nCntAnim++;
	if (m_nCntAnim % m_nPtnSpeed == 0)
	{//UV変更
		m_nPtnAnim++;
		if (m_nPtnAnim >= m_nPtnWide * m_nPtnHeight)
		{//画像の範囲外
			if (m_animation == ANIMATION_LOOP) { m_nPtnAnim = 0; }
			else { Uninit(); return; }
		}

		//UVの設定
		pVtx[0].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide)						, (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight));
		pVtx[1].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide) + (1.0f / m_nPtnWide) , (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight));
		pVtx[2].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide)						, (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight) + (1.0f / m_nPtnHeight));
		pVtx[3].tex = D3DXVECTOR2((m_nPtnAnim % m_nPtnWide) * (1.0f / m_nPtnWide) + (1.0f / m_nPtnWide) , (m_nPtnAnim / m_nPtnWide) * (1.0f / m_nPtnHeight) + (1.0f / m_nPtnHeight));
	}

	switch (state)
	{
	case STATE_FADE:
		fCntState += 0.03f;
		col.a = fCntState;//透明度変更
		length *= 1.0f + (fCntState * 0.075f);

		if (fCntState >= 0.5f)
		{ 
			col.a = 0.5f;
			fCntState = 0.5f; state = STATE_FADEOUT;
		}
		break;
	case STATE_FADEOUT:
		fCntState += 0.03f;
		if (fCntState >= 1.0f) { Uninit(); return; }
		col.a = 1.0f - fCntState;//透明度変更
		length *= 1.0f + (fCntState * 0.075f);
		break;
	case STATE_FADEOUT2:
		fCntState += 0.05f;
		rot.y += D3DX_PI * 0.03f;
		if (fCntState >= 1.0f) { Uninit(); return; }
		col.a = 1.0f - fCntState;//透明度変更
		length *= 1.0f - ((1.0f - fCntState) * 0.1f);
		SetColor(col);
		SetSize(length);
		break;
	case STATE_FADEOUTN:
		col.a -= 0.03f;//透明度変更
		if (col.a <= 0.0f) { Uninit(); return; }
		break;
	case STATE_FIRE:
		CSceneAnim3D *pAnim;
		if (SceneCreate(pAnim, 3))
		{
			pAnim->Set(pos + D3DXVECTOR3((rand() % 50) * 1.0f - 25.0f, (rand() % 50) * 1.0f - 25.0f, (rand() % 50) * 1.0f - 25.0f),
				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(100.0f, 400.0f, 0.0f), CScene::TEX_Fire, true,
				CScene::DRAW_TYPE_ADD, 0, 8, 1, 6, CSceneAnim3D::ANIMATION_NORMAL, CScene3D::STATE_NORMAL);
		}
		if (CManager::GetMode() != CManager::MODE_GAME) { return; }
		PlayerPos = &CManager::GetPlayer()->Getpos();
		//長さ計算
		fDistance = powf(pos.x - PlayerPos[0].x, 2) + powf(pos.z - PlayerPos[0].z, 2);
		fLength = (GetLength().x / 2) * (GetLength().x / 2);
		if (fDistance <= fLength)
		{
			CManager::GetPlayer()->SetCancelMotion(CCharacter::MOTION_LAND + 1);
			CManager::GetSound()->Play(CSound::LABEL_SE_FIRE);
			CManager::GetGame()->SetState(CGame::STATE_OVER);
		}
		break;
	}
	//for (int nCount = 0; nCount < 4; nCount++) { pVtx[nCount].col = col; }
	//pVtx[0].pos = D3DXVECTOR3(-fLengthX[0], 0.1f, fLengthZ[0]);
	//pVtx[1].pos = D3DXVECTOR3(fLengthX[0], 0.1f, fLengthZ[0]);
	//pVtx[2].pos = D3DXVECTOR3(-fLengthX[0], 0.1f, -fLengthZ[0]);
	//pVtx[3].pos = D3DXVECTOR3(fLengthX[0], 0.1f, -fLengthZ[0]);

	//頂点バッファのアンロック
	pVtxBuff->Unlock();
}

//=============================================================================
// 設定処理
//=============================================================================
void CSceneAnim3D::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,TEXTURE nType, bool bBillBoard,
	DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state)
{
	CScene3D::Set(pos, rot, col, length, CScene3D::TEX_MAX, nPtnAnim, nPtnWide, nPtnHeight, bBillBoard, DrawType);
	BindTexture(Load(nType));
	m_animation = animation;
	GetState() = state;
	GetfCntState() = 0.0f;
	m_nCntAnim = -1;
	m_nPtnAnim = nPtnAnim;
	m_nPtnHeight = nPtnHeight;
	m_nPtnSpeed = nPtnSpeed;
	m_nPtnWide = nPtnWide;
}
//=============================================================================
// 設定処理
//=============================================================================
void CSceneAnimEffect::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col, D3DXVECTOR3 length,TEXTURE nType, bool bBillBoard,
	DRAW_TYPE DrawType, int nPtnAnim, int nPtnWide, int nPtnHeight, int nPtnSpeed, ANIMATION animation, STATE state, D3DXVECTOR3 *pPos, CScene *pScene)
{
	CSceneAnim3D::Set(pos, rot, col, length, nType, bBillBoard, DrawType, nPtnAnim, nPtnWide, nPtnHeight, nPtnSpeed, animation, state);
	m_pPos = pPos;
	m_pScene = pScene;
}
//=============================================================================
// 更新処理
//=============================================================================
void CSceneAnimEffect::Update()
{
	if (m_pScene == NULL) { m_pPos = NULL; }
	if (m_pPos != NULL) { GetPosition() = m_pPos[0]; }
	CSceneAnim3D::Update();
}
