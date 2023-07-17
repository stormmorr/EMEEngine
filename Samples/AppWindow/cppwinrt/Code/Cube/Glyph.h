/*

Glyph.h - osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.qage.org www.geopomp.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef GLYPH_H
#define GLYPH_H

#include "Include/Cube.h"

#include <vector>
#include <map>

using namespace Cube;

namespace Cube
{

class Glyph
{
public:
	Glyph();
	~Glyph();

	// Initialize
	void Initialize(void);
	void Unload(void);

	void GenerateBuffers(void);

	// Position
	void SetPosition(BiVector pos);
	BiVector GetPosition(void);

	aabb* m_aabb;
	bool m_Served;
	int nom_Child;
	int nom_Parent;

	// Counters
	int m_numRebuilds;

	static const int VOXEL_GRID_SIZE = 12;
	static const int VOXEL_GRID_SIZE_SQUARED = VOXEL_GRID_SIZE * VOXEL_GRID_SIZE;
	static const int VOXEL_GRID_SIZE_CUBED = VOXEL_GRID_SIZE * VOXEL_GRID_SIZE * VOXEL_GRID_SIZE;
	static const float BLOCK_RENDER_SIZE;
	static const float BLOCK_RENDER_SIZE_Y;
	static const float VOXEL_GRID_RADIUS;
	static float BLOCK_RENDER_ADJUST;

	// Flags for empty VoxelGrid and completely surrounded
	bool m_emptyVoxelGrid;
	bool m_surroundedVoxelGrid;

	// Setup and creation flags
	bool m_created;
	bool m_setup;
	bool m_isUnloading;
	bool m_rebuild;
	bool m_rebuildNeighours;
	bool m_isRebuildingMesh;
	bool m_deleteCachedMesh;

	BiVector m_position;
	BiVector* m_pos;

	/////////////
   // GL
  //
 ///
	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;

	// Indices
	GLuint mIndexBuffer;

	vector<BiVector*> m_vec_Vertex;
	vector<BiVector*> m_vec_Normal;
	vector<BiColor*> m_vec_Color;
	vector<BiTex*> m_vec_Tex;
	vector<Index*> m_vec_Index;

	bool m_PlacedIn;
	bool m_PlacedInLast;
};

class GlyphManager
{
public:
	/* Public methods */
	GlyphManager();
	~GlyphManager();

	bool UpdateGlyphs(void);

	void acResetList(void);

	std::shared_mutex m_Glyph_Muti;

private:
	    /////////////
	   // GL
	  //
	 ///
	///
	GLuint mProgram;

	GLsizei mWindowWidth;
	GLsizei mWindowHeight;

	GLint mModelUniformLocation;
	GLint mViewUniformLocation;
	GLint mProjUniformLocation;

	GLint mCameraTranslationUniformLocation;

	GLint mPosUniformLocation;

	GLint mPositionAttribLocation;
	GLint mNormalAttribLocation;
	GLint mColorAttribLocation;
	GLint mTexCoordAttribLocation;

	GLint mLightPosUniformLocation;
	GLint mLightColorUniformLocation;
	GLint mLightNomUniformLocation;

	GLuint mVertexPositionBuffer;
	GLuint mVertexNormalBuffer;
	GLuint mVertexColorBuffer;
	GLuint mVertexTexCoordBuffer;
	GLuint mIndexBuffer;

	int mDrawCount;

	int m_GlyphCount;

	std::vector<Glyph*> m_vec_Glyph_Spawn;
	std::vector<Glyph*> m_vec_Glyph_Event;
	std::vector<Glyph*> m_vec_Glyph_Function;
	std::vector<Glyph*> m_vec_Glyph_Variable;
	std::vector<Glyph*> m_vec_Glyph_Trigger;

	int m_GlyphNom;
};

extern GlyphManager* g_GlyphManager;

};

#endif