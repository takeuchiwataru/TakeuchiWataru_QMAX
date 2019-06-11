//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "fade.h"
#include "pressenter.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_POS_X         (0)                         // �t�F�[�h�̍���w���W
#define FADE_POS_Y         (0)                         // �t�F�[�h�̍���x���W
#define FADE_WIDTH         (SCREEN_WIDTH)              // �t�F�[�h�̕�
#define FADE_HEIGHT        (SCREEN_HEIGHT)             // �t�F�[�h�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFade = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
FADE					g_fade;					// �t�F�[�h���
MODE					g_modeNext;				// ���̃��[�h
D3DXCOLOR				g_colorFade;			// �t�F�[�h�F

//=============================================================================
// ����������
//=============================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_fade = FADE_IN;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexFade(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{// �t�F�[�h�C�����
			g_colorFade.a -= 0.020f; // ��ʂ𓧖��ɂ���
			if (g_colorFade.a <= 0.0f)
			{// ��ʂ������ɂȂ肫����
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;
			}
		}
		else if (g_fade == FADE_OUT)
		{// �t�F�[�h�A�E�g���
			g_colorFade.a += 0.020f; // ��ʂ�s�����ɂ���
			if (g_colorFade.a >= 1.0f)
			{// ��ʂ������ɂȂ肫����
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;

				// ���[�h�̐ݒ�
				SetMode(g_modeNext);
			}
		}
		VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

		// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		// ���_�o�b�t�@���A�����b�N����
		g_pVtxBuffFade->Unlock();
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureFade);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(FADE_WIDTH, FADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FADE_POS_X, FADE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(FADE_WIDTH, FADE_HEIGHT, 0.0f);


	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFade->Unlock();
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}

