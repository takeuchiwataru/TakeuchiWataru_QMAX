//=============================================================================
//
// �v���C���[���� [player.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CModel;
class CMeshOrbit;
class CObjectBG;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PARTS		(30)
#define MAX_MOTION		(30)

//*****************************************************************************
// �\����
//*****************************************************************************



//*********************************************************************
//�v���C���[�N���X�̒�`
//*********************************************************************
class CPlayer : public CScene //�h���N���X
{
public:
	//�L�[�v�f
	typedef struct
	{
		float fposX;
		float fposY;
		float fposZ;
		float frotX;
		float frotY;
		float frotZ;
	}KEY;
	//�L�[���
	typedef struct
	{
		int nFrame;
		KEY aKey[MAX_PARTS];
	}KEY_INFO;

	//���[�V�������
	typedef struct
	{
		bool bLoop;
		int nNumKey;
		KEY_INFO aKayInfo[MAX_MOTION];
	}MOTION_INFO;

	typedef enum
	{
		PLAYERSTATE_NONE = 0,		//�������
		PLAYERSTATE_NORMAL,			//�ʏ�
		PLAYERSTATE_DAMAGE,			//�_���[�W
		PLAYERSTATE_DEATH,			//���S
		PLAYERSTATE_APPEAR,			//���G
		PLAYERSTATE_GAMEEND,		//�c�@�����I��
		PLAYERSTATE_GAMECLEAR,		//�Q�[�����N���A
		PLAYERSTATE_MAX,			//�ő吔
	}PLAYERSTATE;

	CPlayer();
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	static CPlayer *Create(D3DXVECTOR3 pos, float fLength);
	static HRESULT Load(void);
	static void UnLoad(void);
	static void HitDamage(int nDamage);
	static D3DXVECTOR3 GetPos(void);
	static D3DXVECTOR3 GetRot(void);
	static D3DXVECTOR3 GetMove(void);

	//�n�ʂƂ̓����蔻��
	void CollisitionGround(void);
	//�I�u�W�F�N�g�̓����蔻��
	void CollisitionObject3D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	//�G�r���{�[�h�̓����蔻��
	void CollisitionBillBoardEnemy(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	//�A�C�e���r���{�[�h�̓����蔻��
	void CollisitionBillBoardItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
	//�{�[���̓����蔻��
	void CollisitionBall(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);

	//���[�V�����̍X�V�֐�
	void UpdateMotion(void);

	//�t�@�C���ǂݍ��݊֐�
	void FileLoad(void);						//�t�@�C���ǂݍ���
	char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	char *GetLineTop(char *pStr);				//�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�
private:
	//�����o�ϐ�
	static D3DXVECTOR3			m_pos;					//�ʒu
	D3DXVECTOR3					m_posold;				//�O��̈ʒu
	static D3DXVECTOR3			m_move;					//�ړ���
	static D3DXVECTOR3			m_rot;					//����
	static PLAYERSTATE			m_State;				//�v���C���[�̏��
	D3DXMATRIX					m_mtxWorld;				//���[���h�}�g���b�N�X
	float						m_fDestAngle;			//�v���C���[�̊p�x
	float						m_fDiffAngle;			//����
	bool						m_bJump;				//�W�����v���
	bool						m_bLand;				//���n���
	int							m_nGameEndCnt;			//�Q�[�����I���܂ł̃J�E���g
	int							m_nJumpEndTimer;		//�Q�[���I�����̃W�����v

	static LPD3DXMESH			m_pMeshModel[MAX_PARTS];		//���b�V�����ւ̃|�C���^
	static LPD3DXBUFFER			m_pBuffMatModel[MAX_PARTS];		//�}�e���A�����ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTextureModel[MAX_PARTS];		//�e�N�X�`���ւ̃|�C���^
	static DWORD				m_nNumMatModel[MAX_PARTS];		//�}�e���A�����̐�
	// ���[�V�����֐�
	KEY_INFO					*m_pKeyInfo[MAX_MOTION];		//�L�[���ւ̃|�C���^
	int							m_nKey;							//���݂̃L�[�i���o�[
	int							m_nCountFlame;					//�t���[����

	int							m_nNumParts;					//�p�[�c��
	int							m_aIndexParent[MAX_PARTS];		//�e�̃C���f�b�N�X
	KEY							m_aKayOffset[MAX_PARTS];		//�I�t�Z�b�g���
	MOTION_INFO					m_aMotionInfo[MAX_MOTION];		//���[�V�������
	int							m_nMotionType;					//���[�V�����̃^�C�v(int�^)
	bool						m_bMotionEnd;					//���[�V�����̏I���
	D3DXVECTOR3					m_OffSetPos[MAX_PARTS];			//�I�t�Z�b�g���(���[�V����)
	CObjectBG					*m_pHole;						//�����
public:
	CModel						*m_apModel[MAX_PARTS];			//�p�[�c���
	CMeshOrbit					*m_pMeshOrbit;					//�O�Տ��
};

#endif