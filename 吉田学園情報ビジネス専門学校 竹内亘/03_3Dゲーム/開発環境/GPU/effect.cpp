//=============================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : �|���j
//
//=============================================================================
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_EFFECT		"data/TEXTURE/effect000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	MAX_EFFECT			(4096)							// �G�t�F�N�g�̍ő吔
//#define EFFECT_SIZE			(5)							// �G�t�F�N�g�̃T�C�Y
#define EFFECT_POS			(0)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureEffect = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
EFFECT					g_aEffect[MAX_EFFECT];		// �G�t�F�N�g�̏��

//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for(int nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aEffect[nCntEffect].fRadius = 1.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;
	}

	// ���_���̍쐬
	MakeVertexEffect(pDevice);
}

//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void UninitEffect(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureEffect != NULL)
	{
		g_pTextureEffect->Release();
		g_pTextureEffect = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void UpdateEffect(void)
{
	int nCntEffect;

	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)	
		{// �G�t�F�N�g���g�p����Ă���

			g_aEffect[nCntEffect].nLife--;
			g_aEffect[nCntEffect].fRadius -= 0.5f;

			if (g_aEffect[nCntEffect].nLife <= 0)
			{// ��莞�Ԍo��
				if (g_aEffect[nCntEffect].fRadius <= 0)
				{// ���a���Ȃ��Ȃ�
					g_aEffect[nCntEffect].bUse = false;
				}
			}
		}
		pVtx[0].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius,0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);


		//pVtx[0].pos = D3DXVECTOR3(-EFFECT_POS, EFFECT_POS, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(EFFECT_POS, EFFECT_POS, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(-EFFECT_POS, 0.0f, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(EFFECT_POS, 0.0f, 0.0f);

		pVtx += 4;	//���_�f�[�^���S���i�߂�
	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void DrawEffect(void)
{
	int nCntEffect;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxView, mtxTrans;				// �v�Z�p�}�g���b�N�X

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aEffect[nCntEffect].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aEffect[nCntEffect].mtxWorld._11 = mtxView._11;
		g_aEffect[nCntEffect].mtxWorld._12 = mtxView._21;
		g_aEffect[nCntEffect].mtxWorld._13 = mtxView._31;
		g_aEffect[nCntEffect].mtxWorld._21 = mtxView._12;
		g_aEffect[nCntEffect].mtxWorld._22 = mtxView._22;
		g_aEffect[nCntEffect].mtxWorld._23 = mtxView._32;
		g_aEffect[nCntEffect].mtxWorld._31 = mtxView._13;
		g_aEffect[nCntEffect].mtxWorld._32 = mtxView._23;
		g_aEffect[nCntEffect].mtxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);
		D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

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
		pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);


		if (g_aEffect[nCntEffect].bUse == true)	// �������g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntEffect,
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
void MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT, &g_pTextureEffect);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_EFFECT,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	// ���_�o�b�t�@�̏���ݒ�
	int nCntEffect;

	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		//pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - EFFECT_SIZE, g_aEffect[nCntEffect].pos.y - EFFECT_SIZE, 0.0f);
		//pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + EFFECT_SIZE, g_aEffect[nCntEffect].pos.y - EFFECT_SIZE, 0.0f);
		//pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - EFFECT_SIZE, g_aEffect[nCntEffect].pos.y + EFFECT_SIZE, 0.0f);
		//pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + EFFECT_SIZE, g_aEffect[nCntEffect].pos.y + EFFECT_SIZE, 0.0f);

		pVtx[0].pos = D3DXVECTOR3(-EFFECT_POS, EFFECT_POS, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(EFFECT_POS, EFFECT_POS, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-EFFECT_POS, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(EFFECT_POS, 0.0f, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(0.0f, 0.3f, 0.7f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.3f, 0.7f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.3f, 0.7f, 0.5f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.3f, 0.7f, 0.5f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=============================================================================
// �G�t�F�N�g�ݒ�
//=============================================================================
void SetEffect(D3DXVECTOR3 pos,float fRadius, int nLife)
{
	int nCntEffect;
	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)		//�G�t�F�N�g���g�p����Ă��Ȃ�
		{
			g_aEffect[nCntEffect].pos = pos;
			//g_aEffect[nCntEffect].col = col;
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;			//�g�p���Ă�����
			break;
		}
		pVtx += 4;	//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}
