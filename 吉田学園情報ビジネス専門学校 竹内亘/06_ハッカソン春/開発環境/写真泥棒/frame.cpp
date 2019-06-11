//=============================================================================
//
// �t���[������ [frame.cpp]
// Author : �|���j
//
//=============================================================================
#include "frame.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_FRAME			(2)													// �t���[���̍ő吔
#define FRAME_TEXTURENAME	"data/TEXTURE/frame_timer000.png"				    // �ǂݍ��ރe�N�X�`����
#define FRAME_TEXTURENAME2	"data/TEXTURE/frame_score000.png"					// �ǂݍ��ރe�N�X�`����
#define FRAME_TEXTURENAME3	"data/TEXTURE/frame_life000.png"					// �ǂݍ��ރe�N�X�`����
#define FRAME_SIZE_X (100.0f)													// �t���[���T�C�YX
#define FRAME_SIZE_Y (50.0f)													// �t���[���T�C�YY
#define MAX_FRAME_TYPE		(2)													// �t���[���̎��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexFrame(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
//LPDIRECT3DTEXTURE9		g_pTextureFrame = NULL;			// �e�N�X�`���ւ̃|�C���^
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureFrame[MAX_FRAME] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFrame = NULL;			// ���_�o�b�t�@�ւ̃|�C���^

//D3DXVECTOR3				g_FramePos(640, 50, 0.0f);	// �t���[���̒��_���W
Frame g_aFrame[MAX_FRAME];								// �t���[���̏��

//=============================================================================
// ����������
//=============================================================================
void InitFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �t���[���̏���������
	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		g_aFrame[nCntFrame].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aFrame[nCntFrame].fHeight = 0.0f;
		g_aFrame[nCntFrame].fWidth = 0.0f;
		g_aFrame[nCntFrame].nType = (FRAME)nCntFrame;
		g_aFrame[nCntFrame].bUse = false;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		FRAME_TEXTURENAME,							// �t�@�C���̖��O
		&g_pTextureFrame[0]);						// �e�N�X�`���ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		FRAME_TEXTURENAME2,							// �t�@�C���̖��O
		&g_pTextureFrame[1]);						// �e�N�X�`���ւ̃|�C���^


	// ���_���̍쐬
	MakeVertexFrame(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitFrame(void)
{
	for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureFrame[nCntFrame] != NULL)
		{
			g_pTextureFrame[nCntFrame]->Release();
			g_pTextureFrame[nCntFrame] = NULL;
		}

		//���_�o�b�t�@�̊J��
		if (g_pVtxBuffFrame != NULL)
		{
			g_pVtxBuffFrame->Release();
			g_pVtxBuffFrame = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFrame(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFrame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	int nCntFrame;

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffFrame, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
	{
		if (g_aFrame[nCntFrame].bUse = true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureFrame[g_aFrame[nCntFrame].nType]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntFrame * 4, 2);
		}
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexFrame(LPDIRECT3DDEVICE9 pDevice)
{

		// ���_�o�b�t�@�𐶐�
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_FRAME,		//�m�ۂ���o�b�t�@�̃T�C�Y
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_2D,				//	���_�t�H�[�}�b�g
			D3DPOOL_MANAGED,
			&g_pVtxBuffFrame,
			NULL);

		// ���_����ݒ�
		VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffFrame->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntFrame = 0; nCntFrame < MAX_FRAME; nCntFrame++)
		{
			////���_���W�̐ݒ�
			//pVtx[0].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x - FRAME_SIZE_X, g_aFrame[nCntFrame].pos.y - FRAME_SIZE_Y, g_aFrame[nCntFrame].pos.z);
			//pVtx[1].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x + FRAME_SIZE_X, g_aFrame[nCntFrame].pos.y - FRAME_SIZE_Y, g_aFrame[nCntFrame].pos.z);
			//pVtx[2].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x - FRAME_SIZE_X, g_aFrame[nCntFrame].pos.y + FRAME_SIZE_Y, g_aFrame[nCntFrame].pos.z);
			//pVtx[3].pos = D3DXVECTOR3(g_aFrame[nCntFrame].pos.x + FRAME_SIZE_X, g_aFrame[nCntFrame].pos.y + FRAME_SIZE_Y, g_aFrame[nCntFrame].pos.z);

			if (nCntFrame == FRAME_TIMER)
			{//�^�C�}�[�t���[��
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(550, 0, 0);
				pVtx[1].pos = D3DXVECTOR3(750, 0, 0);
				pVtx[2].pos = D3DXVECTOR3(550, 100, 0);
				pVtx[3].pos = D3DXVECTOR3(750, 100, 0);

				//rhw�̐ݒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

				pVtx += 4;	//���_�f�[�^���S���i�߂�
			}

			else if (nCntFrame == FRAME_SCORE)
			{//�X�R�A�t���[��
				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(770, 0, 0);
				pVtx[1].pos = D3DXVECTOR3(1250, 0, 0);
				pVtx[2].pos = D3DXVECTOR3(770, 100, 0);
				pVtx[3].pos = D3DXVECTOR3(1250, 100, 0);

				//rhw�̐ݒ�
				pVtx[0].rhw = 1.0f;
				pVtx[1].rhw = 1.0f;
				pVtx[2].rhw = 1.0f;
				pVtx[3].rhw = 1.0f;

				//���_�J���[
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

				pVtx += 4;	//���_�f�[�^���S���i�߂�
			}

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffFrame->Unlock();
		}
}






