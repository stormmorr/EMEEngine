/*

    UNSResource - Unification Server Resource Management
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef UNS_RESOURCE_H
#define UNS_RESOURCE_H

#include "../UnSRC/Utility/datatypes.h"

#define UNS_RES_LINE 0
#define UNS_RES_DATA 1
#define UNS_RES_PAGE 2
#define UNS_RES_CHAR_START 3
#define UNS_RES_CHAR 4

#define UNS_GET_FILE 1
#define UNS_DOC_NET 2

#define UNS_LINE_MAX 256
#define UNS_CHAR_PACKET 5

typedef struct UNSRequest
{
public:
	UNSRequest() {};
	~UNSRequest() {};

	const char *m_FileChar;
	std::string m_Filename;
	unsigned int m_Address_S;
	unsigned int m_Address_E;

	Uint8 m_RequestType;

	float timeStamp;
	int typeId;

	int m_SysAddress;
	int m_Count;
} UNSRequest;

#endif