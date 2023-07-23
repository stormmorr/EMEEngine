//****************************************************************************//
// streamsource.h                                                            //
#include "pch.h" // Copyright (C) 2001-2003 Bruno 'Beosil' Heidelberger                       //
//****************************************************************************//
// This library is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU Lesser General Public License as published by   //
// the Free Software Foundation; either version 2.1 of the License, or (at    //
// your option) any later version.                                            //
//****************************************************************************//

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

//****************************************************************************//
// Includes                                                                   //
//****************************************************************************//

#include "cal3d/streamsource.h"
#include "cal3d/error.h"
#include "cal3d/platform.h"

 /*****************************************************************************/
/** Constructs a stream source instance from an existing istream.
  *
  * This function is the only constructor of the stream source.
  *
  * @param inputStream The input stream to use, which should be set up and
  *                    ready to be read from before making the stream source.
  *****************************************************************************/

QunStreamSource::QunStreamSource(std::istream& inputStream)
  : mInputStream(&inputStream)
{
}


/**
 * Destruct the QunStreamSource. Note that input stream is not closed here;
 * this should be handled externally.
 */

QunStreamSource::~QunStreamSource()
{
}

 /*****************************************************************************/
/** Checks whether the data source is in a good state.
  *
  * This function checks if the istream can be used.
  *
  * @return One of the following values:
  *         \li \b true if data source is in a good state
  *         \li \b false if not
  *****************************************************************************/

bool QunStreamSource::ok() const
{
   if (!mInputStream)
      return false;

   return true;
}

 /*****************************************************************************/
/** Sets the error code and message related to a streaming source.
  *
  *****************************************************************************/

void QunStreamSource::setError() const
{
   QunError::setLastError(QunError::INVALID_HANDLE, __FILE__, __LINE__);
}


 /*****************************************************************************/
/** Reads a number of bytes.
  *
  * This function reads a given number of bytes from this data source.
  *
  * @param pBuffer A pointer to the buffer where the bytes are stored into.
  * @param length The number of bytes that should be read.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunStreamSource::readBytes(void* pBuffer, int length)
{
   //Check that the stream is usable
   if (!ok()) return false;

   return QunPlatform::readBytes( *mInputStream, pBuffer, length );

}

 /*****************************************************************************/
/** Reads a float.
  *
  * This function reads a float from this data source.
  *
  * @param value A reference to the float into which the data is read.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunStreamSource::readFloat(float& value)
{
   //Check that the stream is usable
   if (!ok()) return false;

   return QunPlatform::readFloat( *mInputStream, value );
}

/*****************************************************************************/
/** Reads a short.
  *
  * This function reads a short from this data source.
  *
  * @param value A reference to the short into which the data is read.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunStreamSource::readShort(short& value)
{
   //Check that the stream is usable
   if (!ok()) return false;

   return QunPlatform::readShort( *mInputStream, value );
}

/*****************************************************************************/
/** Reads an integer.
  *
  * This function reads an integer from this data source.
  *
  * @param value A reference to the integer into which the data is read.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunStreamSource::readInteger(int& value)
{
   //Check that the stream is usable
   if (!ok()) return false;

   return QunPlatform::readInteger( *mInputStream, value );
}

 /*****************************************************************************/
/** Reads a string.
  *
  * This function reads a string from this data source.
  *
  * @param value A reference to the string into which the data is read.
  *
  * @return One of the following values:
  *         \li \b true if successful
  *         \li \b false if an error happend
  *****************************************************************************/

bool QunStreamSource::readString(std::string& strValue)
{
   //Check that the stream is usable
   if (!ok()) return false;

   return QunPlatform::readString( *mInputStream, strValue );
}
