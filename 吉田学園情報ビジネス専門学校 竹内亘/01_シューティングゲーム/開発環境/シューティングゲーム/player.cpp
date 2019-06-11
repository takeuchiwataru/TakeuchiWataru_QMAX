//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �|���j
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "explosion.h"
#include "game.h"
#include "effect.h"
#include "sound.h"
#include "life.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define POLYGON_TEXTURENAME	"data/TEXTURE/player000.png"		//�e�N�X�`����
#define MAX_PARTTERN		(10)								//�p�^�[���̍ő�
#define POLYGON_COUNT		(1)									//�傫������ƃA�j���[�V�������x���Ȃ�
#define POLYGON_X			(600)								//�|���S����X���W
#define POLYGON_Y			(600)								//�|���S����Y���W
#define PLAYER_SIZE			(25)								//�v���C���[�̑傫��
#define PLAYER_SPEED		(2)									//�v���C���[�̑���
#define PLAYER_X            (640)								//�v���C���[��X���W
#define PLAYER_Y            (560)								//�v���C���[��X���W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
//D3DXVECTOR3 g_posPlayer;							//�v���C���[�̈ʒu
//D3DXVECTOR3 g_movePlayer;							//�v���C���[�̈ړ���
Player g_player;

//=============================================================================
// �v���C���[����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�v���C���[�̏��̏�����
	g_player.pos = D3DXVECTOR3(PLAYER_X, PLAYER_Y, 0.0f);
	g_player.state = PLAYERSTATE_NORMAL;
	g_player.nLife = 3;
	g_player.nCounterState = 0;
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.bDisp = true;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, POLYGON_TEXTURENAME, &g_pTexturePlayer);

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
	pVtx[0].pos = D3DXVECTOR3(POLYGON_X - PLAYER_SIZE, POLYGON_Y - PLAYER_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(POLYGON_X + PLAYER_SIZE, POLYGON_Y - PLAYER_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POLYGON_X - PLAYER_SIZE, POLYGON_Y + PLAYER_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(POLYGON_X + PLAYER_SIZE, POLYGON_Y + PLAYER_SIZE, 0.0f);

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
	case PLAYERSTATE_NORMAL:
		break;

	case PLAYERSTATE_DAMEGE:
		g_player.nCounterState--;

		if (g_player.nCounterState <= 0)
		{
			g_player.state = PLAYERSTATE_DAMEGE;

			//pVtx += (nCntEnemy * 4);	// �Y���̈ʒu�܂Ői�߂�

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
		{
			SetGameState(GAMESTATE_GAMEOVER);

			g_player.state = PLAYERSTATE_END;
		}
		return;
		break;
	}

	if (g_player.bDisp == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{//�������Ɉړ�
			if (GetKeyboardPress(DIK_W) == true)
			{//����Ɉړ�
				g_player.move.x += sinf(D3DX_PI * -0.75f) * PLAYER_SPEED;
				g_player.move.y += cosf(D3DX_PI * -0.75f) * PLAYER_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�����ړ�
				g_player.move.x += sinf(D3DX_PI * -0.25f) * PLAYER_SPEED;
				g_player.move.y += cosf(D3DX_PI * -0.25f) * PLAYER_SPEED;
			}
			else
			{//���ړ�
				g_player.move.x -= PLAYER_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{//�E�����Ɉړ�
			if (GetKeyboardPress(DIK_W) == true)
			{//�E��ړ�
				g_player.move.x += sinf(D3DX_PI * 0.75f) * PLAYER_SPEED;
				g_player.move.y += cosf(D3DX_PI * 0.75f) * PLAYER_SPEED;
			}
			else if (GetKeyboardPress(DIK_S) == true)
			{//�E���ړ�
				g_player.move.x += sinf(D3DX_PI * 0.25f) * PLAYER_SPEED;
				g_player.move.y += cosf(D3DX_PI * 0.25f) * PLAYER_SPEED;
			}
			else
			{//�E�ړ�
				g_player.move.x += PLAYER_SPEED;
			}
		}
		else if (GetKeyboardPress(DIK_W) == true)
		{//��Ɉړ�
			g_player.move.y += cosf(D3DX_PI * 1.0f) * PLAYER_SPEED;
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{//���Ɉړ�
			g_player.move.y += cosf(D3DX_PI * 0.0f) * PLAYER_SPEED;
		}

		if (GetKeyboardTrigger(DIK_SPACE) == true)
		{//�e�𔭎�
			SetBullet(g_player.pos, D3DXVECTOR3(0.0f, -10.0f, 0.0f), BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(-10.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(10.0f, 0.0f, 0.0f), BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(D3DX_PI * 0.75f), cosf(D3DX_PI * 0.75f), 0.0f) * 10, BULLETTYPE_PLAYER);
			SetBullet(g_player.pos, D3DXVECTOR3(sinf(D3DX_PI * -0.75f), cosf(D3DX_PI * -0.75f), 0.0f) * 10, BULLETTYPE_PLAYER);
			PlaySound(SOUND_LABEL_SE_SHOT001);
		}

		//else if (GetKeyboardTrigger(DIK_V) == true)
		//{//�ʃp�^�[���̒e�𔭎�

		//}

		if (g_player.pos.x > SCREEN_WIDTH + PLAYER_SIZE)
		{//�@�̂���ʊO�ɏo����t��
			g_player.pos.x = 0;
		}
		else if (g_player.pos.x < -PLAYER_SIZE)
		{//�@�̂���ʊO�ɏo����t��
			g_player.pos.x = SCREEN_WIDTH;
		}
		else if (g_player.pos.y < -PLAYER_SIZE)
		{//�@�̂���ʊO�ɏo����t��
			g_player.pos.y = SCREEN_HEIGHT;
		}
		else if (g_player.pos.y > SCREEN_HEIGHT + PLAYER_SIZE)
		{//�@�̂���ʊO�ɏo����t��
			g_player.pos.y = 0;
		}

		//�ʒu�X�V�i�ړ��j
		g_player.pos.x += g_player.move.x;
		g_player.pos.y += g_player.move.y;

		g_player.move.x += (0.0f - g_player.move.x) * 0.15f;
		g_player.move.y += (0.0f - g_player.move.y) * 0.15f;

		//���_���W���X�V
		pVtx[0].pos.x = g_player.pos.x - PLAYER_SIZE;	// �����X���W��ݒ�
		pVtx[0].pos.y = g_player.pos.y - PLAYER_SIZE;	// �����Y���W��ݒ�
		pVtx[1].pos.x = g_player.pos.x + PLAYER_SIZE;	// �E���X���W��ݒ�
		pVtx[1].pos.y = g_player.pos.y - PLAYER_SIZE;	// �E���Y���W��ݒ�
		pVtx[2].pos.x = g_player.pos.x - PLAYER_SIZE;	// ������X���W��ݒ�
		pVtx[2].pos.y = g_player.pos.y + PLAYER_SIZE;	// ������Y���W��ݒ�
		pVtx[3].pos.x = g_player.pos.x + PLAYER_SIZE;	// �E����X���W��ݒ�
		pVtx[3].pos.y = g_player.pos.y + PLAYER_SIZE;	// �E����Y���W��ݒ�

	}
	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffPlayer->Unlock();
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

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//=============================================================================
// �v���C���[�̃_���[�W����
//=============================================================================
void HitPlayer(int nDamage)
{
	g_player.nLife -= nDamage;

	if (g_player.nLife <= 0)
	{
		SetExplosion(g_player.pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		PlaySound(SOUND_LABEL_SE_EXPLOSION001);
		g_player.bDisp = false;
		g_player.state = PLAYERSTATE_DEATH;
		g_player.nCounterState = 60;
	}
	else
	{
		g_player.state = PLAYERSTATE_DAMEGE;
		PlaySound(SOUND_LABEL_SE_HIT002);
		g_player.nCounterState = 5;			//�_���[�W��Ԃ̎���

		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		//pVtx += (nCntEnemy * 4);	// �Y���̈ʒu�܂Ői�߂�

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