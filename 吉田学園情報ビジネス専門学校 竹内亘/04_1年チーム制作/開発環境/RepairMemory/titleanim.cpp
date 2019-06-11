//=============================================================================
//
// �^�C�g���A�j���[�V������� [titleanim.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "titleanim.h"
#include "main.h"
#include "input.h"
//#include "sound.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TITLEANIM_TEXTURENAME   "data\\TEXTURE\\titleanim.png"		//�ǂݍ��ރe�N�X�`���t�@�C��
#define TITLEANIM_POS_X			(75)								//�w�i�̍���X���W
#define TITLEANIM_POS_Y			(0)									//�w�i�̍���Y���W
#define TITLEANIM_WHIDTH		(SCREEN_WIDTH - 125)				//�w�i�̕�
#define TITLEANIM_HEIGHT		(SCREEN_HEIGHT - 100)				//�w�i�̍���
#define TITLEANIM_ANIM_U		(0.1f)								//U
#define TITLEANIM_ANIM_V		(0.08333f)							//V

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureTitleAnim = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitleAnim = NULL;		//���_�o�b�t�@�ւ̃|�C���^
TitleAnim				g_TitleAnim;

//=============================================================================
// �^�C�g���A�j���[�V��������������
//=============================================================================
void InitTitleAnim(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//�f�o�C�X�̎擾
	
	g_TitleAnim.nCntAnim = 0;
	g_TitleAnim.nCntAnimNum = 0;
	g_TitleAnim.bUse = false;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TITLEANIM_TEXTURENAME,
		&g_pTextureTitleAnim);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitleAnim,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitleAnim->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(TITLEANIM_POS_X, TITLEANIM_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLEANIM_POS_X + TITLEANIM_WHIDTH, TITLEANIM_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLEANIM_POS_X, TITLEANIM_POS_Y + TITLEANIM_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLEANIM_POS_X + TITLEANIM_WHIDTH, TITLEANIM_POS_Y + TITLEANIM_HEIGHT, 0.0f);

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
	pVtx[1].tex = D3DXVECTOR2(TITLEANIM_ANIM_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TITLEANIM_ANIM_V);
	pVtx[3].tex = D3DXVECTOR2(TITLEANIM_ANIM_U, TITLEANIM_ANIM_V);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleAnim->Unlock();
}

//=============================================================================
// �^�C�g���A�j���[�V�����I������
//=============================================================================
void UninitTitleAnim(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTitleAnim != NULL)
	{
		g_pTextureTitleAnim->Release();
		g_pTextureTitleAnim = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitleAnim != NULL)
	{
		g_pVtxBuffTitleAnim->Release();
		g_pVtxBuffTitleAnim = NULL;
	}
}

//=============================================================================
// �^�C�g���A�j���[�V�����X�V����
//=============================================================================
void UpdateTitleAnim(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTitleAnim->Lock(0, 0, (void**)&pVtx, 0);

	if (g_TitleAnim.bUse == true)
	{
		g_TitleAnim.nCntAnim++;

		if (g_TitleAnim.nCntAnim % 1 == 0)
		{
			if (g_TitleAnim.nCntAnimNum < 118)
			{
				g_TitleAnim.nCntAnimNum++;
			}
		}

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2((g_TitleAnim.nCntAnimNum % 10) * TITLEANIM_ANIM_U, (g_TitleAnim.nCntAnimNum / 10) * TITLEANIM_ANIM_V);
		pVtx[1].tex = D3DXVECTOR2((g_TitleAnim.nCntAnimNum % 10) * TITLEANIM_ANIM_U + TITLEANIM_ANIM_U, (g_TitleAnim.nCntAnimNum / 10) * TITLEANIM_ANIM_V);
		pVtx[2].tex = D3DXVECTOR2((g_TitleAnim.nCntAnimNum % 10) * TITLEANIM_ANIM_U, (g_TitleAnim.nCntAnimNum / 10) * TITLEANIM_ANIM_V + TITLEANIM_ANIM_V);
		pVtx[3].tex = D3DXVECTOR2((g_TitleAnim.nCntAnimNum % 10) * TITLEANIM_ANIM_U + TITLEANIM_ANIM_U, (g_TitleAnim.nCntAnimNum / 10) * TITLEANIM_ANIM_V + TITLEANIM_ANIM_V);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitleAnim->Unlock();
}

//=============================================================================
// �^�C�g���A�j���[�V�����`�揈��
//=============================================================================
void DrawTitleAnim(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitleAnim, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (g_TitleAnim.bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitleAnim);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			0,						//�J�n���钸�_�̃C���f�b�N�X
			2);						//�v���~�e�B�u�̐�
	}
}

//=============================================================================
// �^�C�g���A�j���[�V�����ݒ菈��
//=============================================================================
void SetTitleAnim(void)
{
	g_TitleAnim.nCntAnim = 0;
	g_TitleAnim.nCntAnimNum = 0;
	g_TitleAnim.bUse = true;
}

//=============================================================================
// �^�C�g���A�j���[�V�����擾����
//=============================================================================
TitleAnim GetTitleAnim(void)
{
	return g_TitleAnim;
}

//=============================================================================
// �^�C�g���A�j���[�V�����ԍ�����
//=============================================================================
void SetTitleAnimNum(void)
{
	g_TitleAnim.nCntAnimNum = 118;
}

//=============================================================================
// �^�C�g���A�j���[�V�����j������
//=============================================================================
void DeleteTitleAnim(void)
{
	g_TitleAnim.nCntAnim = 0;
	g_TitleAnim.nCntAnimNum = 0;
	g_TitleAnim.bUse = false;
}