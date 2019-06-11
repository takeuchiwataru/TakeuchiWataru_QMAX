//=============================================================================
//
// PressEnter���� [pressenter.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "pressenter.h"
#include "fade.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_NAME       "data/TEXTURE/pressenter000.png"  // �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexPressEnter(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTexturePressEnter = NULL;	   // �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPressEnter = NULL;	   // ���_�o�b�t�@�ւ̃|�C���^
D3DXVECTOR3             g_PressEnterPos(0.0f, 0.0f, 0.0f); // ���W
D3DXCOLOR               g_PressEnterCol;                   // �F
PRESSENTERSTATE         g_PressEnterState;                 // ���
int                     g_SizePressEnterX;                 // �T�C�YX
int                     g_SizePressEnterY;                 // �T�C�YY
int                     g_nCounterPressEnter;              // Draw����^�C�~���O�Ǘ��J�E���^�[
bool                    g_bDisp;                           // �`�悷�邩���Ȃ���

//=============================================================================
// ����������
//=============================================================================
void InitPressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_PressEnterState = PRESSENTERSTATE_NONE;             // ������Ă��Ȃ���Ԃɂ���
	g_PressEnterCol = D3DXCOLOR(1.0f, 1.0f, 0.0f,1.0f);   // �F��������
	g_PressEnterPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // ���W��������
	g_nCounterPressEnter = 0;                             // �J�E���^�[��0�ɂ���
	g_bDisp = false;                                      // �\���͂��Ȃ�

	// ���_���̐ݒ�
	MakeVertexPressEnter(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitPressEnter(void)
{
	// �e�N�X�`���̊J��
	if (g_pTexturePressEnter != NULL)
	{
		g_pTexturePressEnter->Release();
		g_pTexturePressEnter = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffPressEnter != NULL)
	{
		g_pVtxBuffPressEnter->Release();
		g_pVtxBuffPressEnter = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePressEnter(void)
{
	if (g_nCounterPressEnter >= 100)
	{
		g_nCounterPressEnter = 0;
	}

	if (g_bDisp == true)
	{// �`�悷���ԂȂ��
		g_nCounterPressEnter++;
		if (GetJoyPadTrigger(DIJS_BUTTON_2,0) == TRUE || GetKeyboardTrigger(DIK_RETURN) == true)
		{// ENTER�L�[�������ꂽ
			g_PressEnterState = PRESSENTERSTATE_PUSH;  // ������Ă����Ԃɂ���
		}
	}

	FADE fade;
	fade = GetFade();

	if (fade == FADE_IN)
	{// �t�F�[�h��Ԃ�������
		g_PressEnterState = PRESSENTERSTATE_NONE;
		g_nCounterPressEnter = 0;
	}
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void DrawPressEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffPressEnter, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePressEnter);

	// �|���S���̕`��
	if (g_bDisp == true)
	{// �`�悷���Ԃ�������
		if (g_PressEnterState == PRESSENTERSTATE_NONE)
		{// ������Ă��Ȃ���Ԃ�������
			if (g_nCounterPressEnter / 80 == 0)
			{// �J�E���^�[�����̒l�ɂȂ�����
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
			}
		}
		else if (g_PressEnterState == PRESSENTERSTATE_PUSH)
		{// ������Ă����Ԃ�������
			if (g_nCounterPressEnter % 4 == 0)
			{// �J�E���^�[�����̒l�ɂȂ�����
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
			}
		}
	}
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexPressEnter(LPDIRECT3DDEVICE9 pDevice)
{
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		TEXTURE_NAME,
		&g_pTexturePressEnter);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPressEnter,
		NULL);

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_PressEnterPos.x - g_SizePressEnterX, g_PressEnterPos.y - g_SizePressEnterY, g_PressEnterPos.z);
	pVtx[1].pos = D3DXVECTOR3(g_PressEnterPos.x + g_SizePressEnterX, g_PressEnterPos.y - g_SizePressEnterY, g_PressEnterPos.z);
	pVtx[2].pos = D3DXVECTOR3(g_PressEnterPos.x - g_SizePressEnterX, g_PressEnterPos.y + g_SizePressEnterY, g_PressEnterPos.z);
	pVtx[3].pos = D3DXVECTOR3(g_PressEnterPos.x + g_SizePressEnterX, g_PressEnterPos.y + g_SizePressEnterY, g_PressEnterPos.z);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_PressEnterCol;
	pVtx[1].col = g_PressEnterCol;
	pVtx[2].col = g_PressEnterCol;
	pVtx[3].col = g_PressEnterCol;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPressEnter->Unlock();
}
//=============================================================================
// ���W�̐ݒ�
//=============================================================================
void SetPressEnter(D3DXVECTOR3 pos,int xsize,int ysize)
{
	g_PressEnterPos = pos;
	g_SizePressEnterX = xsize;
	g_SizePressEnterY = ysize;

	VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffPressEnter->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_PressEnterPos.x - g_SizePressEnterX, g_PressEnterPos.y - g_SizePressEnterY, g_PressEnterPos.z);
	pVtx[1].pos = D3DXVECTOR3(g_PressEnterPos.x + g_SizePressEnterX, g_PressEnterPos.y - g_SizePressEnterY, g_PressEnterPos.z);
	pVtx[2].pos = D3DXVECTOR3(g_PressEnterPos.x - g_SizePressEnterX, g_PressEnterPos.y + g_SizePressEnterY, g_PressEnterPos.z);
	pVtx[3].pos = D3DXVECTOR3(g_PressEnterPos.x + g_SizePressEnterX, g_PressEnterPos.y + g_SizePressEnterY, g_PressEnterPos.z);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPressEnter->Unlock();

	g_bDisp = true;
}
//=============================================================================
// ��Ԃ̎擾
//=============================================================================
PRESSENTERSTATE *GetPressEnter(void)
{
	return &g_PressEnterState;
}
//=============================================================================
// �`���Ԃ̎擾
//=============================================================================
bool *GetDispPressEnter(void)
{
	return &g_bDisp;
}
//=============================================================================
// �`�悷�邩���Ȃ���
//=============================================================================
void DispPressEnter(void)
{
	g_bDisp = true;
}