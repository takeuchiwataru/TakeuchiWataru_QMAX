//=============================================================================
//
// �U���Q�[�W���� [attackgauge.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "game.h"
#include "player.h"
#include "attackgauge.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define GAUGE_SIZE    (30)    // �Q�[�W�̃T�C�Y

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexAttackGauge(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureAttackGauge = NULL;   // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAttackGauge = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
ATTACKGAUGE             g_AttackGauge;                  // �Q�[�W

//=============================================================================
// ����������
//=============================================================================
void InitAttackGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_AttackGauge.pos = D3DXVECTOR3(30,30, 0.0f); // ���W��������
	g_AttackGauge.col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);           // �F��������
	g_AttackGauge.ngauge = 0;                                        // �Q�[�W��������

	// ���_���̍쐬
	MakeVertexAttackGauge(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitAttackGauge(void)
{
	// ���_�o�b�t�@�̔j��
	if (g_pTextureAttackGauge != NULL)
	{
		g_pTextureAttackGauge->Release();
		g_pTextureAttackGauge = NULL;
	}
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffAttackGauge != NULL)
	{
		g_pVtxBuffAttackGauge->Release();
		g_pVtxBuffAttackGauge = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateAttackGauge(void)
{
	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffAttackGauge->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y - GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE + g_AttackGauge.ngauge, g_AttackGauge.pos.y - GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y + GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE + g_AttackGauge.ngauge, g_AttackGauge.pos.y + GAUGE_SIZE, g_AttackGauge.pos.z);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffAttackGauge->Unlock();
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawAttackGauge(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffAttackGauge, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureAttackGauge);

	// �|���S���̕`��
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				0,
				2);
}
//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexAttackGauge(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffAttackGauge,
		NULL);

	// ���_�o�b�t�@�𐶐�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffAttackGauge->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y - GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[1].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y - GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[2].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y + GAUGE_SIZE, g_AttackGauge.pos.z);
	pVtx[3].pos = D3DXVECTOR3(g_AttackGauge.pos.x - GAUGE_SIZE, g_AttackGauge.pos.y + GAUGE_SIZE, g_AttackGauge.pos.z);

	// ���_�e�N�X�`��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = g_AttackGauge.col;
	pVtx[1].col = g_AttackGauge.col;
	pVtx[2].col = g_AttackGauge.col;
	pVtx[3].col = g_AttackGauge.col;

	// �e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffAttackGauge->Unlock();
}
//=============================================================================
// �Q�[�W�̑���
//=============================================================================
void AddAttackGauge(int gauge)
{
	g_AttackGauge.ngauge += gauge;  // �Q�[�W�𑝂₷
	if (g_AttackGauge.ngauge >= GAUGE_MAX)
	{
		g_AttackGauge.ngauge = GAUGE_MAX;
		Player *pPlayer;
		pPlayer = GetPlayer();
		pPlayer->state = PLAYERSTATE_GAUGE_MAX;
	}
}
//=============================================================================
// �Q�[�W�̎擾
//=============================================================================
ATTACKGAUGE *GetAttackGauge(void)
{
	return &g_AttackGauge;
}