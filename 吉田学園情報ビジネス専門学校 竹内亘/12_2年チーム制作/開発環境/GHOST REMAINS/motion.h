//=============================================================================
//
// ���[�V�������� [motion.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _MOTION_H_
#define _MOTION_H_

#include "main.h"
#include "scene.h"
#include "SceneAnim3D.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CHAR_PRIORITY	(1)
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CKey
{
public:
	typedef enum
	{
		TYPE_NORMAL = 0,	//�ʏ�L�[
		TYPE_ATTACK,		//�U���L�[
		TYPE_MAX
	}TYPE;
	CKey() { m_pRot = NULL; m_pEffect = NULL; };
	~CKey() {};
	void Uninit(void);

	float		&GetfSlip(void)		{ return m_fSlip; }
	float		&GetfMove(void)		{ return m_fMove; }
	int			&GetnMoveType(void) { return m_nMoveType; }
	D3DXVECTOR3 &GetPos(void)		{ return m_pos; }
	D3DXVECTOR3 *&GetpRot(void)		{ return m_pRot; }
	D3DXVECTOR3 &GetMove(void)		{ return m_move; }
	int			&GetnFrame(void)	{ return m_nFrame; }
	int			&GetnMaxEffect(void){ return m_nMaxEffect; }
	int			*&GetpEffect(void)	{ return m_pEffect; }
	int			&GetnFloating(void) { return m_nFloating; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	float		m_fSlip;		//����
	float		m_fMove;		//�ړ��\���ǂ���
	int			m_nMoveType;	//�ړ����@	0:�i�� 1:�P��
	D3DXVECTOR3 m_pos;			//���_�ړ��l
	D3DXVECTOR3 *m_pRot;		//��]�l
	D3DXVECTOR3	m_move;			//�ړ���
	int			m_nFrame;		//�t���[����
	int			m_nMaxEffect;	//����
	int			*m_pEffect;		//SA�△�G���A����
	int			m_nFloating;	//�ړ����@	0:�ʏ� 1:���V 2:�n�ʕt���Ȃ�
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CAtkKey : public CKey
{
public:

	CAtkKey() {};
	~CAtkKey() {};

	int			&GetnAtkType(void)			{ return m_nAtkType; }
	int			&GetnAtkParts(void)			{ return m_nAtkParts; }
	int			&GetnCntAtk(void)			{ return m_nCntAtk; }
	int			&GetnHitFrame(int nCount)	{ return m_nHitFrame[nCount]; }
	float		&GetfRange(void)			{ return m_fRange; }
	float		&GetfAtkplus(void)			{ return m_fAtkplus; }
	D3DXVECTOR3 &GetBlown(void)				{ return m_blown; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	int			m_nAtkType;		//�U���^�C�v
	int			m_nAtkParts;	//�U������
	int			m_nCntAtk;		//�U����
	int			m_nHitFrame[2];	//�U���L��F
	float		m_fRange;		//�U���͈�
	float		m_fAtkplus;		//�_���[�W�{��
	D3DXVECTOR3	m_blown;		//�������
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class COneMotion
{
public:

	COneMotion() { m_type = NULL; m_Key = NULL; };
	~COneMotion() {};
	void Uninit(void);

	int			&GetnNorBranch(void)			{ return m_nNorBranch; }
	int			&GetnLandBranch(void)			{ return m_nLandBranch; }
	int			&GetnStartCancel(int nNumber)	{ return m_nStartCancel[nNumber]; }
	int			&GetnEndCancel(int nNumber)		{ return m_nEndCancel[nNumber]; }
	int			&GetnOtherCancel(int nNumber)	{ return m_nOtherCancel[nNumber]; }
	int			&GetnStartKey(void)			{ return m_nStartKey; }
	int			&GetnMaxKey(void)				{ return m_nMaxKey; }
	CKey::TYPE	*&GetType(void)					{ return m_type; }
	CKey		**&GetKey(void)					{ return m_Key; }


private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	int		m_nNorBranch;		//�ʏ핪��
	int		m_nLandBranch;		//���n����
	int		m_nStartCancel[2];	//�����L�����Z��	 �J�n, �I��
	int		m_nEndCancel[2];	//�U��؂�L�����Z�� �J�n, �I��
	int		m_nOtherCancel[2];	//���̑��L�����Z��	 �J�n, �I��
	int		m_nStartKey;		//�L�����Z�����J�n�t���[��

	int			m_nMaxKey;		//�L�[�̍ő吔
	CKey::TYPE	*m_type;		//�L�[�̃^�C�v
	CKey		**m_Key;		//�L�[�{��
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CMotion
{
public:
	typedef enum
	{
		TYPE_BOX_Sword,	//��
		TYPE_ENEMY,	//�G
		TYPE_MAX
	}TYPE;
	CMotion()	{ m_OneMotion = NULL; };
	~CMotion()	{};

	static void Load(void);
	static void UnLoad(void);
	void Uninit(void);

	static CMotion *GetMotion(int nType)	 { return m_pMotion[nType]; };
	COneMotion *&GetOneMotion(void) { return m_OneMotion; };
	int &GetnMaxParts(void)			 { return m_nMaxParts; };
	int &GetnMaxMotion(void)		 { return m_nMaxMotion; };

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	static int			m_nNumMotion;			//�ő�L������
	static CMotion		**m_pMotion;				//���[�V�����{��

	int m_nMaxParts;	//�\�����Ă���p�[�c��
	int m_nMaxMotion;	//�\�����Ă��郂�[�V������
	COneMotion *m_OneMotion;
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCharParts
{
public:
	typedef enum
	{
		PLAYER_hara,		//�{�b�N�X���O	��
		PLAYER_hip,		//�{�b�N�X���O	�K
		PLAYER_head,		//�{�b�N�X���O	��
		PLAYER_armUL,		//�{�b�N�X���O	����r
		PLAYER_armDL,		//�{�b�N�X���O	���r
		PLAYER_handL,		//�{�b�N�X���O	��
		PLAYER_armUR,		//�{�b�N�X���O	�E��r
		PLAYER_armDR,		//�{�b�N�X���O	���r
		PLAYER_handR,		//�{�b�N�X���O	��
		PLAYER_legUL,		//�{�b�N�X���O	����
		PLAYER_legDL,		//�{�b�N�X���O	��
		PLAYER_footL,		//�{�b�N�X���O	��
		PLAYER_legUR,		//�{�b�N�X���O	�E��
		PLAYER_legDR,		//�{�b�N�X���O	��
		PLAYER_footR,		//�{�b�N�X���O	��

		ENEMY,				//�G
		PARTS_MAX
	}PARTS;
	CCharParts(void) {};
	~CCharParts() {};

	static void SetPlayer(CCharParts **&Parts, int &nMaxParts);
	static void SetEnemy(CCharParts **&Parts, int &nMaxParts);
	void SetParts(PARTS parts, int nPair);

	PARTS		&GetParts(void)		 { return m_type; }
	int			&GetnParent(void)	 { return m_nParent; }
	D3DXMATRIX	&GetmtxWorld(void)	 { return m_mtxWorld; }
	D3DXVECTOR3 &Getaddrot(void)	 { return m_addrot; }
	D3DXVECTOR3 &GetaddRotmove(void) { return m_addRotmove; }

private://*****************************************************************************
		//�ϐ��錾//***********************************************************************
	PARTS			m_type;						//���f���̎�� ����
	int				m_nParent;					//�e�̔ԍ�
	D3DXMATRIX		m_mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3		m_addrot;					//���Z�̌��� ���[�V����
	D3DXVECTOR3		m_addRotmove;				//���[�V�����̈ړ�
};
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CCharacter	:	public CScene
{
public:
	typedef struct
	{//��ނ��Ƃ̃��f�����ۑ�
		LPD3DXMESH		MeshModel = NULL;		//���b�V�����ւ̃|�C���^
		LPD3DXBUFFER	pBuffMatModel = NULL;	//�}�e���A�����ւ̃|�C���^
		DWORD			nNumMatModel = NULL;	//�}�e���A���̏��
		D3DXVECTOR3		addPos;					//�ʒu�̃v���X�l
		CScene::TEXTURE	tex;					//�摜
		char			aText[32];				//���f���ǂݍ��݂��x�����ߕK�v�ɂȂ�܂Ńe�L�X�g�ŊǗ�
	}MODEL_PARTS;
	typedef enum
	{
		MOTION_NEUTRAL,		//�j���[�g����
		MOTION_WALK,		//����
		MOTION_JUMP,		//�W�����v
		MOTION_LAND,		//���n
	}MOTION;
	CCharacter(int nPrioryity = CHAR_PRIORITY) : CScene::CScene(nPrioryity) { m_pTex = NULL; m_pParts = NULL; m_pScene = NULL; };
	~CCharacter() {};

	static void Load(CCharParts::PARTS parts);
	static void Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(bool bMove);	//���[�V�����̍X�V
	void Draw(void);
	void CancelUpdate(void);						//���[�V�����̃L�����Z���X�V
	void SetCancelMotion(int nNumber);				//���[�V�����̃L�����Z���ݒ�
	void ResetMotion(void);							//���[�V�������j���[�g�����Ƀ��Z�b�g
	void SetRotMotion(void);						//���݂̃L�[�Ɋp�x�����S�ɍ��킹��
	void SetPlusFrame(float fPFrame, float fCount);	//�t���[���̐i�s���x�ݒ�
	void Collision(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, float &fLength);	//�L�������m�̂����蔻��
	void CollisionAll(D3DXVECTOR3 &pos, D3DXVECTOR3 &posold, float &fLength, CScene *pChar);	//�L�������m�̂����蔻��
	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CMotion::TYPE type);			//�ݒ菈��

	D3DXVECTOR3 &Getpos(void)			{ return m_pos; }
	D3DXVECTOR3 &Getposold(void)		{ return m_posold; }
	D3DXVECTOR3 &Getrot(void)			{ return m_rot; }
	D3DXVECTOR3 &Getmove(void) { return m_move; }
	D3DXVECTOR3 &Getaddpos(void)		{ return m_addpos; }
	D3DXVECTOR3 &GetaddPosmove(void)	{ return m_addPosmove; }
	float		&GetfRot(void)		{ return m_fRot; }
	float		&GetfSpeed(void) { return m_fSpeed; }
	float		&GetfFramePlus(void) { return m_fFramePlus; }
	int			&GetnNumMotion(int nNumber) { return m_nNumMotion[nNumber]; }
	bool		&GetbJump(void) { return m_bJump; }
	float		&GetfCola(void) { return m_fCola; }
	void		Land(void);
	void		BindDrawType(CScene::DRAW_TYPE DrawType) { m_DrawType = DrawType; }

	static MODEL_PARTS *&GetpartsAll(int nNumber) { return m_partsAll[nNumber]; }

private://*****************************************************************************
	void SetEffect(CKey *&pKey);

		//�ϐ��錾//***********************************************************************
	static MODEL_PARTS	*m_partsAll[CCharParts::PARTS_MAX];	//�S�p�[�c���

	LPDIRECT3DTEXTURE9	m_pTex;				//�摜
	CScene::DRAW_TYPE	m_DrawType;			// �`�悷����@(���Z�����Ȃ�)
	int				m_nMaxParts;		//�p�[�c��
	CCharParts		**m_pParts;			//�����̃p�[�c���
	CMotion::TYPE	m_Type;				//���[�V�����̎��
	D3DXVECTOR3		m_pos;				//�v���C���[�̌��_
	D3DXVECTOR3		m_posold;			//�O��̃��f���̈ʒu
	D3DXVECTOR3		m_rot;				//�v���C���[�̌���
	D3DXVECTOR3		m_move;				//���f���̈ʒu
	D3DXVECTOR3		m_addpos;			//���Z�̈ʒu ���[�V����
	D3DXVECTOR3		m_addPosmove;		//���[�V�����̈ړ�
	D3DXVECTOR3		m_length;			//�|���S���̒���
	D3DXVECTOR3		m_FNor;				//�n�ʂ̖@��
	float			m_fCola;			//�����x
	float			m_fSpeed;			//�f����
	float			m_fRot;				//�ړ�����
	int				m_nInvincible;		//���G����
	int				m_nNumMotion[4];	//0:���݂̃��[�V���� 1:���̃��[�V���� 2:�L�[�ԍ� 3:�O�̃��[�V����
	float			m_fFrame;			//���݂̃t���[����
	float			m_fFramePlus;		//�t���[���ւ̃v���X�l
	float			m_fFramePlus2;		//�t���[���ւ̎��R�l
	float			m_fInitFrame;		//�t���[���̑��x�������������܂ł̒l
	float			m_fMotionFrame;		//MOTION�S�̂̃t���[�������J�E���g
	int				m_nCancelFrame;		//�L�����Z���҂��̕ێ��t���[����
	int				m_nLeg;				//�E�����o���Ă��邩�������o���Ă��邩
	int				m_nStamina;			//�X�^�~�i
	int				m_nHit[16];			//�������G
	bool			m_bJump;
	CScene			*m_pScene;
	CScene3D		*m_pShadow;			//�e�̃|�C���^
	//int				nLockChar;				//lock���Ă���L����

};
#endif
