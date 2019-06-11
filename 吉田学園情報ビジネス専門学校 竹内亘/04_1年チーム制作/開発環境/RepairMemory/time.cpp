//=============================================================================
//
// �w�i���� [time.cpp]
// Author : ��������
//
//=============================================================================
#include "time.h"
#include "game.h"
#include "score.h"
#include "flontpolygon.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_TIME		"data/TEXTURE/number003.png"						// �ǂݍ��ރe�N�X�`���t�@�C����
#define TIME_NUM			(3)													//�\�����錅��
#define TIME_RIMIT			(60 * 300)											//��������
#define TIME_SIZE			(50.0f)												//�|���S���̑傫��
#define TIME_RED			(60 * 30)											//�^�C����Ԃɂ���b��
#define TIME_POS			((SCREEN_WIDTH / 2) - ((TIME_SIZE * TIME_NUM) / 2))	//�������Ԃ̃|�W�V����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;			// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;			// ���_�o�b�t�@�ւ̃|�C���^
int		g_aTime[TIME_NUM];								// �������i�[����ϐ�
Time	g_Time;

//=============================================================================
// ����������
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�ϐ��錾
	int nCntTime;
	
	g_Time.nTime = TIME_RIMIT;
	g_Time.TimeState = TIMESTATE_STOP;

	for (nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		g_aTime[nCntTime] = 0;
	}
	
	//�J�E���g�_�E���̌v�Z
	CntDownTime();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
							  TEXTURE_TIME,			// �t�@�C���̖��O
							  &g_pTextureTime);		// �e�N�X�`���ւ̃|�C���^

	// ���_���̍쐬
	MakeVertexTime(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitTime(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTime(void)
{
	// ���_����ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//�ϐ��錾
	int nCntTime;

	bool bDeletePartsTuxture = DeletePartsTexture();

	switch (g_Time.TimeState)
	{//�^�C����Ԃ̐ݒ�
	case TIMESTATE_NORMAL:
		break;

	case TIMESTATE_STOP:
		g_Time.nTime = g_Time.nTime;
		break;

	case TIMESTATE_END:
		g_Time.TimeState = TIMESTATE_NONE;
		SetFade(MODE_GAMEOVER);
		break;

	case TIMESTATE_START:
		g_Time.nTime = TIME_RIMIT;		//���Ԃ�����������
		SetTimeState(TIMESTATE_NORMAL);
		break;
	}

	if (g_Time.TimeState == TIMESTATE_NORMAL && bDeletePartsTuxture == false)
	{
		g_Time.nTime--;		//���Ԃ��J�E���g�_�E��

		if ((g_Time.nTime % 60) == 0)	//���ԕ\���v�Z
		{
			//�J�E���g�_�E���̌v�Z
			CntDownTime();

			if (g_Time.nTime == 0)
			{
				g_Time.TimeState = TIMESTATE_END;	//�^�C���I����Ԃɂ���
			}
		}	

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aTime[nCntTime]), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aTime[nCntTime]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aTime[nCntTime]), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aTime[nCntTime]), 1.0f);

			if (g_Time.nTime <= 300)		//�c��T�b�ŐԂ�����
			{//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}

			//�Y���̈ʒu�܂Ői�߂�
			pVtx += 4;
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTime->Unlock();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTime(void)
{
	//�ϐ��錾
	int nCntTime;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureTime);

	// �|���S���̕`��
	for (nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCntTime * 4,
			2);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntTime;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * TIME_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// ���_����ݒ�
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

							//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(TIME_POS + 0.0f + (TIME_SIZE * nCntTime), 15.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TIME_POS + TIME_SIZE + (TIME_SIZE * nCntTime), 15.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TIME_POS + 0.0f + (TIME_SIZE * nCntTime), TIME_SIZE + 15.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TIME_POS + TIME_SIZE + (TIME_SIZE * nCntTime), TIME_SIZE + 15.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.4f, 0.5f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.4f, 0.5f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.4f, 0.5f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.4f, 0.5f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// ���Ԃ̏���
//=============================================================================
void CntDownTime(void)
{
	//�ϐ��錾
	int nNum = 1;
	int nNum2 = 1;
	int nCntNum;
	int nTime;

	//�����̌v�Z
	for (nCntNum = 0; nCntNum < TIME_NUM; nCntNum++)
	{
		nNum *= 10;
	}
	for (nCntNum = 0; nCntNum < TIME_NUM - 1; nCntNum++)
	{
		nNum2 *= 10;
	}

	nTime = g_Time.nTime / 60;	//�b���̌v�Z

	for (nCntNum = 0; nCntNum < TIME_NUM; nCntNum++)
	{
		g_aTime[nCntNum] = (nTime % nNum) / nNum2;	//�i�[���鐔�����v�Z

													//�������P�����炷
		nNum = nNum / 10;
		nNum2 = nNum2 / 10;

		if (nCntNum == TIME_NUM - 1)
		{//����������
			nNum = 100;
			nNum2 = 10;
		}
	}
}

//=============================================================================
// ���Ԃ̏��
//=============================================================================
Time *GetTime(void)
{
	return &g_Time;
}

//=============================================================================
// ���Ԃ̏��
//=============================================================================
void SetTimeState(TIME state)
{
	int nCntTime;

	if (state == TIMESTATE_ADD)
	{
		AddScore(g_Time.nTime / 6);
	}
	else if (state == TIMESTATE_RESET)
	{
		g_Time.nTime = TIME_RIMIT;
		
		CntDownTime();

		// ���_����ݒ�
		VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
		g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

		for (nCntTime = 0; nCntTime < TIME_NUM; nCntTime++)
		{
			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * g_aTime[nCntTime]), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * g_aTime[nCntTime]), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * g_aTime[nCntTime]), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * g_aTime[nCntTime]), 1.0f);

			//�Y���̈ʒu�܂Ői�߂�
			pVtx += 4;
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffTime->Unlock();
	}
	else
	{
		g_Time.TimeState = state;
	}
}