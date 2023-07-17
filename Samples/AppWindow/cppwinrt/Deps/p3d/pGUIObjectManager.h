/*! \file */

#ifndef PGUI_OBJECTMANAGER_H
#define PGUI_OBJECTMANAGER_H

//! Global access to gui manager
P3D_API extern pGUIObjectManager *g_gomanager;

//! Global access to gui manager
P3D_API pGUIObjectManager *get_gui_manager();

//! Types of supported objects
enum 
{
	TYPE_GUI_BUTTON=512,
	TYPE_GUI_CHECK_BOX,
	TYPE_GUI_EDIT_BOX,
	TYPE_GUI_GROUP,
	TYPE_GUI_IMAGE,
	TYPE_GUI_LIST_CONTROL,
	TYPE_GUI_MODELVIEWER,
	TYPE_GUI_MULTILINE_TEXT,
	TYPE_GUI_POP_UP_MENU,
	TYPE_GUI_PROGRESSBAR,
	TYPE_GUI_PROGRESSDISK,
	TYPE_GUI_RADIALCURSOR,
	TYPE_GUI_TREE_CONTROL,
	TYPE_GUI_WINDOW,
};

#define P_GUITYPE2FACTORYID(x) ((x)-512)

//! Hotspot information
typedef struct
{
	int pos_x;
	int pos_y;
	pGUIObject *obj;
} pHotspotInfo;

//! Object center information
typedef struct
{
	int center_pos_x;
	int center_pos_y;
	pGUIObject *obj;
} pObjCenterInfo;

//! Graphic User Interface Manager class
/*!
	This class implements all functionalities supported by interface system. 
*/
class P3D_API pGUIObjectManager
{
	friend class pRender;
	friend class CPGUIEditorDoc;
	friend class CPGUIEditorTreeView;
	friend class CPGUIEditorListView;
	friend class CPGUIEditorRenderView;
	friend class CPGUIEditorMainFrame;

	protected:

		//! factory of gui objects
		pArray<pClassDesc *> m_factory;

		pHashTable<pGUIObject *> m_objects;        //!< objects in hash by id
		pHashTableStr<pGUIObject *> m_objects_str; //!< objects in hash by string

		//! list of root objects
		pArray<pGUIObject *> m_objects_root;
		//! list of event handlers for each root object
		pArray<pGUIEventHandler *> m_eventhandler_root;

		pArray<pFile *> m_files;	//!< array of files with one pFile per .pgo text file
		unsigned int m_objcount;	//!< next availble unique object id

		//! list of objects awaiting deletion
		pArray<unsigned int> m_delete;

		//! variables used for implementing double-click
		bool m_click_flag[3];
		float m_click_time[3];

		float m_tooltip_mousefocus_time;

		//! list of requisitions for hotspots
		pArray<pHotspotInfo> m_req_hotspot;

		//! list of requisitions for place objects in the center
		pArray<pObjCenterInfo> m_req_center;

		//! Is object 'ref' included in tree starting at object 'o'?
		/*!
			@param o start point of the checking
			@param ref target object of the checking
			@return true if there is the reference and false otherwise
		*/
		bool check_reference(pGUIObject *o,pGUIObject *ref);

		//! Find a PRO file.
		/*!
			@param filename path of PRO file
			@return the position of the PRO file into the array of files or -1
		*/
		int find_file(const char *filename) const;

	public:
		float m_time;			//!< global manager time
		float m_elapsed_time; //!< elapsed time since last frame

		//! current position of mouse
		int m_mouse_x,m_mouse_y;
		//! last position of mouse
		int m_mouse_last_x,m_mouse_last_y;
		//! current mouse dragging offset
		int m_mouse_drag_x,m_mouse_drag_y;
		//! mouse state, see paralelo3d.h to a list of all states
		unsigned int m_mouse_state;

		//! current mouse cursor texture
		int m_mouse_cursor;
		//! global mouse cursor for objects that have m_droppable==true
		int m_mouse_cursor_can_drop;
		//! global mouse cursor for objects that have m_droppable==false
		int m_mouse_cursor_cannot_drop;
		//! last mouse cursor texture
		int m_mouse_last_cursor;
		//! current gui object with mouse focus
		pGUIObject *m_mouse_focus;
		//! current gui object with mouse dragging focus
		pGUIObject *m_mouse_drag_focus;
		//! current gui object with mouse dropping focus
		pGUIObject *m_mouse_drop_focus;
		//! current gui object with keyboard input focus
		pGUIObject *m_input_focus;

		//! if true, there is a candidate for receiving a message of DROP
		int m_droppable;

		pGUIEventHandler *m_mouse_drag_focus_eh;
		pGUIEventHandler *m_mouse_drop_focus_eh;

		//! global translation used for scrolling
		int m_translate_x;
		int m_translate_y;

		//! maximum duration used to get double click event (in seconds)
		float m_double_click_time;

		//! shift, alt and ctrl keys state
		unsigned int m_modkeys;

		//! Default constructor.
		pGUIObjectManager();
		
		//! Detructor.
		~pGUIObjectManager();

		//! Resets all resources of manager.
		void reset();

		//! Load PGO files.
		/*!
			Clears the object definition table and load a new GUI file that can
			contain any number of objects (only objects defined in this GUI file
			will be available after the call).
			@param filename path of PGO file
			@return true if successful and false otherwise
		*/
		bool pgo_load(const char* filename);

		//! Unload PGO files.
		/*!
			Destroy the object definition table associated with the PGO file that
			will be unloaded.
			@param filename path of PGO file
			@return true if successful and false otherwise
		*/
		bool pgo_unload(const char* filename);

		//! Saves a PGO file containing all object defined in the object definition table.
		/*!
			@param filename path of PGO file
			@return true if successful and false otherwise
		*/
		bool pgo_save(const char* filename);

		//! Frees all object definition table.
		void pgo_clear();

		//! Creates a new object.
		/*!
		    This method creates a new object from its text definition. The return
			value is a handle to the object and can be used to access the object
			and destroy it when it is no more needed. If the object being created
			includes children, they will also be created.
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

		//! Creates all objects into a PGO file.
		/*!
			@param filename file that contains all objects that will be created
			@param load_tex_flag load or not all textures
			@return true if filename was found and false otherwise
		*/
		bool pgo_create(const char *filename, bool load_tex_flag=true);

		//! This call creates all objects included in the object difinition table at once.
		/*!
			By default, this method creates all gui objects and loads all textures
			related with each created render object. But, if the paramenter "load_tex_flag"
			is equals to false so no one texture will be loaded.
			@param load_tex_flag load or not all textures
		*/
		void create_all(bool load_tex_flag=true);

		//! Destroys the object whose handle is equals to objhandle.
		/*!
			@param objhandle handle of the object to be destroyed
			@param stockobjname name of the object to be destroyed
			@return true if successful and false otherwise
		*/
		bool destroy(unsigned int objhandle);
		bool destroy(const char *stockobjname);

		//! Destroys all stock objects into a PGO file name.
		/*!
			@param filename file that contains all objects that will be destroyed
			@return true if filename was found and false otherwise
		*/
		bool pgo_destroy(const char *filename);

		//! Loads all texture maps for a given PGO file name.
		/*!
			@param filename file that contains all objects that will have its textures loaded
			@return true if filename was found and false otherwise
		*/
		bool pgo_load_textures(const char *filename);
		bool pgo_load_textures(pGUIObject *o,bool recurse_childs=true);

		//! Frees all texture maps for a given PGO file name.
		/*!
			@param filename file that contains all objects that will have its textures unloaded
			@return true if filename was found and false otherwise
		*/
		bool pgo_unload_textures(const char *filename);
		bool pgo_unload_textures(pGUIObject *o,bool recurse_childs=true);

		//! Loads all texture maps.
		void load_all_textures();

		//! Unloads all texture maps.
		void unload_all_textures();

		bool activate(unsigned int objhandle,pGUIEventHandler *eventhandler);
		bool activate(const char* objname,pGUIEventHandler *eventhandler);

		bool activate_modal(unsigned int objhandle,pGUIEventHandler *eventhandler);
		bool activate_modal(const char* objname,pGUIEventHandler *eventhandler);

		bool deactivate(unsigned int objhandle);

		void post_deactivate(unsigned int objhandle);

		void select_object(unsigned int objhandle);
		void select_object(const char* objname);

		void bring_to_front(unsigned int objhandle);
		void bring_to_front(const char* objname);

		bool set_event_handler(unsigned int objhandle,pGUIEventHandler *eventhandler);
		bool set_event_handler(const char* objname,pGUIEventHandler *eventhandler);

		pGUIEventHandler *get_event_handler(unsigned int objhandle);

		//! Retrieves an object by its handle/name.
		/*!
			Given a handle/name, this method retrieves a pointer to the pGUIObject
			associated with this handle/name. If objhandle/objname is not associated with any
			object, this method returns a NULL pointer.
			@param objhandle object handle
			@param objname object name
			@return a pointer to the object associated with objhandle/objname or NULL
		*/
		pGUIObject *get_object(const unsigned int objhandle);
		pGUIObject *get_object(const char *objname);

		//! It treats mouse events.
		/*!
			@param x mouse position (in screen coordinates)
			@param y mouse position (in screen coordinates)
			@param state see paralelo3d.h to a list of all states
		*/
		void do_mouse_input(int x,int y,unsigned int state);

		void do_keyboard_input(int event,int keycode,int mod,int unicode);
		int process_default_button(pGUIObject *obj,pGUIEventHandler *eventhandler);
		int process_cancel_button(pGUIObject *obj,pGUIEventHandler *eventhandler);
		int process_tab_forward(pGUIObject *obj);
		int process_tab_forward(pGUIObject *obj,int actionflag);
		int process_tab_backward(pGUIObject *obj);
		int process_tab_backward(pGUIObject *obj,pGUIObject *&last_focusable,int actionflag);

		void set_focus(const unsigned int objhandle);

		//! Animates all objects in this manager.
		/*!
			@param elapsed_time elapsed_time in seconds
		*/
		void step(float elapsed_time);

		//! Draws all objects in this manager.
		void draw();

		bool get_object_name(unsigned int obj,pString &name);
		
		//! Get/set the object flags bitfield.
		/*!
			These methods get/set the object flags bitfield. The currently available
			flags are P_GUIFLAGS_ENABLED and P_GUIFLAGS_VISIBLE.
			@param obj handle of the object to be changed
			@param flags flags bitfield
			@return true if successful and false otherwise
		*/
		bool set_object_flags(unsigned int obj,const unsigned int flags);
		bool get_object_flags(unsigned int obj,unsigned int& flags);

		//! Get/set the object transformation (translation in x and y). 
		/*!
			These methods get/set the object transformation (translation in x and y). 
			@param obj handle of the object to be changed
			@param pos_x trasnslation in x
			@param pos_y trasnslation in y
			@return true if successful and false otherwise
		*/
		bool set_object_transform(unsigned int obj,const int pos_x,const int pos_y);
		bool get_object_transform(unsigned int obj,int &pos_x,int &pos_y);
		bool set_object_center(unsigned int obj,const int center_pos_x,const int center_pos_y);
		bool get_object_center(unsigned int obj,int &center_pos_x,int &center_pos_y);

		bool position_hotspot(unsigned int obj,int pos_x,int pos_y);

		//! Sets an object parameter.
		/*!
			Sets an object parameter by string or binary data. The parameter to be
			set can be specified by name (string) or parameter index (integer).
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
			Gets an object parameter by string or binary data. The parameter to be
			aquired can be specified by name (string) or parameter index (integer).
			@param obj object handle
			@param param the name(string) or index(integer) of the parameter to be aquired
			@param value the value(string or binary data) of the parameter
			@return true if successful and false otherwise
		*/
		bool get_object_param(unsigned int obj,const char *param,pString& value);
		bool get_object_param(unsigned int obj,const char *param,void *value);
		bool get_object_param(unsigned int obj,int param,pString& value);
		bool get_object_param(unsigned int obj,int param,void *value);

		int get_object_param_id(unsigned int obj,const char *param);

		//! Sets an object parameter.
		/*!
			Sets an object parameter by string or binary data. The string parameter 
			contains a list of child objects separated by periods 
			and a parameter at the end (like obj1.obj2.param).
			@param obj object handle
			@param string a list of child objects and a parameter at the end
			@param value the new value(string or binary data) of the parameter
			@return true if successful and false otherwise
		*/
		bool set_param(unsigned int obj,const char *string,const char *value);
		bool set_param(unsigned int obj,const char *string,const void *value);
		
		//! Gets an object parameter.
		/*!
			Gets an object parameter by string or binary data. The string parameter
			contains a list of child objects separated by periods
			and a parameter at the end (like obj1.obj2.param).
			@param obj object handle
			@param string a list of child objects and a parameter at the end
			@param value the value(string or binary data) of the parameter
			@return true if successful and false otherwise
		*/
		bool get_param(unsigned int obj,const char *string,pString &value);
		bool get_param(unsigned int obj,const char *string,void *value);

		//! Retrieves an object id given its name.
		/*!
			Given a name, this method retrieves the object handle associated 
			with this name. If objname is not associated with any object, this method 
			returns a invalid handle (0).
			@param objname object name
		*/
		int get_object_id(const char *objname);

		void attach_objects(unsigned int parent,unsigned int child,int x,int y);
		void attach_objects_radial(unsigned int parent,unsigned int child,int radius,float angle);

		//! Sets the current mouse cursor texture.
		/*!
			@param cursor_file_name texture file
		*/
		void set_mouse_cursor(const char *cursor_file_name);

		//! Sets global mouse cursor for objects that have m_droppable==true.
		/*!
			@param cursor_file_name texture file
		*/
		void set_mouse_cursor_can_drop(const char *cursor_file_name);

		//! Sets global mouse cursor for objects that have m_droppable==false.
		/*!
			@param cursor_file_name texture file
		*/
		void set_mouse_cursor_cannot_drop(const char *cursor_file_name);

		unsigned int duplicate(unsigned int obj);

		float get_angle_2d(float x,float y);

		void update_vbo();

		//! Change the time for getting double-click.
		/*!
			@param time the time in seconds
		*/
		void set_double_click_time(const float time)
		{ m_double_click_time=time<0.0f?0.0f:time; }

#ifdef _DEBUG
		void debugPrintRoots(FILE *fp);
		void debugPrint(FILE *fp,pGUIObject *o,int tab=0);
#endif

};

#endif

