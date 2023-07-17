/*! \file */

#ifndef PGUITREECONTROL_H
#define PGUITREECONTROL_H

#define ROOT_NODE_ID	0
#define FIRST_NODE_ID	1

#define INVALID_COOKIE	-1

enum
{
	NODE_STATE_NORMAL=0,
	NODE_STATE_EXPANDED
};

enum
{
	NODE_SEL_STATE_NORMAL=0,
	NODE_SEL_STATE_SELECTED
};

class pGUITreeControlItem
{
	public:
		unsigned int m_id;
		pString m_text;
		int m_cookie;
		int m_icon_normal;
		int m_icon_selected;

		pVector m_custom_color_bg;
		pVector m_custom_color_text;
		pVector m_custom_color_bg_sel;
		pVector m_custom_color_text_sel;

		int m_state;
		int m_sel_state;

		pArray<pGUITreeControlItem *> m_child;
		pGUITreeControlItem *m_parent;

		pGUITreeControlItem() :
			m_id(ROOT_NODE_ID),
			m_cookie(0),
			m_icon_normal(-1),
			m_icon_selected(-1),
			m_custom_color_bg(1.0f),
			m_custom_color_text(0.0f,0.0f,0.0f,1.0f),
			m_custom_color_bg_sel(0.0f,0.0f,0.0f,1.0f),
			m_custom_color_text_sel(1.0f),
			m_state(NODE_STATE_EXPANDED),
			m_sel_state(NODE_SEL_STATE_NORMAL),
			m_parent(0)
		{
		};
		
		pGUITreeControlItem(const int id,const pString text,const int cookie,const int icon_normal,const int icon_selected,const pVector color_bg,const pVector color_text,const pVector color_bg_sel,const pVector color_text_sel) :
			m_id(id),
			m_cookie(cookie),
			m_icon_normal(icon_normal),
			m_icon_selected(icon_selected),
			m_custom_color_bg(color_bg),
			m_custom_color_text(color_text),
			m_custom_color_bg_sel(color_bg_sel),
			m_custom_color_text_sel(color_text_sel),
			m_state(NODE_STATE_EXPANDED),
			m_sel_state(NODE_SEL_STATE_NORMAL),
			m_parent(0)
		{
			m_text=text;
		};

		pGUITreeControlItem(const pGUITreeControlItem &in) :
			m_id(in.m_id),
			m_cookie(in.m_cookie),
			m_icon_normal(in.m_icon_normal),
			m_icon_selected(in.m_icon_selected),
			m_custom_color_bg(in.m_custom_color_bg),
			m_custom_color_text(in.m_custom_color_text),
			m_custom_color_bg_sel(in.m_custom_color_bg_sel),
			m_custom_color_text_sel(in.m_custom_color_text_sel),
			m_state(in.m_state),
			m_sel_state(in.m_sel_state),
			m_parent(in.m_parent)
		{
			m_text=in.m_text;

			m_child.free();
			m_child.reserve(in.m_child.num);
			for(int i=0;i<in.m_child.num;i++)
				m_child.add(in.m_child[i]);
		};

		~pGUITreeControlItem()
		{
			pGUITreeControlItem *item;
			for(int i=m_child.num-1;i>=0;i--)
			{
				item=m_child[i];
				m_child.remove(i);
				delete item;
			}
		};

		void operator=(const pGUITreeControlItem &in)
		{
			m_id=in.m_id;
			m_cookie=in.m_cookie;
			m_icon_normal=in.m_icon_normal;
			m_icon_selected=in.m_icon_selected;
			m_text=in.m_text;

			m_custom_color_bg=in.m_custom_color_bg;
			m_custom_color_text=in.m_custom_color_text;
			m_custom_color_bg_sel=in.m_custom_color_bg_sel;
			m_custom_color_text_sel=in.m_custom_color_text_sel;

			m_state=in.m_state;
			m_sel_state=in.m_sel_state;

			m_child.free();
			m_child.reserve(in.m_child.num);
			for(int i=0;i<in.m_child.num;i++)
				m_child.add(in.m_child[i]);

			m_parent=in.m_parent;
		}
};

class P3D_API pGUITreeControl : public pGUIObject
{
	public:
		int m_item_height;
		int m_item_indent;

		int m_tex_bg;
		
		pIconGridInfo m_item_box_grid;
		int m_item_box_normal;
		int m_item_box_expanded;

		pIconGridInfo m_item_icon_grid;
		int m_item_default_icon_normal;
		int m_item_default_icon_selected;

		int m_tex_item;
		int m_tex_item_sel;

		pVector m_color_item;
		pVector m_color_item_sel;
		pVector m_color_item_text;
		pVector m_color_item_sel_text;

		int m_item_border_size;

		int m_transparent_items;
		int m_transparent_sel;

		pArray<pGUITreeControlItem *> m_root;
		pGUITreeControlItem *m_sel;
		unsigned int m_nextid;

		int m_show_dummy_items;

		//! Default/Initialization constructor.
		pGUITreeControl() :
			m_item_height(16),
			m_item_indent(4),
			m_tex_bg(-1),
			m_item_box_normal(-1),
			m_item_box_expanded(-1),
			m_item_default_icon_normal(-1),
			m_item_default_icon_selected(-1),
			m_tex_item(-1),
			m_tex_item_sel(-1),
			m_color_item(1.0f),
			m_color_item_sel(0.0f,0.0f,1.0f),
			m_color_item_text(0.0f),
			m_color_item_sel_text(1.0f),
			m_item_border_size(2),
			m_transparent_items(0),
			m_transparent_sel(0),
			m_show_dummy_items(0),
			m_nextid(FIRST_NODE_ID),m_sel(0)
		{ m_type=TYPE_GUI_TREE_CONTROL; };

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pGUITreeControl(const pGUITreeControl& in) :
			pGUIObject(in),
			m_item_height(in.m_item_height),
			m_item_indent(in.m_item_indent),
			m_tex_bg(in.m_tex_bg),
			m_item_box_grid(in.m_item_box_grid),
			m_item_box_normal(in.m_item_box_normal),
			m_item_box_expanded(in.m_item_box_expanded),
			m_item_icon_grid(in.m_item_icon_grid),
			m_item_default_icon_normal(in.m_item_default_icon_normal),
			m_item_default_icon_selected(in.m_item_default_icon_selected),
			m_tex_item(in.m_tex_item),
			m_tex_item_sel(in.m_tex_item_sel),
			m_color_item(in.m_color_item),
			m_color_item_sel(in.m_color_item_sel),
			m_color_item_text(in.m_color_item_text),
			m_color_item_sel_text(in.m_color_item_sel_text),
			m_item_border_size(in.m_item_border_size),
			m_transparent_items(in.m_transparent_items),
			m_transparent_sel(in.m_transparent_sel),
			m_show_dummy_items(in.m_show_dummy_items),
			m_nextid(in.m_nextid),m_sel(0)
		{
			m_root.free();
			m_root.reserve(in.m_root.num);
			for(int i=0;i<in.m_root.num;i++)
				m_root.add(in.m_root[i]);
		};

		virtual ~pGUITreeControl()
		{
			remove_all();
		};

		void init();
		
		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pGUIObject* clone() const
		{ return new pGUITreeControl(*this); };

		//! Draws this object.
		/*!
			@param scissor_rect rect used in OpenGL scissor test
		*/
		void draw(pRect& scissor_rect);

		void process_mouse_input(pGUIEventHandler *event_handler);

		//! Stores custom parameters in a given pParamDesc object.
		/*! 
			If pd is equals to 0, the method only returns the number of parameters.
			@param i i-th parameter
			@param pd pParamDesc object that holds all informations about the i-th parameter
			@return the number of parameters
		*/ 
		int get_custom_param_desc(int i,pParamDesc *pd);

		void on_pos_parameter_change(int i);

		// item manipulation
		int add_node(const pString name,const unsigned int parent,const int cookie);
		void remove_node(const unsigned int id);
		void remove_all();

		void set_icons(const unsigned int id,const int icon_normal,const int icon_selected);
		void set_colors(const unsigned int id,const pVector color_bg,const pVector color_text,const pVector color_bg_sel,const pVector color_text_sel);

		void set_cur_sel(const unsigned int id);
		unsigned int get_cur_sel();
		int get_cur_sel_cookie();

		void expand_all();
		void retract_all();
		void unselect_all();

		void get_name(const unsigned int id,pString& name);
		int get_cookie(const unsigned int id);

		void set_name(const unsigned int id,const pString name);
		void set_cookie(const unsigned int id,const int cookie);

		bool has_child(const unsigned int id);
		unsigned int get_first_child(const unsigned int id);
		unsigned int get_next_child(const unsigned int id,const unsigned int child);

		unsigned int get_node_at(const int x, const int y);

		void move_node(const unsigned int id,const unsigned int new_parent_id);

	protected:
		void add_node(pGUITreeControlItem *item,pGUITreeControlItem *parent);
		void remove_node(pGUITreeControlItem *item);
		
		int find_node_rec(pGUITreeControlItem *cur_item,pGUITreeControlItem *&item,const unsigned int id);
		void draw_node_rec(pGUITreeControlItem *cur_item,int &posx,int &posy);
		void expand_retract_unselect_rec(pGUITreeControlItem *cur_item,const int mode);
		int process_mouse_rec(pGUITreeControlItem *cur_item,pGUITreeControlItem *&item,int &cury,const int mousey);
		unsigned int get_node_at_rec(const int x, const int y,int &cury,pGUITreeControlItem *cur_item);
};

//! GUI Tree Control Object Class Descriptor
/*!
	It is a descriptor to the pGUITreeControl class and is used, mainly, in objects
	building process.
*/
class pGUITreeControl_desc : public pClassDesc
{
	public:
		//! Creates a new check box object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUITreeControl; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "tree_control"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_TREE_CONTROL; }
};

#endif
