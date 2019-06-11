//=============================================================================
//
// �{�X���� [boss.cpp]
// Author :�@�|���j
//
//=============================================================================
#include "boss.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "sound.h"
#include "player.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(3)								//�{�X�̎��
#define ENEMY_TEXTURE_NAME5 "data/TEXTURE/enemy005.png"		//�G5(�{�X)�̃e�N�X�`����
#define	BOSS_SIZE			(100)							//�{�X�̑傫��
#define BOSS_LIFE			(20)							//�{�X�̗̑�
#define DAMAGE_TIME			(5)								//�_���[�W��Ԃ̎���

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureBoss[MAX_TYPE_ENEMY] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;					//���_�o�b�t�@�ւ̃|�C���^
Boss g_aBoss[MAX_ENEMY];										//�{�X�̏��
int g_nNumBoss;													//�{�X�̑���
float g_Spin = 0.0f;											//�e�̉�]0

//=============================================================================
// �{�X�̏���������
//=============================================================================
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBoss;

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�{�X�̏��̏�����
	for(nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].nType = 0;
		g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;
		g_aBoss[nCntBoss].nCounterState = 0;
		g_aBoss[nCntBoss].nLife = BOSS_LIFE;
		g_aBoss[nCntBoss].nCounterAnimBoss = 0;
		g_aBoss[nCntBoss].nPartternAnimBoss = 0;
		g_aBoss[nCntBoss].bUse = false;
		g_nNumBoss = 0;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME5, &g_apTextureBoss[0]);

	//���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffBoss,
									NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_SIZE, g_aBoss[nCntBoss].pos.y - BOSS_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_SIZE, g_aBoss[nCntBoss].pos.y - BOSS_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_SIZE, g_aBoss[nCntBoss].pos.y + BOSS_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_SIZE, g_aBoss[nCntBoss].pos.y + BOSS_SIZE, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.5f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 1.0f);

		pVtx += 4;	//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBoss->Unlock();
}

//=============================================================================
// �{�X�̏I������
//=============================================================================
void UninitBoss(void)
{
	int nCntTex;

	//�e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureBoss[nCntTex] != NULL)
		{
			g_apTextureBoss[nCntTex]->Release();
			g_apTextureBoss[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//=============================================================================
// �{�X�̍X�V����
//=============================================================================
void UpdateBoss(void)
{
	int nCntBoss;

	//�v���C���[�̎擾
	Player * pPlayer;
	pPlayer = GetPlayer();

	for (nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		g_aBoss[nCntBoss].nCounterAnimBoss++;

		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntBoss * 4);	//�Y���̈ʒu�܂Ői�߂�

		if (g_aBoss[nCntBoss].bUse == true)
		{//�{�X���g�p����Ă���
			switch (g_aBoss[nCntBoss].state)
			{
			case BOSSSTATE_NORMAL:
				if (rand() % 7 == 0)
				{
					//SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_ENEMY);

					//fKakudo = atan2f(pPlayer->pos.x - g_aBoss[nCntBoss].pos.x, pPlayer->pos.y - g_aBoss[nCntBoss].pos.y);		//�p�x���߂�
					//SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(fKakudo) * 5.0f, cosf(fKakudo) * 5.0f, 0.0f), BULLETTYPE_ENEMY);
					
					//��]�e
					g_Spin += 0.1f;		//�e�̉�]�̑���
					D3DXVECTOR3 SetSpin(g_aBoss[nCntBoss].pos);
					D3DXVECTOR3 MoveSpin(0.0f, 0.0f, 0.0f);
					MoveSpin.x += sinf(D3DX_PI * g_Spin) * 4;
					MoveSpin.y += cosf(D3DX_PI * g_Spin) * 4;
					SetBullet(SetSpin, MoveSpin, BULLETTYPE_ENEMY);
					
				}
				break;

			case BOSSSTATE_DAMEGE:
				g_aBoss[nCntBoss].nCounterState--;

				if (g_aBoss[nCntBoss].nCounterState <= 0)
				{
					g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;

					PlaySound(SOUND_LABEL_SE_HIT000);

					//���_�J���[
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;

			case BOSSSTATE_DEATH:
				g_aBoss[nCntBoss].nCounterState--;

				if (g_aBoss[nCntBoss].nCounterState <= 0)
				{
					SetGameState(GAMESTATE_END);
					g_aBoss[nCntBoss].state = BOSSSTATE_END;
				}
				return;
				break;

			}

			if ((g_aBoss[nCntBoss].nCounterAnimBoss % 30) == 0)
			{
				g_aBoss[nCntBoss].nPartternAnimBoss = (g_aBoss[nCntBoss].nPartternAnimBoss + 1) % 2;	//�p�^�[��No.�X�V

				//�e�N�X�`���̍��W���X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f * g_aBoss[nCntBoss].nPartternAnimBoss), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f + (0.5f * g_aBoss[nCntBoss].nPartternAnimBoss), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.5f * g_aBoss[nCntBoss].nPartternAnimBoss), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f * g_aBoss[nCntBoss].nPartternAnimBoss), 1.0f);
			}

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffBoss->Unlock();
		}
	}
}

//=============================================================================
// �{�X�̕`�揈��
//=============================================================================
void DrawBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for(int nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBoss[g_aBoss[nCntBoss].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntBoss,
				2);
		}
	}
}

//=============================================================================
// �{�X�̐ݒ�
//=============================================================================
void SetBoss(D3DXVECTOR3 pos, int nType)
{
	int nCntBoss;

	for(nCntBoss = 0; nCntBoss < MAX_ENEMY; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == false)	//�{�X���g�p����Ă��Ȃ�
		{
			g_aBoss[nCntBoss].pos = pos;

			VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntBoss * 4);	//�Y���̈ʒu�܂Ői�߂�

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_SIZE, g_aBoss[nCntBoss].pos.y - BOSS_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_SIZE, g_aBoss[nCntBoss].pos.y - BOSS_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_SIZE, g_aBoss[nCntBoss].pos.y + BOSS_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_SIZE, g_aBoss[nCntBoss].pos.y + BOSS_SIZE, 0.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffBoss->Unlock();

			g_aBoss[nCntBoss].nType = nType;
			g_aBoss[nCntBoss].bUse = true;	//�g�p���Ă�����
			g_nNumBoss++;
			break;
		}
	}
}

//=============================================================================
// �{�X�̃_���[�W����
//=============================================================================
void HitBoss(int nCntBoss, int nDamage)
{
	int nValue = 0;

	g_aBoss[nCntBoss].nLife -= nDamage;

	if (g_aBoss[nCntBoss].nLife <= 0)
	{
		g_aBoss[nCntBoss].state = BOSSSTATE_DEATH;
		SetExplosion(g_aBoss[nCntBoss].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_aBoss[nCntBoss].bUse = false;
		AddScore(5000);

		g_nNumBoss--;		//�{�X�̑��������炷
		if (g_nNumBoss <= 0)
		{
  			SetGameState(GAMESTATE_GAMECLEAR);
		}
	}

	else
	{
		g_aBoss[nCntBoss].state = BOSSSTATE_DAMEGE;
		g_aBoss[nCntBoss].nCounterState = DAMAGE_TIME;	//�_���[�W��Ԃ̎���

		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntBoss * 4);	//�Y���̈ʒu�܂Ői�߂�

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffBoss->Unlock();
	}
}

//=============================================================================
// �{�X�̎擾
//=============================================================================
Boss *GetBoss(void)
{
	return &g_aBoss[0];
}
