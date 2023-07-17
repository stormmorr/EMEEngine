#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

pROMeshTeapot::~pROMeshTeapot()
{
	m_mesh.reset();
	m_teapot.reset();
}

void pROMeshTeapot::step(const float elapsed_time,const pMatrix& global)
{
	pRenderObject::step(elapsed_time,m_transform*global);
}

void pROMeshTeapot::init(bool active)
{
	if (active)
	{
		m_teapot.build(m_tesselation,m_scale,P_TEAPOT_OPENGL);

		const pTeapotVertex *verts=m_teapot.get_verts();
		const int *faces=m_teapot.get_faces();
		int nf=m_teapot.get_numfaces();
		int nv=m_teapot.get_numverts();

		m_mesh.reset();
		m_mesh.set_numvert(nv);
		m_mesh.set_numface(nf);
		m_mesh.set_nummat(1);

		m_mesh.mat[0].diffuse=m_diffuse;
		m_mesh.mat[0].specular=m_specular;
		m_mesh.mat[0].texid=m_texmap;
		m_mesh.mat[0].texnormalid=m_normalmap;

		int i,j;
		for( i=0;i<nv;i++ )
		{
			for( j=0;j<3;j++ )
			{
				m_mesh.vert[i].pos[j]=verts[i].pos[j];
				m_mesh.vert[i].norm[j]=verts[i].normal[j];
				m_mesh.vert[i].tanu[j]=-verts[i].binormal[j];
				m_mesh.vert[i].tanv[j]=verts[i].tangent[j];
			}
			m_mesh.vert[i].tx[0]=verts[i].texcoord[0];
			m_mesh.vert[i].tx[1]=verts[i].texcoord[1];
		}

		j=0;
		for( i=0;i<nf;i++,j+=3 )
		{
			m_mesh.face[i].vertindx=j;
			m_mesh.face[i].material=0;
			m_mesh.facevert[j]=faces[j];
			m_mesh.facevert[j+1]=faces[j+1];
			m_mesh.facevert[j+2]=faces[j+2];
		}

		m_mesh.compute_normals(1, P_COMPUTE_FACENORM|P_COMPUTE_BBOX);
		m_mesh.compute_facemat();
		m_bbox=m_mesh.bbox;
//		m_mesh.save_p3d("c:\\teapot.p3d");
	}
}

void pROMeshTeapot::draw()
{
#ifndef P_DISABLE_3D
	glMultMatrixf(&m_transform_global.mf[0]);
	m_mesh.draw(g_render->renderflag,g_render->rendermode);
#endif
}

void pROMeshTeapot::draw_shadows(const pVector& lightpos)
{
	pVector lpos=lightpos-m_transform_global.get_translate();
	lpos=m_transform_global.multiply_rotation_transpose(lpos);

	m_mesh.draw_faces_shadow(lpos);
}

int pROMeshTeapot::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type='i';
			pd->data=&m_tesselation;
			pd->name="tesselation";
			pd->comment="Tesselation factor";
		break;
		
		case 1:
			pd->type='f';
			pd->data=&m_scale;
			pd->name="scale";
			pd->comment="Scale factor";
		break;

		case 2:
			pd->type='p';
			pd->data=&m_texmap;
			pd->name="texmap";
			pd->comment="Texture map";
		break;
		
		case 3:
			pd->type='p';
			pd->data=&m_normalmap;
			pd->name="normalmap";
			pd->comment="Normal map";
		break;

		case 4:
			pd->type='c';
			pd->data=&m_diffuse;
			pd->name="duffuse";
			pd->comment="Diffuse color";
		break;

		case 5:
			pd->type='c';
			pd->data=&m_specular;
			pd->name="specular";
			pd->comment="Specular color";
		break;

		case 6:
			pd->type='f';
			pd->data=&m_specular.w;
			pd->name="shine";
			pd->comment="Specular exponent";
		break;

		case 7:
			pd->type='f';
			pd->data=&m_diffuse.w;
			pd->name="transparency";
			pd->comment="Transparency factor";
		break;
	}
	
	return 8;
}

void pROMeshTeapot::setup_light()
{
	m_light.clear();
	if ((m_flags&P_ROFLAGS_ENABLED_VISIBLE)==P_ROFLAGS_ENABLED_VISIBLE)
	for(int i=0;i<g_render->light.num;i++)
	{
		if(g_render->light[i]->update_objects_light(this))
			m_light.add(g_render->light[i]);
	}

	pRenderObject::setup_light();
}

void pROMeshTeapot::on_pos_parameter_change(int i)
{
	if (m_source!=0)
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 0:
		case 1:
			init(m_source!=0);
			break;
		case 2:
			m_mesh.mat[0].texid=m_texmap;
			break;
		case 3:
			m_mesh.mat[0].texnormalid=m_normalmap;
			break;
		case 4:
		case 5:
		case 6:
		case 7:
			m_mesh.mat[0].diffuse=m_diffuse;
			m_mesh.mat[0].specular=m_specular;
			break;
	}
}

#endif
