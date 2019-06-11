//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSound
{// �T�E���h�N���X
public:
	typedef enum
	{// �T�E���h�t�@�C��
		/* *** BGM *** */
		LABEL_TITLE = 0,		// �^�C�g��
		LABEL_TUTORIAL,		// �`���[�g���A��
		LABEL_GAME,			// �Q�[��
		LABEL_ESCAPE,			// �ǂ��Ă���
		LABEL_CLEAR,			// �N���A
		LABEL_OVER,			// �Q�[���I�[�o�[
		LABEL_RESULT,		// �`���[�g���A��
		LABEL_RANKING,		// �����L���O
		LABEL_SE_START,		// �X�^�[�g
		LABEL_SE_ENEMY,		// �G�̏o��
		LABEL_SE_DETH,		// �v���C���[�̎��S��
		LABEL_SE_APPIROBJ,	// �I�u�W�F�N�g�o����
		LABEL_SE_DropBrock,	// �����鏰
		LABEL_SE_HEARTBEAT,	// �S����
		LABEL_SE_JUMP,		// �W�����v
		LABEL_SE_SPEAR,		// ��
		LABEL_SE_SWICH,		// �{�^��
		LABEL_SE_FIRE,		// ��
		LABEL_SE_LAND,		// ���n
		LABEL_SE_PAUSE,		// �|�[�Y
		LABEL_SE_ENTTER,		// ���艹
		LABEL_SE_CURSOR,		// �J�[�\��
		LABEL_SE_WALK,		// ����
		LABEL_SE_CANCEL,		// �L�����Z��
		LABEL_SE_RANKING,		// �����L���O

		LABEL_MAX	// ����
	} LABEL;

	CSound();
	~CSound() {};
	HRESULT Init(HWND hWnd);
	void	Uninit(void);
	HRESULT Play(LABEL label);
	void	Stop(LABEL label);
	void	Stop(void);
	void	CountUp(void);
	void	CountReset(LABEL label) { m_aSoundParam[label].nCntFrame = 0; };
private:
	typedef struct
	{// �p�����[�^
		char *pFilename;	// �t�@�C����
		int  nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
		int  nPlayNext;		//���̍Đ��܂łɕK�v��F��
		int  nCntFrame;		//���݂�F�J�E���g
	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice	*m_apSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	PARAM m_aSoundParam[LABEL_MAX] =
	{
		/* *** BGM *** */
		{ "data/BGM/00_title.wav", -1, 5 },			// �^�C�g��
		{ "data/BGM/01_tutorial.wav", -1, 5 },		// �`���[�g���A��
		{ "data/BGM/02_game.wav", -1, 5 },			// �Q�[��
		{ "data/BGM/03_escape.wav", -1, 5 },		// �ǂ��Ă���
		{ "data/BGM/04_gameclear.wav", -1, 5 },		// �Q�[���N���A
		{ "data/BGM/05_gameover.wav", -1, 5 },		// �Q�[���I�[�o�[
		{ "data/BGM/Result.wav", -1, 5 },		// ���U���g
		{ "data/BGM/06_ranking.wav", -1, 5 },		// �����L���O
		{ "data/SE/00_gamestart.wav", 0, 5 },		// �Q�[���X�^�[�g
		{ "data/SE/01_enemyappearance.wav", 0, 5 },	// �G�̏o��
		{ "data/SE/02_death.wav", 0, 120 },			// ���S
		{ "data/SE/03_appearance.wav", 0, 5 },		// �I�u�W�F�N�g�̏o��
		{ "data/SE/04_Drop.wav", 0, 5 },			// �����鏰
		{ "data/SE/05_heartbeat.wav",0, 5 },		// �S��
		{ "data/SE/06_jump.wav",0, 5 },				// �W�����v
		{ "data/SE/07_spear.wav",0, 5 },			// ��
		{ "data/SE/08_swich02.wav",0, 5 },			// �{�^��
		{ "data/SE/09_fire.wav",0, 5 },				// ��
		{ "data/SE/10_landing.wav",0, 5 },			// ����
		{ "data/SE/11_pause.wav",0, 5 },			// �|�[�Y��
		{ "data/SE/12_decision.wav",0, 5 },			// ���艹
		{ "data/SE/13_cursor.wav",0, 5 },			// �J�[�\����
		{ "data/SE/15_foot.wav",0, 5 },				// �L�����Z����
		{ "data/SE/14_cancel.wav",0, 5 },			// �L�����Z����
		{ "data/SE/RankingSE.wav",0, 5 },			// �L�����Z����

	};
};

#endif
