//=============================================================================
//
// ���U���g���S����(�Q�[���I�[�o�[���)[resultlogo2.cpp]
// Author : �|���j
//
//=============================================================================
#include "resultlogo2.h"
#include "result2.h"
#include "fade.h"

//#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME2       "data/TEXTURE/game_over.png"  // �ǂݍ��ރe�N�X�`���t�@�C���� 
#define TEXTURE_SIZEX       (500)                             // �e�N�X�`���𒣂�t���镝
#define TEXTURE_SIZEY       (175)                             // �e�N�X�`���𒣂�t���鍂��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexResultLogo2(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureResultLogo2 = NULL; // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResultLogo2 = NULL; // ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_PosResultLogo2;             // ���U���g���S���W
D3DXCOLOR				g_colorResultLogo2;		     // ���U���g���S�F
int                     g_nCounterResultLogo2;         // �^�C�g����ʂɑJ�ڂ���^�C�~���O 

//=============================================================================
// ����������
//=============================================================================
void InitResultLogo2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_PosResultLogo2 = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	g_colorResultLogo2 = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���̐ݒ�
	MakeVertexResultLogo2(pDevice);

}

//=============================================================================
// �I������
//=============================================================================
void UninitResultLogo2(void)
{
	// �e�N�X�`���̔j��
	if (g_pTextureResultLogo2 != NULL)
	{
		g_pTextureResultLogo2->Release();
		g_pTextureResultLogo2 = NULL;
	}
	
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffResultLogo2 != NULL)
	{
		g_pVtxBuffResultLogo2->Release();
		g_pVtxBuffResultLogo2 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateResultLogo2(void)
{
	FADE *pFade;
	pFade = GetFade();

	g_nCounterResultLogo2++;

	if (g_nCounterResultLogo2 % 600 == 0 && *pFade == FADE_NONE)
	{// ��莞�Ԃ�����
		SetFade(MODE_RANKING);
	}

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawResultLogo2(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffResultLogo2, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureResultLogo2);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexResultLogo2(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME2,
		&g_pTextureResultLogo2);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffResultLogo2,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffResultLogo2->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_PosResultLogo2.x - TEXTURE_SIZEX, g_PosResultLogo2.y - TEXTURE_SIZEY, g_PosResultLogo2.z);
	pVtx[1].pos = D3DXVECTOR3(g_PosResultLogo2.x + TEXTURE_SIZEX, g_PosResultLogo2.y - TEXTURE_SIZEY, g_PosResultLogo2.z);
	pVtx[2].pos = D3DXVECTOR3(g_PosResultLogo2.x - TEXTURE_SIZEX, g_PosResultLogo2.y + TEXTURE_SIZEY, g_PosResultLogo2.z);
	pVtx[3].pos = D3DXVECTOR3(g_PosResultLogo2.x + TEXTURE_SIZEX, g_PosResultLogo2.y + TEXTURE_SIZEY, g_PosResultLogo2.z);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_colorResultLogo2;
	pVtx[1].col = g_colorResultLogo2;
	pVtx[2].col = g_colorResultLogo2;
	pVtx[3].col = g_colorResultLogo2;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffResultLogo2->Unlock();
}