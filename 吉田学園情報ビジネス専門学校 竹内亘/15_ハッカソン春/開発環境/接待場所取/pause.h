//=============================================================================
//
// �|�[�Y���� [pause.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PAUSEMENU			(3)							//�����L���O�̐�

//*********************************************************************
//�Q�[���N���X�̒�`
//*********************************************************************
class CPause : public CScene //�h���N���X
{
public:
	typedef enum
	{
		SELECTMODE_NONE = 0,
		SELECTMODE_CONTINUE,		//���s���
		SELECTMODE_RETRY,			//���g���C���
		SELECTMODE_QUIT,			//�I��
		SELECTMODE_MAX				//��Ԃ̑���
	}SELECTMODE;					//�񋓌^

	typedef enum
	{
		SELECTTYPE_NONE = 0,	//�I�΂�Ă��Ȃ����
		SELECTTYPE_SELECT,		//�I�΂�Ă���	���
		SELECTTYPE_MAX			//��Ԃ̑���
	}SELECT;

	typedef struct
	{
		SELECT		select;		//�Z���N�g
		D3DXVECTOR3 pos;		//�ʒu
		D3DXCOLOR	col;		//�J���[
	}PAUSESELECT;

	CPause(int nPriority = 7);
	~CPause();
	static CPause *Create(D3DXVECTOR3 pos, float fLength);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static SELECTMODE *GetPauseMode(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static bool GetPauseBool(void);
	static void SetPauseBool(bool PauseBool);
	//�����o�ϐ�
private:
	D3DXVECTOR3					m_InitPos;
	float						m_fWidth, m_fHeight;	// ������
	D3DXVECTOR3					m_TexMove;


	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_PAUSEMENU];			// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;							// ���_�o�b�t�@�ւ̃|�C���^
	static LPDIRECT3DTEXTURE9	m_pTextureBG;						// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffBG;						// ���_�o�b�t�@�ւ̃|�C���^
	CScene2D					*m_apPolygonBG;						// ���j���[�̃|���S��

	PAUSESELECT					m_aPauseMenu[MAX_PAUSEMENU];		// �|�[�Y���j���[
	D3DXVECTOR3					m_Pos[MAX_PAUSEMENU];				// �ʒu
	static SELECTMODE			m_SelectMode;						// �I�����Ă郂�[�h
	int							m_nSelect;							// �I�����Ă���ԍ�
	CScene2D					*m_apPolygon[MAX_PAUSEMENU];		// ���j���[�̃|���S��
	static	bool				m_bPause;							// �|�[�Y�̏��
};

#endif