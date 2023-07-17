//---------------------------------------------------------------------------

#ifndef Unit1usb
#define Unit1usb

#include "windows.h"

//////// Function Typedef Declaration ////////

typedef long (*OpenDevice)(long CardAddress);
typedef void (*CloseDevice)(void);
typedef long (*ReadAnalogChannel)(long Channel);
typedef void (*ReadAllAnalog)(long *Data1, long *Data2);
typedef void (*OutputAnalogChannel)(long Channel, long Data);
typedef void (*OutputAllAnalog)(long Data1, long Data2);
typedef void (*ClearAnalogChannel)(long Channel); 
typedef void (*ClearAllAnalog)(void);
typedef void (*SetAnalogChannel)(long Channel); 
typedef void (*SetAllAnalog)(void);
typedef void (*WriteAllDigital)(long Data);
typedef void (*ClearDigitalChannel)(long Channel);
typedef void (*ClearAllDigital)(void);
typedef void (*SetDigitalChannel)(long Channel);
typedef void (*SetAllDigital)(void);
typedef bool (*ReadDigitalChannel)(long Channel);
typedef long (*ReadAllDigital)(void);
typedef long (*ReadCounter)(long CounterNr);
typedef void (*ResetCounter)(long CounterNr);
typedef void (*SetCounterDebounceTime)(long CounterNr, long DebounceTime);

//---------------------------------------------------------------------------
class usbFrameWork
{
public:
	usbFrameWork();
	~usbFrameWork();

	void acInit(void);
	void acClose(void);

	void acConnect(void);

	void acSetAllDigital(void);
	void acClearAllDigital(void);
	void acSetAllAnalog(void);
	void acClearAllAnalog(void);

#if 0
	void FormCreate(TObject *Sender);
	void Timer1Timer(TObject *Sender);
	void ResetCounter1Click(TObject *Sender);
	void ResetCounter2Click(TObject *Sender);
	void DebounceTime1Click(TObject *Sender);
	void DebounceTime2Click(TObject *Sender);
	void OutputTest1Click(TObject *Sender);
	void Timer2Timer(TObject *Sender);
#endif

public:
	OpenDevice m_OpenDevice;
	CloseDevice m_CloseDevice;
	ReadAnalogChannel m_ReadAnalogChannel;
	ReadAllAnalog m_ReadAllAnalog;
	OutputAnalogChannel m_OutputAnalogChannel;
	OutputAllAnalog m_OutputAllAnalog;
	ClearAnalogChannel m_ClearAnalogChannel;
	ClearAllAnalog m_ClearAllAnalog;
	SetAnalogChannel m_SetAnalogChannel;
	SetAllAnalog m_SetAllAnalog;
	WriteAllDigital m_WriteAllDigital;
	ClearDigitalChannel m_ClearDigitalChannel;
	ClearAllDigital m_ClearAllDigital;
	SetDigitalChannel m_SetDigitalChannel;
	SetAllDigital m_SetAllDigital;
	ReadDigitalChannel m_ReadDigitalChannel;
	ReadAllDigital m_ReadAllDigital;
	ReadCounter m_ReadCounter;
	ResetCounter m_ResetCounter;
	SetCounterDebounceTime m_SetCounterDebounceTime;

	bool TX_On;

private:
	HINSTANCE m_Library;
	bool m_Active;
	bool m_Connected;
};

#endif
