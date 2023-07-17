#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

P3D_API pRenderObjectManager *get_ro_manager()
{
	return g_romanager;
}

pRenderObjectManager::pRenderObjectManager()
{
	m_time=0;
	m_elapsed_time=0;
	m_objcount_stock=0;
	m_objcount_active=(unsigned int)-1;
	m_curr_ro_camera=0;
	m_factory.add(new pROBillboard_desc);
	m_factory.add(new pROCamera_desc);
	m_factory.add(new pROExplosion_desc);
	m_factory.add(new pROExplodeObject_desc);
	m_factory.add(new pROGroup_desc);
	m_factory.add(new pROLensFlare_desc);
	m_factory.add(new pROLight_desc);
	m_factory.add(new pROMesh_desc);
	m_factory.add(new pROMeshHuge_desc);
	m_factory.add(new pROMeshLOD_desc);
	m_factory.add(new pROMeshRelief_desc);
	m_factory.add(new pROMeshSkeleton_desc);
	m_factory.add(new pROMeshTeapot_desc);
	m_factory.add(new pROObfuscatingPoint_desc);
	m_factory.add(new pROPanorama_desc);
	m_factory.add(new pROParticleSystem_desc);
	//*m_factory.add(new pROParticleSystemGPU_desc);
	m_factory.add(new pROProjectile_desc);
	m_factory.add(new pRORotor_desc);
#ifdef P_SOUND
	m_factory.add(new pROSound_desc);
#endif
	m_factory.add(new pROSpaceDust_desc);
	m_factory.add(new pROTrail_desc);
}

pRenderObjectManager::~pRenderObjectManager()
{
#ifdef P_SOUND
	delete g_soundmanager;
#endif
	// free factory
	for( int i=0;i<m_factory.num;i++ )
		delete m_factory[i];
	// free objects
	reset();
}

void pRenderObjectManager::reset()
{
	pRenderObject *o;
	m_objcount_stock=0;
	m_objcount_active=(unsigned int)-1;
	m_time=0;
	m_curr_ro_camera=0;
	
	// free stock
	o = m_stock.get_next_object(1);
	do delete o;
	while(o = m_stock.get_next_object());
	m_stock.reset();
	m_stock_str.reset();

	// free active
	o = m_active.get_next_object(1);
	do delete o;
	while(o = m_active.get_next_object());
	m_active.reset();
	m_active_root.free();
	m_active_visible.free();
	m_active_visible_transp.free();
	m_active_visible_postdraw.free();
	m_active_visible_draw2d.free();

	// free files
	pro_clear();
}

bool pRenderObjectManager::pro_load(const char* filename)
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

int pRenderObjectManager::find_file(const char *filename) const
{
	pString s=g_render->app_path+filename;

	int i;
	for( i=0;i<m_files.num;i++ )
		if (m_files.buf[i]->name==s)
			return i;

	return -1;
}

bool pRenderObjectManager::pro_unload(const char* filename)
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

void pRenderObjectManager::pro_clear()
{
	int i;
	for( i=0;i<m_files.num;i++ )
		delete m_files.buf[i];
	m_files.free();
}

int pro_compare(const void *arg1,const void *arg2)
{
	pRenderObject *obj1=*((pRenderObject **)arg1);
	pRenderObject *obj2=*((pRenderObject **)arg2);
	return obj1->m_name.compare_nocase((const char *)obj2->m_name);
}

bool pRenderObjectManager::pro_save(const char* filename)
{
	FILE *fp = fopen(filename, "wt");

	if (!fp)
		return false;

	// stores objects from stock to local array
	pArray<pRenderObject *> ro_objects;
	pRenderObject *obj=m_stock.get_next_object(1);
	while(obj)
	{
		ro_objects.add(obj);
		obj=m_stock.get_next_object();
	}

	// order objects by name
	qsort(ro_objects.buf,(size_t)(ro_objects.num),sizeof(pRenderObject *),pro_compare);

	// save objects into a file
	int n;
	pString val,def;
	pParamDesc pd;
	pClassDesc *cd;
	pRenderObject *o;
	for(int j=0;j<ro_objects.num;j++)
	{
		cd=m_factory.buf[P_ROTYPE2FACTORYID(ro_objects[j]->m_type)];
		o=(pRenderObject *)cd->create();
		o->m_source=ro_objects[j];

		// write section
		fprintf(fp, "[%s]\n", (const char *)ro_objects[j]->m_name);
		fprintf(fp, "classtype=%s\n", cd->get_name());

		// write parameters
		n = ro_objects[j]->get_common_param_desc(0, 0);
		for(int i=0;i<n;i++)
		{
			o->get_common_param_desc(i, &pd);
			def = pd.get_string();
			ro_objects[j]->get_common_param_desc(i, &pd);
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

unsigned int pRenderObjectManager::create(const char *objname,pFile *f)
{
	// test if this object already exist
	if (m_stock_str.get_object(objname))
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
	for (i = 0; i < m_factory.num; i++){
		if (_stricmp(m_factory.buf[i]->get_name(), (const char *)str) == 0)
			break;
	}
	if (i == m_factory.num)
		return 0;
	cd = m_factory.buf[i];

	// create correspondent object
	pRenderObject* obj = (pRenderObject *)cd->create();

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
	m_objcount_stock+=2;
	m_stock.add(m_objcount_stock, obj);
	m_stock_str.add(objname, obj);

	obj->m_id = m_objcount_stock;
	obj->init(0);//obj->source!=0);

	return m_objcount_stock;
}

unsigned int pRenderObjectManager::create(const char *objname,const char *filename)
{
	// verifies if file exist
	int i=find_file(filename);
	if (i!=-1)
		return create(objname,m_files.buf[i]);
	return 0;
}

bool pRenderObjectManager::pro_create(const char *filename, bool load_tex_flag)
{
	int j,i=find_file(filename);
	if (i!=-1 && m_files.buf[i]->table)
	{
		g_render->texload=0;
		
		for ( j=0;j<m_files.buf[i]->table->num;j++ )
			create((const char *)(m_files.buf[i]->table->buf[j].buf[0]));

		g_render->texload=1;

		if (load_tex_flag)
			pro_load_textures(filename);

		return true;
	}
	return false;
}

void pRenderObjectManager::create_all(bool load_tex_flag)
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

bool pRenderObjectManager::destroy(unsigned int stockobj)
{
	pRenderObject *obj = m_stock.remove(stockobj);

	if (obj)
	{
		m_stock_str.remove(obj->m_name);

		// verifies if exist an active object whose source==stockobj
		pRenderObject *active_obj = m_active.get_next_object(1);
		while(active_obj) 
		{
			if(active_obj->m_source==obj)
				deactivate(active_obj->m_id);
			active_obj=m_active.get_next_object();
		}

		delete obj;
		return true;
	}

	return false;
}

bool pRenderObjectManager::destroy(const char *stockobjname)
{
	pRenderObject *obj = m_stock_str.remove(stockobjname);

	if (obj)
	{
		m_stock.remove(obj->m_id);

		// verifies if exist an active object whose source==stockobj
		pRenderObject *active_obj = m_active.get_next_object(1);
		while(active_obj) 
		{
			if(active_obj->m_source==obj)
				deactivate(active_obj->m_id);
			active_obj=m_active.get_next_object();
		}

		delete obj;
		return true;
	}

	return false;
}

bool pRenderObjectManager::pro_destroy(const char *filename)
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

bool pRenderObjectManager::pro_load_textures(pRenderObject *o,bool recurse_childs)
{
	if (o==0 || (o->m_id&1)==1)
		return false;

	if (recurse_childs)
		for( int i=0;i<o->m_child.num;i++ )
			pro_load_textures(o->m_child.buf[i],recurse_childs);
		
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
			case 'k':
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
			case -'k':
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

bool pRenderObjectManager::pro_load_textures(const char *filename)
{
	int j,i=find_file(filename);
	if (i!=-1 && m_files.buf[i]->table && m_files.buf[i]->flag==0)
	{
		m_files.buf[i]->flag=1;
		for ( j=0;j<m_files.buf[i]->table->num;j++ )
		{
			pRenderObject *o=get_object((const char *)(m_files.buf[i]->table->buf[j].buf[0]));
			pro_load_textures(o,false);

		}
		return true;
	}
	return false;
}

bool pRenderObjectManager::pro_unload_textures(pRenderObject *o,bool recurse_childs)
{
	if (o==0 || (o->m_id&1)==1)
		return false;

	if (recurse_childs)
		for( int i=0;i<o->m_child.num;i++ )
			pro_unload_textures(o->m_child.buf[i],recurse_childs);

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
			case 'k':
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
			case -'k':
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

bool pRenderObjectManager::pro_unload_textures(const char *filename)
{
	int j,i=find_file(filename);
	if (i!=-1 && m_files.buf[i]->table && m_files.buf[i]->flag==1)
	{
		m_files.buf[i]->flag=0;
		for ( j=0;j<m_files.buf[i]->table->num;j++ )
		{
			pRenderObject *o=get_object((const char *)(m_files.buf[i]->table->buf[j].buf[0]));
			pro_unload_textures(o,false);
		}
		return true;
	}
	return false;
}

void pRenderObjectManager::load_all_textures()
{
	pString name;
	int i;
	for( i=0;i<m_files.num;i++ )
		pro_load_textures(m_files.buf[i]->name.right(m_files.buf[i]->name.length()-g_render->app_path.length()));
}

void pRenderObjectManager::unload_all_textures()
{
	int i;
	for( i=0;i<m_files.num;i++ )
		pro_unload_textures(m_files.buf[i]->name.right(m_files.buf[i]->name.length()-g_render->app_path.length()));
}

unsigned int pRenderObjectManager::activate(unsigned int stockobj,bool addToRoot)
{
	pRenderObject *o,*obj = m_stock.get_object(stockobj);

	if (obj)
	{
		o = obj->clone();
		m_objcount_active+=2;
		m_active.add(m_objcount_active,o);
		o->m_id = m_objcount_active;

		if (addToRoot)
			m_active_root.add(o);

		int i,j;
		// activate children
		for (i = 0; i < o->m_child.num; i++)
		{
			j = activate(o->m_child.buf[i]->m_id,0);
			o->m_child.buf[i] = m_active.get_object(j);
			o->m_child.buf[i]->m_parent = o;
		}

		o->init(1);//obj->source!=0);
		return o->m_id;
	}

	return 0;
}

unsigned int pRenderObjectManager::activate(const char* stockobjname,bool addToRoot)
{
	pRenderObject *obj = m_stock_str.get_object(stockobjname);
	if (obj)
		return activate(obj->m_id, addToRoot);

	return 0;
}

bool pRenderObjectManager::deactivate(unsigned int activeobj)
{
	pRenderObject *obj = m_active.remove(activeobj);
	
	if (obj)
	{
		if (obj->m_parent==0)
		{
			for( int i=0;i<m_active_root.num;i++ )
				if (m_active_root.buf[i]==obj)
				{
					m_active_root.remove(i);
					break;
				}
		}

		// free memory of children
		for (int i = 0; i < obj->m_child.num; i++)
			deactivate(obj->m_child.buf[i]->m_id);

		delete obj;
		return true;
	}

	return false;
}

bool pRenderObjectManager::set_object_param(unsigned int obj,const char *param,const char *value)
{
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
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

bool pRenderObjectManager::set_object_param(unsigned int obj,int param,const char *value)
{
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
	if (o==0) 
		return false;
	
	pParamDesc pd;
	o->get_common_param_desc(param,&pd);

	o->on_pre_parameter_change(param);
	pd.set_string(value);
	o->on_pos_parameter_change(param);

	if ((obj&1)==0)
	{
		pRenderObject *ao=m_active.get_next_object(1);
		while(ao)
		{
			if (ao->m_source==o)
			{
				ao->get_common_param_desc(param,&pd);
				ao->on_pre_parameter_change(param);
				pd.set_string(value);
				ao->on_pos_parameter_change(param);
			}
			ao=m_active.get_next_object();
		}
	}

	return true;
}

bool pRenderObjectManager::set_object_param(unsigned int obj,const char *param,const void *value)
{
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
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

bool pRenderObjectManager::set_object_param(unsigned int obj,int param,const void *value)
{
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
	if (o==0) 
		return false;
	
	pParamDesc pd;
	o->get_common_param_desc(param,&pd);

	o->on_pre_parameter_change(param);
	pd.set_binary(value);
	o->on_pos_parameter_change(param);

	if ((obj&1)==0)
	{
		pRenderObject *ao=m_active.get_next_object(1);
		while(ao)
		{
			if (ao->m_source==o)
			{
				ao->get_common_param_desc(param,&pd);
				ao->on_pre_parameter_change(param);
				pd.set_binary(value);
				ao->on_pos_parameter_change(param);
			}
			ao=m_active.get_next_object();
		}
	}

	return true;
}

bool pRenderObjectManager::get_object_param(unsigned int obj,const char *param,pString& value)
{
	value="";
	
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
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

bool pRenderObjectManager::get_object_param(unsigned int obj,int param,pString& value)
{
	value="";
	
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
	if (o==0) 
		return false;
	
	pParamDesc pd;
	o->get_common_param_desc(param,&pd);

	value=pd.get_string();

	return true;
}

bool pRenderObjectManager::get_object_param(unsigned int obj,const char *param,void *value)
{
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
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

bool pRenderObjectManager::get_object_param(unsigned int obj,int param,void *value)
{
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
	if (o==0) 
		return false;
	
	pParamDesc pd;
	o->get_common_param_desc(param,&pd);

	pd.get_binary(value);

	return true;
}

bool pRenderObjectManager::set_param(unsigned int obj,const pString &string,const char *value)
{
	int pos=string.find('.');
	if(pos==-1)
		return set_object_param(obj,(const char *)string,value);

	pString chname=string.left(pos);
	pRenderObject *o=get_object(obj);
	if(o==0)
		return false;

	int i;
	for(i=0;i<o->m_child.num;i++)
		if(o->m_child[i]->m_name.compare((const char *)chname)==0)
		{
			chname=string.right(string.length()-pos-1);
			return set_param(o->m_child[i]->m_id,chname,value);
		}

	return false;
}

bool pRenderObjectManager::set_param(unsigned int obj,const pString &string,const void *value)
{
	int pos=string.find('.');
	if(pos==-1)
		return set_object_param(obj,(const char *)string,value);

	pString chname=string.left(pos);
	pRenderObject *o=get_object(obj);
	if(o==0)
		return false;

	int i;
	for(i=0;i<o->m_child.num;i++)
		if(o->m_child[i]->m_name.compare((const char *)chname)==0)
		{
			chname=string.right(string.length()-pos-1);
			return set_param(o->m_child[i]->m_id,chname,value);
		}

	return false;
}

bool pRenderObjectManager::get_param(unsigned int obj,const pString &string,pString &value)
{
	int pos=string.find('.');
	if(pos==-1)
		return get_object_param(obj,(const char *)string,value);

	pString chname=string.left(pos);
	pRenderObject *o=get_object(obj);
	if(o==0)
		return false;

	int i;
	for(i=0;i<o->m_child.num;i++)
		if(o->m_child[i]->m_name.compare((const char *)chname)==0)
		{
			chname=string.right(string.length()-pos-1);
			return get_param(o->m_child[i]->m_id,chname,value);
		}

	return false;
}

bool pRenderObjectManager::get_param(unsigned int obj,const pString &string,void *value)
{
	int pos=string.find('.');
	if(pos==-1)
		return get_object_param(obj,(const char *)string,value);

	pString chname=string.left(pos);
	pRenderObject *o=get_object(obj);
	if(o==0)
		return false;

	int i;
	for(i=0;i<o->m_child.num;i++)
		if(o->m_child[i]->m_name.compare((const char *)chname)==0)
		{
			chname=string.right(string.length()-pos-1);
			return get_param(o->m_child[i]->m_id,chname,value);
		}

	return false;
}

int pRenderObjectManager::process_visible()
{
	int i, j, num_parents, curr_stack = 0;
	static pArray<pRenderObject *> stack[2];
	pRenderObject *o;

	stack[0].clear();
	stack[1].clear();
	m_active_visible.clear();
	m_active_visible_mesh.clear();
	m_active_visible_transp.clear();
	m_active_visible_postdraw.clear();
	m_active_visible_draw2d.clear();

	// Add all parents into stack.
	for( i=0;i<m_active_root.num;i++ )
		if ((m_active_root.buf[i]->m_flags&P_ROFLAGS_ENABLED_VISIBLE)==P_ROFLAGS_ENABLED_VISIBLE)
			stack[curr_stack].add(m_active_root.buf[i]);
	num_parents = stack[curr_stack].num;

	// Draw all parents.
	while (stack[curr_stack].num != 0)
	{
		for (i = 0; i < num_parents; i++)
		{
			o=stack[curr_stack].buf[i];

			if (g_render->view.clip_bbox(o->m_bbox_global,o->m_num_frustum_planes))
			{
				if (o->m_flags&P_ROFLAGS_CONTAINER)
				{
					m_active_visible.add(o);
					m_active_visible_transp.add(o);
					m_active_visible_mesh.add(o);
				}
				else if ((o->m_flags&P_ROFLAGS_HASMESH)==0)
				{
					if ((o->m_flags&P_ROFLAGS_TRANSP)==0)
						m_active_visible.add(o);
					else
						m_active_visible_transp.add(o);
				}
				else
					m_active_visible_mesh.add(o);
			}

			if (g_render->view.clip_bbox(o->m_bbox_global_childs,o->m_num_frustum_planes))
				for (j = 0; j < o->m_child.num; j++)
					if ((o->m_child.buf[j]->m_flags&P_ROFLAGS_ENABLED_VISIBLE)==P_ROFLAGS_ENABLED_VISIBLE)
						stack[!curr_stack].add(o->m_child.buf[j]);
		}
		stack[curr_stack].clear();
		curr_stack = !curr_stack;
		num_parents = stack[curr_stack].num;
	}

/*	// sort visible meshes by stock object
	int k=m_active_visible_mesh.num,p;
	for( i=0;i<k-1; )
	{
		p=i+1;
		for( j=p;j<k;j++ )
			if (m_active_visible_mesh.buf[i]->m_source==m_active_visible_mesh.buf[j]->m_source)
			{
				if (j>p)
				{
					pRenderObject *tmp=m_active_visible_mesh.buf[j];
					m_active_visible_mesh.buf[j]=m_active_visible_mesh.buf[p];
					m_active_visible_mesh.buf[p]=tmp;
				}
				p++;
			}
		i=p;
	}
*/
	// LOG
	if(g_render->logflag&P_LOG_VISIBLE_OBJS)
	{
		g_render->logreport.print_log(P_LOG_VISIBLE_OBJS,"pRenderObjectManager Draw (nonmesh:%i mesh:%i transp:%i postdraw:%i draw2d:%i) \n",
			m_active_visible.num,m_active_visible_mesh.num,m_active_visible_transp.num,
			m_active_visible_postdraw.num,m_active_visible_draw2d.num);
	}

	return m_active_visible.num + m_active_visible_mesh.num + m_active_visible_transp.num;
}

void pRenderObjectManager::setup_lights()
{	
	for(int i=0;i<m_active_root.num;i++)
		if(m_active_root.buf[i]->m_flags&P_ROFLAGS_ENABLED)
			m_active_root.buf[i]->setup_light();
}

void pRenderObjectManager::step(float elapsed_time)
{
	int i,j;
	pRenderObject *o;
	for( i=0;i<m_active_delete.num;i++ )
	{
		o=get_object(m_active_delete.buf[i]);
		if (o)
		{
			if (o->m_parent)
			{
				for( j=0;j<o->m_parent->m_child.num;j++ )
					if (o->m_parent->m_child.buf[j]==o)
					{
						o->m_parent->m_child.remove(j);
						break;
					}
			}
			deactivate(m_active_delete.buf[i]);
		}
	}
	m_active_delete.clear();

	// LOG
	if(g_render->logflag&P_LOG_ELAPSED_TIME_STEP)
		g_render->logreport.print_log(P_LOG_ELAPSED_TIME_STEP,"pRenderObjectManager Step %f\n",elapsed_time);

	pMatrix global;

	g_render->camera.flag=0;
	
	m_time+=elapsed_time;
	m_elapsed_time=elapsed_time;

	g_render->light.clear();

	if(m_curr_ro_camera)
	{
		// get root of current pROCamera
		pRenderObject *root=m_curr_ro_camera;
		while(root && root->m_parent)
			root=root->m_parent;

		if(g_render->logflag&P_LOG_LAST_UPDATED_OBJ)
		{
			if(root->m_flags&P_ROFLAGS_ENABLED)
			{
				g_render->logreport.print_log(P_LOG_LAST_UPDATED_OBJ,"Last updated object: %s \n",(const char *)(root->m_name));
				root->step(elapsed_time,global);
			}

			for( i=0;i<m_active_root.num;i++ )
				if (m_active_root.buf[i]!=root && m_active_root.buf[i]->m_flags&P_ROFLAGS_ENABLED)
				{
					g_render->logreport.print_log(P_LOG_LAST_UPDATED_OBJ,"Last updated object: %s \n",(const char *)(m_active_root.buf[i]->m_name));
					m_active_root.buf[i]->step(elapsed_time,global);
				}
		}
		else
		{
			if(root->m_flags&P_ROFLAGS_ENABLED)
				root->step(elapsed_time,global);

			for( i=0;i<m_active_root.num;i++ )
				if (m_active_root.buf[i]!=root && m_active_root.buf[i]->m_flags&P_ROFLAGS_ENABLED)
					m_active_root.buf[i]->step(elapsed_time,global);
		}
	}
	else
	{
		if(g_render->logflag&P_LOG_LAST_UPDATED_OBJ)
		{
			for( i=0;i<m_active_root.num;i++ )
				if (m_active_root.buf[i]->m_flags&P_ROFLAGS_ENABLED)
				{
					g_render->logreport.print_log(P_LOG_LAST_UPDATED_OBJ,"Last updated object: %s \n",(const char *)(m_active_root.buf[i]->m_name));
					m_active_root.buf[i]->step(elapsed_time,global);
				}
		}
		else
		{
			for( i=0;i<m_active_root.num;i++ )
				if (m_active_root.buf[i]->m_flags&P_ROFLAGS_ENABLED)
					m_active_root.buf[i]->step(elapsed_time,global);
		}
	}

	setup_lights();
}

void pRenderObjectManager::draw_bbox(pRenderObject *o)
{
#ifndef P_DISABLE_3D
	int i;
	pOrientedBoundBox *obb;

	// draw global bounding box
	if (g_render->debug&1)
		o->m_bbox_global.draw();

	// draw object bounding boxes
	if (g_render->debug&2)
	{
		glPushMatrix();
			glMultMatrixf(o->m_transform_global.mf);
			int nobb=o->get_obb(0,0);
			for( i=0;i<nobb;i++ )
			{
				o->get_obb(i,&obb);
				obb->draw();
			}
		glPopMatrix();
	}
#endif
}

void pRenderObjectManager::draw_bboxes(pArray<pRenderObject *>& objects)
{
#ifndef P_DISABLE_3D
	int i;
	// draw bounding boxes
	if (g_render->debug)
	{
		glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT);
		
		g_render->sel_tex(-1);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		glDisable(GL_DEPTH_TEST);
		glColor4f(0.5f,0.0f,0.0f,1.0f);

		for( i=0;i<objects.num;i++ )
			draw_bbox(objects.buf[i]);

		glEnable(GL_DEPTH_TEST);
		glColor4f(1.0f,0.0f,0.0f,1.0f);

		for( i=0;i<objects.num;i++ )
			draw_bbox(objects.buf[i]);

		glPopAttrib();
	}
#endif
}

void pRenderObjectManager::post_draw()
{
#ifndef P_DISABLE_3D
	int i;
	if(g_render->logflag&P_LOG_LAST_DRAWN_OBJ)
	{
		for( i=0;i<m_active_visible_postdraw.num;i++ )
		{
			g_render->logreport.print_log(P_LOG_LAST_DRAWN_OBJ,"Last drawn object: %s \n",(const char *)(m_active_visible_postdraw.buf[i]->m_name));
			glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT);
			glPushMatrix();
			m_active_visible_postdraw.buf[i]->post_draw();
			glPopMatrix();
			glPopAttrib();
		}
	}
	else
	{
		for( i=0;i<m_active_visible_postdraw.num;i++ )
		{
			glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT|GL_POLYGON_BIT);
			glPushMatrix();
			m_active_visible_postdraw.buf[i]->post_draw();
			glPopMatrix();
			glPopAttrib();
		}
	}
#endif
}

void pRenderObjectManager::draw2d()
{
#ifndef P_DISABLE_3D
	if(g_render->logflag&P_LOG_LAST_DRAWN_OBJ)
	{
		for(int i=0;i<m_active_visible_draw2d.num;i++ )
		{
			g_render->logreport.print_log(P_LOG_LAST_DRAWN_OBJ,"Last drawn object: %s \n",(const char *)(m_active_visible_draw2d.buf[i]->m_name));
			glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
			glPushMatrix();
			m_active_visible_draw2d.buf[i]->draw2d();
			glPopMatrix();
			glPopAttrib();
		}
	}
	else
	{
		for(int i=0;i<m_active_visible_draw2d.num;i++ )
		{
			glPushAttrib(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
			glPushMatrix();
			m_active_visible_draw2d.buf[i]->draw2d();
			glPopMatrix();
			glPopAttrib();
		}
	}
#endif
}

pRenderObject *pRenderObjectManager::get_object(const unsigned int id)
{
	if (id&1)
	{
		return m_active.get_object(id);   
	}
	else
	{
		return m_stock.get_object(id); 
	}
}

pRenderObject *pRenderObjectManager::get_object(const char *objname)
{ 
	pRenderObject *o=m_stock_str.get_object(objname);	
	if (!o)
		return get_object(create(objname));
	return o;
}

int pRenderObjectManager::get_object_id(const char *objname)
{
	pRenderObject *o=m_stock_str.get_object(objname);
	
	if (o)
		return o->m_id;

	return 0;
}

bool pRenderObjectManager::set_object_flags(unsigned int obj,const unsigned int flags)
{
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
	if (o==0) 
		return false;
	
	// LOG
	if(g_render->logflag&P_LOG_SET_OBJ_FLAGS)
		g_render->logreport.print_log(P_LOG_SET_OBJ_FLAGS,"pRenderObjectManager SetFlags %s %u\n",(const char *)o->m_name,flags);

	o->m_flags=flags;
	if ((obj&1)==0)
	{
		pRenderObject *ao=m_active.get_next_object(1);
		while(ao)
		{
			if (ao->m_source==o)
				ao->m_flags=flags;
			ao=m_active.get_next_object();
		}
	}
	return true;
}

bool pRenderObjectManager::get_object_flags(unsigned int obj,unsigned int& flags)
{
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
	if (o==0) 
		return false;
	
	flags=o->m_flags;
	return true;
}

bool pRenderObjectManager::set_object_transform(unsigned int obj,const pMatrix& m)
{
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
	if (o==0) 
		return false;
	
	// LOG
	if(g_render->logflag&P_LOG_SET_OBJ_TRANSFORM)
		g_render->logreport.print_log(P_LOG_SET_OBJ_TRANSFORM,"pRenderObjectManager SetTransform %s %f %f %f\n",(const char *)o->m_name,m.mf[12],m.mf[13],m.mf[14]);

	o->m_transform=m;
	if ((obj&1)==0)
	{
		pRenderObject *ao=m_active.get_next_object(1);
		while(ao)
		{
			if (ao->m_source==o)
				ao->m_transform=m;
			ao=m_active.get_next_object();
		}
	}
	return true;
}

bool pRenderObjectManager::get_object_transform(unsigned int obj,pMatrix& m)
{
	pRenderObject* o;
	if (obj&1)
		o=m_active.get_object(obj);
	else
		o=m_stock.get_object(obj);
	if (o==0) 
		return false;

	m=o->m_transform;
	return true;
}

bool pRenderObjectManager::check_reference(pRenderObject *o,pRenderObject *ref)
{
	if (o==ref)
		return true;
	
	int i;
	for( i=0;i<o->m_child.num;i++ )
		if (check_reference(o->m_child.buf[i],ref))
			return true;

	return false;
}

unsigned pRenderObjectManager::attach_objects(unsigned int parent, const char *par_dummy_name, unsigned int child, const char *ch_dummy_name)
{
	// parent or child is null
	if (parent == 0 || child == 0)
		return 0;

	// child is active
	if (child&1)
		return 0;

	// get parent object
	pRenderObject *parent_obj = get_object(parent);
	if (!parent_obj)
		return 0;

	// get parent's attach point
	pDummy *parent_dummy = 0;
	int i, j, num_dummy = parent_obj->get_attach_point(0, 0);
	for (i = 0; i < num_dummy; i++)
	{
		parent_obj->get_attach_point(i, &parent_dummy);
		if (parent_dummy->name.compare_nocase(par_dummy_name) == 0)
			break;
	}
	if (!parent_dummy)
		return false;

	// get child object
	pRenderObject *child_obj = (parent&1) ? get_object(activate(child,0)) : get_object(child);

	// get child's attach point
	pDummy *child_dummy = 0;
	num_dummy = child_obj->get_attach_point(0, 0);
	for (i = 0; i < num_dummy; i++)
	{
		child_obj->get_attach_point(i, &child_dummy);
		if (child_dummy->name.compare_nocase(ch_dummy_name) == 0)
			break;
	}
	if (!child_dummy)
		return 0;

	// verifies references
	if (check_reference(child_obj,parent_obj))
		return 0;

	// creates an group and inserts it into stock
	pROGroup *group = new pROGroup;	
	m_objcount_stock +=2;
	group->m_id = m_objcount_stock;
	group->m_source = 0;
	group->m_parent = 0;
	pMatrix inv_mat_child;
	child_dummy->transform.get_affine_inverse(inv_mat_child);
	group->m_transform = inv_mat_child*parent_dummy->transform;
	// initialize name
	j=parent_dummy->name.length();
	for (i = 0; i < j; i++)
		if (parent_dummy->name[i] == ' ')
			parent_dummy->name.set_char(i, '_');
	j=child_dummy->name.length();
	for (i = 0; i < j; i++)
		if (child_dummy->name[i] == ' ')
			child_dummy->name.set_char(i, '_');
	group->m_name.format("%s-%s", ch_dummy_name, par_dummy_name);
	group->init(0);

	// insert group into stock
	int count=0;
	while(!m_stock_str.add(group->m_name, group))
		group->m_name.format("%s-%s-%i", ch_dummy_name, par_dummy_name, ++count);
	m_stock.add(group->m_id, group);

	// insert group into parent_obj
	if (parent&1)
	{
		pROGroup *active_group = (pROGroup *)get_object(activate(group->m_id,0));
		active_group->m_child.add(child_obj);
		child_obj->m_parent=active_group;
		parent_obj->m_child.add(active_group);
		active_group->m_parent=parent_obj;
	}
	else
	{
		group->m_child.add(child_obj);
		child_obj->m_parent=group;
		parent_obj->m_child.add(group);
		group->m_parent=parent_obj;
	}

	// LOG
	if(g_render->logflag&P_LOG_ATTACH_OBJECT)
		g_render->logreport.print_log(P_LOG_ATTACH_OBJECT,"pRenderObjectManager AttachObjects %s %s\n",(const char *)parent_obj->m_name,(const char *)child_obj->m_name);

	return child_obj->m_id;
}

unsigned pRenderObjectManager::attach_objects(unsigned int parent,unsigned int child,const pMatrix& child_transform)
{
	// parent or child is null
	if (parent == 0 || child == 0)
		return 0;

	// child is active
	if (child&1)
		return 0;

	// get parent object
	pRenderObject *parent_obj = get_object(parent);
	if (!parent_obj)
		return 0;

	// get child object
	pRenderObject *child_obj = (parent&1) ? get_object(activate(child,0)) : get_object(child);

	// verifies references
	if (check_reference(child_obj,parent_obj))
		return 0;

	// update transform of the child
	child_obj->m_transform=child_transform;

	// insert child into parent_obj
	parent_obj->m_child.add(child_obj);
	child_obj->m_parent=parent_obj;

	// LOG
	if(g_render->logflag&P_LOG_ATTACH_OBJECT)
		g_render->logreport.print_log(P_LOG_ATTACH_OBJECT,"pRenderObjectManager AttachObjects %s %s\n",(const char *)parent_obj->m_name,(const char *)child_obj->m_name);

	return child_obj->m_id;
}

bool pRenderObjectManager::ray_intersect_bbox(pRayIntersectInfo *ri)
{
	bool ret=false;
	ri->dist=BIG;
	ri->mesh=0;

	float d1,d2;
	int i,f;

	pArray<pRenderObject *> stack;
	pRenderObject *o;

	for( i=0;i<m_active_root.num;i++ )
		stack.add(m_active_root.buf[i]);

	while( stack.num )
	{
		o=stack.buf[stack.num-1];
		stack.remove(stack.num-1);

		f=o->m_bbox_global_childs.ray_intersect(ri->ro,ri->rd,d1,d2);
		if (f!=-1)
		{
			for( i=0;i<o->m_child.num;i++ )
				stack.add(o->m_child.buf[i]);
			
			f=o->m_bbox_global.ray_intersect(ri->ro,ri->rd,d1,d2);
			if (f!=-1 && d1>0 && d1<ri->dist)
			{
				ri->dist=d1;
				ri->obj=o;
				ri->face=f;
				ret=true;
			}
		}
	}

	ri->ip=ri->ro+ri->rd*ri->dist;
		
	return ret;
}

bool pRenderObjectManager::ray_intersect(pRayIntersectInfo *ri)
{
	bool ret=false;
	ri->dist=BIG;

	for( int i=0;i<m_active_root.num;i++ )
		if ((m_active_root.buf[i]->m_flags&P_ROFLAGS_ENABLED_VISIBLE)==P_ROFLAGS_ENABLED_VISIBLE)
			if (m_active_root.buf[i]->ray_intersect(ri))
				ret=true;

	return ret;
}

void pRenderObjectManager::post_deactivate(unsigned int activeobj)
{
	if ((activeobj&1)==1)
		m_active_delete.add(activeobj);
}

void pRenderObjectManager::post_draw(pRenderObject *activeobj)
{
	if (activeobj->m_source)
		m_active_visible_postdraw.add(activeobj);
}

void pRenderObjectManager::post_draw2d(pRenderObject *activeobj)
{
	if (activeobj->m_source)
		m_active_visible_draw2d.add(activeobj);
}

void pRenderObjectManager::render_projectiles(pProjectileInfo **p,int count)
{
#ifndef P_DISABLE_3D

	// LOG
	if(g_render->logflag&P_LOG_PROJECTILES)
		g_render->logreport.print_log(P_LOG_PROJECTILES,"pRenderObjectManager RenderProjectile %i\n",count);

	pROProjectile *o;
	for( int i=0;i<count;i++ )
	{
		if (p[i]->start_time==-1.0f)
			p[i]->start_time=(g_romanager->m_time-1.0f)*FABSRAND+1.0f;

		if (g_render->view.is_inside(p[i]->pos))
		{
			o=(pROProjectile *)get_object(p[i]->obj);
			if (o)
			{	
				o->m_start_time=p[i]->start_time;
				o->update_transform(p[i]->pos,p[i]->vel);
				glPushMatrix();
				o->draw();
				glPopMatrix();
			}
		}
	}
#endif
}

void pRenderObjectManager::render_projectiles(pDProjectileInfo **p,int count)
{
#ifndef P_DISABLE_3D

	// LOG
	if(g_render->logflag&P_LOG_PROJECTILES)
		g_render->logreport.print_log(P_LOG_PROJECTILES,"pRenderObjectManager RenderProjectile %i\n",count);

	pVector local_pos;
	pROProjectile *o;
	for( int i=0;i<count;i++ )
	{
		if (p[i]->start_time==-1.0f)
			p[i]->start_time=(g_romanager->m_time-1.0f)*FABSRAND+1.0f;

		o=(pROProjectile *)get_object(p[i]->obj);
		if (o)
		{
			local_pos=pVector(p[i]->pos-m_world_origin);
			if (g_render->view.is_inside(local_pos))
			{
				o->m_start_time=p[i]->start_time;
				o->update_transform(local_pos,p[i]->vel);
	            glPushMatrix();
				o->draw();
				glPopMatrix();
			}
		}
	}
#endif
}

void pRenderObjectManager::render_projectiles(unsigned int stock_obj,pProjectileInfo **p,int count)
{
#ifndef P_DISABLE_3D

	// LOG
	if(g_render->logflag&P_LOG_PROJECTILES)
		g_render->logreport.print_log(P_LOG_PROJECTILES,"pRenderObjectManager RenderProjectile %i\n",count);

	pROProjectile *o=(pROProjectile *)get_object(stock_obj);
	if (o)
	{
		/*if (o->m_mesh)
		{
			g_render->sel_tex(-1);
			o->m_mesh->array_lock(0,g_render->vertbuffer);
			for( int i=0;i<count;i++ )
			{
				if (g_render->view.is_inside(p[i]->pos))
				{
					o->update_transform(p[i]->pos,p[i]->vel);
					glPushMatrix();
					glColor4fv(&o->m_color.x);
					glMultMatrixf(&o->m_transform_global.mf[0]);
					o->m_mesh->array_draw(g_render->vertbuffer);
					glPopMatrix();
				}
			}
			o->m_mesh->array_unlock();
		}
		else*/
		{
			for( int i=0;i<count;i++ )
			{
				if (p[i]->start_time==-1.0f)
					p[i]->start_time=(g_romanager->m_time-1.0f)*FABSRAND+1.0f;

				if (g_render->view.is_inside(p[i]->pos))
				{
					o->m_start_time=p[i]->start_time;
					o->update_transform(p[i]->pos,p[i]->vel);
					glPushMatrix();
					o->draw();
					glPopMatrix();
				}
			}
		}
	}
#endif
}

void pRenderObjectManager::render_projectiles(unsigned int stock_obj,pDProjectileInfo **p,int count)
{
#ifndef P_DISABLE_3D

	// LOG
	if(g_render->logflag&P_LOG_PROJECTILES)
		g_render->logreport.print_log(P_LOG_PROJECTILES,"pRenderObjectManager RenderProjectile %i\n",count);

	pVector local_pos;
	pROProjectile *o=(pROProjectile *)get_object(stock_obj);
	if (o)
	{
		/*if (o->m_mesh)
		{
			g_render->sel_tex(-1);
			o->m_mesh->array_lock(0,g_render->vertbuffer);
			for( int i=0;i<count;i++ )
			{
				local_pos=pVector(p[i]->pos-m_world_origin);
				if (g_render->view.is_inside(local_pos))
				{
					o->update_transform(local_pos,p[i]->vel);
					glPushMatrix();
					glColor4fv(&o->m_color.x);
					glMultMatrixf(&o->m_transform_global.mf[0]);
					o->m_mesh->array_draw(g_render->vertbuffer);
					glPopMatrix();
				}
			}
			o->m_mesh->array_unlock();
		}
		else*/
		{
			for( int i=0;i<count;i++ )
			{
				if (p[i]->start_time==-1.0f)
					p[i]->start_time=(g_romanager->m_time-1.0f)*FABSRAND+1.0f;

				local_pos=pVector(p[i]->pos-m_world_origin);
				if (g_render->view.is_inside(local_pos))
				{
					o->m_start_time=p[i]->start_time;
					o->update_transform(local_pos,p[i]->vel);
					glPushMatrix();
					o->draw();
					glPopMatrix();
				}
			}
		}
	}
#endif
}

void pRenderObjectManager::cut(unsigned int active_obj)
{
	pRenderObject *o=m_active.get_object(active_obj);
	if(o && o->m_parent)
	{
		pRenderObject *p=o->m_parent;
		for(int i=0;i<p->m_child.num;i++)
			if(p->m_child[i]==o)
			{
				p->release_child(i);
				break;
			}
	}
}

unsigned pRenderObjectManager::copy(unsigned int active_obj)
{
	pRenderObject *o=m_active.get_object(active_obj);
	if(o)
	{
		pRenderObject *new_o=rec_clone(o);

		if(new_o)
		{
			m_active_root.add(new_o);
			return new_o->m_id;
		}
	}

	return 0;
}

pRenderObject *pRenderObjectManager::rec_clone(pRenderObject *o)
{
	if(o->m_source==0)
		return 0;

	pRenderObject *new_o=o->clone();
	m_objcount_active+=2;
	m_active.add(m_objcount_active,new_o);
	new_o->m_id=m_objcount_active;

	for(int i=0;i<new_o->m_child.num;i++)
		rec_clone(new_o->m_child[i]);

	return new_o;
}

void pRenderObjectManager::paste(unsigned int active_obj_parent,unsigned int active_obj_child)
{
	pRenderObject *p=m_active.get_object(active_obj_parent);
	pRenderObject *c=m_active.get_object(active_obj_child);

	if(p && c && c->m_parent==0)
	{
		for(int i=0;i<m_active_root.num;i++)
			if(m_active_root[i]==c)
			{
				m_active_root.remove(i);
				break;
			}

		p->m_child.add(c);
		c->m_parent=p;
	}
}

void pRenderObjectManager::set_world_origin(const pDVector& world_origin,bool translate_world)
{ 
	// LOG
	if(g_render->logflag&P_LOG_SET_WORLD_ORIGIN)
		g_render->logreport.print_log(P_LOG_SET_WORLD_ORIGIN,"pRenderObjectManager SetWorldOrigin %lf %lf %lf %i\n",world_origin.x,world_origin.y,world_origin.z,(int)translate_world);

	if (translate_world)
	{
		pDVector dv=m_world_origin-world_origin;
		pVector fv(dv);
		int i;
		for( i=0;i<m_active_root.num;i++ )
			m_active_root.buf[i]->translate_world(fv);
		g_render->camera.pos+=fv;
	}
	m_world_origin=world_origin; 
}

void pRenderObjectManager::set_world_origin_delta(const pVector& delta)
{
	// LOG
	if(g_render->logflag&P_LOG_SET_WORLD_ORIGIN)
		g_render->logreport.print_log(P_LOG_SET_WORLD_ORIGIN,"pRenderObjectManager SetWorldOriginDelta %f %f %f %i\n",delta.x,delta.y,delta.z);

	m_world_origin+=pDVector(delta);

	pVector delta_f(-delta);
	int i;
	for( i=0;i<m_active_root.num;i++ )
		m_active_root.buf[i]->translate_world(delta_f);
	g_render->camera.pos+=delta_f;
}

void pRenderObjectManager::project_point_without_test(const pVector& point,pVector& projected) const
{
#ifndef P_DISABLE_3D
	pDVector d;
		
	gluProject(
		point.x,point.y,point.z,
		g_render->cam_model_mat,
		g_render->cam_proj_mat,
		g_render->cam_viewport,
		&d.x,&d.y,&d.z);

	projected.x=(float)d.x;
	projected.y=g_render->sizey-(float)d.y;
#endif
}

bool pRenderObjectManager::project_point(const pVector& point,pVector& projected) const
{
#ifndef P_DISABLE_3D
	if (g_render->view.is_inside(point))
	{
		project_point_without_test(point,projected);
		return true;
	}
	return false;
#else
	return false;
#endif
}

bool pRenderObjectManager::project_point(unsigned int active_obj,const pVector& point,pVector& point_local)
{
	pRenderObject *o=m_active.get_object(active_obj);
	if (o==0)
		return false;

	point_local=o->m_transform_global.multiply_rotation_transpose(point-o->m_transform_global.get_translate());
	point_local.y=-point_local.y;

	return true;
}

bool pRenderObjectManager::project_aabb(const pBoundBox& aabb,float& min_x,float& min_y,float& max_x,float& max_y) const
{
	if(g_render->view.clip_bbox(aabb))
	{
		float x[8];
		float y[8];

		pVector v;

		project_point_without_test(aabb.get_vert(0),v);
		x[0]=v.x;
		y[0]=v.y;

		min_x=max_x=x[0];
		min_y=max_y=y[0];
		for( int i=1;i<8;i++ )
		{
			project_point_without_test(aabb.get_vert(i),v);
			x[i]=v.x;
			y[i]=v.y;
			
			if(x[i]<min_x)
				min_x=x[i];
			else if(x[i]>max_x)
				max_x=x[i];

			if(y[i]<min_y)
				min_y=y[i];
			else if(y[i]>max_y)
				max_y=y[i];
		}
		return true;
	}
	return false;
}

bool pRenderObjectManager::project_obb(const pOrientedBoundBox& obb,float& min_x,float& min_y,float& max_x,float& max_y) const
{
	//if(g_render->view.clip_bbox(obb))
	{
		float x[8];
		float y[8];
		pVector v;

		project_point_without_test(obb.transform*obb.bb.get_vert(0),v);
		x[0]=v.x;
		y[0]=v.y;

		min_x=max_x=x[0];
		min_y=max_y=y[0];
		for( int i=1;i<8;i++ )
		{
			project_point_without_test(obb.transform*obb.bb.get_vert(i),v);
			x[i]=v.x;
			y[i]=v.y;
			
			if(x[i]<min_x)
				min_x=x[i];
			else if(x[i]>max_x)
				max_x=x[i];

			if(y[i]<min_y)
				min_y=y[i];
			else if(y[i]>max_y)
				max_y=y[i];
		}
		return true;
	}
	//return false;
}

#ifdef _DEBUG
void pRenderObjectManager::debugPrintActive(FILE *fp)
{
	for(int i=0;i<m_active_root.num;i++)
		debugPrint(fp,m_active_root[i]);
}

void pRenderObjectManager::debugPrint(FILE *fp,pRenderObject *o,int tab)
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
