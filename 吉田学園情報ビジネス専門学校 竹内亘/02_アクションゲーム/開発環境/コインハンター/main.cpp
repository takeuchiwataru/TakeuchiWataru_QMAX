//=============================================================================
//
// DirectX [main.cpp]
// Author : �|���j
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
// �}�N����`
//*****************************************************************************
#define CLASS_NAME		"WindowClass"		//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"�R�C���n���^�["	//�E�C���h�E�̖��O(�L���v�V������)
#define BLOCK_X			(0)					//�u���b�N��X���W
#define BLOCK_Y			(0)					//�u���b�N��Y���W


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void); 
void Draw(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3D9 g_pD3D = NULL;				//Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3D�f�o�C�X�ւ̃|�C���^
MODE g_mode = MODE_TITLE;				//���݂̃��[�h

//=============================================================================
// ���C���֐�
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
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExecLastTime;	//�Ō�ɏ�����������

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();	//���ݎ������擾

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �w�肵���N���C�A���g�̈��ی삷�邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	// �E�B���h�E�̐���
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

	//����������(�E�B���h�E�𐶐����Ă���s��)
	if (FAILED(Init(hInstance, hWnd, FALSE)))	//FALSE�Ńt���X�N���[��
	{
		return -1;
	}

	//�E�C���h�E�̕\��(�����������̌�ɍs��)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)	//���b�Z�[�W���擾���Ȃ������ꍇ"0"��Ԃ�
		{//Windows�̏���
			if (msg.message == WM_QUIT)
			{//"WM_QUIT"���b�Z�[�W�������Ă����烋�[�v�𔲂���
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectX�̏���
			dwCurrentTime = timeGetTime();	//���ݎ������擾

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;	//��������������ۑ�

				//�X�V����
				Update();

				//�`�揈��
				Draw();
			}
		}
	}

	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		//"WM_QUIT"���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//�E�B���h�E��j������("WM_DESTROY"���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	//����̏�����Ԃ�
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	//�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));							//���[�N���[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						//�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						//�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									//�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					//�_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;						//�f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					//�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;									//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	//�C���^�[�o��(VSync��҂��ĕ`��)

	//Direct3D�f�o�C�X�̐���
	//[�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,			//�f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,											//�f�o�C�X�^�C�v
		hWnd,													//�t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,					//�f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,													//�f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&g_pD3DDevice)))										//�f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		//��L�̐ݒ肪���s������
		//[�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//��L�̐ݒ肪���s������
			//[�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
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

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//���͏�������������
	InitKeyboard(hInstance, hWnd);

	// �����L���O�X�R�A����������
	InitRankingScore();

	// �v���X�G���^�[����������
	InitPressEnter();

	//�t�F�[�h�̐ݒ�
	InitFade(g_mode);

	//�T�E���h�̏���������
	InitSound(hWnd);

	//���[�h�̐ݒ�
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

	//�^�C�g���I������
	UninitTitle();

	//�^�C�g�����S�I������
	UninitTitleLogo();

	//�`���[�g���A���I������
	UninitTutorial();

	//���U���g�I������
	UninitResult();

	//���U���g���S�I������
	UninitResultLogo();
	UninitResultLogo2();

	// �����L���O��ʏI������
	UninitRanking();

	// �����L���O�����N�I������
	UninitRankingRank();

	// �����L���O�X�R�A�I������
	UninitRankingScore();

	//�v���X�G���^�[�I������
	UninitPressEnter();

	//�t�F�[�h�̏I������
	UninitFade();

	//�T�E���h�̏I������
	UninitSound();

	////�Q�[���I������
	//UninitGame();

	//Direct3D�f�o�C�X�̊J��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g�̊J��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	//���͏����X�V����
	UpdateKeyboard();

	switch (g_mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		UpdateTitle();
		UpdateTitleLogo();
		UpdatePressEnter();
		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����
		UpdateTutorial();
		UpdatePressEnter();
		break;

	case MODE_GAME:			//�Q�[�����
		UpdateGame();
		break;

		//case MODE_RESULT:		//���U���g���
		//	UpdateResult();
		//	UpdateResultLogo();
		//	break;

	case MODE_GAMECLEAR:	//�Q�[���N���A���
		UpdateResult();
		UpdateResultLogo();
		SetRankingScore(GetScore());
		break;

	case MODE_GAMEOVER:		//�Q�[���I�[�o�[���
		UpdateResult();
		UpdateResultLogo2();
		SetRankingScore(GetScore());
		break;

	case MODE_RANKING:		//�����L���O���
		UpdateRanking();
		UpdateRankingRank();
		UpdateRankingScore();
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	//�o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	g_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	//�`��̊J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		switch (g_mode)
		{
		case MODE_TITLE:		//�^�C�g�����
			DrawTitle();
			DrawTitleLogo();
			DrawPressEnter();
			break;

		case MODE_TUTORIAL:		//�`���[�g���A�����
			DrawTutorial();
			DrawPressEnter();
			break;

		case MODE_GAME:			//�Q�[�����
			DrawGame();
			break;

		//case MODE_RESULT:		//���U���g���
		//	DrawResult();
		//	DrawResultLogo();
		//	break;

		case MODE_GAMECLEAR:	//�Q�[���N���A���
			DrawResult();
			DrawResultLogo();
			break;

		case MODE_GAMEOVER:		//�Q�[���I�[�o�[���
			DrawResult();
			DrawResultLogo2();
			break;

		case MODE_RANKING:
			DrawRanking();
			DrawRankingRank();
			DrawRankingScore();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();

		//�`��̏I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// ���[�h�̐ݒ菈��
//=============================================================================
void SetMode(MODE mode)
{
	switch (g_mode)
	{
	case MODE_TITLE:		//�^�C�g�����
		UninitTitle();
		UninitTitleLogo();
		UninitPressEnter();
		break;

	case MODE_TUTORIAL:		//�`���[�g���A�����
		UninitTutorial();
		UninitPressEnter();
		break;

	case MODE_GAME:			//�Q�[�����
		UninitGame();
		UninitPressEnter();
		break;

	//case MODE_RESULT:		//���U���g���
	//	UninitResult();
	//	UninitResultLogo();
	//	break;

	case MODE_GAMECLEAR:		//�Q�[���N���A���
		StopSound(SOUND_LABEL_BGM_GAME);
		UninitResult();
		UninitResultLogo();
		break;

	case MODE_GAMEOVER:		//�Q�[���I�[�o�[���
		StopSound(SOUND_LABEL_BGM_GAME);
		UninitResult();
		UninitResultLogo2();
		break;

	case MODE_RANKING:
		UninitRanking();
		UninitRankingRank();
		break;

	}
	g_mode = mode;	//���݂̃��[�h��؂�ւ���

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
	g_mode = mode;	//���݂̃��[�h��؂�ւ���
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