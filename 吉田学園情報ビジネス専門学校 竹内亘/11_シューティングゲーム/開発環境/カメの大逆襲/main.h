//=============================================================================
//
// ���C������ [main.h]
// Author : �|���j
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include <windows.h>
#include <crtdbg.h>

#include "d3dx9.h"						// �`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"						// ���͌n�ɕK�v
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "xaudio2.h"					// �T�E���h�����ɕK�v
#include <XInput.h> // XInput API


//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e�������ɕK�v
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib,"XInput.lib")	//XInput�ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;				//���_���W
	float rhw;						//1.0f�ŌŒ�
	D3DCOLOR col;					//���_�J���[
	D3DXVECTOR2 tex;				//�e�N�X�`���̍��W
}VERTEX_2D;

//*****************************************************************************
// �O���錾 �C���N���[�h�͂���Ȃ�
//*****************************************************************************
class CRenderer;
class CScene;
class CInputKeyboard;
class CInputJoyPad;
class CXInputJoyPad;
class CPlayer;
class CBullet;
class CSound;
class CNumber;
class CScore;
class CTitle;
class CGame;
class CResult;
class CResult2;
class CRanking;
class CTutorial;
class CFade;
class CPause;
class CPauseMat;
class CPauseSelect;
class CLife;
class CRemain;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
int GetFPS(void);
//CRenderer * GetRenderer(void);
CScene ** GetScene(void);
//CScene * GetScene(void);

#endif