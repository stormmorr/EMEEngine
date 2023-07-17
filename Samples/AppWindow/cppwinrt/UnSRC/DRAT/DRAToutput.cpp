/*

	DRAT Definition ALPHA - Deep Recursive Attributes
	Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "DRATdef.h"
#include "DRATutility.h"

namespace DRAT
{

bool FileGen(DRAT::FileDescriptor i_File)
	{
	FILE			*stream;
	const char		*Filename;
	int				i;

	//// Sub Path
	Filename = "c:\\DRAT\\";
	AppendStr(Filename, i_File.m_Filename.c_str());
	if(i_File.SaveIncrement) RandomStr(Filename, 5);

	//##### - Open our Data File
	stream = fopen(Filename, "w");

	//##### - UN Structure Output #####//

	//for(i = 0; i < i_File.m_class.size(); ++i)
	//	{
		//i_File.m_class[i].getPublic()->m_sheet

		//std::vector<Uint16> m_list;
		//std::vector<trr::trrBinaryCube> BCube;

		//Uint16* buffer = new Uint[layercnt+vixcnt];
		//buffer[i] = layercnt+vixcnt;

		//fwrite(buffer, 1, layercnt+vixcnt, stream);
	//	}

	

	// DRAT Output
	for(i = 0; i < i_File._dratAttr.m_Nom; ++i)
		fprintf(stream, "%f ", i_File._dratAttr.acServeAttribute(i));

#if 0
	//##### - Set Q_MeMPathway->MeMPathway[K].InputType
	Integer = Q_MeMPathway->MeMPathway[K].InputType;
	fprintf(stream,"%d ",Integer);

	//##### - Set Q_MeMPathway->MeMPathway[K].ControlType
	Integer = Q_MeMPathway->MeMPathway[K].ControlType;
	fprintf(stream,"%d ",Integer);

	//##### - Set Q_MeMPathway->MeMPathway[K].OutputType
	Integer = Q_MeMPathway->MeMPathway[K].OutputType;
	fprintf(stream,"%d ",Integer);

	//##### - Set Q_MeMPathway->MeMPathway[K].Active
	Integer = Q_MeMPathway->MeMPathway[K].Active;
	fprintf(stream,"%d ",Integer);

	//##### - Set Q_MeMPathway->MeMPathway[K].InputRange
	Float = Q_MeMPathway->MeMPathway[K].InputRange;
	fprintf(stream,"%f ",Float);
#endif

	return true;
	}

};