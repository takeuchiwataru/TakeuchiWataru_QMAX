//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �|���j
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "particle.h"
#include "bullet.h"
#include "remain.h"
#include "attackgauge.h"
#include "input.h"
#include "reload.h"
#include "game.h"
#include "sound.h"
#include "life.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_TEXTURENAME	"data/TEXTURE/player000.png"		//�e�N�X�`����
#define MAX_PARTTERN		(10)								//�p�^�[���̍ő�
#define	POLYGON_X			(0)									//�|���S��X���W
#define POLYGON_Y			(0)									//�|���S��Y���W
#define POLYGON_COUNT		(1)									//�傫������ƃA�j���[�V�������x���Ȃ�
#define PLAYER_SIZE			(50)								//�v���C���[�̑傫��
#define PLAYER_SPEED		(2)									//�v���C���[�̑���
#define PLAYER_X            (640)								//�v���C���[��X���W
#define PLAYER_Y            (560)								//�v���C���[��X���W
#define MAX_LIFE			(10)								//���C�t�ő�\����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void DecisionPlayer(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTexturePlayer = NULL;    // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
Player                  g_player;                   // �v���C���[
int                     g_CounterAttack;            // �Q�[�W�A�^�b�N
float   g_pSpinPlayer = 0.75f;                       // �p�[�e�B�N���Ɏg�p

//=============================================================================
// �v���C���[����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���C���[�̏��̏�����
	g_player.pos = D3DXVECTOR3(640,670,0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);
	g_player.state = PLAYERSTATE_APPEAR;
	g_player.nCounterState = 120;
	g_player.nLife = PLAYER_LIFE;
	g_player.nRemain = PLAYER_REMAIN;
	g_player.nSharp = PLAYER_SHARP;
	g_player.nCounterSharp = 0;
	g_player.nCounterGauge = 0;
	g_player.bDisp = true;
	g_CounterAttack = 0;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, PLAYER_TEXTURENAME, &g_pTexturePlayer);

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&g_pVtxBuffPlayer,
								NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE, g_player.pos.y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_SIZE, g_player.pos.y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_SIZE, g_player.pos.y + PLAYER_SIZE, 0.0f);

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

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
}

//=============================================================================
// �v���C���[�I������
//=============================================================================
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//=============================================================================
// �v���C���[�X�V����
//=============================================================================
void UpdatePlayer(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_player.state)
	{
	case PLAYERSTATE_APPEAR:
		g_player.nCounterState--;
		if (g_player.nCounterState <= 0)
		{// ������x�o����Ԃ��L�[�v���ꂽ
			g_player.state = PLAYERSTATE_NORMAL;
		}
		break;

	case PLAYERSTATE_NORMAL:
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		break;

	case PLAYERSTATE_DAMEGE:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{// ��ԃJ�E���^�[���O�ɂȂ���
			g_player.state = PLAYERSTATE_NORMAL;

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		break;

	case PLAYERSTATE_DEATH:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{// ��ԃJ�E���^�[���O�ɂȂ���
			if (g_player.nRemain > 0)
			{// �c�@���܂�����
				g_player.pos = D3DXVECTOR3(640, 680, 0.0f);
				g_player.state = PLAYERSTATE_APPEAR;
				g_player.nCounterState = 60;
				g_player.nLife = PLAYER_LIFE;
				g_player.nSharp = PLAYER_SHARP;
				g_player.nCounterSharp = 0;
				g_player.nCounterGauge = 0;
				g_player.bDisp = true;
				SetLife(g_player.nLife);

				// ���_���W�̍X�V
				pVtx[0].pos.x = g_player.pos.x - PLAYER_SIZE;
				pVtx[0].pos.y = g_player.pos.y - PLAYER_SIZE;
				pVtx[1].pos.x = g_player.pos.x + PLAYER_SIZE;
				pVtx[1].pos.y = g_player.pos.y - PLAYER_SIZE;
				pVtx[2].pos.x = g_player.pos.x - PLAYER_SIZE;
				pVtx[2].pos.y = g_player.pos.y + PLAYER_SIZE;
				pVtx[3].pos.x = g_player.pos.x + PLAYER_SIZE;
				pVtx[3].pos.y = g_player.pos.y + PLAYER_SIZE;
			}
			else if (g_player.nRemain <= 0 && g_player.state != PLAYERSTATE_MAX)
			{// �c�@�������Ȃ�
				SetGameState(GAMESTATE_END);
				g_player.state = PLAYERSTATE_MAX;
			}
		}
		return;
		break;
	case PLAYERSTATE_GAUGE_MAX:

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		if (GetKeyboardPress(DIK_SPACE))
		{// SPACE�L�[�������ꑱ���Ă���
			g_CounterAttack++;
			if (g_CounterAttack >= 80)
			{
				SetParticle(g_player.pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 60.0f, rand() % 20);
			}
		}
		if (g_CounterAttack >= 80 && GetKeyboardRelease(DIK_SPACE))
		{// ������x�����ꂽ�㗣���ꂽ
			g_CounterAttack = 0;
			g_player.nCounterGauge = 0;
			ATTACKGAUGE *gauge;
			gauge = GetAttackGauge();
			gauge->ngauge = 0;

			g_player.state = PLAYERSTATE_NORMAL;
			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			Enemy *pEnemy;
			pEnemy = GetEnemy();

			for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{//�G�̐������J��Ԃ�
				if (pEnemy->bUse == true)	//�G���g�p����Ă���
				{
					HitEnemy(nCntEnemy, 1);
				}
			}
			PlaySound(SOUND_LABEL_SE_KAMINARI);
		}
		else if (g_CounterAttack < 80 && GetKeyboardRelease(DIK_SPACE))
		{
			g_CounterAttack = 0;
		}
		break;
	}

	if (g_player.bDisp == true)
	{
		if (g_player.nSharp > 0)
		{// �؂ꖡ���܂�����
			if (GetKeyboardTrigger(DIK_SPACE) == true)
			{//�ؖ���0�ɂȂ�܂ōU��
				D3DXVECTOR3 SetPos(g_player.pos.x + 100, g_player.pos.y + 40, g_player.pos.z);
				D3DXVECTOR3 MovePos(10.0f,10.0f,0.0f);
				SetBullet(SetPos,MovePos,BULLETTYPE_PLAYER);
				g_player.nSharp--;
				CutReload(1);
				PlaySound(SOUND_LABEL_SE_ZANGEKI);
			}
		}
		else if (g_player.nSharp <= 0)
		{//0�ɂȂ�����ؖ���߂�
			g_player.nCounterSharp++;
			if (g_player.nCounterSharp % 30 == 0)
			{
				g_player.nSharp = PLAYER_SHARP;
				g_player.nCounterSharp = 0;
				AddReload();
				PlaySound(SOUND_LABEL_SE_KEN);
			}
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();

	DecisionPlayer();
}

//=============================================================================
// �v���C���[�`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9	pDevice;	//�f�o�C�X�ւ̃|�C���^

	if (g_player.bDisp == true)
	{
		//�f�o�C�X���擾����
		pDevice = GetDevice();

		//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayer);

		if (g_player.state != PLAYERSTATE_APPEAR)
		{// �o�����Ă��΂炭����
		 // �v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				2);
		}
		else if (g_player.state == PLAYERSTATE_APPEAR && g_player.nCounterState % 2 == 0)
		{// �o�����ĊԂ��Ȃ�
		 // �v���C���[�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				2);
		}
	}
}
//=============================================================================
// �v���C���[�̓G�ڐG����
//=============================================================================
void DecisionPlayer(void)
{
	Enemy *pEnemy;
	int nCntEnemy;
	// �G�̎擾
	pEnemy = GetEnemy();
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{// �G�̐������J��Ԃ�
		if (pEnemy[nCntEnemy].bUse == true)
		{// �G���g�p����Ă���
			if (g_player.pos.x + PLAYER_SIZE > pEnemy[nCntEnemy].pos.x - 40 && g_player.pos.x - PLAYER_SIZE	  < pEnemy[nCntEnemy].pos.x + 40
				&& g_player.pos.y + PLAYER_SIZE	 > pEnemy[nCntEnemy].pos.y - 40 && g_player.pos.y - PLAYER_SIZE < pEnemy[nCntEnemy].pos.y + 40)
			{// �v���C���[���G�ɓ�����
				if (g_player.bDisp == true)
				{
					HitPlayer(1);
				}
				pEnemy[nCntEnemy].bUse = false;
			}
		}

	}
}
//=============================================================================
// �v���C���[�̃_���[�W����
//=============================================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{// ���C�t���O�ɂȂ�����
		if (g_player.bDisp == true)
		{// �v���C���[���`���Ԃ�������
			g_player.bDisp = false;
			g_player.nRemain--;
			g_player.state = PLAYERSTATE_DEATH;
			g_player.nCounterState = 60;
			CutRemain();
			for (int nCntParticle = 0; nCntParticle < 90; nCntParticle++)
			{// �p�[�e�B�N������
				g_pSpinPlayer += 0.05f;
				D3DXVECTOR3 movePar(0.0f, 0.0f, 0.0f);
				movePar.x = sinf(D3DX_PI * g_pSpinPlayer) * (rand() % 20 * 0.3f);
				movePar.y = cosf(D3DX_PI * g_pSpinPlayer) * (rand() % 20 * 0.3f);
				SetParticle(g_player.pos, movePar, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 30.0f, rand() % 20);
			}
			PlaySound(SOUND_LABEL_SE_BOMB000);
		}
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMEGE;
		g_player.nCounterState = 20;			//�_���[�W��Ԃ̎���

		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N
		g_pVtxBuffPlayer->Unlock();
	}
	CutLife(1);
}

//=============================================================================
// �v���C���[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}