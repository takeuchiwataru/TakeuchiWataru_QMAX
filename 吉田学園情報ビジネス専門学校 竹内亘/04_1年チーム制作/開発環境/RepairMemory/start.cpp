//=============================================================================
//
// �X�^�[�g�{�^�� [start.cpp]
// Author : ���������@Sato_Asumi
//
//=============================================================================
#include "start.h"
#include "main.h"
#include "input.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define START_TEXTURENAME	"data\\TEXTURE\\press_enter.png"	//�ǂݍ��ރe�N�X�`���t�@�C��
#define WIDTH				(350)								//����
#define HIGHT				(50)								//�c��
#define HERF_W				(WIDTH / 2)							//���� / �Q
#define HERF_H				(HIGHT / 2)							//�c�� / �Q

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureStart = NULL;		//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStart = NULL;		//���_�o�b�t�@�ւ̃|�C���^
ENTER					g_Enter;					//���ݒ�

//=============================================================================
// �X�^�[�g�{�^������������
//=============================================================================
void InitStart(void)
{
	//�ϐ��̏�����
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^
	g_Enter.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu���
	g_Enter.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F���
	g_Enter.ChangeCol = 0.01f;							//�ω��ʂ̏��
	g_Enter.Struct = STARTSTRACT_NORMAL;				//��Ԃ̏��
	g_Enter.bUse = false;								//�g�p���Ă��Ȃ���Ԃɂ���

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		START_TEXTURENAME,
		&g_pTextureStart);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffStart,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
	g_pVtxBuffStart->Unlock();
}

//=============================================================================
// �^�C�g���I������
//=============================================================================
void UninitStart(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureStart != NULL)
	{
		g_pTextureStart->Release();
		g_pTextureStart = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStart != NULL)
	{
		g_pVtxBuffStart->Release();
		g_pVtxBuffStart = NULL;
	}
}

//=============================================================================
// �^�C�g���X�V����
//=============================================================================
void UpdateStart(void)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Enter.bUse == true)
	{
		switch (g_Enter.Struct)
		{
		case STARTSTRACT_NORMAL:

			//�ω��ʂ̕����ϊ�
			if (g_Enter.col.a <= 0.0f || g_Enter.col.a >= 1.0f)
			{
				g_Enter.ChangeCol *= -1;
			}

			//�J���[�X�V
			g_Enter.col.a += g_Enter.ChangeCol;

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(g_Enter.col.r, g_Enter.col.g, g_Enter.col.b, g_Enter.col.a);
			pVtx[1].col = D3DXCOLOR(g_Enter.col.r, g_Enter.col.g, g_Enter.col.b, g_Enter.col.a);
			pVtx[2].col = D3DXCOLOR(g_Enter.col.r, g_Enter.col.g, g_Enter.col.b, g_Enter.col.a);
			pVtx[3].col = D3DXCOLOR(g_Enter.col.r, g_Enter.col.g, g_Enter.col.b, g_Enter.col.a);
			break;

		case STARTSTRACT_ENTER:
			pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			break;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStart->Unlock();
}

//=============================================================================
// �^�C�g���`�揈��
//=============================================================================
void DrawStart(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStart, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureStart);

	if (g_Enter.bUse == true)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
			0,											//�J�n���钸�_�̃C���f�b�N�X
			2);											//�v���~�e�B�u�̐�
	}
}

//=============================================================================
// ���ݒ�
//=============================================================================
void SetEnter(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffStart->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Enter.bUse == false)
	{
		g_Enter.pos = pos;						//�ʒu���

												//�ʒu���̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Enter.pos.x - HERF_W, g_Enter.pos.y - HERF_H, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Enter.pos.x + HERF_W, g_Enter.pos.y - HERF_H, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Enter.pos.x - HERF_W, g_Enter.pos.y + HERF_H, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Enter.pos.x + HERF_W, g_Enter.pos.y + HERF_H, 0.0f);

		g_Enter.col = col;						//�F

												//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(g_Enter.col.r, g_Enter.col.g, g_Enter.col.b, g_Enter.col.a);
		pVtx[1].col = D3DXCOLOR(g_Enter.col.r, g_Enter.col.g, g_Enter.col.b, g_Enter.col.a);
		pVtx[2].col = D3DXCOLOR(g_Enter.col.r, g_Enter.col.g, g_Enter.col.b, g_Enter.col.a);
		pVtx[3].col = D3DXCOLOR(g_Enter.col.r, g_Enter.col.g, g_Enter.col.b, g_Enter.col.a);

		g_Enter.ChangeCol = 0.01f;				//�ω���
		g_Enter.Struct = STARTSTRACT_NORMAL;	//���ݒ�
		g_Enter.bUse = true;					//�g�p���Ă����Ԃɂ���
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStart->Unlock();
}

//=============================================================================
// �X�^�[�g�{�^���̏�Ԑݒ�
//=============================================================================
void SetPush(STARTSTRACT stract)
{//��Ԃ̐ݒ�
	g_Enter.Struct = stract;
}

//=============================================================================
// �X�^�[�g�{�^���̏�Ԑݒ�
//=============================================================================
void DeleteStart(void)
{//��Ԃ̐ݒ�
	g_Enter.bUse = false;
}
