//=============================================================================
//
// ���C�t�A�C�R������ [life.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "life.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/Life000.png"	    // �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZE        (30)                            // �e�N�X�`���̃T�C�Y
#define MAX_LIFE            (8)                             // �̗͂̍ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
LIFE                    g_life[MAX_LIFE];       // ���C�t
int                     g_nCounterLife;         // ���݂̃��C�t��

//=============================================================================
// ����������
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{// ���C�t�A�C�R���������J��Ԃ�
		g_life[nCntLife].pos = D3DXVECTOR3(30, 500, 0);  // ���W��������
		g_life[nCntLife].bUse = false;                  // �g�p���Ă����Ԃɂ���
	}
	g_nCounterLife = 0;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	      // �f�o�C�X�ւ̃|�C���^
		TEXTURE_LIFE,		                  // �t�@�C���̖��O
		&g_pTextureLife);	                  // �e�N�X�`���ւ̃|�C���^

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

	// ���_�o�b�t�@�̔j��
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

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureLife);

	// �|���S���̕`��
	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{// �\�����郉�C�t�A�C�R���������J��Ԃ�
		if (g_life[nCntLife].bUse == true)
		{// ���C�t���g�p����Ă���
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntLife * 4,
				2);
		}
	}
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_LIFE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	float pos = 0;
	// ���_����ݒ�
	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{// ���C�t�A�C�R���������J��Ԃ�
		// ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_life[nCntLife].pos.x - TEXTURE_SIZE + pos, g_life[nCntLife].pos.y - TEXTURE_SIZE, g_life[nCntLife].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_life[nCntLife].pos.x + TEXTURE_SIZE + pos, g_life[nCntLife].pos.y - TEXTURE_SIZE, g_life[nCntLife].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_life[nCntLife].pos.x - TEXTURE_SIZE + pos, g_life[nCntLife].pos.y + TEXTURE_SIZE, g_life[nCntLife].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_life[nCntLife].pos.x + TEXTURE_SIZE + pos, g_life[nCntLife].pos.y + TEXTURE_SIZE, g_life[nCntLife].pos.z);


		// ���_�e�N�X�`��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		pos += 80.0f;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffLife->Unlock();
}
//=============================================================================
// ���C�t�̐ݒ�
//=============================================================================
void SetLife(int life)
{
	g_nCounterLife = life;  // ���C�t��ݒ�

	Player *pPlayer;
	pPlayer = GetPlayer();
	for (int nCntLife = 0; nCntLife < life; nCntLife++)
	{// ���C�t�A�C�R���������J��Ԃ�
		if (g_life[nCntLife].bUse == false)
		{// ���C�t���g�p����Ă��Ȃ�
			g_life[nCntLife].bUse = true;
		}
	}
	
}
//=============================================================================
// ���C�t�̌���
//=============================================================================
void CutLife(int cut)
{
	g_nCounterLife -= cut;

	for (int nCntLife = MAX_LIFE; nCntLife >= 0; nCntLife--)
	{// ���C�t�A�C�R���������J��Ԃ�
		if (g_life[nCntLife].bUse == true)
		{// ���C�t���g�p����Ă���
			g_life[nCntLife].bUse = false;
			break;
		}
	}
}
//=============================================================================
// ���C�t�̑���
//=============================================================================
void AddLife(int nValue)
{
	g_nCounterLife += nValue;

	for (int nCntLife = 0; nCntLife < MAX_LIFE; nCntLife++)
	{// ���C�t�A�C�R���������J��Ԃ�
		if (g_life[nCntLife].bUse == false)
		{// ���C�t���g�p����Ă��Ȃ�
			g_life[nCntLife].bUse = true;
			break;
		}
	}
}