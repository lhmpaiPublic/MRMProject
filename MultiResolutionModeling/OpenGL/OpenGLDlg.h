// OpenGLDlg.h : interface of the OpenGLDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

//OpenGL
class COpenGLDlg : public CDialogImpl<COpenGLDlg>, COpenGL<COpenGLDlg> ,public CUpdateUI<COpenGLDlg>,
		public CMessageFilter, public CIdleHandler
{
	GLfloat m_fAngle;		// Rotation angle of the cube

	GLubyte* buffer[5];
	GLuint texId[5];
public:

	enum { IDD = IDD_OPENGLDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(COpenGLDlg)

	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(COpenGLDlg)
		CHAIN_MSG_MAP(COpenGL<COpenGLDlg>)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		CHAIN_MSG_MAP(CUpdateUI<COpenGLDlg>)
		
		REFLECT_NOTIFICATIONS()		

	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	void CloseDialog(int nVal);

	void OnInit(void);
	void OnRender(void);
	void OnResize(int cx, int cy);
	void UpdateFPS();
	void GLCube(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);
};
