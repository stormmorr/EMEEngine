#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_GUI

pGUIGroup::pGUIGroup(pGUIObject *parent) :
   pGUIObject(parent)
{m_type=TYPE_GUI_GROUP;}

pGUIGroup::~pGUIGroup()
{}

#endif
