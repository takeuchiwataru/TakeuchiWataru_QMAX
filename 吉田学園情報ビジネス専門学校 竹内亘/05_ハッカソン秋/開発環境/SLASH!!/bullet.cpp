//=============================================================================
//
// �e���� [bullet.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "bullet.h"
#include "input.h"
#include "main.h"
#include "enemy.h" 
#include "player.h"
#include "effect.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_POS_X			(80)										//���_���WX�̈ړ���
#define POLYGON_POS_Y			(120)										//���_���WY�̈ړ���
#define EFFECT_COLOR_PLAYER		(D3DXCOLOR (0.3f, 0.8f, 0.8f, 0.6f))	//���@�̒e�̃G�t�F�N�g�J���[
#define EFFECT_RADIUS_PLAYER	(80.0f)									//�G�t�F�N�g�̔��a
#define EFFECT_LIFE_PLAYER		(10)									//�G�t�F�N�g�̃��C�t
#define EFFECT_RADIUS_ENEMY		(50.0f)									//�G�t�F�N�g�̔��a
#define EFFECT_LIFE_ENEMY		(15)									//�G�t�F�N�g�̃��C�t
#define ENEMY_HIT				(100)									//�G�̓����蔻��
#define PLAYER_HIT				(10)									//���@�̓����蔻��
#define BOSS_HIT				(100)									//�G�̓����蔻��

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBullet = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Bullet g_aBullet[MAX_BULLET];						//�e�̏��
float g_Keisu = 1;
int g_nCntTimer = 0;
int g_nCntHomingTimer = 0;

//=============================================================================
// ����������
//=============================================================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;
	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	g_aBullet[0].pos = D3DXVECTOR3(100, 100, 0.0f);
	g_aBullet[0].move = D3DXVECTOR3(0, 0, 0.0f);

	// �e�̏��̏�����
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 40;
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].bUse = false;
		g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;

		
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\��.png",
		&g_pTextureBullet);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
		
		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		//���_
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	int nCntBullet;


	VERTEX_2D *pVtx;//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);



	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//�e���g�p����Ă���
		{
			g_aBullet[nCntBullet].pos.y -= g_aBullet[nCntBullet].move.y;
			g_aBullet[nCntBullet].pos.x -= g_aBullet[nCntBullet].move.x;
			g_aBullet[nCntBullet].nLife--;
			//�ʒu�̍X�V
			//���_���W�X�V
			pVtx[0].pos.x = g_aBullet[nCntBullet].pos.x - POLYGON_POS_X;
			pVtx[0].pos.y = g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y;
			pVtx[1].pos.x = g_aBullet[nCntBullet].pos.x + POLYGON_POS_X;
			pVtx[1].pos.y = g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y;
			pVtx[2].pos.x = g_aBullet[nCntBullet].pos.x - POLYGON_POS_X;
			pVtx[2].pos.y = g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y;
			pVtx[3].pos.x = g_aBullet[nCntBullet].pos.x + POLYGON_POS_X;
			pVtx[3].pos.y = g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y;

			//�e�N�X�`��
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//�e�̃��C�t���s�����甚��
			if (g_aBullet[nCntBullet].nLife <= 0)
			{
				g_aBullet[nCntBullet].bUse = false;
			}
			
			if (g_aBullet[nCntBullet].type == BULLETTYPE_PLAYER)
			{//�����̒e�̏ꍇ
				int nCntEnemy;
				Enemy *pEnemy;
				//�G�̎擾
				pEnemy = GetEnemy();

				Player *pPlayer;
				//�v���C���[�̎擾
				pPlayer = GetPlayer();

				if (g_aBullet[nCntBullet].pos.x > pPlayer->pos.x && g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - 40)
				{
					//���_���W
					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_X, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, 0.0f);

					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
					
				}
				if (g_aBullet[nCntBullet].pos.x - 5 < pPlayer->pos.x && g_aBullet[nCntBullet].pos.y < pPlayer->pos.y - 30)
				{
					//���_���W
					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);


					g_aBullet[nCntBullet].move.y = -10;
				}
					if (g_aBullet[nCntBullet].pos.x < pPlayer->pos.x && g_aBullet[nCntBullet].pos.y > pPlayer->pos.y - 40)
				{
					//���_���W
					pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_X, 0.0f);
					pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, 0.0f);
					pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, 0.0f);
					pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, 0.0f);

					//�e�N�X�`��
					pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
					pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
					pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
					pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
					
				}

				if (g_aBullet[nCntBullet].pos.y > pPlayer->pos.y + 30)
				{
					g_aBullet[nCntBullet].move.y = 0;
				}

				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
				{//�G�̐������J��Ԃ�
					if (pEnemy->bUse == true)	//�G���g�p����Ă���
					{
						if (pEnemy->pos.x - ENEMY_HIT < g_aBullet[nCntBullet].pos.x && pEnemy->pos.x + ENEMY_HIT > g_aBullet[nCntBullet].pos.x
							&& pEnemy->pos.y - ENEMY_HIT < g_aBullet[nCntBullet].pos.y && pEnemy->pos.y + ENEMY_HIT > g_aBullet[nCntBullet].pos.y)
						{//�G�͈͓̔��ɒe����������
							HitEnemy(nCntEnemy, 1);	//1�̓_���[�W
						}
					}
				}
				//�G�t�F�N�g�`��
				SetEffect(g_aBullet[nCntBullet].pos, EFFECT_COLOR_PLAYER, EFFECT_RADIUS_PLAYER, EFFECT_LIFE_PLAYER);
			}
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
	
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBullet);

	// �|���S���̕`��
	for(nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)	//�e���g�p����Ă���
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntBullet),	//�J�n���钸�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
}

//=============================================================================
// �e�̐ݒ菈��
//=============================================================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move,BULLETTYPE type)
{
	int nCntBullet;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
					//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	if (type == BULLETTYPE_PLAYER)
	{
		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
		{

			if (g_aBullet[nCntBullet].bUse == false)	//�e���g�p����Ă��Ȃ�
			{
				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = BULLETTYPE_PLAYER;

				//���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				
				//���_�J���[
				pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

				g_aBullet[nCntBullet].nLife = 17;

				g_aBullet[nCntBullet].bUse = true;
				break;
			}
			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
		}
	}
	else if (type == BULLETTYPE_ENEMY)
	{
		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
		{

			if (g_aBullet[nCntBullet].bUse == false)	//�e���g�p����Ă��Ȃ�
			{

				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = BULLETTYPE_ENEMY;

				//���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				g_aBullet[nCntBullet].nLife = 100;

				g_aBullet[nCntBullet].bUse = true;

				break;
			}
			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
		}
	}
	else if (type == BULLETTYPE_BOSS)
	{
		for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
		{

			if (g_aBullet[nCntBullet].bUse == false)	//�e���g�p����Ă��Ȃ�
			{

				g_aBullet[nCntBullet].pos = pos;
				g_aBullet[nCntBullet].move = move;
				g_aBullet[nCntBullet].type = BULLETTYPE_BOSS;

				//���_���W
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y - POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + POLYGON_POS_X, g_aBullet[nCntBullet].pos.y + POLYGON_POS_Y, g_aBullet[nCntBullet].pos.z);

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				g_aBullet[nCntBullet].nLife = 150;

				g_aBullet[nCntBullet].bUse = true;

				break;
			}
			pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}
//=============================================================================
// �e�̎擾
//=============================================================================
Bullet *GetBullet(void)
{
	return &g_aBullet[0];
}