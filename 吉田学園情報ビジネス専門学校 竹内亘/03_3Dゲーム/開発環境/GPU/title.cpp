//=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : �|���j
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "fade.h"
#include "pressenter.h"
#include "camera.h"
#include "light.h"
#include "meshField.h"
#include "meshWall.h"
#include "model.h"
#include "billboard.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLE_TEXTURE_NAME  "data/TEXTURE/block100.png"				// �ǂݍ��ރe�N�X�`���t�@�C����
#define TITLE_POS_X         (0)                         // �w�i�̍���w���W
#define TITLE_POS_Y         (0)                         // �w�i�̍���x���W
#define TITLE_WIDTH         (SCREEN_WIDTH)              // �w�i�̕�
#define TITLE_HEIGHT        (SCREEN_HEIGHT)             // �w�i�̍���

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureTitle = NULL;		// �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		// ���_�o�b�t�@�ւ̃|�C���^ 
int                     g_nCounterTitle;			// �����L���O��ʂɑJ�ڂ���^�C�~���O 
D3DXVECTOR3 g_posTitle;								// �ʒu
D3DXVECTOR3 g_rotTitle;								// ����
D3DXMATRIX g_mtxWorldTitle;							// ���[���h�}�g���b�N�X

//=============================================================================
// ����������
//=============================================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	g_nCounterTitle = 0;

	//// �e�N�X�`���̓ǂݍ���
	//D3DXCreateTextureFromFile(pDevice,
	//	TITLE_TEXTURE_NAME,
	//	&g_pTextureTitle);

	//// ���_�o�b�t�@�̐���
	//pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	//	D3DUSAGE_WRITEONLY,
	//	FVF_VERTEX_2D,
	//	D3DPOOL_MANAGED,
	//	&g_pVtxBuffTitle,
	//	NULL);

	//VERTEX_2D *pVtx;   // ���_���ւ̃|�C���^

	//// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	//g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//// ���_���W
	//pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);

	//// ���_�e�N�X�`��
	//pVtx[0].rhw = 1.0f;
	//pVtx[1].rhw = 1.0f;
	//pVtx[2].rhw = 1.0f;
	//pVtx[3].rhw = 1.0f;

	////// �@���̐ݒ�
	////pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	////pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	////pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	////pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//// ���_�J���[
	//pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//// �e�N�X�`�����W�̐ݒ�
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//// ���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffTitle->Unlock();

	// �J�����̏���������
	InitCamera();

	// ���C�g�̏���������
	InitLight();

	// ���b�V���t�B�[���h�̏���������
	InitmeshField();

	//// ���b�V���t�B�[���h2�̏���������
	//InitMeshField2();

	// ���b�V���E�H�[���̏���������
	InitMeshWall(0, D3DXVECTOR3(-25.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
	InitMeshWall(1, D3DXVECTOR3(-25.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));
	InitMeshWall(2, D3DXVECTOR3(725.0f, 50.0f, 725.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
	InitMeshWall(3, D3DXVECTOR3(725.0f, 50.0f, -25.0f), D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));

	// ���f���̏���������
	InitModel();
	SetModel(D3DXVECTOR3(715.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH);
	SetModel(D3DXVECTOR3(715.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH);
	SetModel(D3DXVECTOR3(-15.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH2);
	SetModel(D3DXVECTOR3(-15.0f, 0.0f, 695.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BENCH2);

	SetModel(D3DXVECTOR3(400.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA);
	SetModel(D3DXVECTOR3(200.0f, 0.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA);
	SetModel(D3DXVECTOR3(540.0f, 0.0f, 350.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA2);
	SetModel(D3DXVECTOR3(100.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_TAIYA2);

	SetModel(D3DXVECTOR3(100.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BURANKO);
	SetModel(D3DXVECTOR3(170.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_BURANKO);
	SetModel(D3DXVECTOR3(500.0f, 0.0f, 600.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_SLIDE);
	SetModel(D3DXVECTOR3(300.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_JG);
	SetModel(D3DXVECTOR3(600.0f, 0.0f, 120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), MODELTYPE_SEESAW);

	// �r���{�[�h�̏���������
	InitBillboard();
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, 10.0f));
	SetBillboard(D3DXVECTOR3(50.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(100.0f, 0.0f, 650.0f));
	SetBillboard(D3DXVECTOR3(200.0f, 0.0f, 50.0f));
	SetBillboard(D3DXVECTOR3(200.0f, 0.0f, 500.0f));
	SetBillboard(D3DXVECTOR3(250.0f, 0.0f, 250.0f));
	SetBillboard(D3DXVECTOR3(300.0f, 0.0f, 650.0f));
	SetBillboard(D3DXVECTOR3(350.0f, 0.0f, 500.0f));
	SetBillboard(D3DXVECTOR3(400.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(450.0f, 0.0f, 560.0f));
	SetBillboard(D3DXVECTOR3(500.0f, 0.0f, 100.0f));
	SetBillboard(D3DXVECTOR3(500.0f, 0.0f, 10.0f));
	SetBillboard(D3DXVECTOR3(550.0f, 0.0f, 400.0f));
	SetBillboard(D3DXVECTOR3(600.0f, 0.0f, 600.0f));
	SetBillboard(D3DXVECTOR3(650.0f, 0.0f, 50.0f));
	SetBillboard(D3DXVECTOR3(700.0f, 0.0f, 340.0f));

}
//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	// �J�����̏I������
	UninitCamera();

	// ���C�g�̏I������
	UninitLight();

	// ���b�V���t�B�[���h�̏I������
	UninitmeshField();

	//// ���b�V���t�B�[���h2�̏I������
	//UninitMeshField2();

	// ���b�V���E�H�[���̏I������
	UninitMeshWall();

	// ���f���̏I������
	UninitModel();

	// �r���{�[�h�̏I������
	UninitBillboard();

	// �e�N�X�`���̔j��
	if (g_pTextureTitle != NULL)
	{
		g_pTextureTitle->Release();
		g_pTextureTitle = NULL;
	}

	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
}
//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	// �J�����̍X�V����
	UpdateCamera();

	// ���C�g�̍X�V����
	UpdateLight();

	// ���b�V���t�B�[���h�̍X�V����
	UpdatemeshField();

	//// ���b�V���t�B�[���h2�̍X�V����
	//UpdateMeshField2();

	// ���b�V���E�H�[���̍X�V����
	UpdateMeshWall();

	// ���f���̍X�V����
	UpdateModel();

	// �r���{�[�h�̍X�V����
	UpdateBillboard();

	FADE *pFade;
	pFade = GetFade();
	bool *disp;
	disp = GetDispPressEnter();

	g_nCounterTitle++;

	if(GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{// ENTER�L�[�������ꂽ
		SetFade(MODE_TUTORIAL);
		PlaySound(SOUND_LABEL_SE_ENTER000);  // ���艹�𗬂�
		//StopSound(SOUND_LABEL_SE_ENTER000);
	}

	if (g_nCounterTitle % 500 == 0 && *pFade == FADE_NONE)
	{// ��莞�Ԃ�����
		SetFade(MODE_RANKING);
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	// �J�����̐ݒ�
	SetCamera();

	// ���b�V���t�B�[���h�̕`�揈��
	DrawmeshField();

	//// ���b�V���t�B�[���h2�̕`�揈��
	//DrawMeshField2();

	// ���b�V���E�H�[���̕`�揈��
	DrawMeshWall();

	// ���f���̕`�揈��
	DrawModel();

	// �r���{�[�h�̕`�揈��
	DrawBillboard();

	//D3DXMATRIX mtxView, mtxTrans;				//�v�Z�p�}�g���b�N�X

	//// ���[���h�}�g���b�N�X�̏�����
	//D3DXMatrixIdentity(&g_mtxWorldTitle);

	//pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//g_mtxWorldTitle._11 = mtxView._11;
	//g_mtxWorldTitle._12 = mtxView._21;
	//g_mtxWorldTitle._13 = mtxView._31;
	//g_mtxWorldTitle._21 = mtxView._12;
	//g_mtxWorldTitle._22 = mtxView._22;
	//g_mtxWorldTitle._23 = mtxView._32;
	//g_mtxWorldTitle._31 = mtxView._13;
	//g_mtxWorldTitle._32 = mtxView._23;
	//g_mtxWorldTitle._33 = mtxView._33;

	//// �ʒu�𔽉f
	//D3DXMatrixTranslation(&mtxTrans, g_posTitle.x, g_posTitle.y, g_posTitle.z);
	//D3DXMatrixMultiply(&g_mtxWorldTitle, &g_mtxWorldTitle, &mtxTrans);

	//// ���[���h�}�g���b�N�X�̐ݒ�
	//pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldTitle);

	//// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	//pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//// ���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_2D);

	//// �e�N�X�`���̐ݒ�
	//pDevice->SetTexture(0, g_pTextureTitle);

	//// �^�C�g����ʂ̕`��
	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
	//	0,
	//	2);
}