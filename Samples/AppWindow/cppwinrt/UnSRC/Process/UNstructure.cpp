/*

    UNstructure - Physical Structures
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. 
	the original author retain the rights to use, modify, and/or relicense this
	code without notice.

*/

#include "UNstructure.h"
#include "SDL.h"

//#include <gl/glew.h>
#include <gl/gl.h>					// Header File For The OpenGL32 Library
#include <gl/glu.h>					// Header File For The GLu32 Library

using namespace UN;

namespace UN
{

char app_path[256];

unStructureBank::unStructureBank(HWND hWnd)
{
#if 0
	char *c,*cmdline=GetCommandLine();
	if (cmdline[0]=='"') 
		{
		cmdline++;
		c=strchr(cmdline,'"');
		if (c) *c=0;
		}
	else
		{
		c=strchr(cmdline,' ');
		if (c) *c=0;
		}

	strcpy(app_path,cmdline);
	c=strrchr(app_path,'\\');
	if (c) *(c+1)=0;

	/////// Render Initialization ///////
	render_init(app_path,"unRenderer.ini",hWnd,0);
	if (g_render->load_font("data\\fonts.tga")!=-1) g_render->sel_font(0);

	/////// Create Buffer Rendering Context ///////
	set_program_params(false, true);
	create_buffer(RESULTS_WINDOW_WIDTH, RESULTS_WINDOW_HEIGHT);
#endif

	m_PinCount = 0;
}

void unStructureBank::create_buffer(int sx,int sy)
{
	gl_buffers[0]=GL_FRONT_LEFT;

#if 0
	gl_buffers[1]=GL_AUX0;
	gl_buffers[2]=GL_AUX1;
	gl_buffers[3]=GL_AUX2;
#endif
	
    wgl_buffers[0]=WGL_FRONT_LEFT_ARB;

#if 0
    wgl_buffers[1]=WGL_AUX0_ARB;
    wgl_buffers[2]=WGL_AUX1_ARB;
	wgl_buffers[3]=m_nv_render_depth_texture?WGL_DEPTH_COMPONENT_NV:WGL_AUX2_ARB;
#endif

	m_sizex=sx;
	m_sizey=sy;

	m_pbuffer=new pPBuffer(m_sizex, m_sizey, 32, true, true, false, true, true, false, false, true, 1);

	glGenTextures(1,m_tex);

	glBindTexture(GL_TEXTURE_2D,m_tex[0]);
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_sizex, m_sizey, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D,0);

	buffer_bind_render();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	buffer_unbind_render();
}

void unStructureBank::destroy_buffer()
{
	glDeleteTextures(1,m_tex);
	m_tex[0]=0;

	delete m_pbuffer;
	m_pbuffer=0;
}

void unStructureBank::set_program_params(bool depth_bias,bool nv_render_depth_texture)
{
	m_depth_bias=depth_bias;
	m_nv_render_depth_texture=(nv_render_depth_texture&&WGLEW_NV_render_depth_texture);
}

void unStructureBank::buffer_bind_texture(int target)
{
	if (m_pbuffer)
		{
		if (target>=0)
			{
			glActiveTextureARB(GL_TEXTURE0_ARB);
			glBindTexture(GL_TEXTURE_2D,m_tex[target]);
			m_pbuffer->BindAsTexture(wgl_buffers[target]);
			glEnable(GL_TEXTURE_2D);
			}
		else
			{
			glActiveTextureARB(GL_TEXTURE3_ARB);
			glBindTexture(GL_TEXTURE_2D,m_tex[0]);
			m_pbuffer->BindAsTexture(wgl_buffers[0]);
			}
		}
}

void unStructureBank::buffer_unbind_texture(int target)
{
	if (m_pbuffer)
		{
		if (target>=0)
			{
			glActiveTextureARB(GL_TEXTURE0_ARB);
			m_pbuffer->ReleaseTexture(wgl_buffers[target]);
			glBindTexture(GL_TEXTURE_2D,0);
			glDisable(GL_TEXTURE_2D);
			}
		else
			{
			glActiveTextureARB(GL_TEXTURE3_ARB);
			m_pbuffer->ReleaseTexture(wgl_buffers[0]);
			glBindTexture(GL_TEXTURE_2D,0);
			}
		}
}

void unStructureBank::free_programs()
{
	if (m_vert_prog)
		cgDestroyProgram(m_vert_prog);
	m_vert_prog=0;

	if (m_vert_mesh)
		cgDestroyProgram(m_vert_mesh);
	m_vert_mesh=0;

	if (m_frag_prog_normal)
		cgDestroyProgram(m_frag_prog_normal);
	m_frag_prog_normal=0;

	if (m_frag_mesh)
		cgDestroyProgram(m_frag_mesh);
	m_frag_mesh=0;

	if (m_frag_prog_relief)
		cgDestroyProgram(m_frag_prog_relief);
	m_frag_prog_relief=0;

	if (m_frag_prog_light)
		cgDestroyProgram(m_frag_prog_light);
	m_frag_prog_light=0;

	if (m_frag_prog_antialias)
		cgDestroyProgram(m_frag_prog_antialias);
	m_frag_prog_antialias=0;
}

void unStructureBank::checkError(const char *name, const char *situation)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);
  
	if (error != CG_NO_ERROR)
		{
		if (error == CG_COMPILER_ERROR)
			{
			std::string errorstr;
			errorstr += cgGetLastListing(g_render->cgcontext);
#if 0
			MessageBox (0, errorstr.c_str(), "CG Compile ERROR", MB_OK);
#endif
			printf("CG:::Compile Error:::%s:::%s:::\n %s\n", name, situation, errorstr.c_str());
			for(;;) {};
			}
		else
			{
#if 0
			MessageBox (0, "General Fault", "CG ERROR", MB_OK);
#endif
			printf("CG:::General Execution Error\n");
			}
		}
}

GLuint unStructureBank::CreateEmptyTexture(int i_x, int i_y)
{
	GLuint txtnumber;											// Texture ID
	unsigned int* data;											// Stored Data

	// Create Storage Space For Texture Data (128x128x4)
	data = (unsigned int*)new GLuint[((i_x * i_y)* 4 * sizeof(unsigned int))];
	ZeroMemory(data,((i_x * i_y)* 4 * sizeof(unsigned int)));	// Clear Storage Memory

	glGenTextures(1, &txtnumber);								// Create 1 Texture
	glBindTexture(GL_TEXTURE_2D, txtnumber);					// Bind The Texture
	glTexImage2D(GL_TEXTURE_2D, 0, 4, i_x, i_y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete [] data;												// Release data

	return txtnumber;											// Return The Texture ID
}

unPinSheet::unPinSheet(int i_Width, int i_Height, int i_GridWidth, int i_GridHeight)
{
	m_Width = i_Width;
	m_Height = i_Height;
	m_GridWidth = i_GridWidth;
	m_GridHeight = i_GridHeight;

	for(unsigned int i_Y0 = 0; i_Y0 < m_Height; i_Y0 += i_GridHeight)
		{
		for(unsigned int i_X0 = 0; i_X0 < m_Width; i_X0 += i_GridWidth)
			{
			std::vector<unVertex2> i_Vector;
			i_Vector.clear();

			m_RedVerts.push_back(i_Vector);
			m_GreenVerts.push_back(i_Vector);
			m_BlueVerts.push_back(i_Vector);
			}
		}
};

int unStructureBank::acGenerateStructures(int i_StartX, int i_StartY)
{
	float i_Dist = 0;
	float i_DistStr = 0;
	bool i_Flow = false;
	int i_VertStr = -1;
	int i_Pnr = 0;
	int i_VecCount = 0;
	unStructure* i_Structure;
	m_Structure.clear();

	int i_PinIdx = m_PinCount;
	if(i_PinIdx >= m_PinSheet.size()) i_PinIdx = m_PinSheet.size() - 1;

	//printf("trace\n");

	for(int i_Y0 = i_StartY; i_Y0 < m_PinSheet[i_PinIdx]->m_Height; i_Y0 += m_PinSheet[i_PinIdx]->m_GridHeight)
		{
		//printf("tracey\n");
		for(int i_X0 = i_StartX; i_X0 < m_PinSheet[i_PinIdx]->m_Width; i_X0 += m_PinSheet[i_PinIdx]->m_GridWidth)
			{
			//printf("tracex\n");
			i_Structure = new unStructure();

			for(int i_X1 = i_X0; i_X1 < i_X0 + m_PinSheet[i_PinIdx]->m_GridWidth; i_X1++)
				{
				//printf("tracex1 %i \n", m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size());
				for(int i_Cnt = 0; i_Cnt < m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size(); i_Cnt++)
					{
					//printf("tracecnt\n");
					i_Dist = m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount][i_Cnt].acDist(unVertex2(i_X1, i_Y0));

					if(i_Flow)
						{
						if(i_Dist < i_DistStr)
							{
							i_Pnr = i_Cnt;
							i_DistStr = i_Dist;
							}
						}
					else
						{
						i_Pnr = i_Cnt;
						i_DistStr = i_Dist;
						i_Flow = true;
						}
					}

				if(i_Pnr != i_VertStr && m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size() > 0)
					{
					i_Structure->m_PinVerts.push_back(m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount][i_Pnr]);
					i_Structure->m_PinVertsIdx.push_back(i_Pnr);
					}

				i_VertStr = i_Pnr;
				}

			i_Dist = 0;
			i_DistStr = 0;
			i_Flow = false;
			i_VertStr = -1;

			for(int i_Y1 = i_Y0; i_Y1 < i_Y0 + m_PinSheet[i_PinIdx]->m_GridHeight; i_Y1++)
				{
				//printf("tracey1 %i \n", m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size());
				for(int i_Cnt = 0; i_Cnt < m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size(); i_Cnt++)
					{
					i_Dist = m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount][i_Cnt].acDist(unVertex2((i_X0 + m_PinSheet[i_PinIdx]->m_GridWidth) - 1, i_Y1));

					if(i_Flow)
						{
						if(i_Dist < i_DistStr)
							{
							i_Pnr = i_Cnt;
							i_DistStr = i_Dist;
							}
						}
					else
						{
						i_Pnr = i_Cnt;
						i_DistStr = i_Dist;
						i_Flow = true;
						}
					}

				if(i_Pnr != i_VertStr && m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size() > 0)
					{
					i_Structure->m_PinVerts.push_back(m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount][i_Pnr]);
					i_Structure->m_PinVertsIdx.push_back(i_Pnr);
					}

				i_VertStr = i_Pnr;
				}

			i_Dist = 0;
			i_DistStr = 0;
			i_Flow = false;
			i_VertStr = -1;

			for(int i_X1 = (i_X0 + m_PinSheet[i_PinIdx]->m_GridWidth) - 1; i_X1 >= i_X0; i_X1--)
				{
				//printf("tracex3 i_X1 %i >= i_X0 %i \n", i_X1, i_X0);
				//Sleep(5);
				for(int i_Cnt = 0; i_Cnt < m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size(); i_Cnt++)
					{
					i_Dist = m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount][i_Cnt].acDist(unVertex2(i_X1, (i_Y0 + m_PinSheet[i_PinIdx]->m_GridHeight) - 1));

					if(i_Flow)
						{
						if(i_Dist < i_DistStr)
							{
							i_Pnr = i_Cnt;
							i_DistStr = i_Dist;
							}
						}
					else
						{
						i_Pnr = i_Cnt;
						i_DistStr = i_Dist;
						i_Flow = true;
						}
					}

				if(i_Pnr != i_VertStr && m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size() > 0)
					{
					i_Structure->m_PinVerts.push_back(m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount][i_Pnr]);
					i_Structure->m_PinVertsIdx.push_back(i_Pnr);
					}

				i_VertStr = i_Pnr;
				}

			i_Dist = 0;
			i_DistStr = 0;
			i_Flow = false;
			i_VertStr = -1;

			for(int i_Y1 = (i_Y0 + m_PinSheet[i_PinIdx]->m_GridHeight) - 1; i_Y1 >= i_Y0; i_Y1--)
				{
				//printf("tracex4 %i \n", m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size());
				for(int i_Cnt = 0; i_Cnt < m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size(); i_Cnt++)
					{
					i_Dist = m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount][i_Cnt].acDist(unVertex2(i_X0, i_Y1));

					if(i_Flow)
						{
						if(i_Dist < i_DistStr)
							{
							i_Pnr = i_Cnt;
							i_DistStr = i_Dist;
							}
						}
					else
						{
						i_Pnr = i_Cnt;
						i_DistStr = i_Dist;
						i_Flow = true;
						}
					}

				if(i_Pnr != i_VertStr && m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount].size() > 0)
					{
					i_Structure->m_PinVerts.push_back(m_PinSheet[i_PinIdx]->m_GreenVerts[i_VecCount][i_Pnr]);
					i_Structure->m_PinVertsIdx.push_back(i_Pnr);
					}

				i_VertStr = i_Pnr;
				}

			i_Structure->m_PinIdx = i_PinIdx;
			i_Structure->m_PinSheet = m_PinSheet[i_PinIdx];

			m_Structure.push_back(i_Structure);

			//printf("trace m_Structure.size() %i\n", m_Structure.size());
			//Sleep(500);

			i_VecCount++;
			}
		}

	m_PinCount++;

	return m_Structure.size();
}

bool unStructureBank::acAnalyse(unsigned int* i_Screen, unsigned int i_Pitch)
{
	// Layer 0 A_Variables
	unsigned int i_sourcer[EQAL_LAY1_XSKIPFACTOR][EQAL_LAY1_XSKIPFACTOR];
	unsigned int i_sourceg[EQAL_LAY1_XSKIPFACTOR][EQAL_LAY1_XSKIPFACTOR];
	unsigned int i_sourceb[EQAL_LAY1_XSKIPFACTOR][EQAL_LAY1_XSKIPFACTOR];
	int i_Point;
	int i_VecCount = 0;

	unPinSheet* i_PinSheet = new unPinSheet(RESULTS_WINDOW_WIDTH, RESULTS_WINDOW_HEIGHT, EQAL_LAY0_XSKIPFACTOR, EQAL_LAY0_YSKIPFACTOR);
	m_PinSheet.push_back(i_PinSheet);

	/////// Layer 0
	for(int i_Y0 = 0; i_Y0 < RESULTS_WINDOW_HEIGHT; i_Y0 += EQAL_LAY0_YSKIPFACTOR)
		{
		for(int i_X0 = 0; i_X0 < RESULTS_WINDOW_WIDTH; i_X0 += EQAL_LAY0_XSKIPFACTOR)
			{
			/////// Layer 1
			for(int i_Y1 = 0; i_Y1 < ((i_Y0 + EQAL_LAY0_YSKIPFACTOR) - EQAL_LAY1_YSKIPFACTOR); i_Y1 += EQAL_LAY1_YSKIPFACTOR)
				{
				for(int i_X1 = 0; i_X1 < ((i_X0 + EQAL_LAY0_XSKIPFACTOR) - EQAL_LAY1_XSKIPFACTOR); i_X1 += EQAL_LAY1_XSKIPFACTOR)
					{
					i_Point = (i_Y0 + i_Y1) * (i_Pitch) + (i_X0 + i_X1);
					if(i_Point >= RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT) return true;
					i_sourcer[0][0] = ((i_Screen)[i_Point] >> 0) & 0xff;
					i_sourceg[0][0] = ((i_Screen)[i_Point] >> 8) & 0xff;
					i_sourceb[0][0] = ((i_Screen)[i_Point] >> 16) & 0xff;

					i_Point = (i_Y0 + i_Y1) * (i_Pitch) + (i_X0 + (i_X1 + 1));
					if(i_Point >= RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT) return true;
					i_sourcer[0][1] = ((i_Screen)[i_Point] >> 0) & 0xff;
					i_sourceg[0][1] = ((i_Screen)[i_Point] >> 8) & 0xff;
					i_sourceb[0][1] = ((i_Screen)[i_Point] >> 16) & 0xff;

					i_Point = (i_Y0 + i_Y1) * (i_Pitch) + (i_X0 + (i_X1 + 2));
					if(i_Point >= RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT) return true;
					i_sourcer[0][2] = ((i_Screen)[i_Point] >> 0) & 0xff;
					i_sourceg[0][2] = ((i_Screen)[i_Point] >> 8) & 0xff;
					i_sourceb[0][2] = ((i_Screen)[i_Point] >> 16) & 0xff;

					i_Point = (i_Y0 + (i_Y1 + 1)) * (i_Pitch) + (i_X0 + i_X1);
					if(i_Point >= RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT) return true;
					i_sourcer[1][0] = ((i_Screen)[i_Point] >> 0) & 0xff;
					i_sourceg[1][0] = ((i_Screen)[i_Point] >> 8) & 0xff;
					i_sourceb[1][0] = ((i_Screen)[i_Point] >> 16) & 0xff;

					i_Point = (i_Y0 + (i_Y1 + 1)) * (i_Pitch) + (i_X0 + (i_X1 + 1));
					if(i_Point >= RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT) return true;
					i_sourcer[1][1] = ((i_Screen)[i_Point] >> 0) & 0xff;
					i_sourceg[1][1] = ((i_Screen)[i_Point] >> 8) & 0xff;
					i_sourceb[1][1] = ((i_Screen)[i_Point] >> 16) & 0xff;

					i_Point = (i_Y0 + (i_Y1 + 1)) * (i_Pitch) + (i_X0 + (i_X1 + 2));
					if(i_Point >= RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT) return true;
					i_sourcer[1][2] = ((i_Screen)[i_Point] >> 0) & 0xff;
					i_sourceg[1][2] = ((i_Screen)[i_Point] >> 8) & 0xff;
					i_sourceb[1][2] = ((i_Screen)[i_Point] >> 16) & 0xff;

					i_Point = (i_Y0 + (i_Y1 + 2)) * (i_Pitch) + (i_X0 + i_X1);
					if(i_Point >= RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT) return true;
					i_sourcer[2][0] = ((i_Screen)[i_Point] >> 0) & 0xff;
					i_sourceg[2][0] = ((i_Screen)[i_Point] >> 8) & 0xff;
					i_sourceb[2][0] = ((i_Screen)[i_Point] >> 16) & 0xff;

					i_Point = (i_Y0 + (i_Y1 + 2)) * (i_Pitch) + (i_X0 + (i_X1 + 1));
					if(i_Point >= RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT) return true;
					i_sourcer[2][1] = ((i_Screen)[i_Point] >> 0) & 0xff;
					i_sourceg[2][1] = ((i_Screen)[i_Point] >> 8) & 0xff;
					i_sourceb[2][1] = ((i_Screen)[i_Point] >> 16) & 0xff;

					i_Point = (i_Y0 + (i_Y1 + 2)) * (i_Pitch) + (i_X0 + (i_X1 + 2));
					if(i_Point >= RESULTS_WINDOW_WIDTH * RESULTS_WINDOW_HEIGHT) return true;
					i_sourcer[2][2] = ((i_Screen)[i_Point] >> 0) & 0xff;
					i_sourceg[2][2] = ((i_Screen)[i_Point] >> 8) & 0xff;
					i_sourceb[2][2] = ((i_Screen)[i_Point] >> 16) & 0xff;

					unsigned int i_averager = 0;
					unsigned int i_averageg = 0;
					unsigned int i_averageb = 0;

					for(unsigned int i_CntY = 0; i_CntY < EQAL_LAY1_YSKIPFACTOR; i_CntY++)
						{
						for(unsigned int i_CntX = 0; i_CntX < EQAL_LAY1_YSKIPFACTOR; i_CntX++)
							{
							i_averager += i_sourcer[i_CntY][i_CntX];
							i_averageg += i_sourceg[i_CntY][i_CntX];
							i_averageb += i_sourceb[i_CntY][i_CntX];
							}
						}

					i_averager /= EQAL_LAY1_XSKIPFACTOR * EQAL_LAY1_YSKIPFACTOR;
					i_averageg /= EQAL_LAY1_XSKIPFACTOR * EQAL_LAY1_YSKIPFACTOR;
					i_averageb /= EQAL_LAY1_XSKIPFACTOR * EQAL_LAY1_YSKIPFACTOR;

					/////// Generate 2d vector points in three catagories ///////
					if(i_averager > EQAL_2DTHRESH_RED)
						{
						unVertex2 i_Vertex((i_X1 + 2), (i_Y1 + 2));

						i_PinSheet->m_RedVerts[i_VecCount].push_back(i_Vertex);
						}

					if(i_averager > EQAL_2DTHRESH_GREEN)
						{
						unVertex2 i_Vertex((i_X1 + 2), (i_Y1 + 2));

						i_PinSheet->m_GreenVerts[i_VecCount].push_back(i_Vertex);
						}

					if(i_averager > EQAL_2DTHRESH_BLUE)
						{
						unVertex2 i_Vertex((i_X1 + 2), (i_Y1 + 2));

						i_PinSheet->m_BlueVerts[i_VecCount].push_back(i_Vertex);
						}
					}
				}

			i_VecCount++;
			}
		}
}

int unStructureBank::acResizeStructures(void)
{
	bool i_Flow = false;
	int i_MinX = 0;
	int i_MinY = 0;
	int i_MaxX = 0;
	int i_MaxY = 0;

	for(unsigned int i_StructureCount = 0; i_StructureCount < m_Structure.size(); i_StructureCount++)
		{
		for(unsigned int i_VertCount = 0; i_VertCount < m_Structure[i_StructureCount]->m_PinVerts.size(); i_VertCount++)
			{
			if(i_Flow)
				{
				if(m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_X < i_MinX) i_MinX = m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_X;
				if(m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_Y < i_MinY) i_MinY = m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_Y;
				if(m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_X > i_MaxX) i_MaxX = m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_X;
				if(m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_Y > i_MaxY) i_MaxY = m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_Y;
				}
			else
				{
				i_Flow = true;
				i_MinX = m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_X;
				i_MinY = m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_Y;
				i_MaxX = m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_X;
				i_MaxY = m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_Y;
				}
			}

		unVertex2* i_Vertex;

		for(unsigned int i_VertCount = 0; i_VertCount < m_Structure[i_StructureCount]->m_PinVerts.size(); i_VertCount++)
			{
			unVertex2 i_Vertex(m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_X - i_MinX, m_Structure[i_StructureCount]->m_PinVerts[i_VertCount].m_Y - i_MinY);
			m_Structure[i_StructureCount]->m_Verts.push_back(i_Vertex);
			}

		m_Structure[i_StructureCount]->m_Width = i_MaxX - i_MinX;
		m_Structure[i_StructureCount]->m_Height = i_MaxY - i_MinY;
		}

	return m_Structure.size();
}

int unStructureBank::acGenerateTemplates(void)
{
	for(unsigned int i_Count = 0; i_Count < m_Structure.size(); i_Count++)
		{
		acPrintStructure(i_Count);
		}

	return m_Template.size();
}

unTemplate::unTemplate(int i_Width, int i_Height)
{
	m_Width = i_Width;
	m_Height = i_Height;

	glGenTextures(1, &m_Texture);
	m_Buffer = new unsigned int[m_Width * m_Height];

#if 0
	acClear();
#endif
}

void unTemplate::acClear(void)
{
	for(unsigned int i_Count = 0; i_Count < (m_Width * m_Height); i_Count++)
		{
		m_Buffer[i_Count] = 0;
		}
}

void unStructureBank::acPrintStructure(int i_StructureCount)
{
	unTemplate* i_Template;

	i_Template = new unTemplate(m_Structure[i_StructureCount]->m_Width, m_Structure[i_StructureCount]->m_Height);
	i_Template->m_Structure = m_Structure[i_StructureCount];
	m_Template.push_back(i_Template);

	buffer_bind_render();	// bind diffuse mrt texture

#if 1
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#endif

	int vPort[4];

	glGetIntegerv(GL_VIEWPORT, vPort);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	for(unsigned int i_VertCount = 1; i_VertCount < m_Structure[i_StructureCount]->m_Verts.size(); i_VertCount++)
		{
		glColor4f(1,0,0,1);
		glBegin(GL_LINES);
			glVertex2i(m_Structure[i_StructureCount]->m_Verts[i_VertCount - 1].m_X, m_Structure[i_StructureCount]->m_Verts[i_VertCount - 1].m_Y);
			glVertex2i(m_Structure[i_StructureCount]->m_Verts[i_VertCount].m_X, m_Structure[i_StructureCount]->m_Verts[i_VertCount].m_Y);
		glEnd();
		}

#if 0
	for(int lineiter = 0; lineiter < m_DocumentBank->getDocument(0)->m_Content.size(); ++lineiter)
	{ commands_face->draw( 0, m_sizey - (lineiter * point_size), m_DocumentBank->getDocument(0)->m_Content[lineiter].c_str() ); }
#endif

	glBindTexture(GL_TEXTURE_2D, i_Template->m_Texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, i_Template->m_Width, i_Template->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, i_Template->m_Width, i_Template->m_Height, 0);

#if 0
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, GUI_DEFAULT_EDITDX, GUI_DEFAULT_EDITDY);
#endif

	glReadPixels(0, 0, i_Template->m_Width, i_Template->m_Height, GL_COLOR, GL_UNSIGNED_INT, i_Template->m_Buffer);

	buffer_unbind_render();

#if 0
	if(GUI_MIPMAP)
		{
#if 0
		gluBuild2DMipmaps(GL_TEXTURE_2D, picture->bytespixel, picture->sx, picture->sy, GL_RGBA, GL_UNSIGNED_BYTE, picture->buf);
		glTexParameteri(type,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_NEAREST);
#endif
		}
	else
		{	//No MipMap Texture
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		}
#endif
}

void unStructureBank::buffer_bind_render()
{
	if (m_pbuffer)
		{
		m_pbuffer->Bind();
		glDrawBuffersATI(1, gl_buffers);
		}
}

void unStructureBank::buffer_unbind_render()
{
	if (m_pbuffer) m_pbuffer->Unbind();
}

};