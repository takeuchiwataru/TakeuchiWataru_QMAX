//=========================================================================================================================
// 
// �G�t�F�N�g���� [effect.cpp]
// Author : Yamashita
// 
//=========================================================================================================================

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "effect.h"		// �G�t�F�N�g
#include "input.h"		// �G�t�F�N�g

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define	MAX_EFFECT					(10000)									// �G�t�F�N�g�̍ő吔
#define	MAX_EFFECTSMOKE				(50)									// �G�t�F�N�g�̍ő吔(��)
#define	MAX_EFFECTRAIN				(500)									// �G�t�F�N�g�̍ő吔�i�J�j
#define	MAX_EFFECTMAGIC				(500)									// �G�t�F�N�g�̍ő吔�i�J�j
#define	MAX_EFFECTEMOTION			(50)									// �G�t�F�N�g�̍ő吔�i�J�j

#define	TEXTURE_EFFECT_NAME		"data/TEXTURE/effect000.jpg"				// �ǂݍ��ރe�N�X�`���t�@�C���� /����
#define	TEXTURE_EFFECT_NAME1	"data/TEXTURE/flower.png"		// �ǂݍ��ރe�N�X�`���t�@�C���� /��
#define	TEXTURE_EFFECT_NAME2	"data/TEXTURE/Angry.png"					// �ǂݍ��ރe�N�X�`���t�@�C���� /�{��

#define MAX_TEX						(3)

//*************************************************************************************************************************
// �O���[�o���ϐ�
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9				g_pTextureEffect[MAX_TEX] = {};				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9			g_pVtxBuffEffect = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
EFFECT							g_aEffect[MAX_EFFECT];						// �G�t�F�N�g�̏��
int								g_nCntEffectState;							// ��ԃJ�E���^

//=========================================================================================================================
// �G�t�F�N�g����������
//=========================================================================================================================
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���擾
	int nCntEffect;		// �G�t�F�N�g�J�E���^
//	float fData;
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G�t�F�N�g���S�l
	
		
		g_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G�t�F�N�g���S�l

		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G�t�F�N�g�ړ��l
		//g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �G�t�F�N�g�F
		g_aEffect[nCntEffect].Type = EFFECTTYPE_NONE;						// �G�t�F�N�g���
		g_aEffect[nCntEffect].nTypeTx;
		

		g_aEffect[nCntEffect].fRadius = 0.0f;								// �G�t�F�N�g���a
		g_aEffect[nCntEffect].nLife = 0;									// �G�t�F�N�g����
		g_aEffect[nCntEffect].bUse = false;									// �G�t�F�N�g�g�p���Ă��Ȃ����

		g_nCntEffectState = 0;			// ��Ԃ�������

	}
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,TEXTURE_EFFECT_NAME,&g_pTextureEffect[0]);

	// �e�N�X�`���̓ǂݍ���(��)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT_NAME1, &g_pTextureEffect[1]);

	// �e�N�X�`���̓ǂݍ���(��)
	D3DXCreateTextureFromFile(pDevice, TEXTURE_EFFECT_NAME2, &g_pTextureEffect[2]);

	
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer
	(sizeof(VERTEX_3D) * 4 * MAX_EFFECT, D3DUSAGE_WRITEONLY , FVF_VERTEX_3D , D3DPOOL_MANAGED , &g_pVtxBuffEffect , NULL);
	// ���_���̍쐬
	VERTEX_3D *pVtx;
	
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);


	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g

		// ���_�ݒ�
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0.0f);

		//�@���x�N�g��
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���_�J���[�ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`���ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);

		pVtx += 4;	// ���_�f�[�^�̃|�C���^���S���i�߂�
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
// �G�t�F�N�g�I������
//=========================================================================================================================
void UninitEffect(void)
{
	for (int nCnt = 0; nCnt < MAX_TEX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (g_pTextureEffect[nCnt] != NULL)
		{
			g_pTextureEffect[nCnt]->Release();
			g_pTextureEffect[nCnt] = NULL;
		}
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//=========================================================================================================================
// �G�t�F�N�g�X�V����
//=========================================================================================================================
void UpdateEffect(void)
{
	int nCntEffect;			// �G�t�F�N�g�J�E���^

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g�p����Ă���ꍇ
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_BULLET)
			{// �e�G�t�F�N�g�̏ꍇ
				// g_aEffect[nCntEffect].nLife--;
				g_aEffect[nCntEffect].fRadius -= 0.2f;

				if (/*g_aEffect[nCntEffect].nLife <= 0 || */g_aEffect[nCntEffect].fRadius <= 0)
				{// ���C�t��0�ȉ��̏ꍇ
					g_aEffect[nCntEffect].bUse = false;
				}
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION || g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{// �����G�t�F�N�g�̏ꍇ
				g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	// �ړ��l���

				g_aEffect[nCntEffect].nLife--;				// ��������
			
				// ���a����
				if (g_aEffect[nCntEffect].nLife > 0) 
				{
					g_aEffect[nCntEffect].fRadius += 0.005f;
				}
				else
				{
					g_aEffect[nCntEffect].fRadius -= 0.5f;	
				}

				if (g_aEffect[nCntEffect].fRadius <= 0)
				{// ���C�t��0�ȉ��̏ꍇ
					g_aEffect[nCntEffect].bUse = false;
				}
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONRAIN)
			{// �����G�t�F�N�g�̏ꍇ
				g_aEffect[nCntEffect].pos -= g_aEffect[nCntEffect].move;	// �ړ��l���

				g_aEffect[nCntEffect].nLife++;				// ��������

				// ���a����
				if (g_aEffect[nCntEffect].nLife > 0)
				{
					g_aEffect[nCntEffect].fRadius -= 0.005f;
				}
				else
				{
					g_aEffect[nCntEffect].fRadius -= 0.5f;
				}

				if (g_aEffect[nCntEffect].nLife > 100)
				{// ���C�t��0�ȉ��̏ꍇ
					g_aEffect[nCntEffect].move.x = false;
					g_aEffect[nCntEffect].move.y = false;
					g_aEffect[nCntEffect].move.z = false;
				}
				if (g_aEffect[nCntEffect].nLife > 150)
				{
					/*g_aEffect[nCntEffect].rot.x += 1;
					g_aEffect[nCntEffect].rot.y += 1;
					g_aEffect[nCntEffect].rot.z += 1;*/
					//�d��
					/*g_aEffect[nCntEffect].move.y += 1;
					g_aEffect[nCntEffect].move.y -= (0.0f - g_aEffect[nCntEffect].move.y) * 0.5f;
					g_aEffect[nCntEffect].pos.y -= g_aEffect[nCntEffect].move.y; */

					//���S�Ɍ������Ă���
					g_aEffect[nCntEffect].move.x -= sinf(atan2f(g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.x)) * 1.0f;
					g_aEffect[nCntEffect].move.y -= cosf(atan2f(g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.x)) * 1.0f;

				}
				if (g_aEffect[nCntEffect].nLife == 300)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
				
			}	
			
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONHAPPY || 
				g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONUSUALLY || 
				g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONANGRY)
			{// �����G�t�F�N�g�̏ꍇ
				g_aEffect[nCntEffect].pos -= g_aEffect[nCntEffect].move;	// �ړ��l���

				g_aEffect[nCntEffect].nLife--;				// ��������
				//g_aEffect[nCntEffect].rot.z += 0.02f;
				
				// ���a����
				if (g_aEffect[nCntEffect].nLife > 0)
				{
					g_aEffect[nCntEffect].fRadius += 0.005f;
				}
				else
				{
					g_aEffect[nCntEffect].fRadius -= 0.2f;
				}
				

				if (g_aEffect[nCntEffect].fRadius <= 0)
				{// ���C�t��0�ȉ��̏ꍇ
					g_aEffect[nCntEffect].bUse = false;
				}
			}

			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONRIPPLE)
			{// �����G�t�F�N�g�̏ꍇ
				g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	// �ړ��l���

				g_aEffect[nCntEffect].nLife--;				// ��������
				//g_aEffect[nCntEffect].nor = g_aEffect[nCntEffect].move;
				//g_aEffect[nCntEffect].rot.z += 0.02f;

				// ���a����
				if (g_aEffect[nCntEffect].nLife > 0)
				{
					g_aEffect[nCntEffect].fRadius += 0.005f;
				}
				else
				{
					g_aEffect[nCntEffect].fRadius += 0.5f;
				}


				if (g_aEffect[nCntEffect].fRadius <= 40)
				{// ���C�t��0�ȉ��̏ꍇ
					g_aEffect[nCntEffect].bUse = false;
				}
			}

			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONSAD)
			{// �߂����G�t�F�N�g�̏ꍇ
				//g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	// �ړ��l���

				//g_aEffect[nCntEffect].nLife++;				// ��������
															//g_aEffect[nCntEffect].nor = g_aEffect[nCntEffect].move;
				g_aEffect[nCntEffect].rot.z += 0.1f;

															// ���a����
				/*if (g_aEffect[nCntEffect].nLife > 0)
				{
					g_aEffect[nCntEffect].fRadius ;
				}
				else
				{
					g_aEffect[nCntEffect].fRadius;
				}*/

				//if (g_aEffect[nCntEffect].nLife > 60)
				{// ���C�t��0�ȉ��̏ꍇ
					/*g_aEffect[nCntEffect].move.x = false;
					g_aEffect[nCntEffect].move.y = false;
					g_aEffect[nCntEffect].move.z = false;*/
				}

				//if (g_aEffect[nCntEffect].nLife == 75)
				{// ���C�t��0�ȉ��̏ꍇ
					//g_aEffect[nCntEffect].bUse = false;
				}
			}
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONSTAMP)
			{// �X�^���v
			// g_aEffect[nCntEffect].pos.z += g_aEffect[nCntEffect].move.z;	// �ړ��l���
			// g_aEffect[nCntEffect].move.y -= 0.05;

			 g_aEffect[nCntEffect].nLife++;				// ��������
			 g_aEffect[nCntEffect].col.a += 0.02f;		//�����x	

				// ���a����
				
				
			 if (g_aEffect[nCntEffect].nLife < 2)
			 {
				// g_aEffect[nCntEffect].move.z += 10.0f;
				 g_aEffect[nCntEffect].fRadius -= 1.0f;

			 }
				if (g_aEffect[nCntEffect].nLife > 60)
				{// ���C�t��0�ȉ��̏ꍇ
				 g_aEffect[nCntEffect].move.z = false;
				}

				if (g_aEffect[nCntEffect].nLife == 75)
				{// ���C�t��0�ȉ��̏ꍇ
				 g_aEffect[nCntEffect].bUse = false;
				}
			}
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONWATER)
			{// �����G�t�F�N�g�̏ꍇ
				g_aEffect[nCntEffect].move.y -= 0.05f;

				g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	// �ړ��l���

				g_aEffect[nCntEffect].nLife++;				// ��������

															// ���a����
				if (g_aEffect[nCntEffect].nLife > 0)
				{
					g_aEffect[nCntEffect].fRadius += 0.005f;
				}
				else
				{
					g_aEffect[nCntEffect].fRadius -= 0.5f;
				}
				if (g_aEffect[nCntEffect].nLife > 30)
				{// ���C�t��0�ȉ��̏ꍇ
					//SetRainEffect(D3DXVECTOR3(0, 0, 100), EFFECTTYPE_RESURRECTIONWATER, 1, 10, 0, 2);	//��:���a�FHP�F�e�N�X�`���ԍ�
				}
				if (g_aEffect[nCntEffect].nLife > 100)
				{// ���C�t��0�ȉ��̏ꍇ
					
					//g_aEffect[nCntEffect].rot += g_aEffect[nCntEffect].pos;	// �ړ��l���

					g_aEffect[nCntEffect].bUse = false;

					//SetRainEffect(D3DXVECTOR3(0, 0, 100), EFFECTTYPE_RESURRECTIONWATER, 5, 10, 20, 2);	//��:���a�FHP�F�e�N�X�`���ԍ�
				}
			}
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONWATER_1)
			{// �����G�t�F�N�g�̏ꍇ
				g_aEffect[nCntEffect].move.y += 0.002f;	// �ړ��l���
				g_aEffect[nCntEffect].pos += g_aEffect[nCntEffect].move;	// �ړ��l���

				g_aEffect[nCntEffect].nLife++;				// ��������

				// ���a����
				if (g_aEffect[nCntEffect].nLife > 20)
				{
					g_aEffect[nCntEffect].fRadius -= 0.4f;
				}

				if (g_aEffect[nCntEffect].fRadius < 0.0f)
				{// 
					g_aEffect[nCntEffect].bUse = false;
				}
			}
		}
		// ���_�ݒ�
		pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius,g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius,  -g_aEffect[nCntEffect].fRadius, 0.0f);

		// ���_�ݒ�
		pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
		pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
		pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
		pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;
	}
	
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
// �G�t�F�N�g�`�揈��
//=========================================================================================================================
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X���擾
	int nCntEffect;		// �G�t�F�N�g�J�E���^

	D3DXMATRIX mtxRot, mtxTrans, mtxView;		//�v�Z�p�}�g���b�N�X
	//LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�ւ̃|�C���^

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
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

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEffect[nCntEffect].rot.y, g_aEffect[nCntEffect].rot.x, g_aEffect[nCntEffect].rot.z);

			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxRot);						//�ۑ�

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEffect[nCntEffect].pos.x, g_aEffect[nCntEffect].pos.y, g_aEffect[nCntEffect].pos.z);

			D3DXMatrixMultiply(&g_aEffect[nCntEffect].mtxWorld, &g_aEffect[nCntEffect].mtxWorld, &mtxTrans);						//�ۑ�

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aEffect[nCntEffect].mtxWorld);

			//�A���t�@�e�X�g
			/*pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ALPHAREF, 0);						//��l
			pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);		//��r���@�i���傫���j�j
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DCMP_ALWAYS);		//��r���@�i���傫���j�j*/
			//pDevice->SetRenderState(D3DRS_ZENABLE, true);

			//�f�t�H���g�̏ꍇFALSE�ɂȂ��Ă��邩��TRUE�ɂ���
			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);		//��r���@�i���傫���j�j
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION || g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONWATER || g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONWATER_1)
			{
				// ���u�����f�B���O�����Z�����ɐݒ�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			}

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);


			// �|���S���̕`��

			// �G�t�F�N�g���g�p����Ă���ꍇ
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureEffect[g_aEffect[nCntEffect].nTypeTx]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEffect * 4, 2);


			//�A���t�@�l��߂�
			//->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			//pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

			//�f�t�H���g�̏ꍇFALSE�ɂȂ��Ă��邩��TRUE�ɂ���c





			pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);		//��r���@�i���傫���j�j
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION || g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONWATER || g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONWATER_1)
			{
				// ���u�����f�B���O�����ɖ߂�
				pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
				pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			}
		}
	}
}

//=========================================================================================================================
// �e�G�t�F�N�g�ݒ菈��
//=========================================================================================================================
void SetBulletEffect(D3DXVECTOR3 pos, D3DXCOLOR col, EFFECTTYPE Type, float fRadius, int nLife, int nTypeTx)
{
	int nCntEffect;			// �G�t�F�N�g�J�E���^

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == false)
		{// �G�t�F�N�g���g�p����Ă��Ȃ�
			
			g_aEffect[nCntEffect].pos = pos;			// pos�l���
			g_aEffect[nCntEffect].col = col;			// col�l���
			g_aEffect[nCntEffect].Type = Type;			// ��ސݒ�
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;			// ��ސݒ�

			g_aEffect[nCntEffect].fRadius = fRadius;	// ���a�ݒ�
			g_aEffect[nCntEffect].nLife = nLife;		// �����ݒ�
			g_aEffect[nCntEffect].bUse = true;			// �g�p���Ă�����

			// ���_�ݒ�
			/*pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);*/
			// ���_�J���[�ݒ�
			pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

			////�@���x�N�g��
			//pVtx[nCntEffect * 4].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			//pVtx[nCntEffect * 4 + 1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			//pVtx[nCntEffect * 4 + 2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			//pVtx[nCntEffect * 4 + 3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			break;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
// �p�[�e�B�N���G�t�F�N�g�ݒ菈��
//=========================================================================================================================
void SetParticleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife ,int nTypeTx)
{
	int nCntEffect;			// �G�t�F�N�g�J�E���^
	int nCount = 0;			// �G�t�F�N�g���J�E���^

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == false)
		{// �G�t�F�N�g���g�p����Ă��Ȃ�
			
			g_aEffect[nCntEffect].pos = pos;			// pos�l���
			g_aEffect[nCntEffect].Type = Type;			// ��ސݒ�
			g_aEffect[nCntEffect].nLife = nLife;		// �����ݒ�
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;			// ��ސݒ�

			g_aEffect[nCntEffect].bUse = true;			// �g�p���Ă�����

			// �ړ������_����
			g_aEffect[nCntEffect].move.x = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			//g_aEffect[nCntEffect].move.z = tanf((rand() % 628) / 100.0f) * ((rand() % 3) + 1);

			int nNumber = rand() % 3 + 1;

			// col�l���
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.7f, 0.9f, 0.0f, 0.7f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.6f, 0.8f, 0.0f, 0.6f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.5f, 0.7f, 0.0f, 0.5f); }
			}

			g_aEffect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	// ���a�ݒ�

			// ���_�ݒ�
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius,  -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

			nCount++;		// �����J�E���g
			if (nCount == nSetMax)
			{// �����ő吔�ɂȂ����ꍇ
				break;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
// �p�[�e�B�N���G�t�F�N�g�ݒ菈��
//=========================================================================================================================
void SetSmokeEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx)
{
	int nCntEffect;			// �G�t�F�N�g�J�E���^ 
	int nCount = 0;			// �G�t�F�N�g���J�E���^

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

							// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == false)
		{// �G�t�F�N�g���g�p����Ă��Ȃ�
			
			g_aEffect[nCntEffect].pos = pos;			// pos�l���
			g_aEffect[nCntEffect].Type = Type;			// ��ސݒ�
			g_aEffect[nCntEffect].nLife = nLife;		// �����ݒ�
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;	// ��ސݒ�

			g_aEffect[nCntEffect].bUse = true;			// �g�p���Ă�����


			// �ړ������_����
			g_aEffect[nCntEffect].move.x = sinf((rand() % 25) / 700.0f) * ((rand() % 1) + 1);
			g_aEffect[nCntEffect].move.y = cosf((rand() % 100) / 100.0f)  * ((rand() % 1) + 1);
			g_aEffect[nCntEffect].rot.x = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			g_aEffect[nCntEffect].rot.y = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);

			/*g_aEffect[nCntEffect].move.x = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 100.0f)  * ((rand() % 1) + 1);*/
			//g_aEffect[nCntEffect].move.z = tanf((rand() % 628) / 100.0f) * ((rand() % 3) + 1);

			int nNumber = rand() % 3 + 1;

			// col�l���
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONRAIN)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}

			g_aEffect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	// ���a�ݒ�

			// ���_�ݒ�
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

			nCount++;		// �����J�E���g
			if (nCount == nSetMax)
			{// �����ő吔�ɂȂ����ꍇ
				//g_aEffect[nCntEffect].bUse = false;
				nSetMax = 0;
				break;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
// �p�[�e�B�N���G�t�F�N�g�ݒ菈��
//=========================================================================================================================
void SetRainEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx)
{
		int nCntEffect;			// �G�t�F�N�g�J�E���^
		int nCount = 0;			// �G�t�F�N�g���J�E���^

		VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

								// ���_�o�b�t�@�����b�N
		g_pVtxBuffEffect->Lock
		(
			0,
			0,
			(void**)&pVtx,
			0
		);

		for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
		{// �G�t�F�N�g���J�E���g
			if (g_aEffect[nCntEffect].bUse == false)
			{// �G�t�F�N�g���g�p����Ă��Ȃ�

				g_aEffect[nCntEffect].pos = pos;			// pos�l���
				g_aEffect[nCntEffect].Type = Type;			// ��ސݒ�
				g_aEffect[nCntEffect].nLife = nLife;		// �����ݒ�
				g_aEffect[nCntEffect].nTypeTx = nTypeTx;			// ��ސݒ�

				g_aEffect[nCntEffect].bUse = true;			// �g�p���Ă�����
				//g_aEffect[nCntEffect].move.y += 500.0f;

				if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONRAIN)
				{
					// �ړ������_����											
					g_aEffect[nCntEffect].move.x = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
					g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 100.0f)  * ((rand() % 1) + 1);
					g_aEffect[nCntEffect].move.z = cosf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);

					/*g_aEffect[nCntEffect].rot.y = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
					g_aEffect[nCntEffect].rot.x = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
					g_aEffect[nCntEffect].rot.z = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);*/
				}
				if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONWATER || g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONWATER_1)
				{
					// �ړ������_����											
					//g_aEffect[nCntEffect].move.x = sinf((rand() % 25) / 700.0f) * ((rand() % 1) + 1);
					g_aEffect[nCntEffect].move.x = sinf((rand() % 500) / 100.0f) * 0.8f;
					g_aEffect[nCntEffect].move.y = cosf((rand() % 100) / 100.0f)  * 3.0f;
					g_aEffect[nCntEffect].move.z = sinf((rand() % 500) / 100.0f) * 0.8f;
				}
				int nNumber = rand() % 3 + 1;

				// col�l���
				if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
				{
					if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.8f); }
					if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f); }
					if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.3f); }
				}
				else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
				{
					if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f); }
					if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f); }
					if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f); }
				}
				else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONRAIN)
				{
					if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f); }
					if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f); }
					if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f); }
				}
				else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONWATER)
				{
					if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.7f, 0.8f, 0.7f); }
					if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.7f, 0.8f, 0.5f); }
					if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.7f, 0.8f, 0.3f); }
				}
				else
				{
					if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
					if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
					if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				}

				g_aEffect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	// ���a�ݒ�

				// ���_�ݒ�
				pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
				pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);

				// ���_�J���[�ݒ�
				pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
				pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
				pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
				pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

				nCount++;		// �����J�E���g
				if (nCount == nSetMax)
				{// �����ő吔�ɂȂ����ꍇ
					nSetMax = 0;
					break;
				}
			}
		}
		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
// �p�[�e�B�N���G�t�F�N�g�ݒ菈��
//=========================================================================================================================
void SetMagicEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx)
{
	int nCntEffect;			// �G�t�F�N�g�J�E���^
	int nCount = 0;			// �G�t�F�N�g���J�E���^

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

							// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == false)
		{// �G�t�F�N�g���g�p����Ă��Ȃ�R

			g_aEffect[nCntEffect].pos = pos;			// pos�l���
			g_aEffect[nCntEffect].Type = Type;			// ��ސݒ�
			g_aEffect[nCntEffect].nLife = nLife;		// �����ݒ�
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;			// ��ސݒ�

			g_aEffect[nCntEffect].bUse = true;			// �g�p���Ă�����

														// �ړ������_����											
			 g_aEffect[nCntEffect].move.x = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			 g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			 g_aEffect[nCntEffect].move.z = cosf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);

			 g_aEffect[nCntEffect].rot.y = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			 g_aEffect[nCntEffect].rot.x = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			 g_aEffect[nCntEffect].rot.z = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);

			// g_aEffect[nCntEffect].move.z = cosf((rand() % 100) / 100.0f) * ((rand() % 1) + 1);

			int nNumber = rand() % 3 + 1;

			// col�l���
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.7f, 1.0f, 0.0f, 0.7f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.7f, 1.0f, 0.0f, 0.6f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.7f, 1.0f, 0.0f, 0.5f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONRAIN)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f); }
			}

			g_aEffect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	// ���a�ݒ�

																			// ���_�ݒ�
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

			nCount++;		// �����J�E���g
			if (nCount == nSetMax)
			{// �����ő吔�ɂȂ����ꍇ
				//g_aEffect[nCntEffect].bUse = false;
				nSetMax = 0;
				break;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
// ����p�[�e�B�N���G�t�F�N�g�ݒ菈��
//=========================================================================================================================
void SetEmotionEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx)		// ����G�t�F�N�g�ݒ菈��
{
	int nCntEffect;			// �G�t�F�N�g�J�E���^
	int nCount = 0;			// �G�t�F�N�g���J�E���^

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

							// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == false)
		{// �G�t�F�N�g���g�p����Ă��Ȃ�

			g_aEffect[nCntEffect].pos = pos;			// pos�l���
			g_aEffect[nCntEffect].Type = Type;			// ��ސݒ�
			g_aEffect[nCntEffect].nLife = nLife;		// �����ݒ�
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;			// ��ސݒ�
			


			g_aEffect[nCntEffect].bUse = true;			// �g�p���Ă�����

			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONHAPPY)
			{
				// �ړ������_����											
				g_aEffect[nCntEffect].move.x = sinf((rand() % 628) / 100.0f) * 0.5f;
				g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 100.0f)  * 0.5f;

				//g_aEffect[nCntEffect].move.z = cosf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONUSUALLY)
			{
				// �ړ������_����											
				g_aEffect[nCntEffect].move.x = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
				g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 100.0f)  * ((rand() % 1) + 1);
				//g_aEffect[nCntEffect].move.z = cosf((rand() % 500) / 100.0f) * ((rand() % 1) + 1);
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONSAD)
			{
				// �ړ������_����											
				//g_aEffect[nCntEffect].move.x = sinf((rand() % 100) / 10.0f) * ((rand() % 1) + 0.5f);
				//g_aEffect[nCntEffect].move.y = cosf((rand() % 100) / 200.0f)  * ((rand() % 1) + 0.5f);
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONANGRY)
			{
				// �ړ������_����											
				g_aEffect[nCntEffect].move.x = sinf((rand() % 628) / 100.0f) * 0.7f;
				g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 100.0f)  * 0.7f;
				//g_aEffect[nCntEffect].rot.z = cosf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONSTAMP)
			{
				// �ړ������_����											
				//g_aEffect[nCntEffect].move.z = 1;

				//g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 100.0f)  * 0.7f;
				//g_aEffect[nCntEffect].rot.z = cosf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			}
			//g_aEffect[nCntEffect].rot.y = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			//g_aEffect[nCntEffect].rot.x = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			//g_aEffect[nCntEffect].rot.z = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);

			int nNumber = rand() % 3 + 1;

			// col�l���
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.7f, 0.9f, 0.0f, 0.7f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.6f, 0.8f, 0.0f, 0.6f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.5f, 0.7f, 0.0f, 0.5f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONHAPPY)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 1.0f, 0.3f, 1.0f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONSAD)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONANGRY)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONSTAMP)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f); }
			}

			g_aEffect[nCntEffect].fRadius = (7) * 2.0f;	// ���a�ݒ�

																			// ���_�ݒ�
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

			nCount++;		// �����J�E���g
			if (nCount == nSetMax)
			{// �����ő吔�ɂȂ����ꍇ
				nSetMax = 0;
				break;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
// �g��p�[�e�B�N���G�t�F�N�g�ݒ菈��
//=========================================================================================================================
void SetRippleEffect(D3DXVECTOR3 pos, EFFECTTYPE Type, int nSetMax, int nRadius, int nLife, int nTypeTx)
{
	int nCntEffect;			// �G�t�F�N�g�J�E���^
	int nCount = 0;			// �G�t�F�N�g���J�E���^

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

							// ���_�o�b�t�@�����b�N
	g_pVtxBuffEffect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == false)
		{// �G�t�F�N�g���g�p����Ă��Ȃ�

			g_aEffect[nCntEffect].pos = pos;			// pos�l���
			g_aEffect[nCntEffect].Type = Type;			// ��ސݒ�
			g_aEffect[nCntEffect].nLife = nLife;		// �����ݒ�
			g_aEffect[nCntEffect].nTypeTx = nTypeTx;	// ��ސݒ�

			g_aEffect[nCntEffect].bUse = true;			// �g�p���Ă�����

			// �ړ������_����											
			g_aEffect[nCntEffect].move.x = sinf((rand() % 628) / 1.0f) * 0.1f;
			g_aEffect[nCntEffect].move.y = cosf((rand() % 628) / 1.0f)  * 0.1f;


			//g_aEffect[nCntEffect].rot.y = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			//g_aEffect[nCntEffect].rot.x = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);
			//g_aEffect[nCntEffect].rot.z = sinf((rand() % 628) / 100.0f) * ((rand() % 1) + 1);

			int nNumber = rand() % 3 + 1;

			// col�l���
			if (g_aEffect[nCntEffect].Type == EFFECTTYPE_EXPLOSION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 0.8f, 0.0f, 0.5f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTION)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.7f, 0.9f, 0.0f, 0.7f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.6f, 0.8f, 0.0f, 0.6f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.5f, 0.7f, 0.0f, 0.5f); }
			}
			else if (g_aEffect[nCntEffect].Type == EFFECTTYPE_RESURRECTIONRIPPLE)
			{
				if (nNumber == 1) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 2) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f); }
				if (nNumber == 3) { g_aEffect[nCntEffect].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f); }
			}


			g_aEffect[nCntEffect].fRadius = (rand() % nRadius + 1) * 1.0f;	// ���a�ݒ�

			// ���_�ݒ�
			pVtx[nCntEffect * 4].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, -g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 2].pos = D3DXVECTOR3(-g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[nCntEffect * 4 + 3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].fRadius, 0.0f);

			// ���_�J���[�ݒ�
			pVtx[nCntEffect * 4].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 1].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 2].col = g_aEffect[nCntEffect].col;
			pVtx[nCntEffect * 4 + 3].col = g_aEffect[nCntEffect].col;

			nCount++;		// �����J�E���g
			if (nCount == nSetMax)
			{// �����ő吔�ɂȂ����ꍇ
				//nSetMax = 0;
				break;
			}
		}
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffEffect->Unlock();
}

//=========================================================================================================================
// �G�t�F�N�g�j������
//=========================================================================================================================
void DeleteEffect(void)
{
	int nCntEffect;			// �G�t�F�N�g�J�E���^

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{// �G�t�F�N�g���J�E���g
		if (g_aEffect[nCntEffect].bUse == true)
		{// �G�t�F�N�g���g�p����Ă��Ȃ�
			g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G�t�F�N�g���S�l
			g_aEffect[nCntEffect].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G�t�F�N�g���S�l
			g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �G�t�F�N�g�ړ��l																				
			//g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �G�t�F�N�g�F
			g_aEffect[nCntEffect].Type = EFFECTTYPE_NONE;						// �G�t�F�N�g���
			g_aEffect[nCntEffect].nTypeTx;
			g_aEffect[nCntEffect].fRadius = 0.0f;								// �G�t�F�N�g���a
			g_aEffect[nCntEffect].nLife = 0;									// �G�t�F�N�g����
			g_aEffect[nCntEffect].bUse = false;									// �G�t�F�N�g�g�p���Ă��Ȃ����
		}
	}
	
	g_nCntEffectState = 0;			// ��Ԃ�������
}