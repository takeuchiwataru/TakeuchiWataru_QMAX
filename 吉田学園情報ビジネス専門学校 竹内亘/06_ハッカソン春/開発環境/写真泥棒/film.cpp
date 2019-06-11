//=============================================================================
//
// �t�B�������� [film.cpp]
// Author : Jukiya HayakawaFilm
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "film.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_NAME		"data/TEXTURE/film.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZE        (30)                            // �e�N�X�`���̃T�C�Y
#define MAX_FILM			(10)                             // �v���C���[�̃��C�t��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexFilm(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFilm = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFilm = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
FILM                    g_life[MAX_FILM];		// ���C�t
int                     g_nCounterFilm;         // ���݂̃��C�t��

//=============================================================================
// ����������
//=============================================================================
void InitFilm(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntFilm = 0; nCntFilm < MAX_FILM; nCntFilm++)
	{// ���C�t�A�C�R���������J��Ԃ�
		g_life[nCntFilm].pos = D3DXVECTOR3(620.0f,SCREEN_HEIGHT - 50.0f, 0.0);   // ���W��������
		g_life[nCntFilm].bUse = true;                     // �g�p���Ă����Ԃɂ���
	}
	g_nCounterFilm = MAX_FILM;							  // ���݂̃��C�t����������

	 // �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					  // �f�o�C�X�ւ̃|�C���^
		TEXTURE_NAME,									  // �t�@�C���̖��O
		&g_pTextureFilm);								  // �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexFilm(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitFilm(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureFilm != NULL)
	{
		g_pTextureFilm->Release();
		g_pTextureFilm = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffFilm != NULL)
	{
		g_pVtxBuffFilm->Release();
		g_pVtxBuffFilm = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFilm(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFilm(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFilm, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFilm);

	// �|���S���̕`��
	for (int nCntFilm = 0; nCntFilm < MAX_FILM; nCntFilm++)
	{// �\�����郉�C�t�A�C�R���������J��Ԃ�
		if (g_life[nCntFilm].bUse == true)
		{// ���C�t���g�p����Ă���
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntFilm * 4,
				2);
		}
	}
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexFilm(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FILM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFilm,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFilm->Lock(0, 0, (void**)&pVtx, 0);

	float pos = 0;
	// ���_����ݒ�
	for (int nCntFilm = 0; nCntFilm < MAX_FILM; nCntFilm++)
	{// ���C�t�A�C�R���������J��Ԃ�
	 // ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_life[nCntFilm].pos.x - TEXTURE_SIZE + pos, g_life[nCntFilm].pos.y - TEXTURE_SIZE, g_life[nCntFilm].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_life[nCntFilm].pos.x + TEXTURE_SIZE + pos, g_life[nCntFilm].pos.y - TEXTURE_SIZE, g_life[nCntFilm].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_life[nCntFilm].pos.x - TEXTURE_SIZE + pos, g_life[nCntFilm].pos.y + TEXTURE_SIZE, g_life[nCntFilm].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_life[nCntFilm].pos.x + TEXTURE_SIZE + pos, g_life[nCntFilm].pos.y + TEXTURE_SIZE, g_life[nCntFilm].pos.z);


		// ���_�e�N�X�`��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[1].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[2].col = D3DXCOLOR(255, 255, 255, 255);
		pVtx[3].col = D3DXCOLOR(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		pos -= 60.0f;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFilm->Unlock();
}
//=============================================================================
// ���C�t�̌���
//=============================================================================
void CutFilm(int cut)
{
	for (int nCntFilm = 0; nCntFilm < MAX_FILM; nCntFilm++)
	{// ���C�t�A�C�R���������J��Ԃ�
		if (g_life[nCntFilm].bUse == true)
		{// ���C�t���g�p����Ă���
			g_life[nCntFilm].bUse = false;
			g_nCounterFilm--;
			if (g_nCounterFilm <= 0)
			{
				if (GetGameState() != GAMESTATE_END)
				{
					SetGameState(GAMESTATE_END);
				}
			}
			break;
		}
	}
}
int GetFilmNum(void)
{
	return g_nCounterFilm;
}