//=============================================================================
//
// �p�[�e�B�N���̏��� [particl.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "particle.h"
#include "camera.h"
#include "shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PARTICLE_TEXTURE_NAME   "data/TEXTURE/effect000.jpg"     // �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureParticle = NULL;  // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffParticle = NULL;  // ���_�o�b�t�@�ւ̃|�C���^
Particle                g_aParticle[MAX_PARTICLE];  // �p�[�e�B�N���̏��

//=============================================================================
// ����������
//=============================================================================
void InitParticle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// ���_���̍쐬
	MakeVertexParticle(pDevice);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̑������J��Ԃ�
		g_aParticle[nCntParticle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // �ʒu��������
		g_aParticle[nCntParticle].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);    // �ړ��ʂ�������
		g_aParticle[nCntParticle].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ������������
		g_aParticle[nCntParticle].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f); // �F��������
		g_aParticle[nCntParticle].fRadius = 0.0f;                          // ���a��������
		g_aParticle[nCntParticle].bUse = false;                            // �g�p���Ă��Ȃ���Ԃɂ���
		g_aParticle[nCntParticle].nIdxShadow = 0;                          // �e�̔ԍ���������
	}
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
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̑������J��Ԃ�
		if (g_aParticle[nCntParticle].bUse == true)
		{// �p�[�e�B�N�����g�p����Ă���
			g_aParticle[nCntParticle].pos += g_aParticle[nCntParticle].move; // �ʒu�X�V
			g_aParticle[nCntParticle].nLife--;          // ���������
			g_aParticle[nCntParticle].fRadius -= 0.01f; // ���a�����炷
			g_aParticle[nCntParticle].col.r -= 0.01f;   // �Ԃ����炷
			g_aParticle[nCntParticle].col.g -= 0.01f;   // �΂����炷
			g_aParticle[nCntParticle].col.b -= 0.01f;   // �����炷
			g_aParticle[nCntParticle].col.a -= 0.01f;   // �����x�����炷

			// �傫�����X�V
			pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);

			// ���_�J���[���X�V
			pVtx[0].col = g_aParticle[nCntParticle].col;
			pVtx[1].col = g_aParticle[nCntParticle].col;
			pVtx[2].col = g_aParticle[nCntParticle].col;
			pVtx[3].col = g_aParticle[nCntParticle].col;

			// �e�̈ʒu�X�V
			SetPositionShadow(g_aParticle[nCntParticle].nIdxShadow, D3DXVECTOR3(g_aParticle[nCntParticle].pos.x, 0.0f, g_aParticle[nCntParticle].pos.z));

			if (g_aParticle[nCntParticle].nLife <= 0 || g_aParticle[nCntParticle].fRadius <= 0 || g_aParticle[nCntParticle].col.a <= 0)
			{// �������Ȃ��Ȃ���
				g_aParticle[nCntParticle].bUse = false;              // �g�p���Ă��Ȃ���Ԃ�
				DeleteShadow(g_aParticle[nCntParticle].nIdxShadow);  // �e������
			}
		}
		pVtx += 4;   // �|�C���^��i�߂�
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
	D3DXMATRIX mtxView, mtxTrans;               // �v�Z�p�}�g���b�N�X

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE); // �[�x�o�b�t�@�̏������ݐݒ�𖳌���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);// ���ׂĕ`�悷��

	// �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);     // �L����
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);               // �����x��0
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER); // ���傫�����̂�`�悷��

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̑������J��Ԃ�
		if (g_aParticle[nCntParticle].bUse == true)
		{// �p�[�e�B�N�����g�p����Ă���
		    // ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aParticle[nCntParticle].mtxWorld);

			// �������J�����̐��ʂɐݒ�
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

			// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, g_pVtxBuffParticle, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureParticle);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntParticle * 4, NUM_POLYGON);
		}
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z�e�X�g�𖳌��ɂ���(�f�t�H���g�̒l��)
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);      // �[�x�o�b�t�@�ւ̏������݂�L����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL); // �ȉ��̂��̂�`�悷��
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexParticle(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_PARTICLE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffParticle,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		PARTICLE_TEXTURE_NAME,
		&g_pTextureParticle);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̑������J��Ԃ�
	    // ���_���W
		pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);

		// �@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[1].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[2].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);
		pVtx[3].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

		// ���_�J���[
		pVtx[0].col = g_aParticle[nCntParticle].col;
		pVtx[1].col = g_aParticle[nCntParticle].col;
		pVtx[2].col = g_aParticle[nCntParticle].col;
		pVtx[3].col = g_aParticle[nCntParticle].col;

		// �e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;   // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}
//=============================================================================
// �G�t�F�N�g�̐ݒ�
//=============================================================================
void SetParticle(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, float radius, int life)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffParticle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntParticle = 0; nCntParticle < MAX_PARTICLE; nCntParticle++)
	{// �p�[�e�B�N���̑������J��Ԃ�
		if (g_aParticle[nCntParticle].bUse == false)
		{// �p�[�e�B�N�����g�p����Ă��Ȃ�
			g_aParticle[nCntParticle].pos = pos;         // �ʒu��ݒ�
			g_aParticle[nCntParticle].move = move;       // �ړ��ʂ�ݒ�
			g_aParticle[nCntParticle].col = col;         // �F��ݒ�
			g_aParticle[nCntParticle].fRadius = radius;  // ���a��ݒ�
			g_aParticle[nCntParticle].nLife = life;      // ������ݒ�

			// �傫���ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(-g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aParticle[nCntParticle].fRadius, -g_aParticle[nCntParticle].fRadius, 0.0f);

			// �F�ݒ�
			pVtx[0].col = g_aParticle[nCntParticle].col;
			pVtx[1].col = g_aParticle[nCntParticle].col;
			pVtx[2].col = g_aParticle[nCntParticle].col;
			pVtx[3].col = g_aParticle[nCntParticle].col;

			g_aParticle[nCntParticle].nIdxShadow = SetShadow(D3DXVECTOR3(g_aParticle[nCntParticle].pos.x, 0.0f, g_aParticle[nCntParticle].pos.z), g_aParticle[nCntParticle].rot, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.05f), 5, 5); // �e�̔ԍ���ݒ�
			g_aParticle[nCntParticle].bUse = true;
			break;
		}
		pVtx += 4;  // �|�C���^��i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffParticle->Unlock();
}