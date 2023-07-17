#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROLensFlare::calc_num_elements()
{
	// code to prevent arrays of different sizes
	m_num_elem=m_elem_tex.num;
	if(m_elem_pos.num<m_num_elem)
		m_num_elem=m_elem_pos.num;
	if(m_elem_size.num<m_num_elem)
		m_num_elem=m_elem_size.num;
	if(m_elem_opac.num<m_num_elem)
		m_num_elem=m_elem_opac.num;
	if(m_elem_color.num<m_num_elem)
		m_num_elem=m_elem_color.num;
}

void pROLensFlare::init(bool active)
{
	m_bbox.max.vec(1000.0f);
	m_bbox.min.vec(-1000.0f);
	calc_num_elements();
}

void pROLensFlare::step(const float elapsed_time,const pMatrix& global)
{
	m_num_frustum_planes=5-g_render->hugeplaneflag;

	pMatrix transform_global=m_transform*global;

	int i;
	for( i=0;i<16;i++ )
	{
		cam_model_mat[i]=g_render->cam_model_mat[i];
		cam_proj_mat[i]=g_render->cam_proj_mat[i];
	}

	pRenderObject::step(elapsed_time,transform_global);
}

void pROLensFlare::draw()
{
#ifndef P_DISABLE_3D
	static pRayIntersectInfo s_ri;

	pVector pos=m_transform_global.get_translate();

	s_ri.ro=g_render->camera.pos;
	s_ri.rd=pos-s_ri.ro;
	s_ri.rd.normalize();
	if(!g_romanager->ray_intersect(&s_ri))
	{
		// transform lens flare position to screen space
		double x,y,z;
		gluProject(
			pos.x,pos.y,pos.z,			// object position in global space
			cam_model_mat,	// modelview transformation
			cam_proj_mat,		// projectrion transformation
			g_render->cam_viewport,		// view port transformation
			&x,&y,&z					// object position in screen space
		);
		if (z>1)
			return;
		
		// calculates support line of lens flare effect
		pVector mid_screen(g_render->sizex*0.5f,g_render->sizey*0.5f,0.0f);
		pVector line_start((float)x,g_render->sizey-(float)y,0.0f);
		pVector line_end(mid_screen+(mid_screen-line_start));

		// compute how far off-center the flare source is.
		float max_flare_dist=sqrtf(mid_screen.x*mid_screen.x+mid_screen.y*mid_screen.y);
		float flare_dist=mid_screen.distto(line_start);

		// determine overall scaling based on off-center distance.
		float dist_scale=(max_flare_dist-flare_dist)/max_flare_dist;

		// for each element, compute some attributes
		m_elem_calc_pos.clear();
		m_elem_calc_size.clear();
		m_elem_calc_opac.clear();
		for(int i=0;i<m_num_elem;i++)
		{
			// position is interpolated between line_start and line_end
			m_elem_calc_pos.add((1.0f-m_elem_pos[i])*line_start+m_elem_pos[i]*line_end);
			
			if(m_elem_pos[i]==0.0f) // light source
			{
				// in light source, distance doesn't change size
				m_elem_calc_size.add(m_elem_size[i]);

				// in light source, opacity is controlled by m_scale_opacity too
				m_elem_calc_opac.add(m_elem_opac[i]*dist_scale*m_scale_opacity);
			}
			else // other elements than light source
			{
				// size of element depends on its scale, distance scaling and overall
				// scale of the flare itself
				m_elem_calc_size.add(m_elem_size[i]*dist_scale);

				// alpha is based on element alpha and distance scale
				m_elem_calc_opac.add(m_elem_opac[i]*dist_scale);
			}
		}

		g_romanager->post_draw2d(this);
	}
#endif
}

void pROLensFlare::draw2d()
{
#ifndef P_DISABLE_3D
	float half_size;

	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_ONE,GL_ONE);
	for(int i=0;i<m_num_elem;i++)
	{
		glColor3f(m_elem_color[i].x*m_elem_calc_opac[i],m_elem_color[i].y*m_elem_calc_opac[i],m_elem_color[i].z*m_elem_calc_opac[i]);
		g_render->sel_tex(m_elem_tex[i]);
		half_size=m_elem_calc_size[i]*0.5f;
		glPushMatrix();
		glTranslatef(m_elem_calc_pos[i].x-half_size,m_elem_calc_pos[i].y-half_size,0.0f);
		//*glBegin(GL_QUADS);
			glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f,0.0f);
			glTexCoord2f(0.0f,0.0f); glVertex2f(0.0f,m_elem_calc_size[i]);
			glTexCoord2f(1.0f,0.0f); glVertex2f(m_elem_calc_size[i],m_elem_calc_size[i]);
			glTexCoord2f(1.0f,1.0f); glVertex2f(m_elem_calc_size[i],0.0f);
		//*glEnd();
		glPopMatrix();
	}
#endif
}

int pROLensFlare::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd)
	switch(i)
	{
		case 0:
			pd->type=-'p';
			pd->data=&m_elem_tex;
			pd->name="elem_texture";
			pd->comment="Each array position represents a flare element. This array stores "
				        "the texture of each element. Besides, array size must be equals to all";
		break;

		case 1:
			pd->type=-'f';
			pd->data=&m_elem_pos;
			pd->name="elem_position";
			pd->comment="Each array position represents a flare element. This array stores "
				        "the position [0,1] of each element. Besides, array size must be equals to all";
		break;

		case 2:
			pd->type=-'f';
			pd->data=&m_elem_size;
			pd->name="elem_size";
			pd->comment="Each array position represents a flare element. This array stores "
				        "the size (as a scale factor) of each element. Besides, array size must be equals to all";
		break;

		case 3:
			pd->type=-'c';
			pd->data=&m_elem_color;
			pd->name="elem_color";
			pd->comment="Each array position represents a flare element. This array stores "
				        "the color of each element. Besides, array size must be equals to all";
		break;

		case 4:
			pd->type=-'f';
			pd->data=&m_elem_opac;
			pd->name="elem_opacity";
			pd->comment="Each array position represents a flare element. This array stores "
				        "the opacity of each element. Besides, array size must be equals to all";
		break;

		case 5:
			pd->type='f';
			pd->data=&m_scale_opacity;
			pd->name="scale_opacity";
			pd->comment="Controls opacity of textures whose position (elem_position) is 0.0";
		break;
	}

	return 6;
}

void pROLensFlare::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 0:case 1:case 2:case 3:case 4:
			calc_num_elements();
		break;
	}
}

#endif
