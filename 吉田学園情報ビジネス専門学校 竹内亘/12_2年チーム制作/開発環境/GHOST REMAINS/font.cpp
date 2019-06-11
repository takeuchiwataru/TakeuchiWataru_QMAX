//=========================================================================================================//
//
// �w�i���� [bg.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#define _CRT_SECURE_NO_WARNINGS
#include "Font.h"
#include "manager.h"
#include "renderer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*********************************************************************************************************//
// �}�N����`
//*********************************************************************************************************//
#define SPEECH_FLOW		(3)
//*********************************************************************************************************//
// �ÓI�����o�ϐ�
//*********************************************************************************************************//
LPD3DXFONT	CFont::m_pFont[MAX_FONT_TYPE] = {};			// �t�H���g�ւ̃|�C���^

//=========================================================================================================//
// ����������
//=========================================================================================================//
void	CFont::Load(int nID)
{
	if (m_pFont[nID] == NULL)
	{
		switch (nID)
		{
		case 0:
			D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 34, 11, 0, 0, FALSE, MONO_FONT,
				OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &m_pFont[nID]);
			break;
		case 1:
			D3DXCreateFont(CManager::GetRenderer()->GetDevice(), 44, 16, 0, 0, FALSE, MONO_FONT,
				OUT_DEFAULT_PRECIS, DRAFT_QUALITY, DEFAULT_PITCH, "Font", &m_pFont[nID]);
			break;
		}
	}
}
//=========================================================================================================//
// ����������
//=========================================================================================================//
void	CFont::UnLoad(void)
{
	for (int nCntFont = 0; nCntFont < MAX_FONT_TYPE; nCntFont++)
	{
		if (m_pFont[nCntFont] != NULL)
		{// �f�o�b�O�\���p�t�H���g�̊J��
			m_pFont[nCntFont]->Release();
			m_pFont[nCntFont] = NULL;
		}
	}
}
//=========================================================================================================//
// ����������
//=========================================================================================================//
HRESULT CFont::Init(void)
{
	m_bDisplay = false;
	m_state = STATE_NONE;
	return S_OK;
}
//=========================================================================================================//
// �I������
//=========================================================================================================//
void CFont::Uninit(void)
{
	CScene::Uninit();
}
//=========================================================================================================//
// �X�V����
//=========================================================================================================//
void CFont::Update(void)
{
	if (m_state != STATE_NONE)
	{//��Ԃ��ʏ�ł͂Ȃ�...!!
		switch (m_state)
		{
		case STATE_UP:
			break;
		case STATE_FADE:
			m_col.a += m_fCntState;
			if (m_col.a >= 1.0f)
			{
				m_col.a = 1.0f;
				m_state = STATE_FADEOUT;
			}
			break;
		case STATE_FADEOUT2:
			m_col.a -= 0.03f;
			if (m_col.a <= 0.0f) 
			{
				m_col.a = 0.0f;
				m_state = STATE_NONE;
			}
			break;
		case STATE_FADEOUT:
			m_col.a -= m_fCntState;
			if (m_col.a <= 0.0f)
			{
				Uninit();
			}
			break;
		case STATE_ENDOUT:
			if (-1 == m_nMaxFont)
			{
				m_col.a -= m_fCntState;
				if (m_col.a <= 0.0f)
				{
					Uninit();
				}
			}
		}
	}
}

//=========================================================================================================//
// �`�揈��
//=========================================================================================================//
void CFont::Draw(void)
{
	D3DCOLOR col;
	RECT rect;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	char aStr[84];
	char aStr0[84];		//\n�m�F�p
	int nLength;

	// �e�L�X�g�`��
	// hDC      : �f�o�C�X�R���e�L�X�g�̃n���h��
	// lpString : �`�悷�镶����ւ̃|�C���^
	// nCount   : ������̕�����
	// lpRect   : �����`�̈�
	// uFormat  : �e�L�X�g�̐��`���@���w��

	if (m_bDisplay == true)
	{// ��������� �\��
		strcpy(&aStr[0], &m_aStr[0]);
		if (m_nMaxFont > -1)
		{//�����������߂��Ă���
			nLength = (int)strlen(&aStr[0]);
			if (nLength > m_nMaxFont)
			{//������̂ق�������
				strcpy(&aStr[m_nMaxFont], "\0");
				m_nCntTime--;
				if (m_nCntTime <= 0)
				{//�J�E���g���i��
					strcpy(&aStr0[0], &m_aStr[0]);
					strcpy(&aStr0[m_nMaxFont + 1], "\0");
					if (strcmp(&aStr0[m_nMaxFont], "\n") == 0) { m_nMaxFont++; }
					m_nCntTime = SPEECH_FLOW;
					m_nMaxFont += 2;
					if (nLength <= m_nMaxFont) {m_nMaxFont = -1; }
				}
			}
		}

		if (m_bshadow == true)
		{//�e���v�]�Ȃ�
			col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			rect = m_rect;
			rect.left += 2; rect.top += 2; rect.right += 2; rect.bottom += 2;
			m_pFont[m_nType]->DrawText(NULL, &aStr[0], -1, &rect, m_nFormat, col);
		}
		col = m_col;	//�F�̌^��ϊ�
		m_pFont[m_nType]->DrawText(NULL, &aStr[0], -1, &m_rect, m_nFormat, col);
		//DT_LEFT;
	}
}
//=========================================================================================================//
// �����������  Set!!
//=========================================================================================================//
void CFont::Set(RECT rect, D3DXCOLOR col, char *aStr, int nType, int nFormat, int nMaxFont, bool bShadow, STATE state)
{//�����Z�b�g
	m_bDisplay = true;
	m_state = state;
	m_nType = nType;
	m_nFormat = nFormat;
	m_nMaxFont = nMaxFont;
	m_nCntTime = SPEECH_FLOW;
	m_rect = rect;
	strcpy(&m_aStr[0], &aStr[0]);
	m_col = col;
	m_fCntState = 0.0f;
	m_bshadow = bShadow;

	Load(nType);
}
//=========================================================================================================//
//	���������̂ݕύX
//=========================================================================================================//
void	CFont::SetFont(char *aStr, int nMaxFont)
{
	strcpy(&m_aStr[0], &aStr[0]);
	m_nMaxFont = nMaxFont;
}
