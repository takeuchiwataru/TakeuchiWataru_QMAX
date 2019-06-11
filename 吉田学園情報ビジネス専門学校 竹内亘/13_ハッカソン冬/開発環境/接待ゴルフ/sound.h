//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*********************************************************************
//�T�E���h�N���X�̒�`
//*********************************************************************
//��{�N���X
class CSound
{
public:
	// �T�E���h�t�@�C��
	typedef enum //���x���Ɛ��ƕ��т𑵂���
	{
		SOUND_LABEL_BGM_TITLE = 0,	// BGM�^�C�g��
		SOUND_LABEL_BGM_TUTORIAL,	// BGM�`���[�g���A��
		SOUND_LABEL_BGM_GAME,		// BGM�Q�[��
		SOUND_LABEL_BGM_RESULT,		// BGM���U���g
		SOUND_LABEL_BGM_GAMEOVER,	// BGM�Q�[���I�[�o�[
		SOUND_LABEL_BGM_RANKING,	// BGM�����L���O
		SOUND_LABEL_SE_SHOT,		// �V���b�g
		SOUND_LABEL_SE_HAKUSYU,		// ����
		SOUND_LABEL_SE_CUPIN,		// �J�b�v�C��
		SOUND_LABEL_SE_NOTCUPIN,	// �J�b�v�C�����Ȃ������Ƃ�

		SOUND_LABEL_MAX,
	} SOUND_LABEL;
	// �p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g(-1�Ń��[�v�Đ�)
	} SOUNDPARAM;

	CSound();
	~CSound();
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

protected:
	IXAudio2				*m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃|�C���^
	IXAudio2MasteringVoice	*m_pMasteringVoice = NULL;						// �}�X�^�[�{�C�X�ւ̃|�C���^
	IXAudio2SourceVoice		*m_apSourceVoice[SOUND_LABEL_MAX] = {};			// �\�[�X�{�C�X�ւ̃|�C���^
	BYTE					*m_apDataAudio[SOUND_LABEL_MAX] = {};			// �I�[�f�B�I�f�[�^�ւ̃|�C���^
	DWORD					m_aSizeAudio[SOUND_LABEL_MAX] = {};				// �I�[�f�B�I�f�[�^�T�C�Y
    // �e���f�ނ̃p�����[�^ ���x���Ɛ��ƕ��т𑵂���
	SOUNDPARAM m_aSoundParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/title.wav", -1 },		// �^�C�g��
		{ "data/BGM/tutorial.wav", -1 },	// �`���[�g���A��
		{ "data/BGM/game.wav", -1 },		// �Q�[��
		{ "data/BGM/result.wav", -1 },		// ���U���g
		{ "data/BGM/gameover.wav", -1 },	// �Q�[���I�[�o�[
		{ "data/BGM/ranking.wav", -1 },		// �����L���O
		{ "data/SE/shot.wav", 0 },			// �{�[����ł������̉�
		{ "data/SE/hakusyu.wav", 0 },		// ���芅�щ�
		{ "data/SE/cupin.wav", 0 },			// �z�[���C�������������̉�
		{ "data/SE/Notin.wav", 0 },			// �z�[���C�������������̉�
	};
};
#endif
