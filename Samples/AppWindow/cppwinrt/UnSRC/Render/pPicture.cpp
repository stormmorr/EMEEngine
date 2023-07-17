#include "pch.h"
#include "paralelo3d.h"

#include <iostream>

#ifndef P_DISABLE_JPG
#include "jpeg.h"
#endif

#define ROUND(x) ((x)>=0?((int)(x)):((int)(x)-1))

pPicture::pPicture(pPicture& in) :
	sx(in.sx),sy(in.sy),sz(in.sz),
	bytespixel(in.bytespixel),
	size(in.size),
	refcount(in.refcount),
	flags(in.flags)
{ 
	buf=new unsigned char[size];
	memcpy(buf,in.buf,size);
}

void pPicture::operator=(const pPicture& in)
{
	FreePicture();

	sx=in.sx;
	sy=in.sy;
	sz=in.sz;
	bytespixel=in.bytespixel;
	size=size;
	name=in.name;
	flags=in.flags;
	refcount=in.refcount;

	if (size)
	{
		buf=new unsigned char[size];
		memcpy(buf,in.buf,size);
	}
}

void pPicture::FreePicture(void)
{
	delete[] buf;
	buf=0;

}

void pPicture::CreatePicture(int bp,int xd,int yd,int zd)
{
	FreePicture();

    sx=xd; sy=yd; sz=zd; bytespixel=bp;
	size=sx*sy*sz*bytespixel;

	buf=new unsigned char[size];
}

void pPicture::CreatePicture32(int xd,int yd)
{
	FreePicture();

    sx=xd; sy=yd; sz=1; bytespixel=4;
	size=sx*sy*bytespixel;

	buf=new unsigned char[size];
}

void pPicture::CreatePicture24(int xd,int yd)
{
	FreePicture();

    sx=xd; sy=yd; sz=1; bytespixel=3;
	size=sx*sy*bytespixel;

	buf=new unsigned char[sx*sy*bytespixel];
}

int pPicture::LoadTGA(const unsigned char *data,int len)
{
	int x_pos1, x_pos2, y, i, p, cursize;
	unsigned char flag, pixel_order;
	int filepos=18;

	FreePicture();

	sx=sy=0;
		
	if(!((data[16]==8 || data[16]==24 || data[16]==32) && (data[2]==2 || data[2]==3 || data[2]==10)))
		return 0;

	sx=*((unsigned short *)&data[12]);
	sy=*((unsigned short *)&data[14]);

	if(data[16]==8)
		CreatePicture(1,sx,sy);
	else
	if(data[16]==24)
		CreatePicture24(sx,sy);
	else
		CreatePicture32(sx,sy);

	pixel_order=data[17]&0x30;

	filepos+=data[0];

	if (data[2]==2 || data[2]==3)
		memcpy(buf,&data[filepos],size);
	else
	{
		unsigned char *pb=buf, *q, c;

		cursize=0;
		while(cursize<sx*sy)
		{
			c=data[filepos++];
			if((c&0x80))
			{
				c=(c&0x7f)+1;
				memcpy(pb,&data[filepos],bytespixel);
				filepos+=bytespixel;
				q=pb;
				for(i=1; i<c; i++)
				{
					q+=bytespixel;
					q[0]=pb[0];
					q[1]=pb[1];
					q[2]=pb[2];
				}
				pb=q;
				pb+=bytespixel;
			}
			else
			{
				c++;
				memcpy(pb,&data[filepos],c*bytespixel);
				filepos+=c*bytespixel;
				pb+=c*bytespixel;
			}
			cursize+=c;
		}
	}

	if (pixel_order&0x20)
		FlipY();

	for( y=0;y<sy;y++ )
	{
		x_pos1=0;
		if (bytespixel>1)
		for(p=0; p<sx; p++)
		{
			flag=buf[y*sx*bytespixel+x_pos1+2];
			buf[y*sx*bytespixel+x_pos1+2]=buf[y*sx*bytespixel+x_pos1];
			buf[y*sx*bytespixel+x_pos1]=flag;
			x_pos1+=bytespixel;
		}
		if(pixel_order&0x10)
		{
			x_pos1=0;
			x_pos2=(sx-1)*bytespixel;
			for(p=0; p<sx/2; p++)
			{
				for(i=0; i<bytespixel; i++)
				{
					flag=buf[y*sx*bytespixel+x_pos2+i];
					buf[y*sx*bytespixel+x_pos2+i]=buf[y*sx*bytespixel+x_pos1+i];
					buf[y*sx*bytespixel+x_pos1+i]=flag;
				}
				x_pos1+=bytespixel;
				x_pos2-=bytespixel;
			}
		}
	}

	return 1;
}

int pPicture::SaveTGA(const char *file)
{
    FILE *fp;
    int a,b;
    unsigned char TGA_INI[18];
    unsigned char *picline;

    picline=new unsigned char[sx*bytespixel];
    if (!picline)
       return 0;

    if ((fp=fopen(file,"wb"))!=0)
       {
        memset(&TGA_INI[0],0,18);
        TGA_INI[12]=(unsigned char)(sx%256);
        TGA_INI[13]=(unsigned char)(sx/256);
        TGA_INI[14]=(unsigned char)(sy%256);
        TGA_INI[15]=(unsigned char)(sy/256);
        TGA_INI[2]=2;
        TGA_INI[16]=8*bytespixel;
		TGA_INI[17]=0x20;
        fwrite((char *)&TGA_INI[0],18,1,fp);
        for( a=sy-1;a>=0;a-- )
             {
              for( b=0;b<sx;b++ )
                   {
					if (bytespixel==1)
						picline[b*bytespixel]=buf[(a*sx+b)*bytespixel];
					else
					{
						picline[b*bytespixel]=buf[(a*sx+b)*bytespixel+2];
						picline[b*bytespixel+1]=buf[(a*sx+b)*bytespixel+1];
						picline[b*bytespixel+2]=buf[(a*sx+b)*bytespixel];
						if (bytespixel==4)
							picline[b*bytespixel+3]=buf[(a*sx+b)*bytespixel+3];
					}
                   }
              if (fwrite((char *)picline,sx,bytespixel,fp)!=(unsigned int)bytespixel)
                 {
                  fclose(fp);
                  delete[] picline;
                  return 0;
                 }
             }
        fclose(fp);
       }
    delete[] picline;
    return 1;
}

int pPicture::SaveJPG(const char *file,int quality,int progressive)
{
	if (buf==0 || file==0)
		return 0;

	FILE *fp=fopen(file,"wb");
	if (fp==0)
		return 0;

	int rslt=SaveJPG(fp,quality,progressive);

    fclose(fp);
	
	return rslt;
}

int pPicture::SaveJPG(FILE *fp,int quality,int progressive)
{
#ifndef P_DISABLE_JPG
	JPEGDATA data;

	memset(&data,0,sizeof(JPEGDATA));
	data.output_file=fp;
	data.ptr=buf;
	data.quality=quality;
	data.width=sx;
	data.height=sy;
	data.aritcoding=0;
	data.CCIR601sampling=0;
	data.smoothingfactor=0;
	data.numscan=progressive;

	//*jpeg_write(&data);

	if (data.status==0)
		return 1;
	return 0;
#else
	return 0;
#endif
}

int pPicture::LoadTGA(const char *file)
{
	pFile fp;
	if (fp.open(file)==false)
		return false;

	int ret=LoadTGA(fp.buf,fp.len);

	fp.close();

	return ret;
}

int pPicture::LoadJPG(const char *file)
{
	pFile fp;
	if (fp.open(file)==false)
		return false;

	int ret=LoadJPG(fp.buf,fp.len);

	fp.close();

	return ret;
}

int pPicture::LoadJPG(const unsigned char *data,int len)
{
#ifndef P_DISABLE_JPG
	JPEGDATA jpgdata;

	memset(&jpgdata,0,sizeof(JPEGDATA));

	FILE2 f2;
	f2.buffer=(char *)data;
	f2.len=len;
	jpgdata.input_file=&f2;
	
	f2.pos=0;
	//*jpeg_info(&jpgdata);

	if (jpgdata.status==1 && jpgdata.numscan<=1)
		return 0;

	if (jpgdata.components==1)
		CreatePicture(1,jpgdata.width,jpgdata.height);
	else
	if (jpgdata.components==3)
		CreatePicture24(jpgdata.width,jpgdata.height);

	f2.pos=0;
	jpgdata.ptr=buf;
	//*jpeg_read(&jpgdata);

	FlipY();

	if (jpgdata.status==0 || jpgdata.numscan>1)
		return 1;
#endif

	return 0;
}

int pPicture::LoadPIC(const char *file)
{
	int ret=0;
	const char *c=strrchr(file,'.');
	if ((unsigned int)(c-file)==strlen(file)-4)
	{
		if (!_stricmp(c,".tga"))
			ret=LoadTGA(file);
		else
		if (!_stricmp(c,".jpg"))
			ret=LoadJPG(file);
		else
		if (!_stricmp(c,".t3d"))
			ret=LoadT3D(file);
	}
	return ret;
}

void pPicture::GetPixel(int x,int y,pVector& rgb) const
{
	if (buf==0 || sz!=1)
		return;

	x=(x%sx);
	y=(y%sy);

	if(x<0)
		x=sx+x;
	if(y<0)
		y=sy+y;

	int pos=(y*sx+x)*bytespixel;

	if (bytespixel==3)
		rgb.vec(buf[pos]/255.0f,buf[pos+1]/255.0f,buf[pos+2]/255.0f);
	else 
		rgb.vec(buf[pos]/255.0f,buf[pos+1]/255.0f,buf[pos+2]/255.0f,buf[pos+3]/255.0f);
}

void pPicture::CheckSize(int droplevel)
{
	if (buf==0 || sz!=1)
		return;

	int levelx=-1,levely=-1;
	int newsx,newsy;
	int i,j,k;

	i=1;
	while(levelx==-1)
	{
		j=1<<i;
		if (sx==j)
			levelx=i;
		else if (sx<j)
			levelx=i-1;
		i++;
	}
	i=1;
	while(levely==-1)
	{
		j=1<<i;
		if (sy==j)
			levely=i;
		else if (sy<j)
			levely=i-1;
		i++;
	}
	levelx-=droplevel;
	levely-=droplevel;
	if (levelx<0)
		levelx=0;
	if (levely<0)
		levely=0;
	newsx=1<<levelx;
	newsy=1<<levely;
	if (newsx==sx && newsy==sy)
		return;

	unsigned char *data=new unsigned char[newsx*newsy*bytespixel];
	int x,y,xx,yy,xy,p=0,rgba[4];
	for( y=0;y<newsy;y++ )
	for( x=0;x<newsx;x++ )
	{
		xx=(x+1)*sx/newsx;
		yy=(y+1)*sy/newsy;
		xy=(xx-x*sx/newsx)*(yy-y*sy/newsy);
		rgba[0]=rgba[1]=rgba[2]=rgba[3]=0;
		for( j=y*sy/newsy;j<yy;j++ )
			for( i=x*sx/newsx;i<xx;i++ )
				for( k=0;k<bytespixel;k++ )
					rgba[k]+=buf[(j*sx+i)*bytespixel+k];
		
		for( k=0;k<bytespixel;k++ )
			data[p+k]=rgba[k]/xy;
		p+=k;
	}
	
	delete[] buf;
	buf=data;
	sx=newsx;
	sy=newsy;
	size=sx*sy*bytespixel;
}

void pPicture::FlipY()
{
	if (buf==0 || sz!=1)
		return;

	unsigned char *line=new unsigned char[bytespixel*sx];
	for( int i=0;i<sy/2;i++ )
		{
		memcpy(line,&buf[i*sx*bytespixel],bytespixel*sx);
		memcpy(&buf[i*sx*bytespixel],&buf[(sy-i-1)*sx*bytespixel],bytespixel*sx);
		memcpy(&buf[(sy-i-1)*sx*bytespixel],line,bytespixel*sx);
		}
	delete[] line;
}

void pPicture::GetPixel(float x,float y,pVector& rgb,int texfilter) const
{
	if (buf==0 || sz!=1)
		return;

	int xi,yi;
	
	xi=ROUND(x);
	yi=ROUND(y);
	if (texfilter==0)
	{
		GetPixel(xi,yi,rgb);
		return;
	}
	
	pVector c1,c2,c3,c4;
	
	float f=x-xi;
	GetPixel(xi,yi,c1);
	GetPixel(xi+1,yi,c2);
	c3=c2*f+c1*(1.0f-f);

	GetPixel(xi,yi+1,c1);
	GetPixel(xi+1,yi+1,c2);
	c4=c2*f+c1*(1.0f-f);

	f=y-yi;
	rgb=c4*f+c3*(1.0f-f);
}

void pPicture::GetPixelDxDy(float x,float y,float& dx,float& dy,int texfilter) const
{
	if (buf==0 || sz!=1)
		return;

	pVector rgb;
	x*=sx;
	y*=sy;

	GetPixel(x+1,y,rgb,texfilter);
	dx=rgb.color_intensity();
	GetPixel(x-1,y,rgb,texfilter);
	dx-=rgb.color_intensity();

	GetPixel(x,y+1,rgb,texfilter);
	dy=rgb.color_intensity();
	GetPixel(x,y-1,rgb,texfilter);
	dy-=rgb.color_intensity();
}

void pPicture::ToNormalMap(pPicture& p,float factor)
{
	if (buf==0 || sz!=1)
		return;

	if (p.bytespixel==4)
		p.CreatePicture32(sx,sy);
	else
		p.CreatePicture24(sx,sy);

	p.flags=P_PICFLAGS_NORMALMAP;

	int x,y;
	int dx,dy;
	pVector n;
	unsigned char *rgb=p.buf;

	for( y=0;y<sy;y++ )
	for( x=0;x<sx;x++ )
	{
		dx=GetGrayPixel(x-1,y-1)*-1;
		dx+=GetGrayPixel(x-1,y)*-2;
		dx+=GetGrayPixel(x-1,y+1)*-1;
		dx+=GetGrayPixel(x+1,y-1)*1;
		dx+=GetGrayPixel(x+1,y)*2;
		dx+=GetGrayPixel(x+1,y+1)*1;

		dy=GetGrayPixel(x-1,y+1)*-1;
		dy+=GetGrayPixel(x,y+1)*-2;
		dy+=GetGrayPixel(x+1,y+1)*-1;
		dy+=GetGrayPixel(x-1,y-1)*1;
		dy+=GetGrayPixel(x,y-1)*2;
		dy+=GetGrayPixel(x+1,y-1)*1;

		n.vec(dx/-255.0f,dy/-255.0f,factor);
		n.normalize();

		rgb[0]=(unsigned char)((n.x+1.0)*127.5f);
		rgb[1]=(unsigned char)((n.y+1.0)*127.5f);
		rgb[2]=(unsigned char)((n.z+1.0)*127.5f);
		rgb+=3;
		if (p.bytespixel==4)
		{
			rgb[0]=p.buf[4*(x+y*p.sx)+3];
			rgb++;
		}
	}
}

int pPicture::PixelDifference(int x1,int y1,int x2,int y2)
{
	if (buf==0 || sz!=1)
		return 0;

	unsigned char *rgb1,*rgb2;
	rgb1=&buf[bytespixel*(x1+y1*sx)];
	rgb2=&buf[bytespixel*(x2+y2*sx)];
	return (abs((int)rgb1[0]-(int)rgb2[0])+
		abs((int)rgb1[1]-(int)rgb2[1])+
		abs((int)rgb1[2]-(int)rgb2[2]))/3;
}

int pPicture::ShouldAntiAlias(int x,int y,int factor)
{
	if (buf==0 || sz!=1)
		return 0;

	int dif=0,d;
	if (x>0) 
	{
		d=PixelDifference(x-1,y,x,y);
		if (d>dif)
			dif=d;
	}
	if (x<sx-1)
	{
		d=PixelDifference(x+1,y,x,y);
		if (d>dif)
			dif=d;
	}
	if (y>0)
	{
		d=PixelDifference(x,y-1,x,y);
		if (d>dif)
			dif=d;
	}
	if (y<sy-1)
	{
		d=PixelDifference(x,y+1,x,y);
		if (d>dif)
			dif=d;
	}
	return dif>factor;
}

void pPicture::BuildDepthLine(
	float *line,int px,int py,int dx,int dy,
	int sizex,int sizey,int axis,float factor)
{
	int x,i,j;
	float d,f,n,nz,pf;

	axis=!axis;
	j=px+py*sizex;
	i=j*4;
	d=0;
	line[0]=d;
	j+=dx;
	i+=dx*4;
	pf=0;
	for( x=1;x<sizex;x++ )
	{
		n=buf[i+axis]/127.5f-1.0f;
		nz=buf[i+2]/127.5f-1.0f;
		n/=sqrtf(n*n+nz*nz);
		if (n>-0.01f && n<0.01f)
			n=0;
		if (n>-0.98f && n<0.98f)
		{
			f=asinf(n);
			f=tanf(f);
			f*=factor;
			d+=(f+pf)*0.5f;
			pf=f;
		}
		line[x]=d;
		j+=dx;
		i+=dx*4;
	}
}

void pPicture::BuildDepthMap(
	float *depth,float *line,int px,int py,int dx,int dy,
	int sizex,int sizey,int axis,float factor)
{
	int x,y,i,j;
	float d,f,n,nz,pf;
	for( x=0;x<sizex;x++ )
	{
		j=px+py*sizex+x*dx;
		i=j*4;
		d=line[x];
		depth[j]=d;
		j+=dy;
		i+=dy*4;
		pf=0;
		for( y=1;y<sizey;y++ )
		{
			n=buf[i+axis]/127.5f-1.0f;
			nz=buf[i+2]/127.5f-1.0f;
			n/=sqrtf(n*n+nz*nz);
			if (n>-0.01f && n<0.01f)
				n=0;	
			if (n>-0.99f && n<0.99f)
			{
				f=asinf(n);
				f=tanf(f);
				f*=factor;
				d+=(f+pf)*0.5f;
				pf=f;
			}
			depth[j]+=d;
			j+=dy;
			i+=dy*4;
		}
	}
}

void pPicture::BuildDepthMap(unsigned dirflags)
{
	if (bytespixel==3)
	{
		unsigned char *b=buf;
		buf=0;
		CreatePicture32(sx,sy);
		int x,y,p1=0,p2=0;
		for( y=0;y<sy;y++ )
		for( x=0;x<sx;x++ )
		{
			buf[p1]=b[p2];
			buf[p1+1]=b[p2+1];
			buf[p1+2]=b[p2+2];
			buf[p1+3]=0;
			p1+=4;
			p2+=3;
		}
		delete[] b;
	}
	else
	if (bytespixel!=4)
		return;

	float min[4],max[4];
	float *depth[4]={ 0,0,0,0 };
	if (dirflags&1) depth[0]=new float[sx*sy];
	if (dirflags&2) depth[1]=new float[sx*sy];
	if (dirflags&4) depth[2]=new float[sx*sy];
	if (dirflags&8) depth[3]=new float[sx*sy];
	float *line=new float[sx>sy?sx:sy];
	float d,f;

	int x,y,i,j,k;
	int N=4,M=0;

	j=sx*sy;
	for( k=0;k<4;k++ )
	if (dirflags&(1<<k))
	for( i=0;i<j;i++ )
		depth[k][i]=0;

	j=sx>sy?sx:sy;

	if (dirflags&1)
	{
	BuildDepthLine(line,0,0,sx,1,sy,sx,0,1);
	BuildDepthMap(depth[0],line,0,0,sx,1,sy,sx,0,1);
	M++;
	}

	if (dirflags&2)
	{
	BuildDepthLine(line,sx-1,0,sx,-1,sy,sx,0,1);
	BuildDepthMap(depth[1],line,sx-1,0,sx,-1,sy,sx,0,-1);
	M++;
	}

	if (dirflags&4)
	{
	BuildDepthLine(line,0,0,1,sx,sx,sy,1,1);
	BuildDepthMap(depth[2],line,0,0,1,sx,sx,sy,1,1);
	M++;
	}

	if (dirflags&8)
	{
	BuildDepthLine(line,0,sy-1,1,-sx,sx,sy,1,1);
	BuildDepthMap(depth[3],line,0,sy-1,1,-sx,sx,sy,1,-1);
	M++;
	}

	for( k=0;k<N;k++ )
	{
		min[k]=0;
		max[k]=0;
	}
	j=0;
	for( k=0;k<N;k++ )
	if (dirflags&(1<<k))
	{
		j=0;
		for( y=0;y<sy;y++ )
		for( x=0;x<sx;x++ )
		{
			{
				if (depth[k][j]<min[k])
					min[k]=depth[k][j];
				if (depth[k][j]>max[k])
					max[k]=depth[k][j];
			}
			j++;
		}
	}

	i=3;
	j=0;
	for( y=0;y<sy;y++ )
	for( x=0;x<sx;x++ )
	{
		d=0;
		for( k=0;k<N;k++ )
		if (dirflags&(1<<k))
		{
			f=max[k]-min[k];
			if (f>0.01f)
				d+=(depth[k][j]-min[k])/f;
		}
		d/=M;
		buf[i]=(unsigned char)(d*255.0f);
		i+=4;
		j++;
	}

	delete depth[0];
	delete depth[1];
	delete depth[2];
	delete depth[3];
	delete line;
}

int pPicture::SaveT3D(const char *file)
{
	if (buf==0 || file==0)
		return 0;

	FILE *fp=fopen(file,"wb");
	if (fp==0)
		return 0;

	unsigned mn=*((unsigned *)(".T3D"));

	fwrite(&mn,1,sizeof(int),fp);
	fwrite(&bytespixel,1,sizeof(int),fp);
	fwrite(&sx,1,sizeof(int),fp);
	fwrite(&sy,1,sizeof(int),fp);
	fwrite(&sz,1,sizeof(int),fp);
	fwrite(buf,sx*sy,sz*bytespixel,fp);

    fclose(fp);
	
	return 1;
}

int pPicture::LoadT3D(const char *file)
{
	FILE *fp=fopen(file,"rb");
	if (fp==0)
		return 0;
	
	unsigned mn=*((unsigned *)(".T3D"));
	unsigned i;
	fread(&i,1,sizeof(int),fp);
	if (i!=mn)
		return 0;

	fread(&bytespixel,1,sizeof(int),fp);
	fread(&sx,1,sizeof(int),fp);
	fread(&sy,1,sizeof(int),fp);
	fread(&sz,1,sizeof(int),fp);
	flags=P_PICFLAGS_TEX3D;

	CreatePicture(bytespixel,sx,sy,sz);

	fread(buf,sx*sy,sz*bytespixel,fp);

    fclose(fp);
	
	return 1;
}
