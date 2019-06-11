//=============================================================================
//
// �؂ꖡ���� [reload.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "reload.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_RELOAD		"data/TEXTURE/��.png"	    // �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZE        (120)                            // �e�N�X�`���̃T�C�Y

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexReload(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureReload = NULL;  // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReload = NULL;  // ���_�o�b�t�@�ւ̃|�C���^
Reload                  g_Reload[PLAYER_SHARP];   // �؂ꖡ

//=============================================================================
// ����������
//=============================================================================
void InitReload(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntReload = 0; nCntReload < PLAYER_SHARP; nCntReload++)
	{// �؂ꖡ�������J��Ԃ�
		g_Reload[nCntReload].pos = D3DXVECTOR3(900, 650, 0);  // ���W��������
		g_Reload[nCntReload].bUse = false;                  // �g�p���Ă����Ԃɂ���
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	      // �f�o�C�X�ւ̃|�C���^
		TEXTURE_RELOAD,		                  // �t�@�C���̖��O
		&g_pTextureReload);	                  // �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexReload(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitReload(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureReload != NULL)
	{
		g_pTextureReload->Release();
		g_pTextureReload = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffReload != NULL)
	{
		g_pVtxBuffReload->Release();
		g_pVtxBuffReload = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateReload(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawReload(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffReload, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureReload);

	// �|���S���̕`��
	for (int nCntReload = 0; nCntReload < PLAYER_SHARP; nCntReload++)
	{// �\������؂ꖡ�������J��Ԃ�
		if (g_Reload[nCntReload].bUse == true)
		{// �؂ꖡ���g�p����Ă���
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntReload * 4,
				2);
		}
	}
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexReload(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PLAYER_SHARP,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReload,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffReload->Lock(0, 0, (void**)&pVtx, 0);

	float pos = 0;
	// ���_����ݒ�
	for (int nCntReload = 0; nCntReload < PLAYER_SHARP; nCntReload++)
	{// �؂ꖡ�������J��Ԃ�
	 // ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_Reload[nCntReload].pos.x - TEXTURE_SIZE + pos, g_Reload[nCntReload].pos.y - TEXTURE_SIZE, g_Reload[nCntReload].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_Reload[nCntReload].pos.x + TEXTURE_SIZE + pos, g_Reload[nCntReload].pos.y - TEXTURE_SIZE, g_Reload[nCntReload].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_Reload[nCntReload].pos.x - TEXTURE_SIZE + pos, g_Reload[nCntReload].pos.y + TEXTURE_SIZE, g_Reload[nCntReload].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_Reload[nCntReload].pos.x + TEXTURE_SIZE + pos, g_Reload[nCntReload].pos.y + TEXTURE_SIZE, g_Reload[nCntReload].pos.z);


		// ���_�e�N�X�`��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		pos += 30.0f;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffReload->Unlock();
}
//=============================================================================
// �؂ꖡ�̐ݒ�
//=============================================================================
void SetReload(int Reload)
{
	for (int nCntReload = 0; nCntReload < Reload; nCntReload++)
	{// �؂ꖡ�������J��Ԃ�
		if (g_Reload[nCntReload].bUse == false)
		{// �؂ꖡ���g�p����Ă��Ȃ�
			g_Reload[nCntReload].bUse = true;
		}
	}

}
//=============================================================================
// �؂ꖡ�̌���
//=============================================================================
void CutReload(int cut)
{
	for (int nCntReload = PLAYER_SHARP; nCntReload >= 0; nCntReload--)
	{// �؂ꖡ�������J��Ԃ�
		if (g_Reload[nCntReload].bUse == true)
		{// �؂ꖡ���g�p����Ă���
			g_Reload[nCntReload].bUse = false;
			break;
		}
	}
}
//=============================================================================
// �؂ꖡ�̑���
//=============================================================================
void AddReload(void)
{
	for (int nCntReload = 0; nCntReload < PLAYER_SHARP; nCntReload++)
	{// �؂ꖡ�̐������J��Ԃ�
		if (g_Reload[nCntReload].bUse == false)
		{// �؂ꖡ���g�p����Ă��Ȃ�
			g_Reload[nCntReload].bUse = true;
		}
	}
}