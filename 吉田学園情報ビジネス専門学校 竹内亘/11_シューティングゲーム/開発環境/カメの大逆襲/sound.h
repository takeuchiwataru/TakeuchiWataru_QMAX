//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : �|���j
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CSound
{
public:
	//*****************************************************************************
	// �p�����[�^�\���̒�`
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	//*************************************
	// �T�E���h�t�@�C��
	//*************************************
	typedef enum //���x���Ɛ��ƕ��т𑵂���
	{
		SOUND_LABEL_BGM_GAME = 0,
		SOUND_LABEL_BGM_TITLE,
		SOUND_LABEL_BGM_TUTORIAL,
		SOUND_LABEL_BGM_CLEAR,
		SOUND_LABEL_BGM_OVER,
		SOUND_LABEL_SE_BABURU,
		SOUND_LABEL_SE_EXPLOSION,
		SOUND_LABEL_SE_PS,
		SOUND_LABEL_SE_DAMAGE,
		SOUND_LABEL_SE_SELECT,
		SOUND_LABEL_SE_ENETR,
		SOUND_LABEL_MAX
	} SOUND_LABEL;

	CSound();
	~CSound();

	virtual HRESULT Init(HWND hWnd);
	virtual void Uninit(void);

	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	IXAudio2 *m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^ ���x���Ɛ��ƕ��т𑵂���
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{"data/BGM/game.wav",-1},		// �Q�[��BGM
		{"data/BGM/title.wav",-1 },		// �^�C�g��BGM
		{"data/BGM/tutorial.wav",-1 },	// �`���[�g���A��BGM
		{"data/BGM/clear.wav",-1 },		// �N���ABGM
		{"data/BGM/over.wav",-1 },		// �I�[�o�[BGM
		{"data/SE/baburu.wav",0},		// �e�̔���(�o�u��)
		{"data/SE/explosion.wav",0 },	// ����(�o�u��)
		{"data/SE/ps.wav",0 },	// ����(�o�u��)
		{"data/SE/damage.wav",0},		// �_���[�W
		{"data/SE/select.wav", 0 },		// �I����
		{"data/SE/enter.wav", 0 },		// ���艹

		//{ "data/BGM/game.wav", -1 },		// �Q�[��BGM
		//{ "data/BGM/title.wav", -1 },		// �^�C�g��BGM
		//{ "data/BGM/3Dranking.wav", -1 },		// �����L���OBGM
		//{ "data/BGM/gameclear.wav", -1 },	// �Q�[���N���ABGM
		//{ "data/BGM/gameover.wav", -1 },	// �Q�[���I�[�o�[BGM
		//{ "data/SE/karasu.wav", 0 },		// �J���X�̖���
		//{ "data/SE/pause000.wav", 0 },		// �|�[�Y�J��
		//{ "data/SE/pause001.wav", 0 },		// �|�[�Y����
		//{ "data/SE/select000.wav", 0 },		// �I����
		//{ "data/SE/enter001.wav", 0 },		// ���艹
	};
};
#endif
