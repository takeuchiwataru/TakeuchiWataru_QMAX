//=============================================================================
//
// �X�g�[���[��� [story.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "story.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "BG.h"
#include "start.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_TEX	(3)				//�ǂ݂��ރe�N�X�`���̍ő吔
#define MAX_POLYGON	(3)			//�w�i�̍ő吔
#define FADE_SPEED	(0.015f)		//�t�F�[�h�̃X�s�[�h

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureStory[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStory = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Story					g_Story[MAX_POLYGON];			//���ݒ�
STORYSTATE				g_state;						//��Ԑݒ�

//=============================================================================
// ����������
//=============================================================================
void InitStory(void)
{
	//�ϐ��錾
	int		nCntTex;
	int		nCntStory;
	char	cTexName[MAX_TEX][48];		//�t�@�C�������i�[����


	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (nCntStory = 0; nCntStory < MAX_POLYGON; nCntStory++)
	{
		g_Story[nCntStory].bAppear = false;
		g_Story[nCntStory].fCol = 0.0f;
		g_Story[nCntStory].nTexNum = nCntStory;
	}
	g_state = STORYSTATE_FADE;

	//�e�N�X�`���t�@�C�������i�[����
	wsprintf(&cTexName[0][0], "data\\TEXTURE\\story00.png");			//�P����
	wsprintf(&cTexName[1][0], "data\\TEXTURE\\story01.png");			//2����
	wsprintf(&cTexName[2][0], "data\\TEXTURE\\story02.png");			//3����

	//�e�N�X�`���̓ǂݍ���
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &cTexName[nCntTex][0],
								  &g_pTextureStory[nCntTex]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&g_pVtxBuffStory,
								NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStory->Lock(0, 0, (void**)&pVtx, 0);

//�P����------------------------------------------------------
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(100.0f, 150.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1200.0f, 150.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(100.0f, 270.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1200.0f, 270.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

//2����-----------------------------------------------------
		//���_���W�̐ݒ�
		pVtx[4].pos = D3DXVECTOR3(100.0f, 300.0f, 0.0f);
		pVtx[5].pos = D3DXVECTOR3(1200.0f, 300.0f, 0.0f);
		pVtx[6].pos = D3DXVECTOR3(100.0f, 420.0f, 0.0f);
		pVtx[7].pos = D3DXVECTOR3(1200.0f, 420.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[4].rhw = 1.0f;
		pVtx[5].rhw = 1.0f;
		pVtx[6].rhw = 1.0f;
		pVtx[7].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[7].tex = D3DXVECTOR2(1.0f, 1.0f);

//3����----------------------------------------------------
		//���_���W�̐ݒ�
		pVtx[8].pos = D3DXVECTOR3(100.0f, 450.0f, 0.0f);
		pVtx[9].pos = D3DXVECTOR3(1200.0f, 450.0f, 0.0f);
		pVtx[10].pos = D3DXVECTOR3(100.0f, 570.0f, 0.0f);
		pVtx[11].pos = D3DXVECTOR3(1200.0f, 570.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[8].rhw = 1.0f;
		pVtx[9].rhw = 1.0f;
		pVtx[10].rhw = 1.0f;
		pVtx[11].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[9].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[11].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStory->Unlock();

	//�ϐ��Ăяo��
	InitStart();		//�G���^�[�L�[

	//�w�i
	SetBG(0);
	
	//�G���^�[�L�[
	SetEnter(D3DXVECTOR3(190.0f, 695.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

//=============================================================================
// �I������
//=============================================================================
void UninitStory(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureStory[nCntTex] != NULL)
		{
			g_pTextureStory[nCntTex]->Release();
			g_pTextureStory[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStory != NULL)
	{
		g_pVtxBuffStory->Release();
		g_pVtxBuffStory = NULL;
	}

	UninitStart();		//�G���^�[�L�[
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStory(void)
{
	//�ϐ��錾
	int nCntStory;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStory->Lock(0, 0, (void**)&pVtx, 0);

	switch (g_state)
	{
	case STORYSTATE_FADE:
		if (g_Story[0].bAppear == false)
		{
			g_Story[0].fCol += FADE_SPEED;	//�����𕂂��オ�点��

			if (g_Story[0].fCol >= 1.0f)
			{
				g_Story[0].fCol = 1.0f;		//�l��߂�
				g_Story[0].bAppear = true;
			}

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[0].fCol);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[0].fCol);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[0].fCol);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[0].fCol);
		}

		if (g_Story[0].bAppear == true && g_Story[1].bAppear == false)
		{
			g_Story[1].fCol += FADE_SPEED;	//�����𕂂��オ�点��

			if (g_Story[1].fCol >= 1.0f)
			{
				g_Story[1].fCol = 1.0f;		//�l��߂�
				g_Story[1].bAppear = true;
			}

			//���_�J���[�̐ݒ�
			pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[1].fCol);
			pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[1].fCol);
			pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[1].fCol);
			pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[1].fCol);
		}

		if (g_Story[1].bAppear == true && g_Story[2].bAppear == false)
		{
			g_Story[2].fCol += FADE_SPEED;	//�����𕂂��オ�点��

			if (g_Story[2].fCol >= 1.0f)
			{
				g_Story[2].fCol = 1.0f;		//�l��߂�
				g_Story[2].bAppear = true;
			}

			//���_�J���[�̐ݒ�
			pVtx[8].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[2].fCol);
			pVtx[9].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[2].fCol);
			pVtx[10].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[2].fCol);
			pVtx[11].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Story[2].fCol);
		}

		//�S�Ă̕����\����ԂɂȂ�����
		if (g_Story[0].bAppear == true &&
			g_Story[1].bAppear == true &&
			g_Story[2].bAppear == true)
		{
			g_state = STORYSTATE_APPEAR;	//�\����Ԃɂ���
		}

		//�G���^�[�L�[����������
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
		{
			PlaySound(SOUND_LABEL_SE_DECIDE);	//�T�E���h�Đ�
			g_state = STORYSTATE_APPEAR;		//�\����Ԃɂ���
		}
		break;

	case STORYSTATE_APPEAR:

		for (nCntStory = 0; nCntStory < MAX_POLYGON; nCntStory++)
		{
			g_Story[nCntStory].bAppear = true;	//�\����Ԃɂ���
			
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�Y���̈ʒu�܂Ői�߂�
			pVtx += 4;
		}

		//�t�F�[�h�����擾����
		FADE fade;
		fade = GetFade();

		//����L�[�������ꂽ���ǂ���
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
		{
			if (fade != FADE_OUT)		//�t�F�[�h�A�E�g�����s����Ă��Ȃ��Ȃ�
			{
				PlaySound(SOUND_LABEL_SE_DECIDE);	//�T�E���h�Đ�
				SetPush(STARTSTRACT_ENTER);			//�X�^�[�g�{�^���̐ݒ�

				//�t�F�[�h���[�h�ݒ�
				SetFade(MODE_GAME);
			}
		}

		break;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStory->Unlock();

	UpdateStart();		//�G���^�[�L�[
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStory(void)
{
	//�ϐ��錾
	int nCntStory;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

									//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStory, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntStory = 0; nCntStory < MAX_POLYGON; nCntStory++)
	{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureStory[g_Story[nCntStory].nTexNum]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
								   nCntStory * 4,			//�J�n���钸�_�̃C���f�b�N�X
								   2);						//�v���~�e�B�u�̐�
	}

	DrawStart();		//�G���^�[�L�[
}