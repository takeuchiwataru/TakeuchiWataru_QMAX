//=============================================================================
//
// ���C������ [main.cpp]
// Author : �|���j
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
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"AppClass"				// �E�C���h�E�̃N���X��
#define WINDOW_NAME		"GPU"	// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************
LPDIRECT3D9			g_pD3D = NULL;			// Direct3D�I�u�W�F�N�g
LPDIRECT3DDEVICE9	g_pD3DDevice = NULL;	// �f�o�C�X�I�u�W�F�N�g(�`��ɕK�v)
MODE g_mode = MODE_TITLE;					// ���݂̃��[�h

//=============================================================================
// ���C���֐�
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
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̍쐬
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

	// ����������(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, FALSE)))		// FALSE�Ńt���X�N���[��
	{
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	dwExecLastTime = 
	dwFPSLastTime = timeGetTime();
	dwCurrentTime =
	dwFrameCount = 0;

	// �E�C���h�E�̕\��(�����������̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
        }
		else
		{
			dwCurrentTime = timeGetTime();

			if((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 1/60�b�o��
				dwExecLastTime = dwCurrentTime;

				// �X�V����
				Update();

				// �`�揈��
				Draw();

				dwFrameCount++;
			}
		}
	}

	// �I������
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
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
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
    D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if(g_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
    if(FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount			 = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// �o�b�N�o�b�t�@�t�H�[�}�b�g�̓f�B�X�v���C���[�h�ɍ��킹�Ďg��
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed					 = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
									D3DDEVTYPE_HAL, 
									hWnd, 
									D3DCREATE_HARDWARE_VERTEXPROCESSING, 
									&d3dpp, &g_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
										D3DDEVTYPE_HAL, 
										hWnd, 
										D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
										&d3dpp, &g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if(FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, 
											D3DDEVTYPE_REF,
											hWnd, 
											D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
											&d3dpp, &g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
    g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��

	// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O������ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

	// ���͏�������������
	InitKeyboard(hInstance, hWnd);

	// �t�F�[�h�̐ݒ�
	InitFade(g_mode);

	// �v���X�G���^�[����������
	InitPressEnter();

	// �����L���O�X�R�A����������
	InitRankingScore();

	//�T�E���h�̏���������
	InitSound(hWnd);

	// ���[�h�̐ݒ�
	SetMode(g_mode);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	//���͏����I������
	UninitKeyboard();


	//�t�F�[�h�̏I������
	UninitFade();

	//�^�C�g���I������
	UninitTitle();

	//�^�C�g�����S�I������
	UninitTitleLogo();

	// �`���[�g���A���I������
	UninitTutorial();

	// �`���[�g���A�����S�I������
	UninitTutorialLogo();

	// ���U���g�I������
	UninitResult();
	//UninitResult2();

	// ���U���g���S�I������
	UninitResultLogo();
	//UninitResultLogo2();

	//�v���X�G���^�[�I������
	UninitPressEnter();

	// �����L���O��ʏI������
	UninitRanking();

	// �����L���O�����N�I������
	UninitRankingRank();

	// �����L���O�X�R�A�I������
	UninitRankingScore();

	//�T�E���h�̏I������
	UninitSound();

	if(g_pD3DDevice != NULL)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if(g_pD3D != NULL)
	{// Direct3D�I�u�W�F�N�g�̊J��
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	// ���͏����X�V����
	UpdateKeyboard();

	//// �W���C�p�b�h�̍X�V����
	//UpdateDirectInput();

	switch (g_mode)
	{
	case MODE_TITLE:			// �^�C�g�����
		UpdateTitle();
		UpdateTitleLogo();
		UpdatePressEnter();
		break;

	case MODE_TUTORIAL:			// �`���[�g���A�����
		UpdateTutorial();
		UpdateTutorialLogo();
		UpdatePressEnter();
		break;

	case MODE_GAME:				// �Q�[�����
		UpdateGame();
		break;

	case MODE_GAMECLEAR:		// ���U���g���
		UpdateResult();
		UpdateResultLogo();
		break;

	case MODE_GAMEOVER:			// ���U���g���
		UpdateResult2();
		UpdateResultLogo2();
		break;

	case MODE_RANKING:			// �����L���O���
		UpdateRanking();
		UpdateRankingRank();
		UpdateRankingScore();
		break;
	}

	// �t�F�[�h�̍X�V����
	UpdateFade();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �`��̊J�n
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:		// �^�C�g�����
			DrawTitle();
			DrawTitleLogo();
			DrawPressEnter();
			break;

		case MODE_TUTORIAL:			// �`���[�g���A�����
			DrawTutorial();
			DrawTutorialLogo();
			DrawPressEnter();
			break;

		case MODE_GAME:				// �Q�[�����
			DrawGame();
			break;

		case MODE_GAMECLEAR:		// ���U���g���
			DrawResult();
			DrawResultLogo();
			break;

		case MODE_GAMEOVER:			// ���U���g���
			DrawResult2();
			DrawResultLogo2();
			break;

		case MODE_RANKING:			// �����L���O���
			DrawRanking();
			DrawRankingRank();
			DrawRankingScore();
			break;
		}

		// �t�F�[�h�̕`�揈��
		DrawFade();

		// �`��̏I��
		g_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// ���[�h�̐ݒ菈��
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:			// �^�C�g�����
		UninitTitle();
		UninitTitleLogo();
		UninitPressEnter();
		break;

	case MODE_TUTORIAL:			// �`���[�g���A�����
		UninitTutorial();
		UninitTitleLogo();
		UninitPressEnter();
		break;

	case MODE_GAME:				// �Q�[�����
		UninitGame();
		UninitPressEnter();
		break;

	case MODE_GAMECLEAR:		// ���U���g���
		UninitResult();
		UninitResultLogo();
		SetRankingScore(GetScore());
		break;

	case MODE_GAMEOVER:			// ���U���g���
		UninitResult2();
		UninitResultLogo2();
		SetRankingScore(GetScore());
		break;

	case MODE_RANKING:			// �����L���O���
		UninitRanking();
		UninitRankingRank();
		break;
	}
	g_mode = mode;	// ���݂̃��[�h��؂�ւ���

	switch (mode)
	{
	case MODE_TITLE:		// �^�C�g�����
		InitPressEnter();
		InitTitle();
		InitTitleLogo();
		StopSound(SOUND_LABEL_BGM_GAMEOVER);
		StopSound(SOUND_LABEL_BGM_GAMECLEAR);
		StopSound(SOUND_LABEL_BGM_RANKING);
		PlaySound(SOUND_LABEL_BGM_TITLE);
		break;

	case MODE_TUTORIAL:		// �`���[�g���A�����
		InitPressEnter();
		InitTutorial();
		InitTutorialLogo();
		break;

	case MODE_GAME:			// �Q�[�����
		InitGame();
		StopSound(SOUND_LABEL_BGM_TITLE);
		PlaySound(SOUND_LABEL_BGM_GAME);
		break;

	case MODE_GAMECLEAR:	// ���U���g���
		InitResult();
		InitResultLogo();
		StopSound(SOUND_LABEL_BGM_GAME);
		PlaySound(SOUND_LABEL_BGM_GAMECLEAR);
		break;

	case MODE_GAMEOVER:		// ���U���g���
		InitResult2();
		InitResultLogo2();
		StopSound(SOUND_LABEL_BGM_GAME);
		PlaySound(SOUND_LABEL_BGM_GAMEOVER);
		break;

	case MODE_RANKING:		// �����L���O���
		InitRanking();
		InitRankingRank();
		StopSound(SOUND_LABEL_BGM_TITLE);
		StopSound(SOUND_LABEL_BGM_GAMECLEAR);
		StopSound(SOUND_LABEL_BGM_GAMEOVER);
		PlaySound(SOUND_LABEL_BGM_RANKING);
		break;
	}
	g_mode = mode;	// ���݂̃��[�h��؂�ւ���
}

//=============================================================================
// ���[�h�̎擾
//=============================================================================
MODE GetMode(void)
{
	return g_mode;
}


//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}
