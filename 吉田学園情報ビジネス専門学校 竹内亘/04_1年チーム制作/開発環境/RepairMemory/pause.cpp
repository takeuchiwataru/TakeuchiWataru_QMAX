//=============================================================================
//
// �|�[�Y��� [pause.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "pause.h"
#include "main.h"
#include "input.h"
#include "sound.h"
#include "game.h"
#include "fade.h"
#include "gamefade.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_POLYGON		(5)		//�|���S���̍ő吔
#define MAX_TEX			(4)		//�e�N�X�`���̍ő吔

//�䎆
#define STAND_WHIDTH	(450)										//�w�i�̕�
#define STAND_HEIGHT	(500)										//�w�i�̍���
#define STAND_POS_X		((SCREEN_WIDTH / 2) - (STAND_WHIDTH / 2))	//�w�i�̍���X���W
#define STAND_POS_Y		((SCREEN_HEIGHT / 2) - (STAND_HEIGHT / 2))	//�w�i�̍���Y���W

//�R���e�j���[�{�^��
#define CONTINUE_WHIDTH		(350)											//�w�i�̕�
#define CONTINUE_HEIGHT		(70)											//�w�i�̍���
#define CONTINUE_POS_X		((SCREEN_WIDTH / 2) - (CONTINUE_WHIDTH / 2))	//�w�i�̍���X���W
#define CONTINUE_POS_Y		(230)											//�w�i�̍���Y���W

//���g���C�{�^��
#define RETRY_WHIDTH		(250)											//�w�i�̕�
#define RETRY_HEIGHT		(80)											//�w�i�̍���
#define RETRY_POS_X			((SCREEN_WIDTH / 2) - (RETRY_WHIDTH / 2))		//�w�i�̍���X���W
#define RETRY_POS_Y			(345)											//�w�i�̍���Y���W

//�N�C�b�g�{�^��
#define QUIT_WHIDTH			(250)										//�w�i�̕�
#define QUIT_HEIGHT			(80)										//�w�i�̍���
#define QUIT_POS_X			((SCREEN_WIDTH / 2) - (QUIT_WHIDTH / 2))	//�w�i�̍���X���W
#define QUIT_POS_Y			(460)										//�w�i�̍���Y���W

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9			g_pTexturePause[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffPause = NULL;			//���_�o�b�t�@�ւ̃|�C���^
int							g_SelectMode;					//�I������Ă��郂�[�h
Pause						g_Pause[MAX_POLYGON];			//���ݒ�
int							g_PauseTime;					//���ԃJ�E���^�[
bool						g_bTriggerStickPause;

//=============================================================================
// ����������
//=============================================================================
void InitPause(void)
{
	//�ϐ��錾
	int		nCntTex;
	char	cTexName[MAX_TEX][48];		//�t�@�C�������i�[����

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	g_Pause[0].nTex = 0;						//�e�N�X�`���̐ݒ�
	g_Pause[1].nTex = 0;
	g_Pause[2].nTex = 1;
	g_Pause[3].nTex = 2;
	g_Pause[4].nTex = 3;

	g_Pause[0].state = BOTTUNSTATE_NONE;		//�{�^���̏�Ԑݒ�
	g_Pause[1].state = BOTTUNSTATE_NONE;
	g_Pause[2].state = BOTTUNSTATE_SELECT;
	g_Pause[3].state = BOTTUNSTATE_NOMAL;
	g_Pause[4].state = BOTTUNSTATE_NOMAL;

	g_SelectMode = PAUSESTATE_CONTINUE;			//�����Ԃ̐ݒ�
	g_PauseTime = 0;							//���ԃJ�E���^�[
	g_bTriggerStickPause = false;

	//�e�N�X�`���t�@�C�������i�[����
	wsprintf(&cTexName[0][0], "data\\TEXTURE\\pause100.png");		//�䎆
	wsprintf(&cTexName[1][0], "data\\TEXTURE\\pause000.png");		//�R���e�j���[�{�^��
	wsprintf(&cTexName[2][0], "data\\TEXTURE\\pause001.png");		//���g���C�{�^��
	wsprintf(&cTexName[3][0], "data\\TEXTURE\\pause002.png");		//�N�C�b�g�{�^��

	//�e�N�X�`���̓ǂݍ���
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &cTexName[nCntTex][0],
								  &g_pTexturePause[nCntTex]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffPause,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

//�w�i�̍�-----------------------------------------------------------

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

//�䎆-----------------------------------------------------------

	//���_���W�̐ݒ�
	pVtx[4].pos = D3DXVECTOR3(STAND_POS_X, STAND_POS_Y, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(STAND_POS_X + STAND_WHIDTH, STAND_POS_Y, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(STAND_POS_X, STAND_POS_Y + STAND_HEIGHT, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(STAND_POS_X + STAND_WHIDTH, STAND_POS_Y + STAND_HEIGHT, 0.0f);

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

//�R���e�j���[�{�^��-----------------------------------------------------------

	//���_���W�̐ݒ�
	pVtx[8].pos = D3DXVECTOR3(CONTINUE_POS_X, CONTINUE_POS_Y, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(CONTINUE_POS_X + CONTINUE_WHIDTH, CONTINUE_POS_Y, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(CONTINUE_POS_X, CONTINUE_POS_Y + CONTINUE_HEIGHT, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(CONTINUE_POS_X + CONTINUE_WHIDTH, CONTINUE_POS_Y + CONTINUE_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

//���g���C�{�^��-----------------------------------------------------------

	//���_���W�̐ݒ�
	pVtx[12].pos = D3DXVECTOR3(RETRY_POS_X, RETRY_POS_Y, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(RETRY_POS_X + RETRY_WHIDTH, RETRY_POS_Y, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(RETRY_POS_X, RETRY_POS_Y + RETRY_HEIGHT, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(RETRY_POS_X + RETRY_WHIDTH, RETRY_POS_Y + RETRY_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[12].rhw = 1.0f;
	pVtx[13].rhw = 1.0f;
	pVtx[14].rhw = 1.0f;
	pVtx[15].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[12].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(1.0f, 1.0f);

//�N�C�b�g�{�^��-----------------------------------------------------------

//���_���W�̐ݒ�
	pVtx[16].pos = D3DXVECTOR3(QUIT_POS_X, QUIT_POS_Y, 0.0f);
	pVtx[17].pos = D3DXVECTOR3(QUIT_POS_X + QUIT_WHIDTH, QUIT_POS_Y, 0.0f);
	pVtx[18].pos = D3DXVECTOR3(QUIT_POS_X, QUIT_POS_Y + QUIT_HEIGHT, 0.0f);
	pVtx[19].pos = D3DXVECTOR3(QUIT_POS_X + QUIT_WHIDTH, QUIT_POS_Y + QUIT_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[16].rhw = 1.0f;
	pVtx[17].rhw = 1.0f;
	pVtx[18].rhw = 1.0f;
	pVtx[19].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[16].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[17].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[18].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[19].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[16].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[17].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[18].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[19].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitPause(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTexturePause[nCntTex] != NULL)
		{
			g_pTexturePause[nCntTex]->Release();
			g_pTexturePause[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePause(void)
{
	//�ϐ��錾
	int nCntPause;

	DIJOYSTATE pStick = GetStick();

	//�t�F�[�h�����擾����
	FADE fade;
	fade = GetFade();

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//�J�[�\������
	if ((GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_W) == true || ((pStick.rgdwPOV[0] == 0 || pStick.lY < -100) && g_bTriggerStickPause == false)))
	{
		PlaySound(SOUND_LABEL_SE_SELECT);	//�T�E���h�Đ�
		g_SelectMode = (g_SelectMode + (PAUSESTATE_MAX - 1)) % PAUSESTATE_MAX;

		g_bTriggerStickPause = true;
	}
	if ((GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_S) == true || ((pStick.rgdwPOV[0] == 18000 || pStick.lY > 100) && g_bTriggerStickPause == false)))
	{
		PlaySound(SOUND_LABEL_SE_SELECT);	//�T�E���h�Đ�
		g_SelectMode = (g_SelectMode + 1) % PAUSESTATE_MAX;

		g_bTriggerStickPause = true;
	}

	if ((pStick.rgdwPOV[0] != 0 && pStick.rgdwPOV[0] != 18000) && (pStick.lY > -100 && pStick.lY < 100))
	{
		g_bTriggerStickPause = false;
	}

	//�I������
	switch (g_SelectMode)
	{
	case PAUSESTATE_CONTINUE:

		//�{�^���̏�Ԑݒ�
		g_Pause[2].state = BOTTUNSTATE_SELECT;
		g_Pause[3].state = BOTTUNSTATE_NOMAL;
		g_Pause[4].state = BOTTUNSTATE_NOMAL;

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
			g_SelectMode = PAUSESTATE_MAX;
			g_Pause[2].state = BOTTUNSTATE_MAX;
			SetPause(false);
			g_Pause[2].state = BOTTUNSTATE_SELECT;
			g_SelectMode = PAUSESTATE_CONTINUE;
		}
		break;

	case PAUSESTATE_RETRY:

		//�{�^���̏�Ԑݒ�
		g_Pause[2].state = BOTTUNSTATE_NOMAL;
		g_Pause[3].state = BOTTUNSTATE_SELECT;
		g_Pause[4].state = BOTTUNSTATE_NOMAL;

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
			g_SelectMode = PAUSESTATE_MAX;
			g_Pause[3].state = BOTTUNSTATE_MAX;

			if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
			{
				//�t�F�[�h���[�h�ݒ�
				SetGameFade(GAMESTATE_QUESTSELECT);
				StopSound(SOUND_LABEL_BGM_GAME);	//�T�E���h��~
			}
		}
		break;

	case PAUSESTATE_QUIT:

		//�{�^���̏�Ԑݒ�
		g_Pause[2].state = BOTTUNSTATE_NOMAL;
		g_Pause[3].state = BOTTUNSTATE_NOMAL;
		g_Pause[4].state = BOTTUNSTATE_SELECT;

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
			g_SelectMode = PAUSESTATE_MAX;
			g_Pause[4].state = BOTTUNSTATE_MAX;

			if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
			{
				//�t�F�[�h���[�h�ݒ�
				SetFade(MODE_TITLE);
				StopSound(SOUND_LABEL_BGM_GAME);	//�T�E���h��~
			}
		}
		break;
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		switch (g_Pause[nCntPause].state)
		{
		case BOTTUNSTATE_NOMAL:

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			break;

		case BOTTUNSTATE_SELECT:

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;

		case BOTTUNSTATE_NONE:

			if (nCntPause == 0)
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f);
			}
			else
			{
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			break;

		case BOTTUNSTATE_MAX:

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPause(void)
{
	//�ϐ��錾
	int nCntPause;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntPause = 0; nCntPause < MAX_POLYGON; nCntPause++)
	{
		//�e�N�X�`���̐ݒ�
		if (nCntPause == 0)
		{
			pDevice->SetTexture(0, NULL);
		}
		else
		{
			pDevice->SetTexture(0, g_pTexturePause[g_Pause[nCntPause].nTex]);
		}

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
							   nCntPause * 4,			//�J�n���钸�_�̃C���f�b�N�X
							   2);						//�v���~�e�B�u�̐�
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
Pause * GetPause(void)
{
	return &g_Pause[0];
}

//=============================================================================
// ��Ԃ̐ݒ�
//=============================================================================
void SetPauseState(PAUSESTATE state)
{
	g_SelectMode = state;
}