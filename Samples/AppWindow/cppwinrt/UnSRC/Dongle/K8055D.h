
#define FUNCTION __declspec(dllimport)
//#define FUNCTION __declspec(dllexport)

FUNCTION long __stdcall OpenDevice(long CardAddress);
FUNCTION void __stdcall CloseDevice(void);
FUNCTION long __stdcall ReadAnalogChannel(long Channel);
FUNCTION void __stdcall ReadAllAnalog(long *Data1, long *Data2);
FUNCTION void __stdcall OutputAnalogChannel(long Channel, long Data);
FUNCTION void __stdcall OutputAllAnalog(long Data1, long Data2);
FUNCTION void __stdcall ClearAnalogChannel(long Channel); 
FUNCTION void __stdcall ClearAllAnalog(void);
FUNCTION void __stdcall SetAnalogChannel(long Channel); 
FUNCTION void __stdcall SetAllAnalog(void);
FUNCTION void __stdcall WriteAllDigital(long Data);
FUNCTION void __stdcall ClearDigitalChannel(long Channel);
FUNCTION void __stdcall ClearAllDigital(void);
FUNCTION void __stdcall SetDigitalChannel(long Channel);
FUNCTION void __stdcall SetAllDigital(void);
FUNCTION bool __stdcall ReadDigitalChannel(long Channel);
FUNCTION long __stdcall ReadAllDigital(void);
FUNCTION long __stdcall ReadCounter(long CounterNr);
FUNCTION void __stdcall ResetCounter(long CounterNr);
FUNCTION void __stdcall SetCounterDebounceTime(long CounterNr, long DebounceTime);






