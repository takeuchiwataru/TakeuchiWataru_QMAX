//=============================================================================
//
// �����L���O��� [rank.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "rank.h"
#include "main.h"
//#include "sound.h"
#include "input.h"
#include "fade.h"
#include "game.h"
//#include "start.h"
//#include "ranking.h"
//#include "score.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define RANK_TEXTURENAME		"data\\TEXTURE\\score000.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define RANKLOGO_TEXTURENAME	"data\\TEXTURE\\score003.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define RANKTEXTURE_MAX			(2)									//�e�N�X�`���̍ő吔
#define RANK_POS_X				(0)									//�w�i�̍���X���W
#define RANK_POS_Y				(0)									//�w�i�̍���Y���W
#define RANK_WHIDTH				(SCREEN_WIDTH)						//�w�i�̕�
#define RANK_HEIGHT				(SCREEN_HEIGHT)						//�w�i�̍���

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9 g_pTextureRank[RANKTEXTURE_MAX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;				//���_�o�b�t�@�ւ̃|�C���^
int g_nCntTimeRank;											//�Q�[����ʐ؂�ւ��J�E���^�[

//=============================================================================
// ����������
//=============================================================================
void InitRank(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		RANK_TEXTURENAME,
		&g_pTextureRank[0]);

	D3DXCreateTextureFromFile(pDevice,
							  RANKLOGO_TEXTURENAME,
							  &g_pTextureRank[1]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * RANKTEXTURE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank,
		NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^
	g_nCntTimeRank = 0;		//�J�E���^�[�̏�����

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(RANK_POS_X, RANK_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RANK_POS_X + RANK_WHIDTH, RANK_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RANK_POS_X, RANK_POS_Y + RANK_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RANK_POS_X + RANK_WHIDTH, RANK_POS_Y + RANK_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_���W�̐ݒ�
	pVtx[4].pos = D3DXVECTOR3(350, 0, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(1000, 0, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(350, 150, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(1000, 150, 0.0f);

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();

	//�ϐ��Ăяo��
	//InitStart();		//�G���^�[�L�[
	//InitHighScore();	//�����L���O		

	//�G���^�[�L�[
	//SetEnter(D3DXVECTOR3(190.0f, 695.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
}

//=============================================================================
// �I������
//=============================================================================
void UninitRank(void)
{
	//�ϐ��錾
	int nCntRank;

	//�e�N�X�`���̔j��
	for (nCntRank = 0; nCntRank < RANKTEXTURE_MAX; nCntRank++)
	{
		if (g_pTextureRank[nCntRank] != NULL)
		{
			g_pTextureRank[nCntRank]->Release();
			g_pTextureRank[nCntRank] = NULL;
		}
	}
	
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	//UninitStart();		//�G���^�[�L�[
	//UninitHighScore();	//�����L���O
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRank(void)
{
	g_nCntTimeRank++;

	//�t�F�[�h�����擾����
	FADE g_fade;
	g_fade = GetFade();

	//����L�[�������ꂽ���ǂ���
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
		{
			//�T�E���h�Đ�
			//PlaySound(SOUND_LABEL_SE_ENTER);

			//�G���^�[�L�[�̏�ԕύX
			//SetPush(STARTSTRACT_ENTER);

			//�t�F�[�h���[�h�ݒ�
			SetFade(MODE_TITLE);
		}
	}
	if (g_nCntTimeRank == INTERVAL_TIME)
	{
		//�t�F�[�h���[�h�ݒ�
		SetFade(MODE_TITLE);
	}

	//SetHighScore(GetScore());

	//UpdateStart();		//�G���^�[�L�[
	//UpdateHighScore();	//�n�C�X�R�A
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawRank(void)
{
	//�ϐ��錾
	int nCntRank;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntRank = 0; nCntRank < RANKTEXTURE_MAX; nCntRank++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRank[nCntRank]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
							  nCntRank * 4,				//�J�n���钸�_�̃C���f�b�N�X
							  2);						//�v���~�e�B�u�̐�
	}

	//DrawStart();		//�G���^�[�L�[
	//DrawHighScore();	//�����L���O
}