//=============================================================================
//
// ��̏��� [sky.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "sky.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SKY_TEXTURE_NAME0   "data/TEXTURE/sky000.jpg"  // �ǂݍ��ރe�N�X�`���t�@�C����
#define DOME_LENGTH         (100)                      // �c�̒���
#define DOME_SIDE           (50)                       // ���̒���
#define DOME_RADIUS         (10000.0f)                 // ���a�̒���
#define DOME_HEIGHT         (10000.0f)                 // �����̒���
#define BLOCK_LENGTH        (4)                        // �c�̕�����
#define BLOCK_SIDE          (10)                       // ���̕�����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexSky(LPDIRECT3DDEVICE9 pDevice);
void MakeVertexSkyCover(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexSky(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureSky = NULL;    // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSky[2] = {};   // ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9  g_pIdxBuffSky = NULL;    // �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Sky                     g_Sky;                   // ��̏��
float                   g_Addtex = 0.0f;  

//=============================================================================
// ����������
//=============================================================================
void InitSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();   // �f�o�C�X�̎擾

	g_Sky.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ���S���W��������
	g_Sky.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ������������

	g_Sky.Length = DOME_LENGTH;             // �c�̒�����������
	g_Sky.Side = DOME_SIDE;                 // ���̒�����������
	g_Sky.XBlock = BLOCK_SIDE;              // ���̕�������ݒ�
	g_Sky.YBlock = BLOCK_LENGTH;            // �c�̕�������ݒ�
	g_Sky.nNumVertex = (g_Sky.XBlock + 1) * (g_Sky.YBlock + 1); // ���_����ݒ�
	g_Sky.nNumIndex = ((g_Sky.XBlock + 1) * (g_Sky.YBlock + 1)) + (2 * (g_Sky.YBlock - 1)) + (g_Sky.XBlock + 1) * (g_Sky.YBlock - 1);  // �C���f�b�N�X����ݒ�
	g_Sky.nNumPolygon = ((g_Sky.XBlock * g_Sky.YBlock) * 2) + ((g_Sky.YBlock - 1) * 4);  // �`�悷��|���S������ݒ�

	// ���_���̍쐬
	MakeVertexSky(pDevice);
	MakeVertexSkyCover(pDevice);

	// �C���f�b�N�X���̍쐬
	MakeIndexSky(pDevice);
}

//=============================================================================
// �I������
//=============================================================================
void UninitSky(void)
{
	// �e�N�X�`���̊J��
	if (g_pTextureSky != NULL)
	{
		g_pTextureSky->Release();
		g_pTextureSky = NULL;
	}
	

	// ���_�o�b�t�@�̊J��
	for (int nCntVertex = 0; nCntVertex < 2; nCntVertex++)
	{
		if (g_pVtxBuffSky[nCntVertex] != NULL)
		{
			g_pVtxBuffSky[nCntVertex]->Release();
			g_pVtxBuffSky[nCntVertex] = NULL;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (g_pIdxBuffSky != NULL)
	{
		g_pIdxBuffSky->Release();
		g_pIdxBuffSky = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateSky(void)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSky[0]->Lock(0, 0, (void**)&pVtx, 0);

	g_Addtex += 0.00002f;  // �����镪��i�߂�

	for (int nCntV = 0; nCntV < g_Sky.YBlock + 1; nCntV++)
	{//���������̕����������J��Ԃ�
		for (int nCntH = 0; nCntH < g_Sky.XBlock + 1; nCntH++)
		{//���������̕����������J��Ԃ�
			// �e�N�X�`�����W
			pVtx[nCntH].tex = D3DXVECTOR2(0.0f + (nCntH * (1.0f / g_Sky.XBlock)) + g_Addtex, 0.0f - (nCntV * (1.0f / g_Sky.YBlock)));
		}
		pVtx += g_Sky.XBlock + 1;       // ���_�̐擪�̔ԍ���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSky[0]->Unlock();

	g_Sky.rot.y += 0.00002f;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawSky(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;                // �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Sky.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Sky.rot.y, g_Sky.rot.x, g_Sky.rot.z);
	D3DXMatrixMultiply(&g_Sky.mtxWorld, &g_Sky.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Sky.pos.x, g_Sky.pos.y, g_Sky.pos.z);
	D3DXMatrixMultiply(&g_Sky.mtxWorld, &g_Sky.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Sky.mtxWorld);

	//-------------
	//  �ǂ̕`��
	//-------------

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffSky[0], 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetIndices(g_pIdxBuffSky);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureSky);
	

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_Sky.nNumVertex, 0, g_Sky.nNumPolygon);

	//-------------
	//  �W�̕`��
	//-------------

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, g_pVtxBuffSky[1], 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, g_Sky.XBlock);
}

//=============================================================================
// ���_���̍쐬(��)
//=============================================================================
void MakeVertexSky(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_Sky.nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSky[0],
		NULL);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		SKY_TEXTURE_NAME0,
		&g_pTextureSky);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSky[0]->Lock(0, 0, (void**)&pVtx, 0);

	float fAngle = 0;   // �p�x
	float fRadius = 0;  // ���a
	D3DXVECTOR3 pos;    // ���W

	fAngle = 0.0f;                         // �p�x��0��
	fRadius = cosf(0.0f) * DOME_RADIUS;    // ���a��ݒ�
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);   // ���W��ݒ�

	for (int nCntV = 0; nCntV < g_Sky.YBlock + 1; nCntV++)
	{//���������̕����������J��Ԃ�
		for (int nCntH = 0; nCntH < g_Sky.XBlock + 1; nCntH++)
		{//���������̕����������J��Ԃ�
			pos.x = sinf(-fAngle * D3DX_PI) * fRadius;
			pos.y = sinf(0.15f * nCntV) * DOME_HEIGHT - 500.0f;
			pos.z = cosf(-fAngle * D3DX_PI) * fRadius;

			// ���_���W
			pVtx[nCntH].pos = pos;

			// �@���x�N�g��
			pVtx[nCntH].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

			// ���_�J���[
			pVtx[nCntH].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W
			pVtx[nCntH].tex = D3DXVECTOR2(0.0f + 1.0f / (g_Sky.XBlock / 2), 0.0f + (1.0f * nCntV));

			fAngle += 1.0f / (g_Sky.XBlock / 2);  // �p�x��i�߂�

			if (fAngle >= 1.0f)
			{// �{����1�𒴂���
				fAngle = -1.0f;
			}
		}
		fRadius = cosf(0.26f * (nCntV + 1)) * DOME_RADIUS;   // ���a�����X�Ɍ���������
		fAngle = 0.0f;                                       // �p�x��0��
		pVtx += g_Sky.XBlock + 1;                            // ���_�̐擪�̔ԍ���i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSky[0]->Unlock();
}
//=============================================================================
// ���_���̍쐬(�W)
//=============================================================================
void MakeVertexSkyCover(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * (g_Sky.XBlock + 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSky[1],
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.33f, 1.0f);

	if (GetMode() == MODE_RANKING)
	{// �����L���O��ʂ�������
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffSky[1]->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(0.0f, DOME_HEIGHT, 0.0f);

	// �@���x�N�g��
	pVtx[0].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

	// ���_�J���[
	pVtx[0].col = col;

	float fAngle = 0;   // �p�x
	float fRadius = 0;  // ���a
	D3DXVECTOR3 pos;    // ���W

	fAngle = 0.0f;                                         // �p�x��0��
	fRadius = cosf(0.20f * (g_Sky.YBlock)) * DOME_RADIUS;  // ���a��ݒ�
	pos = D3DXVECTOR3(0.0f, sinf(0.15f * (g_Sky.YBlock)) * DOME_HEIGHT - 200.0f, 0.0f);  // ���W��ݒ�

	for (int nCntVer = 1; nCntVer < (g_Sky.XBlock + 2); nCntVer++)
	{// ���������̕����������J��Ԃ�
	    // ���_���W
		pos.x = sinf(-fAngle * D3DX_PI) * fRadius;
		pos.z = cosf(-fAngle * D3DX_PI) * fRadius;

		pVtx[nCntVer].pos = pos;

		// �@���x�N�g��
		pVtx[nCntVer].nor = D3DXVECTOR3(-0.22f, 0.87f, -0.44f);

		// ���_�J���[
		pVtx[nCntVer].col = col;

		fAngle += 1.0f / (g_Sky.XBlock / 2);  // �p�x��i�߂�

		if (fAngle >= 1.0f)
		{// �{����1�𒴂���
			fAngle = -1.0f;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffSky[1]->Unlock();
}
//=============================================================================
// �C���f�b�N�X���̍쐬
//=============================================================================
void MakeIndexSky(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_Sky.nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffSky,
		NULL);

	WORD *pIdx;      // �C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nCntIdx = 0; // �C���f�b�N�X�ԍ�

	// �C���f�b�N�X�o�b�t�@�����b�N��,�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffSky->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxY = 0; nCntIdxY < g_Sky.YBlock; nCntIdxY++)
	{// �c�̕��������J��Ԃ�
		for (int nCntIdxX = 0; nCntIdxX < g_Sky.XBlock + 1; nCntIdxX++, nCntIdx++)
		{// ���̕�����+�P�J��Ԃ�
		    // �㉺�̓���C���f�b�N�X�ԍ���ݒ�
			pIdx[0] = nCntIdx + g_Sky.XBlock + 1; // ����
			pIdx[1] = nCntIdx;                    // �㑤

			pIdx += 2;  // 2���i�߂�
			if (nCntIdxY < g_Sky.YBlock && nCntIdxX == g_Sky.XBlock)
			{// 1 , �������c�̕������̍ŉ��w�ł͂Ȃ�
			 // 2 , ���̕��������ݒ肪�I�����
				pIdx[0] = nCntIdx;                          // �㑤
				pIdx[1] = nCntIdx + (g_Sky.XBlock + 1) + 1; // ���̉���

				pIdx += 2; // 2���i�߂�
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffSky->Unlock();
}