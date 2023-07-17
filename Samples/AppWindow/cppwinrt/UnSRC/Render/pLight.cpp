#include "pch.h"
#include "paralelo3d.h"

void pLight::write(FILE *fp) const
{
	name.write(fp);
	fwrite(&pos.x,4,sizeof(float),fp);
	fwrite(&color.x,3,sizeof(float),fp);
	fwrite(&flags,1,sizeof(int),fp);
	anim_pos_x.write(fp);
	anim_pos_y.write(fp);
	anim_pos_z.write(fp);
	anim_radius.write(fp);
	anim_color.write(fp);
}

void pLight::read(pFile& fp,int ver)
{
	name.read(fp);
	fp.read(&pos.x,4*sizeof(float));
	fp.read(&color.x,3*sizeof(float));
	fp.read(&flags,sizeof(int));
	if(ver>=P3D_FILEVER+3)
	{
		anim_pos_x.read(fp,ver);
		anim_pos_y.read(fp,ver);
		anim_pos_z.read(fp,ver);
	}
	else
	{
		pAnimation a;
		a.read(fp,ver);
	}
	anim_radius.read(fp,ver);
	anim_color.read(fp,ver);
}

bool pLight::update_objects_light(pRenderObject *obj)
{
	bool ret=false;

	if(flags&P_LIGHTFLAGS_ENABLED)
	{
		if (flags&P_LIGHTFLAGS_GLOBAL)
			ret=true;
		else
		if(angle>0.0f) // spot light
		{
			if(frustum.clip_bbox(obj->m_bbox_global))
				ret=true;
		}
		else // omni light
		{
			if(bbox.clip_bbox(obj->m_bbox_global.min,obj->m_bbox_global.max))
				ret=true;
		}

		if (ret && g_render->shadowflag)
			objlistlight.add(obj);
	}

	return ret;
}

void pLight::build_frustum()
{
	frustum.build(
		pos,
		orientation.get_column3(0),orientation.get_column3(1),orientation.get_column3(2),
		angle,1.0f,pos.w);
}
		
void pLight::turn_on(unsigned light_id) const
{
#ifndef P_DISABLE_3D
	pVector v;

	v.vec(pos.x,pos.y,pos.z,1.0f);
	glLightfv(light_id,GL_POSITION,&v.x);

	v.vec(color.x,color.y,color.z,1.0f);
	glLightfv(light_id,GL_DIFFUSE,&v.x);
	glLightfv(light_id,GL_SPECULAR,&v.x);
	glLightf(light_id,GL_LINEAR_ATTENUATION,2.0f/pos.w);

	if(angle>0.0f)
	{
		glLightf(light_id,GL_SPOT_CUTOFF,angle*0.5f);
		v=-orientation.get_column3(2);
		glLightfv(light_id,GL_SPOT_DIRECTION,&v.x);
	}
	else
		glLightf(light_id,GL_SPOT_CUTOFF,180.0f);

	glEnable(light_id);
#endif
}

void pLight::animate(float time)
{
	anim_pos_x.update_loop(time,&pos.x);
	anim_pos_y.update_loop(time,&pos.y);
	anim_pos_z.update_loop(time,&pos.z);
	anim_radius.update_loop(time,&pos.w);
	anim_color.update_loop(time,&color.x);
}
