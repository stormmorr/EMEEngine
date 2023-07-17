/*! \file */

#ifndef PGUILISTCONTROL_H
#define PGUILISTCONTROL_H

#define DEFAULT_COL_WIDTH	50
#define COL_ALIGN_LEFT		0
#define COL_ALIGN_RIGHT		1
#define COL_ALIGN_CENTER	2
#define DEFAULT_COL_ALIGN	COL_ALIGN_LEFT

enum LIST_SELECTION_MODES
{
	LIST_SEL_MODE_SINGLE=0,
	LIST_SEL_MODE_MULTI
};

enum ITEM_SELECTION_STATES
{
	ITEM_SEL_STATE_NORMAL=0,
	ITEM_SEL_STATE_SELECTED
};

class pGUIListControlColumn
{
	public:
		pString m_name;
		int m_width;
		int m_align;
		pArray<pGUIMultilineText *> m_text;

		pGUIListControlColumn(const char *name="",const int width=DEFAULT_COL_WIDTH,const int align=DEFAULT_COL_ALIGN)
		{
			m_name=name;
			m_width=width;
			m_align=align;
		};

		pGUIListControlColumn(const pGUIListControlColumn& in)
		{
			m_name=in.m_name;
			m_width=in.m_width;
			m_align=in.m_align;

			int i;
			pGUIMultilineText *t;
			for(i=m_text.num-1;i>=0;i--)
			{
				t=m_text[i];
				m_text.remove(i);
				delete t;
			}

			m_text.reserve(in.m_text.num);
			for(i=0;i<in.m_text.num;i++)
			{
				t=new pGUIMultilineText(*in.m_text[i]);
				m_text.add(t);
			}
		};

		~pGUIListControlColumn()
		{
			pGUIMultilineText *t;
			for(int i=m_text.num-1;i>=0;i--)
			{
				t=m_text[i];
				m_text.remove(i);
				delete t;
			}
		};
};

class P3D_API pGUIListControl : public pGUIObject
{
	private:
		pArray<pGUIListControlColumn *> m_col;
		int m_item_count;

	public:
		int m_tex_bg;
		int m_tex_item;
		int m_tex_item_sel;
		pVector m_color_item;
		pVector m_color_item_sel;
		pVector m_color_item_text;
		pVector m_color_item_sel_text;
		int m_item_height;

		int m_draw_columns;
		int m_column_text_border_size;
		int m_draw_grid_lines;
		int m_tex_column;
		pVector m_color_column;
		pVector m_color_column_text;
		pVector m_color_grid_lines;

		int m_col_count;

		int m_sel_mode;
		pArray<int> m_sel_state;
		int m_last_sel_item;

		pArray<pVector> m_custom_color_item;
		pArray<pVector> m_custom_color_item_sel;
		pArray<pVector> m_custom_color_item_text;
		pArray<pVector> m_custom_color_item_sel_text;

		//! Default/Initialization constructor.
		pGUIListControl() :
			m_tex_bg(-1),
			m_tex_item(-1),
			m_tex_item_sel(-1),
			m_color_item(1.0f),
			m_color_item_sel(0.0f),
			m_color_item_text(0.0f),
			m_color_item_sel_text(1.0f),
			m_item_height(16),
			m_draw_columns(1),
			m_column_text_border_size(2),
			m_draw_grid_lines(1),
			m_tex_column(-1),
			m_color_column(0.5f),
			m_color_column_text(1.0f),
			m_color_grid_lines(0.0f),
			m_col_count(0),
			m_item_count(0),
			m_sel_mode(0),
			m_last_sel_item(-1)
		{ m_type=TYPE_GUI_LIST_CONTROL; };

		//! Copy constructor.
		/*!
			@param in the new object
		*/
		pGUIListControl(const pGUIListControl& in) :
			pGUIObject(in),
			m_tex_bg(in.m_tex_bg),
			m_tex_item(in.m_tex_item),
			m_tex_item_sel(in.m_tex_item_sel),
			m_color_item(in.m_color_item),
			m_color_item_sel(in.m_color_item_sel),
			m_color_item_text(in.m_color_item_text),
			m_color_item_sel_text(in.m_color_item_sel_text),
			m_item_height(in.m_item_height),
			m_draw_columns(in.m_draw_columns),
			m_column_text_border_size(in.m_column_text_border_size),
			m_draw_grid_lines(in.m_draw_grid_lines),
			m_tex_column(in.m_tex_column),
			m_color_column(in.m_color_column),
			m_color_column_text(in.m_color_column_text),
			m_color_grid_lines(in.m_color_grid_lines),
			m_col_count(in.m_col_count),
			m_item_count(in.m_item_count),
			m_sel_mode(in.m_sel_mode),
			m_last_sel_item(in.m_last_sel_item)
		{
			pGUIListControlColumn *c;
			int i;
			for(i=m_col.num-1;i>=0;i--)
			{
				c=m_col[i];
				m_col.remove(i);
				delete c;
			}
			
			for(i=0;i<in.m_col.num;i++)
			{
				c=new pGUIListControlColumn(*in.m_col[i]);
				m_col.add(c);
			}

			m_sel_state.free();
			m_sel_state.reserve(in.m_sel_state.num);
			for(i=0;i<in.m_sel_state.num;i++)
				m_sel_state.add(in.m_sel_state[i]);

			m_custom_color_item.free();
			m_custom_color_item_sel.free();
			m_custom_color_item_text.free();
			m_custom_color_item_sel_text.free();

			m_custom_color_item.reserve(in.m_custom_color_item.num);
			m_custom_color_item_sel.reserve(in.m_custom_color_item_sel.num);
			m_custom_color_item_text.reserve(in.m_custom_color_item_text.num);
			m_custom_color_item_sel_text.reserve(in.m_custom_color_item_sel_text.num);

			for(i=0;i<in.m_custom_color_item.num;i++)
			{
				m_custom_color_item.add(in.m_custom_color_item[i]);
				m_custom_color_item_sel.add(in.m_custom_color_item_sel[i]);
				m_custom_color_item_text.add(in.m_custom_color_item_text[i]);
				m_custom_color_item_sel_text.add(in.m_custom_color_item_sel_text[i]);
			}
		};

		virtual ~pGUIListControl()
		{
			pGUIListControlColumn *c;
			for(int i=m_col.num-1;i>=0;i--)
			{
				c=m_col[i];
				m_col.remove(i);
				delete c;
			}
		};

		// column operations

		//! Inserts a column into the list control.
		/*!
			@param name the column text, default = ""
			@param width the column width, default = DEFAULT_COL_WIDTH
			@param align the column alignment, default = COL_ALIGN_LEFT
			@param pos the desired position for the new column, -1 for last, default = -1
		*/
		void insert_column(const char *name="",const int width=DEFAULT_COL_WIDTH,const int align=DEFAULT_COL_ALIGN,const int pos=-1);
		//! Removes a column from the list control given its position.
		/*!
			@param pos position of the column to be removed, -1 for last, default = -1
		*/
		void remove_column(const int pos=-1);
		//! Removes a column from the list control given its name.
		/*!
			@param name name of the column to be removed
		*/
		void remove_column(const char *name);
		//! Changes the given column text to the specified string.
		/*!
			@param pos position of the column
			@param name new text for the column
		*/
		void set_column_name(int pos,const char *name);
		//! Changes the given column width to the specified value.
		/*!
			@param pos position of the column
			@param width new width for the column
		*/
		void set_column_width(int pos,const int width);
		//! Changes the given column alignment to the specified value.
		/*!
			@param pos position of the column
			@param align new alignment for the column
		*/
		void set_column_align(int pos,const int align);
		//! Retrieves the text associated with the given column.
		/*!
			@param pos position of the column
			@param name repository for the name to be retrieved
		*/
		void get_column_name(int pos,char *name);
		//! Retrieves the width associated with the given column.
		/*!
			@param pos position of the column
			@returns the column width
		*/
		int get_column_width(int pos);
		//! Retrieves the alignment associated with the given column.
		/*!
			@param pos position of the column
			@returns the column alignment
		*/
		int get_column_align(int pos);
		//! Retrieves the total number of columns.
		/*!
			@returns the number of columns
		*/
		int get_column_count();

		// item operations

		//! Clear the list control content, i.e. the items.
		void reset_content();
		//! Inserts an item into the list control.
		/*!
			@param text text for the item's first cell, default = ""
			@param pos the desired position for the new item, -1 for last, default = -1
		*/
		void insert_item(const char *text="",const int pos=-1);
		//! Removes an item from the list control.
		/*!
			@param pos position of the item to be removed, -1 for last, default = -1
		*/
		void remove_item(const int pos=-1);
		//! Changes the given item cell text to the specified string.
		/*!
			@param text new text for the cell
			@param item position of the item (row)
			@param column cell of the item (column)
		*/
		void set_item_text(const char *text,const int item,const int column=0);
		//! Retrieves the text associated with the desired item cell.
		/*!
			@param text repository for the text to be retrieved
			@param item position of the item (row)
			@param column cell of the item (column)
		*/
		void get_item_text(char *text,const int item,const int column=0);

		void set_item_colors(const pVector color_bg,const pVector color_text,const pVector color_bg_sel,const pVector color_text_sel,const int item);
		void get_item_colors(pVector &color_bg,pVector &color_text,pVector &color_bg_sel,pVector &color_text_sel,const int item);

		//! Retrieves the total number of items.
		/*!
			@returns the number of items
		*/
		int get_item_count();

		// selection

		//! Retrieves the zero-based index of the first selected item, -1 if none is selected.
		/*!
			@returns the first selected item's index
		*/
		int get_first_selected_item();
		//! Retrieves the zero-based index of the next selected item, -1 if end-of-list.
		/*!
			@param item current item in the selected items array
			@returns the next selected item's index
		*/
		int get_next_selected_item(const int cur_item);
		//! Selects an item. If in single-selection mode, unselects the last selected item.
		/*!
			@param item zero-based index of the item to be selected
		*/
		void select_item(const int item);
		//! Unselects an item.
		/*!
			@param item zero-based index of the item to be unselected
		*/
		void unselect_item(const int item);
		//! Selects all items. Void if in single-selection mode.
		void select_all();
		//! Unselects all items.
		void unselect_all();

		void init();
		
		//! Clone operation.
		/*!
			@returns a copy of this object
		*/
		pGUIObject* clone() const
		{ return new pGUIListControl(*this); };

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
};

//! GUI List Control Object Class Descriptor
/*!
	It is a descriptor to the pGUIListControl class and is used, mainly, in objects
	building process.
*/
class pGUIListControl_desc : public pClassDesc
{
	public:
		//! Creates a new check box object.
		/*! 
			@return a pointer to the new window object
		*/
		void *create()	const { return new pGUIListControl; }

		//! Retrieves the name of the associated class.
		/*! 
			@return the name of the associated class
		*/
		const char *get_name() const { return "list_control"; }

		//! Retrieves the type of the associated class.
		/*! 
			@return the type of the associated class
		*/
		int get_type() const { return TYPE_GUI_LIST_CONTROL; }
};


#endif
