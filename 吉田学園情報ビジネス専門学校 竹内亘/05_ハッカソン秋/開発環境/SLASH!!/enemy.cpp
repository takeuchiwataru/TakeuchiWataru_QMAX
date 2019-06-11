//=============================================================================
//
// �G���� [enemy.cpp]
// Author : Mikiya Meguro
//
//=============================================================================
#include "enemy.h"
#include "attackgauge.h"
#include "particle.h"
#include "input.h"
#include "bullet.h"
#include "player.h"
#include "score.h"
#include "game.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ENEMY		(4)				// �G�̎��
#define POLYGON_POS_X		(40)			//���_���WX�̈ړ���
#define POLYGON_POS_Y		(40)			//���_���WY�̈ړ���
#define COUNTER_ANIM_RESET	(2)				//�A�j���[�V�����J�E���g���Z�b�g
#define TEX_POS_X_INIT		(0.5f)			//�e�N�X�`�����WU�̏����ʒu
#define TEX_POS_Y_INIT		(1.0f)			//�e�N�X�`�����WV�̏����ʒu
#define TEX_LEFT			(0.0f)			//�e�N�X�`�����WU��
#define TEX_RIGHT			(0.5f)			//�e�N�X�`�����WU�E
#define TEX_TOP				(0.0f)			//�e�N�X�`�����WV��
#define TEX_BOT				(1.0f)			//�e�N�X�`�����WV��
#define MOVE_ENEMY			(2.0f)			//�G�̈ړ���
#define MOVE_X_ENEMY		(5.0f)			//�G�̈ړ���
#define MOVE_RANDOM_ENEMY	(0.3f)			//�G�̈ړ���

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureEnemy[MAX_TYPE_ENEMY] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Enemy g_aEnemy[MAX_ENEMY];										// �G�̏��	
int		g_nYpos = 0;
int		g_nNumEnemy;										    // �G�̑���
float   g_Randam;                                              // �����_���ړ��Ɏg��
float   g_AngelX;                                              // �����_���ړ��Ɏg��
float   g_AngelY;                                              // �����_���ړ��Ɏg��
int     g_randCounter[MAX_ENEMY];                              // �����_���ړ��Ɏg��
bool    g_randFinish[MAX_ENEMY];
D3DXVECTOR3 MovePosEnemy(0.0f, 0.0f, 0.0f);
float   g_pSpinEnemy = 0.75f;                                 // �p�[�e�B�N���Ɏg�p

//=============================================================================
// ����������
//=============================================================================
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	
	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �G�̏��̏�����
	for(int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].bUse = false;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nCounterAnim = 0;
		g_aEnemy[nCntEnemy].nPatternAnim = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nLife = 1;
		g_aEnemy[nCntEnemy].nCntWall = 0;
		g_aEnemy[nCntEnemy].nCunterStop = 0;
		g_aEnemy[nCntEnemy].nRandomMove = 0;
		g_randCounter[nCntEnemy] = 0;
		g_randFinish[nCntEnemy] = false;
	}

	// �e�N�X�`���̓ǂݍ���(�S�̕�)
	D3DXCreateTextureFromFile(pDevice,
	"data\\TEXTURE\\enemy000.png",
	&g_apTextureEnemy[0]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy001.png",
		&g_apTextureEnemy[1]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy002.png",
		&g_apTextureEnemy[2]);

	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\enemy003.png",
		&g_apTextureEnemy[3]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;
	int nCntEnemy;

	// ���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&g_pVtxBuffEnemy,
									NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);

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
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();

	g_nNumEnemy = 0;	//�G�̑������N���A
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_ENEMY; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (g_apTextureEnemy[nCntTex] != NULL)
		{
			g_apTextureEnemy[nCntTex]->Release();
			g_apTextureEnemy[nCntTex] = NULL;
		}
	}
	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	int nCntEnemy;
	float fMove = 1;
	float fEnemyKakudo;
	float fEnemyMoveX;
	float fEnemyMoveY;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{

		if (g_aEnemy[nCntEnemy].bUse == true)	//�G���g�p��
		{
			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:
			{//�ʒu�̍X�V
				VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
									//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
				g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
				//pVtx += (nCntEnemy * 4);	//���_�f�[�^�̃|�C���^��4���i�߂�	

				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffEnemy->Unlock();
				break;
			}
			case ENEMYSTATE_DAMAGE:
			{
				g_aEnemy[nCntEnemy].nCounterState--;
				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					//�ʒu�̍X�V
					VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
										//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
					g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
					pVtx += (nCntEnemy * 4);	//���_�f�[�^�̃|�C���^��4���i�߂�	
					//���_�J���[
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

					//���_�o�b�t�@���A�����b�N����
					g_pVtxBuffEnemy->Unlock();
				}
				break;
			}
			}
			//�W�O�U�O�ړ��L����
			if (g_aEnemy[nCntEnemy].nType == 0)
			{
				//�ʒu�X�V
				g_aEnemy[nCntEnemy].move.x = 1 * g_aEnemy[nCntEnemy].fMoveEnemyX;
				g_aEnemy[nCntEnemy].move.y = 1 * g_aEnemy[nCntEnemy].fMoveEnemyY;

				//��ʊO�ɍs���Ȃ��悤��
				if (g_aEnemy[nCntEnemy].pos.y > SCREEN_HEIGHT - POLYGON_POS_Y)
				{
					g_aEnemy[nCntEnemy].fMoveEnemyY = -(1.0f);
				}
				else if (g_aEnemy[nCntEnemy].pos.y < 0.0f + POLYGON_POS_Y)
				{
					g_aEnemy[nCntEnemy].fMoveEnemyY = 1.0f;
				}
				if (g_aEnemy[nCntEnemy].pos.x > SCREEN_WIDTH - POLYGON_POS_X)
				{
					g_aEnemy[nCntEnemy].fMoveEnemyX = -(MOVE_X_ENEMY);
					g_aEnemy[nCntEnemy].nCntWall += 1;
				}
				else if (g_aEnemy[nCntEnemy].pos.x < 0 + POLYGON_POS_X)
				{
					g_aEnemy[nCntEnemy].fMoveEnemyX = MOVE_X_ENEMY;
					g_aEnemy[nCntEnemy].nCntWall += 1;
				}
				if (g_aEnemy[nCntEnemy].nCntWall > 3)
				{
					//�v���C���[�̎擾
					Player *pPlayer;
					pPlayer = GetPlayer();

					//�v���C���[�Ƃ̋��������߂�
					fEnemyMoveX = g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x;
					fEnemyMoveY = g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y;
					//�p�x�����߂�
					fEnemyKakudo = atan2f(fEnemyMoveX, fEnemyMoveY);

					D3DXVECTOR3 MovePosEnemy(0.0f, 0.0f, 0.0f);
					//�ړ��ʂ�ݒ�
					MovePosEnemy.x += sinf(fEnemyKakudo) * -5.0f;
					MovePosEnemy.y += cosf(fEnemyKakudo) * -5.0f;
					g_aEnemy[nCntEnemy].move = MovePosEnemy;
				}
			}
			//���i(�ǔ�)�L����
			else if (g_aEnemy[nCntEnemy].nType == 1)
			{
				g_aEnemy[nCntEnemy].move.y = 1 * g_aEnemy[nCntEnemy].fMoveEnemyY;
				//�v���C���[�̎擾
				Player *pPlayer;
				pPlayer = GetPlayer();

				//�v���C���[�Ƃ̋��������߂�
				fEnemyMoveX = g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x;
				fEnemyMoveY = g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y;
				//�p�x�����߂�
				fEnemyKakudo = atan2f(fEnemyMoveX, fEnemyMoveY);

				D3DXVECTOR3 MovePosEnemy(0.0f, 0.0f, 0.0f);
				//�ړ��ʂ�ݒ�
				MovePosEnemy.x += sinf(fEnemyKakudo) * -5.0f;
				MovePosEnemy.y += cosf(fEnemyKakudo) * -5.0f;
				g_aEnemy[nCntEnemy].move = MovePosEnemy;


			}
			//�ꎞ��~�L����
			else if (g_aEnemy[nCntEnemy].nType == 2)
			{
				g_aEnemy[nCntEnemy].nCunterStop++;
				g_aEnemy[nCntEnemy].move.y = 1 * g_aEnemy[nCntEnemy].fMoveEnemyY;

				//�v���C���[�̎擾
				Player *pPlayer;
				pPlayer = GetPlayer();

				//�v���C���[�Ƃ̋��������߂�
				fEnemyMoveX = g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x;
				fEnemyMoveY = g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y;
				//�p�x�����߂�
				fEnemyKakudo = atan2f(fEnemyMoveX, fEnemyMoveY);

				D3DXVECTOR3 MovePosEnemy(0.0f, 0.0f, 0.0f);
				//�ړ��ʂ�ݒ�
				MovePosEnemy.x += sinf(fEnemyKakudo) * -5.0f;
				MovePosEnemy.y += cosf(fEnemyKakudo) * -5.0f;
				g_aEnemy[nCntEnemy].move = MovePosEnemy;
				//�ꎞ��~
				if (g_aEnemy[nCntEnemy].nCunterStop >= rand() % 60)
				{
					g_aEnemy[nCntEnemy].move.y = 0;
					g_aEnemy[nCntEnemy].move.x = 0;
					if (g_aEnemy[nCntEnemy].nCunterStop >= 120)
					{//�����o��
						g_aEnemy[nCntEnemy].nCunterStop = 0;
					}
				}
			}
			//�����_���ړ��L����
			else if (g_aEnemy[nCntEnemy].nType == 3)
			{
				if(g_aEnemy[nCntEnemy].nRandomCnt >= 120)
				{
					g_aEnemy[nCntEnemy].nRandomCnt = 0;
				}
				if (g_aEnemy[nCntEnemy].nRandomCnt % 60 == 0 && g_randFinish[nCntEnemy] == false)
				{// �܂������_���ړ�����
					g_AngelX = rand() % SCREEN_WIDTH + 0.0f;
					g_AngelY = rand() % SCREEN_HEIGHT + 300.0f;

					Player *pPlayer;
					pPlayer = GetPlayer();

					g_Randam = atan2f(g_AngelX - pPlayer->pos.x, g_AngelY - pPlayer->pos.y);

					if (g_Randam > D3DX_PI)
					{// �p�x���~�����̒l�𒴂��Ă��܂���
						g_Randam -= D3DX_PI * 2.0f;
					}
					if (g_Randam < -D3DX_PI)
					{// �p�x���~�����̒l�𒴂��Ă��܂���
						g_Randam += D3DX_PI * 2.0f;
					}
					g_randCounter[nCntEnemy]++;
			
					if (g_randCounter[nCntEnemy] >= rand() % 6 + 4)
					{// �����_���I���
						g_randFinish[nCntEnemy] = true;
					}
					MovePosEnemy.x = sinf(g_Randam) * 5.0f;
					MovePosEnemy.y = cosf(g_Randam) * 5.0f;
				}
				else if (g_randFinish[nCntEnemy] == true)
				{// ���������_���ړ����Ȃ�
					//�v���C���[�̎擾
					Player *pPlayer;
					pPlayer = GetPlayer();

					//�v���C���[�Ƃ̋��������߂�
					fEnemyMoveX = g_aEnemy[nCntEnemy].pos.x - pPlayer->pos.x;
					fEnemyMoveY = g_aEnemy[nCntEnemy].pos.y - pPlayer->pos.y;
					//�p�x�����߂�
					fEnemyKakudo = atan2f(fEnemyMoveX, fEnemyMoveY);
					//�ړ��ʂ�ݒ�
					MovePosEnemy.x = sinf(fEnemyKakudo) * -5.0f;
					MovePosEnemy.y = cosf(fEnemyKakudo) * -5.0f;
					g_aEnemy[nCntEnemy].move = MovePosEnemy;
				}
				g_aEnemy[nCntEnemy].move = MovePosEnemy;
				g_aEnemy[nCntEnemy].nRandomCnt++;
			}
			//��ʊO�ɍs���Ȃ��悤��
			if (g_aEnemy[nCntEnemy].pos.y > SCREEN_HEIGHT - POLYGON_POS_Y)
			{
				g_aEnemy[nCntEnemy].pos.y = SCREEN_HEIGHT - POLYGON_POS_Y;
			}
			if (g_aEnemy[nCntEnemy].pos.x > SCREEN_WIDTH - POLYGON_POS_X)
			{
				g_aEnemy[nCntEnemy].pos.x = SCREEN_WIDTH - POLYGON_POS_X;
			}
			if (g_aEnemy[nCntEnemy].pos.x < 0 + POLYGON_POS_X)
			{
				g_aEnemy[nCntEnemy].pos.x = 0 + POLYGON_POS_X;
			}

		}

		g_aEnemy[nCntEnemy].pos.x += g_aEnemy[nCntEnemy].move.x;
		g_aEnemy[nCntEnemy].pos.y += g_aEnemy[nCntEnemy].move.y;
		//�ʒu�̍X�V
		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
		//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += (nCntEnemy * 4);
		//���_���W�X�V
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
		//����
		g_aEnemy[nCntEnemy].move.x += (0.0f - g_aEnemy[nCntEnemy].move.x) * 0.25f;
		g_aEnemy[nCntEnemy].move.y += (0.0f - g_aEnemy[nCntEnemy].move.y) * 0.25f;
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();

	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEnemy;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{	
		if (g_aEnemy[nCntEnemy].bUse == true)	//�G���g�p����Ă���
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0 + (4 * nCntEnemy),	//�J�n���钸�_�̃C���f�b�N�X
				2); //�`�悷��v���~�e�B�u��
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType)
{
	int nCntEnemy;

	VERTEX_2D *pVtx;//���_���ւ̃|�C���^
	//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)	//�G���g�p����Ă��Ȃ�
		{
			g_aEnemy[nCntEnemy].pos = pos;

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y - POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + POLYGON_POS_X, g_aEnemy[nCntEnemy].pos.y + POLYGON_POS_Y, g_aEnemy[nCntEnemy].pos.z);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aEnemy[nCntEnemy].bUse = true;
			g_aEnemy[nCntEnemy].nCounterState = 0;
			g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
			//g_aEnemy[nCntEnemy].move = move;
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nLife = 1;
			g_aEnemy[nCntEnemy].nCntWall = 0;
			g_aEnemy[nCntEnemy].nCunterStop = 0;
			g_aEnemy[nCntEnemy].nRandomMove = 0;
			g_nNumEnemy++;		//�G�̑��������Z
			g_randFinish[nCntEnemy] = false;
			g_randCounter[nCntEnemy] = 0;
			break;
		}
		pVtx += 4;	//���_�f�[�^�̃|�C���^��4���i�߂�	
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEnemy->Unlock();
}

//=============================================================================
// �G�̎擾
//=============================================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//=============================================================================
// �G�̃_���[�W����
//=============================================================================
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;

	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{
		PlaySound(SOUND_LABEL_SE_BOMB000);
		g_aEnemy[nCntEnemy].bUse = false;
		AddAttackGauge(50);
		Player *pPlayer;
		pPlayer = GetPlayer();
		pPlayer->nCounterGauge += 50;
		for (int nCntParticle = 0; nCntParticle < 90; nCntParticle++)
		{// �p�[�e�B�N������
			g_pSpinEnemy += 0.05f;
			D3DXVECTOR3 movePar(0.0f, 0.0f, 0.0f);
			movePar.x = sinf(D3DX_PI * g_pSpinEnemy) * (rand() % 20 * 0.3f);
			movePar.y = cosf(D3DX_PI * g_pSpinEnemy) * (rand() % 20 * 0.3f);
			SetParticle(g_aEnemy[nCntEnemy].pos, movePar, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), rand() % 10 + 30.0f, rand() % 20);
		}
		AddScore(1000);
	}
	else
	{
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;	//�ǂ̂��炢�\�����邩		

		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^
		//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += (nCntEnemy * 4);	//���_�f�[�^�̃|�C���^��4���i�߂�	
		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffEnemy->Unlock();	
	}
}