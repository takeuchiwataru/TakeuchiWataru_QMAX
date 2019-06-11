//=============================================================================
//
// �Q�[���t�F�[�h���� [gamefade.cpp]
// Author : ���� ����	Sato_Asumi
//
//=============================================================================
#include "gamefade.h"
#include "BG.h"
#include "start.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_POLYGON			(2)					//�`�悷��v���~�e�B�u�̐�
#define GAMEFADE_POS_X		(0)					//�w�i�̍���X���W
#define GAMEFADE_POS_Y		(0)					//�w�i�̍���Y���W
#define GAMEFADE_WHIDTH		(SCREEN_WIDTH)		//�w�i�̕�
#define GAMEFADE_HEIGHT		(SCREEN_HEIGHT)		//�w�i�̍���
#define GAMEFADE_SPEED		(0.03f)				//�t�F�[�h�̃X�s�[�h

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexGameFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureGameFade = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGameFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
GAMEFADE				g_fade;						// �t�F�[�h���
GAMESTATE				g_modeNext;					// ���̃��[�h
D3DXCOLOR				g_colorGameFade;			// �t�F�[�h�F

//=============================================================================
// ����������
//=============================================================================
void InitGameFade(GAMESTATE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_fade = GAMEFADE_IN;									//�t�F�[�h�C����Ԃɂ���
	g_modeNext = modeNext;								
	g_colorGameFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//�s������Ԃɂ���

	// ���_���̐ݒ�
	MakeVertexGameFade(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitGameFade(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGameFade != NULL)
	{
		g_pTextureGameFade->Release();
		g_pTextureGameFade = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGameFade != NULL)
	{
		g_pVtxBuffGameFade->Release();
		g_pVtxBuffGameFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateGameFade(void)
{
	bool pPause = GetGAMEPause();
	QUESTSTATE pQuestState = GetQuestState();

	if (g_fade != GAMEFADE_NONE)
	{
		if (g_fade == GAMEFADE_IN)				//�t�F�[�h�C���̏�ԏ���
		{
			g_colorGameFade.a -= GAMEFADE_SPEED;	//��ʂ𓧖��ɂ��Ă���

			if (g_colorGameFade <= 0.0f)
			{
				g_colorGameFade.a = 0.0f;		//0.0f�ɍĐݒ肷��
				g_fade = GAMEFADE_NONE;			//�������Ă��Ȃ���Ԃɂ���
			}
		}
		else if (g_fade == GAMEFADE_OUT)		//�t�F�[�h�A�E�g�̏�ԏ���
		{
			g_colorGameFade.a += GAMEFADE_SPEED;	//��ʂ�s�����ɂ��Ă���
			
			if (g_colorGameFade.a >= 1.0f)	
			{
				DeleteBG();						//�w�i������
				DeleteStart();					//�X�^�[�g�{�^��������
				g_colorGameFade.a = 1.0f;		//1.0f�ɐݒ肷��
				g_fade = GAMEFADE_IN;			//�t�F�[�h�C����Ԃɂ���

				//���[�h�ݒ�
				if (pPause == true || pQuestState == QUESTSTATE_CLEAR)
				{
					SetQuestState(QUESTSTATE_SEARCH);
				}
				else
				{
					SetQuestState(QUESTSTATE_MISSTION);
				}
				SetGameState(g_modeNext);
			}
		}

		// ���_�o�b�t�@�̏���ݒ�
		VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffGameFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorGameFade.a);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorGameFade.a);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorGameFade.a);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorGameFade.a);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffGameFade->Unlock();
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawGameFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffGameFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGameFade);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexGameFade(LPDIRECT3DDEVICE9 pDevice)
{
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffGameFade,
		NULL);

	// ���_�o�b�t�@�̏���ݒ�
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffGameFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(GAMEFADE_POS_X, GAMEFADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(GAMEFADE_POS_X + GAMEFADE_WHIDTH, GAMEFADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(GAMEFADE_POS_X, GAMEFADE_POS_Y + GAMEFADE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(GAMEFADE_POS_X + GAMEFADE_WHIDTH, GAMEFADE_POS_Y + GAMEFADE_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGameFade->Unlock();
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetGameFade(GAMESTATE modeNext)
{
	if (g_fade == GAMEFADE_NONE)
	{
		g_fade = GAMEFADE_OUT;									//�t�F�[�h�A�E�g��Ԃɂ���
		g_modeNext = modeNext;
		g_colorGameFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//������Ԃɂ���
	}
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
GAMEFADE GetGameFade(void)
{
	return g_fade;
}

