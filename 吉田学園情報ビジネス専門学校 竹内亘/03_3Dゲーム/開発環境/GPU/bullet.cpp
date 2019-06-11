//=============================================================================
//
// �e�̏��� [bullet.cpp]
// Author : �|���j
//
//=============================================================================
#include "bullet.h"
#include "shadow.h"
#include "explosion.h"
#include "effect.h"
#include "particle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BB_TEXTURENAME	"data/TEXTURE/bullet000.png"			// �e�N�X�`����
#define MAX_BULLET	(256)										// �e�̍ő吔
#define BULLET_POS	(3.0f)										// �e�̈ʒu
#define MAX_POS		(4)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//void MakeVertexWall(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			// ���_�o�b�t�@�̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;					// �e�N�X�`���ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];								// �e�̏�� 
//int g_nIdexShadowBillboard;								// �e�̎擾�����邽��
D3DXVECTOR3 aPos[MAX_POS];

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	int nCntBullet;

	// �e�̏���������
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 30;
		g_aBullet[nCntBullet].nType = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].vecA = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].vecB = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].vecC = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;	
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BB_TEXTURENAME, &g_pTextureBullet);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-BULLET_POS, BULLET_POS, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(BULLET_POS, BULLET_POS, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-BULLET_POS, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(BULLET_POS, 0.0f, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	// �e�N�X�`���̉��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;

	aPos[0] = D3DXVECTOR3(-25, 0.0f, -25);
	aPos[1] = D3DXVECTOR3(-25, 0.0f, 725);
	aPos[2] = D3DXVECTOR3(725, 0.0f, 725);
	aPos[3] = D3DXVECTOR3(725, 0.0f, -25);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//�e���g�p����Ă���
		{
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;
			SetPositionShadow(g_aBullet[nCntBullet].nIdexShadow,D3DXVECTOR3(g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y -20,g_aBullet[nCntBullet].pos.z));
			SetEffect(g_aBullet[nCntBullet].pos, 5.0f, 5);

			////��莞�Ԍo��
			//g_aBullet[nCntBullet].nLife--;
			//if (g_aBullet[nCntBullet].nLife <= 0)
			//{
			//	//if (g_aBullet[nCntBullet].pos.z > 225)
			//	//{// Z�ʂ̉�
			//	//	//�����̐ݒ�
			//	//	//SetExplosion(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//	//	SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
			//	//	g_aBullet[nCntBullet].bUse = false;
			//	//	DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
			//	//}
			//	//else if (g_aBullet[nCntBullet].pos.z < -25)
			//	//{// Z�ʂ̎�O
			//	//	//�����̐ݒ�
			//	//	//SetExplosion(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//	//	SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
			//	//	g_aBullet[nCntBullet].bUse = false;
			//	//	DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
			//	//}
			//	//else if (g_aBullet[nCntBullet].pos.x > 225)
			//	//{// X�ʂ̉E
			//	//	//�����̐ݒ�
			//	//	//SetExplosion(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//	//	SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
			//	//	g_aBullet[nCntBullet].bUse = false;
			//	//	DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
			//	//}
			//	//else if (g_aBullet[nCntBullet].pos.x < -25)
			//	//{// X�ʂ̍�
			//	//	//�����̐ݒ�
			//	//	//SetExplosion(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].move, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			//	//	SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
			//	//	g_aBullet[nCntBullet].bUse = false;
			//	//	DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
			//	//}
			//}

			// �O�ς̓����蔻��
			for (int nCnt = 0; nCnt < MAX_POS; nCnt++)
			{
				g_aBullet[nCntBullet].vecA = aPos[nCnt + 1] - aPos[nCnt];
				g_aBullet[nCntBullet].vecC = g_aBullet[nCntBullet].pos - aPos[nCnt];

				if (((g_aBullet[nCntBullet].vecA.z * g_aBullet[nCntBullet].vecC.x) - (g_aBullet[nCntBullet].vecA.x * g_aBullet[nCntBullet].vecC.z)) < 0)
				{
					SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f,0.0f,0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
					g_aBullet[nCntBullet].bUse = false;
					DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
				}
			}

			//// ���ς𗘗p�������ˏ���
			//g_aBullet[nCntBullet].vecA = aPos[1] - aPos[0];
			//g_aBullet[nCntBullet].vecB = g_aBullet[nCntBullet].pos - aPos[0];

			//if ((g_aBullet[nCntBullet].vecA.x * g_aBullet[nCntBullet].vecB.x )+ (g_aBullet[nCntBullet].vecA.z * g_aBullet[nCntBullet].vecB.z))
			//{

			//}

			if (g_aBullet[nCntBullet].nType == BULLETTYPE_PLAYER)
			{// �v���C���[�̒e
				//�G�̎擾
				//Enemy * pEnemy;
				//pEnemy = GetEnemy();

				//for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				//	if (pEnemy->bUse == true)
				//	{
				//		{//�����蔻��
				//			//if (g_aBullet[nCntBullet].pos.x > pEnemy->aModel[nCntEnemy].pos.x - 250 &&
				//			//	g_aBullet[nCntBullet].pos.x < pEnemy->aModel[nCntEnemy].pos.x + 250 &&
				//			//	g_aBullet[nCntBullet].pos.z < pEnemy->aModel[nCntEnemy].pos.z + 250 &&
				//			//	g_aBullet[nCntBullet].pos.z > pEnemy->aModel[nCntEnemy].pos.z - 250)
				//			if(pEnemy->aModel[nCntEnemy].pos.x > g_aBullet[nCntBullet].pos.x - 50 &&
				//				pEnemy->aModel[nCntEnemy].pos.x < g_aBullet[nCntBullet].pos.x + 50 &&
				//				pEnemy->aModel[nCntEnemy].pos.z < g_aBullet[nCntBullet].pos.z + 50 &&
				//				pEnemy->aModel[nCntEnemy].pos.z > g_aBullet[nCntBullet].pos.z - 50)
				//			{
				//				HitEnemy(nCntEnemy, 1);				//�U����
				//				g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
				//				//DeleteShadow(g_aBullet[nCntBullet].nIdexShadow);
				//				SetParticle(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
				//			}
				//		}
				//	}
			}
			pVtx += 4;
		}

		// ���_�o�b�t�@���A�����b�N
		g_pVtxBuffBullet->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	int nCntBullet;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxView, mtxTrans;				//�v�Z�p�}�g���b�N�X

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aBullet[nCntBullet].mtxWorld);

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);

		g_aBullet[nCntBullet].mtxWorld._11 = mtxView._11;
		g_aBullet[nCntBullet].mtxWorld._12 = mtxView._21;
		g_aBullet[nCntBullet].mtxWorld._13 = mtxView._31;
		g_aBullet[nCntBullet].mtxWorld._21 = mtxView._12;
		g_aBullet[nCntBullet].mtxWorld._22 = mtxView._22;
		g_aBullet[nCntBullet].mtxWorld._23 = mtxView._32;
		g_aBullet[nCntBullet].mtxWorld._31 = mtxView._13;
		g_aBullet[nCntBullet].mtxWorld._32 = mtxView._23;
		g_aBullet[nCntBullet].mtxWorld._33 = mtxView._33;

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
		D3DXMatrixMultiply(&g_aBullet[nCntBullet].mtxWorld, &g_aBullet[nCntBullet].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aBullet[nCntBullet].mtxWorld);

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet);

		// �A���t�@�e�X�g
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF,0);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		if (g_aBullet[nCntBullet].bUse == true)	// �e���g�p����Ă���
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBullet,
				2);
		}

		// �A���t�@�e�X�g�𖳌��ɂ���
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
int SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			g_aBullet[nCntBullet].pos = pos;

			g_aBullet[nCntBullet].rot = rot;

			g_aBullet[nCntBullet].move = move;

			g_aBullet[nCntBullet].nIdexShadow = SetShadow(g_aBullet[nCntBullet].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			g_aBullet[nCntBullet].bUse = true;			// �g�p���Ă���
			break;
		}
	}

	return nCntBullet;
}
////=============================================================================
//// �r���{�[�h�̈ʒu��ݒ�
////=============================================================================
//void SetPositionBillboard(int nIdexBillboard, D3DXVECTOR3 pos)
//{
//	g_aBillboard[nIdexBillboard].pos = pos;
//}

