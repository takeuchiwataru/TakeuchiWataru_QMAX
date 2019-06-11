//=============================================================================
//
// �I����� [select.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "select.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "fade.h"
#include "gamefade.h"
#include "BG.h"
#include "flontpolygon.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_TEX			(5)		//�e�N�X�`���̍ő吔
#define	MAX_POLYGON		(5)		//�|���S���̍ő吔
#define MAX_QUEST		(3)		//�N�G�X�g�̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureSelect[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSelect = NULL;		//���_�o�b�t�@�ւ̃|�C���^
QUESTTYPE				g_QuestType = QUESTTYPE_MAX;	//�N�G�X�g�̏��
int						g_nSelectType;					//�I������Ă���^�C�v
Select					g_Select[MAX_POLYGON];			//���̍ő吔
bool					g_bTriggerStickSelect;

//=============================================================================
// ����������
//=============================================================================
void InitSelect(void)
{
	//�ϐ��錾
	int		nCntTex;
	int		nCntSelect;
	char	cTexName[MAX_TEX][48];		//�t�@�C�������i�[����

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (nCntSelect = 0; nCntSelect < MAX_POLYGON; nCntSelect++)
	{
		g_Select[nCntSelect].nTex = nCntSelect;

		if (nCntSelect == 0)
		{
			g_Select[nCntSelect].mode = BOTTUNMODE_SELECT;
		}
		else
		{
			g_Select[nCntSelect].mode = BOTTUNMODE_NOMAL;
		}
	}
	g_nSelectType = QUESTTYPE_TUTORIAL;		//�`���[�g���A���ɐݒ肷��
	g_bTriggerStickSelect = false;

	//�e�N�X�`���t�@�C�������i�[����
	wsprintf(&cTexName[0][0], "data\\TEXTURE\\botunn_tutorial.png");		//�`���[�g���A���{�^��
	wsprintf(&cTexName[1][0], "data\\TEXTURE\\misstion00.png");				//�N�G�X�g�P�{�^��
	wsprintf(&cTexName[2][0], "data\\TEXTURE\\misstion01.png");				//�N�G�X�g2�{�^��
	wsprintf(&cTexName[3][0], "data\\TEXTURE\\misstion02.png");				//�N�G�X�g3�{�^��
	wsprintf(&cTexName[4][0], "data\\TEXTURE\\bottun_title.png");			//�u�^�C�g���ցv�{�^��

	//�e�N�X�`���̓ǂݍ���
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &cTexName[nCntTex][0],
								  &g_pTextureSelect[nCntTex]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSelect,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSelect = 0; nCntSelect < MAX_POLYGON - 1; nCntSelect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(500.0f, 150.0f + (nCntSelect * 130.0f), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, 150.0f + (nCntSelect * 130.0f), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, 220.0f + (nCntSelect * 130.0f), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, 220.0f + (nCntSelect * 130.0f), 0.0f);

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

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(1000.0f, 650.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1250.0f, 650.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(1000.0f, 700.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1250.0f, 700.0f, 0.0f);

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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();

	//�w�i
	SetBG(1);

	QUESTCLEAR *pClearQuest = GetbClearQuest();

	for (int nCntQuest = 0; nCntQuest < MAX_QUEST; nCntQuest++)
	{
		if (pClearQuest[nCntQuest].bClear == true)
		{
			if (pClearQuest[nCntQuest].nScore > 45000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_A, D3DXVECTOR3(855.0f, 315.0f + (nCntQuest * 130.0f), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100.0f, 100.0f);
			}
			else if (pClearQuest[nCntQuest].nScore > 30000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_B, D3DXVECTOR3(855.0f, 315.0f + (nCntQuest * 130.0f), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100.0f, 100.0f);
			}
			else if (pClearQuest[nCntQuest].nScore > 10000)
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_C, D3DXVECTOR3(855.0f, 315.0f + (nCntQuest * 130.0f), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100.0f, 100.0f);
			}
			else
			{
				SetFlontPolygon(FLONTPOLYGONTEXTURE_QUESTSTAMP_D, D3DXVECTOR3(855.0f, 315.0f + (nCntQuest * 130.0f), 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100.0f, 100.0f);
			}
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitSelect(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureSelect[nCntTex] != NULL)
		{
			g_pTextureSelect[nCntTex]->Release();
			g_pTextureSelect[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffSelect != NULL)
	{
		g_pVtxBuffSelect->Release();
		g_pVtxBuffSelect = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSelect(void)
{
	//�ϐ��錾
	int nCntSelect;

	DIJOYSTATE pStick = GetStick();

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//�Q�[���t�F�[�h�����擾����
	GAMEFADE GameFade;
	GameFade = GetGameFade();

	//�t�F�[�h�����擾����
	FADE fade;
	fade = GetFade();

	//�J�[�\������
	if (fade == FADE_NONE && GameFade == GAMEFADE_NONE)
	{
		if ((GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_W) == true || ((pStick.rgdwPOV[0] == 0 || pStick.lY < -100) && g_bTriggerStickSelect == false)))
		{
			PlaySound(SOUND_LABEL_SE_SELECT);	//�T�E���h�Đ�
			g_nSelectType = (g_nSelectType + (QUESTTYPE_MAX - 1)) % QUESTTYPE_MAX;

			g_bTriggerStickSelect = true;
		}
		if ((GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_S) == true || ((pStick.rgdwPOV[0] == 18000 || pStick.lY > 100) && g_bTriggerStickSelect == false)))
		{
			PlaySound(SOUND_LABEL_SE_SELECT);	//�T�E���h�Đ�
			g_nSelectType = (g_nSelectType + 1) % QUESTTYPE_MAX;

			g_bTriggerStickSelect = true;
		}
	}

	if ((pStick.rgdwPOV[0] != 0 && pStick.rgdwPOV[0] != 18000) && (pStick.lY > -100 && pStick.lY < 100))
	{
		g_bTriggerStickSelect = false;
	}

	for (nCntSelect = 0; nCntSelect < MAX_POLYGON; nCntSelect++)
	{
		if (g_Select[nCntSelect].nTex == g_nSelectType)
		{
			g_Select[nCntSelect].mode = BOTTUNMODE_SELECT;
		}
		else
		{
			g_Select[nCntSelect].mode = BOTTUNMODE_NOMAL;
		}
	}

	//�I����ԏ���
	switch (g_nSelectType)
	{
	case QUESTTYPE_TUTORIAL:	//�`���[�g���A��

		if (GameFade != GAMEFADE_OUT)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
			{//�G���^�[�L�[������
				PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
				//SetQuestType(QUESTTYPE_TUTORIAL);
				SetShowTutorial(true);
			}
		}
		break;

	case QUESTTYPE_FIRST:		//�N�G�X�g�P
		if (GameFade != GAMEFADE_OUT)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
			{//�G���^�[�L�[������
				PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
				SetQuestType(QUESTTYPE_FIRST);
			}
		}
		break;

	case QUESTTYPE_SECOND:		//�N�G�X�g2
		if (GameFade != GAMEFADE_OUT)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
			{//�G���^�[�L�[������
				PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
				SetQuestType(QUESTTYPE_SECOND);
			}
		}
		break;

	case QUESTTYPE_THIRD:		//�N�G�X�g3
		if (GameFade != GAMEFADE_OUT)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
			{//�G���^�[�L�[������
				PlaySound(SOUND_LABEL_SE_DECIDE);	//���艹
				SetQuestType(QUESTTYPE_THIRD);
			}
		}
		break;

	case QUESTTYPE_TITLE:		//�^�C�g��
								//�t�F�[�h���[�h�ݒ�
		if (fade != FADE_OUT)
		{
			if (GetKeyboardTrigger(DIK_RETURN) == true || GetButtonTrigger(2) == true)
			{//�G���^�[�L�[������
				PlaySound(SOUND_LABEL_SE_DECIDE);		//���艹
				SetQuestType(QUESTTYPE_TITLE);
				StopSound(SOUND_LABEL_BGM_TUTORIAL);	//�T�E���h��~
			}
		}
		break;
	}

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSelect->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntSelect = 0; nCntSelect < MAX_POLYGON; nCntSelect++)
	{
		switch (g_Select[nCntSelect].mode)
		{
		case BOTTUNMODE_NOMAL:

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			break;

		case BOTTUNMODE_SELECT:

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSelect->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSelect(void)
{
	//�ϐ��錾
	int nCntSelect;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffSelect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntSelect = 0; nCntSelect < MAX_POLYGON; nCntSelect++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureSelect[g_Select[nCntSelect].nTex]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
							   nCntSelect * 4,			//�J�n���钸�_�̃C���f�b�N�X
							   2);						//�v���~�e�B�u�̐�
	}
}