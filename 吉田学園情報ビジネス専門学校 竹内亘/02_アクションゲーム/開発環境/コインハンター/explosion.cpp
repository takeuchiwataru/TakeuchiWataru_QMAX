//=============================================================================
//
// �e�̔������� [explosion.cpp]
// Author :�|���j
//
//=============================================================================
#include "explosion.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_EXPLOSION			(256)													// �����̍ő吔
#define EXPLOSION_TEXTURE_NAME	"data/TEXTURE/explosion000.png"								// �ǂݍ��ރe�N�X�`����
#define EXPLOSION_ANIM_X		((0.125f * g_aExplosion[nCntExplosion].nPatternAnim))	// �ǂݍ��ރe�N�X�`���̃p�^�[��
#define EXPLOSION_HEIGHT		(30)													// �����̍���
#define EXPLOSION_WIDTH			(30)													// �����̕�

//*****************************************************************************
// �O���[�o���ϐ��錾
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureExplosion = NULL;	//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;	//���_�o�b�t�@�ւ̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];				//�g�p���Ă��邩�ǂ���

//=============================================================================
// �����̏���������
//=============================================================================
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�����̏�����
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(0.0f, 1.0f, 1.0f,1.0f);
		g_aExplosion[nCntExplosion].nCounterAnim = 0;
		g_aExplosion[nCntExplosion].nPatternAnim = 0;
		g_aExplosion[nCntExplosion].fHeight = EXPLOSION_HEIGHT;
		g_aExplosion[nCntExplosion].fWidth = EXPLOSION_WIDTH;
		g_aExplosion[nCntExplosion].bUse = false;
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TEXTURE_NAME, &g_pTextureExplosion);

	//���_���̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,						//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&g_pVtxBuffExplosion,
								NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + 0, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + 0, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

		//�e�N�X�`�����W�̐ݒ�
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;	//���_�f�[�^���S���i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �����̏I������
//=============================================================================
void UninitExplosion(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}

	//���_�o�b�t�@�̊J��
	if (g_pTextureExplosion != NULL)
	{
		g_pTextureExplosion->Release();
		g_pTextureExplosion = NULL;
	}
}

//=============================================================================
// �����̍X�V����
//=============================================================================
void UpdateExplosion(void)
{
	int nCntExplosion;

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].nCounterAnim++;

		if ((g_aExplosion[nCntExplosion].nCounterAnim % 5) == 0)
		{
			if (g_aExplosion[nCntExplosion].bUse == true)	//�������g�p����Ă���
			{
				//�p�^�[��No.���X�V
				g_aExplosion[nCntExplosion].nPatternAnim = (g_aExplosion[nCntExplosion].nPatternAnim + 1) % 8;

				//�e�N�X�`�����W�̍X�V
				pVtx[0].tex = D3DXVECTOR2(0.0f + EXPLOSION_ANIM_X, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.125f + EXPLOSION_ANIM_X, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(0.0f + EXPLOSION_ANIM_X, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(0.125f + EXPLOSION_ANIM_X, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim == 0)
				{
					g_aExplosion[nCntExplosion].bUse = false;	//�g�p���Ă��Ȃ���Ԃɂ���
				}
			}
		}
		pVtx +=  4;	//�Y���̈ʒu�܂Ői�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pVtxBuffExplosion->Unlock();
}

//=============================================================================
// �����̕`�揈��
//=============================================================================
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureExplosion);

	//�|���S���̕`��
	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)	//�������g�p����Ă���
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
									4 * nCntExplosion,
									2);
		}
	}
}

//=============================================================================
// �����̐ݒ菈��
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col)
{
	int nCntExplosion;

	for(nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{
			VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

			//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntExplosion * 4);	//�Y���̈ʒu�܂Ői�߂�

			g_aExplosion[nCntExplosion].pos = pos;
			g_aExplosion[nCntExplosion].move = move;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y - EXPLOSION_HEIGHT, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + 0, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + EXPLOSION_WIDTH, g_aExplosion[nCntExplosion].pos.y + 0, 0.0f);

			g_aExplosion[nCntExplosion].col = col;

			//���_�J���[
			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			g_aExplosion[nCntExplosion].nPatternAnim = 0;
		
			////�e�N�X�`�����W�̐ݒ�
			//pVtx[0].tex = D3DXVECTOR2(0.0f + EXPLOSION_ANIM_X, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(0.125f + EXPLOSION_ANIM_X, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(0.0f + EXPLOSION_ANIM_X, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(0.125f + EXPLOSION_ANIM_X, 1.0f);
			//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			//���_�o�b�t�@���A�����b�N
			g_pVtxBuffExplosion->Unlock();

			g_aExplosion[nCntExplosion].nCounterAnim = 0;
			g_aExplosion[nCntExplosion].bUse = true;	//�g�p���Ă�����
			break;
		}
	}
}