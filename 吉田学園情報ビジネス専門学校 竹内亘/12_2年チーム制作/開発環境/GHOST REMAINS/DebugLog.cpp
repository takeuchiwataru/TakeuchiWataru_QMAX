//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : Ryo Sugimoto
//
//=============================================================================
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall�˔j
#include "DebugLog.h"
#include "renderer.h"
#include "manager.h"
#include <stdio.h>
#include <stdarg.h>
#include <tchar.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �X�V����
//=============================================================================
void	CDebugLog::Init(void)
{
	m_Mode = MODE_LOG;
	strcpy(&m_aMode[0], "DebugLog > ");
	m_aStr[0] = '\0';
	m_aFPS[0] = '\0';
	m_nFps = 0;
	m_nSelect = 0;
	m_bDraw = false;
	LogUpdate();

#ifdef _DEBUG
	m_bDraw = true;
#endif

	// �f�o�b�O���\���p�t�H���g�̐���

	D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 26, 8, 0, 0, FALSE, MONO_FONT,
		OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &m_pFont);
}
//=============================================================================
// �I������
//=============================================================================
void	CDebugLog::Uninit(void)
{
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void	CDebugLog::Update(void)
{
	CInputKeyboard *pInputKey = CManager::GetInputKey();
	bool bSelect = false;
	if (m_Mode == MODE_LOG)
	{
		m_aStr[500] = '\0';	//���O�̒��g�����
	}
	else if (m_Mode == MODE_INFO)
	{
		m_aStr[0] = '\0';	//���O�̒��g�����
	}

	if (m_bDraw)
	{
		if (pInputKey->GetTrigger(DIK_ADD))
		{//+
			bSelect = true;
			m_nSelect = (m_nSelect + 1) % MODE_LOG;
		}
		else if (pInputKey->GetTrigger(DIK_SUBTRACT))
		{//-
			bSelect = true;
			m_nSelect = (m_nSelect + MODE_LOG - 1) % MODE_LOG;
		}

		//�i��
		if (pInputKey->GetTrigger(DIK_NUMPADENTER)) 
		{ 
			bSelect = true;
			switch (m_Mode)
			{
			case MODE_NONE:
				switch (m_nSelect)
				{
				case 0: m_Mode = MODE_Change; break;
				case 1: m_Mode = MODE_INFO; break;
				case 2: m_Mode = MODE_LOG; m_aStr[0] = '\0'; break;
				}
				break;
			}
		}

		//�߂�
		if (pInputKey->GetTrigger(DIK_PGDN) && m_Mode != MODE_NONE)
		{
			bSelect = true;
			switch (m_Mode)
			{
			case MODE_Change:
			case MODE_INFO:
			case MODE_LOG:
				m_Mode = MODE_NONE;
				break;
			}
		}
	}

	if (pInputKey->GetTrigger(DIK_F1))
	{//�\����ԕύX
		m_bDraw = (m_bDraw ? false : true);
		m_nSelect = 0;
		bSelect = true;
	}

	if (bSelect)
	{
		LogUpdate();
	}
	wsprintf(&m_aFPS[0], "FPS�F%d", m_nFps);
}
//=============================================================================
// �X�V����
//=============================================================================
void	CDebugLog::Draw(void)
{
	if (m_bDraw)
	{//�\����ԂȂ�
		RECT rect;
		rect = { 2, 2, SCREEN_WIDTH, SCREEN_HEIGHT };
		m_pFont->DrawText(NULL, &m_aFPS[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
		rect = RECT{ 0 , 0, SCREEN_WIDTH, SCREEN_HEIGHT };
		m_pFont->DrawText(NULL, &m_aFPS[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

		rect = { 2, 22, SCREEN_WIDTH, SCREEN_HEIGHT };
		m_pFont->DrawText(NULL, &m_aMode[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
		rect = RECT{ 0 , 20, SCREEN_WIDTH, SCREEN_HEIGHT };
		m_pFont->DrawText(NULL, &m_aMode[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));

		rect = RECT{ 2 , 72, SCREEN_WIDTH, SCREEN_HEIGHT };
		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 0, 0, 255));
		rect = RECT{ 0 , 70, SCREEN_WIDTH, SCREEN_HEIGHT };
		m_pFont->DrawText(NULL, &m_aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void CDebugLog::Printf(MODE mode, const TCHAR* format, ...)
{
	if (mode == m_Mode)
	{
		int		nLength = 0;
		static TCHAR strBuffer_g[1024];
		va_list args;

		va_start(args, format);
		_vstprintf(strBuffer_g, format, args);
		
		if ((int)strlen(&m_aStr[0]) + (int)strlen(strBuffer_g) + 3 < 1024)
		{
			if (m_Mode == MODE_LOG)
			{//���O��ԂȂ�
				char aStr[1024];
				strcpy(&aStr[0], &m_aStr[0]);

				strcpy(&m_aStr[0], " * ");
				strcat(&m_aStr[0], strBuffer_g);
				strcat(&m_aStr[0], &aStr[0]);
			}
			else
			{
				strcat(&m_aStr[0], " * ");
				strcat(&m_aStr[0], strBuffer_g);
			}
		}
		m_aStr[900] = '\0';	//���O�̒��g�����
	}
}
//=============================================================================
// ���O�̍X�V����
//=============================================================================
void CDebugLog::LogUpdate(void)
{
	strcpy(&m_aMode[0], "DebugLog > ");
	switch (m_Mode)
	{
	case MODE_Change: strcat(&m_aMode[0], "Mode > ");	break;
	case MODE_INFO:   strcat(&m_aMode[0], "Info > ");	break;
	case MODE_LOG:    strcat(&m_aMode[0], "Log > ");	break;
	}

	if (m_Mode == MODE_NONE)
	{//�������[�h
		m_aStr[0] = '\0';
		for (int nCount = 0; nCount < 3; nCount++)
		{
			if (m_nSelect != nCount) { strcat(&m_aStr[0], "   "); }
			switch (nCount)
			{
			case 0: strcat(&m_aStr[0], "MODE\n"); break;
			case 1: strcat(&m_aStr[0], "INFO\n"); break;
			case 2: strcat(&m_aStr[0], "LOG\n"); break;
			}
		}
	}
	else if (m_Mode == MODE_Change)
	{//���[�h�ؑ�
		m_aStr[0] = '\0';
		for (int nCount = 0; nCount < 3; nCount++)
		{
			if (m_nSelect != nCount) { strcat(&m_aStr[0], "   "); }
			switch (nCount)
			{
			case 0: strcat(&m_aStr[0], "Title\n"); break;
			case 1: strcat(&m_aStr[0], "Select\n"); break;
			case 2: strcat(&m_aStr[0], "Game\n"); break;
			}
		}
	}

}