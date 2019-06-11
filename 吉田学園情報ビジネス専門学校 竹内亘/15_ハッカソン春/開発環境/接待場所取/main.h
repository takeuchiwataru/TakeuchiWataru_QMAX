//=============================================================================
//
// ���C������ [main.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include "d3dx9.h"							//�`�揈���ɕK�v
#define  DIRECTINPUT_VERSION	(0x0800)	//�r���h���̃G���[�Ώ��p
#include "dinput.h"							//���͏����ɕK�v
#include "xaudio2.h"						//���y�f�[�^�ɕK�v
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <crtdbg.h>
#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__)
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC

//*****************************************************************************
// ���C�u�����t�@�C���̃����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	//d3d9�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	//DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e�����Ԏ擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	//���͏����ɕK�v

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SCREEN_WIDTH	(1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720)		// �E�C���h�E�̍���
#define FVF_VERTEX_2D			(D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)	//���_���W�ƒ��_�J���[�̐ݒ�ƃe�N�X�`�����W
// 3�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@���x�N�g�� / ���_�J���[ )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define MAX_POLYGON				(100)

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CRenderer;
class CScene;
class CManager;
//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//���_���W
	float rhw;			//1.0f�ŌŒ�
	D3DCOLOR col;		//���_�J���[
	D3DXVECTOR2 tex;	//�e�N�X�`�����W
}VERTEX_2D;

// 3�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	//	�@���x�N�g��
						//float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
} VERTEX_3D;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
#ifdef _DEBUG
int  GetFPS(void);
#endif
#endif