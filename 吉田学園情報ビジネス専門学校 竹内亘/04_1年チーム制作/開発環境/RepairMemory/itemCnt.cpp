//=============================================================================
//
// �A�C�e���J�E���^�[���� [itemCnt.cpp]
// Author : ���������@Sato_Aaumi
//
//=============================================================================
#include "itemCnt.h"
#include "questfade.h"
#include "Bottun.h"
#include "item.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_SCORE		"data/TEXTURE/number003.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define MAX_NUM				(2)								// �K�p�ȗ�
#define MOVE_POS			(31.0f)							// �ړ���
#define NUM_SIZE			(30.0f)							// �����̑傫��
#define POS_X				(200.0f)						// X���W
#define POS2_X				(285.0f)						// X���W
#define POS2_Y				(20.0f)							// Y���W

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexItemCnt(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DTEXTURE9		g_pTextureItemCnt = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemCnt = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nItemCnt;						// �g�[�^���X�R�A
int						g_nMaxItem;						// �A�C�e���̑���
ItemCnt					g_ItemCnt[MAX_NUM];				// ���̐ݒ�

//=============================================================================
// ����������
//=============================================================================
void InitItemCnt(void)
{
	//�ϐ��錾
	int nCntNum;
	int nCntMaxNum;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nItemCnt = 0;
	g_nMaxItem = 0;

	for (nCntMaxNum = 0; nCntMaxNum < MAX_NUM; nCntMaxNum++)
	{
		for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
		{
			g_ItemCnt[nCntMaxNum].aNum[nCntNum] = 0;
		}
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
							  TEXTURE_SCORE,		// �t�@�C���̖��O
							  &g_pTextureItemCnt);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexItemCnt(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitItemCnt(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureItemCnt != NULL)
	{
		g_pTextureItemCnt->Release();
		g_pTextureItemCnt = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pTextureItemCnt != NULL)
	{
		g_pTextureItemCnt->Release();
		g_pTextureItemCnt = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItemCnt(void)
{
	//�ϐ��錾
	int nCntItemCnt;
	int nCntMaxNum;
	int nCntNum;			//�X�R�A�̌����̃J�E���^�[
	int nNum = 1;
	int nNum2 = 1;

	// ���_����ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItemCnt->Lock(0, 0, (void**)&pVtx, 0);

	//�A�C�e���̑��������擾
	g_nMaxItem = GetItem();

	//�����̌v�Z
	for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
	{
		nNum *= 10;
	}
	for (nCntNum = 0; nCntNum < NUM_SCORE - 1; nCntNum++)
	{
		nNum2 *= 10;
	}

	//�A�C�e���̍ő吔��ݒ肷��
	for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
	{
		g_ItemCnt[1].aNum[nCntNum] = (g_nMaxItem % nNum) / nNum2;		//�i�[���鐔�����v�Z

		//�������P�����炷
		nNum = nNum / 10;
		nNum2 = nNum2 / 10;
	}

	for (nCntMaxNum = 0; nCntMaxNum < MAX_NUM; nCntMaxNum++)
	{
		for (nCntItemCnt = 0; nCntItemCnt < NUM_SCORE; nCntItemCnt++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_ItemCnt[nCntMaxNum].aNum[nCntItemCnt]), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_ItemCnt[nCntMaxNum].aNum[nCntItemCnt]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_ItemCnt[nCntMaxNum].aNum[nCntItemCnt]), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_ItemCnt[nCntMaxNum].aNum[nCntItemCnt]), 1.0f);

			//�Y���̈ʒu�܂Ői�߂�
			pVtx += 4;
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItemCnt->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItemCnt(void)
{
	//�ϐ��錾
	int nCntItemCnt;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffItemCnt, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureItemCnt);

	// �|���S���̕`��
	for (nCntItemCnt = 0; nCntItemCnt < NUM_SCORE * MAX_NUM; nCntItemCnt++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntItemCnt * 4,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexItemCnt(LPDIRECT3DDEVICE9 pDevice)
{
	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SCORE * MAX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemCnt,
		NULL);

	// ���_����ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffItemCnt->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(POS_X + 0.0f, 10.0f , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(POS_X + NUM_SIZE, 10.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(POS_X + 0.0f, 60.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(POS_X + NUM_SIZE, 60.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_���W�̐ݒ�
	pVtx[4].pos = D3DXVECTOR3(POS_X + 0.0f + MOVE_POS, 10.0f, 0.0f);
	pVtx[5].pos = D3DXVECTOR3(POS_X + NUM_SIZE + MOVE_POS, 10.0f, 0.0f);
	pVtx[6].pos = D3DXVECTOR3(POS_X + 0.0f + MOVE_POS, 60.0f, 0.0f);
	pVtx[7].pos = D3DXVECTOR3(POS_X + NUM_SIZE + 30.0f, 60.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[4].rhw = 1.0f;
	pVtx[5].rhw = 1.0f;
	pVtx[6].rhw = 1.0f;
	pVtx[7].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[4].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[5].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[6].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[7].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[5].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_���W�̐ݒ�
	pVtx[8].pos = D3DXVECTOR3(POS2_X + 0.0f, POS2_Y + 10.0f, 0.0f);
	pVtx[9].pos = D3DXVECTOR3(POS2_X + NUM_SIZE, POS2_Y + 10.0f, 0.0f);
	pVtx[10].pos = D3DXVECTOR3(POS2_X + 0.0f, POS2_Y + 60.0f, 0.0f);
	pVtx[11].pos = D3DXVECTOR3(POS2_X + NUM_SIZE, POS2_Y + 60.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[8].rhw = 1.0f;
	pVtx[9].rhw = 1.0f;
	pVtx[10].rhw = 1.0f;
	pVtx[11].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[8].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[9].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[10].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[11].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[8].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[9].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[10].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[11].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_���W�̐ݒ�
	pVtx[12].pos = D3DXVECTOR3(POS2_X + MOVE_POS, POS2_Y + 10.0f, 0.0f);
	pVtx[13].pos = D3DXVECTOR3(POS2_X + NUM_SIZE + MOVE_POS, POS2_Y + 10.0f, 0.0f);
	pVtx[14].pos = D3DXVECTOR3(POS2_X + 0.0f + MOVE_POS, POS2_Y + 60.0f, 0.0f);
	pVtx[15].pos = D3DXVECTOR3(POS2_X + NUM_SIZE + MOVE_POS, POS2_Y + 60.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[12].rhw = 1.0f;
	pVtx[13].rhw = 1.0f;
	pVtx[14].rhw = 1.0f;
	pVtx[15].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[12].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[13].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[14].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
	pVtx[15].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[12].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[13].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[14].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[15].tex = D3DXVECTOR2(0.1f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItemCnt->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void AddItemCnt(int nValue)
{
	//�ϐ��錾
	int nCntNum;			//�X�R�A�̌����̃J�E���^�[
	int nNum = 1;
	int nNum2 = 1;

	//�����̌v�Z
	for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
	{
		nNum *= 10;
	}
	for (nCntNum = 0; nCntNum < NUM_SCORE - 1; nCntNum++)
	{
		nNum2 *= 10;
	}

	//�X�R�A���Z
	g_nItemCnt += nValue;

	for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
	{
		g_ItemCnt[0].aNum[nCntNum] = (g_nItemCnt % nNum) / nNum2;	//�i�[���鐔�����v�Z

		//�������P�����炷
		nNum = nNum / 10;
		nNum2 = nNum2 / 10;
	}

	if (g_nItemCnt >= g_nMaxItem)
	{
		SetBottunType(BOTTUNTYPE_SELECT);
	}
}

//========================================================================================
//�A�C�e���̏��
//========================================================================================
int GetItemCnt(void)
{
	return g_nItemCnt;
}

//========================================================================================
//�J�E���^�[�����Z�b�g����
//========================================================================================
void ResetItemCnt(void)
{
	g_nItemCnt = 0;
}

//========================================================================================
// �A�C�e����j��
//========================================================================================
void DeleteItemCnt(void)
{
	//�ϐ��錾
	int nCntNum;
	int nCntMaxNum;

	// �X�R�A�̏�����
	g_nItemCnt = 0;
	g_nMaxItem = 0;

	for (nCntMaxNum = 0; nCntMaxNum < MAX_NUM; nCntMaxNum++)
	{
		for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
		{
			g_ItemCnt[nCntMaxNum].aNum[nCntNum] = 0;
		}
	}
}