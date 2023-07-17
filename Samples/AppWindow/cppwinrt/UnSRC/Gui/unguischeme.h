/*

    unGUI - Progressive User Interface
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

*/

#ifndef UNGUISCHEME_H
#define UNGUISCHEME_H

//----------------------------------------------------------------------------//
// Definitions                                                                //
//----------------------------------------------------------------------------//

#define GUI_GIZMO_MULT1 1
#define GUI_GIZMO_MULT2 2
#define GUI_GIZMO_MULT3 5

//----------------------------------------------------------------------------//
// Class Declarations                                                         //
//----------------------------------------------------------------------------//

enum PANETYPES
{
	/**
	 * Static Non-Moving 2 dimensional pane
	 */
	FIXED_2D = 1,

	/**
	 * Movable 2 dimensional pane
	 */
	UNFIXED_2D = 2,

	/**
	 * Static Non-Moving 3 dimensional pane
	 */
	FIXED_3D = 3,

	/**
	 * Movable 3 dimensional pane
	 */
	UNFIXED_3D = 4
};

enum TEXTURETYPES
{
	/**
	 * Static Non-Moving 2 dimensional pane
	 */
	TEX_SINGLE = 1,

	/**
	 * Movable 2 dimensional pane
	 */
	TEX_DUAL = 2
};

enum GUI_EVENT_TYPES
{
	/**
	 * Static Non-Moving 2 dimensional pane
	 */
	UNGUI_EVE_CLICK = 1,

	/**
	 * Movable 2 dimensional pane
	 */
	UNGUI_EVE_EXIT = 2
};

const unsigned int texxcoords[] =
{
1, 0,
0, 0,
0, 1,
1, 1
};

const unsigned int texxreversed[] =
{
1, 1,
0, 1,
0, 0,
1, 0
};

#endif