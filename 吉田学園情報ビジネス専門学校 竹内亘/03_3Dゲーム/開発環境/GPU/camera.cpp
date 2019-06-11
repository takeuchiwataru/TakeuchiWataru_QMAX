//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "model.h"
#include "player2.h"
//#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_camera;	// カメラの情報
int g_nCount;		// 

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f,40.0f, -200.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f,1.0f,0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.fLength = g_camera.posR.z - g_camera.posV.z;
	g_camera.fAngle = g_camera.posV.z - g_camera.posR.z;
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rotDiff = 0.0f;

	//g_camera.fAngle = 0.0f;
	//g_camera.fIntervel = 200.0f;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{

}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	// プレイヤーの取得
	Player2 *pPlayer;
	pPlayer = GetPlayer2();

	if (GetMode() == MODE_GAME)
	{
		//カメラの追従
		g_camera.posRDest.x = pPlayer->pos.x - sinf(pPlayer->rot.y) * 20;
		g_camera.posRDest.y = pPlayer->pos.y + sinf(pPlayer->rot.x) * 20;
		g_camera.posRDest.z = pPlayer->pos.z - cosf(pPlayer->rot.y) * 20;

		g_camera.posVDest.x = pPlayer->pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posVDest.y = pPlayer->pos.y + sinf(g_camera.rot.x) * g_camera.fLength + 50;
		g_camera.posVDest.z = pPlayer->pos.z - cosf(g_camera.rot.y) * g_camera.fLength;

		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.2f;
		g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.2f;
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.2f;
		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 1.0f;
		g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.2f;
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 1.0f;

		g_camera.posV.x = pPlayer->pos.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = pPlayer->pos.z - cosf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posR.x = pPlayer->pos.x;
		g_camera.posR.z = pPlayer->pos.z;

		//if (pPlayer->move.x < 0.05f && pPlayer->move.x > -0.05f /*|| pPlayer->move.z < 1.0f && pPlayer->move.z > -1.0f*/)
		//{
		//	g_nCount++;
		//	if (g_nCount >= 60)
		//	{
		//		g_camera.rotDest.y = pPlayer->rot.y + D3DX_PI;
		//		g_camera.rotDiff = g_camera.rotDest.y - g_camera.rot.y;

				if (g_camera.rotDiff > D3DX_PI)
				{
					g_camera.rotDiff -= D3DX_PI * 2.0f;
				}
				if (g_camera.rotDiff < -D3DX_PI)
				{
					g_camera.rotDiff += D3DX_PI * 2.0f;
				}

				g_camera.rot.y += g_camera.rotDiff * 0.05f;

				if (g_camera.rot.y > D3DX_PI)
				{
					g_camera.rotDiff -= D3DX_PI * 2.0f;
				}
				if (g_camera.rot.y < D3DX_PI)
				{
					g_camera.rotDiff += D3DX_PI * 2.0f;
				}
	//		}
	//	}
	//	else
	//	{
	//		g_nCount = 0;
	//	}
	}

	else if (GetMode() == MODE_TITLE)
	{// 右旋回
		g_camera.rot.y += 0.002f;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}

	else if (GetMode() == MODE_RANKING)
	{// 右旋回
		g_camera.rot.y += 0.002f;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}

	else if (GetMode() == MODE_GAMECLEAR)
	{// 左旋回
		g_camera.rot.y -= 0.002f;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}

	else if (GetMode() == MODE_GAMEOVER)
	{// 左旋回
		g_camera.rot.y -= 0.002f;
		if (g_camera.rot.y > D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	}

	// カメラ移動
	//if (GetKeyboardPress(DIK_A) == true)
	//{// 左方向に移動
	//	g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI * 0.5f) * 2.0f;
	//	g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI * 0.5f) * 2.0f;
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//	
	//	if (GetKeyboardPress(DIK_W) == true)
	//	{// 左前方向に移動
	//		g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{// 右後方向に移動
	//		g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI * 1.0f) *2.0f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_D) == true)
	//{// 右方向に移動
	//	g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 0.5f) * 2.0f;
	//	g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 0.5f) * 2.0f;
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;

	//	if (GetKeyboardPress(DIK_W) == true)
	//	{// 左前方向に移動
	//		g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//	}
	//	else if (GetKeyboardPress(DIK_S) == true)
	//	{// 左後方向に移動
	//		g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 1.0f) *2.0f;
	//		g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//	}
	//}
	//else if (GetKeyboardPress(DIK_W) == true)
	//{// 前方向に移動
	//	g_camera.posV.x -= sinf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//	g_camera.posV.z -= cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;

	//}
	//else if (GetKeyboardPress(DIK_S) == true)
	//{// 後方向に移動
	//	g_camera.posV.x += sinf(g_camera.rot.y + D3DX_PI * 1.0f) *2.0f;
	//	g_camera.posV.z += cosf(g_camera.rot.y + D3DX_PI * 1.0f) * 2.0f;
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) *g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//}

	//// 視点操作
	//if (GetKeyboardPress(DIK_Y) == true)
	//{// 上移動
	//	g_camera.posV.y -= cosf(D3DX_PI) * 2.0f;
	//}
	//else if (GetKeyboardPress(DIK_N) == true)
	//{// 下移動
	//	g_camera.posV.y += cosf(D3DX_PI) * 2.0f;
	//}
	//else if (GetKeyboardPress(DIK_Z) == true)
	//{// 左旋回
	//	g_camera.rot.y += 0.05f;
	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y = -D3DX_PI;
	//	}
	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	//}
	//else if (GetKeyboardPress(DIK_C) == true)
	//{// 右旋回
	//	g_camera.rot.y -= 0.05f;
	//	if (g_camera.rot.y < -D3DX_PI)
	//	{
	//		g_camera.rot.y = D3DX_PI;
	//	}
	//	g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength;
	//}

	//// 注視点操作
	//if (GetKeyboardPress(DIK_T) == true)
	//{// 上移動
	//	g_camera.posR.y -= cosf(D3DX_PI) * 2.0f;
	//}
	//else if (GetKeyboardPress(DIK_B) == true)
	//{// 下移動
	//	g_camera.posR.y += cosf(D3DX_PI) * 2.0f;
	//}
	//else if (GetKeyboardPress(DIK_Q) == true)
	//{// 左旋回
	//	g_camera.rot.y -= 0.05f;
	//	if (g_camera.rot.y > D3DX_PI)
	//	{
	//		g_camera.rot.y = -D3DX_PI;
	//	}
	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//}
	//if (GetKeyboardPress(DIK_E) == true)
	//{// 右旋回
	//	g_camera.rot.y += 0.05f;
	//	if (g_camera.rot.y < -D3DX_PI)
	//	{
	//		g_camera.rot.y = D3DX_PI;
	//	}

	//	g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength;
	//	g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength;
	//}
}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),									// 画角
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,				
		10.0f,													// 手前の位置
		1000.0f);												// 奥の位置

	// プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxView);

	// ビューマトリックスを作成
	D3DXMatrixLookAtLH(&g_camera.mtxView,
		&g_camera.posV,
		&g_camera.posR,
		&g_camera.vecU);

	// ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}
//=============================================================================
// カメラの取得
//=============================================================================
Camera *GetCamera(void)
{
	return &g_camera;
}



