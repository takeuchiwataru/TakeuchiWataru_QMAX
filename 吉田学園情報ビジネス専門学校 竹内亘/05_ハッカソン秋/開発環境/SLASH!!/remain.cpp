//=============================================================================
//
// �c�@���� [remain.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "remain.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIMER		"data/TEXTURE/Player000.png"    // �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_SIZE        (70)                            // �e�N�X�`���̃T�C�Y

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexRemain(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureRemain = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRemain = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
REMAIN                  g_remain[MAX_REMAINNUMBER]; // �c�@
int                     g_nCounterRemain;           // ���݂̎c�@��

//=============================================================================
// ����������
//=============================================================================
void InitRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for (int nCntRemain = 0; nCntRemain < MAX_REMAINNUMBER; nCntRemain++)
	{// ���C�t�A�C�R���������J��Ԃ�
		g_remain[nCntRemain].pos = D3DXVECTOR3(30, 640, 0);  // ���W��������
		g_remain[nCntRemain].bUse = false;                  // �g�p���Ă����Ԃɂ���
	}
	g_nCounterRemain = MAX_REMAINNUMBER - 7;                // ���݂̎c�@����������

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,	      // �f�o�C�X�ւ̃|�C���^
		TEXTURE_TIMER,		                  // �t�@�C���̖��O
		&g_pTextureRemain);	                  // �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexRemain(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitRemain(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureRemain != NULL)
	{
		g_pTextureRemain->Release();
		g_pTextureRemain = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffRemain != NULL)
	{
		g_pVtxBuffRemain->Release();
		g_pVtxBuffRemain = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateRemain(void)
{

}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRemain, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRemain);

	// �|���S���̕`��
	for (int nCntRemain = 0; nCntRemain < MAX_REMAINNUMBER; nCntRemain++)
	{// �\�����郉�C�t�A�C�R���������J��Ԃ�
		if (g_remain[nCntRemain].bUse == true)
		{// ���C�t���g�p����Ă���
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntRemain * 4,
				2);
		}
	}
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexRemain(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_REMAINNUMBER,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRemain,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffRemain->Lock(0, 0, (void**)&pVtx, 0);

	float pos = 0;
	// ���_����ݒ�
	for (int nCntRemain = 0; nCntRemain < MAX_REMAINNUMBER; nCntRemain++)
	{// ���C�t�A�C�R���������J��Ԃ�
	 // ���_���W
		pVtx[0].pos = D3DXVECTOR3(g_remain[nCntRemain].pos.x - TEXTURE_SIZE + pos, g_remain[nCntRemain].pos.y - TEXTURE_SIZE, g_remain[nCntRemain].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_remain[nCntRemain].pos.x + TEXTURE_SIZE + pos, g_remain[nCntRemain].pos.y - TEXTURE_SIZE, g_remain[nCntRemain].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_remain[nCntRemain].pos.x - TEXTURE_SIZE + pos, g_remain[nCntRemain].pos.y + TEXTURE_SIZE, g_remain[nCntRemain].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_remain[nCntRemain].pos.x + TEXTURE_SIZE + pos, g_remain[nCntRemain].pos.y + TEXTURE_SIZE, g_remain[nCntRemain].pos.z);


		// ���_�e�N�X�`��
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
		pos += 60.0f;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRemain->Unlock();
}
//=============================================================================
// �c�@�̐ݒ�
//=============================================================================
void SetRemain(int remain)
{
	g_nCounterRemain = remain;  // �c�@����ݒ�

	for (int nCntRemain = 0; nCntRemain < remain - 1; nCntRemain++)
	{// ���C�t�A�C�R���������J��Ԃ�
		if (g_remain[nCntRemain].bUse == false)
		{// ���C�t���g�p����Ă���
			g_remain[nCntRemain].bUse = true;
		}
	}
}
//=============================================================================
// �c�@�̑���
//=============================================================================
void AddRemain(void)
{
	for (int nCntRemain = 0; nCntRemain < MAX_REMAINNUMBER; nCntRemain++)
	{// ���C�t�A�C�R���������J��Ԃ�
		if (g_remain[nCntRemain].bUse == false)
		{// ���C�t���g�p����Ă���
			g_remain[nCntRemain].bUse = true;
			g_nCounterRemain++;
			break;
		}
	}
}
//=============================================================================
// �c�@�̌���
//=============================================================================
void CutRemain(void)
{
	for (int nCntRemain = MAX_REMAINNUMBER; nCntRemain >= 0; nCntRemain--)
	{// ���C�t�A�C�R���������J��Ԃ�
		if (g_remain[nCntRemain].bUse == true)
		{// ���C�t���g�p����Ă���
			g_remain[nCntRemain].bUse = false;
			g_nCounterRemain--;
			break;
		}
	}
}