//=============================================================================
//
// �G���� [enemy.cpp]
// Author :�@�|���j
//
//=============================================================================
#include "enemy.h"
#include "explosion.h"
#include "bullet.h"
#include "game.h"
#include "score.h"
#include "sound.h"
#include "player.h"
#include "boss.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(7)								//�G�̎��
#define ENEMY_TEXTURE_NAME0	"data/TEXTURE/enemy000.png"		//�G0�̃e�N�X�`����
#define ENEMY_TEXTURE_NAME1	"data/TEXTURE/enemy001.png"		//�G1�̃e�N�X�`����
#define ENEMY_TEXTURE_NAME2	"data/TEXTURE/enemy002.png"		//�G2�̃e�N�X�`����
#define ENEMY_TEXTURE_NAME3	"data/TEXTURE/enemy003.png"		//�G3�̃e�N�X�`����
#define ENEMY_TEXTURE_NAME4 "data/TEXTURE/enemy004.png"		//�G4�̃e�N�X�`����
#define	ENEMY_SIZE			(25)							//�G�̑傫��
#define ENEMY_LIFE			(3)								//�G�̗̑�
#define DAMAGE_TIME			(5)								//�_���[�W��Ԃ̎���

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					//���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];										//�G�̏��
int g_nNumEnemy;												//�G�̑���

//=============================================================================
// �G�̏���������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	//���_���̍쐬
	VERTEX_2D *pVtx;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�G�̏��̏�����
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = ENEMY_LIFE;
		g_aEnemy[nCntEnemy].nCounterAnimEnemy = 0;
		g_aEnemy[nCntEnemy].nPartternAnimEnemy = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_nNumEnemy = 0;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME0, &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME1, &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME2, &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME3, &g_apTextureEnemy[3]);
	D3DXCreateTextureFromFile(pDevice, ENEMY_TEXTURE_NAME4, &g_apTextureEnemy[4]);

	//���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �G�̏I������
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	//�e�N�X�`���̊J��
	for(nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// �G�̍X�V����
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;

	float fKakudo;		//�p�x�p�̕ϐ�

	//�v���C���[�̎擾
	Player * pPlayer;
	pPlayer = GetPlayer();

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].nCounterAnimEnemy++;

		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntEnemy * 4);	//�Y���̈ʒu�܂Ői�߂�

		if (g_aEnemy[nCntEnemy].bUse == true)
		{//�G���g�p����Ă���
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
				if (rand() % 300 == 0)
				{
					//SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(0.0f, 5.0f, 0.0f), BULLETTYPE_ENEMY);

					fKakudo = atan2f(pPlayer->pos.x - g_aEnemy[nCntEnemy].pos.x, pPlayer->pos.y - g_aEnemy[nCntEnemy].pos.y);		//�p�x���߂�
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(fKakudo) * 5.0f, cosf(fKakudo) * 5.0f, 0.0f), BULLETTYPE_ENEMY);
				}
				break;

			case ENEMYSTATE_DAMEGE:
				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;

					PlaySound(SOUND_LABEL_SE_HIT000);

					//���_�J���[
					pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
					pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				}
				break;
			}

			if ((g_aEnemy[nCntEnemy].nCounterAnimEnemy % 30) == 0)
			{
				g_aEnemy[nCntEnemy].nPartternAnimEnemy = (g_aEnemy[nCntEnemy].nPartternAnimEnemy + 1) % 2;	//�p�^�[��No.�X�V

				//�e�N�X�`���̍��W���X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f * g_aEnemy[nCntEnemy].nPartternAnimEnemy), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.5f + (0.5f * g_aEnemy[nCntEnemy].nPartternAnimEnemy), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (0.5f * g_aEnemy[nCntEnemy].nPartternAnimEnemy), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f * g_aEnemy[nCntEnemy].nPartternAnimEnemy), 1.0f);
			}

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffEnemy->Unlock();
		}
	}
}

//=============================================================================
// �G�̕`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntEnemy,
				2);
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, int nType)
{
	int nCntEnemy;

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)	//�G���g�p����Ă��Ȃ�
		{
			g_aEnemy[nCntEnemy].pos = pos;

			VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntEnemy * 4);	//�Y���̈ʒu�܂Ői�߂�

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_SIZE, 0.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffEnemy->Unlock();

			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].bUse = true;	//�g�p���Ă�����
			g_nNumEnemy++;
			break;
		}
	}
}

//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	int nValue = 0;

	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION);
		g_aEnemy[nCntEnemy].bUse = false;
		AddScore(2000);

		g_nNumEnemy--;		//�G�̑��������炷
		if (g_nNumEnemy <= 0)
		{
			//StopSound(SOUND_LABEL_BGM002);
			//SetGameState(GAMESTATE_END);

			//�{�X�̎擾
			Boss * pBoss;
			pBoss = GetBoss();

			SetBoss(D3DXVECTOR3(600, 300, 0.0f), 0);

			//�{�XBGM
			//PlaySound(SOUND_LABEL_BGM003);
		}
	}

	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMEGE;
		g_aEnemy[nCntEnemy].nCounterState = DAMAGE_TIME;	//�_���[�W��Ԃ̎���

		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += (nCntEnemy * 4);	//�Y���̈ʒu�܂Ői�߂�

		//���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		
		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffEnemy->Unlock();
	}
}

//=============================================================================
// �G�̎擾
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}
