/*

	UsbInterface - Velleman USB Interface Board
	Copyright SomptingSOFT/Max Lawlor (C) 2007
	SomptingSOFT Portal www.stsshome.com

	This source is proprietary, and cannot be used, in part or in full without
	the express permission of the original author. The original author retain
	the rights to use, modify, and/or relicense this code without notice.

*/

#include "UsbFrameWork.h"
#include "stdio.h"

#include "../Speech/SpeechDlg.h"

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

extern CSpeechDlg *i_CSpeechDlg;

bool TX_One;

//////// Constructors ////////

usbFrameWork::usbFrameWork()
{
#if 0
	m_Library = LoadLibrary("C://Projects Base//Unification//UnSRC//Dongle//K8055D.dll");
#else
	m_Library = LoadLibrary("K8055D.dll");
#endif

	if(m_Library != 0)
		{
		printf("USB Device Library Loaded\n");

		m_OpenDevice = (OpenDevice)GetProcAddress(m_Library, "OpenDevice");
		m_CloseDevice = (CloseDevice)GetProcAddress(m_Library, "CloseDevice");
		m_ReadAnalogChannel = (ReadAnalogChannel)GetProcAddress(m_Library, "ReadAnalogChannel");
		m_ReadAllAnalog = (ReadAllAnalog)GetProcAddress(m_Library, "ReadAllAnalog");
		m_OutputAnalogChannel = (OutputAnalogChannel)GetProcAddress(m_Library, "OutputAnalogChannel");
		m_OutputAllAnalog = (OutputAllAnalog)GetProcAddress(m_Library, "OutputAllAnalog");
		m_ClearAnalogChannel = (ClearAnalogChannel)GetProcAddress(m_Library, "ClearAnalogChannel");
		m_ClearAllAnalog = (ClearAllAnalog)GetProcAddress(m_Library, "ClearAllAnalog");
		m_SetAnalogChannel = (SetAnalogChannel)GetProcAddress(m_Library, "SetAnalogChannel");
		m_SetAllAnalog = (SetAllAnalog)GetProcAddress(m_Library, "SetAllAnalog");
		m_WriteAllDigital = (WriteAllDigital)GetProcAddress(m_Library, "WriteAllDigital");
		m_ClearDigitalChannel = (ClearDigitalChannel)GetProcAddress(m_Library, "ClearDigitalChannel");
		m_ClearAllDigital = (ClearAllDigital)GetProcAddress(m_Library, "ClearAllDigital");
		m_SetDigitalChannel = (SetDigitalChannel)GetProcAddress(m_Library, "SetDigitalChannel");
		m_SetAllDigital = (SetAllDigital)GetProcAddress(m_Library, "SetAllDigital");
		m_ReadDigitalChannel = (ReadDigitalChannel)GetProcAddress(m_Library, "ReadDigitalChannel");
		m_ReadAllDigital = (ReadAllDigital)GetProcAddress(m_Library, "ReadAllDigital");
		m_ReadCounter = (ReadCounter)GetProcAddress(m_Library, "ReadCounter");
		m_ResetCounter = (ResetCounter)GetProcAddress(m_Library, "ResetCounter");
		m_SetCounterDebounceTime = (SetCounterDebounceTime)GetProcAddress(m_Library, "SetCounterDebounceTime");
		m_Active = true;
		}
	else
		{
		printf("LoadLibrary ERROR\n");
		m_Active = false;
		}

	m_Connected = false;
	TX_One = false;

	//// Initialize Device ////
	acInit();
}

usbFrameWork::~usbFrameWork()
{
	if(m_Active)
		{
		FreeLibrary(m_Library);
		acClose();
		}
}

void usbFrameWork::acInit(void)
{
	if(m_Active)
		{
		int CardAddr = 3 - (int(1) + int(1) * 2);

		int h = m_OpenDevice(CardAddr);

		switch (h)
			{
			case 0 :
			case 1 :
			case 2 :
			case 3 : printf("Found Velleman USB Device!\n"); m_Connected = true; acClearAllDigital(); break;
			case -1 : printf("device not found\n"); m_Connected = false;
			}

		for(;;)
			{
			MSG msg;
			while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
				{
				if (GetMessage(&msg, NULL, 0, 0))
					{
					//if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
					//	{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					//	}
					}
				}

			if(TX_One) acSetAllDigital();

			i_CSpeechDlg->m_pVoice->GetStatus(&i_CSpeechDlg->m_VoiceStatus, NULL);
			if(i_CSpeechDlg->m_VoiceStatus.dwRunningState == 1)
				{
				if(!i_CSpeechDlg->acVoice())
					{
					if(TX_One)
						{
						acClearAllDigital();
						TX_One = false;
						}
					}
				}
			}

		//acClose();
		}
}

void usbFrameWork::acConnect(void)
{
	if(m_Active)
		{
		int CardAddr = 3 - (int(1) + int(1) * 2);
		if(m_OpenDevice(CardAddr) == 3) m_Connected = true;
		else m_Connected = false;
		}
}

//---------------------------------------------------------------------------

void usbFrameWork::acClose(void)
{
	if(m_Active)
		{
		m_CloseDevice();
		m_Connected = false;
		}
}

//---------------------------------------------------------------------------

void usbFrameWork::acSetAllDigital(void)
{
	if(m_Active)
		{
		if(m_Connected)
			{
			m_SetAllDigital();
			}
		else 
			{
			acConnect();
			m_SetAllDigital();
			}
		}
}

//---------------------------------------------------------------------------

void usbFrameWork::acClearAllDigital(void)
{
	if(m_Active)
		{
		if(m_Connected)
			{
			m_ClearAllDigital();
			}
		else 
			{
			acConnect();
			m_ClearAllDigital();
			}
		}
}
//---------------------------------------------------------------------------

void usbFrameWork::acSetAllAnalog(void)
{
	if(m_Active)
		{
		if(m_Connected)
			{
			m_SetAllAnalog();
			}
		else 
			{
			acConnect();
			m_SetAllAnalog();
			}
		}
}
//---------------------------------------------------------------------------

void usbFrameWork::acClearAllAnalog(void)
{
	if(m_Active)
		{
		if(m_Connected)
			{
			m_ClearAllAnalog();
			}
		else 
			{
			acConnect();
			m_ClearAllAnalog();
			}
		}
}
//---------------------------------------------------------------------------

#if 0
void __fastcall TForm1::DAC2Change(TObject *Sender)
{
  if (DisableOtherFunctionCall == false)
    OutputAnalogChannel(2, 255-DAC2->Position);
  Label3->Caption = 255 - DAC2->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  Timer1->Enabled = false;
  long Data1;
  long Data2;
  long i;
  ReadAllAnalog(&Data1, &Data2);
  AD1->Position = Data1;
  AD2->Position = Data2;
  Label4->Caption = IntToStr(Data1);
  Label5->Caption = IntToStr(Data2);
  Counter1->Text = IntToStr(ReadCounter(1));
  Counter2->Text = IntToStr(ReadCounter(2));
  i = ReadAllDigital();
  CheckBox3->Checked = (i & 1)>0;
  CheckBox4->Checked = (i & 2)>0;
  CheckBox5->Checked = (i & 4)>0;
  CheckBox6->Checked = (i & 8)>0;
  CheckBox7->Checked = (i & 16)>0;
  Timer1->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ResetCounter1Click(TObject *Sender)
{
  ResetCounter(1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ResetCounter2Click(TObject *Sender)
{
  ResetCounter(2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DebounceTime1Click(TObject *Sender)
{
  long t1;
   switch (DebounceTime1->ItemIndex) {
    case  0 : t1 = 0;
      break;
    case  1 : t1 = 2;
      break;
    case  2 : t1 = 10;
      break;
    case  3 : t1 = 1000;
   }
  SetCounterDebounceTime(1,t1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DebounceTime2Click(TObject *Sender)
{
  long t2;
   switch (DebounceTime2->ItemIndex) {
    case  0 : t2 = 0;
      break;
    case  1 : t2 = 2;
      break;
    case  2 : t2 = 10;
      break;
    case  3 : t2 = 1000;
   }
  SetCounterDebounceTime(2,t2);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OutputTest1Click(TObject *Sender)
{
    Timer2->Enabled = OutputTest1->Down;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
  ClearDigitalChannel(n);
  op[n-1]->Checked = false;
  n = n +1;
  if (n == 9)
    n = 1;
  SetDigitalChannel(n);
  op[n-1]->Checked = true;
}
#endif

//---------------------------------------------------------------------------