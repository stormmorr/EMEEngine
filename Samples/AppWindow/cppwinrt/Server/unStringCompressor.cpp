/*

    ununStringCompressor - Unification String Compression
    Copyright OSIREM (C) 2007
	www.osirem.com  svn://62.44.82.8/unification

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "unStringCompressor.h"
#include "unHuffmanEncodingTree.h"
#include "RakString.h"
#include "RakAssert.h"
#include <string.h>
#ifndef _PS3
#include <memory.h>
#endif
#if defined(_PS3)
#include "Console2Includes.h"
#endif


using namespace RakNet;

unStringCompressor* unStringCompressor::instance=0;
int unStringCompressor::referenceCount=0;

void unStringCompressor::AddReference(void)
{
	if (++referenceCount==1)
	{
		instance = RakNet::OP_NEW<unStringCompressor>();
	}
}
void unStringCompressor::RemoveReference(void)
{
	assert(referenceCount > 0);

	if (referenceCount > 0)
	{
		if (--referenceCount==0)
		{
			RakNet::OP_DELETE(instance);
			instance=0;
		}
	}
}

unStringCompressor* unStringCompressor::Instance(void)
{
	return instance;
}

unsigned int unenglishCharacterFrequencies[ 256 ] =
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
};

unStringCompressor::unStringCompressor()
{
	DataStructures::Map<int, unHuffmanEncodingTree *>::IMPLEMENT_DEFAULT_COMPARISON();

	// Make a default tree immediately, since this is used for RPC possibly from multiple threads at the same time
	unHuffmanEncodingTree *i_unHuffmanEncodingTree = new unHuffmanEncodingTree();
	i_unHuffmanEncodingTree->GenerateFromFrequencyTable( unenglishCharacterFrequencies );

	unHuffmanEncodingTrees.Set(0, i_unHuffmanEncodingTree);
}
void unStringCompressor::GenerateTreeFromStrings( unsigned char *input, unsigned inputLength, int languageID )
{
	unHuffmanEncodingTree *i_unHuffmanEncodingTree;
	if (unHuffmanEncodingTrees.Has(languageID))
	{
		i_unHuffmanEncodingTree = unHuffmanEncodingTrees.Get(languageID);
		RakNet::OP_DELETE(i_unHuffmanEncodingTree);
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
	i_unHuffmanEncodingTree = new unHuffmanEncodingTree();
	i_unHuffmanEncodingTree->GenerateFromFrequencyTable( frequencyTable );
	unHuffmanEncodingTrees.Set(languageID, i_unHuffmanEncodingTree);
}

unStringCompressor::~unStringCompressor()
{
	for (unsigned i=0; i < unHuffmanEncodingTrees.Size(); i++)
		RakNet::OP_DELETE(unHuffmanEncodingTrees[i]);
}

void unStringCompressor::EncodeString( const char *input, int maxCharsToWrite, BitTransfer *output, int languageID )
{
	unHuffmanEncodingTree *unHuffmanEncodingTree;
	if (unHuffmanEncodingTrees.Has(languageID)==false)
		return;
	unHuffmanEncodingTree=unHuffmanEncodingTrees.Get(languageID);

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

	unHuffmanEncodingTree->EncodeArray( ( unsigned char* ) input, charsToWrite, &encodedBitTransfer );

	stringBitLength = (unsigned int) encodedBitTransfer.acSizeBits();

	output->acPushCompressed( stringBitLength );

	output->acAddbits( encodedBitTransfer.m_Data, stringBitLength );
}

bool unStringCompressor::DecodeString( char *output, int maxCharsToWrite, BitTransfer *input, int languageID )
{
	unHuffmanEncodingTree *unHuffmanEncodingTree;
	if (unHuffmanEncodingTrees.Has(languageID)==false)
		return false;
	if (maxCharsToWrite<=0)
		return false;
	unHuffmanEncodingTree=unHuffmanEncodingTrees.Get(languageID);

	unsigned int stringBitLength;
	int bytesInStream;

	output[ 0 ] = 0;

	if ( input->acReadCompressed( stringBitLength ) == false )
		return false;

	if ( (unsigned) input->acSizeUnreadBits() < stringBitLength )
		return false;

	bytesInStream = unHuffmanEncodingTree->DecodeArray( input, stringBitLength, maxCharsToWrite, ( unsigned char* ) output );

	if ( bytesInStream < maxCharsToWrite )
		output[ bytesInStream ] = 0;
	else
		output[ maxCharsToWrite - 1 ] = 0;

	return true;
}
#ifdef _CSTRING_COMPRESSOR
void unStringCompressor::EncodeString( const CString &input, int maxCharsToWrite, BitTransfer *output )
{
	LPTSTR p = input;
	EncodeString(p, maxCharsToWrite*sizeof(TCHAR), output, languageID);
}
bool unStringCompressor::DecodeString( CString &output, int maxCharsToWrite, BitTransfer *input, int languageID )
{
	LPSTR p = output.GetBuffer(maxCharsToWrite*sizeof(TCHAR));
	DecodeString(p,maxCharsToWrite*sizeof(TCHAR), input, languageID);
	output.ReleaseBuffer(0)

}
#endif
#ifdef _STD_STRING_COMPRESSOR
void unStringCompressor::EncodeString( const std::string &input, int maxCharsToWrite, BitTransfer *output, int languageID )
{
	EncodeString(input.c_str(), maxCharsToWrite, output, languageID);
}
bool unStringCompressor::DecodeString( std::string *output, int maxCharsToWrite, BitTransfer *input, int languageID )
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
void unStringCompressor::EncodeString( const RakString *input, int maxCharsToWrite, BitTransfer *output, int languageID )
{
	EncodeString(input->C_String(), maxCharsToWrite, output, languageID);
}
bool unStringCompressor::DecodeString( RakString *output, int maxCharsToWrite, BitTransfer *input, int languageID )
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
