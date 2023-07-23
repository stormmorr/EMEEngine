//****************************************************************************//
// dualquaternion.h                                                           //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_DUAL_QUATERNION_H
#define CAL_DUAL_QUATERNION_H

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/global.h"
#include "cal3d/vector.h"
#include "cal3d/quaternion.h"

//****************************************************************************//
// Class declaration                                                          //
//****************************************************************************//

class CAL3D_API QunDualQuaternion
{
public:
	// member variables
	QunQuaternion	nondual;
	QunQuaternion	dual;
	
	// constructors/destructor
	QunDualQuaternion() {}	// default constructor
	QunDualQuaternion( const QunDualQuaternion& inOther )	// copy constructor
		: nondual( inOther.nondual ), dual( inOther.dual ) {}
	QunDualQuaternion(	const QunQuaternion& inRotation,
						const QunVector& inTranslation );
	~QunDualQuaternion() {}
	
	// assignment
	inline QunDualQuaternion&	operator=( const QunDualQuaternion& inOther )
	{
		nondual = inOther.nondual;
		dual = inOther.dual;
		return *this;
	}
	
	inline void operator*=( float s )
	{
		nondual *= s;
		dual *= s;
	}
	
	inline void operator+=( const QunDualQuaternion& inOther )
	{
		nondual += inOther.nondual;
		dual += inOther.dual;
	}
	
	void	normalize();
	
	void	transformPoint( const QunVector& inPt, QunVector& outPt );
};


#endif	// CAL_DUAL_QUATERNION_H

//****************************************************************************//
