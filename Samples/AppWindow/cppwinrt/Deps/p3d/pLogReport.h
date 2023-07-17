/*! \file */

#ifndef PLOGREPORT_H
#define PLOGREPORT_H

//! Log report class
/*!
	This class implements an object to manage log report.
*/
class P3D_API pLogReport
{
	private:

		int m_offset;		//!< 
		FILE *m_logfile;	//!< log file

	public:

		//! Default constructor.
		pLogReport() :
			m_offset(0),
			m_logfile(NULL)
		{ }

		//! Destructor.
		~pLogReport();

		//! Creates a log file.
		/*!
			@param path path of log file
			@return true if lof file was created and false otherwise
		*/
		bool create_logfile(const char* path);

		//! Prints a log message.
		/*!
			@param flag current type of log message
			@param fmt template string for the log message
		*/
		void print_log(int flag,const char *fmt, ...);
};

#endif
