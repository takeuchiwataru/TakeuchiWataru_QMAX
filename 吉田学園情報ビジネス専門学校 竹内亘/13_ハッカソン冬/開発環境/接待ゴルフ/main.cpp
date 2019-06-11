//=============================================================================
//
// メイン処理 [main.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CLASS_NAME				"AppClass"			// ウインドウのクラス名
#define WINDOW_NAME				"接待ゴルフ"		// ウインドウのキャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#ifdef _DEBUG
int  GetFPS(void);
#endif

//*****************************************************************************
// グローバル変数:
//*****************************************************************************
#ifdef _DEBUG
int			g_nCountFPS;			// FPSカウンタ
#endif
//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

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
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hWnd;
	MSG msg;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	srand((unsigned int)time(0));
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
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


	//マネージャークラス作成
	CManager *pManager;
	pManager = new CManager;
	if (pManager != NULL)
	{
		// 初期化処理
		if (FAILED(pManager->Init(hInstance, hWnd, FALSE)))	//FALSEにするとフルスクリーン
		{
			return-1;
		}

		// 分解能を設定
		timeBeginPeriod(1);

		// フレームカウント初期化
		dwCurrentTime =
			dwFrameCount = 0;
		dwExecLastTime =
			dwFPSLastTime = timeGetTime();

		// ウインドウの表示
		ShowWindow(hWnd, nCmdShow);
		UpdateWindow(hWnd);

		// メッセージループ
		while (1)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{// PostQuitMessage()が呼ばれたらループ終了
					break;
				}
				else
				{
					// メッセージの翻訳とディスパッチ
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
			else
			{
				dwCurrentTime = timeGetTime();	// 現在の時間を取得
				if ((dwCurrentTime - dwFPSLastTime) >= 500)
				{// 0.5秒ごとに実行
#ifdef _DEBUG
				// FPSを算出
					g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
#endif
					dwFPSLastTime = dwCurrentTime;	// 現在の時間を保存
					dwFrameCount = 0;
				}

				if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
				{// 1/60秒経過
					dwExecLastTime = dwCurrentTime;	// 現在の時間を保存

					// 更新処理
					pManager->Update();

					// 描画処理
					pManager->Draw();

					dwFrameCount++;
				}
			}
		}

		//マネージャー破棄
		if (pManager != NULL)
		{
			pManager->Uninit();
			delete pManager;
			pManager = NULL;
		}

		// ウィンドウクラスの登録を解除
		UnregisterClass(CLASS_NAME, wcex.hInstance);

		// 分解能を戻す
		timeEndPeriod(1);
	}
	else
	{
		return -1;
	}

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:				// [ESC]キーが押された
			DestroyWindow(hWnd);	// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#ifdef _DEBUG
//=============================================================================
// FPS取得
//=============================================================================
int GetFPS(void)
{
	return g_nCountFPS;
}
#endif

//=============================================================================
// レンダリングクラス取得
//=============================================================================
//CRenderer *GetRenderer(void)
//{
//	return g_pRenderer;
//}

