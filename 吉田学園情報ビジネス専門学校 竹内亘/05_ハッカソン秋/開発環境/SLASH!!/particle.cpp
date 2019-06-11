//=============================================================================
//
// �p�[�e�B�N���̏��� [particle.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "particle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PARTICLE	  "data/TEXTURE/effect000.jpg"    // �ǂݍ��ރe�N�X�`���t�@�C����
#define PARTICLE_TEXTURESIZE  (10)                            // �|���S���̃T�C�Y
#define	MAX_PARTICLE		  (4096)						  // �p�[�e�B�N���̍ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 move;		// �ړ���
	D3DXCOLOR col;			// �F
	float fRadius;			// ���a(�傫��)
	int nLife;				// �\������(����)
	bool bUse;				// �g�p���Ă��邩�ǂ���
} PARTICLE;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureParticle = NULL;	 // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;	 // ���_�o�b�t�@�ւ̃|�C���^
PARTICLE			    g_aParticle[MAX_PARTICLE];   // �p�[�e�B�N���̏��

//=============================================================================
// ����������
//=============================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̐������J��Ԃ�
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aParticle[nCntParticle].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aParticle[nCntParticle].fRadius = 0.0f;
		g_aParticle[nCntParticle].nLife = 0;
		g_aParticle[nCntParticle].bUse = false;
	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_PARTICLE,
		&g_pTextureParticle);

	// ���_���̍쐬
	MakeVertexParticle(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitParticle(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffParticle != NULL)
	{
		g_pVtxBuffParticle->Release();
		g_pVtxBuffParticle = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateParticle(void)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	// �|���S���̕`��
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̐������J��Ԃ�
		if (g_aParticle[nCntParticle].bUse == true)
		{// �p�[�e�B�N�����g�p����Ă���
			g_aParticle[nCntParticle].nLife--;
			g_aParticle[nCntParticle].pos += g_aParticle[nCntParticle].move;

			g_aParticle[nCntParticle].fRadius--;
			g_aParticle[nCntParticle].col.r -= 0.005f;
			g_aParticle[nCntParticle].col.g -= 0.02f;
			g_aParticle[nCntParticle].col.b -= 0.05f;
			g_aParticle[nCntParticle].col.a -= 0.005f;

			if (g_aParticle[nCntParticle].nLife <= 0)
			{// ��莞�Ԍo��
				if (g_aParticle[nCntParticle].fRadius <= 0)
				{// ���a���Ȃ��Ȃ�
					g_aParticle[nCntParticle].bUse = false;
				}
			}

			// ���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);

			// �F���̍X�V
			pVtx[0].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[1].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[2].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[3].col = D3DXCOLOR(g_aParticle[nCntParticle].col);

		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureParticle);

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �|���S���̕`��
	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̐������J��Ԃ�
		if (g_aParticle[nCntParticle].bUse == true)
		{// �p�[�e�B�N�����g�p����Ă���
		 // �e�N�X�`���̓ǂݍ���
			pDevice->SetTexture(0, g_pTextureParticle);

			// �p�[�e�B�N���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntParticle * 4,
				2);
		}
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̐������J��Ԃ�
	    // ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);

		// ���_�e�N�X�`��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}


//=============================================================================
// �G�t�F�N�g�ݒ�
//=============================================================================
void SetParticle(D3DXVECTOR3 pos,D3DXVECTOR3 move,D3DXCOLOR col, float fRadius, int nLife)
{
	// ���_���̍쐬
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̐������J��Ԃ�
		if (g_aParticle[nCntParticle].bUse == false)
		{// �p�[�e�B�N�����g�p����Ă��Ȃ�
			g_aParticle[nCntParticle].pos = pos;
			g_aParticle[nCntParticle].move = move;
			g_aParticle[nCntParticle].col = col;

			// �F���̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[1].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[2].col = D3DXCOLOR(g_aParticle[nCntParticle].col);
			pVtx[3].col = D3DXCOLOR(g_aParticle[nCntParticle].col);

			g_aParticle[nCntParticle].fRadius = fRadius;

			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);

			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}