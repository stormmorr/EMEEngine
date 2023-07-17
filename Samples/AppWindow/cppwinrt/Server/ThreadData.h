#ifndef _THREAD_DATA_H_
#define _THREAD_DATA_H_

class icThreadData;

class Data_Interface
{
public:
	virtual icThreadData * ReadData() = 0;
	virtual void WriteData(icThreadData *) = 0;
};


class icThreadData : public Data_Interface
{
public:
	virtual icThreadData * ReadData() = 0;
	virtual void WriteData(icThreadData *) = 0;
};

#endif //_THREAD_DATA_H_