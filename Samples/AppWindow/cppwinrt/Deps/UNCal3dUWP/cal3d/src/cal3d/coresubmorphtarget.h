//****************************************************************************//
// coresubmorphtarget.h                                                       //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifndef CAL_CORESUBMORPHTARGET_H
#define CAL_CORESUBMORPHTARGET_H


#include "cal3d/global.h"
#include "cal3d/vector.h"
#include "cal3d/refcounted.h"
#include "cal3d/refptr.h"
class QunCoreSubmesh;

class CAL3D_API QunCoreSubMorphTarget
{
public:
  struct BlendVertex
  {
     QunVector position;
     QunVector normal;
  };
  
public:
  QunCoreSubMorphTarget() : m_coreSubmesh( NULL ) { }
  virtual ~QunCoreSubMorphTarget() { }
  
  virtual void	setCoreSubmesh( QunCoreSubmesh* inCoreSubmesh );
  QunCoreSubmesh*		getCoreSubmesh() const;

  int getBlendVertexCount() const;
  std::vector<BlendVertex>& getVectorBlendVertex();
  virtual bool reserve(int blendVertexCount);
  bool setBlendVertex(int vertexId, const BlendVertex& vertex);

  void	getBlendVertex( int vertexId, BlendVertex& outVertex ) const;

private:
			QunCoreSubMorphTarget( const QunCoreSubMorphTarget& inOther );	// unimp
			
	std::vector<BlendVertex>	m_vectorBlendVertex;
	QunCoreSubmesh*				m_coreSubmesh;
};

// The difference map is reference counted because we can use the same difference
// map on multiple actor heads.
class QunSharedDifferenceMap : public cal3d::RefCounted
{
public:
			QunSharedDifferenceMap() : m_NextIndex(0),
					m_vectorVertexIndexSize(0),
					m_vectorVertexIndexPtr(0),
					m_vectorBlendVertexPtr(0) { }

  bool reserve(int blendVertexCount);
  bool appendBlendVertex(int vertexId, const QunCoreSubMorphTarget::BlendVertex& vertex);
  
  bool	getBlendVertex( int vertexId, QunCoreSubMorphTarget::BlendVertex& outVertex ) const;

protected:
			~QunSharedDifferenceMap() { }

private:
	std::vector<QunCoreSubMorphTarget::BlendVertex>		m_vectorBlendVertex;
	std::vector<int>									m_vectorVertexIndex;
	mutable	int											m_NextIndex;
	
	// performance optimization: direct access to vector size and arrays
	mutable int											m_vectorVertexIndexSize;
	mutable const int*									m_vectorVertexIndexPtr;
	mutable const QunCoreSubMorphTarget::BlendVertex*	m_vectorBlendVertexPtr;
};
typedef cal3d::RefPtr<QunSharedDifferenceMap> QunSharedDifferenceMapPtr;


class QunCoreSubMorphTargetDiffMap : public QunCoreSubMorphTarget
{
public:
			QunCoreSubMorphTargetDiffMap();
			QunCoreSubMorphTargetDiffMap( const QunCoreSubMorphTargetDiffMap& inOther );
			~QunCoreSubMorphTargetDiffMap() { }

	virtual bool reserve(int blendVertexCount);
	virtual void	setCoreSubmesh( QunCoreSubmesh* inCoreSubmesh );

	bool appendBlendVertex(int vertexId, const QunCoreSubMorphTarget::BlendVertex& vertex);

private:
	QunSharedDifferenceMapPtr	m_diffMap;
};

#endif
//****************************************************************************//
