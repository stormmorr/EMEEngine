#include "pch.h"
#include "paralelo3d.h"

const char *pParamDesc::get_string() const
{
	static pString str;

	str.set_char(0,0);

#ifdef P_MANAGER_OBJ
	if (type>255 && type<512)
	{
		if (*((pRenderObject **)data)!=0)
				str=(*((pRenderObject **)data))->m_name;
	}
	else
#endif
#ifdef P_MANAGER_GUI
	if(type>511)
	{
		if (*((pGUIObject **)data)!=0)
				str=(*((pGUIObject **)data))->m_name;
	}
	else
#endif
#ifdef P_MANAGER_OBJ
	if(type<-255 || type==-'o')
	{
		pArray<pRenderObject*>& a=*((pArray<pRenderObject*> *)data);
		for( int i=0;i<a.num;i++ )
		{
			if (i!=0) str+=" ";
			str+=a[i]->m_name;
		}
	}
	else
#endif
#ifdef P_MANAGER_GUI
	if(type<-511 || type==-'g')
	{
		pArray<pGUIObject*>& a=*((pArray<pGUIObject*> *)data);
		for( int i=0;i<a.num;i++ )
		{
			if (i!=0) str+=" ";
			str+=a[i]->m_name;
		}
	}
	else
#endif
	switch(type)
	{
		case 'u':
			str.format("%u",(*((unsigned int *)data)));
		break;
		case -'u':
		{
			pArray<unsigned>& a=*((pArray<unsigned int> *)data);
			pString s;
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				s.format("%u",a[i]);
				str+=s;
			}
		}
		break;
		case 'b':
			str.format("%i",(*((int *)data))==0?0:1);
		break;
		case -'b':
		{
			pArray<int>& a=*((pArray<int> *)data);
			pString s;
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				s.format("%i",a[i]==0?0:1);
				str+=s;
			}
		}
		break;
		case 'i':
			str.format("%i",*((int *)data));
		break;
		case -'i':
		{
			pArray<int>& a=*((pArray<int> *)data);
			pString s;
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				s.format("%i",a[i]);
				str+=s;
			}
		}
		break;
		case 'f':
			str.format("%.3f",*((float *)data));
		break;
		case 'a':
			str.format("%.3f",acos(*((float *)data))*PIUNDER180);
		break;
		case -'f':
		case -'a':
		{
			pArray<float>& a=*((pArray<float> *)data);
			pString s;
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				if (type==-'f')
					s.format("%.3f",a[i]);
				else
					str.format("%.3f",acos(a[i])*PIUNDER180);
				str+=s;
			}
		}
		break;
		case 'd':
			str.format("%.6le",*((double *)data));
		break;
		case -'d':
		{
			pArray<double>& a=*((pArray<double> *)data);
			pString s;
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				s.format("%.6le",a[i]);
				str+=s;
			}
		}
		break;
		case 'c':
		case 'v':
			str.format("%.3f %.3f %.3f",
				((float *)data)[0],
				((float *)data)[1],
				((float *)data)[2]);
		break;
		case -'c':
		case -'v':
		{
			pArray<pVector>& a=*((pArray<pVector> *)data);
			pString s;
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				s.format("%.3f %.3f %.3f",a[i].x,a[i].y,a[i].z);
				str+=s;
			}
		}
		break;
		case 'q':
			str.format("%.6le %.6le %.6le",
				((double *)data)[0],
				((double *)data)[1],
				((double *)data)[2]);
		break;
		case -'q':
		{
			pArray<pDVector>& a=*((pArray<pDVector> *)data);
			pString s;
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				s.format("%.6le %.6le %.6le",a[i].x,a[i].y,a[i].z);
				str+=s;
			}
		}
		break;
		case 't':
			str.format("%.3f %.3f %.3f %.3f",
				((float *)data)[0],
				((float *)data)[1],
				((float *)data)[2],
				((float *)data)[3]);
		break;
		case -'t':
		{
			pArray<pVector>& a=*((pArray<pVector> *)data);
			pString s;
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				s.format("%.3f %.3f %.3f %.3f",a[i].x,a[i].y,a[i].z,a[i].w);
				str+=s;
			}
		}
		break;
		case 'e':
		{
			str.format("%i %.3f %.3f %.3f %.3f",
				((pPeriodicFunc *)data)->m_type,
				((pPeriodicFunc *)data)->m_args[0],
				((pPeriodicFunc *)data)->m_args[1],
				((pPeriodicFunc *)data)->m_args[2],
				((pPeriodicFunc *)data)->m_args[3]);
		}
		break;
		case 'p':
			if (*((int *)data)!=-1)
				str=g_render->pic[*((int *)data)]->name;
		break;
		case -'p':
		{
			pArray<int>& a=*((pArray<int> *)data);
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				str+=g_render->pic[a[i]]->name;
			}
		}
		break;
#ifdef P_SOUND
		case 'h':
			if (*((int *)data)!=-1)
				str=g_soundmanager->m_sounds[*((int *)data)]->m_name;
		break;
		case -'h':
		{
			pArray<int>& a=*((pArray<int> *)data);
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				str+=g_soundmanager->m_sounds[a[i]]->m_name;
			}
		}
		break;
#endif
		case 'n':
			if (*((int *)data)!=-1)
				str=g_render->pic[g_render->font[*((int *)data)]->pic]->name;
		break;
		case -'n':
		{
			pArray<int>& a=*((pArray<int> *)data);
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				str+=g_render->pic[g_render->font[a[i]]->pic]->name;
			}
		}
		break;
#ifdef P_MANAGER_OBJ
		case 'o':
			if (*((pRenderObject **)data)!=0)
				str=(*((pRenderObject **)data))->m_name;
		break;
#endif
#ifdef P_MANAGER_GUI
		case 'g':
			if (*((pGUIObject **)data)!=0)
				str=(*((pGUIObject **)data))->m_name;
		break;
#endif
		case 'k':
			if (*((pMeshSkeleton **)data)!=0)
				str=(*((pMeshSkeleton **)data))->name;
		break;
		case -'k':
		{
			pArray<pMeshSkeleton*>& a=*((pArray<pMeshSkeleton*> *)data);
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				str+=a[i]->name;
			}
		}
		break;
		case 'm':
			if (*((pMesh **)data)!=0)
				str=(*((pMesh **)data))->name;
		break;
		case -'m':
		{
			pArray<pMesh*>& a=*((pArray<pMesh*> *)data);
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				str+=a[i]->name;
			}
		}
		break;
		case 's':
			str=*((pString *)data);
		break;
		case -'s':
		{
			pArray<pString>& a=*((pArray<pString> *)data);
			for( int i=0;i<a.num;i++ )
			{
				if (i!=0) str+=" ";
				str+=a[i];
			}
		}
		break;
		case 'r':
		{
			pVector rot, trans;
			((pMatrix *)data)->get_transformation(rot, trans);
			str.format("%.3f %.3f %.3f %.3f %.3f %.3f",
				trans.x, trans.y, trans.z,
				rot.x  , rot.y  , rot.z);
		}
		break;
	}
	return str;
}

void pParamDesc::get_binary(void * bin) const
{
	int size=0;
	if(type>255)
		size=4;
	else
#ifdef P_MANAGER_OBJ
	if((type<-255 && type>-512) || type==-'o')
		*((pArray<pRenderObject*> *)bin)=*((pArray<pRenderObject*> *)data);
	else
#endif
#ifdef P_MANAGER_GUI
	if(type<-511 || type==-'g')
		*((pArray<pGUIObject*> *)bin)=*((pArray<pGUIObject*> *)data);
	else
#endif
	switch(type)
	{
		case -'u':
			*((pArray<unsigned int> *)bin)=*((pArray<unsigned int> *)data);
		break;
		case -'b':
		case -'i':
			*((pArray<int> *)bin)=*((pArray<int> *)data);
		break;
		case -'f':
		case -'a':
			*((pArray<float> *)bin)=*((pArray<float> *)data);
		break;
		case -'d':
			*((pArray<double> *)bin)=*((pArray<double> *)data);
		break;
		case 'c':
			size=12;
			break;
		case 'v':
		case 't':
			size=16;
		break;
		case 'q':
			size=24;
		break;
		case 'e':
			size=20;
		break;
		case -'c':
		case -'v':
			*((pArray<pVector> *)bin)=*((pArray<pVector> *)data);
		break;
		case -'t':
			*((pArray<pVector> *)bin)=*((pArray<pVector> *)data);
		break;
		case -'q':
			*((pArray<pDVector> *)bin)=*((pArray<pDVector> *)data);
		break;
		case 's':
			*((pString *)bin)=*((pString *)data);
		break;
		case -'s':
			*((pArray<pString> *)bin)=*((pArray<pString> *)data);
		break;
		case 'r':
			size=64;
		break;
		case 'u':
		case 'b':
		case 'i':
		case 'f':
		case 'a':
#ifdef P_MANAGER_OBJ
		case 'o':
#endif
#ifdef P_MANAGER_GUI
		case 'g':
#endif
			size=4;
		break;
		case 'd':
			size=8;
		break;
	}
	memcpy(bin, data, size);
}

void pParamDesc::set_string(const char *str)
{
	// LOG
	if(g_render && g_render->logflag&P_LOG_SET_OBJ_PARAM)
		g_render->logreport.print_log(P_LOG_SET_OBJ_PARAM,"pParamDesc SetParam %s %s\n",(const char *)name,str);

#ifdef P_MANAGER_OBJ
	if (type>255 && type<512)
		(*((pRenderObject **)data))=(pRenderObject *)g_romanager->get_object(str);
	else
#endif
#ifdef P_MANAGER_GUI
	if (type>511)
		(*((pGUIObject **)data))=(pGUIObject *)g_gomanager->get_object(str);
	else
#endif
#ifdef P_MANAGER_OBJ
	if (type<-255 && type>-512)
	{
		char *c=(char *)str,*cc;
		pArray<pRenderObject*> *a=(pArray<pRenderObject*> *)data;
		pRenderObject *o;

		pString s;
		a->clear();
		while(c && *c!=0)
		{
			cc=strchr(c,' ');
			if (cc==0)
			{
				o = (pRenderObject*)g_romanager->get_object(c);
				if(o)
					a->add(o);
				break;
			}

			s.copy(c,0,cc-c);

			o = (pRenderObject*)g_romanager->get_object(s);

			if(o)
				a->add(o);

			c=cc+1;
		}
	}
	else
#endif
#ifdef P_MANAGER_GUI
	if (type<-511)
	{
		char *c=(char *)str,*cc;
		pArray<pGUIObject*> *a=(pArray<pGUIObject*> *)data;
		pGUIObject *o;

		pString s;
		a->clear();
		while(c && *c!=0)
		{
			cc=strchr(c,' ');
			if (cc==0)
			{
				o = (pGUIObject*)g_gomanager->get_object(c);

				if(o)
					a->add(o);
				break;
			}

			s.copy(c,0,cc-c);

			o = (pGUIObject*)g_gomanager->get_object(s);

			if(o)
				a->add(o);

			c=cc+1;
		}
	}
	else
#endif
	switch(type)
	{
		case 'u':
		{
			*((unsigned int *)data)=0;
			sscanf(str,"%u",(unsigned int *)data);
			if((*(unsigned int *)data)>0)
			{
				unsigned int u=*(unsigned int *)data;
				unsigned int n=1;
				while(u>>n!=0)
					n++;
				if(u-((unsigned int)1<<(n-1))>(((unsigned int)1<<n)-(1<<(n-1)))/2)
					*(unsigned int *)data=1<<n;
				else
					*(unsigned int *)data=1<<(n-1);
			}
		}
		break;
		case -'u':
		{
			char *c=(char *)str;
			pArray<unsigned int> *a=(pArray<unsigned int> *)data;
			unsigned int u;
			a->clear();
			while(c && *c!=0)
			{
				if (sscanf(c,"%u",&u)!=1) 
					break;
				unsigned int n=1;
				while(u>>n!=0)
					n++;
				if(u-((unsigned int)1<<(n-1))>((1<<n)-((unsigned int)1<<(n-1)))/2)
					a->add(1<<n);
				else
					a->add(1<<(n-1));
				c=strchr(c,' ');
				if (c==0) break;
				c++;
			}
		}
		break;
		case 'b':
		{
			*((int *)data)=0;
			sscanf(str,"%i",(int *)data);
			*((int *)data)=(*((int *)data)==0)?0:1;
		}
		break;
		case -'b':
		{
			char *c=(char *)str;
			pArray<int> *a=(pArray<int> *)data;
			int i;
			a->clear();
			while(c && *c!=0)
			{
				if (sscanf(c,"%i",&i)!=1) 
					break;
				a->add((i==0)?0:1);
				c=strchr(c,' ');
				if (c==0) break;
				c++;
			}
		}
		break;
		case 'i':
		{
			*((int *)data)=0;
			sscanf(str,"%i",(int *)data);
		}
		break;
		case -'i':
		{
			char *c=(char *)str;
			pArray<int> *a=(pArray<int> *)data;
			int i;
			a->clear();
			while(c && *c!=0)
			{
				if (sscanf(c,"%i",&i)!=1) 
					break;
				a->add(i);
				c=strchr(c,' ');
				if (c==0) break;
				c++;
			}
		}
		break;
		case 'f':
		{
			*((float *)data)=0;
			sscanf(str,"%f",(float *)data);
		}
		break;
		case 'a':
		{
			*((float *)data)=0;
			sscanf(str,"%f",(float *)data);
			*((float *)data)=(float)cos(*((float *)data)*PIOVER180);
		}
		break;
		case -'f':
		case -'a':
		{
			char *c=(char *)str;
			pArray<float> *a=(pArray<float> *)data;
			float f;
			a->clear();
			while(c && *c!=0)
			{
				if (sscanf(c,"%f",&f)!=1) 
					break;
				a->add(f);
				c=strchr(c,' ');
				if (c==0) break;
				c++;
			}
		}
		break;
		case 'd':
		{
			*((double *)data)=0;
			sscanf(str,"%le",(double *)data);
		}
		break;
		case -'d':
		{
			char *c=(char *)str;
			pArray<double> *a=(pArray<double> *)data;
			double f;
			a->clear();
			while(c && *c!=0)
			{
				if (sscanf(c,"%le",&f)!=1) 
					break;
				a->add(f);
				c=strchr(c,' ');
				if (c==0) break;
				c++;
			}
		}
		break;
		case 'c':
		case 'v':
		{
			((float *)data)[0]=
			((float *)data)[1]=
			((float *)data)[2]=0;
			sscanf(str,"%f %f %f",
				&((float *)data)[0],
				&((float *)data)[1],
				&((float *)data)[2]);
		}
		break;
		case -'c':
		case -'v':
		{
			char *c=(char *)str;
			pArray<pVector> *a=(pArray<pVector> *)data;
			pVector v;
			a->clear();
			while(c && *c!=0)
			{
			  int i;
				for(i=0;i<3; )
				{
					if (sscanf(c,"%f",&v[i])!=1) 
						break;
					else i++;
					c=strchr(c,' ');
					if (c==0) break;
					c++;
				}
				if (i==3)
					a->add(v);
				else break;
			}
		}
		break;
		case 'q':
		{
			((double *)data)[0]=
			((double *)data)[1]=
			((double *)data)[2]=0;
			sscanf(str,"%le %le %le",
				&((double *)data)[0],
				&((double *)data)[1],
				&((double *)data)[2]);
		}
		break;
		case -'q':
		{
			char *c=(char *)str;
			pArray<pDVector> *a=(pArray<pDVector> *)data;
			pDVector v;
			a->clear();
			while(c && *c!=0)
			{ 
			  int i;
				for(i=0;i<3; )
				{
					if (sscanf(c,"%le",&v[i])!=1) 
						break;
					else i++;
					c=strchr(c,' ');
					if (c==0) break;
					c++;
				}
				if (i==3)
					a->add(v);
				else break;
			}
		}
		break;
		case 't':
		{
			((float *)data)[0]=
			((float *)data)[1]=
			((float *)data)[2]=
			((float *)data)[3]=0;
			sscanf(str,"%f %f %f %f",
				&((float *)data)[0],
				&((float *)data)[1],
				&((float *)data)[2],
				&((float *)data)[3]);
		}
		break;
		case -'t':
		{
			char *c=(char *)str;
			pArray<pVector> *a=(pArray<pVector> *)data;
			pVector v;
			a->clear();
			while(c && *c!=0)
			{
			  int i;
				for(i=0;i<4; )
				{
					if (sscanf(c,"%f",&v[i])!=1) 
						break;
					else i++;
					c=strchr(c,' ');
					if (c==0) break;
					c++;
				}
				if (i==4)
					a->add(v);
				else break;
			}
		}
		break;
		case 'e':
		{
			((pPeriodicFunc *)data)->m_type = 0;
			((pPeriodicFunc *)data)->m_args[0] =
			((pPeriodicFunc *)data)->m_args[1] =
			((pPeriodicFunc *)data)->m_args[2] =
			((pPeriodicFunc *)data)->m_args[3] =0.0f;

			sscanf(str,"%i %f %f %f %f",
				&((pPeriodicFunc *)data)->m_type,
				&((pPeriodicFunc *)data)->m_args[0],
				&((pPeriodicFunc *)data)->m_args[1],
				&((pPeriodicFunc *)data)->m_args[2],
				&((pPeriodicFunc *)data)->m_args[3]);
		}
		break;
		case 'p':
		{
			int texid = g_render->load_tex(str,0,g_render->texload);
			if (texid == -1 && str[0] != 0 && str[0] != ' ')
			{
				pString msg = pString("pRenderP3D: Could not load ") + str + "\n";
				OutputDebugString((LPCWSTR)(const char *)msg);
			}
			else
				*((int *)data) = texid;
		}
		break;
		case -'p':
		{
			char *c=(char *)str,*cc;
			pArray<int> *a=(pArray<int> *)data;

			int texid;
			pString s;
			a->clear();
			while(c && *c!=0)
			{
				cc=strchr(c,' ');
				if (cc==0)
				{
					texid = g_render->load_tex(c,0,g_render->texload);
					if (texid == -1 && c[0] != 0 && c[0] != ' ')
					{
						pString msg = pString("pRenderP3D: Could not load ") + c + "\n";
						OutputDebugString((LPCWSTR)(const char *)msg);
					}
					else
						a->add(texid);

					break;
				}
				
				s.copy(c,0,cc-c);

				texid = g_render->load_tex(s,0,g_render->texload);
				if (texid == -1 && s[0] != 0 && s[0] != ' ')
				{
					pString msg = pString("pRenderP3D: Could not load ") + s + "\n";
					OutputDebugString((LPCWSTR)(const char *)msg);
				}
				else
					a->add(texid);

				c=cc+1;
			}
		}
		break;
#ifdef P_SOUND
		case 'h':
		{
			int sndid=g_soundmanager->load_sound(str);
			if(sndid==-1 && str[0]!=0 && str[0]!=' ')
			{
				pString msg=pString("pSoundManager: Could not load ") + str + "\n";
				OutputDebugString((const char *)msg);
			}
			else
				*((int *)data)=sndid;
		}
		break;
		case -'h':
		{
			char *c=(char *)str,*cc;
			pArray<int> *a=(pArray<int> *)data;

			int sndid;
			pString s;
			a->clear();
			while(c && *c!=0)
			{
				cc=strchr(c,' ');
				if (cc==0)
				{
					sndid = g_soundmanager->load_sound(c);
					if (sndid == -1 && c[0] != 0 && c[0] != ' ')
					{
						pString msg = pString("pSoundManager: Could not load ") + c + "\n";
						OutputDebugString((const char *)msg);
					}
					else
						a->add(sndid);

					break;
				}
				
				s.copy(c,0,cc-c);

				sndid = g_soundmanager->load_sound(s);
				if (sndid == -1 && s[0] != 0 && s[0] != ' ')
				{
					pString msg = pString("pSoundManager: Could not load ") + s + "\n";
					OutputDebugString((const char *)msg);
				}
				else
					a->add(sndid);

				c=cc+1;
			}
		}
		break;
#endif
		case 'n':
		{
			int fontid = g_render->load_font(str);
			if (fontid == -1 && str[0] != 0 && str[0] != ' ')
			{
				pString msg = pString("pRenderP3D: Could not load font ") + str + "\n";
				OutputDebugString((LPCWSTR)(const char *)msg);
			}
			else
				*((int *)data) = fontid;
		}
		break;
		case -'n':
		{
			char *c=(char *)str,*cc;
			pArray<int> *a=(pArray<int> *)data;

			int fontid;
			pString s;
			a->clear();
			while(c && *c!=0)
			{
				cc=strchr(c,' ');
				if (cc==0)
				{
					fontid = g_render->load_font(c);
					if (fontid == -1 && c[0] != 0 && c[0] != ' ')
					{
						pString msg = pString("pRenderP3D: Could not load font ") + c + "\n";
						OutputDebugString((LPCWSTR)(const char *)msg);
					}
					else
						a->add(fontid);

					break;
				}
				
				s.copy(c,0,cc-c);

				fontid = g_render->load_font(s);
				if (fontid == -1 && s[0] != 0 && s[0] != ' ')
				{
					pString msg = pString("pRenderP3D: Could not load font ") + s + "\n";
					OutputDebugString((LPCWSTR)(const char *)msg);
				}
				else
					a->add(fontid);

				c=cc+1;
			}
		}
		break;
#ifdef P_MANAGER_OBJ
		case 'o':
			*((pRenderObject **)data)=(pRenderObject *)g_romanager->get_object(str);
		break;
		case -'o':
		{
			char *c=(char *)str,*cc;
			pArray<pRenderObject*> *a=(pArray<pRenderObject*> *)data;
			pRenderObject *o;

			pString s;
			a->clear();
			while(c && *c!=0)
			{
				cc=strchr(c,' ');
				if (cc==0)
				{
					o = (pRenderObject*)g_romanager->get_object(c);

					if(o)
						a->add(o);
					break;
				}

				s.copy(c,0,cc-c);

				o = (pRenderObject*)g_romanager->get_object(s);

				if(o)
					a->add(o);

				c=cc+1;
			}
		}
		break;
#endif
#ifdef P_MANAGER_GUI
		case 'g':
			*((pGUIObject **)data)=(pGUIObject *)g_gomanager->get_object(str);
		break;
		case -'g':
		{
			char *c=(char *)str,*cc;
			pArray<pGUIObject*> *a=(pArray<pGUIObject*> *)data;
			pGUIObject *o;

			pString s;
			a->clear();
			while(c && *c!=0)
			{
				cc=strchr(c,' ');
				if (cc==0)
				{
					o = (pGUIObject*)g_gomanager->get_object(c);

					if(o)
						a->add(o);
					break;
				}

				s.copy(c,0,cc-c);

				o = (pGUIObject*)g_gomanager->get_object(s);

				if(o)
					a->add(o);

				c=cc+1;
			}
		}
		break;
#endif
		case 'k':
		{
			pMeshSkeleton *m = g_render->load_mesh_skeleton(str);
			if (m == 0 && str[0] != 0 && str[0] != ' ')
			{
				pString msg = pString("pRenderP3D: Could not load ") + str + "\n";
				OutputDebugString((LPCWSTR)(const char *)msg);
			}
			else
				*((pMesh **)data) = m;
		}
		break;
		case -'k':
		{
			char *c=(char *)str,*cc;
			pArray<pMeshSkeleton*> *a=(pArray<pMeshSkeleton*> *)data;

			pMeshSkeleton *m;
			pString s;
			a->clear();
			while(c && *c!=0)
			{
				cc=strchr(c,' ');
				if (cc==0)
				{
					m = g_render->load_mesh_skeleton(c);
					if (m == 0 && c[0] != 0 && c[0] != ' ')
					{
						pString msg = pString("pRenderP3D: Could not load ") + c + "\n";
						OutputDebugString((LPCWSTR)(const char *)msg);
					}
					else
						a->add(m);

					break;
				}
				
				s.copy(c,0,cc-c);

				m = g_render->load_mesh_skeleton(s);
				if (m == 0 && s[0] != 0 && s[0] != ' ')
				{
					pString msg = pString("pRenderP3D: Could not load ") + s + "\n";
					OutputDebugString((LPCWSTR)(const char *)msg);
				}
				else
					a->add(m);

				c=cc+1;
			}
		}
		break;
		case 'm':
		{
			pMesh *m = g_render->load_mesh(str,1);
			if (m == 0 && str[0] != 0 && str[0] != ' ')
			{
				pString msg = pString("pRenderP3D: Could not load ") + str + "\n";
				OutputDebugString((LPCWSTR)(const char *)msg);
			}
			else
				*((pMesh **)data) = m;
		}
		break;
		case -'m':
		{
			char *c=(char *)str,*cc;
			pArray<pMesh*> *a=(pArray<pMesh*> *)data;

			pMesh *m;
			pString s;
			a->clear();
			while(c && *c!=0)
			{
				cc=strchr(c,' ');
				if (cc==0)
				{
					m = g_render->load_mesh(c,1);
					if (m == 0 && c[0] != 0 && c[0] != ' ')
					{
						pString msg = pString("pRenderP3D: Could not load ") + c + "\n";
						OutputDebugString((LPCWSTR)(const char *)msg);
					}
					else
						a->add(m);

					break;
				}
				
				s.copy(c,0,cc-c);

				m = g_render->load_mesh(s,1);
				if (m == 0 && s[0] != 0 && s[0] != ' ')
				{
					pString msg = pString("pRenderP3D: Could not load ") + s + "\n";
					OutputDebugString((LPCWSTR)(const char *)msg);
				}
				else
					a->add(m);

				c=cc+1;
			}
		}
		break;
		case 's':
			*((pString *)data)=str;
		break;
		case -'s':
		{
			char *c=(char *)str,*cc;
			pArray<pString> *a=(pArray<pString> *)data;

			pString s;
			a->clear();
			while(c && *c!=0)
			{
				cc=strchr(c,' ');
				if (cc==0)
				{
					a->add(c);
					break;
				}
				s.copy(c,0,cc-c);
				a->add(s);
				c=cc+1;
			}
		}
		break;
		case 'r':
		{
			pVector rot, trans;
			sscanf(str,"%f %f %f %f %f %f",
				&trans.x, &trans.y, &trans.z,
				&rot.x  , &rot.y  , &rot.z);
			((pMatrix *)data)->set_transformation(rot, trans);
		}
		break;
	}
}

void pParamDesc::set_binary(const void *bin)
{
	int size=0;
	if(type>255)
		size=4;
#ifdef P_MANAGER_OBJ
	if((type<-255 && type>-512) || type==-'o')
		*((pArray<pRenderObject*> *)data)=*((pArray<pRenderObject*> *)bin);
	else
#endif
#ifdef P_MANAGER_GUI
	if(type<-511 || type==-'g')
		*((pArray<pGUIObject*> *)data)=*((pArray<pGUIObject*> *)bin);
	else
#endif
	switch(type)
	{
		case -'u':
			*((pArray<unsigned int> *)data)=*((pArray<unsigned int> *)bin);
		break;
		case -'b':
		case -'i':
			*((pArray<int> *)data)=*((pArray<int> *)bin);
		break;
		case -'f':
		case -'a':
			*((pArray<float> *)data)=*((pArray<float> *)bin);
		break;
		case -'d':
			*((pArray<double> *)data)=*((pArray<double> *)bin);
		break;
		case 'c':
			size=12;
			break;
		case 'v':
		case 't':
			size=16;
		break;
		case 'q':
			size=24;
		break;
		case 'e':
			size=20;
		break;
		case -'c':
		case -'v':
			*((pArray<pVector> *)data)=*((pArray<pVector> *)bin);
		break;
		case -'t':
			*((pArray<pVector> *)data)=*((pArray<pVector> *)bin);
		break;
		case -'q':
			*((pArray<pDVector> *)data)=*((pArray<pDVector> *)bin);
		break;
		case 's':
			*((pString *)data)=*((pString *)bin);
		break;
		case -'s':
			*((pArray<pString> *)data)=*((pArray<pString> *)bin);
		break;
		case 'r':
			size=64;
		break;
		case 'u':
		case 'b':
		case 'i':
		case 'f':
		case 'a':
#ifdef P_MANAGER_OBJ
		case 'o':
#endif
#ifdef P_MANAGER_GUI
		case 'g':
#endif
			size=4;
		break;
		case 'd':
			size=8;
		break;
	}
	memcpy(data, bin, size);
}
