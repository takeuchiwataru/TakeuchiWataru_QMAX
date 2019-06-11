//=============================================================================
//
// �A�C�e���t�H���g��� [itemfont.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "itemfont.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_LINE	(2)

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPD3DXFONT			g_pItemFont[MAX_LINE] = {};			// �t�H���g�ւ̃|�C���^
ItemFont			g_ItemFont[MAX_LINE];				//�t�H���g�̏��
bool				g_bUseItemFont;						//�t�H���g���g�p���Ă��邩�ǂ���

//=============================================================================
// ����������
//=============================================================================
void InitItemFont(void)
{
	//�ϐ��錾
	int nCntItemFont;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (nCntItemFont = 0; nCntItemFont < MAX_LINE; nCntItemFont++)
	{
		g_ItemFont[nCntItemFont].font[0] = {};
		g_ItemFont[nCntItemFont].type = TYPEITEMFONT_MAX;
		g_ItemFont[nCntItemFont].bUse = false;

		//�t�H���g�̐ݒ�
		D3DXCreateFont(pDevice, 50, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
					   OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pItemFont[nCntItemFont]);
	}

	//�O���[�o���ϐ��̏�����
	g_bUseItemFont = false;
}

//=============================================================================
// �I������
//=============================================================================
void UninitItemFont(void)
{
	//�ϐ��錾
	int nCntItemFont;

	// �t�H���g�̊J��
	for (nCntItemFont = 0; nCntItemFont < MAX_LINE; nCntItemFont++)
	{
		if (g_pItemFont[nCntItemFont] != NULL)
		{
			g_pItemFont[nCntItemFont] ->Release();
			g_pItemFont[nCntItemFont] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItemFont(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItemFont(void)
{
	//�ϐ��錾
	int nCntItemFont;
	RECT rect = { 400, 610, (LONG)SCREEN_WIDTH, (LONG)SCREEN_HEIGHT };		//X���W, Y���W, �w���̕`��͈�, Y���̕`��͈�

	// �e�L�X�g�`��
	for (nCntItemFont = 0; nCntItemFont < MAX_LINE; nCntItemFont++)
	{
		if (g_ItemFont[nCntItemFont].bUse == true)
		{
			g_pItemFont[0]->DrawText(NULL, &g_ItemFont[nCntItemFont].font[0], -1, &rect, DT_LEFT, D3DXCOLOR(0.2f, 0.1f, 0.015f, 1.0f));
		}
	}
}

//=============================================================================
// ���ݒ�
//=============================================================================
void SetItemFont(char font[256], TYPEITEMFONT type)
{
	//�ϐ��錾
	int nCntItemFont;

	for (nCntItemFont = 0; nCntItemFont < MAX_LINE; nCntItemFont++)
	{
		if (g_ItemFont[nCntItemFont].bUse == false)
		{
			//������̑��
			wsprintf(&g_ItemFont[nCntItemFont].font[0], "%s", &font[0]);
			g_ItemFont[nCntItemFont].type = type;
			g_ItemFont[nCntItemFont].bUse = true;
			g_bUseItemFont = true;					//�t�H���g���g�p���Ă����Ԃɂ���
			break;
		}
	}
}

//=============================================================================
// �t�H���g������
//=============================================================================
void DeleteItemFont(void)
{
	//�ϐ��錾
	int nCntItemFont;

	for (nCntItemFont = 0; nCntItemFont < MAX_LINE; nCntItemFont++)
	{
		g_ItemFont[nCntItemFont].font[0] = {};
		g_ItemFont[nCntItemFont].type = TYPEITEMFONT_MAX;
		g_ItemFont[nCntItemFont].bUse = false;
	}
	
	g_bUseItemFont = false;						//�t�H���g���g�p���Ă��Ȃ���Ԃɂ���
}

//=============================================================================
// �����擾����
//=============================================================================
bool GetUseItemFont(void)
{
	return g_bUseItemFont;
}

