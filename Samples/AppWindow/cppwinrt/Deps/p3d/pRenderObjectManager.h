/*! \file */

#ifndef PRENDEROBJECTMANAGER_H
#define PRENDEROBJECTMANAGER_H

//! Global access to render object manager
P3D_API extern pRenderObjectManager *g_romanager;

//! Global access to render object manager
P3D_API pRenderObjectManager *get_ro_manager();

//! Types of supported objects
enum 
{	
	TYPE_RO_FIRST=255,
	TYPE_RO_BILLBOARD,
	TYPE_RO_CAMERA,
	TYPE_RO_EXPLOSION,
	TYPE_RO_EXPLODE_OBJECT,
	TYPE_RO_GROUP,
	TYPE_RO_LENS_FLARE,
	TYPE_RO_LIGHT,
	TYPE_RO_MESH,
	TYPE_RO_MESH_HUGE,
	TYPE_RO_MESH_LOD,
	TYPE_RO_MESH_RELIEF,
	TYPE_RO_MESH_SKELETON,
	TYPE_RO_MESH_TEAPOT,
	TYPE_RO_OBFUSCATING_POINT,
	TYPE_RO_PANORAMA,
	TYPE_RO_PARTICLE_SYSTEM,
	TYPE_RO_PARTICLE_SYSTEM_GPU,
	TYPE_RO_PROJECTILE,
	TYPE_RO_ROTOR,
#ifdef P_SOUND
	TYPE_RO_SOUND,
#endif
	TYPE_RO_SPACE_DUST,
	TYPE_RO_TRAIL
};

#define P_ROTYPE2FACTORYID(x) ((x)-256)

//! Render Object Manager class
/*!
	This class implements all functionalities supported by render objects system. 
*/
class P3D_API pRenderObjectManager
{
	friend class pRender;
	friend class pRenderGlow;
	friend class pRenderRipple;
	friend class pRenderShadowMap;
	friend class pRenderMB;
	friend class pRenderObject;
	friend class CPROEditorDoc;
	friend class CPROEditorTreeView;
	friend class CPROEditorListView;
	friend class CPROEditorRenderView;
	friend class CPROEditorMainFrame;

	public:
		pArray<pRenderObject *> m_active_root;

	protected:	
		//! factory of render objects
		pArray<pClassDesc *> m_factory;

		//! stock objects in hash by id
		pHashTable<pRenderObject *> m_stock;
		//! stock objects in hash by string
		pHashTableStr<pRenderObject *> m_stock_str;
		
		//! active objects in hash by id
		pHashTable<pRenderObject *> m_active;
		//! list root active objects
		
		//! list of active objects to be destoyed
		pArray<unsigned int> m_active_delete;
		
		//! visible active objects list
		pArray<pRenderObject *> m_active_visible;
		//! transparent visible active objects list
		pArray<pRenderObject *> m_active_visible_mesh;
		//! transparent visible active objects list
		pArray<pRenderObject *> m_active_visible_transp;
		//! transparent visible active objects list
		pArray<pRenderObject *> m_active_visible_postdraw;
		//! visible active 2d objects list
		pArray<pRenderObject *> m_active_visible_draw2d;

		//! double-precision world origin (it is used to manipulate double-precision objects)
		pDVector m_world_origin;

		pArray<pFile *> m_files;		//!< array of files with one pFile per .pro text file
		unsigned int m_objcount_stock;	//!< next availble unique stock object id
		unsigned int m_objcount_active;	//!< next availble unique active object id

		//! Is object 'ref' included in tree starting at object 'o'?
		/*!
			@param o start point of the checking
			@param ref target object of the checking
			@return true if there is the reference and false otherwise
		*/
		bool check_reference(pRenderObject *o,pRenderObject *ref);

		//! Find a PRO file.
		/*!
			@param filename path of PRO file
			@return the position of the PRO file into the array of files or -1
		*/
		int find_file(const char *filename) const;

	public:
		float m_time;	//!< global manager time
		float m_elapsed_time; //!< elapsed time since last frame
		pRenderObject *m_curr_ro_camera; //! current render object camera

		//! Default constructor.
		pRenderObjectManager();

		//! Detructor.
		~pRenderObjectManager();

		//! Resets all resources of manager.
		void reset();

		//! Load PRO files.
		/*!
			Creates a new object definition table and load the PRO file that can
			contain any number of objects.
			@param filename path of PRO file
			@return true if successful and false otherwise
		*/
		bool pro_load(const char* filename);

		//! Unload PRO files.
		/*!
			Destroy the object definition table associated with the PRO file that
			will be unloaded.
			@param filename path of PRO file
			@return true if successful and false otherwise
		*/
		bool pro_unload(const char* filename);

		//! Saves a PRO file containing all objects defined in the object definition table.
		/*!
			@param filename path of PRO file
			@return true if successful and false otherwise
		*/
		bool pro_save(const char* filename);

		//! Frees all object definition table.
		void pro_clear();

		//! Creates a new object.
		/*!
		    This method creates a new object from its text definition. The return
			value is a handle to the object and can be used to access the object and
			destroy it when it is no more needed. If the object being created includes
			childs, the childs will also be created. By default, this method search
			by the new object's text definition into the cache with all loaded .pro
			text files, otherwise, this text definition is searched into file f.
			@param objname name of new object
			@param f file that contains the text definition of the new object
			@return a handle to the new object
		*/
		unsigned int create(const char *objname,pFile *f=0);

		//! Creates a new object.
		/*!
		    This method creates a new object from its text definition. The return
			value is a handle to the object and can be used to access the object and
			destroy it when it is no more needed. If the object being created includes
			childs, the childs will also be created. This text definition is searched
			into file whose name is filename.
			@param objname name of new object
			@param filename file that contains the text definition of the new object
			@return a handle to the new object
		*/
		unsigned int create(const char *objname,const char *filename);

		//! Creates all objects into a PRO file.
		/*!
			@param filename file that contains all objects that will be created
			@param load_tex_flag load or not all textures
			@return true if filename was found and false otherwise
		*/
		bool pro_create(const char *filename, bool load_tex_flag=true);

		//! This call creates all objects included in the object difinition table at once.
		/*!
			By default, this method creates all render objects and loads all textures
			related with each created render object. But, if the paramenter "load_tex_flag"
			is equals to false so no one texture will be loaded.
			@param load_tex_flag load or not all textures
		*/
		void create_all(bool load_tex_flag=true);

		//! Destroys the object whose handle is equals to stockobj.
		/*!
			This method destroys an object from the stock. When an object from the
			stock is destroyed, all active copies of it will also be destroyed.
			@param stockobj handle of the object to be destroyed
			@param stockobjname name of the object to be destroyed
			@return true if successful and false otherwise
		*/
		bool destroy(unsigned int stockobj);
		bool destroy(const char *stockobjname);

		//! Destroys all stock objects into a PRO file name.
		/*!
			@param filename file that contains all objects that will be destroyed
			@return true if filename was found and false otherwise
		*/
		bool pro_destroy(const char *filename);

		//! Loads all texture maps for a given PRO file name.
		/*!
			@param filename file that contains all objects that will have its textures loaded
			@return true if filename was found and false otherwise
		*/
		bool pro_load_textures(const char *filename);
		bool pro_load_textures(pRenderObject *o,bool recurse_childs=true);

		//! Frees all texture maps for a given PRO file name.
		/*!
			@param filename file that contains all objects that will have its textures unloaded
			@return true if filename was found and false otherwise
		*/
		bool pro_unload_textures(const char *filename);
		bool pro_unload_textures(pRenderObject *o,bool recurse_childs=true);

		//! Loads all texture maps.
		void load_all_textures();

		//! Unloads all texture maps.
		void unload_all_textures();

		//! Activates a given stock object.
		/*!
			Activates a given stock object and return the handle for the activated copy.
			@param stockobj stock object's handle
			@param addToRoot insert flag to hash of root active objects
			@return a handle to the activated object
		*/
		unsigned int activate(unsigned int stockobj,bool addToRoot=true);
		unsigned int activate(const char *stockobjname,bool addToRoot=true);

		//! Deactivates a given active object.
		/*!
			Deactivates a given active object (removing it from simulation).
			@param activeobj active object's handle
			@return true is successful and false otherwise
		*/
		bool deactivate(unsigned int activeobj);

		//! Adds object to destroy list so it is destroyed at the end of frame step.
		/*!
			@param activeobj active object to be deactivated
		*/
		void post_deactivate(unsigned int activeobj);

		//! Adds object to post draw list so is drawn after all others.
		/*!
			@param active object pointer
		*/
		void post_draw(pRenderObject *activeobj);

		//! Adds object to post draw 2d list so is drawn in 2d mode.
		/*!
			@param active object pointer
		*/
		void post_draw2d(pRenderObject *activeobj);

		//! Animates all objects in this manager.
		/*!
			@param elapsed_time elapsed_time in seconds
		*/
		void step(float elapsed_time);

		//! Draws all visible objects in this manager.
		void draw_bbox(pRenderObject *o);
		void draw_bboxes(pArray<pRenderObject *>& objects);
		
		//! Draws objects into post draw list.
		void post_draw();

		//! Draws all 2d visible objects in this manager.
		void draw2d();

		//! Get/set the object flags bitfield.
		/*!
			These methods get/set the object flags bitfield. The currently available
			flags are P_ROFLAGS_ENABLED, P_ROFLAGS_VISIBLE and P_ROFLAGS_TRANSP.
			@param obj handle of the object to be changed
			@param flags flags bitfield
			@return true if successful and false otherwise
		*/
		bool set_object_flags(unsigned int obj,const unsigned flags);
		bool get_object_flags(unsigned int obj,unsigned int& flags);

		//! Get/set the object transformation matrix (translation/rotation). 
		/*!
			These methods get/set the object transformation matrix (translation/rotation). 
			@param obj handle of the object to be changed
			@param m matrix (translation/rotation)
			@return true if successful and false otherwise
		*/
		bool set_object_transform(unsigned int obj,const pMatrix& m);
		bool get_object_transform(unsigned int obj,pMatrix& m);

		//! Sets an object parameter.
		/*!
			Sets an object parameter by string or binary data. Object can be from
			stock or active lists. The parameter to be set can be specified by name
			(string) or parameter index (integer).
			@param obj object handle
			@param param the name(string) or index(integer) of the parameter to be set
			@param value the new value(string or binary data) of the parameter
			@return true if successful and false otherwise
		*/
		bool set_object_param(unsigned int obj,const char *param,const char *value);
		bool set_object_param(unsigned int obj,const char *param,const void *value);
		bool set_object_param(unsigned int obj,int param,const char *value);
		bool set_object_param(unsigned int obj,int param,const void *value);

		//! Gets an object parameter.
		/*!
			Gets an object parameter by string or binary data. Object can be from
			stock or active lists. The parameter to be aquired can be specified by
			name (string) or parameter index (integer).
			@param obj object handle
			@param param the name(string) or index(integer) of the parameter to be aquired
			@param value the value(string or binary data) of the parameter
			@return true if successful and false otherwise
		*/
		bool get_object_param(unsigned int obj,int param,pString& value);
		bool get_object_param(unsigned int obj,int param,void *value);
		bool get_object_param(unsigned int obj,const char *param,pString& value);
		bool get_object_param(unsigned int obj,const char *param,void *value);

		//! Sets an object parameter.
		/*!
			Sets an object parameter by string or binary data. Object can be from
			stock or active lists. The string parameter contains a list of child objects
			separated by periods and a parameter at the end (like obj1.obj2.param).
			@param obj object handle
			@param string a list of child objects and a parameter at the end
			@param value the new value(string or binary data) of the parameter
			@return true if successful and false otherwise
		*/
		bool set_param(unsigned int obj,const pString &string,const char *value);
		bool set_param(unsigned int obj,const pString &string,const void *value);
		
		//! Gets an object parameter.
		/*!
			Gets an object parameter by string or binary data. Object can be from
			stock or active lists. The string parameter contains a list of child objects
			and a parameter at the end (like obj1.obj2.param).
			@param obj object handle
			@param string a list of child objects and a parameter at the end
			@param value the value(string or binary data) of the parameter
			@return true if successful and false otherwise
		*/
		bool get_param(unsigned int obj,const pString &string,pString &value);
		bool get_param(unsigned int obj,const pString &string,void *value);

		//! Retrieves an object by its handle/name.
		/*!
			Given a handle/name, this method retrieves a pointer to the pRenderObject
			associated with this handle/name. If id/objname is not associated with any
			object, this method returns a NULL pointer.
			@param id object handle
			@param objname object name
			@return a pointer to the object associated with id/objname or NULL
		*/
		pRenderObject *get_object(const unsigned int id);
		pRenderObject *get_object(const char *objname);

		//! Retrieves an stock object id by its name.
		/*!
			Given a name, this method retrieves the stock object handle	associated 
			with this name. If objname is not associated with any object, this method 
			returns a invalid handle (0).
			@param objname stock object name
		*/
		int get_object_id(const char *objname);

		//! Attach an object with another object.
		/*!
			Given two handles (parent and child) and two attach point names
			(par_dummy_name and ch_dummy_name), this method try to attach
			child into parent.
			@param parent target object of attachment
			@param par_dummy_name attach point name associated with parent
			@param child source object of attachment
			@param ch_dummy_name attach point name associated with child
			@return the attached object's id, or 0 if the attach attempt fails
		*/
		unsigned int attach_objects(unsigned int parent,const char *par_dummy_name,unsigned int child,const char *ch_dummy_name);
		
		//! Attach an object with another object.
		/*!
			Given two handles (parent and child) and a transformation
			(child_transform), this method try to attach child into parent.
			@param parent target object of attachment
			@param child source object of attachment
			@param child_transform attach point associated with child
			@return the attached object's id, or 0 if the attach attempt fails
		*/
		unsigned int attach_objects(unsigned int parent,unsigned int child,const pMatrix& child_transform);

		//! Intersects a ray with all visible and/or enable objects in this manager.
		/*!
			@param ri contains all informations about the nearest intersection during the process
			@return true if there is intersection and false otherwise
		*/
		bool ray_intersect(pRayIntersectInfo *ri);
		bool ray_intersect_bbox(pRayIntersectInfo *ri);

		//! Renders several projectiles of several types at once. Each projectile is defined by its object id, position and velocity.
		/*!
			@param p array of pointers to projectile information structs
			@param cound number of projectiles in array
		*/
		void render_projectiles(pProjectileInfo **p,int count);
		void render_projectiles(pDProjectileInfo **p,int count);
		
		//! Renders several projectiles of one type at once. Each projectile is defined by its position and velocity.
		/*!
			In this method, the attribute that represents the object id into the struct pProjectileInfo
			is ignored.
			@param stock_obj stock object id of all projectiles
			@param p array of pointers to projectile information structs
			@param count number of projectiles in array
		*/
		void render_projectiles(unsigned int stock_obj,pProjectileInfo **p,int count);
		void render_projectiles(unsigned int stock_obj,pDProjectileInfo **p,int count);

		//! Look for all objects inside view frustum.
		/*!
			@return the number of visible objects
		*/
		int process_visible();
		
		void setup_lights();

		//! Release active object from parent.
		/*!
			This methods releases a non-root active object from its parent and inserts it
			into the active objects root list.
			@param active_obj active object id
		*/
		void cut(unsigned int active_obj);

		//! Clone active object and its hierarchy.
		/*!
			This methods clones an active object along with its hierarchy, and inserts it
			into the active objects root list.
			@param active_obj active object id
			@return the newly-created object's id
		*/
		unsigned int copy(unsigned int active_obj);

		//! Link root active object to a new parent.
		/*!
			This methods sets the second object as a child of the first. The second object
			must be a root active object.
			@param active_obj_parent object id for the parent active object
			@param active_obj_child object id for the child active object
		*/
		void paste(unsigned int active_obj_parent,unsigned int active_obj_child);

		//! Set a new value to double-precision world origin.
		/*!
			It is used to manipulate double-precision objects.
			@param world_origin double-precision position
		*/
		void set_world_origin(const pDVector& world_origin,bool translate_world=true);
		
		//! Moves the world oribin by a displacement given by delta.
		/*!
			@param delta displacement
		*/
		void set_world_origin_delta(const pVector& delta);

		//! Get the world origin value
		pDVector get_world_origin()
		{ return m_world_origin; }

		bool project_point(const pVector& point,pVector& projected) const;
		bool project_point(unsigned int active_obj,const pVector& point,pVector& point_local);
		bool project_aabb(const pBoundBox& aabb,float& min_x,float& min_y,float& max_x,float& max_y) const;
		bool project_obb(const pOrientedBoundBox& obb,float& min_x,float& min_y,float& max_x,float& max_y) const;

		void project_point_without_test(const pVector& point,pVector& projected) const;

#ifdef _DEBUG
	void debugPrintActive(FILE *fp);
	void debugPrint(FILE *fp,pRenderObject *o,int tab=0);
#endif
	
	protected:
		pRenderObject *rec_clone(pRenderObject *o);
};

#endif
