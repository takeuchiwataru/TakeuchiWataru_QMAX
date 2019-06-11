//=============================================================================
//
// �e���� [shadow.cpp]
// Author : �������� Sato_Asumi
//
//=============================================================================
#include "shadow.h"
#include "game.h"
#include "xobject.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_NAME	"data\\TEXTURE\\shadow000.jpg"	//�ǂ݂��ރe�N�X�`���t�@�C����
#define MAX_SHADOW		(100)							//�e�̍ő吔
#define COLOR_A			(0.6f)							//�J���[�� a�l
#define CHANGE_COL		(0.0015f)						//�F�̕ω���

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL;	// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR2				g_texShadow;				//�e�N�X�`��
Shadow					g_shadow[MAX_SHADOW];		//�e�̏��

													//=============================================================================
													// ����������
													//=============================================================================
void InitShadow(void)
{
	//�ϐ��錾
	int nCntShadow;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

													// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTextureShadow);

	//���̏�����
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].Otherpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_shadow[nCntShadow].color.a = COLOR_A;
		g_shadow[nCntShadow].bUse = false;
		g_shadow[nCntShadow].fHight = 0.0f;
		g_shadow[nCntShadow].fWhidth = 0.0f;
		g_shadow[nCntShadow].fLength = 0.0f;
	}

	// ���_���̍쐬
	MakeVertexShadow(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	//�ϐ��錾
	int nCntShadow;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX		  mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

												// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_shadow[nCntShadow].mtxWorld);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_shadow[nCntShadow].rot.y, g_shadow[nCntShadow].rot.x, g_shadow[nCntShadow].rot.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_shadow[nCntShadow].pos.x, g_shadow[nCntShadow].pos.y, g_shadow[nCntShadow].pos.z);
			D3DXMatrixMultiply(&g_shadow[nCntShadow].mtxWorld, &g_shadow[nCntShadow].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_shadow[nCntShadow].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureShadow);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntShadow * 4,
				2);
		}
	}

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntShadow;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COLOR_A);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COLOR_A);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COLOR_A);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, COLOR_A);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fHight, float fWhidth)
{
	//�ϐ��錾
	int		nCntShadow;
	int		nNumShadow = 0;	//�e�̔ԍ��ۑ�
	float	fAngle;			//�p�x�̐ݒ�
	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == false)
		{
			g_shadow[nCntShadow].pos = pos;			//���W��ݒ�
			g_shadow[nCntShadow].fHight = fHight;	//������ݒ�
			g_shadow[nCntShadow].fWhidth = fWhidth;	//����ݒ�

													//�Ίp���̊p�x
			fAngle = (float)atan2(g_shadow[nCntShadow].fWhidth, g_shadow[nCntShadow].fHight);

			//�ӂ̒���
			g_shadow[nCntShadow].fLength = sqrtf((g_shadow[nCntShadow].fWhidth * g_shadow[nCntShadow].fWhidth) + (g_shadow[nCntShadow].fHight * g_shadow[nCntShadow].fHight));

			//���_�����߂�
			g_shadow[nCntShadow].Otherpos.x = sinf(fAngle) * g_shadow[nCntShadow].fLength;
			g_shadow[nCntShadow].Otherpos.z = cosf(fAngle) * g_shadow[nCntShadow].fLength;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-g_shadow[nCntShadow].Otherpos.x, 0.0f, g_shadow[nCntShadow].Otherpos.z);
			pVtx[1].pos = D3DXVECTOR3(g_shadow[nCntShadow].Otherpos.x, 0.0f, g_shadow[nCntShadow].Otherpos.z);
			pVtx[2].pos = D3DXVECTOR3(-g_shadow[nCntShadow].Otherpos.x, 0.0f, -g_shadow[nCntShadow].Otherpos.z);
			pVtx[3].pos = D3DXVECTOR3(g_shadow[nCntShadow].Otherpos.x, 0.0f, -g_shadow[nCntShadow].Otherpos.z);

			g_shadow[nCntShadow].bUse = true;		//�g�p���Ă����Ԃɂ���
			nNumShadow = nCntShadow;				//�e�̔ԍ��ۑ�
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();

	return nNumShadow;
}

//=============================================================================
// �e�̈ʒu��ݒ�
//=============================================================================
void SetPostionShadow(int nIdxShadow, D3DXVECTOR3 pos, D3DXVECTOR3 OldPos)
{
	QUESTSTATE pQuestState = GetQuestState();
	QUESTTYPE pQuestType = GetQuestType();

	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^

	if (g_shadow[nIdxShadow].bUse == true)
	{
		//�e�̈ʒu�X�V
		g_shadow[nIdxShadow].pos = D3DXVECTOR3(pos.x, 0.0f, pos.z);

		if (pQuestState == QUESTSTATE_PUZZLE)
		{
			if (pQuestType == QUESTTYPE_FIRST)
			{
				if (-452.8f - 150.0f < g_shadow[nIdxShadow].pos.x && 430.3f - 150.0f  > g_shadow[nIdxShadow].pos.x &&
					-531.6f < g_shadow[nIdxShadow].pos.z && 531.4f > g_shadow[nIdxShadow].pos.z)
				{
					g_shadow[nIdxShadow].pos.y = 70.0f;
				}
			}
			else if (pQuestType == QUESTTYPE_SECOND)
			{
				if (-452.8f - 150.0f < g_shadow[nIdxShadow].pos.x && 430.3f - 150.0f  > g_shadow[nIdxShadow].pos.x &&
					-531.6f < g_shadow[nIdxShadow].pos.z && 531.4f > g_shadow[nIdxShadow].pos.z)
				{
					g_shadow[nIdxShadow].pos.y = 70.0f;
				}
			}
			else if (pQuestType == QUESTTYPE_THIRD)
			{
				if (-452.8f - 150.0f < g_shadow[nIdxShadow].pos.x && 430.3f - 150.0f  > g_shadow[nIdxShadow].pos.x &&
					-531.6f < g_shadow[nIdxShadow].pos.z && 531.4f > g_shadow[nIdxShadow].pos.z)
				{
					g_shadow[nIdxShadow].pos.y = 70.0f;
				}
			}
		}

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

		//���݂̈ʒu���O��̈ʒu�������������Ƃ�
		if (pos.y > OldPos.y)
		{
			if (g_shadow[nIdxShadow].color.a > 0.0f)
			{
				g_shadow[nIdxShadow].color.a -= CHANGE_COL;		//�����x��������
			}
		}

		//���݂̈ʒu���O��̈ʒu�����Ⴉ�����Ƃ�
		if (pos.y < OldPos.y)
		{
			if (g_shadow[nIdxShadow].color.a < COLOR_A)
			{
				g_shadow[nIdxShadow].color.a += CHANGE_COL;		//�����x���グ��
			}
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4 * nIdxShadow;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_shadow[nIdxShadow].color.a);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_shadow[nIdxShadow].color.a);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_shadow[nIdxShadow].color.a);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_shadow[nIdxShadow].color.a);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// �e����������
//=============================================================================
void DeleteShadow(void)
{
	//�ϐ��錾
	int		nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_shadow[nCntShadow].bUse == true)
		{
			g_shadow[nCntShadow].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_shadow[nCntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_shadow[nCntShadow].Otherpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_shadow[nCntShadow].color.a = COLOR_A;
			g_shadow[nCntShadow].bUse = false;
			g_shadow[nCntShadow].fHight = 0.0f;
			g_shadow[nCntShadow].fWhidth = 0.0f;
			g_shadow[nCntShadow].fLength = 0.0f;
		}
	}
}
void DeleteShadow(int nIdxShadow)
{
	g_shadow[nIdxShadow].bUse = false;
}