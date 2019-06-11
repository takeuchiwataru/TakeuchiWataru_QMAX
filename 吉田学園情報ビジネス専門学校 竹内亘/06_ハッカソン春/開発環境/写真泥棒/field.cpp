//=============================================================================
//
// �n�ʂ̏��� [field.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "field.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FIELD_TEXTURENAME    "FIELD_TEXTURENAME"
#define FIELDSET             "FIELDSET"
#define END_FIELDSET         "END_FIELDSET"
#define MAX_FIELD            (30)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice);
void MakeIndexField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9      g_pTextureField[MAX_FIELD] = {}; // �e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField[MAX_FIELD] = {}; // ���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9  g_pIdxBuffField[MAX_FIELD] = {}; // �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
Field                   g_aField[MAX_FIELD];             // �t�B�[���h���
int                     g_SetField;                      // �t�B�[���h���Z�b�g������
int                     g_SetTexField;                   // �t�B�[���h�̃e�N�X�`�����Z�b�g������

//=============================================================================
// ����������
//=============================================================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	  // �f�o�C�X�̎擾

	FILE *pFile;           // �e�L�X�g�t�@�C���ւ̃|�C���^
	char str0[128];        // ����Ȃ�����
	char TexFileName[64];  // x�t�@�C���̖��O
	int TexType;           // �e�N�X�`���̎��
	D3DXVECTOR3 pos;       // �t�B�[���h�̍��W
	float Side;            // ��
	float Depth;           // ���s
	int XBlock;            // ���̕�����
	int ZBlock;            // ���s�̕�����
	g_SetTexField = 0;     // �e�N�X�`���t�@�C����ǂݍ��񂾉񐔂�������
	g_SetField = 0;        // �Z�b�g�����񐔂�������

	// �e�L�X�g�t�@�C�����J��
	pFile = fopen("data/TEXT/map.txt", "r");

	if (pFile != NULL)
	{// �e�L�X�g�t�@�C��������
		while (fscanf(pFile, "%s", &str0[0]) != EOF)
		{// �e�L�X�g�t�@�C���̖��[�܂ŕ���������s���󔒂�����܂œǂݎ��
			if (strcmp(&str0[0], FIELD_TEXTURENAME) == 0)
			{// �t�B�[���h�̃e�N�X�`���̃t�@�C������������Ă�����
				if (fscanf(pFile, "%s %s", &str0[0], &TexFileName[0]) == 2)
				{// �t�B�[���h�̃e�N�X�`���̃t�@�C������ǂݎ������
				 // �e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice,
						TexFileName,
						&g_pTextureField[g_SetTexField]);
				}
				g_SetTexField++;    // �e�N�X�`������ǂݍ��񂾉񐔂𑝂₷
			}
			if (strcmp(&str0[0], FIELDSET) == 0)
			{// �t�B�[���h�̃Z�b�g��񂪏�����Ă�����
				int nCntSet = 0;  // ����ݒ肵����
				while (strcmp(&str0[0], END_FIELDSET) != 0)
				{// �t�B�[���h�̐ݒ肪�I���܂ŌJ��Ԃ�
					if (nCntSet == FIELDSET_TEXTYPE)
					{// 1��ڂ�������
						if (fscanf(pFile, "%s %s %d", &str0[0], &str0[0], &TexType) == 3)
						{// ���W����ǂݎ������
							g_aField[g_SetField].TexType = TexType;  // �e�N�X�`���̎�ނ�ݒ�
						}
					}
					else if (nCntSet == FIELDSET_POS)
					{// 2��ڂ�������
						if (fscanf(pFile, "%s %f %f %f", &str0[0], &pos.x, &pos.y, &pos.z) == 4)
						{// ���W����ǂݎ������
							g_aField[g_SetField].pos = D3DXVECTOR3(pos.x, pos.y, pos.z);  // �ʒu��ݒ�
						}
					}
					else if (nCntSet == FIELDSET_ROT)
					{// 3��ڂ�������
						if (fscanf(pFile, "%s %f %f %f",&str0[0], &pos.x, &pos.y, &pos.z) == 4)
						{// ��������ǂݎ������
							g_aField[g_SetField].rot = D3DXVECTOR3(pos.x, pos.y, pos.z);  // ������ݒ�
						}
					}
					else if (nCntSet == FIELDSET_SIDE)
					{// 4��ڂ�������
						if (fscanf(pFile, "%s %f", &str0[0], &Side) == 2)
						{// ���̒�������ǂݎ������
							g_aField[g_SetField].Side = Side;  // ����ݒ�
						}
					}
					else if (nCntSet == FIELDSET_DEPTH)
					{// 5��ڂ�������
						if (fscanf(pFile, "%s %f", &str0[0], &Depth) == 2)
						{// ���s�̒�������ǂݎ������
							g_aField[g_SetField].Depth = Depth;  // ���s��ݒ�
						}
					}
					else if (nCntSet == FIELDSET_XBLOCK)
					{// 6��ڂ�������
						if (fscanf(pFile,  "%s %d", &str0[0], &XBlock) == 2)
						{// ���̕���������ǂݎ������
							g_aField[g_SetField].XBlock = XBlock;  // ���̕�������ݒ�
						}
					}
					else if (nCntSet == FIELDSET_ZBLOCK)
					{// 7��ڂ�������
						if (fscanf(pFile, "%s %d", &str0[0], &ZBlock) == 2)
						{// ���s�̕���������ǂݎ������
							g_aField[g_SetField].ZBlock = ZBlock;  // ���s�̕�������ݒ�
						}
					}
					fscanf(pFile, "%s", &str0[0]);
					nCntSet++;  // �Z�b�g�������ς��邽�߂ɑ��₷
				}

				// ���_��,�C���f�b�N�X��,�|���S�����̐ݒ�
				g_aField[g_SetField].nNumVertex = (g_aField[g_SetField].XBlock + 1) * (g_aField[g_SetField].ZBlock + 1);
				g_aField[g_SetField].nNumIndex = ((g_aField[g_SetField].XBlock + 1) * (g_aField[g_SetField].ZBlock + 1)) + (2 * (g_aField[g_SetField].ZBlock - 1)) + (g_aField[g_SetField].XBlock + 1) * (g_aField[g_SetField].ZBlock - 1);
				g_aField[g_SetField].nNumPolygon = ((g_aField[g_SetField].XBlock * g_aField[g_SetField].ZBlock) * 2) + ((g_aField[g_SetField].ZBlock - 1) * 4);
			    
                // ���_���̍쐬
				MakeVertexField(pDevice);

				// �C���f�b�N�X���̍쐬
				MakeIndexField(pDevice);
				
				g_SetField++;  // �t�B�[���h�����Z�b�g�������𑝂₷
			}
		}
	}
	// �t�@�C������đ��̃v���O�������炢�����悤�ɂ���
	fclose(pFile);
}

//=============================================================================
// �I������
//=============================================================================
void UninitField(void)
{
	for (int nCntField = 0; nCntField < MAX_FIELD; nCntField++)
	{// �t�B�[���h���Z�b�g�ł��镪�J��Ԃ�
		// �e�N�X�`���̊J��
		if (g_pTextureField[nCntField] != NULL)
		{
			g_pTextureField[nCntField]->Release();
			g_pTextureField[nCntField] = NULL;
		}

		// ���_�o�b�t�@�̊J��
		if (g_pVtxBuffField[nCntField] != NULL)
		{
			g_pVtxBuffField[nCntField]->Release();
			g_pVtxBuffField[nCntField] = NULL;
		}

		// �C���f�b�N�X�o�b�t�@�̊J��
		if (g_pIdxBuffField[nCntField] != NULL)
		{
			g_pIdxBuffField[nCntField]->Release();
			g_pIdxBuffField[nCntField] = NULL;
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateField(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;                // �v�Z�p�}�g���b�N�X

	for (int nCntField = 0; nCntField < g_SetField; nCntField++)
	{// �t�B�[���h���Z�b�g�����񐔕��J��Ԃ�
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_aField[nCntField].mtxWorld);
		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aField[nCntField].rot.y, g_aField[nCntField].rot.x, g_aField[nCntField].rot.z);
		D3DXMatrixMultiply(&g_aField[nCntField].mtxWorld, &g_aField[nCntField].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aField[nCntField].pos.x, g_aField[nCntField].pos.y, g_aField[nCntField].pos.z);
		D3DXMatrixMultiply(&g_aField[nCntField].mtxWorld, &g_aField[nCntField].mtxWorld, &mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aField[nCntField].mtxWorld);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, g_pVtxBuffField[nCntField], 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetIndices(g_pIdxBuffField[nCntField]);

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureField[g_aField[nCntField].TexType]);

		// �|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, g_aField[nCntField].nNumVertex, 0, g_aField[nCntField].nNumPolygon);
	}
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
void MakeVertexField(LPDIRECT3DDEVICE9 pDevice)
{
	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * g_aField[g_SetField].nNumVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField[g_SetField],
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;

	// ���_�o�b�t�@�����b�N��,���_�f�[�^�ւ̃|�C���^���擾
	g_pVtxBuffField[g_SetField]->Lock(0, 0, (void**)&pVtx, 0);

	float XPos = -(g_aField[g_SetField].Side / 2) * g_aField[g_SetField].XBlock;
	float ZPos = (g_aField[g_SetField].Depth / 2) * g_aField[g_SetField].ZBlock;
	float Utex = 0.0f;
	float Vtex = 0.0f;

	for (int nCntVertex = 0; nCntVertex < g_aField[g_SetField].nNumVertex; nCntVertex++)
	{// ���_�������J��Ԃ�
		if (nCntVertex != 0 && nCntVertex % (g_aField[g_SetField].XBlock + 1) == 0)
		{// ���̕��������ݒ肵�I���Ă���
			XPos -= g_aField[g_SetField].Side * (g_aField[g_SetField].XBlock + 1); // X���W��i�߂Ă������߂� 
			ZPos -= g_aField[g_SetField].Depth;                      // Z���W����O�ɐi�߂�
			Utex -= 1.0f * (g_aField[g_SetField].XBlock + 1);         // �e�N�X�`����U���W��i�߂Ă�������߂�
			Vtex += 1.0f;                                // �e�N�X�`����V���W��1���i�߂�
		}
		// ���_���W
		pVtx[nCntVertex].pos = D3DXVECTOR3(XPos, 0.0f, ZPos);

		// �@���x�N�g��
		pVtx[nCntVertex].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[
		pVtx[nCntVertex].col = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);

		// �e�N�X�`�����W
		pVtx[nCntVertex].tex = D3DXVECTOR2(Utex, Vtex);

		XPos += g_aField[g_SetField].Side;  // X���W�����ɐi�߂�
		Utex += 1.0f;          // �e�N�X�`����U���W��i�߂�
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffField[g_SetField]->Unlock();
}
//=============================================================================
// �C���f�b�N�X���̍쐬
//=============================================================================
void MakeIndexField(LPDIRECT3DDEVICE9 pDevice)
{
	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * g_aField[g_SetField].nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffField[g_SetField],
		NULL);

	WORD *pIdx;       // �C���f�b�N�X�f�[�^�ւ̃|�C���^
	int nCntIdx = 0;  // �C���f�b�N�X�ԍ�

	// �C���f�b�N�X�o�b�t�@�����b�N��,�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	g_pIdxBuffField[g_SetField]->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxY = 0; nCntIdxY < g_aField[g_SetField].ZBlock; nCntIdxY++)
	{// �c�̕��������J��Ԃ�
		for (int nCntIdxX = 0; nCntIdxX < g_aField[g_SetField].XBlock + 1; nCntIdxX++, nCntIdx++)
		{// ���̕�����+�P�J��Ԃ�
		 // �㉺�̓���C���f�b�N�X�ԍ���ݒ�
			pIdx[0] = nCntIdx + g_aField[g_SetField].XBlock + 1; // ����
			pIdx[1] = nCntIdx;                      // �㑤

			pIdx += 2;  // 2���i�߂�
			if (nCntIdxY < g_aField[g_SetField].ZBlock - 1 && nCntIdxX == g_aField[g_SetField].XBlock)
			{// 1 , �������c�̕������̍ŉ��w�ł͂Ȃ�
			 // 2 , ���̕��������ݒ肪�I�����
				pIdx[0] = nCntIdx;                            // �㑤
				pIdx[1] = nCntIdx + (g_aField[g_SetField].XBlock + 1) + 1; // ���̉���

				pIdx += 2; // 2���i�߂�
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N����
	g_pIdxBuffField[g_SetField]->Unlock();
}