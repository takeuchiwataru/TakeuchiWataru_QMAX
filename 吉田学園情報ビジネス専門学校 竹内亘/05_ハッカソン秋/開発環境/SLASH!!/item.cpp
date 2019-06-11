//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : Niwa Hodaka
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "bullet.h"
#include "life.h"
#include "remain.h"
#include "reload.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ITEM		(3)						    // �A�C�e���̎��
#define ITEM_TEXTURE_NAME0  "data/TEXTURE/item000.png"  // �ǂݍ��ޓG�̃e�N�X�`���t�@�C����[0�Ԗ�]
#define ITEM_TEXTURE_NAME1  "data/TEXTURE/item001.png"  // �ǂݍ��ޓG�̃e�N�X�`���t�@�C����[1�Ԗ�]
#define ITEM_TEXTURE_NAME2  "data/TEXTURE/item002.png"  // �ǂݍ��ޓG�̃e�N�X�`���t�@�C����[2�Ԗ�]

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_apTextureItem[MAX_TYPE_ITEM] = {};	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
ITEM                    g_aItem[MAX_ITEM];                      // �A�C�e���̏��             

//=============================================================================
// ����������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �A�C�e���̏��̏�����
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{// �A�C�e���̐������J��Ԃ�
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // �A�C�e���̍��W��������
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // �A�C�e���̍��W��������
		g_aItem[nCntItem].nType = 0;                             // �A�C�e���̎�ނ�������
		g_aItem[nCntItem].nCounterState = 0;                     // �A�C�e���̏�ԃJ�E���^�[��������
		g_aItem[nCntItem].bUse = false;                          // �A�C�e���͎g�p���Ă��Ȃ���Ԃɂ���
	}

    // �e�N�X�`���̓ǂݍ���(3��)
	// �P�̖�
	D3DXCreateTextureFromFile(pDevice,
		ITEM_TEXTURE_NAME0,
		&g_apTextureItem[0]);
	// �Q�̖�
	D3DXCreateTextureFromFile(pDevice,
		ITEM_TEXTURE_NAME1,
		&g_apTextureItem[1]);
	// �R�̖�
	D3DXCreateTextureFromFile(pDevice,
		ITEM_TEXTURE_NAME2,
		&g_apTextureItem[2]);

	// ���_���̍쐬
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItem,
		NULL);

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{// �A�C�e���̐������J��Ԃ�
	 // ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);

		// ���_�e�N�X�`��
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

		pVtx += 4;
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void UninitItem(void)
{
	int nCntTex;

	// �e�N�X�`���̊J��
	for (nCntTex = 0; nCntTex < MAX_TYPE_ITEM; nCntTex++)
	{// �G�̃e�N�X�`���t�@�C���������J��Ԃ�
		if (g_apTextureItem[nCntTex] != NULL)
		{
			g_apTextureItem[nCntTex]->Release();
			g_apTextureItem[nCntTex] = NULL;
		}
	}

	// ���_�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateItem(void)
{
	int nCntItem;
	VERTEX_2D *pVtx;
	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{// �A�C�e���̐������J��Ԃ�
		if (g_aItem[nCntItem].bUse == true)
		{// �A�C�e�����g�p����Ă���

			Bullet *pBullet;
			pBullet = GetBullet();
			Player *pPlayer;
			pPlayer = GetPlayer();

			g_aItem[nCntItem].move.x = sinf(atan2f(pPlayer->pos.x - g_aItem[nCntItem].pos.x, pPlayer->pos.y - g_aItem[nCntItem].pos.y)) * 2.0f;
			g_aItem[nCntItem].move.y = cosf(atan2f(pPlayer->pos.x - g_aItem[nCntItem].pos.x, pPlayer->pos.y - g_aItem[nCntItem].pos.y)) * 2.0f;

			g_aItem[nCntItem].pos += g_aItem[nCntItem].move;

			for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
			{
				if (pBullet->bUse == true)
				{// �e���g�p����Ă�����
					if (g_aItem[nCntItem].pos.x > pBullet->pos.x - 30 && g_aItem[nCntItem].pos.x < pBullet->pos.x + 30
						&& g_aItem[nCntItem].pos.y > pBullet->pos.y - 30 && g_aItem[nCntItem].pos.y < pBullet->pos.y + 30)
					{// �A�C�e�����a���ɂ�������
						switch (g_aItem[nCntItem].nType)
						{
						case 0:
							pPlayer->nSharp = 5;
							PlaySound(SOUND_LABEL_SE_KENMA);
							AddReload();
							break;
						case 1:
							pPlayer->nLife++;
							PlaySound(SOUND_LABEL_SE_LIFEKAIHUKU);
							AddLife(1);
							break;
						case 2:
							pPlayer->nRemain++;
							PlaySound(SOUND_LABEL_SE_ZANKIKAIHUKU);
							AddRemain();
							break;
						}
						g_aItem[nCntItem].bUse = false;

						if (g_aItem[nCntItem].pos.x > pPlayer->pos.x - 30 && g_aItem[nCntItem].pos.x < pPlayer->pos.x + 30
							&& g_aItem[nCntItem].pos.y > pPlayer->pos.y - 30 && g_aItem[nCntItem].pos.y < pPlayer->pos.y + 30)
						{
							g_aItem[nCntItem].bUse = false;
						}
					}
				}
			}
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{// �G�̐������J��Ԃ�
		if (g_aItem[nCntItem].bUse == true)
		{// �G���g�p����Ă���
		 // �e�N�X�`���̓ǂݍ���
			pDevice->SetTexture(0, g_apTextureItem[g_aItem[nCntItem].nType]);

			// �G�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntItem * 4,
				2);
		}
	}
}

//=============================================================================
// �G�̐ݒ�
//=============================================================================
void SetItem(D3DXVECTOR3 pos, int nType, D3DXVECTOR3 move)
{
	int nCntItem;
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{// �G�̐������J��Ԃ�
		if (g_aItem[nCntItem].bUse == false)
		{// �G���g�p����Ă���
			g_aItem[nCntItem].pos = pos;
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x - TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.y + TEXTURE_ITEM_SIZE, g_aItem[nCntItem].pos.z);

			// �F���̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aItem[nCntItem].move = move;
			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].bUse = true;
			break;
		}
		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}