//=============================================================================
//
// �}�[�N�̏��� [mark.cpp]
// Author : �������� Sato_Asumi
//
//=============================================================================
#include "mark.h"
#include "shadow.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_NAME	"data\\TEXTURE\\mark.png"		//�ǂ݂��ރe�N�X�`���t�@�C����
#define MAX_MARK		(4)								//�ǂ̍ő吔
#define CHANGE_MOVE		(0.3f)							//�ω���
#define CHANGE_COUNTER	(40)							//�ω��ʃJ�E���^�[

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
void MakeVertexMark(LPDIRECT3DDEVICE9 pDevice);

//=============================================================================
// �O���[�o���ϐ�
//=============================================================================
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMark = NULL;	//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9		g_pTextureMark = NULL;	// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR2				g_texMark;				//�e�N�X�`��
Mark					g_Mark[MAX_MARK];		//�ǂ̏��

//=============================================================================
// ����������
//=============================================================================
void InitMark(void)
{
	//�ϐ��錾
	int nCntMark;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();		// �f�o�C�X�̎擾

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
							  TEXTURE_NAME,
						      &g_pTextureMark);

	//�ϐ��̏�����
	for (nCntMark = 0; nCntMark < MAX_MARK; nCntMark++)
	{
		g_Mark[nCntMark].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S���W
		g_Mark[nCntMark].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
		g_Mark[nCntMark].Oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
		g_Mark[nCntMark].ChangeMove = 0.0f;							//�ω���
		g_Mark[nCntMark].nCntMove = 0;								//�ω��ʃJ�E���^�[
		g_Mark[nCntMark].bUse = false;								//�g�p���Ă��邩�ǂ���
	}

	// ���_���̍쐬
	MakeVertexMark(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitMark(void)
{
	//�e�N�X�`���̊J��
	if (g_pTextureMark != NULL)
	{
		g_pTextureMark->Release();
		g_pTextureMark = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMark != NULL)
	{
		g_pVtxBuffMark->Release();
		g_pVtxBuffMark = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMark(void)
{
	//�ϐ��錾
	int nCntMark;

	for (nCntMark = 0; nCntMark < MAX_MARK; nCntMark++)
	{
		if (g_Mark[nCntMark].bUse == true)
		{
			//�J�E���^�[�̉��Z
			g_Mark[nCntMark].nCntMove++;

			if ((g_Mark[nCntMark].nCntMove % CHANGE_COUNTER) == 0)
			{//��莞�Ԃ��o�߂�����
				g_Mark[nCntMark].ChangeMove *= -1;	//������ς���
			}

			//�ړ��ʂ̍X�V
			g_Mark[nCntMark].move.y = g_Mark[nCntMark].ChangeMove;

			//�ʒu�̍X�V
			g_Mark[nCntMark].pos += g_Mark[nCntMark].move;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMark(void)
{
	//�ϐ��錾
	int nCntMark;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX		  mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X
	D3DXMATRIX		  mtxView;					//�r���[�}�g���N�X

	//�A���t�@�e�X�g������L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	for (nCntMark = 0; nCntMark < MAX_MARK; nCntMark++)
	{
		if (g_Mark[nCntMark].bUse == true)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Mark[nCntMark].mtxWorld);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�t�s���ݒ�
			g_Mark[nCntMark].mtxWorld._11 = mtxView._11;
			g_Mark[nCntMark].mtxWorld._12 = mtxView._21;
			g_Mark[nCntMark].mtxWorld._13 = mtxView._31;
			g_Mark[nCntMark].mtxWorld._21 = mtxView._12;
			g_Mark[nCntMark].mtxWorld._22 = mtxView._22;
			g_Mark[nCntMark].mtxWorld._23 = mtxView._32;
			g_Mark[nCntMark].mtxWorld._31 = mtxView._13;
			g_Mark[nCntMark].mtxWorld._32 = mtxView._23;
			g_Mark[nCntMark].mtxWorld._33 = mtxView._33;

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Mark[nCntMark].pos.x, g_Mark[nCntMark].pos.y, g_Mark[nCntMark].pos.z);
			D3DXMatrixMultiply(&g_Mark[nCntMark].mtxWorld, &g_Mark[nCntMark].mtxWorld, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Mark[nCntMark].mtxWorld);

			// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffMark, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureMark);

			// �|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntMark * 4,
				2);
		}
	}

	//�A���t�@�e�X�g�����𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexMark(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	int nCntMark;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_MARK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMark,
		NULL);

	VERTEX_3D * pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffMark->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMark = 0; nCntMark < MAX_MARK; nCntMark++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-13.0f, 26.0f, 00.0f);
		pVtx[1].pos = D3DXVECTOR3(13.0f, 26.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-13.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(13.0f, 0.0f, 0.0f);

		//�@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//�Y���̈ʒu�܂Ői�߂�
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMark->Unlock();
}

//=============================================================================
// �ݒ���
//=============================================================================
int SetMark(D3DXVECTOR3 pos)
{
	//�ϐ��錾
	int nCntMark;
	int nNumMark = 0;

	for (nCntMark = 0; nCntMark < MAX_MARK; nCntMark++)
	{
		if (g_Mark[nCntMark].bUse == false)
		{
			g_Mark[nCntMark].pos = pos;
			g_Mark[nCntMark].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Mark[nCntMark].ChangeMove = 0.1f;
			g_Mark[nCntMark].nCntMove = 0;
			g_Mark[nCntMark].bUse = true;
			nNumMark = nCntMark;
			break;
		}
	}
	
	return nNumMark;
}

//=============================================================================
// �}�[�N������
//=============================================================================
void DeleteMark(void)
{
	//�ϐ��錾
	int nCntMark;

	for (nCntMark = 0; nCntMark < MAX_MARK; nCntMark++)
	{
		if (g_Mark[nCntMark].bUse == true)
		{
			g_Mark[nCntMark].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S���W
			g_Mark[nCntMark].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
			g_Mark[nCntMark].Oldpos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
			g_Mark[nCntMark].ChangeMove = 0.0f;							//�ω���
			g_Mark[nCntMark].nCntMove = 0;								//�ω��ʃJ�E���^�[
			g_Mark[nCntMark].bUse = false;								//�g�p���Ă��邩�ǂ���
		}
	}
}
void DeleteMark(int nIdxMark)
{
	if (g_Mark[nIdxMark].bUse == true)
	{
		g_Mark[nIdxMark].bUse = false;		//�g�p���Ă��Ȃ���Ԃɂ���
	}
}