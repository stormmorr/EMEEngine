/*

    BitTransfer.h - Data Transportation Container
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	the rights to use, modify, and/or relicense this code without notice.

*/

#ifndef BITTRANSFER_H
#define BITTRANSFER_H

#include "../UnSRC/Utility/RakNetMsgIdentOSI.h"
#include "unStringCompressorOSI.h"
#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"

#if 0
#define BT_TYPE_
#endif

#define BITS_TO_BYTES(x) (((x)+7)>>3)
#define BYTES_TO_BITS(x) ((x)<<3)

#define BT_CHAR_DATA 0

#define BT_SIZE_CHAR 1000000

#if 1
#define BT_DEBUG 1
#else
#define BT_DEBUG 0
#endif

class BitTransfer
{
public:
	BitTransfer();
	BitTransfer(unsigned char i_Ident);
	BitTransfer(unsigned char i_Ident, unsigned char i_Type);
	BitTransfer(unsigned char* i_Data, const unsigned int i_LengthInBytes, bool i_Copy);
	~BitTransfer();

	unsigned int m_BitsUsed;
	unsigned int m_Allocated;
	unsigned int m_ReadOffset;

	unsigned char* m_Data;

	unsigned char acTag(void);
	float acTimeStamp(void);

	void acAssertEmpty(void);

	void acPrintBits(char *out) const;
	void acPrintBits(void) const;

	inline unsigned int acSize(void) { return BITS_TO_BYTES(m_BitsUsed); }
	inline unsigned int acSizeBits(void) { return m_BitsUsed; }
	inline unsigned int acSizeUnreadBits(void) const { return m_BitsUsed - m_ReadOffset; }

	inline void acReset(void) { m_BitsUsed = 0; m_ReadOffset = 0; }

template <class templateType>
	void acPush(templateType var);
template <class templateType>
	void acPushAlloc(templateType var);
template <class templateType>
	bool acRead(templateType &var);

	void acPush(bool var);

template <class templateType>
	void acPushCompressed(templateType var);

template <class templateType>
	bool acReadCompressed(templateType &var);

	void acAddbits(const unsigned char* i_Input, unsigned int i_BitCount);
	void acAddbitsFast(const unsigned char* i_Input, unsigned int i_BitCount);
	void acAddbitsNonAlligned(const unsigned char* i_Input, unsigned int i_BitCount);
	void acAddbitsCompressed(const unsigned char* i_Input, const unsigned int i_Size, const bool i_UnsignedData);

	void acAddbit0(void);
	void acAddbit1(void);

	bool acReadBit(void);

	unsigned int acCopyData(unsigned char** i_Data) const;

private:
	bool acReadBits(unsigned char *i_Output, unsigned int i_BitsToRead);
	void acReadBitsNonAlligned(unsigned char *i_Output, unsigned int i_BitsToRead);
	bool acReadCompressed(unsigned char* i_Output, const unsigned int i_Size, const bool i_UnsignedData);

	void acExpand(unsigned int i_BitCount);
	void acExpandSection(unsigned int i_BitCount);
};

class BitTemplate
{
public:
	BitTemplate();
	BitTemplate(unsigned char i_Ident);
	BitTemplate(unsigned char* i_Data, const unsigned int i_LengthInBytes, bool i_Copy);
	~BitTemplate();

	unsigned int m_BitsUsed;

	inline unsigned int acSize(void) { return BITS_TO_BYTES(m_BitsUsed); }
	inline unsigned int acSizeBits(void) { return m_BitsUsed; }

	inline void acReset(void) { m_BitsUsed = 0; }

template <class templateType>
	void acPushAlloc(templateType var);

	void acAddbits(unsigned int i_BitCount);
};

template <class templateType>
inline void BitTransfer::acPush(templateType var)
	{
	acAddbitsFast((unsigned char*) &var, sizeof(templateType) * 8);
	}

template <class templateType>
inline void BitTransfer::acPushAlloc(templateType var)
	{
	acAddbits((unsigned char*) &var, sizeof(templateType) * 8);
	}

template <class templateType>
inline void BitTransfer::acPushCompressed(templateType var)
	{
	acAddbitsCompressed((unsigned char*) &var, sizeof(templateType) * 8, true);
	}

inline void BitTransfer::acPush(bool var)
	{
	if(var)
		acAddbit1();
	else
		acAddbit0();
	}

template <class templateType>
inline bool BitTransfer::acRead(templateType &var)
	{
	return acReadBits((unsigned char*) &var, sizeof(templateType) * 8);
	}

template <>
inline bool BitTransfer::acRead(bool &var)
	{
	if(m_ReadOffset + 1 > m_BitsUsed)
		return false;

	if(m_Data[m_ReadOffset >> 3] & (0x80 >> (m_ReadOffset & 7)))   // Is it faster to just write it out here?
		var = true;
	else
		var = false;

	// Has to be on a different line for Mac
	m_ReadOffset++;

	return true;
	}

template <class templateType>
inline bool BitTransfer::acReadCompressed(templateType &var)
	{
	return acReadCompressed((unsigned char*) &var, sizeof(templateType) * 8, true);
	}

template <class templateType>
inline void BitTemplate::acPushAlloc(templateType var)
	{
	acAddbits(sizeof(templateType) * 8);
	}

#endif