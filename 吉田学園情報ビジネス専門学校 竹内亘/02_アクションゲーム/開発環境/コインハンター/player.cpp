//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : �|���j
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "block.h"
#include "item.h"
#include "sound.h"
#include "explosion.h"
#include "fade.h"
#include "game.h"

//#include "bullet.h"
//#include "explosion.h"
//#include "effect.h"
//#include "life.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PLAYER_TEXTURENAME	"data/TEXTURE/player000.png"		//�e�N�X�`���� 
#define MAX_PARTTERN		(10)								//�p�^�[���̍ő�
#define	POLYGON_X			(0)									//�|���S��X���W
#define POLYGON_Y			(0)									//�|���S��Y���W
#define POLYGON_COUNT		(1)									//�傫������ƃA�j���[�V�������x���Ȃ�
#define PLAYER_SIZE			(35)								//�v���C���[�̑傫��
#define PLAYER_SPEED		(1)									//�v���C���[�̑���
#define PLAYER_X            (640)								//�v���C���[��X���W
#define PLAYER_Y            (560)								//�v���C���[��X���W
#define MAX_LIFE			(10)								//���C�t�ő�\����
#define PLAYER_LIFE			(3)									//�v���C���[���C�t
#define PLAYER_REMAIN		(3)									//�v���C���[�̎c�@
#define PLAYER_SHARP		(5)									//�v���C���[�̌��̐ؖ�
#define PLAYER_JUMPPOWER	(15)								//�W�����v��
#define PLAYER_TEX			(4)									//�������̃e�N�X�`��
#define TEX_MOVE			(8)									//�e�N�X�`���̓����X�s�[�h
#define PLAYER_WIDTH		(20)								//�v���C���[�̕�
#define	PLAYER_HEIGHT		(45)								//�v���C���[�̍���


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�ւ̃|�C���^
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
	g_player.pos = D3DXVECTOR3(50,680,0.0f);
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.nCounterAnim = 0;
	g_player.nPatternAnim = 0;
	g_player.nDirectionMove = 0;
	g_player.col = D3DXCOLOR(0.0f, 0.0f, 0.0f,0.0f);
	g_player.state = PLAYERSTATE_NORMALL;
	g_player.nCounterState = 0;
	g_player.fHeight = PLAYER_HEIGHT;
	g_player.fWidth = PLAYER_WIDTH;
	//g_player.nLife = PLAYER_LIFE;
	//g_player.Remain = PLAYER_REMAIN;
	//g_player.nSharp = PLAYER_SHARP;
	//g_player.nCounterSharp = 0;
	//g_player.nCounterGauge = 0;
	g_player.bDisp = true;
	g_player.bJump = false;
	g_player.pBlock = NULL;

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
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y + 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y + 0, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

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
	g_player.nCounterAnim++;

	g_player.posold = g_player.pos;   // �O��̈ʒu��ۑ�

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//switch (g_player.state)
	//{
	//case PLAYERSTATE_NORMALL:
	//	break;

	//case PLAYERSTATE_DEATH:
	//	g_player.nCounterState--;

	//	if (g_player.pos.y < SCREEN_HEIGHT + PLAYER_SIZE)
	//	{
	//		SetGameState(GAMESTATE_GAMEOVER);
	//		g_player.state = PLAYERSTATE_END;
	//	}
	//	return;
	//	break;
	//}
	
	if (g_player.bDisp == true)
	{
		if (GetKeyboardPress(DIK_A) == true || GetKeyboardPress(DIK_LEFT) == true)
		{//�������Ɉړ�
			g_player.move.x -= PLAYER_SPEED;

			if (g_player.nDirectionMove == 0)
			{//����������E������
				g_player.nDirectionMove = 1;
				g_player.nCounterAnim = 0;
				g_player.nPatternAnim = 0;
			}
		}
		else if (GetKeyboardPress(DIK_D) == true || GetKeyboardPress(DIK_RIGHT) == true)
		{//�E�����Ɉړ�
			g_player.move.x += PLAYER_SPEED;

			if (g_player.nDirectionMove == 1)
			{//�E�������獶������
				g_player.nDirectionMove = 0;
				g_player.nCounterAnim = 0;
				g_player.nPatternAnim = 0;
			}
		}
	}

	//��ʂ̉������[�v������
	if (g_player.pos.x > SCREEN_WIDTH + PLAYER_SIZE)
	{//�v���C���[����ʊO�ɏo����t��
		g_player.pos.x = 0;
	}
	else if (g_player.pos.x < -PLAYER_SIZE)
	{//�v���C���[����ʊO�ɏo����t��
		g_player.pos.x = SCREEN_WIDTH;
	}

	////�t�F�[�h�̎擾
	//FADE *fade;
	//fade = GetFade();

	//if (g_player.pos.y < SCREEN_HEIGHT + PLAYER_SIZE)
	//{//�v���C���[����������
	//	SetFade(MODE_GAMEOVER);
	//}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{//�X�y�[�X�L�[�������ꂽ
		if (g_player.bJump == false)
		{
			g_player.bJump = true;					//�W�����v���g�p���Ă�
			g_player.move.y -= PLAYER_JUMPPOWER;	//�W�����v��
			PlaySound(SOUND_LABEL_SE_JUMP000);
		}
	}

	if (g_player.bJump == false)
	{//�W�����v���g�p���ĂȂ�
		if (g_player.move.x >= 1.0f || g_player.move.x <= -1.0f)
		{//�ړ����Ă�
			g_player.nCounterAnim++;
			if ((g_player.nCounterAnim % 7) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PLAYER_TEX;
			}
		}

		else if (g_player.move.x <= 1.0f && g_player.move.x >= -1.0f)
		{//�ړ����ĂȂ�
			if (g_player.nPatternAnim % 2 != 0)
			{
				g_player.nCounterAnim++;
				if ((g_player.nCounterAnim % 7) == 0)
				{
					g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PLAYER_TEX;
				}
			}
		}
	}
	else if (g_player.bJump == true)
	{//�W�����v���Ă�
		if(g_player.nPatternAnim % 2 == 0)
		{
			g_player.nCounterAnim++;
			if ((g_player.nCounterAnim % 7) == 0)
			{
				g_player.nPatternAnim = (g_player.nPatternAnim + 1) % PLAYER_TEX;
			}

		}
	}

	g_player.move.y += 0.5f;				//�d�͉��Z���Z
	g_player.pos.x += g_player.move.x;		//���ړ�
	g_player.pos.y += g_player.move.y;		//����

	//�u���b�N�Ƃ̓����蔻��
	if (CollisionBlock(&g_player.pos, &g_player.posold, &g_player.move, &g_player.fWidth, &g_player.fHeight, &g_player.pBlock) == true)
	{
		g_player.bJump = false;			//�g�p���ĂȂ�
	}
	else
	{
		if (g_player.bJump == false)
		{
			g_player.bJump = false;		//�g�p���Ă�
		}
	}

	//�A�C�e���Ƃ̓����蔻��
	if (CollisionItem(&g_player.pos, &g_player.posold, &g_player.move, &g_player.fWidth, &g_player.fHeight) == true)
	{
		g_player.bDisp = false;			//�g�p���ĂȂ�
	}
	else
	{
		if (g_player.bDisp == false)
		{
			g_player.bDisp = true;		//�g�p���Ă�
		}
	}


	//�ʒu�X�V�i�ړ��j
	g_player.pos.x += g_player.move.x;
	g_player.move.x += (0.0f - g_player.move.x) * 0.40f;

	//if (g_player.pos.y >= 680)
	//{//���}���u�Ŏg����
	//	g_player.pos.y = 680;
	//	g_player.move.y = 0.0f;
	//	g_player.bJump = false;
	//}

	//g_player.pos.y += g_player.move.y;
	//g_player.move.y += (0.0f - g_player.move.y) * 0.15f;

	//���_���W���X�V
	//pVtx[0].pos.x = g_player.pos.x - PLAYER_SIZE;	// �����X���W��ݒ�
	//pVtx[0].pos.y = g_player.pos.y - PLAYER_SIZE;	// �����Y���W��ݒ�
	//pVtx[1].pos.x = g_player.pos.x + PLAYER_SIZE;	// �E���X���W��ݒ�
	//pVtx[1].pos.y = g_player.pos.y - PLAYER_SIZE;	// �E���Y���W��ݒ�
	//pVtx[2].pos.x = g_player.pos.x - PLAYER_SIZE;	// ������X���W��ݒ�
	//pVtx[2].pos.y = g_player.pos.y + PLAYER_SIZE;	// ������Y���W��ݒ�
	//pVtx[3].pos.x = g_player.pos.x + PLAYER_SIZE;	// �E����X���W��ݒ�
	//pVtx[3].pos.y = g_player.pos.y + PLAYER_SIZE;	// �E����Y���W��ݒ�

	//if (g_player.pBlock != NULL)
	//{
	//	if (g_player.pBlock->nType == BLOCKTYPE_BERUTOKONBEA)
	//	{
	//		//�v���C���[�̈ʒu�X�V
	//	}
	//}

	//���_���W���X�V
	pVtx[0].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y - PLAYER_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_player.pos.x - PLAYER_WIDTH, g_player.pos.y + 0, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_player.pos.x + PLAYER_WIDTH, g_player.pos.y + 0, 0.0f);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f + ((g_player.nPatternAnim % PLAYER_TEX)* 0.25f), 0.0f + (g_player.nDirectionMove * 0.5f));
	pVtx[1].tex = D3DXVECTOR2(0.25f + ((g_player.nPatternAnim % PLAYER_TEX)* 0.25f), 0.0f + (g_player.nDirectionMove * 0.5f));
	pVtx[2].tex = D3DXVECTOR2(0.0f + ((g_player.nPatternAnim % PLAYER_TEX)* 0.25f), 0.5f + (g_player.nDirectionMove * 0.5f));
	pVtx[3].tex = D3DXVECTOR2(0.25f + ((g_player.nPatternAnim % PLAYER_TEX)* 0.25f), 0.5f + (g_player.nDirectionMove * 0.5f));

	pVtx += 4;	//���_�f�[�^���S���i�߂�

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

////=============================================================================
//// �v���C���[�̃_���[�W����
////=============================================================================
//void HitPlayer(int nDamage)
//{
//	g_player.nLife -= nDamage;
//
//	if (g_player.nLife <= 0)
//	{
//		//SetExplosion(g_player.pos, D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
//		g_player.bDisp = false;
//		g_player.state = PLAYERSTATE_DEATH;
//		g_player.nCounterState = 60;
//	}
//
//	else
//	{
//		g_player.state = PLAYERSTATE_DAMEGE;
//		g_player.nCounterState = 5;			//�_���[�W��Ԃ̎���
//
//		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
//
//		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
//		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);
//
//		//pVtx += (nCntEnemy * 4);	// �Y���̈ʒu�܂Ői�߂�
//
//		//���_�J���[
//		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
//
//		//���_�o�b�t�@���A�����b�N
//		g_pVtxBuffPlayer->Unlock();
//	}
//	//CutLife(1);
//}
//
//=============================================================================
// �v���C���[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_player;
}