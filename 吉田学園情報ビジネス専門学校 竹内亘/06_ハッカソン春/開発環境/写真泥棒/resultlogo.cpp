//=============================================================================
//
// ���U���g���S���� [resultlogo.cpp]
// Author : �|���j
//
//=============================================================================
#include "resultlogo.h"
#include "result.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME1       "data/TEXTURE/gameover.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZEX       (500)								// �e�N�X�`���𒣂�t���镝
#define TEXTURE_SIZEY       (175)								// �e�N�X�`���𒣂�t���鍂��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexResultLogo(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureResultLogo = NULL; // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultLogo = NULL; // ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_PosResultLogo;             // ���U���g���S���W
D3DXCOLOR				g_colorResultLogo;		     // ���U���g���S�F
int                     g_nCounterResultLogo;        // �^�C�g����ʂɑJ�ڂ���^�C�~���O 
//=============================================================================
// ����������
 //=============================================================================
void InitResultlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_PosResultLogo = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_colorResultLogo = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexResultLogo(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitResultlogo(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureResultLogo != NULL)
	{
		g_pTextureResultLogo->Release();
		g_pTextureResultLogo = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffResultLogo != NULL)
	{
		g_pVtxBuffResultLogo->Release();
		g_pVtxBuffResultLogo = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultlogo(void)
{
	FADE fade;
	fade = GetFade();

	g_nCounterResultLogo++;

	if (g_nCounterResultLogo % 600 == 0 && fade == FADE_NONE)
	{// ��莞�Ԃ�����
		SetFade(MODE_RANKING);
	}
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawResultlogo(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffResultLogo, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultLogo);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexResultLogo(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME1,
		&g_pTextureResultLogo);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultLogo,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

					   // ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResultLogo->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_PosResultLogo.x - TEXTURE_SIZEX, g_PosResultLogo.y - TEXTURE_SIZEY, g_PosResultLogo.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosResultLogo.x + TEXTURE_SIZEX, g_PosResultLogo.y - TEXTURE_SIZEY, g_PosResultLogo.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosResultLogo.x - TEXTURE_SIZEX, g_PosResultLogo.y + TEXTURE_SIZEY, g_PosResultLogo.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosResultLogo.x + TEXTURE_SIZEX, g_PosResultLogo.y + TEXTURE_SIZEY, g_PosResultLogo.z);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorResultLogo;
	pVtx[1].col = g_colorResultLogo;
	pVtx[2].col = g_colorResultLogo;
	pVtx[3].col = g_colorResultLogo;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultLogo->Unlock();
}