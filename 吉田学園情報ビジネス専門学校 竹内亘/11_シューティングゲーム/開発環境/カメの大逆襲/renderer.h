//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : �|���j
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�̒�`
//*****************************************************************************
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//LPDIRECT3DDEVICE9 GetDevice(void);
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }
private:
#ifdef _DEBUG
	void DrawFPS(void);
#endif
	// �����o�ϐ�
	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	bool m_bPause;							// �|�[�Y�����ǂ���
	static CPause *m_pPause;

#ifdef _DEBUG
	LPD3DXFONT				m_pFont;		// �t�H���g�ւ̃|�C���^
	int						m_nCountFPS;	// FPS�J�E���^
#endif

};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

#endif