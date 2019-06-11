//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : ���� ����	Sato_Asumi
//
//=============================================================================
#include "score.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SCORE		"data/TEXTURE/number003.png"	//�ǂݍ��ރe�N�X�`���t�@�C����
#define NUM_SCORE			(6)								//�X�R�A�̌���
#define MOVE_POS			(40.0f)							//�ړ���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureScore = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
int						g_nScore;					// �X�R�A
int						g_aNum[NUM_SCORE];			// �P���ɐ������i�[����ϐ�
float					g_fScoreColor;

//=============================================================================
// ����������
//=============================================================================
void InitScore(void)
{
	//�ϐ��錾
	int nCntNum;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �X�R�A�̏�����
	g_nScore = 0;
	g_fScoreColor = 0.0f;

	for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
	{
		g_aNum[nCntNum] = 0;
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&g_pTextureScore);	// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexScore(pDevice);	
}

//=============================================================================
// �I������
//=============================================================================
void UninitScore(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pTextureScore != NULL)
	{
		g_pTextureScore->Release();
		g_pTextureScore = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateScore(void)
{
	//�ϐ��錾
	int nCntScore;

	QUESTSTATE pQuestState = GetQuestState();

	if (pQuestState == QUESTSTATE_CLEAR)
	{
		if (g_fScoreColor < 1.0f)
		{
			g_fScoreColor += 0.01f;
		}
		else
		{
			g_fScoreColor = 1.0f;
		}
	}

	// ���_����ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aNum[nCntScore]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aNum[nCntScore]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aNum[nCntScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aNum[nCntScore]), 1.0f);

		if (pQuestState == QUESTSTATE_CLEAR)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, g_fScoreColor);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, g_fScoreColor);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, g_fScoreColor);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, g_fScoreColor);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
		}

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawScore(void)
{	
	//�ϐ��錾
	int nCntScore;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureScore);

	// �|���S���̕`��
	for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
								nCntScore * 4,
								2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexScore(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntScore;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_SCORE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffScore,
		NULL);

	// ���_����ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(950.0f + 0.0f + (MOVE_POS * nCntScore), 15.0f , 0.0f);
		pVtx[1].pos = D3DXVECTOR3(950.0f + MOVE_POS + (MOVE_POS * nCntScore), 15.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(950.0f + 0.0f + (MOVE_POS * nCntScore), 75.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(950.0f + MOVE_POS + (MOVE_POS * nCntScore), 75.0f, 0.0f);

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

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void SetScore(int nValue)
{
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
	g_nScore = nValue;

	for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
	{
		g_aNum[nCntNum] = (g_nScore % nNum) / nNum2;	//�i�[���鐔�����v�Z

														//�������P�����炷
		nNum = nNum / 10;
		nNum2 = nNum2 / 10;
	}
}
void AddScore(int nValue)
{
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
	g_nScore += nValue;

	for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
	{
 		g_aNum[nCntNum] = (g_nScore % nNum) / nNum2;	//�i�[���鐔�����v�Z

		//�������P�����炷
		nNum = nNum / 10;
		nNum2 = nNum2 / 10;
	}
}

//========================================================================================
//�I������
//========================================================================================
int GetScore(void)
{
	return g_nScore;
}

//========================================================================================
//�X�R�A�����Z�b�g����
//========================================================================================
void ReSetScore(void)
{
	g_nScore = 0;

	//�ϐ��錾
	int nCntScore;
	int nCntNum;			//�X�R�A�̌����̃J�E���^�[

	for (nCntNum = 0; nCntNum < NUM_SCORE; nCntNum++)
	{
		g_aNum[nCntNum] = 0;
	}

	// ���_����ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aNum[nCntScore]), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aNum[nCntScore]), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aNum[nCntScore]), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aNum[nCntScore]), 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

//========================================================================================
//�X�R�A�ʒu�傫���ύX
//========================================================================================
void SetScore(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	//�ϐ��錾
	int nCntScore;

	QUESTSTATE pQuestState = GetQuestState();

	// ���_����ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntScore = 0; nCntScore < NUM_SCORE; nCntScore++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(pos.x + 0.0f + (fWidth * nCntScore), pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth + (fWidth * nCntScore), pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x + 0.0f + (fWidth * nCntScore), pos.y + fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth + (fWidth * nCntScore), pos.y + fHeight, 0.0f);
		//���_�J���[�̐ݒ�
		if (pQuestState == QUESTSTATE_REPORT)
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 0.0f);
		}
		else
		{
			pVtx[0].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.7f, 0.0f, 1.0f);
		}
		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

	g_fScoreColor = 0.0f;
}