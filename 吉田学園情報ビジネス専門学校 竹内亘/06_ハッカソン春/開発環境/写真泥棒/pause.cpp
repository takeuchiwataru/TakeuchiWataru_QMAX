//=============================================================================
//
// ポーズ処理 [pause.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "pause.h"
#include "fade.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
//--------------
// 黒画面用
//--------------
#define PAUSE_POS_X        (0)                         // ポーズの左上Ｘ座標
#define PAUSE_POS_Y        (0)                         // ポーズの左上Ｙ座標
#define PAUSE_WIDTH        (SCREEN_WIDTH)              // ポーズの幅
#define PAUSE_HEIGHT       (SCREEN_HEIGHT)             // ポーズの高さ

//--------------
// ロゴ用
//--------------
#define TEXTURE_NAME       "data/TEXTURE/pause100.png"  // 読み込むテクスチャファイル名
#define PAUSELOGO_POS_X    (350)                              // ポーズロゴの左上Ｘ座標
#define PAUSELOGO_POS_Y    (150)                              // ポーズロゴ左上Ｙ座標
#define PAUSELOGO_WIDTH    (970)                              // ポーズロゴの幅
#define PAUSELOGO_HEIGHT   (570)                              // ポーズロゴの高さ

//--------------
// 選択項目用
//--------------
#define PAUSESELECT_TEXTURE_NAME1  "data/TEXTURE/pause000.png" // 読み込むテクスチャファイル名(再開)
#define PAUSESELECT_TEXTURE_NAME2  "data/TEXTURE/pause001.png" // 読み込むテクスチャファイル名(やり直し)
#define PAUSESELECT_TEXTURE_NAME3  "data/TEXTURE/pause002.png" // 読み込むテクスチャファイル名(終了)
#define MAX_PAUSE_SELECT          (RESTART_MAX)                      // ポーズ選択できる項目の数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexPauseLogo(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
//--------------
// 黒画面用
//--------------
LPDIRECT3DTEXTURE9		g_pTexturePause = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;	// 頂点バッファへのポインタ
D3DXCOLOR				g_colorPause;			// ポーズ画面色

//--------------
// ロゴ用
//--------------
LPDIRECT3DTEXTURE9		g_pTexturePauseLogo = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseLogo = NULL;	// 頂点バッファへのポインタ
D3DXCOLOR				g_colorPauseLogo;		    // ポーズロゴ色

//--------------
// 選択項目用
//--------------
LPDIRECT3DTEXTURE9		g_pTexturePauseSelect[MAX_PAUSE_SELECT] = {}; // テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseSelect = NULL;                 // 頂点バッファへのポインタ
PAUSE                   g_aPause[MAX_PAUSE_SELECT];                   // ポーズ項目
RESTART                 g_restart;                                    // 遷移する先
float                   g_col;                                        // 色の変化に使用
int                     g_Select;                                     // 選択に使用

//=============================================================================
// 初期化処理
//=============================================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_colorPause = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f);

	// 頂点情報の設定
	MakeVertexPause(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPause(void)
{
	// テクスチャの開放
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePause(void)
{

}

//=============================================================================
// タイトル画面
//=============================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePause);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPause(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);


	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_colorPause;
	pVtx[1].col = g_colorPause;
	pVtx[2].col = g_colorPause;
	pVtx[3].col = g_colorPause;

	// 頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();
}

//=============================================================================
// ポーズロゴの初期化処理
//=============================================================================
void InitPauseLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_colorPauseLogo = D3DXCOLOR(0.3f, 0.8f, 1.0f, 1.0f);

	// 頂点情報の設定
	MakeVertexPauseLogo(pDevice);
}

//=============================================================================
// ポーズロゴの終了処理
//=============================================================================
void UninitPauseLogo(void)
{
	// テクスチャの開放
	if (g_pTexturePauseLogo != NULL)
	{
		g_pTexturePauseLogo->Release();
		g_pTexturePauseLogo = NULL;
	}

	// 頂点バッファの開放
	if (g_pVtxBuffPauseLogo != NULL)
	{
		g_pVtxBuffPauseLogo->Release();
		g_pVtxBuffPauseLogo = NULL;
	}
}

//=============================================================================
// ポーズロゴの更新処理
//=============================================================================
void UpdatePauseLogo(void)
{
}
//=============================================================================
// ポーズロゴの描画処理
//=============================================================================
void DrawPauseLogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPauseLogo, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePauseLogo);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ポーズロゴの頂点情報の作成
//=============================================================================
void MakeVertexPauseLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTexturePauseLogo);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseLogo,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffPauseLogo->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(PAUSELOGO_POS_X, PAUSELOGO_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(PAUSELOGO_WIDTH, PAUSELOGO_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(PAUSELOGO_POS_X, PAUSELOGO_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(PAUSELOGO_WIDTH, PAUSELOGO_HEIGHT, 0.0f);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_colorPauseLogo;
	pVtx[1].col = g_colorPauseLogo;
	pVtx[2].col = g_colorPauseLogo;
	pVtx[3].col = g_colorPauseLogo;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffPauseLogo->Unlock();
}
//=============================================================================
// 選択項目の初期化処理
//=============================================================================
void InitPauseSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_aPause[0].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);  // 色を初期化
	g_aPause[0].select = PAUSESELECT_SELECT;              // スタートはCONTINUEから
														  // 値の初期化
	for (int nCntPauseSelect = 1; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
	{// 項目の数だけ繰り返し
		g_aPause[nCntPauseSelect].col = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);  // 色を初期化
		g_aPause[nCntPauseSelect].select = PAUSESELECT_NONE;                // 選択されていない状態にする
		g_aPause[nCntPauseSelect].nCounter = 0;                             // カウンターは戻しておく
	}
	g_col = 0.01f;                // 色の変化を初期化
	g_restart = RESTART_CONTINUE; // ゲーム再開状態にしておく
	g_Select = 0;                 // 選択されている番号はCONTINUEに

								  // 頂点情報の設定
	MakeVertexPauseSelect(pDevice);
}

//=============================================================================
// 選択項目の終了処理
//=============================================================================
void UninitPauseSelect(void)
{
	// テクスチャの開放
	for (int nCntPauseSelect = 0; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
	{// 読み込んだテクスチャの数だけ繰り返し
		if (g_pTexturePauseSelect[nCntPauseSelect] != NULL)
		{
			g_pTexturePauseSelect[nCntPauseSelect]->Release();
			g_pTexturePauseSelect[nCntPauseSelect] = NULL;
		}
	}

	// 頂点バッファの開放
	if (g_pVtxBuffPauseSelect != NULL)
	{
		g_pVtxBuffPauseSelect->Release();
		g_pVtxBuffPauseSelect = NULL;
	}
}

//=============================================================================
// 選択項目の更新処理
//=============================================================================
void UpdatePauseSelect(void)
{
	if (GetFade() == FADE_NONE)
	{// フェードしていない
		// 選択項目移動処理
		if (GetJoyPadTrigger(DIJS_BUTTON_18,0) == TRUE || GetKeyboardTrigger(DIK_W) == true
			|| GetKeyboardRepeat(DIK_W) == true || GetJoyPadRepeat(DIJS_BUTTON_18,0) == true)
		{// 上方向の入力がされた
			g_aPause[g_Select].select = PAUSESELECT_NONE;
			g_aPause[(g_Select + (MAX_PAUSE_SELECT - 1)) % MAX_PAUSE_SELECT].select = PAUSESELECT_SELECT;
			g_Select = (g_Select + (MAX_PAUSE_SELECT - 1)) % MAX_PAUSE_SELECT;
			g_aPause[g_Select].col.r = 0.8f;
			g_aPause[g_Select].col.g = 0.8f;
			g_aPause[g_Select].col.b = 0.8f;
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		else if (GetJoyPadTrigger(DIJS_BUTTON_19,0) == TRUE || GetKeyboardTrigger(DIK_S) == true
			|| GetKeyboardRepeat(DIK_S) == true || GetJoyPadRepeat(DIJS_BUTTON_19,0) == true)
		{// 下方向の入力がされた
			g_aPause[g_Select].select = PAUSESELECT_NONE;
			g_aPause[(g_Select + 1) % MAX_PAUSE_SELECT].select = PAUSESELECT_SELECT;
			g_Select = (g_Select + 1) % MAX_PAUSE_SELECT;
			g_aPause[g_Select].col.r = 0.8f;
			g_aPause[g_Select].col.g = 0.8f;
			g_aPause[g_Select].col.b = 0.8f;
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		else if (GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
		{// 決定ボタンが押された
			g_aPause[g_Select].select = PAUSESELECT_PUSH;   // 押されている状態
			g_aPause[g_Select].col.r = 1.0f;
			g_aPause[g_Select].col.g = 1.0f;
			g_aPause[g_Select].col.b = 1.0f;
		}
		if (GetJoyPadTrigger(DIJS_BUTTON_9,0) == TRUE || GetKeyboardTrigger(DIK_P) == true)
		{// ポーズが解除された
			g_aPause[0].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);  // 色を初期化
			g_aPause[0].select = PAUSESELECT_SELECT;              // スタートはCONTINUEから
			for (int nCntPauseSelect = 1; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
			{// 項目の数だけ繰り返し
				g_aPause[nCntPauseSelect].col = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);  // 色を初期化
				g_aPause[nCntPauseSelect].select = PAUSESELECT_NONE;                // 選択されていない状態にする
			}
			g_Select = 0;      // 選択されている番号はCONTINUEに
		}
		// 画面遷移
		if (GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
		{// 決定ボタンが押された
			switch (g_Select)
			{
			case RESTART_CONTINUE:
				g_restart = RESTART_CONTINUE; // ゲーム再開状態に
				break;
			case RESTART_RETRY:
				g_restart = RESTART_RETRY;    // ゲームやり直し状態に
				PlaySound(SOUND_LABEL_SE_DECIDE);
				break;
			case RESTART_QUIT:
				g_restart = RESTART_QUIT;     // タイトル遷移状態に
				PlaySound(SOUND_LABEL_SE_DECIDE);
				break;
			}
		}
	}
	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPauseSelect = 0; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
	{// 項目の数だけ繰り返し
		if (g_aPause[nCntPauseSelect].select == PAUSESELECT_SELECT)
		{// 選択されていたら
			g_aPause[nCntPauseSelect].col.r += g_col;
			g_aPause[nCntPauseSelect].col.g += g_col;
			g_aPause[nCntPauseSelect].col.b += g_col;

			if (g_aPause[nCntPauseSelect].col.r < 0.3f || g_aPause[nCntPauseSelect].col.r >= 1.0f)
			{// 色が既定の値に達した
				g_col *= -1;
			}
		}
		else if (g_aPause[nCntPauseSelect].select == PAUSESELECT_NONE)
		{// 選択されていなかったら
			g_aPause[nCntPauseSelect].col.r = 0.15f;
			g_aPause[nCntPauseSelect].col.g = 0.15f;
			g_aPause[nCntPauseSelect].col.b = 0.15f;
		}
		else if (g_aPause[nCntPauseSelect].select == PAUSESELECT_PUSH)
		{// 押されている状態なら
			g_aPause[nCntPauseSelect].nCounter++;
		}
		// 頂点カラーの更新
		pVtx[0].col = g_aPause[nCntPauseSelect].col;
		pVtx[1].col = g_aPause[nCntPauseSelect].col;
		pVtx[2].col = g_aPause[nCntPauseSelect].col;
		pVtx[3].col = g_aPause[nCntPauseSelect].col;

		pVtx += 4;
	}
	// 頂点バッファをアンロックする
	g_pVtxBuffPauseSelect->Unlock();
}
//=============================================================================
// 選択項目の描画処理
//=============================================================================
void DrawPauseSelect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffPauseSelect, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPauseSelect = 0; nCntPauseSelect < MAX_PAUSE_SELECT; nCntPauseSelect++)
	{// 項目の数だけ繰り返し
		if (g_aPause[nCntPauseSelect].select != PAUSESELECT_PUSH || g_aPause[nCntPauseSelect].select == PAUSESELECT_PUSH && g_aPause[nCntPauseSelect].nCounter % 3 == 0)
		{// 決定キーが押されていないか,すでに押されていてカウンターが既定の値だったら
			// テクスチャの設定
			pDevice->SetTexture(0, g_pTexturePauseSelect[nCntPauseSelect]);

			// ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPauseSelect * 4, NUM_POLYGON);
		}
	}
}

//=============================================================================
// 選択項目の頂点情報の作成
//=============================================================================
void MakeVertexPauseSelect(LPDIRECT3DDEVICE9 pDevice)
{
	// テクスチャの読み込み(CONTINUE)
	D3DXCreateTextureFromFile(pDevice,
		PAUSESELECT_TEXTURE_NAME1,
		&g_pTexturePauseSelect[0]);

	// テクスチャの読み込み(RETRY)
	D3DXCreateTextureFromFile(pDevice,
		PAUSESELECT_TEXTURE_NAME2,
		&g_pTexturePauseSelect[1]);

	// テクスチャの読み込み(QUIT)
	D3DXCreateTextureFromFile(pDevice,
		PAUSESELECT_TEXTURE_NAME3,
		&g_pTexturePauseSelect[2]);

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * (4 * MAX_PAUSE_SELECT),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseSelect,
		NULL);

	VERTEX_2D *pVtx;   // 頂点情報へのポインタ

	// 頂点バッファをロックし,頂点データへのポインタを取得
	g_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	//-----------
	//  再開
	//-----------

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(500, 190, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(830, 190, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(500, 280, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(830, 280, 0.0f);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_aPause[0].col;
	pVtx[1].col = g_aPause[0].col;
	pVtx[2].col = g_aPause[0].col;
	pVtx[3].col = g_aPause[0].col;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//-----------
	//  やり直し
	//-----------

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(440, 310, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(880, 310, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(440, 400, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(880, 400, 0.0f);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_aPause[0].col;
	pVtx[1].col = g_aPause[0].col;
	pVtx[2].col = g_aPause[0].col;
	pVtx[3].col = g_aPause[0].col;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//-----------
	//  終了
	//-----------

	// 頂点座標
	pVtx[0].pos = D3DXVECTOR3(515, 430, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(815, 430, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(515, 520, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(815, 520, 0.0f);

	// 頂点テクスチャ
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = g_aPause[0].col;
	pVtx[1].col = g_aPause[0].col;
	pVtx[2].col = g_aPause[0].col;
	pVtx[3].col = g_aPause[0].col;

	// テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロックする
	g_pVtxBuffPauseSelect->Unlock();
}
//=============================================================================
// 項目の取得
//=============================================================================
RESTART GetRestart(void)
{
	return g_restart;
}