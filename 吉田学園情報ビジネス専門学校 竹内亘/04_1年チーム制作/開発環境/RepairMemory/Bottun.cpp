//=============================================================================
//
// �{�^������ [Bottun.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "Bottun.h"
#include "main.h"
#include "sound.h"
#include "input.h"
#include "questfade.h"
#include "flontpolygon.h"
#include  "time.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	MAX_TEX			(1)		//�e�N�X�`���̍ő吔
#define	MAX_POLYGON		(1)		//�|���S���̍ő吔

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureBottun[MAX_TEX] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBottun = NULL;		//���_�o�b�t�@�ւ̃|�C���^
int						g_nBottunType;					//�I������Ă���^�C�v
Bottun					g_Bottun[MAX_POLYGON];			//���̍ő吔
int						g_nCntBottun;

//=============================================================================
// ����������
//=============================================================================
void InitBottun(void)
{
	//�ϐ��錾
	int		nCntTex;
	int		nCntBottun;
	char	cTexName[MAX_TEX][48];		//�t�@�C�������i�[����

	g_nCntBottun = 0;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��̏�����
	for (nCntBottun = 0; nCntBottun < MAX_POLYGON; nCntBottun++)
	{
		g_Bottun[nCntBottun].nTex = nCntBottun;
		g_Bottun[nCntBottun].bUse = false;
		g_Bottun[nCntBottun].type = BOTTUNTYPE_NOMAL;
	}
	g_nBottunType = QUESTTYPE_TUTORIAL;		//�`���[�g���A���ɐݒ肷��

	//�e�N�X�`���t�@�C�������i�[����
	wsprintf(&cTexName[0][0], "data\\TEXTURE\\bottun_atelier.png");		//[�H�[��]�̃{�^��

	//�e�N�X�`���̓ǂݍ���
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice,
								  &cTexName[nCntTex][0],
								  &g_pTextureBottun[nCntTex]);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBottun,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBottun->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBottun = 0; nCntBottun < MAX_POLYGON; nCntBottun++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(970.0f, 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1270.0f, 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(970.0f, 80.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1270.0f, 80.0f, 0.0f);

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
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBottun->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitBottun(void)
{
	//�ϐ��錾
	int nCntTex;

	//�e�N�X�`���̔j��
	for (nCntTex = 0; nCntTex < MAX_TEX; nCntTex++)
	{
		if (g_pTextureBottun[nCntTex] != NULL)
		{
			g_pTextureBottun[nCntTex]->Release();
			g_pTextureBottun[nCntTex] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBottun != NULL)
	{
		g_pVtxBuffBottun->Release();
		g_pVtxBuffBottun = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBottun(void)
{
	//�ϐ��錾
	int nCntBottun;

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBottun->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBottun = 0; nCntBottun < MAX_POLYGON; nCntBottun++)
	{
		if (g_Bottun[nCntBottun].bUse == true)
		{
			switch (g_Bottun[nCntBottun].type)
			{
			case BOTTUNTYPE_NOMAL:

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				break;

			case BOTTUNTYPE_SELECT:

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				if (g_nCntBottun == 0)
				{
					SetFlontPolygon(FLONTPOLYGONTEXTURE_PAZZLE_IN, D3DXVECTOR3(SCREEN_WIDTH + 400, SCREEN_HEIGHT / 2, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 700, 300);
					SetTimeState(TIMESTATE_STOP);
				}
				else if (g_nCntBottun == 120/*GetKeyboardTrigger(DIK_O) == true*/)
				{
					SetBottunType(BOTTUNTYPE_ENTER);
				}
				
				g_nCntBottun++;
				
				break;

			case BOTTUNTYPE_ENTER:

				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				//�N�G�X�g�t�F�[�h�̏����擾����
				QUESTFADE  pQuestFade;
				pQuestFade = GetQuestFade();

				if (pQuestFade != QUESTFADE_OUT)
				{//�p�Y�����[�h�ֈڍs����
					SetQuestFade(QUESTSTATE_PUZZLE);
				}
				break;
			}
		}
		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBottun->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBottun(void)
{
	//�ϐ��錾
	int nCntBottun;

	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBottun, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBottun = 0; nCntBottun < MAX_POLYGON; nCntBottun++)
	{
		if (g_Bottun[nCntBottun].bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBottun[g_Bottun[nCntBottun].nTex]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
				nCntBottun * 4,			//�J�n���钸�_�̃C���f�b�N�X
				2);						//�v���~�e�B�u�̐�
		}
	}
}

//=============================================================================
// �{�^���̏�Ԑݒ�
//=============================================================================
void SetBottunType(BOTTUNTYPE type)
{
	//�ϐ��錾
	int nCntBottun;

	for (nCntBottun = 0; nCntBottun < MAX_POLYGON; nCntBottun++)
	{
		if (g_Bottun[nCntBottun].bUse == true)
		{
			g_Bottun[nCntBottun].type = type;
		}
	}
}

//=============================================================================
// �{�^���̐ݒ�
//=============================================================================
void SetBottun(void)
{
	//�ϐ��錾
	int nCntBottun;

	for (nCntBottun = 0; nCntBottun < MAX_POLYGON; nCntBottun++)
	{
		if (g_Bottun[nCntBottun].bUse == false)
		{
			g_Bottun[nCntBottun].bUse = true;
			g_Bottun[nCntBottun].type = BOTTUNTYPE_NOMAL;
			break;
		}
	}
}

//=============================================================================
// �{�^��������
//=============================================================================
void DeleteBottun(void)
{
	//�ϐ��錾
	int nCntBottun;

	for (nCntBottun = 0; nCntBottun < MAX_POLYGON; nCntBottun++)
	{
		g_Bottun[nCntBottun].bUse = false;
	}

	g_nCntBottun = 0;
}