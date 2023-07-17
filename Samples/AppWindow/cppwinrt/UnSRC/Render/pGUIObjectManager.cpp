#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

#define DEFAULT_DOUBLECLICK_TIME 0.2f

P3D_API pGUIObjectManager *get_gui_manager()
{
	return g_gomanager;
}

pGUIObjectManager::pGUIObjectManager()
{
	m_click_flag[0]=m_click_flag[1]=m_click_flag[2]=true;
	m_click_time[0]=m_click_time[1]=m_click_time[2]=0.0f;

	m_mouse_drag_x=0;
	m_mouse_drag_y=0;

	m_mouse_last_x=0;
	m_mouse_last_y=0;
	
	m_time=0;
	m_elapsed_time=0;

	m_objcount=0;
	m_mouse_state=0;
	m_mouse_cursor=-1;
	m_mouse_cursor_can_drop=-1;
	m_mouse_cursor_cannot_drop=-1;
	m_mouse_last_cursor=-1;
	m_mouse_focus=0;
	m_mouse_drag_focus=0;
	m_mouse_drop_focus=0;
	m_input_focus=0;

	m_mouse_drag_focus_eh=NULL;
	m_mouse_drop_focus_eh=NULL;

	m_translate_x=0;
	m_translate_y=0;

	m_double_click_time=DEFAULT_DOUBLECLICK_TIME;

	m_tooltip_mousefocus_time=-1.0f;

	m_modkeys=0;

	m_factory.add(new pGUIButton_desc);
	m_factory.add(new pGUICheckBox_desc);
	m_factory.add(new pGUIEditBox_desc);
	m_factory.add(new pGUIGroup_desc);
	m_factory.add(new pGUIImage_desc);
	m_factory.add(new pGUIListControl_desc);
	m_factory.add(new pGUIModelViewer_desc);
	m_factory.add(new pGUIMultilineText_desc);
	m_factory.add(new pGUIPopUpMenu_desc);
	m_factory.add(new pGUIProgressBar_desc);
	m_factory.add(new pGUIProgressDisk_desc);
	m_factory.add(new pGUIRadialCursor_desc);
	m_factory.add(new pGUITreeControl_desc);
	m_factory.add(new pGUIWindow_desc);
}
	
pGUIObjectManager::~pGUIObjectManager()
{
	// free factory
	for( int i=0;i<m_factory.num;i++ )
		delete m_factory[i];
	// free objects
	reset();
}

void pGUIObjectManager::reset()
{
	m_mouse_drag_x=0;
	m_mouse_drag_y=0;
	
	m_mouse_last_x=0;
	m_mouse_last_y=0;

	m_objcount=0;
	m_time=0;
	m_mouse_state=0;
	m_mouse_cursor=-1;
	m_mouse_cursor_can_drop=-1;
	m_mouse_cursor_cannot_drop=-1;
	m_mouse_last_cursor=-1;
	m_mouse_focus=0;
	m_mouse_drag_focus=0;
	m_mouse_drop_focus=0;
	m_input_focus=0;

	m_mouse_drag_focus_eh=NULL;
	m_mouse_drop_focus_eh=NULL;

	m_translate_x=0;
	m_translate_y=0;

	m_double_click_time=DEFAULT_DOUBLECLICK_TIME;

	m_modkeys=0;

	// free objects
	pGUIObject *o = m_objects.get_next_object(1);
	do delete o;
	while(o = m_objects.get_next_object());
	m_objects.reset();
	m_objects_str.reset();
	m_objects_root.free();
	m_eventhandler_root.free();

	// free file
	pgo_clear();
}

bool pGUIObjectManager::pgo_load(const char* filename)
{
	pString s=g_render->app_path+filename;

	pFile *file=new pFile;
	if (file->open(s))
	{
		file->append_table();
		file->close();
		m_files.add(file);
		return true;
	}

	delete file;
	return false;
}

bool pGUIObjectManager::pgo_unload(const char* filename)
{
	int i=find_file(filename);

	if (i!=-1)
	{
		m_files.buf[i]->clear_table();
		delete m_files.buf[i];
		m_files.remove(i);
		return true;
	}

	return false;
}


int pGUIObjectManager::find_file(const char *filename) const
{
	pString s=g_render->app_path+filename;

	int i;
	for( i=0;i<m_files.num;i++ )
		if (m_files.buf[i]->name==s)
			return i;

	return -1;
}

void pGUIObjectManager::pgo_clear()
{
	int i;
	for( i=0;i<m_files.num;i++ )
		delete m_files.buf[i];
	m_files.free();
}

int pgo_compare(const void *arg1,const void *arg2)
{
	pGUIObject *obj1=*((pGUIObject **)arg1);
	pGUIObject *obj2=*((pGUIObject **)arg2);
	return obj1->m_name.compare_nocase((const char *)obj2->m_name);
}

bool pGUIObjectManager::pgo_save(const char* filename)
{
	FILE *fp = fopen(filename, "wt");

	if (!fp)
		return false;

	// stores objects from stock to local array
	pArray<pGUIObject *> gui_objects;
	pGUIObject *obj=m_objects.get_next_object(1);
	while(obj)
	{
		gui_objects.add(obj);
		obj=m_objects.get_next_object();
	}

	// order objects by name
	qsort(gui_objects.buf,(size_t)(gui_objects.num),sizeof(pGUIObject *),pgo_compare);

	// sabe objects into a file
	int n;
	pString val,def;
	pParamDesc pd;
	pClassDesc *cd;
	pGUIObject *o;
	for(int j=0;j<gui_objects.num;j++)
	{
		cd=m_factory.buf[P_GUITYPE2FACTORYID(gui_objects[j]->m_type)];
		o=(pGUIObject *)cd->create();

		// write section
		fprintf(fp, "[%s]\n", (const char *)gui_objects[j]->m_name);
		fprintf(fp, "classtype=%s\n", cd->get_name());

		// write parameters
		n = gui_objects[j]->get_common_param_desc(0, 0);
		for(int i=0;i<n;i++)
		{
			o->get_common_param_desc(i, &pd);
			def = pd.get_string();
			gui_objects[j]->get_common_param_desc(i, &pd);
			val = pd.get_string();
			if (val[0] && strcmp(val,def))
				fprintf(fp, "%s=%s\n", (const char *)pd.name, (const char *)val);
		}
		
		fprintf(fp, "\n");
		delete o;
	}

	fclose(fp);
	return true;
}

unsigned int pGUIObjectManager::create(const char *objname,pFile *f)
{
	// test if this object already exists
	if (m_objects_str.get_object(objname))
		return 0;

	int i;
	pFile *ff=NULL;
	if (f)
		ff=f;
	else
	{
		for( i=0;i<m_files.num;i++ )
			if (m_files.buf[i]->find_group(objname))
			{
				ff=m_files.buf[i];
				break;
			}
	}
	if (ff==NULL)
		return 0;

	pString str;
	if (!ff->get_profile_string(objname, "classtype", str))
		return 0;

	// find correspondent class descriptor
	pClassDesc* cd = 0;
	for (i = 0; i < m_factory.num; i++)
		if (_stricmp(m_factory.buf[i]->get_name(), (const char *)str) == 0)
			break;
	if (i == m_factory.num)
		return 0;
	cd = m_factory.buf[i];

	// create corresponding object
	pGUIObject* obj = (pGUIObject *)cd->create();

	// initialize object
	pParamDesc pd;
	int n = obj->get_common_param_desc(0, 0);
	for (i = 0; i < n; i++)
	{
		obj->get_common_param_desc(i, &pd);
		if (ff->get_profile_string(objname, pd.name, str))
			pd.set_string((const char *)str);
	}
	obj->m_name = objname;

	// store object into hash table
	m_objects.add(++m_objcount, obj);
	m_objects_str.add(objname, obj);

	obj->m_id = m_objcount;
	obj->init();

	// update m_parent attribute for each child
	for (i=0;i<obj->m_child.num;i++)
		obj->m_child.buf[i]->m_parent=obj;

	return m_objcount;
}

unsigned int pGUIObjectManager::create(const char *objname,const char *filename)
{
	// verifies if file exist
	int i=find_file(filename);
	if (i!=-1)
		return create(objname,m_files.buf[i]);
	return 0;
}

bool pGUIObjectManager::pgo_create(const char *filename, bool load_tex_flag)
{
	int j,i=find_file(filename);
	if (i!=-1 && m_files.buf[i]->table)
	{
		g_render->texload=0;

		for ( j=0;j<m_files.buf[i]->table->num;j++ )
			create((const char *)(m_files.buf[i]->table->buf[j].buf[0]));

		g_render->texload=1;

		if (load_tex_flag)
			pgo_load_textures(filename);

		return true;
	}
	return false;
}

void pGUIObjectManager::create_all(bool load_tex_flag)
{
	g_render->texload=0;

	int i,j;
	for ( i=0;i<m_files.num;i++ )
		if (m_files.buf[i]->table)
			for ( j=0;j<m_files.buf[i]->table->num;j++ )
				create((const char *)(m_files.buf[i]->table->buf[j].buf[0]),m_files.buf[i]);

	g_render->texload=1;

	if (load_tex_flag)
		load_all_textures();
}

bool pGUIObjectManager::destroy(unsigned int objhandle)
{
	pGUIObject *obj = m_objects.remove(objhandle);
	if (obj)
	{
		m_objects_str.remove(obj->m_name);
		deactivate(objhandle);
		delete obj;
		return true;
	}

	return false;
}

bool pGUIObjectManager::destroy(const char *stockobjname)
{
	pGUIObject *obj = m_objects_str.remove(stockobjname);
	if (obj)
	{
		m_objects.remove(obj->m_id);
		deactivate(obj->m_id);
		delete obj;
		return true;
	}

	return false;
}

bool pGUIObjectManager::pgo_destroy(const char *filename)
{
	int j,i=find_file(filename);
	if (i!=-1 && m_files.buf[i]->table)
	{
		for ( j=0;j<m_files.buf[i]->table->num;j++ )
			destroy((const char *)(m_files.buf[i]->table->buf[j].buf[0]));
		return true;
	}
	return false;
}

bool pGUIObjectManager::pgo_load_textures(pGUIObject *o,bool recurse_childs)
{
	if (o==0)
		return false;

	if (recurse_childs)
		for( int i=0;i<o->m_child.num;i++ )
			pgo_load_textures(o->m_child.buf[i],recurse_childs);

	pParamDesc pd;
	int k,n=o->get_common_param_desc(0,0);
	for ( k=0;k<n;k++ )
	{
		o->get_common_param_desc(k,&pd);
		switch(pd.type)
		{
			case 'p':
			{
				int *d=(int *)pd.data;
				g_render->tex_add_reference(*d);
			}
			break;
			case -'p':
			{
				pArray<int> *d=(pArray<int> *)pd.data;
				for( int ii=0;ii<d->num;ii++ )
					g_render->tex_add_reference(d->buf[ii]);
			}
			break;
			case 'm':
			{
				pMesh *m=*((pMesh **)pd.data);
				if (m)
				{
					for( int ii=0;ii<m->nmat;ii++)
					{
						g_render->tex_add_reference(m->mat[ii].texid);
						g_render->tex_add_reference(m->mat[ii].texnormalid);
						g_render->tex_add_reference(m->mat[ii].texselfillumid);
						for( int jj=0;jj<m->mat[ii].passes.num;jj++ )
							g_render->tex_add_reference(m->mat[ii].passes[jj].m_texid);
					}
				}
			}
			break;
			case -'m':
			{
				pArray<pMesh *> *d=(pArray<pMesh *> *)pd.data;
				for( int ii=0;ii<d->num;ii++ )
				{
					pMesh *m=d->buf[ii];
					if (m)
					{
						for( int jj=0;jj<m->nmat;jj++)
						{
							g_render->tex_add_reference(m->mat[jj].texid);
							g_render->tex_add_reference(m->mat[jj].texnormalid);
							g_render->tex_add_reference(m->mat[jj].texselfillumid);
							for( int kk=0;kk<m->mat[jj].passes.num;kk++ )
								g_render->tex_add_reference(m->mat[jj].passes[kk].m_texid);
						}
					}
				}
			}
			break;
		}
	}
	return true;
}

bool pGUIObjectManager::pgo_load_textures(const char *filename)
{
	int j,i=find_file(filename);
	if (i!=-1 && m_files.buf[i]->table && m_files.buf[i]->flag==0)
	{
		m_files.buf[i]->flag=1;
		for ( j=0;j<m_files.buf[i]->table->num;j++ )
		{
			pGUIObject *o=get_object((const char *)(m_files.buf[i]->table->buf[j].buf[0]));
			pgo_load_textures(o,false);
		}
		return true;
	}
	return false;
}

bool pGUIObjectManager::pgo_unload_textures(pGUIObject *o,bool recurse_childs)
{
	if (o==0)
		return false;

	if (recurse_childs)
		for( int i=0;i<o->m_child.num;i++ )
			pgo_unload_textures(o->m_child.buf[i],recurse_childs);

	pParamDesc pd;
	int k,n=o->get_common_param_desc(0,0);
	for ( k=0;k<n;k++ )
	{
		o->get_common_param_desc(k,&pd);
		switch(pd.type)
		{
			case 'p':
			{
				int *d=(int *)pd.data;
				g_render->tex_remove_reference(*d);
			}
			break;
			case -'p':
			{
				pArray<int> *d=(pArray<int> *)pd.data;
				for( int ii=0;ii<d->num;ii++ )
					g_render->tex_remove_reference(d->buf[ii]);
			}
			break;
			case 'm':
			{
				pMesh *m=*((pMesh **)pd.data);
				if (m)
				{
					for( int ii=0;ii<m->nmat;ii++)
					{
						g_render->tex_remove_reference(m->mat[ii].texid);
						g_render->tex_remove_reference(m->mat[ii].texnormalid);
						g_render->tex_remove_reference(m->mat[ii].texselfillumid);
						for( int jj=0;jj<m->mat[ii].passes.num;jj++ )
							g_render->tex_remove_reference(m->mat[ii].passes[jj].m_texid);
					}
				}
			}
			break;
			case -'m':
			{
				pArray<pMesh *> *d=(pArray<pMesh *> *)pd.data;
				for( int ii=0;ii<d->num;ii++ )
				{
					pMesh *m=d->buf[ii];
					if (m)
					{
						for( int jj=0;jj<m->nmat;jj++)
						{
							g_render->tex_remove_reference(m->mat[jj].texid);
							g_render->tex_remove_reference(m->mat[jj].texnormalid);
							g_render->tex_remove_reference(m->mat[jj].texselfillumid);
							for( int kk=0;kk<m->mat[jj].passes.num;kk++ )
								g_render->tex_remove_reference(m->mat[jj].passes[kk].m_texid);
						}
					}
				}
			}
			break;
		}
	}
	return true;
}

bool pGUIObjectManager::pgo_unload_textures(const char *filename)
{
	int j,i=find_file(filename);
	if (i!=-1 && m_files.buf[i]->table && m_files.buf[i]->flag==1)
	{
		m_files.buf[i]->flag=0;
		for ( j=0;j<m_files.buf[i]->table->num;j++ )
		{
			pGUIObject *o=get_object((const char *)(m_files.buf[i]->table->buf[j].buf[0]));
			pgo_unload_textures(o,false);
		}
		return true;
	}
	return false;
}

void pGUIObjectManager::load_all_textures()
{
	pString name;
	int i;
	for( i=0;i<m_files.num;i++ )
		pgo_load_textures(m_files.buf[i]->name.right(m_files.buf[i]->name.length()-g_render->app_path.length()));
}

void pGUIObjectManager::unload_all_textures()
{
	int i;
	for( i=0;i<m_files.num;i++ )
		pgo_unload_textures(m_files.buf[i]->name.right(m_files.buf[i]->name.length()-g_render->app_path.length()));
}

bool pGUIObjectManager::activate(unsigned int objhandle,pGUIEventHandler *eventhandler)
{
	pGUIObject *obj = m_objects.get_object(objhandle);
	if (obj)
	{
		m_objects_root.add(obj);
		m_eventhandler_root.add(eventhandler);
		obj->init();
		return true;
	}

	return false;
}

bool pGUIObjectManager::activate(const char* objname,pGUIEventHandler *eventhandler)
{
	pGUIObject *obj = m_objects_str.get_object(objname);
	if (obj)
		return activate(obj->m_id, eventhandler);

	return false;
}

bool pGUIObjectManager::activate_modal(unsigned int objhandle,pGUIEventHandler *eventhandler)
{
	if(m_input_focus) m_input_focus->on_kill_focus();
	m_input_focus=0;
	if(activate(objhandle,eventhandler))
	{
		m_objects.get_object(objhandle)->m_modal=1;
		return true;
	}

	return false;
}

bool pGUIObjectManager::activate_modal(const char* objname,pGUIEventHandler *eventhandler)
{
	if(m_input_focus) m_input_focus->on_kill_focus();
	m_input_focus=0;
	if(activate(objname,eventhandler))
	{
		m_objects_str.get_object(objname)->m_modal=1;
		return true;
	}

	return false;
}

bool pGUIObjectManager::deactivate(unsigned int objhandle)
{
	int i;
	for( i=0;i<m_objects_root.num;i++ )
		if (m_objects_root.buf[i]->m_id==objhandle)
		{
			if(m_objects_root.buf[i]==m_mouse_focus)
				m_mouse_focus=0;
			if(m_objects_root.buf[i]==m_mouse_drag_focus)
			{
				m_mouse_drag_focus=0;
				m_mouse_drag_focus_eh=NULL;
			}
			if(m_objects_root.buf[i]==m_input_focus)
				m_input_focus=0;
			
			m_objects_root.remove(i);
			m_eventhandler_root.remove(i);

			return true;
		}

	return false;
}

void pGUIObjectManager::post_deactivate(unsigned int objhandle)
{
	m_delete.add(objhandle);
}

void pGUIObjectManager::select_object(unsigned int objhandle)
{
	pGUIObject *obj=get_object(objhandle);
	if(obj)
		if(obj->m_parent==0)
		{
			for(int i=m_objects_root.num-1;i>=0;i--)
				if(m_objects_root[i]==obj)
				{
					pGUIEventHandler *e=m_eventhandler_root[i];
					m_eventhandler_root.remove(i);
					m_eventhandler_root.add(e);
					m_objects_root.remove(i);
					m_objects_root.add(obj);
					break;
				}
		}
		else
			select_object(obj->m_parent->m_id);
}

void pGUIObjectManager::select_object(const char* objname)
{
	pGUIObject *obj=m_objects_str.get_object(objname);
	if(obj)
		select_object(obj->m_id);
}

void pGUIObjectManager::bring_to_front(unsigned int objhandle)
{
	pGUIObject *obj=get_object(objhandle);
	if(obj)
		if(obj->m_parent)
		{
			for(int i=0;i<obj->m_parent->m_child.num;i++)
				if(obj->m_parent->m_child[i]==obj)
				{
					obj->m_parent->m_child.remove(i);
					obj->m_parent->m_child.add(obj);
					break;
				}
		}
		else
			select_object(objhandle);
}

void pGUIObjectManager::bring_to_front(const char* objname)
{
	pGUIObject *obj=m_objects_str.get_object(objname);
	if(obj)
		bring_to_front(obj->m_id);
}

bool pGUIObjectManager::set_event_handler(unsigned int objhandle,pGUIEventHandler *eventhandler)
{
	int i;
	for( i=0;i<m_objects_root.num;i++ )
		if (m_objects_root.buf[i]->m_id==objhandle)
		{
			m_eventhandler_root[i]=eventhandler;
			return true;
		}

	return false;
}

bool pGUIObjectManager::set_event_handler(const char* objname,pGUIEventHandler *eventhandler)
{
	pGUIObject *obj = m_objects_str.get_object(objname);
	if(obj)
		return set_event_handler(obj->m_id,eventhandler);

	return false;
}

pGUIEventHandler *pGUIObjectManager::get_event_handler(unsigned int objhandle)
{
	pGUIObject *obj=m_objects.get_object(objhandle);

	while(obj->m_parent)
		obj=obj->m_parent;

	for(int i=0;i<m_objects_root.num;i++)
		if(m_objects_root[i]==obj)
			return m_eventhandler_root[i];

	return 0;
}

bool pGUIObjectManager::set_object_param(unsigned int obj,const char *param,const char *value)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	int i,n;
	pParamDesc pd;
	n=o->get_common_param_desc(0,0);
	for( i=0;i<n;i++ )
	{
		o->get_common_param_desc(i,&pd);
		if (!_stricmp(pd.name,param))
			break;
	}
	if (i==n)
		return false;

	return set_object_param(obj,i,value);
}

bool pGUIObjectManager::set_object_param(unsigned int obj,int param,const char *value)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	pParamDesc pd;
	o->get_common_param_desc(param,&pd);

	o->on_pre_parameter_change(param);
	pd.set_string(value);
	o->on_pos_parameter_change(param);

	return true;
}

bool pGUIObjectManager::set_object_param(unsigned int obj,const char *param,const void *value)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	int i,n;
	pParamDesc pd;
	n=o->get_common_param_desc(0,0);
	for( i=0;i<n;i++ )
	{
		o->get_common_param_desc(i,&pd);
		if (!_stricmp(pd.name,param))
			break;
	}
	if (i==n)
		return false;

	return set_object_param(obj,i,value);
}

bool pGUIObjectManager::set_object_param(unsigned int obj,int param,const void *value)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	pParamDesc pd;
	o->get_common_param_desc(param,&pd);

	o->on_pre_parameter_change(param);
	pd.set_binary(value);
	o->on_pos_parameter_change(param);

	return true;
}

bool pGUIObjectManager::get_object_param(unsigned int obj,const char *param,pString& value)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	int i,n;
	pParamDesc pd;
	n=o->get_common_param_desc(0,0);
	for( i=0;i<n;i++ )
	{
		o->get_common_param_desc(i,&pd);
		if (!_stricmp(pd.name,param))
			break;
	}
	if (i==n)
		return false;

	value=pd.get_string();

	return true;
}

bool pGUIObjectManager::get_object_param(unsigned int obj,int param,pString& value)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	pParamDesc pd;
	o->get_common_param_desc(param,&pd);

	value=pd.get_string();

	return true;
}

bool pGUIObjectManager::get_object_param(unsigned int obj,const char *param,void *value)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	int i,n;
	pParamDesc pd;
	n=o->get_common_param_desc(0,0);
	for( i=0;i<n;i++ )
	{
		o->get_common_param_desc(i,&pd);
		if (!_stricmp(pd.name,param))
			break;
	}
	if (i==n)
		return false;

	pd.get_binary(value);

	return true;
}

bool pGUIObjectManager::get_object_param(unsigned int obj,int param,void *value)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	pParamDesc pd;
	o->get_common_param_desc(param,&pd);

	pd.get_binary(value);

	return true;
}

int pGUIObjectManager::get_object_param_id(unsigned int obj,const char *param)
{
	pGUIObject* o=m_objects.get_object(obj);
	if(o==0) 
		return -1;
	
	int i,n;
	pParamDesc pd;
	n=o->get_common_param_desc(0,0);
	for(i=0;i<n;i++)
	{
		o->get_common_param_desc(i,&pd);
		if(_stricmp(pd.name,param)==0)
			return i;
	}

	return -1;
}

bool pGUIObjectManager::set_param(unsigned int obj,const char *string,const char *value)
{
	pString str=string;
	int pos=str.find('.');
	if(pos==-1)
		return set_object_param(obj,string,value);

	pString chname=str.left(pos);
	pGUIObject *o=get_object(obj);
	if(o==0)
		return false;

	int i;
	for(i=0;i<o->m_child.num;i++)
		if(o->m_child[i]->m_name.compare((const char *)chname)==0)
		{
			chname=str.right(str.length()-pos-1);
			return set_param(o->m_child[i]->m_id,chname,value);
		}

	return false;
}

bool pGUIObjectManager::set_param(unsigned int obj,const char *string,const void *value)
{
	pString str=string;
	int pos=str.find('.');
	if(pos==-1)
		return set_object_param(obj,string,value);

	pString chname=str.left(pos);
	pGUIObject *o=get_object(obj);
	if(o==0)
		return false;

	int i;
	for(i=0;i<o->m_child.num;i++)
		if(o->m_child[i]->m_name.compare((const char *)chname)==0)
		{
			chname=str.right(str.length()-pos-1);
			return set_param(o->m_child[i]->m_id,chname,value);
		}

	return false;
}

bool pGUIObjectManager::get_param(unsigned int obj,const char *string,pString &value)
{
	pString str=string;
	int pos=str.find('.');
	if(pos==-1)
		return get_object_param(obj,string,value);

	pString chname=str.left(pos);
	pGUIObject *o=get_object(obj);
	if(o==0)
		return false;

	int i;
	for(i=0;i<o->m_child.num;i++)
		if(o->m_child[i]->m_name.compare((const char *)chname)==0)
		{
			chname=str.right(str.length()-pos-1);
			return get_param(o->m_child[i]->m_id,chname,value);
		}

	return false;
}

bool pGUIObjectManager::get_param(unsigned int obj,const char *string,void *value)
{
	pString str=string;
	int pos=str.find('.');
	if(pos==-1)
		return get_object_param(obj,string,value);

	pString chname=str.left(pos);
	pGUIObject *o=get_object(obj);
	if(o==0)
		return false;

	int i;
	for(i=0;i<o->m_child.num;i++)
		if(o->m_child[i]->m_name.compare((const char *)chname)==0)
		{
			chname=str.right(str.length()-pos-1);
			return get_param(o->m_child[i]->m_id,chname,value);
		}

	return false;
}

void pGUIObjectManager::do_mouse_input(int x,int y,unsigned int state)
{
	m_mouse_last_x=m_mouse_x;
	m_mouse_last_y=m_mouse_y;
	
	m_mouse_x=x;
	m_mouse_y=y;

	// clear clicks and unclicks flags
	m_mouse_state&=(P_GUI_MOUSESTATE_LEFTDOWN|P_GUI_MOUSESTATE_RIGHTDOWN|P_GUI_MOUSESTATE_MIDDLEDOWN);

	// calculates click or double-click state
	if((m_mouse_state&P_GUI_MOUSESTATE_LEFTDOWN)==0 && state&P_GUI_MOUSESTATE_LEFTDOWN)
	{
		if(m_click_flag[0])
		{
			m_mouse_state|=P_GUI_MOUSESTATE_LEFTCLICK;
			m_click_time[0]=m_time;
			m_click_flag[0]=false;
		}
		else
		{
			if(m_time-m_click_time[0]<m_double_click_time)
			{
				m_mouse_state|=P_GUI_MOUSESTATE_LEFTDCLICK;
				m_click_flag[0]=true;
			}
			else
			{
				m_mouse_state|=P_GUI_MOUSESTATE_LEFTCLICK;
				m_click_time[0]=m_time;
			}
		}
	}
	if((m_mouse_state&P_GUI_MOUSESTATE_RIGHTDOWN)==0 && state&P_GUI_MOUSESTATE_RIGHTDOWN)
	{
		if(m_click_flag[1])
		{
			m_mouse_state|=P_GUI_MOUSESTATE_RIGHTCLICK;
			m_click_time[1]=m_time;
			m_click_flag[1]=false;
		}
		else
		{
			if(m_time-m_click_time[1]<m_double_click_time)
			{
				m_mouse_state|=P_GUI_MOUSESTATE_RIGHTDCLICK;
				m_click_flag[1]=true;
			}
			else
			{
				m_mouse_state|=P_GUI_MOUSESTATE_RIGHTCLICK;
				m_click_time[1]=m_time;
			}
		}
	}
	if((m_mouse_state&P_GUI_MOUSESTATE_MIDDLEDOWN)==0 && state&P_GUI_MOUSESTATE_MIDDLEDOWN)
	{
		if(m_click_flag[2])
		{
			m_mouse_state|=P_GUI_MOUSESTATE_MIDDLECLICK;
			m_click_time[2]=m_time;
			m_click_flag[2]=false;
		}
		else
		{
			if(m_time-m_click_time[2]<m_double_click_time)
			{
				m_mouse_state|=P_GUI_MOUSESTATE_MIDDLEDCLICK;
				m_click_flag[2]=true;
			}
			else
			{
				m_mouse_state|=P_GUI_MOUSESTATE_MIDDLECLICK;
				m_click_time[2]=m_time;
			}
		}
	}

	// calculates unclick state
	if(m_mouse_state&P_GUI_MOUSESTATE_LEFTDOWN && (state&P_GUI_MOUSESTATE_LEFTDOWN)==0)
		m_mouse_state|=P_GUI_MOUSESTATE_LEFTUNCLICK;
	if(m_mouse_state&P_GUI_MOUSESTATE_RIGHTDOWN && (state&P_GUI_MOUSESTATE_RIGHTDOWN)==0)
		m_mouse_state|=P_GUI_MOUSESTATE_RIGHTUNCLICK;
	if(m_mouse_state&P_GUI_MOUSESTATE_MIDDLEDOWN && (state&P_GUI_MOUSESTATE_MIDDLEDOWN)==0)
		m_mouse_state|=P_GUI_MOUSESTATE_MIDDLEUNCLICK;

	// clear downs flags
	m_mouse_state&=~(P_GUI_MOUSESTATE_LEFTDOWN|P_GUI_MOUSESTATE_RIGHTDOWN|P_GUI_MOUSESTATE_MIDDLEDOWN);
	// update downs flags
	m_mouse_state|=state&(P_GUI_MOUSESTATE_LEFTDOWN|P_GUI_MOUSESTATE_RIGHTDOWN|P_GUI_MOUSESTATE_MIDDLEDOWN);

	pGUIObject *o=0;
	int i,j;
	
	for(i=m_objects_root.num-1;i>=0;i--) // find mouse-focused object
	{
		if( m_objects_root[i]->m_flags&P_GUIFLAGS_VISIBLE && 
			m_objects_root[i]->is_inside(m_mouse_x,m_mouse_y))
		{
			o=m_objects_root[i];

			for(j=0;j<o->m_child.num;j++)
				if(	o->m_child[j]->m_flags&P_GUIFLAGS_VISIBLE && 
					o->m_child[j]->is_inside(m_mouse_x,m_mouse_y))
				{
					o=o->m_child[j];
					j=-1;
				}

			break;
		}

		if(m_objects_root[i]->m_modal)
			break;
	}

	if(m_mouse_drag_focus && m_mouse_drag_focus_eh) // mouse dragging on
	{
		if(o && o->m_droppable)
		{
			m_droppable=m_eventhandler_root[i]->event_handler(P_GUI_MSG_DRAGOVER,o->m_id,m_mouse_drag_focus->m_id,0);
			m_mouse_drop_focus=o;
			m_mouse_drop_focus_eh=m_eventhandler_root[i];
		}

		// defines mouse cursor
		m_mouse_last_cursor=m_mouse_cursor;
		if(o==0 || m_droppable==0 || (o && o->m_droppable==0) || (o==m_mouse_drag_focus))
			m_mouse_cursor=(m_mouse_drag_focus->m_mouse_cursor_cannot_drop==-1)?m_mouse_cursor_cannot_drop:m_mouse_drag_focus->m_mouse_cursor_cannot_drop;
		else
			m_mouse_cursor=(m_mouse_drag_focus->m_mouse_cursor_can_drop==-1)?m_mouse_cursor_can_drop:m_mouse_drag_focus->m_mouse_cursor_can_drop;

		m_mouse_drag_focus->process_mouse_input(m_mouse_drag_focus_eh);
	}
	else if(o) // no mouse dragging, process input on mouse focus, if any
	{
		// general-purpose mouse events
		if(m_eventhandler_root[i])
		{
			if(m_mouse_state&P_GUI_MOUSESTATE_LEFTCLICK)
				m_eventhandler_root[i]->event_handler(P_GUI_MSG_LEFTMOUSEDOWN,o->m_id,0,0);
			if(m_mouse_state&P_GUI_MOUSESTATE_LEFTUNCLICK)
				m_eventhandler_root[i]->event_handler(P_GUI_MSG_LEFTMOUSEUP,o->m_id,0,0);
			if(m_mouse_state&P_GUI_MOUSESTATE_RIGHTCLICK)
				m_eventhandler_root[i]->event_handler(P_GUI_MSG_RIGHTMOUSEDOWN,o->m_id,0,0);
			if(m_mouse_state&P_GUI_MOUSESTATE_RIGHTUNCLICK)
				m_eventhandler_root[i]->event_handler(P_GUI_MSG_RIGHTMOUSEUP,o->m_id,0,0);
		}

		// pop-up
		if(m_mouse_state&P_GUI_MOUSESTATE_RIGHTUNCLICK)
		{
			pGUIObject *pop=o;
			while(pop && pop->m_popup==0)
				pop=pop->m_parent;

			if(pop)
			{
				if(m_input_focus) m_input_focus->on_kill_focus(); // call onkillfocus for the last focused object

				// no focus
				m_input_focus=NULL;

				if(m_eventhandler_root[i])
					m_eventhandler_root[i]->event_handler(P_GUI_MSG_POPUP,pop->m_id,0,0);
			}

			if(m_mouse_focus)
				m_mouse_focus->m_tooltip_flag=0;
			m_tooltip_mousefocus_time=g_render->curtimef;
		}
		else
		{
			if(m_mouse_focus!=o)
			{
				pGUIEventHandler *eh;
				if(m_mouse_focus)
				{
					m_mouse_focus->m_tooltip_flag=0;

					m_mouse_focus->on_kill_mouse(); // call onkillmouse for the last focused object
					eh=get_event_handler(m_mouse_focus->m_id);
					if(eh)
						eh->event_handler(P_GUI_MSG_MOUSEOUT,m_mouse_focus->m_id,0,0);
				}

				m_tooltip_mousefocus_time=g_render->curtimef;

				m_mouse_focus=o;
				m_mouse_focus->on_get_mouse();

				eh=get_event_handler(m_mouse_focus->m_id);
				if(eh)
					eh->event_handler(P_GUI_MSG_MOUSEIN,m_mouse_focus->m_id,0,0);
			}
			
/*			CODE MOVED TO STEP METHOD
			if(m_mouse_x!=m_mouse_last_x || m_mouse_y!=m_mouse_last_y)
				m_tooltip_mousefocus_time=g_render->curtimef;

			if(m_mouse_focus && m_mouse_focus->m_tooltip_flag!=1 && m_tooltip_mousefocus_time>0.0f && (g_render->curtimef-m_tooltip_mousefocus_time)>g_render->tooltip_delay)
			{
				m_mouse_focus->m_tooltip_flag=1;
				m_mouse_focus->m_tooltip_x=m_mouse_x;
				m_mouse_focus->m_tooltip_y=m_mouse_y;
			}
*/			
			if(m_mouse_state&P_GUI_MOUSESTATE_LEFTCLICK)
			{
				if(m_mouse_focus)
					m_mouse_focus->m_tooltip_flag=0;
				m_tooltip_mousefocus_time=-1.0f;

				if(o->m_clickable && m_input_focus!=o)
				{
					if(m_input_focus) m_input_focus->on_kill_focus(); // call onkillfocus for the last focused object

					// change focus
					m_input_focus=o;
					select_object(o->m_id);

					m_input_focus->on_get_focus(); // call ongetfocus for the newly focused object
				}
			}

			o->process_mouse_input(get_event_handler(o->m_id));
		}
	}
	else 
	{
		pGUIEventHandler *eh;
		if(m_mouse_focus)
		{
			m_mouse_focus->m_tooltip_flag=0;

			m_mouse_focus->on_kill_mouse(); // call onkillmouse for the last focused object
			eh=get_event_handler(m_mouse_focus->m_id);
			if(eh)
				eh->event_handler(P_GUI_MSG_MOUSEOUT,m_mouse_focus->m_id,0,0);
		}
		m_mouse_focus=0;

		// if no object has the focus, call onkillfocus for the last focused object
		if(m_mouse_state&P_GUI_MOUSESTATE_LEFTCLICK || m_mouse_state&P_GUI_MOUSESTATE_RIGHTCLICK)
		{
			if(m_input_focus) m_input_focus->on_kill_focus();
			m_input_focus=0;
		}
	}

	// mouse dragging config
	if(m_mouse_state&P_GUI_MOUSESTATE_LEFTDOWN)
	{
		m_mouse_drag_x=m_mouse_x-m_mouse_last_x;
		m_mouse_drag_y=m_mouse_y-m_mouse_last_y;
		// verifies if mouse is moving
		if(m_mouse_last_x!=m_mouse_x || m_mouse_last_y!=m_mouse_y)
		{
			if(m_mouse_drag_focus==0 && m_mouse_focus && m_mouse_focus->m_draggable)
			{
				m_mouse_drag_focus=m_mouse_focus;
				m_mouse_drag_focus_eh=m_eventhandler_root[i];
				m_mouse_drag_focus->on_begin_drag();
				if(m_mouse_drag_focus_eh)
					m_mouse_drag_focus_eh->event_handler(P_GUI_MSG_BEGINDRAG,m_mouse_drag_focus->m_id,0,0);
			}
		}
	}
	else
	{
		if(m_mouse_drag_focus && m_mouse_drag_focus_eh)
		{
			if(m_mouse_drop_focus && m_mouse_drop_focus_eh && m_droppable)
				m_mouse_drop_focus_eh->event_handler(P_GUI_MSG_DROP,m_mouse_drop_focus->m_id,m_mouse_drag_focus->m_id,0);

			m_mouse_drag_focus->on_end_drag();
			m_mouse_drag_focus_eh->event_handler(P_GUI_MSG_ENDDRAG,m_mouse_drag_focus->m_id,0,0);
		}

		// restores mouse_cursor;
		m_mouse_cursor=m_mouse_last_cursor;

		m_mouse_drag_x=0;
		m_mouse_drag_y=0;
		m_mouse_drag_focus=0;
		m_mouse_drag_focus_eh=NULL;
		m_droppable=0;
		m_mouse_drop_focus=0;
		m_mouse_drop_focus_eh=NULL;
		m_mouse_last_cursor=-1;
	}
}

void pGUIObjectManager::do_keyboard_input(int event,int keycode,int mod,int unicode)
{
	m_modkeys=mod;
	
	if(keycode==SDLK_RETURN)
		process_default_button(m_objects_root[m_objects_root.num-1],m_eventhandler_root[m_eventhandler_root.num-1]);
	else if(keycode==SDLK_ESCAPE)
		process_cancel_button(m_objects_root[m_objects_root.num-1],m_eventhandler_root[m_eventhandler_root.num-1]);
	else if(keycode==SDLK_TAB)
		if(mod&KMOD_SHIFT)
			process_tab_backward(m_objects_root[m_objects_root.num-1]);
		else
			process_tab_forward(m_objects_root[m_objects_root.num-1]);

	if(m_input_focus)
		m_input_focus->process_keyboard_input(keycode,mod,(unsigned char)unicode);
}



int pGUIObjectManager::process_default_button(pGUIObject *obj,pGUIEventHandler *eventhandler)
{
	if(obj==0)
		return 1;

	if(obj->m_flags&P_GUIFLAGS_ENABLED && obj->m_flags&P_GUIFLAGS_VISIBLE && obj->m_type==TYPE_GUI_BUTTON && ((pGUIButton*)obj)->m_default)
	{
		if(eventhandler)
			eventhandler->event_handler(P_GUI_MSG_BUTTONCLICK,obj->m_id,0,0);
		return 0;
	}

	int ret=1;
	for(int i=0;i<obj->m_child.num;i++)
	{
		if(obj->m_child[i]->m_flags&P_GUIFLAGS_ENABLED && obj->m_child[i]->m_flags&P_GUIFLAGS_VISIBLE)
		{
		ret=process_default_button(obj->m_child[i],eventhandler);
		if(ret==0)
			break;
	}
	}
		
	return ret;
}

int pGUIObjectManager::process_cancel_button(pGUIObject *obj,pGUIEventHandler *eventhandler)
{
	if(obj==0)
		return 1;

	if(obj->m_flags&P_GUIFLAGS_ENABLED && obj->m_flags&P_GUIFLAGS_VISIBLE && obj->m_type==TYPE_GUI_BUTTON && ((pGUIButton*)obj)->m_cancel)
	{
		if(eventhandler)
			eventhandler->event_handler(P_GUI_MSG_BUTTONCLICK,obj->m_id,0,0);
		return 0;
	}

	int ret=1;
	for(int i=0;i<obj->m_child.num;i++)
	{
		if(obj->m_child[i]->m_flags&P_GUIFLAGS_ENABLED && obj->m_child[i]->m_flags&P_GUIFLAGS_VISIBLE)
		{
		ret=process_cancel_button(obj->m_child[i],eventhandler);
		if(ret==0)
			break;
	}
	}
		
	return ret;
}


int pGUIObjectManager::process_tab_forward(pGUIObject *obj)
{
	int ret=process_tab_forward(obj,0);
	if(ret==0)
		return 0;
	if(ret==1)
		return process_tab_forward(obj,1)>0?1:0;

	return 1;
}



int pGUIObjectManager::process_tab_forward(pGUIObject *obj,int actionflag)
{
	if(obj==0)
		return 0;

	if(!(obj->m_flags&P_GUIFLAGS_ENABLED && obj->m_flags&P_GUIFLAGS_VISIBLE) || actionflag==2)
		return actionflag;

	if(actionflag==1 && obj->m_focusable)
	{
		if(m_input_focus) m_input_focus->on_kill_focus();

		m_input_focus=obj;
		select_object(obj->m_id);

		m_input_focus->on_get_focus();
		
		return 2;
	}

	if(obj==m_input_focus)
		if(actionflag==0)
			actionflag=1;
		else
			return 2;
	
	for(int i=0;i<obj->m_child.num;i++)
	{
		if(obj->m_child[i]->m_flags&P_GUIFLAGS_ENABLED && obj->m_child[i]->m_flags&P_GUIFLAGS_VISIBLE)
		{
			actionflag=process_tab_forward(obj->m_child[i],actionflag);
		if(actionflag==2)
			return 2;
	}
	}

	return actionflag;
}


int pGUIObjectManager::process_tab_backward(pGUIObject *obj)
{
	pGUIObject *new_obj=0;
	int ret=process_tab_backward(obj,new_obj,0);
	if(ret==1)
	{
		ret=process_tab_backward(obj,new_obj,1);
		if(new_obj)
		{
			if(m_input_focus) m_input_focus->on_kill_focus();

			m_input_focus=new_obj;
			select_object(new_obj->m_id);

			m_input_focus->on_get_focus();
		}
	}
	
	return ret;
}

int pGUIObjectManager::process_tab_backward(pGUIObject *obj,pGUIObject *&last_focusable,int actionflag)
{
	if(obj==0)
		return 0;

	if(!(obj->m_flags&P_GUIFLAGS_ENABLED && obj->m_flags&P_GUIFLAGS_VISIBLE))
	return actionflag;

	if(actionflag==0 && obj==m_input_focus)
	{
		if(last_focusable)
		{
			m_input_focus->on_kill_focus();

			m_input_focus=last_focusable;
			select_object(last_focusable->m_id);

			m_input_focus->on_get_focus();
			
			return 2;
		}
		else
			return 1;
	}
	else if(obj->m_focusable)
		last_focusable=obj;

	int ret=0;
	for(int i=0;i<obj->m_child.num;i++)
	{
		if(obj->m_child[i]->m_flags&P_GUIFLAGS_ENABLED && obj->m_child[i]->m_flags&P_GUIFLAGS_VISIBLE)
		{
			ret=process_tab_backward(obj->m_child[i],last_focusable,actionflag);
			if(ret>0)
				return ret;
		}
	}

	return ret;
}

void pGUIObjectManager::set_focus(const unsigned int objhandle)
{
	pGUIObject *o=get_object(objhandle);

	if(m_input_focus) m_input_focus->on_kill_focus();

	m_input_focus=o;
	select_object(o->m_id);

	m_input_focus->on_get_focus();
}

void pGUIObjectManager::step(float elapsed_time)
{
	// LOG
	if(g_render->logflag&P_LOG_ELAPSED_TIME_STEP)
		g_render->logreport.print_log(P_LOG_ELAPSED_TIME_STEP,"pGUIObjectManager Step %f\n",elapsed_time);

	int global_x=0,global_y=0;

	m_time+=elapsed_time;
	m_elapsed_time=elapsed_time;

	// calculates click or double-click state
	//if((m_time-m_click_elapsed_time[0])>m_double_click_time || (m_time-m_click_elapsed_time[1])>m_double_click_time || (m_time-m_click_elapsed_time[2])>m_double_click_time)
	//	do_mouse_input(m_mouse_x,m_mouse_y,m_mouse_state);

	// update
	int i;
	if(g_render->logflag&P_LOG_LAST_UPDATED_OBJ)
	{
		for(i=0;i<m_objects_root.num;i++)
			if(m_objects_root.buf[i]->m_flags&P_GUIFLAGS_ENABLED)
			{
				g_render->logreport.print_log(P_LOG_LAST_UPDATED_OBJ,"Last updated object: %s \n",(const char *)(m_objects_root.buf[i]->m_name));
				m_objects_root.buf[i]->step(elapsed_time,global_x,global_y);
			}
	}
	else
	{
		for(i=0;i<m_objects_root.num;i++)
			if(m_objects_root.buf[i]->m_flags&P_GUIFLAGS_ENABLED)
				m_objects_root.buf[i]->step(elapsed_time,global_x,global_y);
	}

	// requisitions for hotspots
	for(i=0;i<m_req_hotspot.num;i++)
	{
		m_req_hotspot.buf[i].obj->on_pre_parameter_change(3);
		m_req_hotspot.buf[i].obj->m_pos_x+=m_req_hotspot.buf[i].pos_x-(m_req_hotspot.buf[i].obj->m_global_x+m_req_hotspot.buf[i].obj->m_hotspot_x);
		m_req_hotspot.buf[i].obj->on_pos_parameter_change(3);
		m_req_hotspot.buf[i].obj->on_pre_parameter_change(4);
		m_req_hotspot.buf[i].obj->m_pos_y+=m_req_hotspot.buf[i].pos_y-(m_req_hotspot.buf[i].obj->m_global_y+m_req_hotspot.buf[i].obj->m_hotspot_y);
		m_req_hotspot.buf[i].obj->on_pos_parameter_change(4);
	}
	m_req_hotspot.clear();

	// requisitions for place objects in the center
	for(i=0;i<m_req_center.num;i++)
	{
		m_req_center.buf[i].obj->on_pre_parameter_change(3);
		m_req_center.buf[i].obj->m_pos_x+=m_req_center.buf[i].center_pos_x-(m_req_center.buf[i].obj->m_global_x+m_req_center.buf[i].obj->m_width/2);
		m_req_center.buf[i].obj->on_pos_parameter_change(3);
		m_req_center.buf[i].obj->on_pre_parameter_change(4);
		m_req_center.buf[i].obj->m_pos_y+=m_req_center.buf[i].center_pos_y-(m_req_center.buf[i].obj->m_global_y+m_req_center.buf[i].obj->m_height/2);
		m_req_center.buf[i].obj->on_pos_parameter_change(4);
	}
	m_req_center.clear();

	// CODE MOVED FROM DO_MOUSE_INPUT METHOD
	if(m_mouse_x!=m_mouse_last_x || m_mouse_y!=m_mouse_last_y)
		m_tooltip_mousefocus_time=g_render->curtimef;

	if(m_mouse_focus && m_mouse_focus->m_tooltip_flag!=1 && m_tooltip_mousefocus_time>0.0f && (g_render->curtimef-m_tooltip_mousefocus_time)>g_render->tooltip_delay)
	{
		m_mouse_focus->m_tooltip_flag=1;
		m_mouse_focus->m_tooltip_x=m_mouse_x;
		m_mouse_focus->m_tooltip_y=m_mouse_y;
	}
	//
			
	pGUIObject *o;
	for(i=0;i<m_delete.num;i++)
	{
		o=get_object(m_delete.buf[i]);
		if(o)
		{
			if(o->m_parent)
			{
				for(int j=0;j<o->m_parent->m_child.num;j++)
					if (o->m_parent->m_child.buf[j]==o)
					{
						o->m_parent->m_child.remove(j);
						break;
					}
			}
			deactivate(m_delete.buf[i]);
		}
	}
	m_delete.clear();
}

void pGUIObjectManager::draw()
{
	// LOG
	if(g_render->logflag&P_LOG_VISIBLE_OBJS)
		g_render->logreport.print_log(P_LOG_VISIBLE_OBJS,"pGUIObjectManager Draw %i \n",m_objects_root.num);

#ifndef P_DISABLE_3D
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_SCISSOR_TEST);
	
	// to do scrolling
	glPushMatrix();
	glTranslatef((float)m_translate_x,(float)m_translate_y,0.0f);

	pRect r;
	if(g_render->logflag&P_LOG_LAST_DRAWN_OBJ)
	{
		for(int i=0;i<m_objects_root.num;i++)
			if(m_objects_root.buf[i]->m_flags&P_GUIFLAGS_VISIBLE)
			{
				r.m_translate_x=m_translate_x; // to do scrolling of scissors
				r.m_translate_y=m_translate_y; // to do scrolling of scissors
				r.m_x=m_objects_root.buf[i]->m_global_x+r.m_translate_x;
				r.m_y=m_objects_root.buf[i]->m_global_y+r.m_translate_y;
				r.m_width=m_objects_root.buf[i]->m_width;
				r.m_height=m_objects_root.buf[i]->m_height;

				glScissor(r.m_x,g_render->sizey-(r.m_y+r.m_height),r.m_width,r.m_height);
				g_render->logreport.print_log(P_LOG_LAST_DRAWN_OBJ,"Last drawn object: %s \n",(const char *)(m_objects_root.buf[i]->m_name));
				m_objects_root.buf[i]->draw(r);
			}
	}
	else
	{
		for(int i=0;i<m_objects_root.num;i++)
			if(m_objects_root.buf[i]->m_flags&P_GUIFLAGS_VISIBLE)
			{
				r.m_translate_x=m_translate_x; // to do scrolling of scissors
				r.m_translate_y=m_translate_y; // to do scrolling of scissors
				r.m_x=m_objects_root.buf[i]->m_global_x+r.m_translate_x;
				r.m_y=m_objects_root.buf[i]->m_global_y+r.m_translate_y;
				r.m_width=m_objects_root.buf[i]->m_width;
				r.m_height=m_objects_root.buf[i]->m_height;

				glScissor(r.m_x,g_render->sizey-(r.m_y+r.m_height),r.m_width,r.m_height);
				m_objects_root.buf[i]->draw(r);
			}
	}
	glDisable(GL_SCISSOR_TEST);
	
	// to do scrolling
	glPopMatrix();

	int cursor=m_mouse_cursor;
	if (m_mouse_focus && m_mouse_focus->m_mouse_cursor!=-1)
		cursor=m_mouse_focus->m_mouse_cursor;
	if (cursor!=-1 && g_render->pic[cursor])
	{
		int sizex=g_render->pic[cursor]->sx;
		int sizey=g_render->pic[cursor]->sy;
		int posx=m_mouse_x-sizex/2;
		int posy=m_mouse_y-sizey/2;

		glColor4f(1.0f,1.0f,1.0f,1.0f);
		g_render->sel_tex(cursor);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		
		//*glBegin(GL_QUADS);
			glTexCoord2i(0,1);
			glVertex2i(posx,posy);
			glTexCoord2i(0,0);
			glVertex2i(posx,posy+sizey);
			glTexCoord2i(1,0);
			glVertex2i(posx+sizex,posy+sizey);
			glTexCoord2i(1,1);
			glVertex2i(posx+sizex,posy);
		//*glEnd();
	}
#endif
}

pGUIObject *pGUIObjectManager::get_object(const unsigned int id)
{
	return m_objects.get_object(id); 
}

pGUIObject *pGUIObjectManager::get_object(const char *objname)
{ 
	pGUIObject *o=m_objects_str.get_object(objname);	
	if (!o)
		return get_object(create(objname));

	return o;
}

int pGUIObjectManager::get_object_id(const char *objname)
{
	pGUIObject *o=m_objects_str.get_object(objname);	
	if (o)
		return o->m_id;

	return 0;
}

bool pGUIObjectManager::get_object_name(unsigned int obj,pString &name)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;

	name=o->m_name;
	return true;
}

bool pGUIObjectManager::set_object_flags(unsigned obj,const unsigned int flags)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	// LOG
	if(g_render->logflag&P_LOG_SET_OBJ_FLAGS)
		g_render->logreport.print_log(P_LOG_SET_OBJ_FLAGS,"pGUIObjectManager SetFlags %s %u\n",(const char *)o->m_name,flags);

	o->on_pre_parameter_change(1);
	o->m_flags=flags;
	o->on_pos_parameter_change(1);
	return true;
}

bool pGUIObjectManager::get_object_flags(unsigned obj,unsigned int& flags)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	flags=o->m_flags;
	return true;
}

bool pGUIObjectManager::set_object_transform(unsigned int obj,const int pos_x,const int pos_y)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;
	
	// LOG
	if(g_render->logflag&P_LOG_SET_OBJ_TRANSFORM)
		g_render->logreport.print_log(P_LOG_SET_OBJ_TRANSFORM,"pGUIObjectManager SetTransform %s %f %f\n",(const char *)o->m_name,pos_x,pos_y);

	o->on_pre_parameter_change(3);
	o->m_pos_x=pos_x;
	o->on_pos_parameter_change(3);
	o->on_pre_parameter_change(4);
	o->m_pos_y=pos_y;
	o->on_pos_parameter_change(4);
	return true;
}

bool pGUIObjectManager::get_object_transform(unsigned int obj,int &pos_x,int &pos_y)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;

	pos_x=o->m_pos_x;
	pos_y=o->m_pos_y;
	return true;
}

bool pGUIObjectManager::set_object_center(unsigned int obj,const int center_pos_x,const int center_pos_y)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;

	pObjCenterInfo objcenter={center_pos_x,center_pos_y,o};
	m_req_center.add(objcenter);
	
	/*o->on_pre_parameter_change(3);
	o->m_pos_x+=center_pos_x-(o->m_global_x+o->m_width/2);
	o->on_pos_parameter_change(3);
	o->on_pre_parameter_change(4);
	o->m_pos_y+=center_pos_y-(o->m_global_y+o->m_height/2);
	o->on_pos_parameter_change(4);*/
	return true;
}

bool pGUIObjectManager::get_object_center(unsigned int obj,int &center_pos_x,int &center_pos_y)
{
	pGUIObject* o=m_objects.get_object(obj);
		if (o==0) 
		return false;

	center_pos_x=o->m_global_x+o->m_width/2;
	center_pos_y=o->m_global_y+o->m_height/2;
	return true;
}

bool pGUIObjectManager::position_hotspot(unsigned int obj,int pos_x,int pos_y)
{
	pGUIObject* o=m_objects.get_object(obj);
	if (o==0) 
		return false;

	pHotspotInfo hotspot={pos_x,pos_y,o};
	m_req_hotspot.add(hotspot);
	
	/*o->on_pre_parameter_change(3);
	o->m_pos_x+=pos_x-(o->m_global_x+o->m_hotspot_x);
	o->on_pos_parameter_change(3);
	o->on_pre_parameter_change(4);
	o->m_pos_y+=pos_y-(o->m_global_y+o->m_hotspot_y);
	o->on_pos_parameter_change(4);*/
	return true;
}

bool pGUIObjectManager::check_reference(pGUIObject *o,pGUIObject *ref)
{
	if (o==ref)
		return true;
	
	int i;
	for( i=0;i<o->m_child.num;i++ )
		if (check_reference(o->m_child.buf[i],ref))
			return true;

	return false;
}

void pGUIObjectManager::attach_objects(unsigned int parent,unsigned int child,int x,int y)
{
	pGUIObject *p=get_object(parent);
	pGUIObject *c=get_object(child);

	if(p&&c)
	{
		c->m_pos_x=x;
		c->m_pos_y=y;

		if(c->m_parent)
		{
			for(int i=0;i<c->m_parent->m_child.num;i++)
			{
				if(c->m_parent->m_child[i]==c)
				{
					c->m_parent->m_child.remove(i);
					break;
				}
			}
		}

		c->m_parent=p;
		p->m_child.add(c);
	}
}

void pGUIObjectManager::attach_objects_radial(unsigned int parent,unsigned int child,int radius,float angle)
{
	pGUIObject *p=get_object(parent);
	pGUIObject *c=get_object(child);

	if(p&&c)
	{
		int centerx=(int)(p->m_width/2.0f);
		int centery=(int)(p->m_height/2.0f);
		
		float anglerad=angle*PIOVER180;
		centerx+=(int)(radius*sinf(anglerad));
		centery+=(int)(-radius*cosf(anglerad));

		c->m_pos_x=centerx-(int)(c->m_width/2.0f);
		c->m_pos_y=centery-(int)(c->m_height/2.0f);

		if(c->m_parent)
		{
			for(int i=0;i<c->m_parent->m_child.num;i++)
			{
				if(c->m_parent->m_child[i]==c)
				{
					c->m_parent->m_child.remove(i);
					break;
				}
			}
		}

		c->m_parent=p;
		p->m_child.add(c);
	}
}

void pGUIObjectManager::set_mouse_cursor(const char *cursor_file_name)
{
	if (cursor_file_name==0 || cursor_file_name[0]==0)
		m_mouse_cursor=-1;
	else
		m_mouse_cursor=g_render->load_tex(cursor_file_name,0,1);
}

void pGUIObjectManager::set_mouse_cursor_can_drop(const char *cursor_file_name)
{
	if (cursor_file_name==0 || cursor_file_name[0]==0)
		m_mouse_cursor_can_drop=-1;
	else
		m_mouse_cursor_can_drop=g_render->load_tex(cursor_file_name,0,1);
}

void pGUIObjectManager::set_mouse_cursor_cannot_drop(const char *cursor_file_name)
{
	if (cursor_file_name==0 || cursor_file_name[0]==0)
		m_mouse_cursor_cannot_drop=-1;
	else
		m_mouse_cursor_cannot_drop=g_render->load_tex(cursor_file_name,0,1);
}

unsigned int pGUIObjectManager::duplicate(unsigned int obj)
{
	pGUIObject *o=m_objects.get_object(obj);
	if(o==0) 
		return 0;

	pClassDesc *cd=g_gomanager->m_factory.buf[P_GUITYPE2FACTORYID(o->m_type)];
	if(cd==0)
		return 0;

	pGUIObject *new_o=o->clone();

	// find a valid name for the new object
	int obj_count=0;
	pString obj_name;
	do
		obj_name.format("%s%i",cd->get_name(),obj_count++);
	while(get_object(obj_name)!=0);

	// rename the new object
	new_o->m_name = obj_name;

	// insert new object into manager
	m_objcount++;
	m_objects.add(m_objcount,new_o);
	m_objects_str.add(new_o->m_name,new_o);
	new_o->m_id=m_objcount;

	int n=o->m_child.num;
	for(int i=0;i<n;i++)
		new_o->m_child[i]=get_object(duplicate(o->m_child[i]->m_id));

	return new_o->m_id;
}

float pGUIObjectManager::get_angle_2d(float x,float y)
{
	float len=x*x+y*y;
	if (len<0.001f)
		return 0.0f;

	len=1.0f/sqrtf(len);
	x*=len;
	y*=len;

	float ang=acosf(-y)*PIUNDER180;
	if(x>0)
		return ang;
	return 360-ang;
}

void pGUIObjectManager::update_vbo()
{
	pGUIObject *obj=m_objects.get_next_object(1);
	while(obj)
	{
		obj->update_vbo();
		obj=m_objects.get_next_object();
	}
}

#ifdef _DEBUG
void pGUIObjectManager::debugPrintRoots(FILE *fp)
{
	for(int i=0;i<m_objects_root.num;i++)
		debugPrint(fp,m_objects_root[i]);
}

void pGUIObjectManager::debugPrint(FILE *fp,pGUIObject *o,int tab)
{
	if(o)
	{
		for(int i=0;i<tab;i++)
			fprintf(fp,"\t");
		fprintf(fp,"%s\n",(const char *)o->m_name);

		for(int i=0;i<o->m_child.num;i++)
			debugPrint(fp,o->m_child[i],tab+1);
	}
}
#endif

#endif
