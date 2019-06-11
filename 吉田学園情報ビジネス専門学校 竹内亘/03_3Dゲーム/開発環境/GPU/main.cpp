//=============================================================================
//
// メイン処理 [main.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
//#include "camera.h"
//#include "light.h"
//#include "polygon.h"
//#include "player.h"
//#include "model.h"
//#include "shadow.h"
//#include "wall.h"
//#include "billboard.h"
//#include "bullet.h"
//#include "meshField.h"
//#include "meshCylinder.h"
//#include "meshWall.h"
//#include "explosion.h"
//#include "effect.h"

#include "input.h"
#include "fade.h"
#include "game.h"
#include "title.h"
#include "titlelogo.h"
#include "tutorial.h"
#include "tutoriallogo.h"
#include "pressenter.h"
#include "result.h"
#include "result2.h"
#include "resultlogo.h"
#include "resultlogo2.h"
#include "ranking.h"
#include "rankingrank.h"
#include "rankingscore.h"
#include "score.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// ウインドウのクラス名
#define WINDOW_NAME		"GPU"	// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3Dオブジェクト
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// デバイスオブジェクト(描画に必要)
MODE g_mode = MODE_TITLE;					// 現在のモード

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		NULL
	};
	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	HWND hWnd;
	MSG msg;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							(rect.right - rect.left),
							(rect.bottom - rect.top),
							NULL,
							NULL,
							hInstance,
							NULL);

	// 初期化処理(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, FALSE)))		// FALSEでフルスクリーン
	{
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// ウインドウの表示(初期化処理の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60秒経過
				dwExecLastTime = dwCurrentTime;

				// 更新処理
				Update();

				// 描画処理
				Draw();

				dwFrameCount++;
			}
		}
	}

	// 終了処理
	Uninit();

	// 分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount			 = 1;							// バックバッファの数
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// バックバッファフォーマットはディスプレイモードに合わせて使う
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed					 = bWindow;						// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// デバイスオブジェクトの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリング
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ライティングモード有効
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定

	// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理を設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

	// 入力処理初期化処理
	InitKeyboard(hInstance, hWnd);

	// フェードの設定
	InitFade(g_mode);

	// プレスエンター初期化処理
	InitPressEnter();

	// ランキングスコア初期化処理
	InitRankingScore();

	//サウンドの初期化処理
	InitSound(hWnd);

	// モードの設定
	SetMode(g_mode);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	//入力処理終了処理
	UninitKeyboard();


	//フェードの終了処理
	UninitFade();

	//タイトル終了処理
	UninitTitle();

	//タイトルロゴ終了処理
	UninitTitleLogo();

	// チュートリアル終了処理
	UninitTutorial();

	// チュートリアルロゴ終了処理
	UninitTutorialLogo();

	// リザルト終了処理
	UninitResult();
	//UninitResult2();

	// リザルトロゴ終了処理
	UninitResultLogo();
	//UninitResultLogo2();

	//プレスエンター終了処理
	UninitPressEnter();

	// ランキング画面終了処理
	UninitRanking();

	// ランキングランク終了処理
	UninitRankingRank();

	// ランキングスコア終了処理
	UninitRankingScore();

	//サウンドの終了処理
	UninitSound();

	if(g_pD3DDevice != NULL)
	{// デバイスオブジェクトの開放
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3Dオブジェクトの開放
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	// 入力処理更新処理
	UpdateKeyboard();

	//// ジョイパッドの更新処理
	//UpdateDirectInput();

	switch (g_mode)
	{
	case MODE_TITLE:			// タイトル画面
		UpdateTitle();
		UpdateTitleLogo();
		UpdatePressEnter();
		break;

	case MODE_TUTORIAL:			// チュートリアル画面
		UpdateTutorial();
		UpdateTutorialLogo();
		UpdatePressEnter();
		break;

	case MODE_GAME:				// ゲーム画面
		UpdateGame();
		break;

	case MODE_GAMECLEAR:		// リザルト画面
		UpdateResult();
		UpdateResultLogo();
		break;

	case MODE_GAMEOVER:			// リザルト画面
		UpdateResult2();
		UpdateResultLogo2();
		break;

	case MODE_RANKING:			// ランキング画面
		UpdateRanking();
		UpdateRankingRank();
		UpdateRankingScore();
		break;
	}

	// フェードの更新処理
	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// 描画の開始
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:		// タイトル画面
			DrawTitle();
			DrawTitleLogo();
			DrawPressEnter();
			break;

		case MODE_TUTORIAL:			// チュートリアル画面
			DrawTutorial();
			DrawTutorialLogo();
			DrawPressEnter();
			break;

		case MODE_GAME:				// ゲーム画面
			DrawGame();
			break;

		case MODE_GAMECLEAR:		// リザルト画面
			DrawResult();
			DrawResultLogo();
			break;

		case MODE_GAMEOVER:			// リザルト画面
			DrawResult2();
			DrawResultLogo2();
			break;

		case MODE_RANKING:			// ランキング画面
			DrawRanking();
			DrawRankingRank();
			DrawRankingScore();
			break;
		}

		// フェードの描画処理
		DrawFade();

		// 描画の終了
		g_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// モードの設定処理
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:			// タイトル画面
		UninitTitle();
		UninitTitleLogo();
		UninitPressEnter();
		break;

	case MODE_TUTORIAL:			// チュートリアル画面
		UninitTutorial();
		UninitTitleLogo();
		UninitPressEnter();
		break;

	case MODE_GAME:				// ゲーム画面
		UninitGame();
		UninitPressEnter();
		break;

	case MODE_GAMECLEAR:		// リザルト画面
		UninitResult();
		UninitResultLogo();
		SetRankingScore(GetScore());
		break;

	case MODE_GAMEOVER:			// リザルト画面
		UninitResult2();
		UninitResultLogo2();
		SetRankingScore(GetScore());
		break;

	case MODE_RANKING:			// ランキング画面
		UninitRanking();
		UninitRankingRank();
		break;
	}
	g_mode = mode;	// 現在のモードを切り替える

	switch (mode)
	{
	case MODE_TITLE:		// タイトル画面
		InitPressEnter();
		InitTitle();
		InitTitleLogo();
		StopSound(SOUND_LABEL_BGM_GAMEOVER);
		StopSound(SOUND_LABEL_BGM_GAMECLEAR);
		StopSound(SOUND_LABEL_BGM_RANKING);
		PlaySound(SOUND_LABEL_BGM_TITLE);
		break;

	case MODE_TUTORIAL:		// チュートリアル画面
		InitPressEnter();
		InitTutorial();
		InitTutorialLogo();
		break;

	case MODE_GAME:			// ゲーム画面
		InitGame();
		StopSound(SOUND_LABEL_BGM_TITLE);
		PlaySound(SOUND_LABEL_BGM_GAME);
		break;

	case MODE_GAMECLEAR:	// リザルト画面
		InitResult();
		InitResultLogo();
		StopSound(SOUND_LABEL_BGM_GAME);
		PlaySound(SOUND_LABEL_BGM_GAMECLEAR);
		break;

	case MODE_GAMEOVER:		// リザルト画面
		InitResult2();
		InitResultLogo2();
		StopSound(SOUND_LABEL_BGM_GAME);
		PlaySound(SOUND_LABEL_BGM_GAMEOVER);
		break;

	case MODE_RANKING:		// ランキング画面
		InitRanking();
		InitRankingRank();
		StopSound(SOUND_LABEL_BGM_TITLE);
		StopSound(SOUND_LABEL_BGM_GAMECLEAR);
		StopSound(SOUND_LABEL_BGM_GAMEOVER);
		PlaySound(SOUND_LABEL_BGM_RANKING);
		break;
	}
	g_mode = mode;	// 現在のモードを切り替える
}

//=============================================================================
// モードの取得
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}


//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
