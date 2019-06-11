//=============================================================================
//
// �e���� [bullet.cpp]
// Author :�|���j
//
//=============================================================================
#include "bullet.h"
#include "explosion.h"
#include "enemy.h"
#include "boss.h"
#include "player.h"
#include "effect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BULLET			(256)								//�e�̍ő吔
#define POLYGON_X			(1200)								//�|���S����X���W
#define POLYGON_Y			(350)								//�|���S����Y���W
#define BULLET_TEXTURENAME	"data/TEXTURE/bullet000.png"		//�e�N�X�`����
#define BULLET_SIZE			(5)									//�e�̑傫��
#define BULLET_SIZE_1		(15)								//�e�̑傫��
#define ENEMY_HIT			(30)								//�G�̓����蔻��
#define BOSS_HIT			(40)								//�{�X�̓����蔻��
#define PLAYER_HIT			(25)								//�v���C���[�̓����蔻��
#define KEISUU_DATA			(0.3f)								//�W���̐���


//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;	//�e�̈ʒu
	D3DXVECTOR3 move;	//�e�̈ړ�
	D3DXCOLOR col;		//�e�̐F
	int nLife;			//�e�̃��C�t
	BULLETTYPE type;	//�e�̎��
	bool bUse;
} Bullet;

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//�g�p���Ă��邩�ǂ���

//=============================================================================
// �e�̏���������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�|���S�����W�̐ݒ�
	g_aBullet[0].pos = D3DXVECTOR3(POLYGON_X, POLYGON_Y, 0.0f);
	g_aBullet[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
		g_aBullet[nCntBullet].nLife = 20;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BULLET_TEXTURENAME, &g_pTextureBullet);

	//���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,						//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&g_pVtxBuffBullet,
								NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y +BULLET_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �e�̏I������
//=============================================================================
void UninitBullet(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//�e���g�p����Ă���
		{
			//�G�t�F�N�g�̐ݒ�
			SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].col, 10.0f, 10);
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//���_���W�̍X�V
			pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

			if (g_aBullet[nCntBullet].pos.y < 0)
			{
				g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
			}

			//��莞�Ԍo��
			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				//�����̐ݒ�
				SetExplosion(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 1.0f, 1.0f,1.0f));
				g_aBullet[nCntBullet].bUse = false;
			}

			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)	//�v���C���[�̒e
			{
				int nCntEnemy;
				
				//�G�̎擾
				Enemy *pEnemy;
				pEnemy = GetEnemy();

				//�{�X�̎擾
				Boss *pBoss;
				pBoss = GetBoss();

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{
					if (pEnemy->bUse == true)
					{//�G���g�p����Ă���
						if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
						{
							if (g_aBullet[nCntBullet].pos.x >  pEnemy->pos.x - ENEMY_HIT
								&& g_aBullet[nCntBullet].pos.x <  pEnemy->pos.x + ENEMY_HIT
								&& g_aBullet[nCntBullet].pos.y <  pEnemy->pos.y + ENEMY_HIT
								&& g_aBullet[nCntBullet].pos.y > pEnemy->pos.y - ENEMY_HIT)
							{
								HitEnemy(nCntEnemy, 1);				//�U����
								g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
							}
						}
					}

					else if (pBoss->bUse == true)
					{//�{�X���g�p����Ă���
						if (g_aBullet[nCntBullet].pos.x >  pBoss->pos.x - BOSS_HIT
							&& g_aBullet[nCntBullet].pos.x <  pBoss->pos.x + BOSS_HIT
							&& g_aBullet[nCntBullet].pos.y <  pBoss->pos.y + BOSS_HIT
							&& g_aBullet[nCntBullet].pos.y > pBoss->pos.y - BOSS_HIT)
						{
							HitBoss(nCntEnemy, 1);				//�U����
							g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
						}
					}
				}
				//�G�t�F�N�g�̐ݒ�(�v���C���[�e�j
				SetEffect(g_aBullet[nCntBullet].pos, g_aBullet[nCntBullet].col, 20, 20);
			}
			else if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)	//�G�̒e
			{
				Player *pPlayer;

				//�v���C���[�̎擾
				pPlayer = GetPlayer();

				if (pPlayer->bDisp == true)
				{//�v���C���[���g�p����Ă���
					if (g_aBullet[nCntBullet].type == BULLETTYPE_ENEMY)
					{
						if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x - PLAYER_HIT
							&& g_aBullet[nCntBullet].pos.x < pPlayer->pos.x + PLAYER_HIT
							&& g_aBullet[nCntBullet].pos.y <  pPlayer->pos.y + PLAYER_HIT
							&& g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - PLAYER_HIT)

						{
							HitPlayer(1);						//�U����
							g_aBullet[nCntBullet].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
						}
					}
				}
			}
		}
		pVtx +=  4;	//�Y���̈ʒu�܂Ői�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �e�̕`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	//�|���S���̕`��
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//�e���g�p����Ă���
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
									4 * nCntBullet,
									2);
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, BULLETTYPE type)
{
	int nCntBullet;

	float fDiffAngle;	//����
	float fDestAngle;	//�ړI�̊p�x
	float fMoveAngle;	//���݂̊p�x

	fDestAngle = 0;
	fMoveAngle = 0;

	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{
			if (type == BULLETTYPE_PLAYER)
			{
				g_aBullet[nCntBullet].pos = pos;

				VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += (nCntBullet * 4);	//�Y���̈ʒu�܂Ői�߂�

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				//���_�o�b�t�@���A�����b�N
				g_pVtxBuffBullet->Unlock();

				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;
				g_aBullet[nCntBullet].bUse = true;	//�g�p���Ă�����
				g_aBullet[nCntBullet].nLife = 40;	//�g�p���Ă�����
				break;
			}
			else if (type == BULLETTYPE_ENEMY)
			{
				fDiffAngle = fDestAngle - fMoveAngle;

				if (fDiffAngle > D3DX_PI)
				{
					fDiffAngle -= D3DX_PI * 2.0f;
				}
				else if (fDiffAngle < D3DX_PI)
				{
					fDiffAngle += D3DX_PI * 2.0f;
				}

				fMoveAngle += fDiffAngle * KEISUU_DATA;

				if (fDiffAngle > D3DX_PI)
				{
					fDiffAngle -= D3DX_PI * 2.0f;
				}
				else if (fDiffAngle < D3DX_PI)
				{
					fDiffAngle += D3DX_PI * 2.0f;
				}

				g_aBullet[nCntBullet].pos = pos;

				VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

				//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
				g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += (nCntBullet * 4);	//�Y���̈ʒu�܂Ői�߂�

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_1, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_1, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_1, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_1, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE_1, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_1, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE_1, g_aBullet[nCntBullet].pos.y - BULLET_SIZE_1, 0.0f);

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);

				//���_�o�b�t�@���A�����b�N
				g_pVtxBuffBullet->Unlock();

				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = BULLETTYPE_ENEMY;
				g_aBullet[nCntBullet].bUse = true;	//�g�p���Ă�����
				g_aBullet[nCntBullet].nLife = 100;	//�g�p���Ă�����
				break;
			}
		}
	}
}