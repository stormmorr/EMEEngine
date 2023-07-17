/*
* "$Id$"
*
*   OpenGL quadric pencil demo.
*
* Contents:
*
*   WinMain()             - Main entry...
*   DisplayErrorMessage() - Display an error message dialog.
*   MakePalette()         - Make a color palette for RGB colors if
*                           necessary.
*   PencilProc()           - Handle window events in the viewing window.
*   LoadAllTextures()     - Load texture images for the scene.
*   RepaintWindow()       - Redraw the client area with our scene.
*
* Revision History:
*
*   $Log$
*/

/*
* Include necessary headers.
*/
#define _WIN32_WINNT 0x0500 
#include "texture.h"
#include "pencil.h"
#include <stdarg.h>
#include <math.h>

// #define NUM_PENCILS 1000
#define NUM_PENCILS 1000

/*
* Globals...
*/

HWND		PencilWindow;		/* Scene window */
HDC			PencilDC;		/* Drawing context */
HGLRC		PencilRC[2];		/* OpenGL rendering context */

GLuint		PencilTexture[2],LeadTexture[2];		/* Lead... */

GLfloat		PencilRoll[NUM_PENCILS]; // = {0.0, 90.0, 30.0, 45.0, 60.0};	/* Pencil orientation */
GLfloat		PencilPitch[NUM_PENCILS]; // = {0.0, 15.0, 30.0, 45.0, 60.0};
GLfloat		PencilHeading[NUM_PENCILS]; // = {0.0, 15.0, 30.0, 45.0, 60.0};
GLfloat		PencilRollDelta[NUM_PENCILS];
GLfloat		PencilPitchDelta[NUM_PENCILS];
GLfloat		PencilHeadingDelta[NUM_PENCILS];
GLUquadricObj	*PencilObj;
GLfloat		g_zAngle;
int			rec_width, rec_height;

void			DisplayErrorMessage(char *, ...);
LRESULT CALLBACK	PencilProc(HWND, UINT, WPARAM, LPARAM);
void			LoadAllTextures(int i);
void			RepaintWindow(RECT *);
static DWORD dwScreenWidth = 1280;
static DWORD dwScreenHeight = 1024;

BOOL bSetDisplayMode(void)
{
	DEVMODE deviceMode;
	HWND hDesktop = GetDesktopWindow();
	HDC  hDCDesk = GetDC(hDesktop);
	deviceMode.dmSize = sizeof(DEVMODE);
	deviceMode.dmBitsPerPel = GetDeviceCaps(hDCDesk,BITSPIXEL);
	ReleaseDC(hDesktop,hDCDesk);
	deviceMode.dmPelsWidth = dwScreenWidth;
	deviceMode.dmPelsHeight = dwScreenHeight;
	deviceMode.dmFields = DM_BITSPERPEL	| DM_PELSWIDTH | DM_PELSHEIGHT;

	if(ChangeDisplaySettings(&deviceMode,0) == DISP_CHANGE_SUCCESSFUL)
		return TRUE;

	return FALSE;
}

int GetNProc()
{
	SYSTEM_INFO sys;
	GetSystemInfo(&sys);
	int nProc = sys.dwNumberOfProcessors;
	char *sproc = getenv("NPROC");
	if (sproc)
		nProc = atoi(sproc);
	return nProc;
}

/*
* 'WinMain()' - Main entry...
*/

int APIENTRY
WinMain(HINSTANCE hInst,		/* I - Current process instance */
		HINSTANCE hPrevInstance,	/* I - Parent process instance */
		LPSTR     lpCmdLine,		/* I - Command-line arguments */
		int       nCmdShow)		/* I - Show window at startup? */
{
	MSG		msg;			/* Window UI event */
	WNDCLASS	wc;			/* Window class */
	RECT		rect;			/* Current client area rectangle */
	int i;

	if (!bSetDisplayMode())
		return (FALSE);
	
	wc.style         = 0;
	wc.lpfnWndProc   = (WNDPROC)PencilProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInst;
	wc.hIcon         = NULL;
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = 0;         
	wc.lpszClassName = "Textured Quadric Pencil";

	if (RegisterClass(&wc) == 0)
	{
		DisplayErrorMessage("Unable to register window class!");
		return (FALSE);
	};

	PencilWindow = CreateWindow("Textured Quadric Pencil", "Textured Quadric Pencil",
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP | WS_VISIBLE,
		0, 0, dwScreenWidth, dwScreenHeight,
		NULL, NULL, hInst,NULL);

	if (PencilWindow == NULL)
	{
		DisplayErrorMessage("Unable to create window!");
		return (FALSE);
	};

	for(i=0;i<NUM_PENCILS; i++)
	{
		PencilRollDelta[i] = (rand() % 30 ) / 20.0f;
		PencilPitchDelta[i] = (rand() % 30 ) / 20.0f;
		PencilHeadingDelta[i] = (rand() % 30 ) / 20.0f;
	}
	ShowWindow(PencilWindow, nCmdShow);
	UpdateWindow(PencilWindow);

	while (TRUE)
	{

		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
			if (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				return (1);


		for(i=0;i<NUM_PENCILS;i++)
		{
			
			PencilRoll[i]    += PencilRollDelta[i];
			PencilPitch[i]   += PencilPitchDelta[i];
			PencilHeading[i] += PencilHeadingDelta[i];
			
		}

		GetClientRect(PencilWindow, &rect);
		RepaintWindow(&rect);
	};

	return (msg.wParam);
}


/*
* 'DisplayErrorMessage()' - Display an error message dialog.
*/

void
DisplayErrorMessage(char *format,	/* I - printf() style format string */
					...)		/* I - Other arguments as necessary */
{
	va_list	ap;			/* Argument pointer */
	char		s[1024];		/* Output string */


	if (format == NULL)
		return;

	va_start(ap, format);
	vsprintf(s, format, ap);
	va_end(ap);

	MessageBeep(MB_ICONEXCLAMATION);
	MessageBox(NULL, s, "Error", MB_OK | MB_ICONEXCLAMATION);
}


LRESULT CALLBACK
PencilProc(HWND   hWnd,		/* I - Window triggering this event */
		   UINT   uMsg,		/* I - Message type */
		   WPARAM wParam,		/* I - 'word' parameter value */
		   LPARAM lParam)		/* I - 'long' parameter value */
{
	int			pf;	/* Pixel format ID */
	PIXELFORMATDESCRIPTOR pfd;	/* Pixel format information */
	PAINTSTRUCT		ps;	/* WM_PAINT message info */
	RECT			rect;	/* Current client area rectangle */


	switch (uMsg)
	{
	case WM_CREATE :
		/*
		* 'Create' message.  Get device and rendering contexts, and
		* setup the client area for OpenGL drawing...
		*/

		PencilDC = GetDC(hWnd);              

		pfd.nSize        = sizeof(pfd);
		pfd.nVersion     = 1;
		pfd.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.dwLayerMask  = PFD_MAIN_PLANE;	/* Main drawing plane */
		pfd.iPixelType   = PFD_TYPE_RGBA;	/* RGB color buffer */
		pfd.cColorBits   = 0;			/* Best color buffer please */
		pfd.cDepthBits   = 32;			/* Need a depth buffer */
		pfd.cStencilBits = 0;			/* No stencil buffer */
		pfd.cAccumBits   = 0;			/* No accumulation buffer */

		pf = ChoosePixelFormat(PencilDC, &pfd);
		if (pf == 0)
			DisplayErrorMessage("texscene was unable to choose a suitable pixel format!");
		else if (!SetPixelFormat(PencilDC, pf, &pfd))
			DisplayErrorMessage("texscene was unable to set the pixel format!");

		PencilRC[0] = wglCreateContext(PencilDC);
		wglMakeCurrent(PencilDC, PencilRC[0]);
		LoadAllTextures(0);
		PencilObj = gluNewQuadric();
		gluQuadricTexture(PencilObj, GL_TRUE);

		PencilRC[1] = wglCreateContext(PencilDC);
		wglMakeCurrent(PencilDC, PencilRC[1]);
		LoadAllTextures(1);

		wglMakeCurrent(PencilDC, PencilRC[0]);

		break;

	case WM_SIZE :
	case WM_PAINT :
		/*
		* Repaint the client area with our bitmap...
		*/

		BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rect);
		RepaintWindow(&rect);

		EndPaint(hWnd, &ps);
		break;

	case WM_KEYDOWN:
		// Escape key, exit the program
		if(wParam == VK_ESCAPE)
		{
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_QUIT :
	case WM_CLOSE :
		DestroyWindow(PencilWindow);

		exit(0);
		break;

	case WM_DESTROY :
		if (PencilRC[0])
			wglDeleteContext(PencilRC[0]);
		if (PencilRC[1])
			wglDeleteContext(PencilRC[1]);

		if (PencilDC)
			ReleaseDC(PencilWindow, PencilDC);

		ChangeDisplaySettings(NULL,0);

		PostQuitMessage(0);
		break;

	default :
		return (DefWindowProc(hWnd, uMsg, wParam, lParam));
	};

	return (FALSE);
}


/*
* 'LoadAllTextures()' - Load texture images for the scene.
*/

void
LoadAllTextures(int i)
{
	PencilTexture[i] = TextureLoadBitmap("pencil.bmp");
	LeadTexture[i] = TextureLoadBitmap("lead.bmp");
}

static UINT ThreadFunc(LPVOID lpParam)
{
	int threadId = (lpParam ? 1 : 0);
	static int nProc = GetNProc();

	if (nProc > 1)
		wglMakeCurrent(PencilDC, PencilRC[threadId]);
	
	// Setup Lighting and initial configuration of a circle
	{
		glViewport(0,0,rec_width, rec_height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, (float)rec_width / (float)rec_height,
			0.1, 10000.0);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, -50.0f, -500.0f);
		if (threadId == 0)
			glRotatef(75.0f, 1.0, 0.0, 0.0);
		else
		{
			glTranslatef(0.0f, 0.0f, -100.0f);
			glRotatef(40.0f, 1.0, 0.0, 0.0);
			glRotatef(80.0f, 0.0, 1.0, 0.0);
		}
		glRotatef(g_zAngle,0.0f, 0.0f, 1.0f);
	}

	for (int i=0;i<NUM_PENCILS;i++)
	{
		glPushMatrix();
		// Render each pencil
		{
			glRotatef(360.0f * i / NUM_PENCILS, 0.0f, 0.0f, 1.0f);
			glTranslatef(300.0f, 0.0f, 0.0f);

			glRotatef(PencilHeading[i], 0.0, -1.0, 0.0);
			glRotatef(PencilPitch[i], 1.0, 0.0, 0.0);
			glRotatef(PencilRoll[i], 0.0, 0.0, -1.0);

			gluQuadricNormals(PencilObj, GLU_FLAT);
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, PencilTexture[threadId] );

			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, -20.0);
				gluCylinder(PencilObj, 5.0, 5.0, 40.0, 6, 2);
			}
			glPopMatrix();

			gluQuadricNormals(PencilObj, GLU_SMOOTH);
			glEnable( GL_TEXTURE_2D );
			glBindTexture( GL_TEXTURE_2D, LeadTexture[threadId] );

			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, 20.0);
				gluCylinder(PencilObj, 5.0, 0.0, 7.5, 6, 2);
			}
			glPopMatrix();

			glPushMatrix();
			{
				glTranslatef(0.0, 0.0, -20.0);

				gluCylinder(PencilObj, 5.0, 0.0, 0.0, 6, 2);
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	glFinish();

	return 0;
}

void RepaintWindow(RECT *rect)	/* I - Client area rectangle */
{
	int i;
	static GLfloat zAngle = 0;
	static HANDLE hThread;
	int nProc = GetNProc();
	
	zAngle += 0.4f;
	g_zAngle = zAngle;
	
	rec_width = rect->right;
	rec_height = rect->bottom;

	glClearColor(0.3, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (nProc < 1)
		hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) ThreadFunc, NULL, 0, NULL);
	else
		ThreadFunc(NULL);
	
	//ThreadFunc(&nProc);
	
	if (nProc > 1)
		WaitForSingleObject(hThread, INFINITE);
	
	SwapBuffers(PencilDC);
}
