#include "pch.h"
#include "paralelo3d.h"

P3D_API pRender *g_render=0;
#ifdef P_MANAGER_OBJ
P3D_API pRenderObjectManager *g_romanager=0;
#endif
#ifdef P_MANAGER_GUI
P3D_API pGUIObjectManager *g_gomanager=0;
#endif

P3D_API pRender *get_render() 
{
	return g_render;
}

P3D_API void render_init(const char *app_path,const char *inifilename,HWND hwnd,int fullscreen,int norender)
{
	render_free();
	g_render=new pRender(app_path, inifilename);

	g_render->pre_create(hwnd);

	if(norender!=-1)
		g_render->norender=norender;

	g_render->fullscreen=fullscreen;
	g_render->create();

#ifdef P_MANAGER_OBJ
	g_romanager=new pRenderObjectManager();
#endif
#ifdef P_MANAGER_GUI
	g_gomanager=new pGUIObjectManager();
#endif

	//*g_render->rg_enabled = 1;
	//*g_render->rr_enabled = 1;
	g_render->shadowflag = 1;

#ifndef P_DISABLE_3D
	if (g_render->norender==0)
	{
		if(g_render->rg_enabled && pRenderGlow::test())
			g_render->rg.init(15);
		if(g_render->rr_enabled && pRenderRipple::test())
			g_render->rr.init(g_render->rr.m_size,g_render->rr.m_fragment+1);
		bool shadow_map_test=pRenderShadowMap::test(); // it must stay here
		if(g_render->shadowflag && shadow_map_test)
			g_render->rs.init(g_render->rs.m_size);
		if (g_render->load_cubemap_tex(g_render->cube_map_tex_name)==false && g_render->cube_map_tex)
		{
			glDeleteTextures(1,&g_render->cube_map_tex);
			g_render->cube_map_tex=0;
		}
		if (g_render->load_spheremap_tex(g_render->sph_map_tex_name)==false && g_render->sph_map_tex)
		{
			glDeleteTextures(1,&g_render->sph_map_tex);
			g_render->sph_map_tex=0;
		}
	}
#endif

	// LOG
	g_render->logreport.create_logfile(app_path);
}

P3D_API void render_free()
{
#ifdef P_MANAGER_GUI
	delete g_gomanager;
	g_gomanager=0;
#endif
#ifdef P_MANAGER_OBJ
	delete g_romanager;
	g_romanager=0;
#endif
	delete g_render;
	g_render=0;
}

P3D_API char *LoadTextFile(const char *file)
{
	pFile fp;
	if (fp.open(file)==false)
		return 0;
	
	char *buf=new char[fp.len+1];
	fp.read(buf,fp.len);
	buf[fp.len]=0;
	
	fp.close();

	return buf;
}

#if 0 // P_SUPPORT_CG
int CgCheckError(void)
{
	CGerror err = cgGetError();
	if (err != CG_NO_ERROR)
	{
		char str[515];
		sprintf(str,"%s\n",cgGetErrorString(err));
		OutputDebugString(str);
		return 1;
	}
	return 0;
}
#endif

pRender::pRender(const char *path,const char *inifilename)
{
	hwnd=0;
	hdc=0;
	hrc=0;
	winmenu=0;
	debug=0;
	norender=0;
	app_path=path;
	sizex=0;
	sizey=0;
#ifndef P_DISABLE_3D
	rg_enabled=1;
	rr_enabled=1;
	mb_enabled=1;
	ac_enabled=1;
	ac_factor=0.6f;
	cube_map_tex=0;
	sph_map_tex=0;
	env_map_mode=P_ENVMODE_NONE;
#endif
	aspect=1.0f;
	nearplane=1.0f;
	farplane=10000.0;
	hugeplane=10000.0;
	hugeplaneflag=true;
	alphatestval=0.5f;
	colorbits=0;
	depthbits=0;
	stencilbits=0;
	accumbits=0;
	cur_font=0;
	cursorx=cursory=0;;
	target_pos.vec(0);
	target_moving=0;
	bgclear=1;
	bgcolor.vec(0,0,0,1);
	lightambient.vec(0.2f,0.2f,0.2f,1.0f);
	texfilter=1;
	texmipmap=1;
	fog=0;
	curdraw=0;
	curfps=0;
	drawfps=1;
	texdetail=0;
	loddetail=0;
	rendermode=0;
	renderflag=0;
	maxtex2dsize=0;
	maxtex3dsize=0;
	maxlights=0;
	maxoctreedepth=5;
	maxtextureunits=1;
	texload=1;
	texresize=1;
	selvideomode=-1;
	fullscreen=0;
	starttime=0;
	curtime=0;
	curtimef=0.0f;
	curdt=0;
	curdtf=0;
	cur_profile=0;
	sel_profile=-1;
	camkeys="SXQEAD";
	camctrl[0]=new pCameraCtrlObs();
	camctrl[1]=new pCameraCtrlOrbit();
	selcamctrl=0;
	vertbuffer=1;
	const_blink_color.vec(0.0f,0.0f,0.0f,0.0f);
	shader_path="";
	camerafov=0;

	shadowflag=1;
	svtype=0;
	logflag=0;

	tooltip_delay=1.0f;
	tooltip_bgcolor.vec(1.0f,1.0f,1.0f,1.0f);
	tooltip_textcolor.vec(0.0f,0.0f,0.0f,1.0f);
	tooltip_tex=-1;
	tooltip_font=-1;
	tooltip_fontsize=16;
	tooltip_border=2;
	info = false;
	infoedit = false;
	framememory = false;
	
	load_ini(inifilename);
#if 0 // P_SUPPORT_CG
	cgcontext=0;
#endif
	norender=0;

	//*timeBeginPeriod(1);
}

pRender::~pRender()
{
	//*timeEndPeriod(1);

#ifndef P_DISABLE_3D
	rg.reset();
	rr.reset();
	rs.reset();
	if (cube_map_tex)
	{
		glDeleteTextures(1,&cube_map_tex);
		cube_map_tex=0;
	}
	if (sph_map_tex)
	{
		glDeleteTextures(1,&sph_map_tex);
		sph_map_tex=0;
	}
#endif
	destroy();
	delete camctrl[0];
	//delete camctrl[1];
}

void pRender::pre_create(HWND hWnd)
{
#ifdef P_INIT_OGL
	DEVMODE	dm;
	hwnd=hWnd;
	winmenu=GetMenu(hwnd);

	hdc=GetDC(hwnd);
	colorbits=GetDeviceCaps(hdc,BITSPIXEL);
	ReleaseDC(hwnd,hdc);
	if (colorbits==24)
		colorbits=32;

	int i,j;
	i=0;
	while(EnumDisplaySettings(NULL,i,&dm))
	{
		if ((int)dm.dmBitsPerPel==colorbits)
			videomode.add(dm);
		i++;
	}
	j=-1;
	for( i=0;i<videomode.num;i++ )
		if (videomode[i].dmPelsWidth==(unsigned int)sizex &&
			videomode[i].dmPelsHeight==(unsigned int)sizey)
		{
			if ((int)videomode[i].dmDisplayFrequency>j && videomode[i].dmDisplayFrequency<=120)
			{
				j=videomode[i].dmDisplayFrequency;
				selvideomode=i;
			}
		}
#endif
}

int pRender::create(int menuflag)
{
#ifdef P_INIT_OGL
	if (norender==0)
	{
	int i,j;
	PIXELFORMATDESCRIPTOR pfd;
	hdc=GetDC(hwnd);
	
	sizex=videomode[selvideomode].dmPelsWidth;
	sizey=videomode[selvideomode].dmPelsHeight;
	if (fullscreen==1)
	{
		SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPED);
		if (menuflag) SetMenu(hwnd,0);
		SetWindowPos(hwnd,HWND_TOPMOST,0,0,sizex,sizey,SWP_SHOWWINDOW);
		ChangeDisplaySettings(&videomode[selvideomode],CDS_FULLSCREEN);
	}
	else
	if (fullscreen==0)
	{
		SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPEDWINDOW);
		if (menuflag) SetMenu(hwnd,winmenu);
		SetWindowPos(hwnd,HWND_TOP,0,0,sizex,sizey,SWP_SHOWWINDOW);
	}

	i=1;
	j=DescribePixelFormat(hdc,i,sizeof(PIXELFORMATDESCRIPTOR),&pfd);
	while(i<=j)
	{
		DescribePixelFormat(hdc,i,sizeof(PIXELFORMATDESCRIPTOR),&pfd);
		if (pfd.iPixelType==0 && pfd.cColorBits==colorbits && pfd.cStencilBits==8 && ((pfd.cAccumBits>=colorbits && ac_enabled)||ac_enabled==0) && (pfd.dwFlags==PFD_SUPPORT_OPENGL && PFD_DOUBLEBUFFER))
			//(pfd.dwFlags&PFD_DOUBLEBUFFER))
			
			//&& pfd.dwFlags&PFD_GENERIC_FORMAT)
			break;
		i++;
	}
	if (i>j)
	{
		i=1;
		j=DescribePixelFormat(hdc,i,sizeof(PIXELFORMATDESCRIPTOR),&pfd);
		while(i<=j)
		{
			DescribePixelFormat(hdc,i,sizeof(PIXELFORMATDESCRIPTOR),&pfd);
			if (pfd.iPixelType==0 && 
				pfd.cColorBits==colorbits &&
				(pfd.dwFlags&PFD_DOUBLEBUFFER))
				//&& pfd.dwFlags&PFD_GENERIC_FORMAT)
				break;
			i++;
		}
		if (i>j)
			return 0;
	}

	if (SetPixelFormat(hdc, i, &pfd) == false) 
		return 0;

	hrc = wglCreateContext( hdc );
	wglMakeCurrent( hdc, hrc );

	RECT rect;
	GetClientRect(hwnd,&rect);
	resize(rect.right-rect.left,rect.bottom-rect.top);
	}
#endif
#ifndef P_DISABLE_3D
	if (norender==0)
	{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
	glEnable(GL_POINT_SMOOTH);
	//glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	//glEnable(GL_LINE_SMOOTH);

	glGetIntegerv(GL_MAX_LIGHTS,&maxlights);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE,&maxtex2dsize);
	glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE_EXT,&maxtex3dsize);
	
	glGetIntegerv(GL_DEPTH_BITS,&depthbits);
	glGetIntegerv(GL_STENCIL_BITS,&stencilbits);
	glGetIntegerv(GL_ACCUM_RED_BITS,&accumbits);
	accumbits = accumbits*4;

	if(accumbits == 0)
		ac_enabled=0;
	else
	{
		glClearAccum(0,0,0,0);
		glClear(GL_ACCUM_BUFFER_BIT);
	}

	glewInit(); //IBM servers donot have glew
	if (GLEW_ARB_multitexture==0)
		maxtextureunits=1;
	else
		glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB,&maxtextureunits);

#if 0 // P_SUPPORT_CG
	cgcontext = cgCreateContext();
	CgCheckError();
#endif

	profile_build();
	}
#endif

	//*starttime=timeGetTime();
	starttime = 0;
	return 1;
}

void pRender::destroy()
{
#ifdef P_INIT_OGL
	if (fullscreen>0)
		ChangeDisplaySettings(NULL,NULL);
#endif
	reset();
	
	if (norender==0)
	{
	int i;
	for( i=0;i<profile.num;i++ )
		delete profile[i];
	profile.free();
	cur_profile=0;

#if 0 // P_SUPPORT_CG
	if (cgcontext)
		cgDestroyContext(cgcontext);
	cgcontext=0;
	CgCheckError();
#endif
#ifdef P_INIT_OGL
	if (hdc)
		ReleaseDC(hwnd,hdc);
	hdc=0;
	if (hrc)
		wglDeleteContext(hrc);
	hrc=0;
#endif
	}
}

void pRender::resize(int sx,int sy)
{
#ifdef P_INIT_OGL
	if (hrc==0)
		return;
#endif
	if (norender==0)
	{
#ifndef P_DISABLE_3D
    glViewport(0, 0, sx, sy);
#endif
	if (sy==0)
		aspect=1;
	else aspect=(float)sx/sy;
	sizex=sx;
	sizey=sy;
#ifndef P_DISABLE_3D
		if (ac_enabled && accumbits>=colorbits)
			ac_enabled=2;
#endif
	}
}

pMeshSkeleton *pRender::load_mesh_skeleton(const char *modelfile)
{
	int i,j;
	for( i=0;i<model.num;i++ )
		if ((model.buf[i]->flags&P_MESHFLAGS_SKELETON) && 
		       !_stricmp(modelfile,(const char *)model.buf[i]->name))
			break;

	pString str=app_path+modelfile;

	if (i<model.num)
	{
		if (norender==0)
		for( j=0;j<model.buf[i]->nmat;j++ )
			model.buf[i]->mat[j].load_textures(str);
		return (pMeshSkeleton *)model.buf[i];
	}

	pMeshSkeleton *m;
	m=new pMeshSkeleton;

	int vb=g_render->vertbuffer;
	g_render->vertbuffer=0;

	if (m->load_p3d(str,maxoctreedepth)==0)
	{
		delete m;
		return 0;
	}
	
	m->flags=P_MESHFLAGS_SKELETON;
	m->name=modelfile;

	i=str.find_reverse('.');
	if (i!=-1 && i==str.length()-4)
	{
		str.set_char(i,0);
		str+=".phy";
		m->load_phy(str);
		str.set_char(i,0);
		str+=".ani";
		m->load_ani_rest(str);
		if (m->check_data()==false)
		{
			delete m;
			return 0;
		}
	}

	if (norender==0)
	for( i=0;i<m->nmat;i++ )
		m->mat[i].load_textures(str);
	model.add(m);

	g_render->vertbuffer=vb;
	m->build();

	return m;
}

pMesh *pRender::load_mesh(const char *modelfile, float f_UVFactor)
{
	int i,j;
	for( i=0;i<model.num;i++ )
		if (0)
			break;

	pString str=app_path+modelfile;

	printf("pRender::load_mesh::PATH %s\n", str.getbuf());

	if (i<model.num)
	{
		if (norender==0)
		for( j=0;j<model.buf[i]->nmat;j++ )
			model.buf[i]->mat[j].load_textures(str);
		return model.buf[i];
	}

	pMesh *m;
	m=new pMesh;

	i=str.length();
	j=str.find_reverse('.');
	if (j!=i-4)
	{
		delete m;
		printf("pMesh:::Error MeshName\n");
		return 0;
	}
#ifdef P_SUPPORT_3DS
	if (_stricmp((((const char *)str)+j),".3ds")==0)
	{
		if (m->load_3ds(str,maxoctreedepth)==0)
		{
			delete m;
			return 0;
		}
	}
	else
#endif
	{
		if (m->load_p3d(str,f_UVFactor,maxoctreedepth)==0)
		{
			printf("pMesh:::Error load_p3d\n");
			delete m;
			return 0;
		}
	}
	m->name=modelfile;
	if (norender==0)
	for( i=0;i<m->nmat;i++ )
		m->mat[i].load_textures(str);
	model.add(m);

	printf("pMesh:::Mesh Loaded %s\n", str.getbuf());

	return m;
}

void pRender::reset()
{
	int i;
#ifdef P_MANAGER_OBJ
	if (g_romanager)
		g_romanager->reset();
#endif
#ifdef P_MANAGER_GUI
	if (g_gomanager)
		g_gomanager->reset();
#endif

#if 0
	if(model.num > 1)
		{
		for( i=0;i<model.num;i++ )
			delete model[i];
		}
	else
		{
		delete model[0];
		}
#endif

	model.free();

	light.free();

	for( i=0;i<pic.num;i++ )
		delete pic[i];

#ifndef P_DISABLE_3D
	glDeleteTextures(picid.num,picid.buf);
#endif

	picid.free();
	pic.free();

	cur_font=0;
	for( i=0;i<font.num;i++ )
		delete font.buf[i];
	font.free();

	blink_data.free();
	blink_data_out.free();
	const_blink_color.vec(0.0f,0.0f,0.0f,0.0f);
}

void pRender::init()
{
#ifdef P_INIT_OGL
	if (hrc==0)
		return;
#endif

#ifndef P_DISABLE_3D
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glColor4f(1,1,1,1);
	glClearColor(bgcolor.x,bgcolor.y,bgcolor.z,1);
	glClearDepth(1);
	glClearStencil(0);
	glClear(GL_DEPTH_BUFFER_BIT|(bgclear?GL_COLOR_BUFFER_BIT:0));

	glLineWidth(1);
	glPointSize(1);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glBlendFunc(GL_ONE,GL_ZERO);
	glEnable(GL_BLEND);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
	
	pVector v(0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,&v.x);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,&v.x);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glAlphaFunc(GL_GREATER,alphatestval);
	glDisable(GL_ALPHA_TEST);
	
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glFogi(GL_FOG_MODE,GL_LINEAR);
	glFogf(GL_FOG_START,g_render->farplane*0.5f);
	glFogf(GL_FOG_END,g_render->farplane);
#endif
}

void pRender::draw(pArray<pRenderObject *>& objects)
{
#ifndef P_DISABLE_3D
	int i;
	if(logflag&P_LOG_LAST_DRAWN_OBJ)
	{
		for( i=0;i<objects.num;i++ )
		{
			logreport.print_log(P_LOG_LAST_DRAWN_OBJ,"Last drawn object: %s \n",(const char *)(objects.buf[i]->m_name));
			glPushAttrib(GL_FOG_BIT|GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT);
			glPushMatrix();
			objects.buf[i]->draw();
			glPopMatrix();
			glPopAttrib();
		}
	}
	else
	{
		for( i=0;i<objects.num;i++ )
		{
			glPushAttrib(GL_FOG_BIT|GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT);
			glPushMatrix();
			objects.buf[i]->draw();
			glPopMatrix();
			glPopAttrib();
		}
	}
#endif
}

void pRender::clear()
{
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
}

void pRender::begin_draw()
{
#ifdef P_INIT_OGL
	if (hrc==0)
		return;
#endif

#ifndef P_DISABLE_3D
	if (rr_enabled && rr.m_ripplepb && rr.m_start_time>0)
		rr.m_ripplepb->Bind();
#endif

	init();
	
	float fov=(camerafov>0?camerafov:camera.fov);
	view.build(camera.pos,camera.X,camera.Y,camera.Z,fov/aspect,aspect,farplane);

	set_camera();
}

void pRender::end_draw()
{
#ifdef P_INIT_OGL
	if (hrc==0)
		return;

	/*ac_factor = 0.01;

	if (ac_enabled)
		{
		glAccum(GL_ACCUM, 1.0f-ac_factor);
		glAccum(GL_RETURN, 0.1f);
		
		//glClear(GL_ACCUM_BUFFER_BIT);
		glAccum(GL_ACCUM, ac_factor);
		ac_enabled=2;
		}*/

	//glReadBuffer(GL_BACK);
	//glDrawBuffer(GL_BACK);
	//glAccum(GL_RETURN, 0.2f);

	//glDrawBuffer(GL_BACK);
	//glReadBuffer(GL_BACK);
    //glAccum(GL_ACCUM, 0.5f);

	//glAccum(GL_LOAD, 1.0f-ac_factor);
	//glClear(GL_ACCUM_BUFFER_BIT);
	//glAccum(GL_ACCUM, 1.0f-ac_factor);

	glClearColor(0,1,1,1);
	glClearDepth(1);
	glDisable(GL_TEXTURE_2D);

	//SwapBuffers(hdc);

	//glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	//printf("Clear\n");

	//SwapBuffers(hdc);

	//glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
	//printf("Clear\n");

	SwapBuffers(hdc);

	/*glClearColor( 1, 0, 0, 1 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	ac_factor = 0.3;
	glAccum(GL_ACCUM, ac_factor);*/
#endif
}

void pRender::update_texflags()
{
#ifndef P_DISABLE_3D
	for( int i=0;i<picid.num;i++ )
	if (pic[i])
	{
		unsigned type=(pic[i]->flags&&P_PICFLAGS_TEX3D)?GL_TEXTURE_3D:GL_TEXTURE_2D;

		glBindTexture(type,picid[i]);
		
		if (texmipmap && (pic[i]->flags&P_MATFLAGS_NOMIPMAP)==0 && pic[i]->buf)
		{
			build_mipmaps(pic[i],type);
			glTexParameteri(type,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_NEAREST);
		}
		else
			glTexParameteri(type,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
		glTexParameteri(type,GL_TEXTURE_MAG_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
	}
#endif
}

void pRender::tex_add_reference(int tex)
{
	if (tex>=0 && pic.buf[tex])
	{
		pic.buf[tex]->refcount++;
		if (picid.buf[tex]==0)
		{
			unsigned int id;
			
			glGenTextures(1,&id);
			picid.buf[tex]=id;

			pPicture *p=pic.buf[tex];
			p->LoadPIC(app_path+p->name);
			p->CheckSize(texdetail);

			if (p->flags&P_PICFLAGS_TEX3D)
			{
				glBindTexture(GL_TEXTURE_3D,id);
				set_tex_params(p,GL_TEXTURE_3D,GL_TEXTURE_3D);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D,id);
				set_tex_params(p,GL_TEXTURE_2D,GL_TEXTURE_2D);
			}

			p->FreePicture();
		}
	}
}

void pRender::tex_remove_reference(int tex)
{
	if (tex>=0 && pic.buf[tex])
	{
		pic.buf[tex]->refcount--;
		if (pic.buf[tex]->refcount<=0)
		{
			pic.buf[tex]->refcount=0;
			if (picid.buf[tex])
			{
				glDeleteTextures(1,&picid.buf[tex]);
				picid.buf[tex]=0;
			}
		}
	}
}

int pRender::load_tex(const char *texfile,int flags,int load)
{
	if (texfile==0 || texfile[0]==0 || texfile[0]==' ')
		return -1;

	int i;
	for( i=0;i<pic.num;i++ )
		if (pic.buf[i])
		if (!_stricmp(texfile,(const char *)pic.buf[i]->name)
			&& pic.buf[i]->flags==flags)
		{
			if (picid.buf[i]>0)
				pic.buf[i]->refcount++;
			return i;
		}

	unsigned int id;
	pPicture *p=new pPicture;

	if (load)
	{
		id=p->LoadPIC(app_path+texfile);
		if (id==0)
		{
			delete p;
			return -1;
		}
		p->refcount=1;
	    p->CheckSize(texdetail);
	}
	else
		p->refcount=0;

	p->name=texfile;
	pic.add(p);

	p->flags=flags;

	if (load)
	{
#ifndef P_DISABLE_3D
		glGenTextures(1,&id);
		picid.add(id);
		if (p->flags&P_PICFLAGS_TEX3D)
		{
			glBindTexture(GL_TEXTURE_3D,id);
			set_tex_params(p,GL_TEXTURE_3D,GL_TEXTURE_3D);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D,id);
			set_tex_params(p,GL_TEXTURE_2D,GL_TEXTURE_2D);
		}
#else
		picid.add(0);
#endif
	}
	else
		picid.add(0);

	if (load)
		pic.buf[pic.num-1]->FreePicture();

	return picid.num-1;
}

void pRender::set_tex_params(pPicture *p,unsigned int type1,unsigned int type2)
{
#ifndef P_DISABLE_3D
	if (p==0)
		return;

	if (p->bytespixel==4)
	{
		if (p->sz==1)
			glTexImage2D(type2,0,GL_RGBA,p->sx,p->sy,0,GL_RGBA,GL_UNSIGNED_BYTE,p->buf);
		else
			glTexImage3DEXT(type2,0,GL_RGBA,p->sx,p->sy,p->sz,0,GL_RGBA,GL_UNSIGNED_BYTE,p->buf);
		if (texmipmap && (p->flags&P_MATFLAGS_NOMIPMAP)==0 && p->sz==1)
		{
			build_mipmaps(p,type2);
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_NEAREST);
		}
		else
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
		glTexParameteri(type1,GL_TEXTURE_MAG_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
	}
	else
	if (p->bytespixel==3)
	{
		if (p->sz==1)
			glTexImage2D(type2,0,GL_RGB,p->sx,p->sy,0,GL_RGB,GL_UNSIGNED_BYTE,p->buf);
		else
			glTexImage3DEXT(type2,0,GL_RGB,p->sx,p->sy,p->sz,0,GL_RGB,GL_UNSIGNED_BYTE,p->buf);
		if (texmipmap && (p->flags&P_MATFLAGS_NOMIPMAP)==0 && p->sz==1)
		{
			build_mipmaps(p,type2);
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_NEAREST);
		}
		else
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
		glTexParameteri(type1,GL_TEXTURE_MAG_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
	}
	else
	if (p->bytespixel==1)
	{
		if (p->sz==1)
			glTexImage2D(type2,0,1,p->sx,p->sy,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,p->buf);
		else
			glTexImage3DEXT(type2,0,1,p->sx,p->sy,p->sz,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,p->buf);
		if (texmipmap && (p->flags&P_MATFLAGS_NOMIPMAP)==0 && p->sz==1)
		{
			build_mipmaps(p,type2);
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR_MIPMAP_LINEAR:GL_NEAREST_MIPMAP_NEAREST);
		}
		else
			glTexParameteri(type1,GL_TEXTURE_MIN_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
		glTexParameteri(type1,GL_TEXTURE_MAG_FILTER,texfilter?GL_LINEAR:GL_NEAREST);
	}
#endif
}

void pRender::sel_tex(int tex)
{
#ifndef P_DISABLE_3D
	if (tex<0 || tex>=picid.num)
		glDisable(GL_TEXTURE_2D);
	else
	{
		glBindTexture(GL_TEXTURE_2D,picid.buf[tex]);
		glEnable(GL_TEXTURE_2D);
	}
#endif
}

void pRender::check_input()
{
	camctrl[0]->check_input();
}

void pRender::update_camera() 
{
	camctrl[0]->update();
}

void pRender::update()
{
	unsigned int time;
	/*do 
	{	
		//QueryPerformanceCounter(); // faster
		//*#ifdef WIN32
		//*	time=timeGetTime()-starttime;
		//*#else
		//*	time=SDL_GetTicks()-starttime;
		//*#endif
		curdt=time-curtime;
	} while(curdt<1);
	if (curdt>1000) 
		curdt=10;
	curdtf=curdt*0.001f;
	curtime=time;
	curtimef=curtime*0.001f;

	static int last_time=0;
	static int frame_count=0;
	frame_count++;
	if (time-last_time>500)
	{
		curfps=frame_count*1000/(time-last_time);
		frame_count=0;
		last_time=time;
	}

	// LOG
	if(logflag&P_LOG_RENDER_UPDATE)
		logreport.print_log(P_LOG_RENDER_UPDATE,"\npRender Update %f\n",curtimef);*/
}

void pRender::set_camera(bool envmapmode)
{
#ifndef P_DISABLE_3D
	float a=(float)sizex/sizey;
	float fov=(camerafov>0?camerafov:camera.fov);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov/a,a,nearplane,hugeplaneflag?30.0f*farplane:farplane);
	if (envmapmode==true)
		glMultMatrixf((float *)&camera.mat_t);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (envmapmode==false)
		glMultMatrixf((float *)&camera.mat_t);
	glTranslatef(-camera.pos.x,-camera.pos.y,-camera.pos.z);

	glGetFloatv(GL_MODELVIEW_MATRIX,view_matrix.mf);
	glGetFloatv(GL_PROJECTION_MATRIX,proj_matrix.mf);
	glGetDoublev(GL_MODELVIEW_MATRIX,cam_model_mat);
	glGetDoublev(GL_PROJECTION_MATRIX,cam_proj_mat);

	cam_viewport[0]=0;
	cam_viewport[1]=0;
	cam_viewport[2]=sizex;
	cam_viewport[3]=sizey;
#endif
#ifdef P_SOUND
	g_soundmanager->set_listener(camera.pos,-camera.mat.get_column3(2),camera.mat.get_column3(1));
#endif
}

void pRender::set_camera_mesh(bool envmapmode)
{
#ifndef P_DISABLE_3D
	float a=(float)sizex/sizey;
	float fov=(camerafov>0?camerafov:camera.fov);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov/a,a,nearplane,hugeplaneflag?30.0f*farplane:farplane);
	//if (envmapmode==true)
	//	glMultMatrixf((float *)&camera.mat_t);
	
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//if (envmapmode==false)
	//	glMultMatrixf((float *)&camera.mat_t);
	//glTranslatef(-camera.pos.x,-camera.pos.y,-camera.pos.z);

	glGetFloatv(GL_MODELVIEW_MATRIX,view_matrix.mf);
	glGetFloatv(GL_PROJECTION_MATRIX,proj_matrix.mf);
	glGetDoublev(GL_MODELVIEW_MATRIX,cam_model_mat);
	glGetDoublev(GL_PROJECTION_MATRIX,cam_proj_mat);

	cam_viewport[0]=0;
	cam_viewport[1]=0;
	cam_viewport[2]=sizex;
	cam_viewport[3]=sizey;
#endif
#ifdef P_SOUND
	g_soundmanager->set_listener(camera.pos,-camera.mat.get_column3(2),camera.mat.get_column3(1));
#endif
}

void pRender::get_ray(float x,float y,pVector& ray)
{
#ifndef P_DISABLE_3D
	double Px,Py,Pz;
	gluUnProject(x,y,0.01,cam_model_mat,cam_proj_mat,cam_viewport, &Px,&Py,&Pz);
	ray.vec((float)Px-camera.pos.x,(float)Py-camera.pos.y,(float)Pz-camera.pos.z);
	ray.normalize();
#endif
}

void pRender::set_draw2d()
{
#ifdef P_INIT_OGL
	if (hrc==0)
		return;
#endif

#ifndef P_DISABLE_3D
	rr_enabled = 1;
	rr.m_start_time = 5;
	if (rr_enabled && rr.m_ripplepb && rr.m_start_time>0)
		rr.m_ripplepb->Unbind();

	rg_enabled = 1;
	if (rg_enabled && rg.m_tex)
		rg.generate_glow();

	// Accumulation blur
	//ac_factor = 0.01;
	//if (ac_enabled==2)
		//{
		//ac_enabled=1;
		//glClear(GL_ACCUM_BUFFER_BIT);
		//glAccum(GL_ACCUM, ac_factor);
		//}

	// sets 2d camera in screen coordinates
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,sizex,0,sizey,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,(float)sizey,0);
	glScalef(1,-1,1);

	// sets standard text state
	glDisable(GL_STENCIL_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glStencilMask(0);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_CULL_FACE);
	glColor4ub(255,255,255,255);
#endif
}

void pRender::draw_text(int x,int y,const char *text,int size,int n)
{
#ifdef P_INIT_OGL
	if (hrc==0)
		return;
#endif

#ifndef P_DISABLE_3D
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	const unsigned char *utext=(unsigned char *)text;
	if (cur_font==0 || cur_font->pic==-1)
		return;

	int len=(n==-1?strlen(text):n);
	sel_tex(cur_font->pic);
	
	cursorx=x;
	cursory=y;

	//*glBegin(GL_QUADS);
	float xx,yy;
	for( int i=0;i<len;i++ )
		if(utext[i]=='\n')
		{
			cursory+=size;
			y+=size;
			x=cursorx;
		}
		else
		{
			xx=(utext[i]%P_FONTS_NUM)*P_FONTS_FACTOR;
			yy=1.0f-(utext[i]/P_FONTS_NUM)*P_FONTS_FACTOR;

			glTexCoord2f(xx+P_FONTS_FACTOR,yy);
			glVertex2i(x+size,y);

			glTexCoord2f(xx+P_FONTS_FACTOR,yy-P_FONTS_FACTOR);
			glVertex2i(x+size,y+size);

			glTexCoord2f(xx,yy-P_FONTS_FACTOR);
			glVertex2i(x,y+size);

			glTexCoord2f(xx,yy);
			glVertex2i(x,y);

			x+=cur_font->width[utext[i]]*size/cur_font->charsize;
		}
	//*glEnd();

	cursorx=x;
#endif
}

void pRender::draw_text_center(int x,int y,const char *text,int size)
{
#ifdef P_INIT_OGL
	if (hrc==0)
		return;
#endif
	if (cur_font==0)
		return;

	const unsigned char *utext=(unsigned char *)text;
	int s=0;

	unsigned char* c=(unsigned char*)strchr(text,'\n');
	if(c==0)
	{
		s=get_text_size(text,size);
		draw_text(x-(s/2),y,text,size);
	}
	else
	{
		const unsigned char *t=utext;
		for( ;utext!=c;utext++ )
			s+=cur_font->width[*utext]*size/cur_font->charsize;

		draw_text(x-(s/2),y,(char *)t,size,utext-t);
		draw_text_center(x,y+size,(char *)++utext,size);
	}
}

int pRender::get_text_size(const char *text, int size)
{
	if (cur_font==0) 
		return 0;
	const unsigned char *utext=(unsigned char *)text;
	int ret=0,i=0,j=strlen(text);
	for( ;i<j;i++ )
		ret+=cur_font->width[utext[i]]*size/cur_font->charsize;
	return ret;
}

const char *get_file_name(const char *fullfile)
{
	const char *c1=strrchr(fullfile,'\\');
	const char *c2=strrchr(fullfile,'/');
	if (c2>c1)
		c1=c2;
	if (c1==0)
		return fullfile;
	else
		return c1+1;
}

const char *get_path_name(const char *fullfile)
{
	static pString s;
	s=fullfile;
	const char *c1=strrchr(fullfile,'\\');
	const char *c2=strrchr(fullfile,'/');
	if (c2>c1)
		c1=c2;
	if (c1==0)
		return "";
	s.set_char(c1-fullfile+1,0);
	return (const char *)s;
}

bool check_path(const pString& app_path,const pString& file1,pString& file2)
{
	pString s;
	
	s=get_path_name(file1);
	s+=get_file_name(file2);
	
	if (file2[0]==0 || file2[0]==' ' ||
		strncmp(app_path,s,app_path.length()))
	{
		file2="";
		return false;
	}

	file2=((const char *)s)+app_path.length();
	return true;
}

void pRender::build_mipmaps(pPicture *picture,unsigned int type2)
{
#ifndef P_DISABLE_3D
	if (picture->buf==0 || 
		(picture->flags&P_PICFLAGS_NOMIPMAP))
		return;

	int format=0;
	if (picture->bytespixel==1)
		format=GL_LUMINANCE;
	else
	if (picture->bytespixel==3)
		format=GL_RGB;
	else
	if (picture->bytespixel==4)
		format=GL_RGBA;

	if (format)
		gluBuild2DMipmaps(GL_TEXTURE_2D,picture->bytespixel,
			picture->sx,picture->sy,format,GL_UNSIGNED_BYTE,picture->buf);
#endif
}

int pRender::build_onepixelmap(unsigned char r,unsigned char g,unsigned char b)
{
#ifndef P_DISABLE_3D
	unsigned int mapID;
	glGenTextures(1, &mapID);
	glBindTexture(GL_TEXTURE_2D, mapID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE_EXT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE_EXT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	unsigned char map[3];
	map[0]=r;
	map[1]=g;
	map[2]=b;

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
			   1, 1, 0, GL_RGB,
			   GL_UNSIGNED_BYTE, map);

	picid.add(mapID);
	pic.add(0);
	
	glDisable(GL_TEXTURE_2D);
	sel_tex(-1);

	return pic.num-1;
#else
	return -1;
#endif
}

void pRender::reset_tex_state()
{
#ifndef P_DISABLE_3D
	if (GLEW_ARB_multitexture)
	{
		int i=maxtextureunits-1;
		for( ;i>=0;i-- )
		{
			glActiveTextureARB(GL_TEXTURE0_ARB+i);
			glDisable(GL_TEXTURE_2D);
			glClientActiveTextureARB(GL_TEXTURE0_ARB+i);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY); 
		}
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
#endif
}

void pRender::profile_build()
{
#ifndef P_DISABLE_3D
	pRenderProfile *rp;

	profile.free();
	sel_profile=-1;

	rp=new pRenderProfileStandardSP("STANDARD_SP");
	if (rp->test())
		profile.add(rp);
	else 
		delete rp;

	rp=new pRenderProfileStandardMP("STANDARD_MP");
	if (rp->test())
		profile.add(rp);
	else 
		delete rp;

#if 0 // P_SUPPORT_CG
	rp=new pRenderProfileVertexMP("VERTEX_MP");
	if (rp->test())
		profile.add(rp);
	else 
		delete rp;

	rp=new pRenderProfileFragmentMP("FRAGMENT_MP",false);
	if (rp->test())
		profile.add(rp);
	else 
		delete rp;

	rp=new pRenderProfileFragmentMP("FRAGMENT_FULL_MP",true);
	if (rp->test())
		profile.add(rp);
	else 
		delete rp;
#endif

	if (profile.num)
		profile_select(profile.num-1);
#endif
}

void pRender::profile_select(int p)
{
	if (profile.num==0)
		return;
	if (sel_profile!=-1)
		profile[sel_profile]->reset();
	if (p<0 || p>=profile.num)
		p=-1;
	sel_profile=p;
	if (p>=0)
	{
		profile.buf[sel_profile]->load();
		cur_profile=profile.buf[sel_profile];
	}
}

int pRender::profile_get_count() const
{
	return profile.num;
}

const char *pRender::profile_get_name(int p) const
{
	if(p<profile.num)
		return (const char *)(profile.buf[p]->name);

	return NULL;
}

int pRender::create_texture(int sx,int sy,int bytespixel,unsigned int color)
{
#ifndef P_DISABLE_3D
	unsigned int t;
	glGenTextures(1,&t);
	glBindTexture(GL_TEXTURE_2D,t);
	picid.add(t);

	pPicture *p=new pPicture;
	p->CreatePicture(bytespixel,sx,sy);
	pic.add(p);

	int i;
	if (bytespixel==1)
		for( i=0;i<p->size;i++ )
			p->buf[i]=(unsigned char)color;
	else
	if (bytespixel==2)
		for( i=0;i<p->size;i+=2 )
			*((unsigned short *)&p->buf[i])=(unsigned short)color;
	if (bytespixel==3)
		for( i=0;i<p->size;i+=3 )
		{
			p->buf[i]=((unsigned char *)&color)[0];
			p->buf[i+1]=((unsigned char *)&color)[1];
			p->buf[i+2]=((unsigned char *)&color)[2];
		}
	else
	if (bytespixel==4)
		for( i=0;i<p->size;i+=4 )
			*((unsigned int *)&p->buf[i])=color;

	set_tex_params(p,GL_TEXTURE_2D,GL_TEXTURE_2D);

	return picid.num-1;
#else
	return -1;
#endif
}

bool pRender::load_cubemap_tex(const char *texfile)
{
#ifndef P_DISABLE_3D
	if (cube_map_tex)
	{
		glDeleteTextures(1,&cube_map_tex);
		cube_map_tex=0;
	}

	if (texfile[0]==0)
		return false;

	pString base_name(texfile);
	pString full_name;
	pString extension;
	pPicture pic;

	// get extension
	extension=strrchr(base_name,'.');

	// get base name
	const char *c=strrchr(base_name,'_');
	if (c==NULL)
		return false;
	base_name=base_name.left(base_name.length()-strlen(c));

	// create cube map
	glGenTextures(1,&cube_map_tex);
	glBindTexture(GL_TEXTURE_CUBE_MAP,cube_map_tex);

	// read posx texture
	full_name=app_path+base_name+"_posx"+extension;
	if (pic.LoadPIC(full_name)==0)
		return false;
	if (pic.bytespixel==4)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,GL_RGBA,pic.sx,pic.sy,0,GL_RGBA,GL_UNSIGNED_BYTE,pic.buf);
	else
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,GL_RGB,pic.sx,pic.sy,0,GL_RGB,GL_UNSIGNED_BYTE,pic.buf);

	// read negx texture
	full_name=app_path+base_name+"_negx"+extension;
	if (pic.LoadPIC(full_name)==0)
		return false;
	if (pic.bytespixel==4)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,GL_RGBA,pic.sx,pic.sy,0,GL_RGBA,GL_UNSIGNED_BYTE,pic.buf);
	else
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,GL_RGB,pic.sx,pic.sy,0,GL_RGB,GL_UNSIGNED_BYTE,pic.buf);

	// read posy texture
	full_name=app_path+base_name+"_posy"+extension;
	if (pic.LoadPIC(full_name)==0)
		return false;
	if (pic.bytespixel==4)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,GL_RGBA,pic.sx,pic.sy,0,GL_RGBA,GL_UNSIGNED_BYTE,pic.buf);
	else
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,GL_RGB,pic.sx,pic.sy,0,GL_RGB,GL_UNSIGNED_BYTE,pic.buf);

	// read negy texture
	full_name=app_path+base_name+"_negy"+extension;
	if (pic.LoadPIC(full_name)==0)
		return false;
	if (pic.bytespixel==4)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,GL_RGBA,pic.sx,pic.sy,0,GL_RGBA,GL_UNSIGNED_BYTE,pic.buf);
	else
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,GL_RGB,pic.sx,pic.sy,0,GL_RGB,GL_UNSIGNED_BYTE,pic.buf);

	// read posz texture
	full_name=app_path+base_name+"_posz"+extension;
	if (pic.LoadPIC(full_name)==0)
		return false;
	if (pic.bytespixel==4)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,GL_RGBA,pic.sx,pic.sy,0,GL_RGBA,GL_UNSIGNED_BYTE,pic.buf);
	else
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,GL_RGB,pic.sx,pic.sy,0,GL_RGB,GL_UNSIGNED_BYTE,pic.buf);

	// read negz texture
	full_name=app_path+base_name+"_negz"+extension;
	if (pic.LoadPIC(full_name)==0)
		return false;
	if (pic.bytespixel==4)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,GL_RGBA,pic.sx,pic.sy,0,GL_RGBA,GL_UNSIGNED_BYTE,pic.buf);
	else
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,GL_RGB,pic.sx,pic.sy,0,GL_RGB,GL_UNSIGNED_BYTE,pic.buf);

	return true;
#else
	return false;
#endif
}

bool pRender::load_spheremap_tex(const char *texfile)
{
#ifndef P_DISABLE_3D
	if (sph_map_tex)
	{
		glDeleteTextures(1,&sph_map_tex);
		sph_map_tex=0;
	}

	if (texfile[0]==0)
		return false;

	pPicture pic;

	// create sphere map
	glGenTextures(1,&sph_map_tex);
	glBindTexture(GL_TEXTURE_2D,sph_map_tex);

	if (pic.LoadPIC(app_path+texfile)==0)
		return false;
	if (pic.bytespixel==4)
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pic.sx,pic.sy,0,GL_RGBA,GL_UNSIGNED_BYTE,pic.buf);
	else
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,pic.sx,pic.sy,0,GL_RGB,GL_UNSIGNED_BYTE,pic.buf);

	return true;
#else
	return false;
#endif
}

void pRender::load_ini(const char* inifilename)
{
	char buf[252];
	pString str=app_path+inifilename;
	renderini_path_store=str;

#if 0
	printf("...loading renderer ini file from ::: %s\n", str.getbuf());
#endif

	// Global parameters
	pParamDesc pd;
	int num_params=get_global_param_desc(0,0);
	for(int i=0;i<num_params;i++)
	{
		get_global_param_desc(i,&pd);
		buf[0]=0;
		//*GetPrivateProfileString("pGlobal",pd.name,"",buf,252,str);
		if(buf[0]!=0)
			pd.set_string(buf);
	}

	//*GetPrivateProfileString("pRender","norender","0",buf,252,str);
	sscanf(buf,"%i",&norender);
	//*GetPrivateProfileString("pRender","resolution","640 480",buf,252,str);
	sscanf(buf,"%i %i",&sizex,&sizey);
	//printf("str %s buf %s sizex %i sizey %i\n", str.getbuf(), buf, sizex, sizey);
	//for(;;) {}
	//*GetPrivateProfileString("pRender","fullscreen","0",buf,252,str);
	sscanf(buf,"%i",&fullscreen);
	//*GetPrivateProfileString("pRender","max_octree_depth","50",buf,252,str);
	sscanf(buf,"%i",&maxoctreedepth);
	//*GetPrivateProfileString("pRender","tex_resize","1",buf,252,str);
	sscanf(buf,"%i",&texresize);
	//*GetPrivateProfileString("pRender","draw_fps","1",buf,252,str);
	sscanf(buf,"%i",&drawfps);
	//*GetPrivateProfileString("pRender","camera_ctrl","1",buf,252,str);
	sscanf(buf,"%i",&selcamctrl);
	if (selcamctrl<0) selcamctrl=0;
	if (selcamctrl>1) selcamctrl=1;

	//*GetPrivateProfileString("pRender","camera_keys","SXQEAD",buf,252,str);
	if (strlen(buf)==6)
		camkeys=buf;

	pCameraCtrlObs *co=(pCameraCtrlObs *)camctrl[0];

	//*GetPrivateProfileString("pCameraCtrlObs","move_vel","10",buf,252,str);
	sscanf(buf,"%f",&co->movevel);
	//*GetPrivateProfileString("pCameraCtrlObs","rot_vel","50",buf,252,str);
	sscanf(buf,"%f",&co->rotvel);
	//*GetPrivateProfileString("pCameraCtrlObs","radius","1",buf,252,str);
	sscanf(buf,"%f",&co->radius);

#if 0
	pCameraCtrlOrbit *cb=(pCameraCtrlOrbit *)camctrl[1];

	//*GetPrivateProfileString("pCameraCtrlOrbit","move_vel","25",buf,252,str);
	sscanf(buf,"%f",&cb->movevel);
	//*GetPrivateProfileString("pCameraCtrlOrbit","rot_vel","50",buf,252,str);
	sscanf(buf,"%f",&cb->rotvel);
#endif

	/// Camera Override
	selcamctrl = 0;
}

void pRender::save_ini()
{
#if 0
	pString str=/*app_path*/+"unRenderer.ini";
	FILE *fp = fopen((const char *)str, "wt");
#else
	pString str;
	FILE *fp = fopen((const char *)renderini_path_store, "wt");
#endif

	if (!fp)
		return;

	// Global parameters
	fprintf(fp,"[pGlobal]\n");
	str="";
	pParamDesc pd;
	int num_params=get_global_param_desc(0,0);
	for(int i=0;i<num_params;i++)
	{
		get_global_param_desc(i,&pd);
		str=pd.get_string();
		fprintf(fp,"%s=%s\n",(const char *)pd.name,(const char *)str);
	}

	fprintf(fp,"\n");

	fprintf(fp,"[pRender]\n");
	if (selvideomode!=-1)
		fprintf(fp,"resolution=%i %i\n",
			videomode[selvideomode].dmPelsWidth,
			videomode[selvideomode].dmPelsHeight);
	fprintf(fp,"norender=%i\n",norender);
	fprintf(fp,"fullscreen=%i\n",fullscreen);
	fprintf(fp,"max_octree_depth=%i\n",maxoctreedepth);
	fprintf(fp,"tex_resize=%i\n",texresize);
	fprintf(fp,"draw_fps=%i\n",drawfps);
	fprintf(fp,"camera_ctrl=%i\n",selcamctrl);
	fprintf(fp,"camera_keys=%s\n",(const char *)camkeys);

	fprintf(fp,"\n");

	pCameraCtrlObs *co=(pCameraCtrlObs *)camctrl[0];
	fprintf(fp,"[pCameraCtrlObs]\n");
	fprintf(fp,"move_vel=%f\n",co->movevel);
	fprintf(fp,"rot_vel=%f\n",co->rotvel);
	fprintf(fp,"radius=%f\n",co->radius);

	fprintf(fp,"\n");

	pCameraCtrlOrbit *cb=(pCameraCtrlOrbit *)camctrl[1];
	fprintf(fp,"[pCameraCtrlOrbit]\n");
	fprintf(fp,"move_vel=%f\n",cb->movevel);
	fprintf(fp,"rot_vel=%f\n",cb->rotvel);

	fclose(fp);

	printf("Stored unRenderer.ini to %s\n", renderini_path_store.getbuf());
}

void pRender::set_fullscreen(int fsflag,int menuflag)
{
#ifdef P_INIT_OGL
	if (fullscreen==fsflag)
		return;
	fullscreen=fsflag;
	int nr=norender;
	norender=1;
	if (fullscreen==1)
	{
		ChangeDisplaySettings(&videomode[selvideomode],CDS_FULLSCREEN);
		SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPED);
		if (menuflag) SetMenu(hwnd,0);
		sizex=videomode[selvideomode].dmPelsWidth;
		sizey=videomode[selvideomode].dmPelsHeight;
		SetWindowPos(hwnd,HWND_TOP,0,0,sizex,sizey,SWP_SHOWWINDOW);
		ShowCursor(false);
	}
	else
	if (fullscreen==0)
	{
		ChangeDisplaySettings(NULL,NULL);
		SetWindowLong(hwnd,GWL_STYLE,WS_OVERLAPPEDWINDOW);
		if (menuflag) SetMenu(hwnd,winmenu);
		SetWindowPos(hwnd,HWND_TOP,0,0,sizex,sizey,SWP_SHOWWINDOW);
		InvalidateRect(GetDesktopWindow(),NULL,true);
		ShowCursor(true);
	}
	norender=nr;
	resize(sizex,sizey);
#endif
}

int pRender::sel_font(int fontid)
{
	int i;
	
	if(cur_font==0)
		i=-1;
	else
		for(i=0;i<font.num;i++)
			if(cur_font->pic==font[i]->pic)
				break;
	
	if (font.num>fontid && fontid>=0)
		cur_font=font[fontid];

	if(i==font.num)
		return -1;
	return i;
}

int pRender::load_font(const char *fontfile)
{
	pFontInfo *fi=new pFontInfo;
	
	char str[512];
	strcpy(str,fontfile);
	int td=texdetail;
	texdetail=0;
	fi->pic=load_tex(str,0,1);
	texdetail=td;
	if (fi->pic!=-1)
	{
#ifndef P_DISABLE_3D
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
#endif
		
		fi->size=pic[fi->pic]->sx;
		fi->charsize=fi->size/P_FONTS_NUM;

		int i;
		for( i=0;i<256;i++ )
			fi->width[i]=fi->charsize;

		char *c=strstr(str,".tga");
		if (c && (unsigned int)(c-str)==strlen(str)-4)
		{
			strcpy(c,".txt");

			pString str2=app_path+str;
			pFile fp;
			if (fp.open(str2))
			{
				for( i=0;i<256;i++ )
					fi->width[i]=fp.get_int();

				fp.close();
			}
		}

		font.add(fi);
		return font.num-1;
	}
	
	delete fi;
	return -1;
}

void pRender::blink(const int time,const pVector& color,const int add_blend)
{
	blink_data.add(color);
	pVector v2((float)time,(float)curtime,(float)add_blend,0.0f);
	blink_data.add(v2);
}

void pRender::blink_in(const int time,const pVector& color,const int add_blend)
{
	blink_data.add(color);
	pVector v2((float)time,(float)curtime,(float)add_blend,1.0f);
	blink_data.add(v2);
}

void pRender::blink_out(const int time,const pVector& color,const int add_blend)
{
	blink_data_out.add(color);
	pVector v2((float)time,(float)curtime,(float)add_blend,2.0f);
	blink_data_out.add(v2);
}

void pRender::const_blink(const pVector& color)
{
	const_blink_color=color;
}

void pRender::draw_blink()
{
#ifndef P_DISABLE_3D
	sel_tex(-1);

	//draw const blink
	if(const_blink_color.w>0.0f)
	{
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glColor4fv(&const_blink_color.x);
		//*glBegin(GL_QUADS);
			glVertex2i(0,0);
			glVertex2i(sizex,0);
			glVertex2i(sizex,sizey);
			glVertex2i(0,sizey);
		//*glEnd();
	}

	//draw timed blink with fading
	for(int i=0;i<blink_data.num;i+=2)
	{
		float elapsed_time=curtime-blink_data[i+1].y; // blink_data[i+1].y: start time

		if(blink_data[i+1].w==0.0f) // blink_data[i+1].w: blink mode (0 - fande in/out, 1 - fade in, 2 - fade out)
		{
			if(elapsed_time>blink_data[i+1].x) // blink_data[i+1].x: blink time
			{
				blink_data.remove(i);
				blink_data.remove(i);
				i-=2;
				continue;
			}

			float half_blink=blink_data[i+1].x/2; // blink_data[i+1].x: blink time
			float blink_factor;
			if(elapsed_time<half_blink)
				blink_factor=elapsed_time/half_blink;
			else
				blink_factor=2-(elapsed_time/half_blink);

			if(blink_data[i+1].z>0) // blink_data[i+1].z: additive blend flag
			{
				glBlendFunc(GL_ONE,GL_ONE);
				glColor3f(blink_data[i].x*blink_factor,blink_data[i].y*blink_factor,blink_data[i].z*blink_factor); // blink_data[i]: blink color
			}
			else
			{
				if (blink_data[i+1].z<0 && elapsed_time<half_blink)
					blink_factor=1.0f;
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				glColor4f(blink_data[i].x,blink_data[i].y,blink_data[i].z,blink_data[i].w*blink_factor);
			}
		}
		else if(blink_data[i+1].w==1.0f) // blink_data[i+1].w: blink mode (0 - fande in/out, 1 - fade in, 2 - fade out)
		{
			float blink_factor;

			if(elapsed_time>blink_data[i+1].x) // blink_data[i+1].x: blink time
			{
				if(blink_data_out.num>0)
				{
					// remove blink fade in from blink_data
					blink_data.remove(i);
					blink_data.remove(i);
					i-=2;

					// add blink fade out to blink_data
					blink_data_out[1].y=(float)curtime;
					blink_data.add(blink_data_out[0]);
					blink_data.add(blink_data_out[1]);

					// remove blink fade out from blink_data_out
					blink_data_out.remove(0);
					blink_data_out.remove(0);

					continue;
				}
				blink_factor=1.0f;
			}
			else
				blink_factor=elapsed_time/blink_data[i+1].x; // blink_data[i+1].x: blink time;

			if(blink_data[i+1].z>0) // blink_data[i+1].z: additive blend flag
			{
				glBlendFunc(GL_ONE,GL_ONE);
				glColor3f(blink_data[i].x*blink_factor,blink_data[i].y*blink_factor,blink_data[i].z*blink_factor); // blink_data[i]: blink color
			}
			else
			{
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				glColor4f(blink_data[i].x,blink_data[i].y,blink_data[i].z,blink_data[i].w*blink_factor);
			}
		}
		else if(blink_data[i+1].w==2.0f) // blink_data[i+1].w: blink mode (0 - fande in/out, 1 - fade in, 2 - fade out)
		{
			if(elapsed_time>blink_data[i+1].x) // blink_data[i+1].x: blink time
			{
				blink_data.remove(i);
				blink_data.remove(i);
				i-=2;
				continue;
			}

			float blink_factor=1.0f-(elapsed_time/blink_data[i+1].x); // blink_data[i+1].x: blink time;

			if(blink_data[i+1].z>0) // blink_data[i+1].z: additive blend flag
			{
				glBlendFunc(GL_ONE,GL_ONE);
				glColor3f(blink_data[i].x*blink_factor,blink_data[i].y*blink_factor,blink_data[i].z*blink_factor); // blink_data[i]: blink color
			}
			else
			{
				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				glColor4f(blink_data[i].x,blink_data[i].y,blink_data[i].z,blink_data[i].w*blink_factor);
			}
		}

		//*glBegin(GL_QUADS);
			glVertex2i(0,0);
			glVertex2i(sizex,0);
			glVertex2i(sizex,sizey);
			glVertex2i(0,sizey);
		//*glEnd();
	}
#endif
}

void pRender::draw3d()
{
#ifndef P_DISABLE_3D
#ifdef P_MANAGER_OBJ
	int i;
	g_romanager->process_visible();

	if (fog)
		glEnable(GL_FOG);
	else
		glDisable(GL_FOG);
	pVector black(0,0,0,0);
	g_render->bgcolor.w=0;

	glFogfv(GL_FOG_COLOR,&g_render->bgcolor.x);
	// Render non-mesh opaque objects.
	glBlendFunc(GL_ONE,GL_ZERO);
	rendermode=-1;
	g_render->draw(g_romanager->m_active_visible);

	if(cur_profile->get_caps()&P_RENDERCAPS_MULTI_PASS)
	{
		glFogfv(GL_FOG_COLOR,&g_render->bgcolor.x);
		if(shadowflag || cur_profile->get_caps()&P_RENDERCAPS_VERTEX_LIGHTING || cur_profile->get_caps()&P_RENDERCAPS_PIXEL_LIGHTING)
		{
			// Render opaque ambient pass.
			rendermode=P_RENDERMODE_AMBIENT;
			renderflag=P_RENDERFLAG_TEXTURE;
			cur_profile->ambient_pass(g_romanager->m_active_visible_mesh);

			glFogfv(GL_FOG_COLOR,&black.x);
			// Render opaque illumination pass.
			glPushAttrib(GL_ENABLE_BIT|GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			glDepthMask(GL_FALSE);
			glBlendFunc(GL_ONE,GL_ONE);
		}
		if(cur_profile->get_caps()&P_RENDERCAPS_SHADOWS)
		{
			if(shadowflag)
			{
				for( i=0;i<light.num;i++ )
				{
					bool shadowmap=(rs.m_shadow_buffer && light.buf[i]->angle>0.0f);
					if((light.buf[i]->flags&P_LIGHTFLAGS_NOSHADOW)==0)
					{
						if(light.buf[i]->type_shadow==pLight::SHADOW_VOLUME)
						{
							shadows_stencil_init();
							
							rendermode=P_RENDERMODE_SHADOWS;
							cur_profile->draw_shadows(light.buf[i]);

							shadows_stencil_test();
						}
						else 
						if (light.buf[i]->type_shadow==pLight::SHADOW_MAP && 
							shadowmap)
						{
							rendermode=P_RENDERMODE_SHADOWS;
							renderflag=0;
							rs.generate_shadow_map(light.buf[i]);
							if((cur_profile->get_caps()&P_RENDERCAPS_PIXEL_LIGHTING)==0)
								rs.bind_shadow_map(light.buf[i]);
						}
					}

					rendermode=0;
					cur_profile->draw_mp(light.buf[i]);

					if((light.buf[i]->flags&P_LIGHTFLAGS_NOSHADOW)==0)
					{
						if (light.buf[i]->type_shadow==pLight::SHADOW_VOLUME)
							shadows_stencil_release();
						else 
						if (light.buf[i]->type_shadow==pLight::SHADOW_MAP && 
							shadowmap)
						{
							if((cur_profile->get_caps()&P_RENDERCAPS_PIXEL_LIGHTING)==0)
								rs.unbind_shadow_map();
						}
					}
				}
			}
			else
			{
				rendermode=0;
				//for( i=0;i<light.num;i++ )
				//	cur_profile->draw_mp(light.buf[i]);
				cur_profile->draw_mp(g_romanager->m_active_visible_mesh);
			}
		}
		else
		{
			rendermode=0;
			//for( i=0;i<light.num;i++ )
			//	cur_profile->draw_mp(light.buf[i]);
			cur_profile->draw_mp(g_romanager->m_active_visible_mesh);
		}
		glPopAttrib();
	}
	else
	{
		glFogfv(GL_FOG_COLOR,&g_render->bgcolor.x);
		rendermode=0;
		glPushAttrib(GL_COLOR_BUFFER_BIT);
		cur_profile->draw_sp(g_romanager->m_active_visible_mesh);
		glPopAttrib();
	}

	glFogfv(GL_FOG_COLOR,&g_render->bgcolor.x);
	// Render non-mesh transparent objects.
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	rendermode=-2;
	g_render->draw(g_romanager->m_active_visible_transp);

#ifdef P_TRANSPARENT
	glPushAttrib(GL_ENABLE_BIT|GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDepthMask(GL_FALSE);
	if(cur_profile->get_caps()&P_RENDERCAPS_MULTI_PASS)
	{
		glFogfv(GL_FOG_COLOR,&g_render->bgcolor.x);
		if(shadowflag || cur_profile->get_caps()&P_RENDERCAPS_VERTEX_LIGHTING || cur_profile->get_caps()&P_RENDERCAPS_PIXEL_LIGHTING)
		{
			// Render transparent ambient pass.
			rendermode=P_RENDERMODE_AMBIENT|P_RENDERMODE_TRANSP;
			renderflag=P_RENDERFLAG_TEXTURE;
			cur_profile->ambient_pass(g_romanager->m_active_visible_mesh);

			glFogfv(GL_FOG_COLOR,&black.x);
			// Render transparent illumination pass.
			glBlendFunc(GL_SRC_ALPHA,GL_ONE);
		}
		rendermode=P_RENDERMODE_TRANSP;
		//for( i=0;i<light.num;i++ )
		//	cur_profile->draw_mp(light.buf[i]);
		cur_profile->draw_mp(g_romanager->m_active_visible_mesh);
	}
	else
	{
		glFogfv(GL_FOG_COLOR,&g_render->bgcolor.x);
		rendermode=P_RENDERMODE_TRANSP;
		cur_profile->draw_sp(g_romanager->m_active_visible_mesh);
	}
	glPopAttrib();
#endif

#ifdef P_EXTRAPASS
	// draw extra render pass
	glPushAttrib(GL_ENABLE_BIT|GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_ONE,GL_ONE);

	glFogfv(GL_FOG_COLOR,&black.x);
	rendermode=P_RENDERMODE_PASS;
	renderflag=P_RENDERFLAG_NORMAL|P_RENDERFLAG_TEXTURE|P_RENDERFLAG_TEXTURE2;
	g_render->draw(g_romanager->m_active_visible_mesh);
	for( i=g_render->maxtextureunits-1;i>=0;i-- )
		pRenderPass::clear_pass(GL_TEXTURE0_ARB+i);
	glPopAttrib();
#endif
	
	glDisable(GL_FOG);

	rendermode=0;
	renderflag=0;
	g_romanager->post_draw();

#ifdef P_MANAGER_OBJ
	if(debug)
	{
		g_romanager->draw_bboxes(g_romanager->m_active_visible);
		g_romanager->draw_bboxes(g_romanager->m_active_visible_mesh);
		g_romanager->draw_bboxes(g_romanager->m_active_visible_transp);
		g_romanager->draw_bboxes(g_romanager->m_active_visible_postdraw);
		g_romanager->draw_bboxes(g_romanager->m_active_visible_draw2d);
	}
#endif
#endif
#endif
}
	
void pRender::shadows_stencil_init()
{
#ifndef P_DISABLE_3D
	glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilMask(~0);

	glEnable(GL_STENCIL_TEST);
	glEnable(GL_STENCIL);
	glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
	glEnable(GL_CULL_FACE);
	glColor4ub(64,64,64,64);

	glClear(GL_STENCIL_BUFFER_BIT);
#endif
}

void pRender::shadows_stencil_test()
{
#ifndef P_DISABLE_3D
	glStencilMask(0);
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
	glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
	glStencilFunc(GL_EQUAL,0,~0);
#endif
}

void pRender::shadows_stencil_release()
{
#ifndef P_DISABLE_3D
	glPopAttrib();
#endif
}

void pRender::draw2d()
{
#ifndef P_DISABLE_3D
	if (rr_enabled && rr.m_ripplepb && rr.m_start_time>0)
		rr.m_ripplepb->Bind();

	if (rg_enabled && rg.m_tex)
		rg.draw_glow();

	if (rr_enabled && rr.m_ripplepb && rr.m_start_time>0)
	{
		rr.m_ripplepb->Unbind();
		rr.draw();
	}
	draw_blink();

	// Accumulation blur
	/*if (accumbits>=colorbits)
	if (ac_enabled==2)
	{
		ac_enabled=1;
		glClear(GL_ACCUM_BUFFER_BIT);
		glAccum(GL_ACCUM, ac_factor);
	}
	else
	if (ac_enabled)
	{
		glAccum(GL_ACCUM, 1.0f-ac_factor);
		glAccum(GL_RETURN, 1.0f);
		
		glClear(GL_ACCUM_BUFFER_BIT);
		glAccum(GL_ACCUM, ac_factor);
	}	*/
	
#ifdef P_MANAGER_OBJ
	g_romanager->draw2d();
#endif
#ifdef P_MANAGER_GUI
	g_gomanager->draw();
#endif

	sel_font(0);

	if (drawfps)
	{
		pString str;
		glColor3f(1,1,1);

		str.format("fps %i",curfps);
		draw_text(0,0,str,16);
	}

#ifdef P_MANAGER_OBJ
	if (debug)
	{
		pString str;
		glColor3f(1,1,1);

		str.format("stock %i",g_romanager->m_stock.get_count());
		draw_text(0,16,str,16);

		str.format("active %i",g_romanager->m_active.get_count());
		draw_text(0,32,str,16);

		str.format("root %i",g_romanager->m_active_root.num);
		draw_text(0,48,str,16);
	}
#endif

#ifdef P_MANAGER_GUI
	if (debug)
	{
		pString str;
		str.format("gui %i",g_gomanager->m_objects_root.num);
		draw_text(0,64,str,16);
	}
#endif

#endif
}

int pRender::get_global_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	{
		pd->comment="";
		switch(i)
		{
			case 0:
				pd->type='i';
				pd->data=&debug;
				pd->name="debug";
				break;
			case 1:
				pd->type='i';
				pd->data=&logflag;
				pd->name="logflag";
				pd->comment="Log flag\\Elapsed Time Step\\Last Updated Object\\Visible Objects\\Last Drawn Object\\Set Object Flags\\Set Obj Transform\\Set Obj Param\\Attach Object\\Release object\\Projectiles\\Set World Origin\\Render Update";
				break;
			case 2:
				pd->type='f';
				pd->data=&nearplane;
				pd->name="near_plane";
				break;
			case 3:
				pd->type='f';
				pd->data=&farplane;
				pd->name="far_plane";
				break;
			case 4:
				pd->type='d';
				pd->data=&hugeplane;
				pd->name="huge_plane";
				break;
			case 5:
				pd->type='b';
				pd->data=&hugeplaneflag;
				pd->name="huge_plane_flag";
				break;
			case 6:
				pd->type='f';
				pd->data=&camerafov;
				pd->name="camera_fov";
				break;
			case 7:
				pd->type='b';
				pd->data=&fog;
				pd->name="fog";
				break;
			case 8:
				pd->type='b';
				pd->data=&bgclear;
				pd->name="bg_clear";
				break;
			case 9:
				pd->type='c';
				pd->data=&bgcolor;
				pd->name="bg_color";
				break;
			case 10:
				pd->type='c';
				pd->data=&lightambient;
				pd->name="light_ambient";
				break;
			case 11:
				pd->type='b';
				pd->data=&texfilter;
				pd->name="tex_filter";
				break;
			case 12:
				pd->type='b';
				pd->data=&texmipmap;
				pd->name="tex_mipmap";
				break;
			case 13:
				pd->type='b';
				pd->data=&vertbuffer;
				pd->name="vert_buffer";
				break;
			case 14:
				pd->type='b';
				pd->data=&drawfps;
				pd->name="draw_fps";
				break;
			case 15:
				pd->type='i';
				pd->data=&texdetail;
				pd->name="texdetail";
				break;
			case 16:
				pd->type='i';
				pd->data=&loddetail;
				pd->name="loddetail";
				break;
#ifndef P_DISABLE_3D
			case 17:
				pd->type='b';
				pd->data=&rr_enabled;
				pd->name="ripple";
				break;
			case 18:
				pd->type='b';
				pd->data=&rr.m_fragment;
				pd->name="ripple_fragment";
				break;
			case 19:
				pd->type='u';
				pd->data=&rr.m_size;
				pd->name="ripple_resolution";
				break;
			case 20:
				pd->type='i';
				pd->data=&rr.m_vertexgridsize;
				pd->name="ripple_vertexgridsize";
				break;
			case 21:
				pd->type='f';
				pd->data=&rr.m_radius;
				pd->name="ripple_radius";
				break;
			case 22:
				pd->type='f';
				pd->data=&rr.m_duration;
				pd->name="ripple_duration";
				break;
			case 23:
				pd->type='f';
				pd->data=&rr.m_intensity;
				pd->name="ripple_intensity";
				break;
			case 24:
				pd->type='b';
				pd->data=&rg_enabled;
				pd->name="glow";
				break;
			case 25:
				pd->type='u';
				pd->data=&rg.m_size;
				pd->name="glow_resolution";
				break;
			case 26:
				pd->type='i';
				pd->data=&rg.m_blurnumpass;
				pd->name="glow_blurnumpass";
				break;
			case 27:
				pd->type='f';
				pd->data=&rg.m_blurfeedbackfact;
				pd->name="glow_feedbackfact";
				break;
			case 28:
				pd->type='b';
				pd->data=&shadowflag;
				pd->name="shadow_flag";
				break;
			case 29:
				pd->type='u';
				pd->data=&rs.m_size;
				pd->name="shadow_map_resolution";
				break;
			case 30:
				pd->type='f';
				pd->data=&rs.m_shadow_offset_factor;
				pd->name="shadow_map_offset_factor";
				break;
			case 31:
				pd->type='f';
				pd->data=&rs.m_shadow_offset_units;
				pd->name="shadow_map_offset_units";
				break;
			case 32:
				pd->type='b';
				pd->data=&svtype;
				pd->name="shadow_volume_peredge";
				break;
			case 33:
				pd->type='b';
				pd->data=&ac_enabled;
				pd->name="motion_blur_accum";
				break;
			case 34:
				pd->type='f';
				pd->data=&ac_factor;
				pd->name="motion_blur_accum_factor";
				break;
			case 35:
				pd->type='f';
				pd->data=&alphatestval;
				pd->name="alpha_test_val";
				break;
			case 36:
				pd->type='f';
				pd->data=&tooltip_delay;
				pd->name="tooltip_delay_time";
				break;
			case 37:
				pd->type='c';
				pd->data=&tooltip_bgcolor;
				pd->name="tooltip_bgcolor";
				break;
			case 38:
				pd->type='f';
				pd->data=&tooltip_bgcolor.w;
				pd->name="tooltip_bgtransp";
				break;
			case 39:
				pd->type='c';
				pd->data=&tooltip_textcolor;
				pd->name="tooltip_textcolor";
				break;
			case 40:
				pd->type='f';
				pd->data=&tooltip_textcolor.w;
				pd->name="tooltip_texttransp";
				break;
			case 41:
				pd->type='p';
				pd->data=&tooltip_tex;
				pd->name="tooltip_tex";
				break;
			case 42:
				pd->type='n';
				pd->data=&tooltip_font;
				pd->name="tooltip_font";
				break;
			case 43:
				pd->type='i';
				pd->data=&tooltip_fontsize;
				pd->name="tooltip_fontsize";
				break;
			case 44:
				pd->type='i';
				pd->data=&tooltip_border;
				pd->name="tooltip_border_size";
				break;
			case 45:
				pd->type='s';
				pd->data=&cube_map_tex_name;
				pd->name="cube_map_tex_base_name";
				pd->comment="Environment CubeBie Mapping files|Environment Mapping files (*.tga;*.jpg)|*.tga;*.jpg||";
				break;
			case 46:
				pd->type='s';
				pd->data=&sph_map_tex_name;
				pd->name="sphere_map_tex_name";
				pd->comment="Environment Sphere Mapping file|Environment Sphere Mapping file (*.tga;*.jpg)|*.tga;*.jpg||";
				break;
			case 47:
				pd->type='i';
				pd->data=&env_map_mode;
				pd->name="env_map_mode";
				pd->comment="Environment Mapping Mode|None|CubeBie Mapping|Sphere Mapping";
				break;
#ifdef P_SOUND
			case 48:
				pd->type='f';
				pd->data=&g_soundmanager->m_doppler_factor;
				pd->name="doppler_factor";
				break;
			case 49:
				pd->type='f';
				pd->data=&g_soundmanager->m_doppler_velocity;
				pd->name="doppler_velocity";
				break;
		}
	}
	return 50;
#else
		}
	}
	return 48;
#endif
#else
		}
	}
	return 17;
#endif
}

bool pRender::set_global_param(const char *param,const char *value)
{
	pParamDesc pd;
	int i,j;
	j=get_global_param_desc(0,0);
	for( i=0;i<j;i++ )
	{
		get_global_param_desc(i,&pd);
		if (_stricmp(pd.name,param)==0)
			break;
	}
	if (i==j)
		return false;

	on_pre_parameter_change(i);
	pd.set_string(value);
	on_pos_parameter_change(i);

	return true;
}


bool pRender::get_global_param(const char *param,pString& value)
{
	pParamDesc pd;
	int i,j;
	j=get_global_param_desc(0,0);
	for( i=0;i<j;i++ )
	{
		get_global_param_desc(i,&pd);
		if (_stricmp(pd.name,param)==0)
			break;
	}
	if (i==j)
		return false;

	value=pd.get_string();

	return true;
}

void pRender::on_pre_parameter_change(int i)
{
}

void pRender::on_pos_parameter_change(int i)
{
#ifndef P_DISABLE_3D
	switch(i)
	{
	case 11:
	case 12:
		update_texflags();
		break;

	case 17:
	case 18:
	case 19:
	case 20:
		if(pRenderRipple::test())
			rr.init(rr_enabled?rr.m_size:0,rr.m_fragment+1);
		break;
	case 24:
	case 25:
		if(pRenderGlow::test())
			rg.init(rg_enabled?rg.m_size:0);
		break;
	case 28:
		g_render->profile_select(g_render->sel_profile);
		if(pRenderShadowMap::test())
		{
			rs.init(shadowflag?rs.m_size:0);
			g_render->profile_select(g_render->sel_profile);
		}
		break;
	case 29:
		if(pRenderShadowMap::test())
		{
			rs.init(shadowflag?rs.m_size:0);
			g_render->profile_select(g_render->sel_profile);
		}
		break;
	case 32:
		g_render->profile_select(g_render->sel_profile);
		break;
	case 45:
		{
			if (load_cubemap_tex(cube_map_tex_name)==false && cube_map_tex)
			{
				glDeleteTextures(1,&cube_map_tex);
				cube_map_tex=0;
			}
		}
		break;
	case 46:
		{
			if (load_spheremap_tex(sph_map_tex_name)==false && sph_map_tex)
			{
				glDeleteTextures(1,&sph_map_tex);
				sph_map_tex=0;
			}
		}
		break;
#ifdef P_SOUND
	case 49:
		g_soundmanager->update_doppler_velocity();
		break;
#endif
	}
#endif
}

void pRender::do_frame(bool process_camera)
{
	update();
	if (process_camera)
	{
		check_input();
		update_camera();
	}

#ifdef P_MANAGER_OBJ
	g_romanager->step(curdtf);
#endif
#ifdef P_MANAGER_GUI
	g_gomanager->step(curdtf);
#endif

	begin_draw();
	
	draw3d();

	set_draw2d();

	draw2d();

	end_draw();
}

void pRender::draw_shadows(pLight *l,pRenderObject *obj)
{
#ifndef P_DISABLE_3D
	if(l==0 || obj==0)
		return;
	
#ifdef GL_ATI_separate_stencil
	if (GLEW_ATI_separate_stencil)
	{
		glDisable(GL_CULL_FACE);

		glStencilFuncSeparateATI(GL_ALWAYS,GL_ALWAYS,0,~0);
		glStencilOpSeparateATI(GL_BACK,GL_KEEP,GL_INCR_WRAP_EXT,GL_KEEP);
		glStencilOpSeparateATI(GL_FRONT,GL_KEEP,GL_DECR_WRAP_EXT,GL_KEEP);

		obj->draw_shadows(l->pos);

		glEnable(GL_CULL_FACE);
	}
	else
#endif
#ifdef GL_EXT_stencil_two_side
	if (GLEW_EXT_stencil_two_side)
	{
		glDisable(GL_CULL_FACE);
		glEnable(GL_STENCIL_TEST_TWO_SIDE_EXT);
	
		glActiveStencilFaceEXT(GL_BACK);
		glStencilFunc(GL_ALWAYS,0,~0);
		glStencilOp(GL_KEEP,GL_INCR_WRAP_EXT,GL_KEEP);

		glActiveStencilFaceEXT(GL_FRONT);
		glStencilOp(GL_KEEP,GL_DECR_WRAP_EXT,GL_KEEP);
		glStencilFunc(GL_ALWAYS,0,~0);

		obj->draw_shadows(l->pos);

		glEnable(GL_CULL_FACE);
		glDisable(GL_STENCIL_TEST_TWO_SIDE_EXT);
	}
	else
#endif
	{
		glStencilFunc(GL_ALWAYS,0,~0);

		glStencilOp(GL_KEEP,GL_INCR_WRAP_EXT,GL_KEEP);
		glCullFace(GL_FRONT);
		obj->draw_shadows(l->pos);

		glStencilOp(GL_KEEP,GL_DECR_WRAP_EXT,GL_KEEP);
		glCullFace(GL_BACK);
		obj->draw_shadows(l->pos);
	}
#endif
}

void pRender::set_shader_path(const char *path)
{
	shader_path=path;

	int len=strlen(path);
	if (len && path[len-1]!='/' && path[len-1]!='\\')
		shader_path+="/";
}

void pRender::set_app_path(const char *path)
{
	app_path=path;

	int len=strlen(path);
	if (len && path[len-1]!='/' && path[len-1]!='\\')
		shader_path+="/";
}

void pRender::clean_resources()
{
	int i;
	for( i=0;i<model.num;i++ )
		if (model.buf[i])
			model.buf[i]->flags&=~P_MESHFLAGS_REF;

#ifdef P_MANAGER_OBJ
	{
	pRenderObject *o=g_romanager->m_stock.get_next_object(1);
	while(o)
	{
		pParamDesc pd;
		int k,n=o->get_common_param_desc(0,0);
		for ( k=0;k<n;k++ )
		{
			o->get_common_param_desc(k,&pd);
			switch(pd.type)
			{
				case 'k':
				case 'm':
				{
					pMesh *m=*((pMesh **)pd.data);
					if (m)
						m->flags|=P_MESHFLAGS_REF;
				}
				break;
				case -'k':
				case -'m':
				{
					pArray<pMesh *> *d=(pArray<pMesh *> *)pd.data;
					for( int ii=0;ii<d->num;ii++ )
					{
						pMesh *m=d->buf[ii];
						if (m)
							m->flags|=P_MESHFLAGS_REF;
					}
				}
				break;
			}
		}
		
		o=g_romanager->m_stock.get_next_object();
	}
	}
#endif

#ifdef P_MANAGER_GUI
	{
	pGUIObject *o=g_gomanager->m_objects.get_next_object(1);
	while(o)
	{
		pParamDesc pd;
		int k,n=o->get_common_param_desc(0,0);
		for ( k=0;k<n;k++ )
		{
			o->get_common_param_desc(k,&pd);
			switch(pd.type)
			{
				case 'k':
				case 'm':
				{
					pMesh *m=*((pMesh **)pd.data);
					if (m)
						m->flags|=P_MESHFLAGS_REF;
				}
				break;
				case -'k':
				case -'m':
				{
					pArray<pMesh *> *d=(pArray<pMesh *> *)pd.data;
					for( int ii=0;ii<d->num;ii++ )
					{
						pMesh *m=d->buf[ii];
						if (m)
							m->flags|=P_MESHFLAGS_REF;
					}
				}
				break;
			}
		}
		
		o=g_gomanager->m_objects.get_next_object();
	}
	}
#endif

	for( i=0;i<model.num;i++ )
		if (model.buf[i] &&	(model.buf[i]->flags&P_MESHFLAGS_REF)==0)
		{
			delete model.buf[i];
			model.remove(i);
			i--;
		}
}

