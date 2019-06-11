//=============================================================================
//
// �t�B�����t���[���̏��� [filmframe.cpp]
// Author :�@Jukiya Hayakawa
//
//=============================================================================
#include "filmframe.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FRAME_TEXTURE_NAME0	"data\\TEXTURE\\filmframe.png"		// �e�N�X�`����
#define	FRAME_SIZE_X			(330)								// �傫��
#define	FRAME_SIZE_Y			(60)								// �傫��
#define	MAX_FRAME			(1)									//�����N�̍ő吔

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureFilmFrame = NULL;				// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFilmFrame = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
FILMFRAME g_aFilmFrame;													// �����N�̏��

//=============================================================================
// ����������
//=============================================================================
void InitFilmFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntFilmFrame;

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���̏�����
	g_aFilmFrame.pos = D3DXVECTOR3(350.0f, 650.0f, 0.0f);	//�ʒu�̏�����
	g_aFilmFrame.bUse = true;								//�g�p��Ԃɂ���

														// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, FRAME_TEXTURE_NAME0, &g_apTextureFilmFrame);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FRAME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFilmFrame,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffFilmFrame->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntFilmFrame = 0; nCntFilmFrame < MAX_FRAME; nCntFilmFrame++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aFilmFrame.pos.x - FRAME_SIZE_X, g_aFilmFrame.pos.y - FRAME_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aFilmFrame.pos.x + FRAME_SIZE_X, g_aFilmFrame.pos.y - FRAME_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aFilmFrame.pos.x - FRAME_SIZE_X, g_aFilmFrame.pos.y + FRAME_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aFilmFrame.pos.x + FRAME_SIZE_X, g_aFilmFrame.pos.y + FRAME_SIZE_Y, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		break;

		pVtx += 4;	// ���_�f�[�^���S���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffFilmFrame->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitFilmFrame(void)
{

	// �e�N�X�`���̊J��
	if (g_apTextureFilmFrame != NULL)
	{
		g_apTextureFilmFrame->Release();
		g_apTextureFilmFrame = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffFilmFrame != NULL)
	{
		g_pVtxBuffFilmFrame->Release();
		g_pVtxBuffFilmFrame = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFilmFrame(void)
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawFilmFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffFilmFrame, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntFilmFrame = 0; nCntFilmFrame < MAX_FRAME; nCntFilmFrame++)
	{
		if (g_aFilmFrame.bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureFilmFrame);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				4 * nCntFilmFrame,
				2);
		}
	}
}