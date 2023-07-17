#include "pch.h"
#include "paralelo3d.h"

#ifdef P_MANAGER_OBJ

void pROTrail::init(bool active)
{
	if (m_num_trail_points!=0)
	{
		m_path.resize(m_num_trail_points);
		m_delay=m_duration/m_num_trail_points;

		m_start_time=g_romanager->m_time;
	}
}

void pROTrail::step(const float elapsed_time,const pMatrix& global)
{
	int p=m_path.length();

	// remove i first trail points whose life is over
	int i;
	for(i=0;i<p;i++ )
		if (g_romanager->m_time-m_path[i].vel.w<m_duration)
			break;
	m_path.remove_begin(i);

	// calculates the matrix that transforms trail to world space
	pMatrix m=m_transform*global;
	pVector vel,pos=m.get_translate();

	p=m_path.length();

	// updates trail's bounding box
	pBoundBox bb;
	bb.reset();
	bb.add_point(pos);
	for( i=0;i<p;i++ )
		bb.add_point(m_path[i].pos);
	bb.max+=m_width*0.5f;
	bb.min-=m_width*0.5f;

	// if trail has velocity, apply velocity to points
	if (m_vel>0)
		for( i=0;i<p;i++ )
			m_path[i].pos+=m_path[i].vel*elapsed_time;

	// verifies if a new trail point can be created
	p--;
	if (p>=0)
		m_path[p].pos=pos;
	m_totdt+=elapsed_time;
	if (m_totdt>m_delay)
	{
		if (p<1 || m_path[p-1].pos.distto2(pos)>m_threshold)
		{
			vel=m_vel*m_transform_global.get_column3(2);
			vel.w=g_romanager->m_time;
			m_path.add(pListData(pos,vel));
			m_totdt=0;
		}
	}

	// update bounding box
	pMatrix m2;
	m.get_affine_inverse(m2);
	m_bbox.reset();
	m_bbox.add_bbox(bb,m2);

	pRenderObject::step(elapsed_time,m);
}

bool point_inside_tri(const pVector& p,const pVector& p1,const pVector& p2,const pVector& p3)
{
	pVector c1,c2;
	pVector v1,v2;
	
	v1=p-p1;
	v2=p2-p1;
	c1.cross(v1,v2);
	v2=p3-p1;
	c2.cross(v1,v2);

	if (VECDOT(c1,c2)>0)
		return false;

	v1=p-p2;
	v2=p1-p2;
	c1.cross(v1,v2);
	v2=p3-p2;
	c2.cross(v1,v2);

	if (VECDOT(c1,c2)>0)
		return false;

	v1=p-p3;
	v2=p1-p3;
	c1.cross(v1,v2);
	v2=p2-p3;
	c2.cross(v1,v2);

	if (VECDOT(c1,c2)>0)
		return false;

	return true;
}

void line_line_intersect(const pVector& p1,const pVector& p2,pVector& p3,pVector& p4,float& t1,float& t2)
{
	pVector v=p2-p1;
	int i=0,i1,i2;
	if (fabsf(v.y)<fabsf(v.x))
		i=1;
	if (fabsf(v.z)<fabsf(v[i]))
		i=2;
	if (i==0)
		{ i1=1; i2=2; }
	else
	if (i==1)
		{ i1=0; i2=2; }
	else
		{ i1=0; i2=1; }

	float a1=p2[i2]-p1[i2];
	float b1=p1[i1]-p2[i1];
	float c1=p2[i1]*p1[i2]-p1[i1]*p2[i2];

	float a2=p4[i2]-p3[i2];
	float b2=p3[i1]-p4[i1];
	float c2=p4[i1]*p3[i2]-p3[i1]*p4[i2];

	float d=a1*b2-a2*b1;

	float x=(b1*c2-b2*c1)/d;
	float y=(a2*c1-a1*c2)/d;

	t1=(x-p1[i1])/(p2[i1]-p1[i1]);
	t2=(x-p3[i1])/(p4[i1]-p3[i1]);
}

void check_concave(const pVector& p1,const pVector& p2,pVector& p3,pVector& p4)
{
	float t1,t2;
	line_line_intersect(p1,p2,p3,p4,t1,t2);

	if (t1>=0.0 && t1<=1.0f)
	{
		if (t2<0)
			p3=p1;
		else
			p4=p2;
	}
	else	
	if (t2>=0.0 && t2<=1.0f)
	{
		if (t1<0)
			p3=p3+t2*(p4-p3);
		else
			p4=p3+t2*(p4-p3);
	}
}

void pROTrail::draw()
{
#ifndef P_DISABLE_3D
	int i,p=m_path.length();

	if (g_render->debug)
	{
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);

		g_render->sel_tex(-1);
		glColor3f(0.5f,0.5f,0.5f);
		glLineWidth(1.0f);
		//*glBegin(GL_LINE_STRIP);
		for( i=0;i<p;i++ )
			//*glVertex3fv(&m_path[i].pos.x);
		//*glEnd();

		glPointSize(3.0f);
		glColor3f(1.0f,1.0f,1.0f);
		//*glBegin(GL_POINTS);
		for( i=0;i<p;i++ )
			//*glVertex3fv(&m_path[i].pos.x);
		//*glEnd();
		//*glEnd();
		glPointSize(1.0f);
	}

	pVector v1,v2,v3,z,lastpos1,lastpos2;
	float j,s0,s1;
	bool use_tcmod=GLEW_ARB_multitexture&&(m_tcmod_texture!=-1);

	if (p<2)
		return;

	// if necessary, do animation on texture coordinates
	if (m_texture!=-1)
		if (g_render->pic[m_texture]->sx>g_render->pic[m_texture]->sy)
			m_num_frames=g_render->pic[m_texture]->sx/g_render->pic[m_texture]->sy;
		else
			m_num_frames=1;
	else
		m_num_frames=0;
	float si=0.0f,sf=1.0f;
	bool do_animation=m_frame_rate>0.0f && m_num_frames>1;
	if(do_animation)
	{
		int frame=(int)(m_frame_rate*(g_romanager->m_time-m_start_time));
		sf=1.0f/m_num_frames;
		si=sf*(frame%m_num_frames);
		sf+=si;
	}

	// set texture units
	if(use_tcmod)
	{
		// set current texture
		glActiveTextureARB(GL_TEXTURE0_ARB);
		g_render->sel_tex(m_texture);
		glActiveTextureARB(GL_TEXTURE1_ARB);
		g_render->sel_tex(m_tcmod_texture);

		// apply modifier on texture coordinates
		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glTranslatef(fmodf(m_tcmod_vel_s*g_romanager->m_time,1.0f),0.0f,0.0f);
	}
	else
		g_render->sel_tex(m_texture);

	if (m_blendadd)
	{
		if (g_render->fog)
		{
			pVector black(0);
			glFogfv(GL_FOG_COLOR,&black.x);
		}
		glBlendFunc(GL_ONE,GL_ONE);
	}
	else
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glDepthMask(GL_FALSE);
	
	//*glBegin(GL_QUAD_STRIP);
	for( i=0;i<p;i++ )
	{
		z=g_render->camera.pos-m_path[i].pos;
		z.normalize();
		v3.null();
		if (i>0)
		{
			v1=m_path[i].pos-m_path[i-1].pos;
			v2.cross(z,v1);
			v2.normalize();
			v3+=v2;
		}
		if (i<p-1)
		{
			v1=m_path[i+1].pos-m_path[i].pos;
			v2.cross(z,v1);
			v2.normalize();
			v3+=v2;
		}
		v3.normalize();

		j=m_duration-(g_romanager->m_time-m_path[i].vel.w);
		m_color.w=j<0.0f?0.0f:j<m_fade?j/m_fade:1.0f;
		glColor4fv(&m_color.x);

		s0=s1=(float)i/(p-1);
		if(do_animation)
			s0=(1-s0)*sf+s0*si;
						
		v1=m_path[i].pos+v3*m_width;
		v2=m_path[i].pos-v3*m_width;
//		if (i>0)
//			check_concave(lastpos1,lastpos2,v1,v2);
//		lastpos1=v1;
//		lastpos2=v2;
		if(use_tcmod)
		{
			glMultiTexCoord2f(GL_TEXTURE0_ARB,s0,0.0f);
			glMultiTexCoord2f(GL_TEXTURE1_ARB,s1,0.0f);
			//*glVertex3fv(&v1.x);
			glMultiTexCoord2f(GL_TEXTURE0_ARB,s0,1.0f);
			glMultiTexCoord2f(GL_TEXTURE1_ARB,s1,1.0f);
			//*glVertex3fv(&v2.x);
		}
		else
		{
			glTexCoord2f(s0,0.0f);
			//*glVertex3fv(&v1.x);
			glTexCoord2f(s0,1.0f);
			//*glVertex3fv(&v2.x);
		}
	}
	//*glEnd();

	// restore texture units
	if(use_tcmod)
	{
		// restore texture of unit texture 1
		g_render->sel_tex(-1);

		// restore matrix of unit texture 1
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);

		glActiveTextureARB(GL_TEXTURE0_ARB);
	}
#endif
}

int pROTrail::get_custom_param_desc(int i,pParamDesc *pd)
{
	if (pd!=0)
	switch(i)
	{
		case 0:
			pd->type='b';
			pd->data=&m_blendadd;
			pd->name="blendadd";
			pd->comment="Additive blend flag";
			break;
		case 1:
			pd->type='i';
			pd->data=&m_num_trail_points;
			pd->name="numtrailpoints";
			pd->comment="Maximum number of points in trail";
			break;
		case 2:
			pd->type='f';
			pd->data=&m_threshold;
			pd->name="threshold";
			pd->comment="Threshold in scene units for consecutive trail particles to be released";
			break;
		case 3:
			pd->type='f';
			pd->data=&m_width;
			pd->name="width";
			pd->comment="Width of trail rectangle";
			break;
		case 4:
			pd->type='c';
			pd->data=&m_color;
			pd->name="color";
			pd->comment="Trail main color";
			break;
		case 5:
			pd->type='p';
			pd->data=&m_texture;
			pd->name="texture";
			pd->comment="Trail texture map";
			break;
		case 6:
			pd->type='f';
			pd->data=&m_vel;
			pd->name="vel";
			pd->comment="Initial velocity for trail points";
			break;
		case 7:
			pd->type='f';
			pd->data=&m_duration;
			pd->name="duration";
			pd->comment="Duration of each trail point";
			break;
		case 8:
			pd->type='f';
			pd->data=&m_fade;
			pd->name="fade";
			pd->comment="The time trail points fade out before being destroyed";
			break;
		case 9:
			pd->type='f';
			pd->data=&m_frame_rate;
			pd->name="frame_rate";
			pd->comment="Frame rate for animation map";
			break;
		case 10:
			pd->type='p';
			pd->data=&m_tcmod_texture;
			pd->name="tcmod_texture";
			pd->comment="Second tetxure map to use with tcmod scroll";
			break;
		case 11:
			pd->type='f';
			pd->data=&m_tcmod_vel_s;
			pd->name="tcmod_vel_s";
			pd->comment="Scroll velocity for tcmod texture";
			break;
	}
	return 12;
}

void pROTrail::on_pos_parameter_change(int i)
{
	switch(i-P_RONUMDEFAULTPARAM)
	{
		case 1:
		{
			if (m_num_trail_points!=0)
			{
				m_path.resize(m_num_trail_points);
				m_delay=m_duration/m_num_trail_points;
			}
		}
		break;

		case 5:
		{
			if (m_texture!=-1)
				if (g_render->pic[m_texture]->sx>g_render->pic[m_texture]->sy)
					m_num_frames=g_render->pic[m_texture]->sx/g_render->pic[m_texture]->sy;
				else
					m_num_frames=1;
			else
				m_num_frames=0;
		}
		break;

		case 7:
		{
			if (m_num_trail_points!=0)
				m_delay=m_duration/m_num_trail_points;
		}
		break;
	};
}

void pROTrail::translate_world(const pVector& t)
{
	int i=0,j=m_path.length();
	for( ;i<j;i++ )
		m_path[i].pos+=t;

	pRenderObject::translate_world(t);
}

#endif
