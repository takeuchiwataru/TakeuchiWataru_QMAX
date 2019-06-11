//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number000.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZE        (30)                            // �e�N�X�`���̃T�C�Y
#define MAX_SCORENUMBER     (8)                             // �X�R�A�̌���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_ScorePos;                 // ���_���W
int                     g_TexturePos;               // �e�N�X�`��X���W
int						g_nScore;					// �X�R�A

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_nScore = 0;                             // �X�R�A�̏�����
	g_ScorePos = D3DXVECTOR3(1230, 30, 0.0f); // ���W�̏�����

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureScore);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexScore(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	// �|���S���̕`��
	for (int nCntScore = 0; nCntScore < MAX_SCORENUMBER; nCntScore++)
	{// �\������X�R�A�̌��������J��Ԃ�
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntScore * 4,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORENUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�
	for (int nCntScore = 0; nCntScore < MAX_SCORENUMBER; nCntScore++)
	{// �X�R�A�̌��������J��Ԃ�
		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_ScorePos.x - TEXTURE_SIZE, g_ScorePos.y - TEXTURE_SIZE, g_ScorePos.z);
		pVtx[1].pos = D3DXVECTOR3(g_ScorePos.x + TEXTURE_SIZE, g_ScorePos.y - TEXTURE_SIZE, g_ScorePos.z);
		pVtx[2].pos = D3DXVECTOR3(g_ScorePos.x - TEXTURE_SIZE, g_ScorePos.y + TEXTURE_SIZE, g_ScorePos.z);
		pVtx[3].pos = D3DXVECTOR3(g_ScorePos.x + TEXTURE_SIZE, g_ScorePos.y + TEXTURE_SIZE, g_ScorePos.z);


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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
		g_ScorePos.x -= 50;
	}
	g_ScorePos.x = 1000;
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddScore(int nValue)
{
	int Score = 1;
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;
	g_nScore += nValue;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntScore = 0; nCntScore < MAX_SCORENUMBER; nCntScore++)
	{// �X�R�A�̌��������J��Ԃ�
		g_TexturePos = g_nScore % (Score * 10) / Score;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_TexturePos), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_TexturePos), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_TexturePos), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_TexturePos), 1.0f);

		pVtx += 4;
		Score *= 10;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}
//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int GetScore(void)
{
	return g_nScore;
}