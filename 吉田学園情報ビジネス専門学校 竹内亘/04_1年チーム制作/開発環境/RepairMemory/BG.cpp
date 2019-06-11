//=============================================================================
//
// �w�i���� [BG.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "BG.h"
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEX	(3)		//�ǂ݂��ރe�N�X�`���̍ő吔
#define MAX_BG	(2)		//�w�i�̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBG[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;		//���_�o�b�t�@�ւ̃|�C���^
BG						g_BG[MAX_BG];				//���ݒ�

//=============================================================================
// �X�^�[�g�{�^������������
//=============================================================================
void InitBG(void)
{
	//�ϐ��錾
	char	BGName[MAX_TEX][48];		//�t�@�C�������i�[����
	int		nCntTex;
	int     nCntBG;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		g_BG[nCntBG].nTexNum = 0;				//�e�N�X�`���̔ԍ�
		g_BG[nCntBG].bUse = false;				//�g�p���Ă��Ȃ���Ԃɂ���
	}

	//�e�N�X�`���t�@�C�������i�[����
	wsprintf(&BGName[0][0], "data\\TEXTURE\\bg004.jpg");	//�X�g�[���[�w�i
	wsprintf(&BGName[1][0], "data\\TEXTURE\\select.jpg");	//�N�G�X�g�I����ʔw�i
	wsprintf(&BGName[2][0], "data\\TEXTURE\\quest.jpg");	//�N�G�X�g�N���A���


	//�e�N�X�`���̓ǂݍ���
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &BGName[nCntTex][0],
								  &g_pTextureBG[nCntTex]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BG,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffBG,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTex = 0; nCntTex < MAX_BG; nCntTex++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBG->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitBG(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureBG[nCntTex] != NULL)
		{
			g_pTextureBG[nCntTex]->Release();
			g_pTextureBG[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateBG(void)
{
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawBG(void)
{
	//�ϐ��錾
	int nCntBG;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		if (g_BG[nCntBG].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBG[g_BG[nCntBG].nTexNum]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								   nCntBG * 4,				//�J�n���钸�_�̃C���f�b�N�X
								   2);						//�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// ���ݒ�
//=============================================================================
void SetBG(int nTexNum)
{
	//�ϐ��錾
	int nCntBG;

	for (nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		if (g_BG[nCntBG].bUse == false)
		{
			g_BG[nCntBG].nTexNum = nTexNum;		//�e�N�X�`���̔ԍ�
			g_BG[nCntBG].bUse = true;			//�g�p���Ă����Ԃɂ���
			break;
		}
	}
}

//=============================================================================
// �w�i������
//=============================================================================
void DeleteBG()
{
	//�ϐ��錾
	int nCntBG;

	for (nCntBG = 0; nCntBG < MAX_BG; nCntBG++)
	{
		if (g_BG[nCntBG].bUse == true)
		{
			g_BG[nCntBG].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
		}
	}
}