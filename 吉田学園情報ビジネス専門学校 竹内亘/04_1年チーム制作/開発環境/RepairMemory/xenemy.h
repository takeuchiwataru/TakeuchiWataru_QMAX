//=========================================================================================================================
//
// �G���� [xenemy.h]
// Author : Eisuke Sakagawa
//
//=========================================================================================================================
#ifndef _XENEMY_H_
#define _XENEMY_H_

//*************************************************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// �}�N����`
//*************************************************************************************************************************
#define XENEMY_TEXT_NAME			(255)						
#define XENEMY_TEXT_INFO			"data\\TEXT\\enemydata.ini"
//#define XENEMY_TEXT_INFO			"data\\TEXT\\enemymodeldata.txt"
#define MAX_XENEMYPARTS				(20)					
#define MAX_XENEMYANIM				(12)					
#define MAX_XENEMYANIMKEY			(10)					

//*************************************************************************************************************************
// �\���̒�`
//*************************************************************************************************************************
typedef enum
{
	ENEMYTYPE_1 = 0,
	ENEMYTYPE_2,
	ENEMYTYPE_3,
	ENEMYTYPE_4,
	ENEMYTYPE_MAX
}ENEMYTYPE;

typedef enum
{
	ENEMYANIM_NEUTRAL = 0,
	ENEMYANIM_WALK,
	ENEMYANIM_ATTACK,
	ENEMYANIM_MAX
}ENEMYANIM;

typedef struct
{
	char						FileName[XENEMY_TEXT_NAME];		// X�t�@�C����
	LPD3DXMESH					pMesh = NULL;					// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER				pBuffMat = NULL;				// �}�e���A�����ւ̃|�C���^
	DWORD						nNumMat = NULL;					// �}�e���A�����̐�
	D3DXMATRIX					mtxWorld;						// ���[���h�}�g���b�N�X
	int							nIndexParent;					// �e�q�֌W
	D3DXVECTOR3					Initpos;						// �����ʒu
	D3DXVECTOR3					posDest;						// �ڕW�ʒu
	D3DXVECTOR3					pos;							// ���݈ʒu
	D3DXVECTOR3					move;							// �ړ�
	D3DXVECTOR3					Initrot;						// ��������
	D3DXVECTOR3					rotDest;						// �ڕW����
	D3DXVECTOR3					rot;							// ���݌���
	D3DXVECTOR3					posAnim[MAX_XENEMYANIM][MAX_XENEMYANIMKEY];		// �A�j���[�V����pos
	D3DXVECTOR3					rotAnim[MAX_XENEMYANIM][MAX_XENEMYANIMKEY];		// �A�j���[�V����rot
	D3DXVECTOR3					vtxMin;							// ���_�̍ŏ��l
	D3DXVECTOR3					vtxMax;							// ���_�̍ő�l
}XENEMYMODEL;

typedef struct
{
	D3DXMATRIX					mtxWorld;						// ���[���h�}�g���b�N�X
	int							nIdxShadow;						// �e�ԍ�
	D3DXVECTOR3					Initpos;						// �����ʒu
	D3DXVECTOR3					pos;							// ���݈ʒu
	D3DXVECTOR3					posOld;							// �O��ʒu
	D3DXVECTOR3					move;							// �ړ�
	D3DXVECTOR3					Initrot;						// ��������
	D3DXVECTOR3					rotDest;						// �ڕW����
	D3DXVECTOR3					rot;							// ���݌���
	D3DXVECTOR3					vtxMin;							// ���_�̍ŏ��l
	D3DXVECTOR3					vtxMax;							// ���_�̍ő�l
	int							nCntTimerand;					// �J�E���^�[
	int							nCntTime;						// �J�E���^�[
	int							nMaxPartsNum;					// �p�[�c��
	XENEMYMODEL					aModel[MAX_XENEMYPARTS];		// �p�[�c���
	int							nMaxAnimNum;					// �A�j���[�V������
	int							nAnimChange;					// �A�j���[�V�����`�F���W
	int							nAnimloop[MAX_XENEMYANIM];		// ���[�v
	int							nAnimkey[MAX_XENEMYANIM];		// �L�[��
	int							nAnimfram[MAX_XENEMYANIM][MAX_XENEMYANIMKEY];		// �t���[����
	ENEMYANIM					nAnimnow;						// ���݃A�j���[�V����
	int							nAnimkeynow;					// ���݃L�[
	int							nIdxMark;						// �g�p�}�[�N�ԍ�
	bool						bIdxMarkUse;					// �g�p�}�[�N
	bool						bAttack;						// �g�p���Ă��邩
	bool						bUse;							// �g�p���Ă��邩
}XENEMY;

typedef struct
{
	int							nSetNum;						// �\����
	char						FileName[XENEMY_TEXT_NAME];		// X�t�@�C����
}XENEMYINI;

//*************************************************************************************************************************
// �v���g�^�C�v�錾
//*************************************************************************************************************************
void InitXEnemy(void);				// �G����������
void UninitXEnemy(void);			// �G�I������
void UpdateXEnemy(void);			// �G�X�V����
void DrawXEnemy(void);				// �G�`�揈��

void SetXEnemy(ENEMYTYPE type, D3DXVECTOR3 pos, D3DXVECTOR3 Initrot, D3DXVECTOR3 rot);				// �G�ݒ菈��
XENEMY *GetXEnemy(void);			// �G�擾����
bool CollisionXEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax);
void DeleteXEnemy(void);
#endif
