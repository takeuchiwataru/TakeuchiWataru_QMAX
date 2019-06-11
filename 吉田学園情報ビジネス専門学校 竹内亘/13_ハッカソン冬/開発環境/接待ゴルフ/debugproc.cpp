//=============================================================================
//
// �f�o�b�O���� [light.cpp]
// Author :  Meguro Mikiya
//
//=============================================================================
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[MAX_CHAR] = {};

//--------------------------------------------
//�f�o�b�O�N���X �R���X�g���N�^
//--------------------------------------------
CDebugProc::CDebugProc()
{
}

//--------------------------------------------
//�f�o�b�O�N���X �f�X�g���N�^
//--------------------------------------------
CDebugProc::~CDebugProc()
{
}
//=============================================================================
// �f�o�b�O�̏���������
//=============================================================================
void CDebugProc::Init(void)
{
#ifdef _DEBUG

	//�f�o�C�X���擾
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 20, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);
#endif
}

//=============================================================================
// �f�o�b�O�̏I������
//=============================================================================
void CDebugProc::Uninit(void)
{
#ifdef _DEBUG

	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif
}

//=============================================================================
// �f�o�b�O�̍X�V����
//=============================================================================
void CDebugProc::Update(void)
{
}

//=============================================================================
// �v�����g�֐�
//=============================================================================
void CDebugProc::Print(int Num, char * fmt, ...)
{
#ifdef _DEBUG
	// *fmt �C�ӂ̐��̕����񂪊i�[����Ă���
	va_list list;
	char text[MAX_CHAR];
	text[0] = '\0';
	va_start(list, fmt);
	//�e�L�X�g�̏�������
	vsprintf(text,fmt,list);

	if (Num == 1)
	{
		// �厖�@���ɂȂ���
		strcat(&m_aStr[0], &text[0]);
	}
	else if (Num == 0)
	{
		// �㏑��
		wsprintf(&m_aStr[0], &text[0]);
	}
	va_end(list);
#endif
}

//=============================================================================
// �`�揈��	�֐�
//=============================================================================
void CDebugProc::Draw(void)
{
#ifdef _DEBUG
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
#endif

}

