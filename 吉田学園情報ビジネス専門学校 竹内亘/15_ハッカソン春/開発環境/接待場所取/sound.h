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
		SOUND_LABEL_SE_DECIDE,		// ����
		SOUND_LABEL_SE_PAUSE,		// �|�[�Y
		SOUND_LABEL_SE_SELECT,		// �Z���N�g
		SOUND_LABEL_SE_CANCEL,		// �L�����Z��

		SOUND_LABEL_SE_FOOTSTEP,	// ����
		SOUND_LABEL_SE_JUMP,		// �W�����v
		SOUND_LABEL_SE_SCORE,		// �X�R�A���Z
		SOUND_LABEL_SE_ITEMGET,		// �A�C�e���l��
		SOUND_LABEL_SE_SODAFULL,	// �Y�_
		SOUND_LABEL_SE_SODA,		// �Y�_2
		SOUND_LABEL_SE_SODAKAIHOU,	// ���
		SOUND_LABEL_SE_TUMBLE,		// �]����
		SOUND_LABEL_SE_HIT00,		// �Փ�
		SOUND_LABEL_SE_HIT01,		// �Փ�
		SOUND_LABEL_SE_HIT02,		// �Փ�
		SOUND_LABEL_SE_START00,		// �X�^�[�g
		SOUND_LABEL_SE_START01,		// �X�^�[�g

		SOUND_LABEL_SE_DAMAGE,		// �X�^�[�g
		SOUND_LABEL_SE_BREAK,		// �X�^�[�g
		SOUND_LABEL_SE_THROW,		// �X�^�[�g
		SOUND_LABEL_SE_WARNING,		// �X�^�[�g

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
		{ "data/SE/decide.wav", 0 },		// ���艹
		{ "data/SE/pause.wav", 0 },			// �|�[�Y��
		{ "data/SE/select.wav", 0 },		// �Z���N�g��
		{ "data/SE/cansel.wav", 0 },		// �L�����Z����
		{ "data/SE/footstep2.wav", 0 },		// ����
		{ "data/SE/jump.wav", 0 },			// �W�����v��
		{ "data/SE/score.wav", 0 },			// �X�R�A��
		{ "data/SE/itemget.wav", 0 },		// �A�C�e���Q�b�g��
		{ "data/SE/sodafull.wav", 0 },		// �Y�_��
		{ "data/SE/soda.wav", 0 },			// �Y�_��
		{ "data/SE/kaihou.wav", 0 },		// �����
		{ "data/SE/tumble.wav", 0 },		// �]���艹
		{ "data/SE/destroy002.wav", 0 },	// �Ռ���000
		{ "data/SE/destroy003.wav", 0 },	// �Ռ���001
		{ "data/SE/hit.wav", 0 },			// �Ռ���002
		{ "data/SE/Start00.wav", 0 },			// �X�^�[�g��00
		{ "data/SE/Start01.wav", 0 },			// �X�^�[�g��01

		{ "data/SE/damage.wav", 0 },		// �Ռ���001
		{ "data/SE/glass-break.wav", 0 },	// �Ռ���002
		{ "data/SE/throw.wav", 0 },			// �X�^�[�g��00
		{ "data/SE/warning.wav", 0 },		// �X�^�[�g��01

	};
};
#endif
