//=============================================================================
//
// �p�[�e�B�N���̏��� [particle.cpp]
// Author : �|���j
//
//=============================================================================
#include "particle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_PARTICLE	  "data/TEXTURE/effect000.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define PARTICLE_SIZE  (20)										// �|���S���̃T�C�Y
#define	MAX_PARTICLE		  (4096)							// �p�[�e�B�N���̍ő吔

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
	D3DXCreateTextureFromFile(pDevice,TEXTURE_PARTICLE,&g_pTextureParticle);

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
	VERTEX_3D *pVtx;
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
			pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);

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
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxView, mtxTrans;				// �v�Z�p�}�g���b�N�X

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aParticle[nCntParticle].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aParticle[nCntParticle].mtxWorld._11 = mtxView._11;
		g_aParticle[nCntParticle].mtxWorld._12 = mtxView._21;
		g_aParticle[nCntParticle].mtxWorld._13 = mtxView._31;
		g_aParticle[nCntParticle].mtxWorld._21 = mtxView._12;
		g_aParticle[nCntParticle].mtxWorld._22 = mtxView._22;
		g_aParticle[nCntParticle].mtxWorld._23 = mtxView._32;
		g_aParticle[nCntParticle].mtxWorld._31 = mtxView._13;
		g_aParticle[nCntParticle].mtxWorld._32 = mtxView._23;
		g_aParticle[nCntParticle].mtxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aParticle[nCntParticle].pos.x, g_aParticle[nCntParticle].pos.y, g_aParticle[nCntParticle].pos.z);
		D3DXMatrixMultiply(&g_aParticle[nCntParticle].mtxWorld, &g_aParticle[nCntParticle].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aParticle[nCntParticle].mtxWorld);

		// �A���t�@�e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);


		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		if (g_aParticle[nCntParticle].bUse == true)	// �p�[�e�B�N�����g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureParticle);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntParticle,
				2);
		}

		// �A���t�@�e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		// ���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_���̍쐬
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̐������J��Ԃ�
	 //   // ���_���W
		//pVtx[0].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
		//pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
		//pVtx[2].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x - g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);
		//pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].pos.x + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.y + g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].pos.z);

		pVtx[0].pos = D3DXVECTOR3(-PARTICLE_SIZE, PARTICLE_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PARTICLE_SIZE, PARTICLE_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-PARTICLE_SIZE, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PARTICLE_SIZE, 0.0f, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	VERTEX_3D *pVtx;
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

			g_aParticle[nCntParticle].nLife = nLife;
			g_aParticle[nCntParticle].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}