/// \file
///
/// This file is part of RakNet Copyright 2003 Jenkins Software LLC
///
/// Usage of RakNet is subject to the appropriate license agreement.
#include "pch.h"

#include "unsStringCompressor.h"
#include "DS_HuffmanEncodingTree.h"
#include "unHuffmanEncodingTree.h"
#include "BitStream.h"
#include "RakString.h"
#include "RakAssert.h"
#include <string.h>
#if !defined(_PS3) && !defined(__PS3__) && !defined(SN_TARGET_PS3)
#include <memory.h>
#endif
#if defined(_PS3) || defined(__PS3__) || defined(SN_TARGET_PS3)
                        
#endif

using namespace RakNet;

unsStringCompressor* unsStringCompressor::instance=0;
int unsStringCompressor::referenceCount=0;

void unsStringCompressor::AddReference(void)
{
	if (++referenceCount==1)
	{
		instance = RakNet::OP_NEW<unsStringCompressor>( __FILE__, __LINE__ );
	}
}
void unsStringCompressor::RemoveReference(void)
{
	RakAssert(referenceCount > 0);

	if (referenceCount > 0)
	{
		if (--referenceCount==0)
		{
			RakNet::OP_DELETE(instance, __FILE__, __LINE__);
			instance=0;
		}
	}
}

unsStringCompressor* unsStringCompressor::Instance(void)
{
	return instance;
}

/*unsigned int englishCharacterFrequencies[ 256 ] =
{
	0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		722,
		0,
		0,
		2,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		11084,
		58,
		63,
		1,
		0,
		31,
		0,
		317,
		64,
		64,
		44,
		0,
		695,
		62,
		980,
		266,
		69,
		67,
		56,
		7,
		73,
		3,
		14,
		2,
		69,
		1,
		167,
		9,
		1,
		2,
		25,
		94,
		0,
		195,
		139,
		34,
		96,
		48,
		103,
		56,
		125,
		653,
		21,
		5,
		23,
		64,
		85,
		44,
		34,
		7,
		92,
		76,
		147,
		12,
		14,
		57,
		15,
		39,
		15,
		1,
		1,
		1,
		2,
		3,
		0,
		3611,
		845,
		1077,
		1884,
		5870,
		841,
		1057,
		2501,
		3212,
		164,
		531,
		2019,
		1330,
		3056,
		4037,
		848,
		47,
		2586,
		2919,
		4771,
		1707,
		535,
		1106,
		152,
		1243,
		100,
		0,
		2,
		0,
		10,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0,
		0
};*/

extern unsigned int englishCharacterFrequencies[ 256 ];

unsStringCompressor::unsStringCompressor()
{
	printf("unHuffmanEncodingTrees.Set(0, f_unHuffmanEncodingTree)\n");
	DataStructures::Map<int, unHuffmanEncodingTree *>::IMPLEMENT_DEFAULT_COMPARISON();

	// Make a default tree immediately, since this is used for RPC possibly from multiple threads at the same time
	unHuffmanEncodingTree *f_unHuffmanEncodingTree = RakNet::OP_NEW<unHuffmanEncodingTree>( __FILE__, __LINE__ );
	f_unHuffmanEncodingTree->GenerateFromFrequencyTable( englishCharacterFrequencies );

	unHuffmanEncodingTrees.Set(0, f_unHuffmanEncodingTree);
}
void unsStringCompressor::GenerateTreeFromStrings( unsigned char *input, unsigned inputLength, int languageID )
{
	unHuffmanEncodingTree *f_unHuffmanEncodingTree;
	if (unHuffmanEncodingTrees.Has(languageID))
	{
		f_unHuffmanEncodingTree = unHuffmanEncodingTrees.Get(languageID);
		RakNet::OP_DELETE(f_unHuffmanEncodingTree, __FILE__, __LINE__);
	}

	unsigned index;
	unsigned int frequencyTable[ 256 ];

	if ( inputLength == 0 )
		return ;

	// Zero out the frequency table
	memset( frequencyTable, 0, sizeof( frequencyTable ) );

	// Generate the frequency table from the strings
	for ( index = 0; index < inputLength; index++ )
		frequencyTable[ input[ index ] ] ++;

	// Build the tree
	f_unHuffmanEncodingTree = RakNet::OP_NEW<unHuffmanEncodingTree>( __FILE__, __LINE__ );
	f_unHuffmanEncodingTree->GenerateFromFrequencyTable( frequencyTable );
	unHuffmanEncodingTrees.Set(languageID, f_unHuffmanEncodingTree);
}

unsStringCompressor::~unsStringCompressor()
{
	for (unsigned i=0; i < unHuffmanEncodingTrees.Size(); i++)
		RakNet::OP_DELETE(unHuffmanEncodingTrees[i], __FILE__, __LINE__);
}

void unsStringCompressor::EncodeString( const char *input, int maxCharsToWrite, BitTransfer *output, int languageID )
{
	unHuffmanEncodingTree *f_unHuffmanEncodingTree;
	if (unHuffmanEncodingTrees.Has(languageID)==false)
		return;
	f_unHuffmanEncodingTree=unHuffmanEncodingTrees.Get(languageID);

	if ( input == 0 )
	{
		output->acPushCompressed( (unsigned int) 0 );
		return;
	}

	BitTransfer encodedBitTransfer;

	unsigned int stringBitLength;

	int charsToWrite;

	if ( maxCharsToWrite<=0 || ( int ) strlen( input ) < maxCharsToWrite )
		charsToWrite = ( int ) strlen( input );
	else
		charsToWrite = maxCharsToWrite - 1;

	f_unHuffmanEncodingTree->EncodeArray( ( unsigned char* ) input, charsToWrite, &encodedBitTransfer );

	stringBitLength = (unsigned int) encodedBitTransfer.acSizeBits();

	output->acPushCompressed( stringBitLength );

	output->acAddbits( encodedBitTransfer.m_Data, stringBitLength );
}

bool unsStringCompressor::DecodeString( char *output, int maxCharsToWrite, BitTransfer *input, int languageID )
{
	unHuffmanEncodingTree *f_unHuffmanEncodingTree;
	//if (unHuffmanEncodingTrees.Has(languageID)==false)
	//	return false;
	if (maxCharsToWrite<=0)
		return false;
	f_unHuffmanEncodingTree=unHuffmanEncodingTrees.Get(languageID);

	unsigned int stringBitLength;
	int bytesInStream;

	output[ 0 ] = 0;

	if ( input->acReadCompressed( stringBitLength ) == false )
		return false;

	if ( (unsigned) input->acSizeUnreadBits() < stringBitLength )
		return false;

	bytesInStream = f_unHuffmanEncodingTree->DecodeArray( input, stringBitLength, maxCharsToWrite, ( unsigned char* ) output );

	if ( bytesInStream < maxCharsToWrite )
		output[ bytesInStream ] = 0;
	else
		output[ maxCharsToWrite - 1 ] = 0;

	return true;
}
#ifdef _CSTRING_COMPRESSOR
void unsStringCompressor::EncodeString( const CString &input, int maxCharsToWrite, BitTransfer *output )
{
	LPTSTR p = input;
	EncodeString(p, maxCharsToWrite*sizeof(TCHAR), output, languageID);
}
bool unsStringCompressor::DecodeString( CString &output, int maxCharsToWrite, BitTransfer *input, int languageID )
{
	LPSTR p = output.GetBuffer(maxCharsToWrite*sizeof(TCHAR));
	DecodeString(p,maxCharsToWrite*sizeof(TCHAR), input, languageID);
	output.ReleaseBuffer(0)

}
#endif
#ifdef _STD_STRING_COMPRESSOR
void unsStringCompressor::EncodeString( const std::string &input, int maxCharsToWrite, BitTransfer *output, int languageID )
{
	EncodeString(input.c_str(), maxCharsToWrite, output, languageID);
}
bool unsStringCompressor::DecodeString( std::string *output, int maxCharsToWrite, BitTransfer *input, int languageID )
{
	if (maxCharsToWrite <= 0)
	{
		output->clear();
		return true;
	}

	char *destinationBlock;
	bool out;

#if !defined(_XBOX) && !defined(_X360)
	if (maxCharsToWrite < MAX_ALLOCA_STACK_ALLOCATION)
	{
		destinationBlock = (char*) alloca(maxCharsToWrite);
		out=DecodeString(destinationBlock, maxCharsToWrite, input, languageID);
		*output=destinationBlock;
	}
	else
#endif
	{
		destinationBlock = (char*) rakMalloc( maxCharsToWrite );
		out=DecodeString(destinationBlock, maxCharsToWrite, input, languageID);
		*output=destinationBlock;
		rakFree(destinationBlock);
	}

	return out;
}
#endif
void unsStringCompressor::EncodeString( const RakString *input, int maxCharsToWrite, BitTransfer *output, int languageID )
{
	EncodeString(input->C_String(), maxCharsToWrite, output, languageID);
}
bool unsStringCompressor::DecodeString( RakString *output, int maxCharsToWrite, BitTransfer *input, int languageID )
{
	if (maxCharsToWrite <= 0)
	{
		output->Clear();
		return true;
	}

	char *destinationBlock;
	bool out;

#if !defined(_XBOX) && !defined(_X360)
	if (maxCharsToWrite < MAX_ALLOCA_STACK_ALLOCATION)
	{
		destinationBlock = (char*) alloca(maxCharsToWrite);
		out=DecodeString(destinationBlock, maxCharsToWrite, input, languageID);
		*output=destinationBlock;
	}
	else
#endif
	{
		destinationBlock = (char*) rakMalloc( maxCharsToWrite );
		out=DecodeString(destinationBlock, maxCharsToWrite, input, languageID);
		*output=destinationBlock;
		rakFree(destinationBlock);
	}

	return out;
}
