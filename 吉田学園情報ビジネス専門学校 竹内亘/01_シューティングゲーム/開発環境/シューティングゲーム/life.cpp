//=============================================================================
//
// ���C�t���� [life.cpp]
// Author : �|���j
//
//=============================================================================
#include "main.h"
#include "life.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/life000.png"		//�ǂݍ��ރe�N�X�`���t�@�C����
#define LIFE_SIZE (15.0f)									//���C�t�T�C�Y
#define LIFE_WIDE (25)										//���C�t�̕�
#define LIFE_POS (30)										//���C�t�̏ꏊ
#define MAX_LIFE (3)										//���C�t�̌���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;				// ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3				g_LifePos(100, 50, 0.0f);			// ���C�t�̒��_���W
LIFE					g_nLife[MAX_LIFE];					// ���C�t
//int						g_TexturePosLife;				// �e�N�X�`��X���W
int g_Life;

//=============================================================================
// ����������
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntLife;
	g_Life = 3;
	//���C�t�̏�����
	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{
		g_nLife[nCntLife].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_LIFE,			// �t�@�C���̖��O
		&g_pTextureLife);		// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexLife(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitLife(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureLife != NULL)
	{
		g_pTextureLife->Release();
		g_pTextureLife = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateLife(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntLife;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLife);

	// �|���S���̕`��
	for (nCntLife = 0; nCntLife < g_Life; nCntLife++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntLife, 2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// ���_����ݒ�
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	int nCntLife;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{

		//���_���W�̐ݒ� 
		pVtx[0].pos = D3DXVECTOR3(g_LifePos.x - LIFE_SIZE, g_LifePos.y - LIFE_SIZE, g_LifePos.z);
		pVtx[1].pos = D3DXVECTOR3(g_LifePos.x + LIFE_SIZE, g_LifePos.y - LIFE_SIZE, g_LifePos.z);
		pVtx[2].pos = D3DXVECTOR3(g_LifePos.x - LIFE_SIZE, g_LifePos.y + LIFE_SIZE, g_LifePos.z);
		pVtx[3].pos = D3DXVECTOR3(g_LifePos.x + LIFE_SIZE, g_LifePos.y + LIFE_SIZE, g_LifePos.z);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^���S���i�߂�
		g_LifePos.x -= 30;
	}
	g_LifePos.x = 100;

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// ���C�t����
//=============================================================================
void CutLife(int nCut)
{
	g_Life -= nCut;
}
