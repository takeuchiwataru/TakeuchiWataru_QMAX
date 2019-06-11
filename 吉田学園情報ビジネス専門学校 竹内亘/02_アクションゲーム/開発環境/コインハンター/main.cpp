//=============================================================================
//
// DirectX [main.cpp]
// Author : 竹内亘
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "score.h"
#include "fade.h"
#include "game.h"
#include "title.h"
#include "titlelogo.h"
#include "tutorial.h"
#include "result.h"
#include "resultlogo.h"
#include "pressenter.h"
#include "ranking.h"
#include "rankingrank.h"
#include "rankingscore.h"
#include "sound.h"

//#include "clear.h"
//#include "over.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME		"WindowClass"		//ウインドウクラスの名前
#define WINDOW_NAME		"コインハンター"	//ウインドウの名前(キャプション名)
#define BLOCK_X			(0)					//ブロックのX座標
#define BLOCK_Y			(0)					//ブロックのY座標


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void); 
void Draw(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3D9 g_pD3D = NULL;				//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;				//現在のモード

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WindowProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		CLASS_NAME,
		LoadIcon(NULL, IDI_APPLICATION)
	};
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;	//現在時刻
	DWORD dwExecLastTime;	//最後に処理した時刻

	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();	//現在時刻を取得

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を保護するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの生成
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

	//初期化処理(ウィンドウを生成してから行う)
	if (FAILED(Init(hInstance, hWnd, FALSE)))	//FALSEでフルスクリーン
	{
		return -1;
	}

	//ウインドウの表示(初期化処理の後に行う)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	//メッセージを取得しなかった場合"0"を返す
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{//"WM_QUIT"メッセージが送られてきたらループを抜ける
				break;
			}
			else
			{
				//メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();	//現在時刻を取得

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;	//処理した時刻を保存

				//更新処理
				Update();

				//描画処理
				Draw();
			}
		}
	}

	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//"WM_QUIT"メッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//ウィンドウを破棄する("WM_DESTROY"メッセージを送る)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//既定の処理を返す
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							//ワークをゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						//ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						//ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						//バックバッファの形式
	d3dpp.BackBufferCount = 1;									//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;						//デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;									//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//リフレッシュレート(現在の速度に合わせる)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//インターバル(VSyncを待って描画)

	//Direct3Dデバイスの生成
	//[デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,			//ディスプレイアダプタ
		D3DDEVTYPE_HAL,											//デバイスタイプ
		hWnd,													//フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,					//デバイス作成制御の組み合わせ
		&d3dpp,													//デバイスのプレゼンテーションパラメータ
		&g_pD3DDevice)))										//デバイスインターフェースへのポインタ
	{
		//上記の設定が失敗したら
		//[デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//上記の設定が失敗したら
			//[デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//入力処理初期化処理
	InitKeyboard(hInstance, hWnd);

	// ランキングスコア初期化処理
	InitRankingScore();

	// プレスエンター初期化処理
	InitPressEnter();

	//フェードの設定
	InitFade(g_mode);

	//サウンドの初期化処理
	InitSound(hWnd);

	//モードの設定
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

	//タイトル終了処理
	UninitTitle();

	//タイトルロゴ終了処理
	UninitTitleLogo();

	//チュートリアル終了処理
	UninitTutorial();

	//リザルト終了処理
	UninitResult();

	//リザルトロゴ終了処理
	UninitResultLogo();
	UninitResultLogo2();

	// ランキング画面終了処理
	UninitRanking();

	// ランキングランク終了処理
	UninitRankingRank();

	// ランキングスコア終了処理
	UninitRankingScore();

	//プレスエンター終了処理
	UninitPressEnter();

	//フェードの終了処理
	UninitFade();

	//サウンドの終了処理
	UninitSound();

	////ゲーム終了処理
	//UninitGame();

	//Direct3Dデバイスの開放
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクトの開放
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	//入力処理更新処理
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:		//タイトル画面
		UpdateTitle();
		UpdateTitleLogo();
		UpdatePressEnter();
		break;

	case MODE_TUTORIAL:		//チュートリアル画面
		UpdateTutorial();
		UpdatePressEnter();
		break;

	case MODE_GAME:			//ゲーム画面
		UpdateGame();
		break;

		//case MODE_RESULT:		//リザルト画面
		//	UpdateResult();
		//	UpdateResultLogo();
		//	break;

	case MODE_GAMECLEAR:	//ゲームクリア画面
		UpdateResult();
		UpdateResultLogo();
		SetRankingScore(GetScore());
		break;

	case MODE_GAMEOVER:		//ゲームオーバー画面
		UpdateResult();
		UpdateResultLogo2();
		SetRankingScore(GetScore());
		break;

	case MODE_RANKING:		//ランキング画面
		UpdateRanking();
		UpdateRankingRank();
		UpdateRankingScore();
		break;
	}

	//フェードの更新処理
	UpdateFade();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	//バックバッファ＆Ｚバッファのクリア
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	//描画の開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:		//タイトル画面
			DrawTitle();
			DrawTitleLogo();
			DrawPressEnter();
			break;

		case MODE_TUTORIAL:		//チュートリアル画面
			DrawTutorial();
			DrawPressEnter();
			break;

		case MODE_GAME:			//ゲーム画面
			DrawGame();
			break;

		//case MODE_RESULT:		//リザルト画面
		//	DrawResult();
		//	DrawResultLogo();
		//	break;

		case MODE_GAMECLEAR:	//ゲームクリア画面
			DrawResult();
			DrawResultLogo();
			break;

		case MODE_GAMEOVER:		//ゲームオーバー画面
			DrawResult();
			DrawResultLogo2();
			break;

		case MODE_RANKING:
			DrawRanking();
			DrawRankingRank();
			DrawRankingScore();
			break;
		}

		//フェードの描画処理
		DrawFade();

		//描画の終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// モードの設定処理
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:		//タイトル画面
		UninitTitle();
		UninitTitleLogo();
		UninitPressEnter();
		break;

	case MODE_TUTORIAL:		//チュートリアル画面
		UninitTutorial();
		UninitPressEnter();
		break;

	case MODE_GAME:			//ゲーム画面
		UninitGame();
		UninitPressEnter();
		break;

	//case MODE_RESULT:		//リザルト画面
	//	UninitResult();
	//	UninitResultLogo();
	//	break;

	case MODE_GAMECLEAR:		//ゲームクリア画面
		StopSound(SOUND_LABEL_BGM_GAME);
		UninitResult();
		UninitResultLogo();
		break;

	case MODE_GAMEOVER:		//ゲームオーバー画面
		StopSound(SOUND_LABEL_BGM_GAME);
		UninitResult();
		UninitResultLogo2();
		break;

	case MODE_RANKING:
		UninitRanking();
		UninitRankingRank();
		break;

	}
	g_mode = mode;	//現在のモードを切り替える

	switch (mode)
	{
	case MODE_TITLE:
		InitPressEnter();
		InitTitle();
		InitTitleLogo();
		PlaySound(SOUND_LABEL_BGM_TITLE);
		break;

	case MODE_TUTORIAL:
		InitPressEnter();
		InitTutorial();
		break;

	case MODE_GAME:
		InitGame();
		StopSound(SOUND_LABEL_BGM_TITLE);
		PlaySound(SOUND_LABEL_BGM_GAME);
		break;

	//case MODE_RESULT:
	//	InitResult();
	//	InitResultLogo();
	//	break;

	case MODE_GAMECLEAR:
		InitResult();
		InitResultLogo();
		StopSound(SOUND_LABEL_BGM_GAME);
		PlaySound(SOUND_LABEL_BGM_GAMECLEAR);
		break;

	case MODE_GAMEOVER:
		InitResult();
		InitResultLogo2();
		StopSound(SOUND_LABEL_BGM_GAME);
		PlaySound(SOUND_LABEL_BGM_GAMEOVER);
		break;

	case MODE_RANKING:
		InitRanking();
		InitRankingRank();
		StopSound(SOUND_LABEL_BGM_GAMECLEAR);
		StopSound(SOUND_LABEL_BGM_GAMEOVER);
		break;

	}
	g_mode = mode;	//現在のモードを切り替える
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