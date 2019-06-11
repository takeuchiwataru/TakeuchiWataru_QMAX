//=============================================================================
//
// �A�C�e������ [item.cpp]
// Author : �|���j
//
//=============================================================================
#include "item.h"
#include "player.h"
#include "score.h"
#include "timer.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_TYPE_ITEM		(3)							// �A�C�e���̎��
#define ITEM_TEXTURE_COIN  "data/TEXTURE/coin000.png"	// �e�N�X�`����
#define ITEM_TEXTURE_COIN2 "data/TEXTURE/coin001.png"	// �e�N�X�`����
#define TEX_COIN			(4)							// �R�C���e�N�X�`���A�j���[�V������
#define TEX_ANIM_SPEED		(8)							// �A�j���[�V�����X�s�[�h

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItem[MAX_TYPE_ITEM] = {};					// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;					// ���_�o�b�t�@�ւ̃|�C���^
Item                    g_aItem[MAX_ITEM];                      // �A�C�e���̏��
int g_nNumCoin;													// �R�C���̑���

//=============================================================================
// �A�C�e���̏���������
//=============================================================================
void InitItem(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// �f�o�C�X�̎擾
	pDevice = GetDevice();

	// �A�C�e���̏��̏�����
	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   
		g_aItem[nCntItem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  
		g_aItem[nCntItem].nType = ITEMTYPE_COIN;
		g_aItem[nCntItem].nCounterState = 0;
		g_aItem[nCntItem].nCounterAnim = 0;
		g_aItem[nCntItem].nPatternAnim = 0;
		g_aItem[nCntItem].fHeight = 0.0f;
		g_aItem[nCntItem].fWidth = 0.0f;
		g_aItem[nCntItem].bUse = false;
		g_nNumCoin = 0;
	}

	//�e�N�X�`���̓ǂݍ���
	// �R�C��
	D3DXCreateTextureFromFile(pDevice,ITEM_TEXTURE_COIN,&g_pTextureItem[0]);

	D3DXCreateTextureFromFile(pDevice, ITEM_TEXTURE_COIN2, &g_pTextureItem[1]);


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
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.25f, 1.0f);

		pVtx += 4;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �A�C�e���̏I������
//=============================================================================
void UninitItem(void)
{
	int nCntTex;

	for (nCntTex = 0; nCntTex < MAX_TYPE_ITEM; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureItem[nCntTex] != NULL)
		{
			g_pTextureItem[nCntTex]->Release();
			g_pTextureItem[nCntTex] = NULL;
		}

		// ���_�o�b�t�@�̊J��
		if (g_pVtxBuffItem != NULL)
		{
			g_pVtxBuffItem->Release();
			g_pVtxBuffItem = NULL;
		}
	}
}

//=============================================================================
// �A�C�e���̍X�V����
//=============================================================================
void UpdateItem(void)
{
	VERTEX_2D *pVtx;

	int nCntItem;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].nCounterAnim++;

		if (g_aItem[nCntItem].bUse == true)
		{// �A�C�e�����g�p����Ă���
			if (g_aItem[nCntItem].nCounterAnim % TEX_ANIM_SPEED == 0)
			{
				g_aItem[nCntItem].nPatternAnim = (g_aItem[nCntItem].nPatternAnim + 1) % TEX_COIN;

				//�e�N�X�`�����W�̍X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f + (g_aItem[nCntItem].nPatternAnim * 0.25f), 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.25f + (g_aItem[nCntItem].nPatternAnim * 0.25f), 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + (g_aItem[nCntItem].nPatternAnim * 0.25f), 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.25f + (g_aItem[nCntItem].nPatternAnim * 0.25f), 1.0f);
			}
		}
		pVtx += 4;
	}
	
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}

//=============================================================================
// �A�C�e���̕`�揈��
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
	{
		if (g_aItem[nCntItem].bUse == true)
		{// �A�C�e�����g�p����Ă���
		 // �e�N�X�`���̓ǂݍ���
			pDevice->SetTexture(0, g_pTextureItem[g_aItem[nCntItem].nType]);

			// �G�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntItem * 4,
				2);
		}
	}
}

//=============================================================================
// �A�C�e���̐ݒ�
//=============================================================================
void SetItem(D3DXVECTOR3 pos, float fWidth, float fHeight, ITEMTYPE nType)
{
	int nCntItem;
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		if (g_aItem[nCntItem].bUse == false)
		{
			g_aItem[nCntItem].pos = pos;
			g_aItem[nCntItem].fHeight = fHeight;
			g_aItem[nCntItem].fWidth = fWidth;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth, g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight, 0.0f);

			// �F���̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aItem[nCntItem].nType = nType;
			g_aItem[nCntItem].bUse = true;
			g_nNumCoin++;
			break;
		}
		pVtx +=4 ;
	}
	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}
//=============================================================================
// �A�C�e���̓����蔻��
//=============================================================================
bool CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove,float * fWidth, float * fHeight)
{
	int nCntItem;

	bool bGet = false;		//�Q�b�g�������ǂ���

	//�A�C�e���̎擾
	Item * pItem;
	pItem = GetItem();

	for (nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++,pItem++)
	{
		if (pItem->bUse == true)
		{//�A�C�e�����g���Ă���
			if (pPos->x + (*fWidth / 2) > g_aItem[nCntItem].pos.x &&
				pPos->x - (*fWidth / 2) < g_aItem[nCntItem].pos.x + g_aItem[nCntItem].fWidth &&
				pPos->y + (*fHeight / 2) > g_aItem[nCntItem].pos.y  &&
				pPos->y - (*fHeight / 2) < g_aItem[nCntItem].pos.y + g_aItem[nCntItem].fHeight)
			{
				pItem->bUse = false;
				SetExplosion(g_aItem[nCntItem].pos,D3DXVECTOR3(0.0f,5.0f,0.0f),D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
				PlaySound(SOUND_LABEL_SE_COINOOO);

				if (g_aItem[nCntItem].nType == ITEMTYPE_COIN)
				{
					AddScore(100);
				}

				else if (g_aItem[nCntItem].nType == ITEMTYPE_COIN2)
				{
					AddScore(500);
				}

				g_nNumCoin--;						//�R�C���̑��������炷
				if(g_nNumCoin <= 0)
				{//0�ɂȂ�����
					StopTimer();
					SetFade(MODE_GAMECLEAR);
				}
			}
		}
	}
	return bGet;
}

//=============================================================================
// �A�C�e���̎擾
//=============================================================================
Item *GetItem(void)
{
	return &g_aItem[0];
}

//=============================================================================
// �A�C�e���̑������擾
//=============================================================================
int GetCoin(void)
{
	return g_nNumCoin;
}
