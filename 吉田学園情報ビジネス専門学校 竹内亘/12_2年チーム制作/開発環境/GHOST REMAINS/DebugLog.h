//=============================================================================
//
// �����_�����O���� [DebugLog.h]
// Author : Ryo Sugimoto
//
//=============================================================================
#ifndef _DEBUGLOG_H_
#define _DEBUGLOG_H_

#include "main.h"
//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CDebugLog
{
public:
	typedef enum
	{
		MODE_NONE,		
		MODE_Change,
		MODE_INFO,
		MODE_LOG,
		MODE_MAX
	}MODE;
	CDebugLog() {};
	~CDebugLog() {};
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Printf(MODE mode, const TCHAR* format, ...);
	int  &GetnFPS(void) { return m_nFps; }

private:
	//�ϐ��錾//***********************************************************************
	void LogUpdate(void);

	MODE		m_Mode;			// ���݂̃��[�h
	LPD3DXFONT	m_pFont;		// �t�H���g�ւ̃|�C���^
	char		m_aFPS[16];		// FPS�̕�����
	char		m_aMode[64];	// MODE�̕�����
	char		m_aStr[1024];	// ������

	int			m_nFps;			//FPS�J�E���g
	int			m_nSelect;		// �I��
	bool		m_bDraw;		// �\�����
};

#endif
