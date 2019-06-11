//=============================================================================
//
// �N�G�X�g�t�F�[�h���� [questfade.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "questfade.h"
#include "BG.h"
#include "xenemy.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_POLYGON			(2)					//�`�悷��v���~�e�B�u�̐�
#define QUESTFADE_POS_X		(0)					//�w�i�̍���X���W
#define QUESTFADE_POS_Y		(0)					//�w�i�̍���Y���W
#define QUESTFADE_WHIDTH	(SCREEN_WIDTH)		//�w�i�̕�
#define QUESTFADE_HEIGHT	(SCREEN_HEIGHT)		//�w�i�̍���
#define QUESTFADE_SPEED		(0.03f)				//�t�F�[�h�̃X�s�[�h

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexQuestFade(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureQuestFade = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffQuestFade = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
QUESTFADE				g_fade;						// �t�F�[�h���
QUESTSTATE				g_QuestModeNext;			// ���̃��[�h
D3DXCOLOR				g_colorQuestFade;			// �t�F�[�h�F

//=============================================================================
// ����������
//=============================================================================
void InitQuestFade(QUESTSTATE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �l�̏�����
	g_fade = QUESTFADE_IN;									//�t�F�[�h�C����Ԃɂ���
	g_QuestModeNext = modeNext;								
	g_colorQuestFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//�s������Ԃɂ���

	// ���_���̐ݒ�
	MakeVertexQuestFade(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitQuestFade(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureQuestFade != NULL)
	{
		g_pTextureQuestFade->Release();
		g_pTextureQuestFade = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffQuestFade != NULL)
	{
		g_pVtxBuffQuestFade->Release();
		g_pVtxBuffQuestFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateQuestFade(void)
{
	if (g_fade != QUESTFADE_NONE)
	{
		if (g_fade == QUESTFADE_IN)				//�t�F�[�h�C���̏�ԏ���
		{
			g_colorQuestFade.a -= QUESTFADE_SPEED;	//��ʂ𓧖��ɂ��Ă���

			if (g_colorQuestFade <= 0.0f)
			{
				g_colorQuestFade.a = 0.0f;		//0.0f�ɍĐݒ肷��
				g_fade = QUESTFADE_NONE;			//�������Ă��Ȃ���Ԃɂ���
			}
		}
		else if (g_fade == QUESTFADE_OUT)		//�t�F�[�h�A�E�g�̏�ԏ���
		{
			g_colorQuestFade.a += QUESTFADE_SPEED;	//��ʂ�s�����ɂ��Ă���
			
			if (g_colorQuestFade.a >= 1.0f)	
			{
				DeleteXEnemy();					//�Z�l������
				DeleteBG();						//�w�i������
				g_colorQuestFade.a = 1.0f;		//1.0f�ɐݒ肷��
				g_fade = QUESTFADE_IN;			//�t�F�[�h�C����Ԃɂ���

				//���[�h�ݒ�
				SetQuestState(g_QuestModeNext);
			}
		}

		// ���_�o�b�t�@�̏���ݒ�
		VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffQuestFade->Lock(0, 0, (void**)&pVtx, 0);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorQuestFade.a);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorQuestFade.a);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorQuestFade.a);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_colorQuestFade.a);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffQuestFade->Unlock();
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawQuestFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffQuestFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureQuestFade);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexQuestFade(LPDIRECT3DDEVICE9 pDevice)
{
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffQuestFade,
		NULL);

	// ���_�o�b�t�@�̏���ݒ�
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffQuestFade->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(QUESTFADE_POS_X, QUESTFADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(QUESTFADE_POS_X + QUESTFADE_WHIDTH, QUESTFADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(QUESTFADE_POS_X, QUESTFADE_POS_Y + QUESTFADE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(QUESTFADE_POS_X + QUESTFADE_WHIDTH, QUESTFADE_POS_Y + QUESTFADE_HEIGHT, 0.0f);

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
	g_pVtxBuffQuestFade->Unlock();
}

//=============================================================================
// �t�F�[�h�̐ݒ�
//=============================================================================
void SetQuestFade(QUESTSTATE modeNext)
{
	if (g_fade == QUESTFADE_NONE)
	{
		g_fade = QUESTFADE_OUT;									//�t�F�[�h�A�E�g��Ԃɂ���
		g_QuestModeNext = modeNext;
		g_colorQuestFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//������Ԃɂ���
	}
}

//=============================================================================
// �t�F�[�h�̎擾
//=============================================================================
QUESTFADE GetQuestFade(void)
{
	return g_fade;
}

