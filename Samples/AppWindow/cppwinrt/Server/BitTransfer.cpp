/*

    BitTransfer.h - Data Transportation Container
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retains
	*/#include "pch.h"/*the rights to use, modify, and/or relicense this code without notice.

*/

#include "BitTransfer.h"
//*#include "GetTime.h"
#include "stdio.h"

BitTransfer::BitTransfer()
{
#pragma message("FIX:::Add packet modes and modescribe")
	m_Allocated = 1024 * 8;
	m_BitsUsed = 0;
	m_ReadOffset = 0;
	m_Data = (unsigned char*)malloc((unsigned int)BITS_TO_BYTES(m_Allocated));
}

BitTransfer::BitTransfer(unsigned char i_Ident)
{
#pragma message("FIX:::Add packet modes and modescribe")
	m_Allocated = 1024 * 8;

	m_BitsUsed = 0;
	m_ReadOffset = 0;
	m_Data = (unsigned char*)malloc((unsigned int)BITS_TO_BYTES(m_Allocated));

	//*float i_TimeStamp = RakNet::GetTime();
	//*unsigned char i_Id_TimeStamp = ID_TIMESTAMP;
	//*acAddbits((unsigned char*) &i_Id_TimeStamp, 8);
	//*acAddbits((unsigned char*) &i_TimeStamp, 32);
	//*acAddbits((unsigned char*) &i_Ident, 8);
}

BitTransfer::BitTransfer(unsigned char i_Ident, unsigned char i_Type)
{
	switch(i_Type)
		{
		case BT_CHAR_DATA:
			{
#if 0
			m_Allocated = 1024 * 8;
#endif
#if 1
			m_Allocated = BT_SIZE_CHAR;
#endif
#if 0
			m_Allocated = 1024 * 8 * 1550;
#endif
			}break;

		default:
			{
#if 1
			m_Allocated = 1024 * 8;
#endif
#if 0
			m_Allocated = BT_SIZE_CHAR;
#endif
			}break;
		}

	m_BitsUsed = 0;
	m_ReadOffset = 0;
	m_Data = (unsigned char*)malloc((unsigned int)BITS_TO_BYTES(m_Allocated));

	//*float i_TimeStamp = RakNet::GetTime();
	//*unsigned char i_Id_TimeStamp = ID_TIMESTAMP;
	//*acAddbits((unsigned char*) &i_Id_TimeStamp, 8);
	//*acAddbits((unsigned char*) &i_TimeStamp, 32);
	//*acAddbits((unsigned char*) &i_Ident, 8);
}

BitTransfer::BitTransfer(unsigned char* i_Data, const unsigned int i_LengthInBytes, bool i_Copy)
{
	m_ReadOffset = 0;
	m_BitsUsed = i_LengthInBytes << 3;
	m_Allocated = i_LengthInBytes << 3;

#if defined(BT_DEBUG)
	if(i_LengthInBytes <= 0)
		{
		printf("ERROR:::BT_DEBUG BitTransfer constructor recieved null data\n");
		//for(;;) {};
		}
#endif

	if(i_Copy)
		{
		m_Data = (unsigned char*)malloc((unsigned int)i_LengthInBytes);

		memcpy(m_Data, i_Data, (unsigned int)i_LengthInBytes);
		}
	else m_Data = (unsigned char*)i_Data;
}

BitTransfer::~BitTransfer()
{
	//free(m_Data);
}

BitTemplate::BitTemplate()
{
	m_BitsUsed = 0;
}

BitTemplate::BitTemplate(unsigned char i_Ident)
{
	m_BitsUsed = 0;

	acAddbits(8);
	acAddbits(32);
	acAddbits(8);
}

BitTemplate::BitTemplate(unsigned char* i_Data, const unsigned int i_LengthInBytes, bool i_Copy)
{
	m_BitsUsed = i_LengthInBytes << 3;

#if defined(BT_DEBUG)
	if(i_LengthInBytes <= 0)
		{
		printf("ERROR:::BT_DEBUG BitTransfer constructor recieved null data\n");
		//for(;;) {};
		}
#endif
}

BitTemplate::~BitTemplate()
{

}

void BitTransfer::acAddbits(const unsigned char* i_Input, unsigned int i_BitCount)
{
	if (i_BitCount<=0)
		return;

	acExpand(i_BitCount);

	unsigned int i_i_Offset = 0;
	unsigned char i_DataByte;
	unsigned int i_BitsUsedMod8 = m_BitsUsed & 7;
	
	// Faster to put the while at the top surprisingly enough
	while(i_BitCount > 0)
		{
		i_DataByte = *(i_Input + i_i_Offset);

		if(i_BitCount < 8)   // i_Alignment means in the case of a partial byte, the bits are aligned from the right (bit 0) rather than the left (as in the normal internal representation)
			i_DataByte <<= 8 - i_BitCount;  // shift left to get the bits on the left, as in our internal representation
			
		// Writing to a new byte each time
		if(i_BitsUsedMod8 == 0)
			* (m_Data + (m_BitsUsed >> 3)) = i_DataByte;
		else
			{
			// Copy over the new m_Data.
			*(m_Data + (m_BitsUsed >> 3)) |= i_DataByte >> (i_BitsUsedMod8); // First half
			
			if (8 - (i_BitsUsedMod8) < 8 && 8 - (i_BitsUsedMod8) < i_BitCount)   // If we didn't write it all out in the first half (8 - (m_BitsUsed%8) is the number we wrote in the first half)
				{
				*(m_Data + (m_BitsUsed >> 3) + 1) = (unsigned char)(i_DataByte << (8 - (i_BitsUsedMod8))); // Second half (overlaps byte boundary)
				}
			}

		if(i_BitCount >= 8)
			m_BitsUsed += 8;
		else
			m_BitsUsed += i_BitCount;

		if (i_BitCount>=8)
			i_BitCount -= 8;
		else
			i_BitCount=0;

		i_i_Offset++;
		}
}

void BitTransfer::acAddbitsFast(const unsigned char* i_Input, unsigned int i_BitCount)
{
#if defined(BT_DEBUG)
	if(i_BitCount > m_Allocated)
		{
		printf("ERROR:::BT_DEBUG bit container reports overflowing by %i bits\n", m_Allocated - i_BitCount);
		//for(;;) {};
		}
#endif

	unsigned int i_i_Offset = 0;
	unsigned char i_DataByte;
	unsigned int i_BitsUsedMod8 = m_BitsUsed & 7;

	// Faster to put the while at the top surprisingly enough
	while(i_BitCount > 0)
		{
		i_DataByte = *(i_Input + i_i_Offset);

		if(i_BitCount < 8)   // i_Alignment means in the case of a partial byte, the bits are aligned from the right (bit 0) rather than the left (as in the normal internal representation)
			i_DataByte <<= 8 - i_BitCount;  // shift left to get the bits on the left, as in our internal representation

		// Writing to a new byte each time
		if(i_BitsUsedMod8 == 0)
			*(m_Data + (m_BitsUsed >> 3)) = i_DataByte;
		else
			{
			// Copy over the new m_Data.
			*(m_Data + (m_BitsUsed >> 3)) |= i_DataByte >> (i_BitsUsedMod8); // First half
			
			if(8 - (i_BitsUsedMod8) < 8 && 8 - (i_BitsUsedMod8) < i_BitCount)   // If we didn't write it all out in the first half (8 - (m_BitsUsed%8) is the number we wrote in the first half)
				{
				*(m_Data + (m_BitsUsed >> 3) + 1) = (unsigned char)(i_DataByte << (8 - (i_BitsUsedMod8))); // Second half (overlaps byte boundary)
				}
			}

		if(i_BitCount >= 8)
			m_BitsUsed += 8;
		else
			m_BitsUsed += i_BitCount;

		if (i_BitCount>=8)
			i_BitCount -= 8;
		else
			i_BitCount=0;

		i_i_Offset++;
		}
}

void BitTransfer::acAddbitsNonAlligned(const unsigned char* i_Input, unsigned int i_BitCount)
{
	if (i_BitCount<=0)
		return;

	acExpand(i_BitCount);

	unsigned int i_i_Offset = 0;
	unsigned char i_DataByte;
	unsigned int i_BitsUsedMod8 = m_BitsUsed & 7;

	// Faster to put the while at the top surprisingly enough
	while(i_BitCount > 0)
		{
		i_DataByte = *(i_Input + i_i_Offset);

		// Writing to a new byte each time
		if(i_BitsUsedMod8 == 0)
			*(m_Data + (m_BitsUsed >> 3)) = i_DataByte;
		else
			{
			// Copy over the new m_Data.
			*(m_Data + (m_BitsUsed >> 3)) |= i_DataByte >> (i_BitsUsedMod8); // First half
			
			if(8 - (i_BitsUsedMod8) < 8 && 8 - (i_BitsUsedMod8) < i_BitCount)   // If we didn't write it all out in the first half (8 - (m_BitsUsed%8) is the number we wrote in the first half)
				{
				*(m_Data + (m_BitsUsed >> 3) + 1) = (unsigned char) (i_DataByte << (8 - (i_BitsUsedMod8))); // Second half (overlaps byte boundary)
				}
			}

		if (i_BitCount >= 8)
			m_BitsUsed += 8;
		else
			m_BitsUsed += i_BitCount;

		if (i_BitCount>=8)
			i_BitCount -= 8;
		else
			i_BitCount=0;

		i_i_Offset++;
		}
}

void BitTransfer::acExpand(const unsigned int i_BitCount)
{
	unsigned int i_BitsUsed = i_BitCount + m_BitsUsed;

	//printf("~~~~~~~~~~~~~~~~~~~~~\n");
	//printf("acExpand~~~~~~~~~~~~~\n");
	//printf("~~~~~~~~~~~~~~~~~~~~~\n");

	//printf("m_BitsUsed %i i_BitsUsed %i m_Allocated %i\n", m_BitsUsed, i_BitsUsed, m_Allocated);
	
	if(m_Allocated < i_BitsUsed)
		{
		i_BitsUsed = (i_BitCount + m_BitsUsed) * 2;
		if(i_BitsUsed - (i_BitCount + m_BitsUsed) > 1048576)
			i_BitsUsed = i_BitCount + m_BitsUsed + 1048576;

		unsigned int i_Allocate = BITS_TO_BYTES(i_BitsUsed);

		//printf("i_Allocate %i\n", i_Allocate);

#if 0
		if (m_Data==(unsigned char*)stackData)
			{
			if (i_Allocate > BitTransfer_STACK_ALLOCATION_SIZE)
				{
#endif

				unsigned char* i_Data = (unsigned char*) malloc((unsigned int)i_Allocate);
				memcpy((void*)i_Data, (void*)m_Data, (unsigned int)BITS_TO_BYTES(m_Allocated));
				m_Data = i_Data;

#if 0
				}
			}
		else
			{
			m_Data = (unsigned char*) realloc(m_Data,(unsigned int)i_Allocate);
			}
#endif
		}
	
	if ( i_BitsUsed > m_Allocated ) m_Allocated = i_BitsUsed;

	//printf("m_Allocated %i\n", m_Allocated);
}

void BitTransfer::acExpandSection(const unsigned int i_BitCount)
{
	unsigned int i_BitsUsed = i_BitCount + m_BitsUsed;

#if 0
	unsigned int i_BitsUsedStr = (i_BitCount + m_BitsUsed) * 2;
		if(i_BitsUsedStr - (i_BitCount + m_BitsUsed) > 1048576)
			i_BitsUsedStr = i_BitCount + m_BitsUsed + 1048576;
#endif

	while(((m_Allocated - 1) >> 3) < ((i_BitsUsed - 1) >> 3))
		{
		m_Allocated += 1024 * 8;
		}

	unsigned char* i_Data = (unsigned char*) malloc((unsigned int)m_Allocated);
	memcpy((void*)i_Data, (void*)m_Data, (unsigned int)BITS_TO_BYTES(m_Allocated));
	m_Data = i_Data;

	if(i_BitsUsed > m_Allocated) m_Allocated = i_BitsUsed;
}

// Should hit if reads didn't match writes
void BitTransfer::acAssertEmpty(void)
{
	//*assert( m_ReadOffset == m_BitsUsed );
}

void BitTransfer::acPrintBits( char *out ) const
{
	if ( m_BitsUsed <= 0 )
		{
		strcpy(out, "...Empty\n" );
		return;
		}

	unsigned int strIndex=0;
	for(unsigned int counter = 0; counter < BITS_TO_BYTES( m_BitsUsed ); counter++)
		{
		unsigned int stop;

		if(counter == (m_BitsUsed - 1) >> 3)
			stop = 8 - (((m_BitsUsed - 1) & 7) + 1);
		else
			stop = 0;

		for(unsigned int counter2 = 7; counter2 >= stop; counter2--)
			{
			if((m_Data[counter] >> counter2) & 1)
				out[strIndex++]='1';
			else
				out[strIndex++]='0';

			if (counter2==0)
				break;
			}

		out[strIndex++]=' ';
		}

	out[strIndex++]='\n';

	out[strIndex++]=0;
}

float BitTransfer::acTimeStamp(void)
{
	unsigned char i_UseTimeStamp;
	float i_TimeStamp;
	
	acReadBits((unsigned char*) &i_UseTimeStamp, 8);
	acReadBits((unsigned char*) &i_TimeStamp, 32);
	return i_TimeStamp;
}

unsigned char BitTransfer::acTag(void)
{
	unsigned char i_Tag;
	acReadBits((unsigned char*) &i_Tag, 8);
	return i_Tag;
}

void BitTransfer::acPrintBits(void) const
{
	char out[2048];

	acPrintBits(out);

	printf(out);
}

bool BitTransfer::acReadBits(unsigned char *i_Output, unsigned int i_BitsToRead)
{
//#if defined(BT_DEBUG)
	if(i_BitsToRead <= 0)
		{
		printf("ERROR:::BT_DEBUG inverse or null datasize to read %i bits\n", i_BitsToRead);
		//for(;;) {};
		}

	if(m_ReadOffset + i_BitsToRead > m_BitsUsed)
		{
		printf("ERROR:::BT_DEBUG read exceed %i bits:::position %i:::container depth %i\n", i_BitsToRead, m_ReadOffset, m_BitsUsed);
		//for(;;) {};
		return false;
		}
	else
		{
//#endif

		unsigned int i_ReadOffsetMod8;
		unsigned int i_Offset = 0;
		
		memset(i_Output, 0, (unsigned int)BITS_TO_BYTES(i_BitsToRead));
		
		i_ReadOffsetMod8 = m_ReadOffset & 7;
		
		while(i_BitsToRead > 0)
			{
			*(i_Output + i_Offset) |= *(m_Data + (m_ReadOffset >> 3)) << (i_ReadOffsetMod8); // First half

			if(i_ReadOffsetMod8 > 0 && i_BitsToRead > 8 - (i_ReadOffsetMod8))   // If we have a second half, we didn't read enough bytes in the first half
				*(i_Output + i_Offset) |= *(m_Data + (m_ReadOffset >> 3) + 1) >> (8 - (i_ReadOffsetMod8)); // Second half (overlaps byte boundary)

			if(i_BitsToRead >= 8)
				{
				i_BitsToRead -= 8;
				m_ReadOffset += 8;
				i_Offset++;
				}
			else
				{
				int neg = (int)i_BitsToRead - 8;

				if(neg < 0)   // Reading a partial byte for the last byte, shift right so the data is aligned on the right
					{
					*(i_Output + i_Offset) >>= -neg;

					m_ReadOffset += 8 + neg;
					}
				else m_ReadOffset += 8;

				i_Offset++;

				i_BitsToRead=0;
				}
			}
//#if defined(BT_DEBUG)
		}
//#endif

	return true;
}

void BitTransfer::acReadBitsNonAlligned(unsigned char *i_Output, unsigned int i_BitsToRead)
{
#if defined(BT_DEBUG)
	if(i_BitsToRead <= 0)
		{
		printf("ERROR:::BT_DEBUG inverse or null datasize to read %i bits\n", i_BitsToRead);
		//for(;;) {};
		}

	if(m_ReadOffset + i_BitsToRead > m_BitsUsed)
		{
		printf("ERROR:::BT_DEBUG read exceed %i bits:::position %i:::container depth %i\n", i_BitsToRead, m_ReadOffset, m_BitsUsed);
		//for(;;) {};
		}
#endif

	unsigned int i_ReadOffsetMod8;
	unsigned int i_Offset = 0;

	memset(i_Output, 0, (unsigned int)BITS_TO_BYTES(i_BitsToRead));

	i_ReadOffsetMod8 = m_ReadOffset & 7;

	while(i_BitsToRead > 0)
		{
		*(i_Output + i_Offset) |= *(m_Data + (m_ReadOffset >> 3)) << (i_ReadOffsetMod8); // First half

		if(i_ReadOffsetMod8 > 0 && i_BitsToRead > 8 - (i_ReadOffsetMod8))   // If we have a second half, we didn't read enough bytes in the first half
			*(i_Output + i_Offset) |= *(m_Data + (m_ReadOffset >> 3) + 1) >> (8 - (i_ReadOffsetMod8)); // Second half (overlaps byte boundary)

		if(i_BitsToRead >= 8)
			{
			i_BitsToRead -= 8;
			m_ReadOffset += 8;
			i_Offset++;
			}
		else
			{
			int neg = (int)i_BitsToRead - 8;

			if(neg < 0) m_ReadOffset += 8 + neg;
			else m_ReadOffset += 8;

			i_Offset++;

			i_BitsToRead=0;
			}
		}
}

void BitTransfer::acAddbitsCompressed(const unsigned char* i_Input, const unsigned int i_Size, const bool i_UnsignedData)
{
	unsigned int currentByte = (i_Size >> 3) - 1; // PCs

	unsigned char byteMatch;
	
	if(i_UnsignedData)
		{
		byteMatch = 0;
		}
	else
		{
		byteMatch = 0xFF;
		}
	
	// Write upper bytes with a single 1
	// From high byte to low byte, if high byte is a byteMatch then write a 1 bit. Otherwise write a 0 bit and then write the remaining bytes
	while(currentByte > 0)
		{
		if(i_Input[currentByte] == byteMatch)   // If high byte is byteMatch (0 of 0xff) then it would have the same value shifted
			{
			bool b = true;
			acPush(b);
			}
		else
			{
			// Write the remainder of the data after writing 0
			bool b = false;
			acPush(b);
			
			acAddbits(i_Input, (currentByte + 1) << 3);
			
			return;
			}
		
		currentByte--;
		}
	
	// If the upper half of the last byte is a 0 (positive) or 16 (negative) then write a 1 and the remaining 4 bits.  Otherwise write a 0 and the 8 bites.
	if((i_UnsignedData && ((*(i_Input + currentByte)) & 0xF0) == 0x00) ||
		(i_UnsignedData == false && ((*(i_Input + currentByte)) & 0xF0) == 0xF0))
		{
		bool b = true;
		acPush(b);
		acAddbits(i_Input + currentByte, 4);
		}
	else
		{
		bool b = false;
		acPush(b);
		acAddbits(i_Input + currentByte, 8);
		}
}

void BitTransfer::acAddbit0(void)
{
	acExpand(1);

	// New bytes need to be zeroed
	if((m_BitsUsed & 7) == 0)
		m_Data[m_BitsUsed >> 3] = 0;

	m_BitsUsed++;
}

void BitTransfer::acAddbit1( void )
{
	acExpand( 1 );

	unsigned int numberOfBitsMod8 = m_BitsUsed & 7;

	if(numberOfBitsMod8 == 0)
		m_Data[m_BitsUsed >> 3] = 0x80;
	else
		m_Data[m_BitsUsed >> 3] |= 0x80 >> (numberOfBitsMod8); // Set the bit to 1

	m_BitsUsed++;
}

bool BitTransfer::acReadCompressed(unsigned char* i_Output, const unsigned int i_Size, const bool i_UnsignedData)
{
	unsigned int currentByte = ( i_Size >> 3 ) - 1;
	unsigned char byteMatch, halfByteMatch;
	
	if(i_UnsignedData)
		{
		byteMatch = 0;
		halfByteMatch = 0;
		}
	else
		{
		byteMatch = 0xFF;
		halfByteMatch = 0xF0;
		}

	// Upper bytes are specified with a single 1 if they match byteMatch
	// From high byte to low byte, if high byte is a byteMatch then write a 1 bit. Otherwise write a 0 bit and then write the remaining bytes
	while(currentByte > 0)
		{
		// If we read a 1 then the data is byteMatch.
		bool b;
		
		if(acRead(b) == false)
			return false;

		if(b)   // Check that bit
			{
			i_Output[currentByte] = byteMatch;
			currentByte--;
			}
		else
			{
			// Read the rest of the bytes
			acReadBits(i_Output, (currentByte + 1) << 3);
			return true;
			}
		}
	
	// All but the first bytes are byteMatch.  If the upper half of the last byte is a 0 (positive) or 16 (negative) then what we read will be a 1 and the remaining 4 bits.
	// Otherwise we read a 0 and the 8 bytes
	//assert(m_ReadOffset+1 <= m_BitsUsed); // If this assert is hit the stream wasn't long enough to read from
	if(m_ReadOffset + 1 > m_BitsUsed)
		return false;

	bool b;

	if(acRead(b) == false)
		return false;

	if(b)   // Check that bit
		{
		acReadBits(i_Output + currentByte, 4);

		i_Output[currentByte] |= halfByteMatch; // We have to set the high 4 bits since these are set to 0 by ReadBits
		}
	else
		{
		acReadBits(i_Output + currentByte, 8);
		}
	
	return true;
}

bool BitTransfer::acReadBit(void)
{
	bool result = (m_Data[m_ReadOffset >> 3] & (0x80 >> (m_ReadOffset & 7))) !=0;
	m_ReadOffset++;
	return result;
}

unsigned int BitTransfer::acCopyData(unsigned char** i_Data) const
{
#if defined(BT_DEBUG)
	if(m_BitsUsed <= 0)
		{
		printf("ERROR:::BT_DEBUG acCopyData source void of data\n");
		//for(;;) {};
		}
#endif
	
	*i_Data = (unsigned char*) malloc ((unsigned int) BITS_TO_BYTES(m_BitsUsed));
	memcpy(*i_Data, m_Data, sizeof(unsigned char) * (unsigned int)(BITS_TO_BYTES(m_BitsUsed)));
	return m_BitsUsed;
}

void BitTemplate::acAddbits(unsigned int i_BitCount)
{
	if (i_BitCount<=0)
		{
		printf("ERROR:::BT_DEBUG BitTemplate source void of data\n");
		//for(;;) {};
		}

	m_BitsUsed += i_BitCount;
}