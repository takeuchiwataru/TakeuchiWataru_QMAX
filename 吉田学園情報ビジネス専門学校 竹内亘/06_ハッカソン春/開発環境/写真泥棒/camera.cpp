//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "camera.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CAMERA_ANGEL_VIEW  (45.0f)    // カメラの画角
#define CAMERA_MOVE        (15.0f)    // カメラの移動量
#define AROUND_SPEED       (0.02f)    // 回り込み速度初期値
#define AROUND_TIME        (50)       // 回り込み待ち時間初期値

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Camera g_camera;  // カメラの情報

//=============================================================================
// カメラの初期化処理
//=============================================================================
void InitCamera(void)
{
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);       // 現在の注視点を初期化
	g_camera.posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 目的の視点を初期化
	g_camera.posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // 目的の注視点を初期化
	g_camera.posVAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 加える分の視点を初期化
	g_camera.posRAdd = D3DXVECTOR3(0.0f, 100.0f, 0.0f);  // 加える分の注視点を初期化
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);       // ベクトルを初期化
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);        // 現在の向きを初期化
	g_camera.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 目的の向きを初期化
	g_camera.state = CAMERASTATE_NORMAL;                 // 通常の状態に
	g_camera.fWaraparoundSpeed = AROUND_SPEED;           // 回り込み速度を初期化
	g_camera.nWaraparoundTime = AROUND_TIME;             // 回り込み待ち時間を初期化
	g_camera.nCounterTime = 0;                           // 待ち時間カウンターを初期化
	g_camera.posVAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 目的の視点座標を初期化
	g_camera.posRAdd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 目的の注視点座標を初期化
	g_camera.fLength = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // 距離を初期化

	// ビューポートの設定
	g_camera.ViewPort.X = 0;                  // x座標左端
	g_camera.ViewPort.Y = 0;                  // y座標上端
	g_camera.ViewPort.Width = SCREEN_WIDTH;   // x座標右端
	g_camera.ViewPort.Height = SCREEN_HEIGHT; // x座標下端
	g_camera.ViewPort.MinZ = 0.0f;            // 手前
	g_camera.ViewPort.MaxZ = 1.0f;            // 奥側

	if (GetMode() == MODE_RANKING)
	{// ランキング画面だったら
		g_camera.fLength.x = 200;
		g_camera.fLength.y = 30;
		g_camera.fLength.z = 200;
	}
	else if (GetMode() == MODE_TITLE)
	{// タイトル画面だったら
		g_camera.fLength.x = 200;
		g_camera.fLength.y = 50;
		g_camera.fLength.z = 200;

		g_camera.posR = D3DXVECTOR3(0.0f, 300.0f, 0.0f);       // 現在の注視点を初期化
	}
	else if(GetMode() == MODE_GAME)
	{// それ以外の画面だったら
		g_camera.fLength.x = 600;
		g_camera.fLength.y = 300;
		g_camera.fLength.z = 600;
	}
	else if (GetMode() == MODE_TUTORIAL)
	{// それ以外の画面だったら
		g_camera.fLength.x = 200;
		g_camera.fLength.y = 0;
		g_camera.fLength.z = 200;
		g_camera.posR = D3DXVECTOR3(0.0f, 240.0f,800.0f);       // 現在の注視点を初期化
	}

	g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
	g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.y) * g_camera.fLength.y;
	g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
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
// デバック用カメラ操作の処理
#if 0
//-----------------
// 視点移動
//-----------------
	if (GetKeyboardPress(DIK_LEFT) == true)
	{// Aキーが押された
		if (GetKeyboardPress(DIK_UP) == true)
		{// 同時にWキーが押された
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// 同時にSキーが押された
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{// 同時に何も押されていない
			g_camera.posV.x -= sinf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y + (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{// Dキーが押された
		if (GetKeyboardPress(DIK_UP) == true)
		{// 同時にWキーが押された
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.75f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.75f)) * CAMERA_MOVE;
		}
		else if (GetKeyboardPress(DIK_DOWN) == true)
		{// 同時にSキーが押された
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.25f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.25f)) * CAMERA_MOVE;
		}
		else
		{// 同時に何も押されていない
			g_camera.posV.x -= sinf(g_camera.rot.y - (D3DX_PI * 0.5f)) * CAMERA_MOVE;
			g_camera.posV.z -= cosf(g_camera.rot.y - (D3DX_PI * 0.5f)) * CAMERA_MOVE;
		}

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	else if (GetKeyboardPress(DIK_UP) == true)
	{// Wキーが押された
		g_camera.posV.x += sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.posV.z += cosf(g_camera.rot.y) * CAMERA_MOVE;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	else if (GetKeyboardPress(DIK_DOWN) == true)
	{// Sキーが押された
		g_camera.posV.x -= sinf(g_camera.rot.y) * CAMERA_MOVE;
		g_camera.posV.z -= cosf(g_camera.rot.y) * CAMERA_MOVE;

		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	//-----------------
	// 視点旋回
	//-----------------
	if (GetKeyboardPress(DIK_Z) == true)
	{// Zキーが押された
		g_camera.rot.y -= D3DX_PI / 120;
		if (g_camera.rot.y <= -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength.z;

	}
	if (GetKeyboardPress(DIK_C) == true)
	{// Cキーが押された
		g_camera.rot.y += D3DX_PI / 120;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x - sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posV.z = g_camera.posR.z - cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	//-----------------
	// 注視点旋回
	//-----------------
	if (GetKeyboardPress(DIK_Q) == true)
	{// Qキーが押された
		g_camera.rot.y -= D3DX_PI / 120;
		if (g_camera.rot.y < -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	if (GetKeyboardPress(DIK_E) == true)
	{// Eキーが押された
		g_camera.rot.y += D3DX_PI / 120;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posR.x = g_camera.posV.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posR.z = g_camera.posV.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	//-----------------
	// カメラリセット
	//-----------------
	if (GetKeyboardPress(DIK_G) == true)
	{// SPACEキーが押された
		g_camera.posV = D3DXVECTOR3(0.0f, 130.0f, -250.0f);
		g_camera.posR = D3DXVECTOR3(0.0f, 00.0f, 0.0f);
		g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_camera.rot.y = atan2f(g_camera.posV.x - g_camera.posR.x, g_camera.posV.z - g_camera.posR.z);
	}

	//-----------------
	// 注視点上昇下降
	//-----------------
	if (GetKeyboardPress(DIK_T) == true)
	{// Tキーが押された
		g_camera.posR.y += 3.5f;
	}
	if (GetKeyboardPress(DIK_B) == true)
	{// Bキーが押された
		g_camera.posR.y -= 3.5f;
	}
	//-----------------
	// 視点上昇下降
	//-----------------
	if (GetKeyboardPress(DIK_Y) == true)
	{// Yキーが押された
		g_camera.posV.y += 3.5f;
	}
	if (GetKeyboardPress(DIK_N) == true)
	{// Nキーが押された
		g_camera.posV.y -= 3.5f;
	}

	//------------------------
	// ズームイン ズームアウト
	//------------------------
	if (GetKeyboardPress(DIK_U) == true)
	{// Uキーが押された
		if (g_camera.fLength.z >= 60)
		{
			g_camera.fLength.z -= 2.0f;
		}
	}
	if (GetKeyboardPress(DIK_M) == true)
	{// Mキーが押された
		if (g_camera.fLength.z <= 350)
		{
			g_camera.fLength.z += 2.0f;
		}
	}
#endif

	if (GetMode() == MODE_TITLE)
	{// タイトル画面だったら
		g_camera.rot.y += D3DX_PI / 1200;
		if (g_camera.rot.y >= D3DX_PI)
		{
			g_camera.rot.y = -D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	else if (GetMode() == MODE_RANKING)
	{// ランキング画面だったら
		g_camera.rot.y -= D3DX_PI / 1200;
		if (g_camera.rot.y <= -D3DX_PI)
		{
			g_camera.rot.y = D3DX_PI;
		}
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_camera.fLength.x;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_camera.fLength.z;
	}
	else if (GetMode() == MODE_GAME)
	{// ゲーム画面だったら
		Player *pPlayer = GetPlayer();  // プレイヤーの取得

		// 視点設定
		g_camera.posVDest.x = (pPlayer->pos.x + (5.0f * pPlayer->move.x)) - sinf(g_camera.rot.y) * g_camera.fLength.x;  // 目的の視点を設定
		g_camera.posVDest.y = (pPlayer->pos.y + g_camera.posVAdd.y) + cosf(0.0f) * g_camera.fLength.y / 1.7f;           // 目的の視点を設定
		g_camera.posVDest.z = (pPlayer->pos.z + (5.0f * pPlayer->move.z)) - cosf(g_camera.rot.y) * g_camera.fLength.z;  // 目的の視点を設定

		// 注視点設定
		g_camera.posRDest.x = (pPlayer->pos.x + (5.0f * pPlayer->move.x)) + sinf(pPlayer->rot.y + D3DX_PI) * ((pPlayer->move.x * pPlayer->move.x) + ((pPlayer->move.x * pPlayer->move.x))); // 目的の注視点を設定
		g_camera.posRDest.y = (pPlayer->pos.y + g_camera.posRAdd.y + 40.0f);                                                                                // 目的の注視点を設定
		g_camera.posRDest.z = (pPlayer->pos.z + (5.0f * pPlayer->move.z)) + cosf(pPlayer->rot.y + D3DX_PI) * ((pPlayer->move.z * pPlayer->move.z) + ((pPlayer->move.z * pPlayer->move.z))); // 目的の注視点を設定

		g_camera.posV.x += (g_camera.posVDest.x - g_camera.posV.x) * 0.5f; // 現在の視点を設定
		g_camera.posV.y += (g_camera.posVDest.y - g_camera.posV.y) * 0.5f; // 現在の視点を設定
		g_camera.posV.z += (g_camera.posVDest.z - g_camera.posV.z) * 0.5f; // 現在の視点を設定

		g_camera.posR.x += (g_camera.posRDest.x - g_camera.posR.x) * 0.30f; // 現在の注視点を設定
		g_camera.posR.y += (g_camera.posRDest.y - g_camera.posR.y) * 0.30f; // 現在の注視点を設定
		g_camera.posR.z += (g_camera.posRDest.z - g_camera.posR.z) * 0.30f; // 現在の注視点を設定

		if (GetKeyboardPress(DIK_RIGHT) == true ||
			GetJoyPadPress(DIJS_BUTTON_16, 0) == TRUE)
		{// 左アナログスティックが右に倒された
			g_camera.rot.y += D3DX_PI / 120;
			if (g_camera.rot.y >= D3DX_PI)
			{
				g_camera.rot.y = -D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_LEFT) == true ||
			GetJoyPadPress(DIJS_BUTTON_17, 0) == TRUE)
		{// 左アナログスティックが左に倒された
			g_camera.rot.y -= D3DX_PI / 120;
			if (g_camera.rot.y <= -D3DX_PI)
			{
				g_camera.rot.y = D3DX_PI;
			}
		}
		else if (GetKeyboardPress(DIK_UP) == true ||
			GetJoyPadPress(DIJS_BUTTON_14, 0) == TRUE)
		{// 左アナログスティックが上に倒された 
			if (g_camera.fLength.y >= 70.0f)
			{// 視点が既定の値まで下がっていない
				g_camera.fLength.y -= 3.0f;
			}
		}
		else if (GetKeyboardPress(DIK_DOWN) == true ||
			GetJoyPadPress(DIJS_BUTTON_15, 0) == TRUE)
		{// 左アナログスティックが下に倒された
			if (g_camera.fLength.y <= 320.0f)
			{// 視点が既定の値まで上がっていない
				g_camera.fLength.y += 3.0f;
			}
		}
	}
}
//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	// ビューポートの設定
	pDevice->SetViewport(&g_camera.ViewPort);

	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	// プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(CAMERA_ANGEL_VIEW),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		50000.0f);

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