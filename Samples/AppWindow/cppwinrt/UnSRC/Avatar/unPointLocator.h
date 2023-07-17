/*

	unPointLocator - Visual Aid for locating a physical 3d point
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef __Point_Locator_h__
#define __Point_Locator_h__

#include "Q-PortSHELL-VAR.h"

#ifdef UNIFICATION
#if 0
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// EGL includes
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#endif
#endif

class unPointLocator
{
public:
	unPointLocator() { i_Pos.x = 0; i_Pos.y = 0; i_Pos.z = 0; };
	~unPointLocator() {};

	void setPos(float i_x, float i_y, float i_z) { i_Pos.x = i_x; i_Pos.y = i_y; i_Pos.z = i_z; }
	void incPos(float i_x, float i_y, float i_z) { i_Pos.x += i_x; i_Pos.y += i_y; i_Pos.z += i_z; }
	QpoVec3d getPos(void) { return i_Pos; }

	void acPrintLocation(void) { printf("Point x %f y %f z %f\n", i_Pos.x, i_Pos.y, i_Pos.z); }
	void acRender(void)
		{
#if 0 // QAGE_DESKTOP
		glColor3f(0.05f, 1.0f, 0.05f);
		//*glBegin(GL_LINES);

			glVertex3f(i_Pos.x, i_Pos.y, i_Pos.z);
			glVertex3f(i_Pos.x + 10, i_Pos.y, i_Pos.z);

			glVertex3f(i_Pos.x, i_Pos.y, i_Pos.z);
			glVertex3f(i_Pos.x, i_Pos.y + 10, i_Pos.z);

			glVertex3f(i_Pos.x, i_Pos.y, i_Pos.z);
			glVertex3f(i_Pos.x, i_Pos.y, i_Pos.z + 10);

			glVertex3f(i_Pos.x, i_Pos.y, i_Pos.z);
			glVertex3f(i_Pos.x - 10, i_Pos.y, i_Pos.z);

			glVertex3f(i_Pos.x, i_Pos.y, i_Pos.z);
			glVertex3f(i_Pos.x, i_Pos.y - 10, i_Pos.z);

			glVertex3f(i_Pos.x, i_Pos.y, i_Pos.z);
			glVertex3f(i_Pos.x, i_Pos.y, i_Pos.z - 10);

		//*glEnd();
#endif
		}

	QpoVec3d i_Pos;
};

#endif