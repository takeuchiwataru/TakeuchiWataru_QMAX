//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Hodaka Niwa
//
//=============================================================================
#include "player.h"
#include "film.h"
#include "input.h"
#include "camera.h"
#include "shadow.h"
#include "effect.h"
#include "animal.h"
#include "model.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_FILENAME   "MODEL_FILENAME"
#define CHARACTERSET     "CHARACTERSET"
#define MOVE             "MOVE"
#define JUMP             "JUMP"
#define INDEX            "INDEX"
#define PARENT           "PARENT"
#define POS              "POS"
#define ROT              "ROT"
#define PARTSSET         "PARTSSET"
#define END_PARTSSET     "END_PARTSSET"
#define END_CHARACTERSET "END_CHARACTERSET"
#define MOTIONSET        "MOTIONSET"
#define LOOP             "LOOP"
#define NUM_KEY          "NUM_KEY"
#define KEYSET           "KEYSET"
#define FRAME            "FRAME"
#define KEY              "KEY"
#define END_KEY          "END_KEY"
#define END_KEYSET       "END_KEYSET"
#define END_MOTIONSET    "END_MOTIONSET"

#define PLAYER_INERTIA   (0.123f)                                  // ����
#define GRAVITY_POWER    (-0.4f)                                   // �d��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void PlayerOperation(void);          // �v���C���[�̑��쏈��
void PlayerTransition(void);         // �v���C���[�̑J�ڏ���
void PlayerAction(void);             // �v���C���[���A�N�V������Ԃ̏���
void PlayerMotion(void);             // ���[�V��������
void PlayerMotionBlend(void);        // ���[�V�����u�����h����
void PlayerMotionAdvance(void);      // ���[�V�����i�s����
void SwitchKey(void);                // �L�[�t���[���̐؂�ւ�����
void SwitchMotion(void);             // ���[�V�����؂�ւ�����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Player  g_Player;                 // �v���C���[���

//=============================================================================
// ����������
//=============================================================================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾

	FILE  *pFile;           // �e�L�X�g�t�@�C���ւ̃|�C���^
	char  str0[128];        // ����Ȃ�����
	char  xFileName[64];    // x�t�@�C���̖��O
	D3DXVECTOR3 OffsetPos;  // �e���f������̋���
	D3DXVECTOR3 OffsetRot;  // �e���f������̌���
	float fJump;            // �W�����v��
	float fMovement;        // �ړ���
	int   nIdxParent;       // �e���f��
	int   nCntModel = 0;    // ���f����ǂݍ��񂾐��𐔂���ϐ�
	int   nCntParts = 0;    // ���f���̃p�[�c����ǂݍ��񂾉񐔂𐔂���ϐ�
	int   nCntPlayer = 0;   // �v���C���[�̐�
	int   nCntMotion = 0;   // ���[�V�����̔ԍ�
	int   nCntKey = 0;      // �L�[�t���[���̔ԍ��𐔂���ϐ�
	int   nPlaybackKey;     // �t���[����
	int   nCntKeyModel = 0; // ���f���̐����̃L�[�t���[���𐔂���ϐ�
	int   bLoop;            // ���[�V���������[�v���邩���Ȃ���
	int   nNumKey = 0;      // �L�[�t���[���̐�
	D3DXVECTOR3 posAdd;     // ��̈ʒu�ɉ�����l
	D3DXVECTOR3 DestAngle;  // �ړI�̌���

	// �t�@�C���I�[�v��
	pFile = fopen("data/TEXT/motion.txt", "r");

	if (pFile != NULL)
	{// �t�@�C�����J����
		while (fscanf(pFile, "%s", &str0[0]) != EOF)
		{// �e�L�X�g�t�@�C���̖��[�܂ŕ���������s���󔒂�����܂œǂݎ��
			if (strcmp(&str0[0], MODEL_FILENAME) == 0)
			{// x�t�@�C���̊g���q��������Ă�����
				if (fscanf(pFile, "%s %s", &str0[0], &xFileName[0]) == 2)
				{// ���f���̃t�@�C������ǂݎ������
					// x�t�@�C���̓ǂݍ���
					D3DXLoadMeshFromX(&xFileName[0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_Player.aModel[nCntModel].pBuffMat,
						NULL,
						&g_Player.aModel[nCntModel].nNumMat,
						&g_Player.aModel[nCntModel].pMesh);

					// �}�e���A����񂩂�e�N�X�`���������o��
					D3DXMATERIAL* pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();
					D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[g_Player.aModel[nCntModel].nNumMat];
					g_Player.aModel[nCntModel].pTexture = new LPDIRECT3DTEXTURE9[g_Player.aModel[nCntModel].nNumMat];

					for (DWORD nCntMat = 0; nCntMat < g_Player.aModel[nCntModel].nNumMat; nCntMat++)
					{// ���_���̐������J��Ԃ� 
					 // �}�e���A������ǂݍ���
						pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

						// ����������������
						pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

						// �e�N�X�`������������
						g_Player.aModel[nCntModel].pTexture[nCntMat] = NULL;

						// �e�N�X�`���̏���ǂݍ���
						if (pMat[nCntMat].pTextureFilename != NULL &&
							lstrlen(pMat[nCntMat].pTextureFilename) > 0)
						{// �e�N�X�`���̃t�@�C����������
							D3DXCreateTextureFromFile(pDevice,
								pMat[nCntMat].pTextureFilename,
								&g_Player.aModel[nCntModel].pTexture[nCntMat]);
						}

					}
				}
				nCntModel++;  // ��ނ��ς��̂Ői�߂Ă���
			}
			if (strcmp(&str0[0], CHARACTERSET) == 0)
			{// �L�����N�^�[��񂪏�����Ă�����
				while (strcmp(&str0[0], END_CHARACTERSET) != 0)
				{// �L�����N�^�[��񂪏I���܂œǂݎ��
					if (strcmp(&str0[0], MOVE) == 0)
					{// �ړ��͂�������Ă�����
						if (fscanf(pFile, "%s %f", &str0[0], &fMovement) == 2)
						{// �ړ��͂�ǂݎ������
							g_Player.fMovement = fMovement;
						}
					}
					if (strcmp(&str0[0], JUMP) == 0)
					{// �W�����v�͂�������Ă�����
						if (fscanf(pFile, "%s %f", &str0[0], &fJump) == 2)
						{// �W�����v�͂�ǂݎ������
							g_Player.fJumpPower = fJump;
						}
					}

					if (strcmp(&str0[0], PARTSSET) == 0)
					{// ���f���̃p�[�c��񂪏�����Ă�����
						int nCntSet = 0;
						int nCntPartsNum = 0;
						while (strcmp(&str0[0], END_PARTSSET) != 0)
						{// ���f���̃p�[�c��񂪏I���܂œǂݎ��
							if (strcmp(&str0[0], INDEX) == 0)
							{// �p�[�c�ԍ���ǂݎ��
								fscanf(pFile, "%s %d", &str0[0], &nCntPartsNum);
							}
							else if (strcmp(&str0[0], PARENT) == 0)
							{// �e���f���̔ԍ���ǂݎ��
								if (fscanf(pFile, "%s %d", &str0[0], &nIdxParent) == 2)
								{// �e���f���̔ԍ���ǂݎ��
									g_Player.aModel[nCntPartsNum].nIdxModelParent = nIdxParent;
								}
							}
							else if (strcmp(&str0[0], POS) == 0)
							{// �e���f������̋�����ǂݎ��
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetPos.x, &OffsetPos.y, &OffsetPos.z) == 4)
								{// ���W����ǂݎ������
									g_Player.aModel[nCntPartsNum].pos = OffsetPos;
								}
							}
							else if (strcmp(&str0[0], ROT) == 0)
							{// �e���f������̌�����ǂݎ��
								if (fscanf(pFile, "%s %f %f %f", &str0[0], &OffsetRot.x, &OffsetRot.y, &OffsetRot.z) == 4)
								{// ��������ǂݎ������
									g_Player.aModel[nCntPartsNum].rot = OffsetRot;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
							nCntSet++;                     // �Z�b�g�����񐔂𑝂₷
						}
					}
					fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
				}
			}
			if (strcmp(&str0[0], MOTIONSET) == 0)
			{// ���[�V������񂪏�����Ă�����
				nCntKey = 0;    // �L�[�t���[���̃|�C���^���W��߂�
				while (strcmp(&str0[0], END_MOTIONSET) != 0)
				{// ���[�V������񂪏I���܂œǂݎ��
					if (strcmp(&str0[0], LOOP) == 0)
					{// ���[�v���邩���Ȃ�����ǂݎ��
						if (fscanf(pFile, "%s %d", &str0[0], &bLoop) == 2)
						{// ���[�v���邩���Ȃ�����ǂݎ�ꂽ
							if (bLoop == 1)
							{
								g_Player.aMotion[nCntMotion].bLoop = true;
							}
							else
							{
								g_Player.aMotion[nCntMotion].bLoop = false;
							}
						}
					}
					else if (strcmp(&str0[0], NUM_KEY) == 0)
					{// �L�[�t���[������ǂݎ��
						if (fscanf(pFile, "%s %d", &str0[0], &nNumKey) == 2)
						{// �L�[�t���[������ǂݎ�ꂽ
							g_Player.aMotion[nCntMotion].nNumKey = nNumKey;
						}
					}
					else if (strcmp(&str0[0], KEYSET) == 0)
					{// �L�[�t���[����񂪏�����Ă�����
						nCntKeyModel = 0;
						while (strcmp(&str0[0], FRAME) != 0)
						{// �L�[�t���[������񂪏I���܂œǂݎ��
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
						}
						if (fscanf(pFile, "%s %d", &str0[0], &nPlaybackKey) == 2)
						{// �L�[�t���[������ǂݎ�ꂽ
							g_Player.aMotion[nCntMotion].Key[nCntKey].nPlayBackKey = nPlaybackKey;
						}
						while (strcmp(&str0[0], END_KEYSET) != 0)
						{// �L�[�t���[����񂪏I���܂œǂݎ��
							if (strcmp(&str0[0], KEY) == 0)
							{// �L�[�t���[���̖ړI�̈ʒu��񂪏�����Ă�����
								while (strcmp(&str0[0], END_KEY) != 0)
								{// �L�[�t���[���̖ړI�̈ʒu��񂪏I���܂œǂݎ��
									if (strcmp(&str0[0], POS) == 0)
									{// ���W����ǂݎ��
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &posAdd.x, &posAdd.y, &posAdd.z) == 4)
										{// ���W����ǂݎ������
											g_Player.aMotion[nCntMotion].Key[nCntKey].posAdd[nCntKeyModel] = posAdd;
										}
									}
									else if (strcmp(&str0[0], ROT) == 0)
									{// ��������ǂݎ��
										if (fscanf(pFile, "%s %f %f %f", &str0[0], &DestAngle.x, &DestAngle.y, &DestAngle.z) == 4)
										{// ��������ǂݎ������
											g_Player.aMotion[nCntMotion].Key[nCntKey].DestAngle[nCntKeyModel] = DestAngle;
										}
									}
									fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
								}
								if (nCntKeyModel < MAX_MODEL - 1)
								{// ���f�����Ƃ̃L�[�t���[�����p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
									nCntKeyModel++;
								}
							}
							fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
						}
						if (nCntKey < MAX_MODEL - 1)
						{// �L�[�t���[�����p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
							nCntKey++;
						}
					}
					fscanf(pFile, "%s", &str0[0]); // �t�@�C����ǂݐi�߂�
				}
				if (nCntMotion < MAX_MOTION - 1)
				{// ���[�V�������p�ӂł��鐔�܂ł��|�C���^���i��łȂ�
					nCntMotion++;   // ���[�V�����ԍ������炷
				}
			}
		}
	}

	// �t�@�C������đ��̃v���O�������炢�����悤�ɂ���
	fclose(pFile);

	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);           // �ړ��ʂ�������
	g_Player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);            // ���݂̌�����������
	g_Player.DestAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // �ړI�̌�����������
	g_Player.DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);      // ������������
	g_Player.state = PLAYERSTATE_NORMAL;                     // �ʏ�̏�Ԃ�
	g_Player.radius = D3DXVECTOR3(11.5f, 30.0f, 11.5f);      // �����蔻������͈͂�������
	g_Player.ShadowCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.35f); // �e�̐F��ݒ�
	g_Player.ShadowWidth = 15;                               // �e�̕���ݒ�
	g_Player.ShadowDepth = 15;                               // �e�̉��s��ݒ�
	g_Player.bJump = false;                                  // �W�����v���Ă��Ȃ���Ԃ�
	g_Player.mState = MOTIONSTATE_NORMAL;                    // ���[�V�����̏�Ԃ͒ʏ�̏�Ԃ�

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
		g_Player.aModel[nCntModel].posStd = g_Player.aModel[nCntModel].pos;
		g_Player.aModel[nCntModel].rot = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel];
	}

	// �e�̔ԍ���ݒ�
	g_Player.nIdxShadow = SetShadow(D3DXVECTOR3(g_Player.pos.x, 1.0f, g_Player.pos.z), g_Player.rot, g_Player.ShadowCol, g_Player.ShadowWidth, g_Player.ShadowDepth);

	// ���[�V�����J�ڏ���
	SwitchMotion();

	g_Player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);     // ���݂̈ʒu��������
	g_Player.posold = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ���݂̈ʒu��������
}

//=============================================================================
// �I������
//=============================================================================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�������J��Ԃ�
		// ���b�V���̔j��
		if (g_Player.aModel[nCntModel].pMesh != NULL)
		{
			g_Player.aModel[nCntModel].pMesh->Release();
			g_Player.aModel[nCntModel].pMesh = NULL;
		}

		// �}�e���A���̔j��
		if (g_Player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_Player.aModel[nCntModel].pBuffMat->Release();
			g_Player.aModel[nCntModel].pBuffMat = NULL;
		}

		// �e�N�X�`���̔j��
		for (DWORD nCntMat = 0; nCntMat < g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{
			if (g_Player.aModel[nCntModel].pTexture[nCntMat] != NULL)
			{
				g_Player.aModel[nCntModel].pTexture[nCntMat]->Release();
				g_Player.aModel[nCntModel].pTexture[nCntMat] = NULL;
			}
		}
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdatePlayer(void)
{
	if (g_Player.state != PLAYERSTATE_TAKEPICTURE
		&& g_Player.state != PLAYERSTATE_LANDING)
	{// �������Ԃł���
		// �ړ�����
		PlayerOperation();
	}

	// ����ł���v���C���[�̑J�ڏ���
	PlayerTransition();

	if (g_Player.state == PLAYERSTATE_TAKEPICTURE)
	{// �v���C���[���A�N�V������Ԃł���
		PlayerAction();
	}

	if (g_Player.mState == MOTIONSTATE_NORMAL)
	{// �ʏ�̃��[�V������Ԃ�������
		// ���[�V��������
		PlayerMotion();
	}
	else if (g_Player.mState == MOTIONSTATE_SWITCH)
	{// ���[�V�����؂�ւ���Ԃ�������
		// ���[�V�����u�����h����
		PlayerMotionBlend();
	}

	if (g_Player.mState == MOTIONSTATE_NORMAL)
	{// �L�[�t���[����i�߂��Ԃ�������
		// ���[�V�����i�s����
		PlayerMotionAdvance();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxParent;     // �v�Z�p�}�g���b�N�X
	D3DXVECTOR3 vecRot, vecTrans;               // �v�Z�p���f���̌���,���W
	D3DMATERIAL9 matDef;                        // ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;                         // �}�e���A���f�[�^�ւ̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Player.mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.rot.y, g_Player.rot.x, g_Player.rot.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Player.pos.x, g_Player.pos.y, g_Player.pos.z);
	D3DXMatrixMultiply(&g_Player.mtxWorld, &g_Player.mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Player.mtxWorld);

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�������J��Ԃ�
		if (g_Player.aModel[nCntModel].nIdxModelParent == -1)
		{// �e�����Ȃ�
			mtxParent = g_Player.mtxWorld;     // �v���C���[�̃}�g���b�N�X�������炤
		}
		else
		{// �e������
			mtxParent = g_Player.aModel[g_Player.aModel[nCntModel].nIdxModelParent].mtxWorld;   // �e���f���̃}�g���b�N�X�������炤
		}
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Player.aModel[nCntModel].mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Player.aModel[nCntModel].rot.y, g_Player.aModel[nCntModel].rot.x, g_Player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Player.aModel[nCntModel].pos.x, g_Player.aModel[nCntModel].pos.y, g_Player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxTrans);

		// �e�̏��������ɔ��f
		D3DXMatrixMultiply(&g_Player.aModel[nCntModel].mtxWorld, &g_Player.aModel[nCntModel].mtxWorld, &mtxParent);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Player.aModel[nCntModel].mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_Player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_Player.aModel[nCntModel].nNumMat; nCntMat++)
		{// �ݒ肳��Ă����}�e���A���̐������J��Ԃ�
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_Player.aModel[nCntModel].pTexture[nCntMat]);

			// ���f��(�p�[�c)�̕`��
			g_Player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}

		// �ۑ����Ă����}�e���A���ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}
//=============================================================================
// �v���C���[�̑��쏈��
//=============================================================================
void PlayerOperation(void)
{
	g_Player.posold = g_Player.pos;   // �O��̈ʒu�X�V

	//------------------
	// �L�[�{�[�h����
	//------------------
	if (GetKeyboardPress(DIK_A) == true)
	{// �������̓��͂����ꂽ
		Camera *pCamera;
		pCamera = GetCamera();
		if (GetKeyboardPress(DIK_W) == true)
		{// �����ɏ�����̓��͂����ꂽ
		    // �ړ�����
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player.fMovement;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player.fMovement;

			// �ړI�̊p�x�ύX
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.75f);
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// �����ɉ������̓��͂����ꂽ
		    // �ړ�����
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player.fMovement;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player.fMovement;

			 // �ړI�̊p�x�ύX
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.25f);
			
		}
		else
		{// ����������ĂȂ�
		 // �ړ�����
			g_Player.move.x += sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player.fMovement;
			g_Player.move.z += cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player.fMovement;

			// �ړI�̊p�x�ύX
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * 0.5f);
		}
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{// �E�����̓��͂����ꂽ
		Camera *pCamera;
		pCamera = GetCamera();
		if (GetKeyboardPress(DIK_W) == true)
		{// �����ɏ�����̓��͂����ꂽ
		 // �ړ�����
			g_Player.move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player.fMovement;
			g_Player.move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.75f)) * g_Player.fMovement;

			// �ړI�̊p�x�ύX
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.75f);
		}
		else if (GetKeyboardPress(DIK_S) == true)
		{// �����ɉ������̓��͂����ꂽ
		 // �ړ�����
			g_Player.move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player.fMovement;
			g_Player.move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.25f)) * g_Player.fMovement;

			// �ړI�̊p�x�ύX
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.25f);

		}
		else
		{// ����������ĂȂ�
		 // �ړ�����
			g_Player.move.x -= sinf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player.fMovement;
			g_Player.move.z -= cosf(pCamera->rot.y - (D3DX_PI * 0.5f)) * g_Player.fMovement;

			// �ړI�̊p�x�ύX
			g_Player.DestAngle.y = pCamera->rot.y + (D3DX_PI * -0.5f);
		}
	}
	else if (GetKeyboardPress(DIK_W) == true)
	{// ������̓��͂����ꂽ
		Camera *pCamera;
		pCamera = GetCamera();

		// �ړ�����
		g_Player.move.x += sinf(pCamera->rot.y) * g_Player.fMovement;
		g_Player.move.z += cosf(pCamera->rot.y) * g_Player.fMovement;

		// �ړI�̊p�x�ύX
		g_Player.DestAngle.y = pCamera->rot.y + D3DX_PI;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{// �������̓��͂����ꂽ
		Camera *pCamera;
		pCamera = GetCamera();

		// �ړ�����
		g_Player.move.x += sinf(pCamera->rot.y + D3DX_PI) * g_Player.fMovement;
		g_Player.move.z += cosf(pCamera->rot.y + D3DX_PI) * g_Player.fMovement;

		g_Player.DestAngle.y = pCamera->rot.y;

	}
	else if (GetJoyPadPress(DIJS_BUTTON_18,0) == true || GetJoyPadPress(DIJS_BUTTON_19,0) == true
		|| GetJoyPadPress(DIJS_BUTTON_20,0) == true || GetJoyPadPress(DIJS_BUTTON_21,0) == true)
	{// �\���L�[���͂����ꂽ
		Camera *pCamera;
		pCamera = GetCamera();

		// �ړ�����
		g_Player.move.x += sinf(pCamera->rot.y + GetJotPadRadian(0)) * g_Player.fMovement;
		g_Player.move.z += cosf(pCamera->rot.y + GetJotPadRadian(0)) * g_Player.fMovement;

		// �ړI�̊p�x�ύX
		g_Player.DestAngle.y = pCamera->rot.y + GetJotPadRadian(0) - D3DX_PI;

	}
	else if (GetJoyPadPress(DIJS_BUTTON_10,0) == true || GetJoyPadPress(DIJS_BUTTON_11,0) == true ||
		GetJoyPadPress(DIJS_BUTTON_12,0) == true || GetJoyPadPress(DIJS_BUTTON_13,0) == true)
	{// ���A�i���O�X�e�B�b�N�̓��͂����ꂽ
		Camera *pCamera;
		pCamera = GetCamera();

		// �ړ�����
		g_Player.move.x -= sinf(pCamera->rot.y - GetJotPadRightStick(0)) * g_Player.fMovement;
		g_Player.move.z -= cosf(pCamera->rot.y - GetJotPadRightStick(0)) * g_Player.fMovement;

		// �ړI�̊p�x�ύX
		g_Player.DestAngle.y = pCamera->rot.y - GetJotPadRightStick(0);

	}

	if (GetKeyboardTrigger(DIK_SPACE) == true || GetJoyPadPress(DIJS_BUTTON_1,0) == true)
	{// �W�����v�{�^���������ꂽ
		if (g_Player.bJump == false)
		{// �W�����v���Ă��Ȃ�
 			g_Player.move.y += g_Player.fJumpPower;   // �㏸������
			g_Player.bJump = true;                    // �W�����v������Ԃ�
			g_Player.state = PLAYERSTATE_JUMP;        // �W�����v��Ԃ�
			// ���[�V�����؂�ւ�����
			SwitchMotion();
			PlaySound(SOUND_LABEL_SE_JUMP);
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadPress(DIJS_BUTTON_2, 0) == true)
	{// �A�N�V�����{�^���������ꂽ
		if (GetFilmNum() > 0)
		{// �B���ʐ^�̃t�B�������܂�����
			if (g_Player.state = PLAYERSTATE_TAKEPICTURE)
			{// �ʐ^������Ă��Ȃ�
				g_Player.state = PLAYERSTATE_TAKEPICTURE;    // �ʐ^������Ԃ�
				// ���[�V�����؂�ւ�����
				SwitchMotion();
			}
		}
	}
}
//=============================================================================
// �v���C���[�̏�ԑJ�ڏ���
//=============================================================================
void PlayerTransition(void)
{
	// �d�͂����Z����
	g_Player.move.y += GRAVITY_POWER;

	// �ʒu���ړ�
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;

	// �p�x�̏C��
	g_Player.DiffAngle.y = g_Player.DestAngle.y - g_Player.rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

	if (g_Player.DiffAngle.y > D3DX_PI)
	{// ������D3DX_PI�𒴂���
		g_Player.DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (g_Player.DiffAngle.y < -D3DX_PI)
	{// ������-D3DX_PI�𒴂���
		g_Player.DiffAngle.y += D3DX_PI * 2.0f;
	}

	g_Player.rot.y += g_Player.DiffAngle.y * 0.1f;

	if (g_Player.rot.y > D3DX_PI)
	{// ���݂̌�����D3DX_PI�𒴂���
		g_Player.rot.y -= D3DX_PI * 2.0f;
	}
	if (g_Player.rot.y < -D3DX_PI)
	{// ���݂̌�����-D3DX_PI�𒴂���
		g_Player.rot.y += D3DX_PI * 2.0f;
	}

	if (g_Player.bJump == false && g_Player.state != PLAYERSTATE_LANDING && g_Player.state != PLAYERSTATE_TAKEPICTURE)
	{// �W�����v���Ă��Ȃ������n��ԂłȂ����ʐ^���B���Ă��Ȃ�
		if (g_Player.move.x <= 1.0f && g_Player.move.x >= -1.0f &&
			g_Player.move.z <= 1.0f && g_Player.move.z >= -1.0f)
		{// �ړ����Ă��Ȃ�������
			if (g_Player.state != PLAYERSTATE_NORMAL)
			{// �ړ����Ă��Ȃ���Ԃ���Ȃ�������
				g_Player.state = PLAYERSTATE_NORMAL;     // �ʏ�̏�Ԃ�
				// ���[�V�����؂�ւ�����
				SwitchMotion();
			}
		}
		if (g_Player.move.x > 1.0f || g_Player.move.x < -1.0f ||
			g_Player.move.z > 1.0f || g_Player.move.z < -1.0f)
		{// �ړ����Ă�����
			if (g_Player.state != PLAYERSTATE_MOVE)
			{// �ړ����Ă����Ԃ���Ȃ�������
				g_Player.state = PLAYERSTATE_MOVE;       // �ړ����Ă����Ԃ�
				// ���[�V�����؂�ւ�����
				SwitchMotion();
			}
		}
	}

	// �e�̈ʒu�X�V
	SetPositionShadow(g_Player.nIdxShadow, D3DXVECTOR3(g_Player.pos.x, 1.0f, g_Player.pos.z));

	// �e�̐F�X�V
	SetColShadow(g_Player.nIdxShadow, g_Player.ShadowCol);

	// �e�̑傫���X�V
	SetSizeShadow(g_Player.nIdxShadow, g_Player.ShadowWidth, g_Player.ShadowDepth);

	if (g_Player.pos.y < 0.0f)
	{// ���n����
		g_Player.pos.y = 0.0f;         // �ʒu��߂�
		g_Player.move.y = 0.0f;        // �d�͂�����
		g_Player.ShadowWidth = 15;     // �e�̕���߂�
		g_Player.ShadowDepth = 15;     // �e�̉��s��߂�
		g_Player.ShadowCol.a = 0.15f;  // �e�̓����x��߂�
		if (g_Player.state == PLAYERSTATE_JUMP)
		{// �W�����v��Ԃ�������
			if (g_Player.bJump == true)
			{// �W�����v���Ă���
				if (g_Player.move.x <= 1.0f && g_Player.move.x >= -1.0f &&
					g_Player.move.z <= 1.0f && g_Player.move.z >= -1.0f)
				{// �ړ����Ă��Ȃ�������
					g_Player.state = PLAYERSTATE_LANDING;        // ���n��Ԃ�
																 // ���[�V�����؂�ւ�����
					SwitchMotion();
					g_Player.move.x = 0.0f;   // �ړ��𖳎�����
					g_Player.move.z = 0.0f;   // �ړ��𖳎�����

				}
				else if (g_Player.move.x > 1.0f || g_Player.move.x < -1.0f ||
					g_Player.move.z > 1.0f || g_Player.move.z < -1.0f)
				{// �ړ����Ă�����
					g_Player.state = PLAYERSTATE_MOVE;           // �ړ����Ă����Ԃ�
					// ���[�V�����؂�ւ�����
					SwitchMotion();
				}
			}
			PlaySound(SOUND_LABEL_SE_GROUND);
		}
		g_Player.bJump = false;      // �W�����v���Ă��Ȃ������
	}

	if (g_Player.pos.x - 50.0f <= -1450.0f)
	{// �����̍�����o�悤�Ƃ���
		g_Player.pos.x = -1400.0f;
	}
	if (g_Player.pos.x + 50.0f >= 1450.0f)
	{// �����̉E����o�悤�Ƃ���
		g_Player.pos.x = 1400.0f;
	}
	if (g_Player.pos.z - 50.0f <= -1450.0f)
	{// �����̑O����o�悤�Ƃ���
		g_Player.pos.z = -1400.0f;
	}
	if (g_Player.pos.z + 50.0f >= 1450.0f)
	{// �����̌�납��o�悤�Ƃ���
		g_Player.pos.z = 1400.0f;
	}

	CollisionModel(&g_Player.pos, &g_Player.posold, &g_Player.move, D3DXVECTOR3(40.0f, 50.0f, 40.0f));

	// �����𓭂�����
	g_Player.move.x += (0.0f - g_Player.move.x) * PLAYER_INERTIA;
	g_Player.move.z += (0.0f - g_Player.move.z) * PLAYER_INERTIA;

	if (g_Player.bJump == true)
	{// �W�����v���Ă�����
		if (g_Player.move.y > 0.0f)
		{// �󒆂ɏオ���Ă���
			g_Player.ShadowWidth -= 0.3f;
			g_Player.ShadowDepth -= 0.3f;
			g_Player.ShadowCol.a -= 0.006f;
		}
		else if (g_Player.move.y < 0.0f)
		{// �n��ɗ����Ă���
			g_Player.ShadowWidth += 0.3f;
			g_Player.ShadowDepth += 0.3f;
			g_Player.ShadowCol.a += 0.006f;
		}
	}

	if (g_Player.state == PLAYERSTATE_MOVE)
	{// �ړ����Ă�����
		if (g_Player.nKey == 0 && g_Player.nMotionCounter == 1 || g_Player.nKey == 2 && g_Player.nMotionCounter == 1)
		{
			PlaySound(SOUND_LABEL_SE_DASH);
		}
	}
	else
	{
		StopSound(SOUND_LABEL_SE_DASH);
	}
}
//=============================================================================
// �v���C���[���A�N�V������Ԃ̎��̏���
//=============================================================================
void PlayerAction(void)
{
	if (g_Player.nKey == 2 && g_Player.nMotionCounter == 2)
	{
		D3DXMATRIX mtxRot, mtxTrans, mtxEffect;       // �v�Z�p�}�g���b�N�X
		D3DXVECTOR3 EffectPos;                        // �G�t�F�N�g���o���ʒu(�I�t�Z�b�g)
		float EffectRadius = 10.0f;                   // �G�t�F�N�g�̔��a

		EffectPos = D3DXVECTOR3(0.0f, 20.0f, -10.0f); // �G�t�F�N�g���o���ʒu��ݒ�

		for (int nCntEffect = 0; nCntEffect < 30; nCntEffect++, EffectRadius += 4.0f, EffectPos.z -= 15.0f)
		{// �G�t�F�N�g���o���񐔕��J��Ԃ�
		 // ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&mtxEffect);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
			D3DXMatrixMultiply(&mtxEffect, &mtxEffect, &mtxRot);

			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, EffectPos.x, EffectPos.y, EffectPos.z);
			D3DXMatrixMultiply(&mtxEffect, &mtxEffect, &mtxTrans);

			// �e�̏��������ɔ��f
			D3DXMatrixMultiply(&mtxEffect, &mtxEffect, &g_Player.aModel[1].mtxWorld);

			SetEffect(D3DXVECTOR3(mtxEffect._41, mtxEffect._42, mtxEffect._43), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), EffectRadius, 30);

			if (nCntEffect == 15)
			{
				CollisionShutterAnimal(D3DXVECTOR3(mtxEffect._41, mtxEffect._42, mtxEffect._43), D3DXVECTOR3(200.0f, 0.0f, 200.0f));
				CollisionShutterModel(D3DXVECTOR3(mtxEffect._41, mtxEffect._42, mtxEffect._43), D3DXVECTOR3(200.0f, 0.0f, 200.0f));
			}
		}

		CutFilm(1);
		PlaySound(SOUND_LABEL_SE_SHUTTER);
	}
}

//=============================================================================
// �v���C���[�̃��[�V����
//=============================================================================
void PlayerMotion(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	    // ���݂̈ʒu�X�V
		g_Player.aModel[nCntModel].pos.x += g_Player.aModel[nCntModel].posDiff.x / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;
		g_Player.aModel[nCntModel].pos.y += g_Player.aModel[nCntModel].posDiff.y / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;
		g_Player.aModel[nCntModel].pos.z += g_Player.aModel[nCntModel].posDiff.z / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;

		g_Player.aModel[nCntModel].rot.x += g_Player.aModel[nCntModel].DiffAngle.x / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;

		if (g_Player.aModel[nCntModel].rot.x > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].rot.x < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
		}

		g_Player.aModel[nCntModel].rot.y += g_Player.aModel[nCntModel].DiffAngle.y / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;

		if (g_Player.aModel[nCntModel].rot.y > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].rot.y < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
		}

		g_Player.aModel[nCntModel].rot.z += g_Player.aModel[nCntModel].DiffAngle.z / g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey;

		if (g_Player.aModel[nCntModel].rot.z > D3DX_PI)
		{// ���݂̌�����D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].rot.z < -D3DX_PI)
		{// ���݂̌�����-D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
		}
	}
}
//=============================================================================
// �v���C���[�̃��[�V�����u�����h����
//=============================================================================
void PlayerMotionBlend(void)
{
	// �u�����h�J�E���^�[��i�߂�
	g_Player.nBlendCounter++;
		for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
		{// ���f���̃p�[�c�����J��Ԃ�
		    // ���݂̈ʒu�X�V
			g_Player.aModel[nCntModel].pos.x += g_Player.aModel[nCntModel].posDiff.x / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);
			g_Player.aModel[nCntModel].pos.y += g_Player.aModel[nCntModel].posDiff.y / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);
			g_Player.aModel[nCntModel].pos.z += g_Player.aModel[nCntModel].posDiff.z / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);

			g_Player.aModel[nCntModel].rot.x += g_Player.aModel[nCntModel].DiffAngle.x / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);

			if (g_Player.aModel[nCntModel].rot.x > D3DX_PI)
			{// ���݂̌�����D3DX_PI�𒴂���
				g_Player.aModel[nCntModel].rot.x -= D3DX_PI * 2.0f;
			}
			if (g_Player.aModel[nCntModel].rot.x < -D3DX_PI)
			{// ���݂̌�����-D3DX_PI�𒴂���
				g_Player.aModel[nCntModel].rot.x += D3DX_PI * 2.0f;
			}
			g_Player.aModel[nCntModel].rot.y += g_Player.aModel[nCntModel].DiffAngle.y / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);

			if (g_Player.aModel[nCntModel].rot.y > D3DX_PI)
			{// ���݂̌�����D3DX_PI�𒴂���
				g_Player.aModel[nCntModel].rot.y -= D3DX_PI * 2.0f;
			}
			if (g_Player.aModel[nCntModel].rot.y < -D3DX_PI)
			{// ���݂̌�����-D3DX_PI�𒴂���
				g_Player.aModel[nCntModel].rot.y += D3DX_PI * 2.0f;
			}

			g_Player.aModel[nCntModel].rot.z += g_Player.aModel[nCntModel].DiffAngle.z / (g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f);

			if (g_Player.aModel[nCntModel].rot.z > D3DX_PI)
			{// ���݂̌�����D3DX_PI�𒴂���
				g_Player.aModel[nCntModel].rot.z -= D3DX_PI * 2.0f;
			}
			if (g_Player.aModel[nCntModel].rot.z < -D3DX_PI)
			{// ���݂̌�����-D3DX_PI�𒴂���
				g_Player.aModel[nCntModel].rot.z += D3DX_PI * 2.0f;
			}
		}

	if (g_Player.nBlendCounter >= g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey * 0.3f)
	{// �u�����h�J�E���^�[������̒l��
        g_Player.nBlendCounter = 0;            // �u�����h�J�E���^�[��������
		if (g_Player.aMotion[g_Player.state].nNumKey >= 2)
		{// �L�[�t���[����2�ȏ゠������
			g_Player.mState = MOTIONSTATE_NORMAL;  // ���[�V�����̏�Ԃ�ʏ�̏�Ԃ�
			g_Player.nKey++;                       // �L�[�t���[����i�߂�
		    // �L�[�t���[���؂�ւ�����
			SwitchKey();
		}
		else
		{// �L�[�t���[��������ȏ�Ȃ�
			g_Player.mState = MOTIONSTATE_STOP;    // ���[�V�����̏�Ԃ����[�V�������Ȃ���Ԃ�
		}
	}
}
//=============================================================================
// ���[�V�����i�s����
//=============================================================================
void PlayerMotionAdvance(void)
{
	g_Player.nMotionCounter++;   // ���[�V�����J�E���^�[��i�߂�
	if (g_Player.nMotionCounter >= g_Player.aMotion[g_Player.state].Key[g_Player.nKey].nPlayBackKey)
	{// �Đ��t���[�����ɒB����
		if (g_Player.nKey == g_Player.aMotion[g_Player.state].nNumKey - 1)
		{// ���݂̃L�[�t���[���������̃��[�V�����̃L�[�t���[���̑�����������
			if (g_Player.aMotion[g_Player.state].bLoop == true)
			{// ���[�v���锻�肾������
				g_Player.nKey = 0;             // ���݂̃L�[�t���[�������ɖ߂�
				// �L�[�t���[���؂�ւ�����
				SwitchKey();
			}
			else
			{// ���[�v���Ȃ����肾������
				if (g_Player.state == PLAYERSTATE_LANDING || g_Player.state == PLAYERSTATE_TAKEPICTURE)
				{// ���n��Ԃ��A�N�V������Ԃ�������
					g_Player.state = PLAYERSTATE_NORMAL;  // �ʏ��Ԃ�

					// ���[�V�����؂�ւ�����
					SwitchMotion();
				}
				else
				{// ����ȊO�̃��[�V�����Ȃ��
					g_Player.mState = MOTIONSTATE_STOP;
				}
			}
		}
		else
		{
			g_Player.nKey++;         // ���݂̃L�[�t���[����i�߂�

			// �L�[�t���[���؂�ւ�����
			SwitchKey();
		}
		g_Player.nMotionCounter = 0;   // �J�E���^�[��߂�
	}
}
//=============================================================================
// �L�[�t���[���؂�ւ�����
//=============================================================================
void SwitchKey(void)
{
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	    // �ڕW�̍��W�ݒ�
		g_Player.aModel[nCntModel].posDiff.x = g_Player.aModel[nCntModel].posStd.x - (g_Player.aModel[nCntModel].pos.x - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].x);
		g_Player.aModel[nCntModel].posDiff.y = g_Player.aModel[nCntModel].posStd.y - (g_Player.aModel[nCntModel].pos.y - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].y);
		g_Player.aModel[nCntModel].posDiff.z = g_Player.aModel[nCntModel].posStd.z - (g_Player.aModel[nCntModel].pos.z - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].z);

	    // �p�x�̍����̏C��
		g_Player.aModel[nCntModel].DiffAngle.x = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].x - g_Player.aModel[nCntModel].rot.x;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player.aModel[nCntModel].DiffAngle.x > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.x -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.x < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.x += D3DX_PI * 2.0f;
		}
		// �p�x�̍����̏C��
		g_Player.aModel[nCntModel].DiffAngle.y = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].y - g_Player.aModel[nCntModel].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player.aModel[nCntModel].DiffAngle.y > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.y -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.y < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.y += D3DX_PI * 2.0f;
		}

		// �p�x�̍����̏C��
		g_Player.aModel[nCntModel].DiffAngle.z = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].z - g_Player.aModel[nCntModel].rot.z;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player.aModel[nCntModel].DiffAngle.z > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.z -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.z < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.z += D3DX_PI * 2.0f;
		}
	}
}

//=============================================================================
// ���[�V�����؂�ւ�����
//=============================================================================
void SwitchMotion(void)
{
	g_Player.nMotionCounter = 0;          // ���[�V�����J�E���^�[�����Z�b�g
	g_Player.nKey = 0;                    // ���݂̃L�[�t���[�������Z�b�g
	g_Player.mState = MOTIONSTATE_SWITCH; // ���[�V�����؂�ւ���Ԃ�

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{// ���f���̃p�[�c�����J��Ԃ�
	    // �ڕW�̍��W�ݒ�
		g_Player.aModel[nCntModel].posDiff.x = g_Player.aModel[nCntModel].posStd.x - (g_Player.aModel[nCntModel].pos.x - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].x);
		g_Player.aModel[nCntModel].posDiff.y = g_Player.aModel[nCntModel].posStd.y - (g_Player.aModel[nCntModel].pos.y - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].y);
		g_Player.aModel[nCntModel].posDiff.z = g_Player.aModel[nCntModel].posStd.z - (g_Player.aModel[nCntModel].pos.z - g_Player.aMotion[g_Player.state].Key[g_Player.nKey].posAdd[nCntModel].z);

	    // �p�x�̍����̏C��
		g_Player.aModel[nCntModel].DiffAngle.x = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].x - g_Player.aModel[nCntModel].rot.x;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player.aModel[nCntModel].DiffAngle.x > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.x -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.x < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.x += D3DX_PI * 2.0f;
		}
		// �p�x�̍����̏C��
		g_Player.aModel[nCntModel].DiffAngle.y = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].y - g_Player.aModel[nCntModel].rot.y;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player.aModel[nCntModel].DiffAngle.y > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.y -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.y < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.y += D3DX_PI * 2.0f;
		}

		// �p�x�̍����̏C��
		g_Player.aModel[nCntModel].DiffAngle.z = g_Player.aMotion[g_Player.state].Key[g_Player.nKey].DestAngle[nCntModel].z - g_Player.aModel[nCntModel].rot.z;   // ���݂̌����ƖړI�̌����̍������v�Z

		if (g_Player.aModel[nCntModel].DiffAngle.z > D3DX_PI)
		{// ������D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.z -= D3DX_PI * 2.0f;
		}
		if (g_Player.aModel[nCntModel].DiffAngle.z < -D3DX_PI)
		{// ������-D3DX_PI�𒴂���
			g_Player.aModel[nCntModel].DiffAngle.z += D3DX_PI * 2.0f;
		}
	}
}
//=============================================================================
// �v���C���[�̎擾
//=============================================================================
Player *GetPlayer(void)
{
	return &g_Player;
}