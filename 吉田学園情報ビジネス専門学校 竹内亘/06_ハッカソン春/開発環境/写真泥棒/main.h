//=============================================================================
//
// ���C������ [main.h]
// Author : Hodaka Niwa
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS         // �x���Ώ��p�}�N��
#include <stdio.h>
#include <windows.h>
#include <time.h>                       // �����_���Ȓl���o�͂��邽�߂ɕK�v
#include "d3dx9.h"
#define DIRECTINPUT_VERSION (0x0800)	// �x���Ώ��p
#include "dinput.h"
#include "xaudio2.h"                    // �T�E���h�����ɕK�v

//*****************************************************************************
// ���C�u�����t�@�C��
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)	// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)	// �E�C���h�E�̍���
#define NUM_POLYGON     (2)     // �`�悷��|���S����

// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@���x�N�g�� / ���_�J���[ / �e�N�X�`�����W)
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_2D;

// �R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;    // �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

//���(���[�h)�̎��
typedef enum
{
	MODE_TITLE = 0,    // �^�C�g�����
	MODE_GAME,         // �Q�[�����
	MODE_TUTORIAL,     // �`���[�g���A�����
	MODE_RESULT,       // ���ʉ��
	MODE_RANKING,      // �����L���O���
	MODE_MAX           // ��ʂ̎��
}MODE;   // ���(���[�h)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif