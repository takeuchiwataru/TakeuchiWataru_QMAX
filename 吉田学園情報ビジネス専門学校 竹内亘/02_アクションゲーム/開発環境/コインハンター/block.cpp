//=============================================================================
//
// �u���b�N���� [block.cpp]
// Author :�|���j
//
//=============================================================================
#include "block.h"
#include "player.h"
#include "explosion.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_BLOCK			(256 * 2)							//�u���b�N�̍ő吔
#define BLOCK_TEXTURENAME	"data/TEXTURE/block000.jpg"			//�e�N�X�`����
#define BLOCK_TEXTURENAME2	"data/TEXTURE/block500.png"			//�e�N�X�`����
#define BLOCK_TEXTURENAME3	"data/TEXTURE/block100.png"			//�e�N�X�`����
#define BLOCK_TEXTURENAME4	"data/TEXTURE/bane.png"				//�e�N�X�`����
#define BLOCK_TEXTURENAME5	"data/TEXTURE/block200.jpg"			//�e�N�X�`����

#define BLOCK_SIZE			(20)								//�u���b�N�̑傫��
#define BLOCK_SIZE1			(100)								//�u���b�N�̑傫��
#define BLOCK_X				(200)								//�u���b�N��X���W
#define BLOCK_Y				(50)								//�u���b�N��Y���W
#define MAX_TYPE_BLOCK		(30)								//�u���b�N�̎��
//#define POLYGON_X			(1200)								//�|���S����X���W
//#define POLYGON_Y			(350)								//�|���S����Y���W

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureBlock[MAX_TYPE_BLOCK] = {};	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Block g_aBlock[MAX_BLOCK];


//=============================================================================
// �u���b�N�̏���������
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�u���b�N�̏��̊e������
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_aBlock[nCntBlock].fWidth = 0.0f;
		g_aBlock[nCntBlock].fHeight = 0.0f;
		g_aBlock[nCntBlock].nType = BLOCKTYPE_NOMALL;
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBlock[nCntBlock].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME2, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME2, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME3, &g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME3, &g_pTextureBlock[4]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME4, &g_pTextureBlock[5]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TEXTURENAME5, &g_pTextureBlock[6]);

	//���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,						//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&g_pVtxBuffBlock,
								NULL);
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y , 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y , 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

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
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̏I������
//=============================================================================
void UninitBlock(void)
{
	int nCntTex;

	for (nCntTex = 0; nCntTex < MAX_TYPE_BLOCK; nCntTex++)
	{
		//�e�N�X�`���̊J��
		if (g_pTextureBlock[nCntTex] != NULL)
		{
			g_pTextureBlock[nCntTex]->Release();
			g_pTextureBlock[nCntTex] = NULL;
		}

		//���_�o�b�t�@�̊J��
		if (g_pVtxBuffBlock != NULL)
		{
			g_pVtxBuffBlock->Release();
			g_pVtxBuffBlock = NULL;
		}
	}

}

//=============================================================================
// �u���b�N�̍X�V����
//=============================================================================
void UpdateBlock(void)
{
	int nCntBlock;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			pVtx += 4;	//���_�f�[�^���S���i�߂�
		}
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}

//=============================================================================
// �u���b�N�̕`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBlock;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for(nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)	//�u���b�N���g�p����Ă���
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntBlock].nType]);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
									nCntBlock * 4,
									2);
		}
	}
}

//=============================================================================
// �u���b�N�̐ݒ菈��
//=============================================================================
void SetBlock(D3DXVECTOR3 pos,float fWidth, float fHeight,BLOCKTYPE nType)
{
	//�u���b�N�𕪊�����ϐ�
	float  fBlockHeight;
	float  fBlockWidth;

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].nType = nType;

			g_aBlock[nCntBlock].fHeight = fHeight;
			g_aBlock[nCntBlock].fWidth = fWidth;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight, 0.0f);

			//���_�J���[
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			fBlockHeight = g_aBlock[nCntBlock].fHeight / 50;
			fBlockWidth = g_aBlock[nCntBlock].fWidth / 50;

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fBlockWidth, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, fBlockHeight);
			pVtx[3].tex = D3DXVECTOR2(fBlockWidth, fBlockHeight);

			if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BERUTOKONBEA)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			}
			else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BERUTOKONBEA2)
			{
				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			}
			else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_PUSH)
			{

			}

			g_aBlock[nCntBlock].bUse = true;	//�g�p���Ă�
			break;
		}
		pVtx += 4;	//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
// �u���b�N�̓����蔻��
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove ,float * fWidth, float * fHeight ,Block **pBlock)
{
	int nCntBlock;

	bool bLand = false;			//���n�������ǂ���

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�u���b�N���g���Ă���
			if (pPos->x + (*fWidth / 2) > g_aBlock[nCntBlock].pos.x &&
				pPos->x - (*fWidth / 2) < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
			{//�c����
				if (pPos->y >= g_aBlock[nCntBlock].pos.y && pPosold->y <= g_aBlock[nCntBlock].pos.y)
				{//�ォ��߂荞�񂾏ꍇ
					bLand = true;
					pPos->y = g_aBlock[nCntBlock].pos.y;
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BERUTOKONBEA)
					{//�x���g�R���x�A�E
						g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;		//���ړ�
						pPos->x = pPosold->x + 7;
						pMove->y = 0.0f;
					}
					else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BERUTOKONBEA2)
					{//�x���g�R���x�A��
						g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;		//���ړ�
						pPos->x = pPosold->x - 3;
						pMove->y = 0.0f;
					}
					//else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BERUTOKONBEA3)
					//{//�x���g�R���x�A��
					//	g_aBlock[nCntBlock].pos.x += g_aBlock[nCntBlock].move.x;		//���ړ�
					//	pPos->x = pPosold->x + 5;
					//	pMove->y = 0.0f;
					//}

					else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_JUMP)
					{//�W�����v�u���b�N
						g_aBlock[nCntBlock].pos.y += g_aBlock[nCntBlock].move.y;		//�c�ړ�
						pMove->y = -6.0f;
						PlaySound(SOUND_LABEL_SE_JUMP001);
					}
					else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_FALL)
					{//�����u���b�N
						g_aBlock[nCntBlock].pos.y = g_aBlock[nCntBlock].pos.y * 10.0f;
					}
					else if (g_aBlock[nCntBlock].nType == BLOCKTYPE_PUSH)
					{//������u���b�N
						pMove->y = 0.0f;
					}
					//if (g_aBlock[nCntBlock].pos.y >= 680)
					//{//���}���u�Ŏg����
					//	g_aBlock[nCntBlock].pos.y = 680;
					//	g_aBlock[nCntBlock].move.y = 0.0f;
					//	g_aBlock[nCntBlock].bUse = false;
					//}
				}
				else if (pPos->y - *fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight &&
					pPosold->y - *fHeight  >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{//������߂荞�񂾏ꍇ
					pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight + *fHeight;
					pMove->y = 0.0f;

					if (g_aBlock[nCntBlock].nType == BLOCKTYPE_BREAK)
					{//�󂹂�u���b�N
						g_aBlock[nCntBlock].bUse = false;
						//SetExplosion(g_aBlock[nCntBlock].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
						PlaySound(SOUND_LABEL_SE_BREAK);

					}
				}
				else if (pPos->y > g_aBlock[nCntBlock].pos.y  &&
					pPos->y - (*fHeight / 2) - 10 < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight)
				{//������
					if (pPos->x + *fWidth + 10 >= g_aBlock[nCntBlock].pos.x &&
						pPosold->x - *fWidth +10 <= g_aBlock[nCntBlock].pos.x)
					{//������߂荞�񂾏ꍇ
						pPos->x = g_aBlock[nCntBlock].pos.x - *fWidth + 10;
						//pPosold->x = g_aBlock[nCntBlock].pos.x - *fWidth + 10;
						pMove->x = 0.0f;

						if (g_aBlock[nCntBlock].nType == BLOCKTYPE_PUSH)
						{//������u���b�N
							g_aBlock[nCntBlock].pos.x = g_aBlock[nCntBlock].pos.x + 3.0f;			//���ړ�
							PlaySound(SOUND_LABEL_SE_OSU);

						}

					}
					else if (pPos->x - *fWidth - 10<= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth &&
						pPosold->x + *fWidth -10 >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth)
					{//�E����߂荞�񂾏ꍇ
						pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + *fWidth  - 10;
						//pPosold->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth + *fWidth - 10;
						pMove->x = 0.0f;
						if (g_aBlock[nCntBlock].nType == BLOCKTYPE_PUSH)
						{//������u���b�N
							g_aBlock[nCntBlock].pos.x = g_aBlock[nCntBlock].pos.x - 2.0f;		//���ړ�
							PlaySound(SOUND_LABEL_SE_OSU);
						}
					}
				}
			}
		}
	}
	//if (pBlock != NULL)
	//{//��Ŏg��
	//	*pBlock = &g_aBlock[];
	//}
	return bLand;
}
