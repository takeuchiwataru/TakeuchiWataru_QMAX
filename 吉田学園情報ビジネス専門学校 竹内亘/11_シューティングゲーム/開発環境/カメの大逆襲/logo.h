//=============================================================================
//
// ���S���� [logo.h]
// Author : �|���j
//
//=============================================================================
#ifndef _LOGO_H_
#define _LOGO_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TITLELOGO_TEXTURE "data/TEXTURE/title_logo.png"			// �^�C�g�����S�̃e�N�X�`��
#define RESULTLOGO_TEXTURE000 "data/TEXTURE/gameclear.png"	// ���U���g���S(�N���A)�̃e�N�X�`��
#define RESULTLOGO_TEXTURE001 "data/TEXTURE/gameover.png"		// ���U���g���S(�I�[�o�[)�̃e�N�X�`��
#define TUTORIALLOGO_TEXTURE "data/TEXTURE/tutorial_logo.png"	// �`���[�g���A�����S�̃e�N�X�`��
#define RANKINGLOGO_TEXTURE ""
#define PRESSENTER_TEXTURE "data/TEXTURE/press_enter.png"		// �v���X�G���^�[�̃e�N�X�`��
#define PRESSENTER_TEXTURE002 "data/TEXTURE/press_enter2.png"		// �v���X�G���^�[�̃e�N�X�`��
#define PAUSEMAT_TEXTURE	"data/TEXTURE/pause200.png"			// �|�[�Y�䎆�̃e�N�X�`��
#define PAUSESELECT_TEXTURE000	"data/TEXTURE/pause101.png"		// CONTINUE
#define PAUSESELECT_TEXTURE001	"data/TEXTURE/pause102.png"		// RETRY
#define PAUSESELECT_TEXTURE002	"data/TEXTURE/pause103.png"		// QUIT
#define FRAME_TEXTURE000 "data/TEXTURE/life_frame.png"			// ���C�t�t���[��
#define FRAME_TEXTURE001 "data/TEXTURE/score_frame.png"			// �X�R�A�t���[��
#define IMAGE_TEXTURE000 "data/TEXTURE/remain000.png"			// �v���C���[1�̎c�@
#define IMAGE_TEXTURE001 "data/TEXTURE/remain001.png"			// �v���C���[1�̎c�@
#define IMAGE_TEXTURE002 "data/TEXTURE/tutorial000.png"			// �R���g���[���[����
#define IMAGE_TEXTURE003 "data/TEXTURE/tutorial001.png"			// PS����
#define RANKINGRANK_TEXTURE "data/TEXTURE/ranking_rank.png"		// �����L���O�����N
#define LOGO_SIZE_X (150)
#define LOGO_SIZE_Y (50)
#define TEXTURE_SIZE_X      (400)								// �e�N�X�`���𒣂�t���镝
#define TEXTURE_SIZE_Y      (150)								// �e�N�X�`���𒣂�t���鍂��
#define PRESSENTER_SIZE_X   (250)								// �v���X�G���^�[��
#define PRESSENTER_SIZE_Y   (50)								// �v���X�G���^�[����

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CLogo : public CScene
{
public:
	CLogo(int nPriority);
	~CLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPosition(D3DXVECTOR3 pos, float fwidth, float fheight);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetColor(D3DXCOLOR col);					// �J���[�̐ݒu
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);

private:
	LPDIRECT3DTEXTURE9	m_pTexture;						// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^

protected:
	D3DXVECTOR3				m_pos;						// �ʒu
	D3DXVECTOR3				m_move;						// �ړ�
	D3DXCOLOR				m_col;						// �F
}; 
//*****************************************************************************
// �^�C�g�����S�N���X�̒�`
//*****************************************************************************
class CTitleLogo : public CLogo
{
public:
	CTitleLogo();
	~CTitleLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTitleLogo * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`���̃|�C���^
};
//*****************************************************************************
// ���U���g�N���X���S�N���X�̒�`
//*****************************************************************************
class CResultLogo : public CLogo
{
public:
	typedef enum
	{// ���U���g�̎��
		RESULTTYPE_CLEAR,
		RESULTTYPE_OVER,
		RESULTTYPE_MAX,
	}RESULTTYPE;

	CResultLogo();
	~CResultLogo();
	HRESULT Init(D3DXVECTOR3 pos, RESULTTYPE type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CResultLogo * Create(D3DXVECTOR3 pos,RESULTTYPE type);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[RESULTTYPE_MAX];	// ���L�e�N�X�`���̃|�C���^
	RESULTTYPE m_nType;										// ���U���g�̎��
};
//*****************************************************************************
// �`���[�g���A�����S�N���X�̒�`
//*****************************************************************************
class CTutorialLogo : public CLogo
{
public:
	CTutorialLogo();
	~CTutorialLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTutorialLogo * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`���̃|�C���^
};
//*****************************************************************************
// �����L���O���S�N���X�̒�`
//*****************************************************************************
class CRankingLogo : public CLogo
{
public:
	CRankingLogo();
	~CRankingLogo();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CRankingLogo * Create(D3DXVECTOR3 pos);
	static HRESULT Load(void);
	static void Unload(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`���̃|�C���^
};
//*****************************************************************************
// �v���X�G���^�[�N���X�̒�`
//*****************************************************************************
class CPressEnter : public CLogo
{
public:
	typedef enum
	{//�v���X�G���^�[�̏��
		PRESSENTERSTATE_NONE = 0,
		PRESSENTERSTATE_PUSH,
		PRESSENTERSTATE_MAX
	}PRESSENTERSTATE;

	typedef enum
	{//�v���X�G���^�[
		PRESSENTER_TITLE = 0,
		PRESSENTER_TUTORIAL,
		PRESSENTER_MAX
	}PRESSENTER;

	CPressEnter();
	~CPressEnter();
	HRESULT Init(D3DXVECTOR3 pos, PRESSENTER type);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CPressEnter * Create(D3DXVECTOR3 pos,PRESSENTER type);
	static HRESULT Load(void);
	static void Unload(void);
	static void DispPressEnter(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[PRESSENTER_MAX];				// ���L�e�N�X�`���̃|�C���^
	PRESSENTERSTATE         m_PressEnterState;			// ���
	PRESSENTER				m_nType;					// ���
	int                     m_nCounterPressEnter;		// Draw����^�C�~���O�Ǘ��J�E���^�[
	static bool             m_bDisp;					// �`�悷�邩���Ȃ���
};
#endif
