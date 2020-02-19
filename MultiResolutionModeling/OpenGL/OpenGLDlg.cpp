// OpenGLDlg.cpp : implementation of the COpenGLDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenGLDlg.h"

BOOL COpenGLDlg::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

BOOL COpenGLDlg::OnIdle()
{
	m_fAngle+= 1; // Add some rotation to the cube
	UpdateFPS();
	RedrawWindow();

	UIUpdateChildWindows();
	return FALSE;
}

LRESULT COpenGLDlg::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);
	m_fAngle = 0;
	COpenGL<COpenGLDlg>::OnCreate(uMsg, wParam, lParam, bHandled);


	return FALSE;
}

LRESULT COpenGLDlg::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return COpenGL<COpenGLDlg>::OnSize(uMsg, wParam, lParam, bHandled);
}

LRESULT COpenGLDlg::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	return 0;
}

LRESULT COpenGLDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

LRESULT COpenGLDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ShowWindow(SW_HIDE);
	return 0;
}

void COpenGLDlg::CloseDialog(int nVal)
{
	DestroyWindow();
	::PostQuitMessage(nVal);
}

void COpenGLDlg::OnInit(void) {
	m_fAngle = 0.0f;

	glClearColor(0.000f, 0.000f, 0.000f, 1.0f); //Background color

	// Activate lighting and a light source
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	// Define material parameters
	static GLfloat glfMatAmbient[] = {0.000f, 0.450f, 1.000f, 1.0f};
	static GLfloat glfMatDiffuse[] = {0.000f, 0.000f, 0.580f, 1.0f};
	static GLfloat glfMatSpecular[]= {1.000f, 1.000f, 1.000f, 1.0f};
	static GLfloat glfMatEmission[]= {0.000f, 0.000f, 0.000f, 1.0f};
	static GLfloat fShininess = 128.000f;

	// Set material parameters
	glMaterialfv(GL_FRONT, GL_AMBIENT,  glfMatAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE,  glfMatDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, glfMatSpecular);
	glMaterialfv(GL_FRONT, GL_EMISSION, glfMatEmission);
	glMaterialf(GL_FRONT, GL_SHININESS, fShininess);

	CRect rc;
	GetClientRect(rc);
	OnResize(rc.Width(), rc.Height());
}

void COpenGLDlg::OnRender(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear buffers
	glLoadIdentity(); // Load identity matrix

	// Add a light source
	GLfloat glfLight[] = {-4.0f, 4.0f, 4.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, glfLight);

	// Position and rotate the camera
	glTranslatef(0.0f, 0.0f, -5.0f);	
	glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fAngle, 0.0f, 1.0f, 0.0f);

	// Draw a cube
	static GLfloat r = .7f;
	GLCube(-r, -r, -r, r, r, r);

	glFlush();
}

void COpenGLDlg::OnResize(int cx, int cy) {
	GLfloat fFovy  = 30.0f; // Field-of-view
	GLfloat fZNear = 1.0f;  // Near clipping plane
	GLfloat fZFar = 10.0f;  // Far clipping plane

	// Calculate viewport aspect
	RECT rc;
	GetClientRect(&rc);

	GLfloat fAspect = (GLfloat)(rc.right-rc.left) / (GLfloat)(rc.bottom-rc.top);

	// Define viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fFovy, fAspect, fZNear, fZFar);
	glViewport(rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top);
	glMatrixMode(GL_MODELVIEW);
}

void COpenGLDlg::UpdateFPS()
{
	const int FRAMEINTERVAL = 1000;            // Show FPS every 1000th milliseconds
	static DWORD nFrames = 0;                  // Number of frames since last update
	static DWORD nLastTick = GetTickCount();   // Time of last update
	DWORD nTick = GetTickCount();              // Current time
	if(nTick-nLastTick>=FRAMEINTERVAL)
	{	
		float fFPS = 1000.0f*(GLfloat)nFrames/(GLfloat)(nTick-nLastTick);
		nLastTick = nTick;
		DWORD nFramesback = nFrames;
		nFrames = 0;
		char szFPS[256];
		sprintf_s(szFPS, sizeof(szFPS), "%.1f FPS, %d", fFPS, nFramesback);
		//SetWindowText(szFPS);
	}
	nFrames++;
}
// GLCube()
// Renders a cube.
//
void COpenGLDlg::GLCube(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{
	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x2, y2, z2);
	glVertex3f(x1, y2, z2);
	glVertex3f(x1, y1, z2);
	glVertex3f(x2, y1, z2);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(x2, y2, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y2, z1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(x1, y2, z2);
	glVertex3f(x1, y2, z1);
	glVertex3f(x1, y1, z1);
	glVertex3f(x1, y1, z2);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y1, z2);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y2, z1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x1, y2, z1);
	glVertex3f(x1, y2, z2);
	glVertex3f(x2, y2, z2);
	glVertex3f(x2, y2, z1);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y1, z1);
	glVertex3f(x2, y1, z2);
	glVertex3f(x1, y1, z2);
	glEnd();
}