//=============================================================================
//
// �`���[�g���A���w�i�̏��� [tutorialbg.cpp]
// Author : Jukiya Hayakawa
//
//=============================================================================
#include "tutorialbg.h"
#include "main.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TUTORIALBG_TEXTURE_NAME0	"data\\TEXTURE\\tutorial000.png"	//�e�N�X�`����
#define TUTORIALBG_TEXTURE_NAME1	"data\\TEXTURE\\tutorial001.png"	//�e�N�X�`����
#define TUTORIALBG_SIZE_X		(650.0f)								// �傫��
#define TUTORIALBG_SIZE_Y		(300.0f)								// �n�ʑ傫��
#define MAX_TUTORIALBG			(2)										// �`���[�g���A���w�i�̐�

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTutorialBG(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9	g_pVtxBuffTutorialBG = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureTutorialBG[MAX_TUTORIALBG];	// �e�N�X�`���ւ̃|�C���^
TUTORIALBG				g_aTutorialBG[MAX_TUTORIALBG];

//=============================================================================
// ����������
//=============================================================================
void InitTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

												// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TUTORIALBG_TEXTURE_NAME0, &g_pTextureTutorialBG[0]);
	D3DXCreateTextureFromFile(pDevice, TUTORIALBG_TEXTURE_NAME1, &g_pTextureTutorialBG[1]);

	// ���_���̍쐬
	MakeVertexTutorialBG(pDevice);

	for (int nCntTutorialBG = 0; nCntTutorialBG < MAX_TUTORIALBG; nCntTutorialBG++)
	{
		// �|���S���̏���ݒ�
		g_aTutorialBG[nCntTutorialBG].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
		g_aTutorialBG[nCntTutorialBG].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
		g_aTutorialBG[nCntTutorialBG].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���

		g_aTutorialBG[nCntTutorialBG].bUse = false;
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitTutorialBG(void)
{
	for (int nCntTutorialBG = 0; nCntTutorialBG < MAX_TUTORIALBG; nCntTutorialBG++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureTutorialBG[nCntTutorialBG] != NULL)
		{
			g_pTextureTutorialBG[nCntTutorialBG]->Release();
			g_pTextureTutorialBG[nCntTutorialBG] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffTutorialBG != NULL)
	{
		g_pVtxBuffTutorialBG->Release();
		g_pVtxBuffTutorialBG = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTutorialBG(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTutorialBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		// �f�o�C�X�ւ̃|�C���^
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

									// �f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int nCntTutorialBG = 0; nCntTutorialBG < MAX_TUTORIALBG; nCntTutorialBG++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aTutorialBG[nCntTutorialBG].rot.y, g_aTutorialBG[nCntTutorialBG].rot.x, g_aTutorialBG[nCntTutorialBG].rot.z);
		D3DXMatrixMultiply(&g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG, &g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aTutorialBG[nCntTutorialBG].pos.x, g_aTutorialBG[nCntTutorialBG].pos.y, g_aTutorialBG[nCntTutorialBG].pos.z);
		D3DXMatrixMultiply(&g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG, &g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aTutorialBG[nCntTutorialBG].mtxWorldTutorialBG);


		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffTutorialBG, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTutorialBG[nCntTutorialBG]);

		if (g_aTutorialBG[nCntTutorialBG].bUse == true)	// �e���g�p����Ă���
		{
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntTutorialBG,
				2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTutorialBG(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_TUTORIALBG,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorialBG,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTutorialBG = 0; nCntTutorialBG < MAX_TUTORIALBG; nCntTutorialBG++)
	{
		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x - TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y + TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x + TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y + TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x - TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y - TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x + TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y - TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[1].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[2].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[3].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//���_�f�[�^�̃|�C���^��4���i�߂�
		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorialBG->Unlock();
}

//=============================================================================
// �`���[�g���A���w�i�̐ݒ�
//=============================================================================
void SetTutorialBG(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	int nCntTutorialBG;

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTutorialBG->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTutorialBG = 0; nCntTutorialBG < MAX_TUTORIALBG; nCntTutorialBG++)
	{
		if (g_aTutorialBG[nCntTutorialBG].bUse == false)
		{
			g_aTutorialBG[nCntTutorialBG].pos = pos;
			g_aTutorialBG[nCntTutorialBG].rot = rot;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x - TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y + TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x + TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y + TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x - TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y - TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aTutorialBG[nCntTutorialBG].pos.x + TUTORIALBG_SIZE_X, g_aTutorialBG[nCntTutorialBG].pos.y - TUTORIALBG_SIZE_Y, g_aTutorialBG[nCntTutorialBG].pos.z);

			g_aTutorialBG[nCntTutorialBG].bUse = true;
			break;
		}
		pVtx += 4;	// �Y���̈ʒu�܂Ői�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTutorialBG->Unlock();
}