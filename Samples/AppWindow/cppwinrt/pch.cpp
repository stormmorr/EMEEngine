//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

using namespace std::placeholders;

bool g_KeepShare = false;
int g_PEERCNT = 0;
int g_SHARECNT = 0;
int g_PerShareCount = 0;
bool g_RenderHesh = false;
bool g_LowtonOn = false;
picosha2::hash256_one_by_one g_hasha;
time_t g_Currtime;
time_t g_Storetime;
time_t g_CurrtimeSEC;
time_t g_StoretimeSEC;
time_t g_currenttime;
time_t g_storagetime;
int g_timeDiff = 0;
int g_timeCnt = 0;
int g_timeCntLast = 0;
int g_timeActual = 0;
float g_LowtonMark = FLT_MAX;
int g_OCSCP_LowtonMark = 0;
std::shared_ptr<Cube::CubeHESH> g_Lowton;
std::shared_ptr<Cube::CubeHASH_originstring> g_LowtonHash;
std::vector<int> g_vec_Bookmark;
bool g_GameOpen = false;
bool g_Editor_ON = false;
int g_Found_Share = 0;
int g_Found_Block = 0;
int g_Found_Msg = 0;
std::string g_Found_Text = "";
int g_CurrentShareOffset = 0;
int g_PEER = 0;
int g_CurrentShareOffsetMAX = 1;
int g_PEERMAX = 1;
int g_espo_ShareOffset = 0;
int g_espo_Peer = 0;
float g_espo_Score = 0;
float g_espo_Amount = 0.0f;
float g_espo_ECN_Amount = 0.0f;
std::string g_espo_Owner = "";
std::string g_espo_Date = "";
int g_CurrentComID = 0;
float g_CurrentSharePrice = 0.0f;
int g_CurrentShareID = 0;
bool g_Once = false;
int g_EventOffset = 0;
int g_codeIndex = 0;
float g_TimeDiff = 0.0f;
std::string g_codeStorage[4];
std::vector<std::vector<std::string>> g_CopyStack;
int g_CopyStackPageN = 0;
float g_BoardPushHeightAdjust = 2.0f;
float g_ComPositionToPoint2fFactor = 220.0f;
float g_ComICOPositionToComPositionX = 106.0f / 40.0f; // / 8.0f
float g_ComICOPositionToComPositionY = 106.0f / 25.0f; // / 8.0f
float g_CarriageReturnX = 0.0f;
bool g_TXD_Scan = false;
bool g_ConnectedECD = false;
float g_RADX = 0.0f;
float g_RADY = 0.0f;
float g_RADZ = 0.0f;
int g_CoolDown = 0;
float g_CoolBoost = false;
int g_OCSCP_ThreadCount = 0;
int g_Engine_ThreadCount = 0;
int g_Divine_ThreadCount = 0;
int g_GUItimer = 4;
int g_SaveComplete_ThreadCount = 8;
int g_Diviner_ThreadCount = 6;
bool g_BoughtCom = false;
bool g_MyOwnCom = false;
bool g_GameFocusOn = true;

std::map<std::string, std::shared_ptr<ecom_base>> g_Map_ecomRefBase;
std::map<std::string, int> g_Map_ecomRefCount;

std::map<std::string, boost::any> g_Map_Function;

std::map<std::string, std::shared_ptr<FuncHolding>> g_Map_Function_Sig;

std::vector<std::vector<std::string>> g_vec_Path;
std::vector<std::vector<std::string>> g_vec_PathLabel;

std::string g_FilePath;

int g_StreamIndex = 0;

std::vector<int> g_vec_CubeBie;

bool g_Complete = false;
int g_Exists = 0;
bool g_Loaded = false;
bool g_Copied = false;

QpoSoundPtr g_Stream[ECOIN_MAX_SOUND];
WAVEFORMATEX* g_StreamWaveForm[ECOIN_MAX_SOUND];
unsigned int g_StreamLength[ECOIN_MAX_SOUND];

std::vector<int> g_StreamGuide;
std::vector<int> g_vec_Cube;

float g_Spin;

int g_CollideFlagX;
int g_CollideFlagZ;

Cube::BiVector g_Position;

int g_GridX[4];
int g_GridY[4];
int g_GridZ[4];

int g_PlayerShowEnemyIdx;

std::vector<Cube::BiVector> g_vec_Spawn;

int g_SoundLod;

bool g_LoggedOn;
bool g_FailedLoggedOn;

bool g_GameLoader;
bool g_GameRender;

bool g_Qy[1024];
std::vector<int> g_vec_Qy;

float g_TX;

bool g_FileReady;

//Insert Placement
int g_PlaceScale;
float g_PlaceInsertPosInc;
float g_PlaceInsertAngInc;

float g_PlaceInsertX;
float g_PlaceInsertY;
float g_PlaceInsertZ;

float g_PlaceInsertXrot;
float g_PlaceInsertYrot;
float g_PlaceInsertZrot;

bool g_TerrainUpdate = true;

int g_PlaceInsertCharID;

//Terrain Insert
int g_TerrainInsertScale;
int g_TerrainInsertFillX;
int g_TerrainInsertFillY;
int g_TerrainInsertFillZ;
int g_TerrainInsertMoveX;
int g_TerrainInsertMoveY;
int g_TerrainInsertMoveZ;
int g_TerrainInsertNegatedX;
int g_TerrainInsertNegatedY;
int g_TerrainInsertNegatedZ;
int g_TerrainInsertMaxX;
int g_TerrainInsertMaxY;
int g_TerrainInsertMaxZ;
int g_TerrainInsertFillXres;
int g_TerrainInsertFillYres;
int g_TerrainInsertFillZres;
int g_TerrainInsertMoveXres;
int g_TerrainInsertMoveYres;
int g_TerrainInsertMoveZres;
int g_TerrainInsertNegatedXres;
int g_TerrainInsertNegatedYres;
int g_TerrainInsertNegatedZres;
int g_TerrainInsertMaxXres;
int g_TerrainInsertMaxYres;
int g_TerrainInsertMaxZres;

int g_TerrainInsertUpdateMode;

float g_Sp;

float g_ArenaSize = 0.4;

float g_Zoom = 1.0;
float g_ZoomFactor = 0.0;

int g_Player = 0;
int g_PlayerNom = 2;

int g_qa_Radar;
int g_qa_ClientTime;
int g_qa_FrameRateLimiter;

int g_MouseMode[QNOMPLAYER];

int kldirection[QNOMPLAYER];

float g_LevelFactor = 0;

bool g_FirstStack[QNOMPLAYER];

bool m_ButtonDown[QNOMPLAYER][50];

std::vector<std::string> g_StructureAString;

std::shared_mutex g_UpdatingMuti;

bool g_Activate;

int g_QamSpawnInsertCharacterSelect;
int g_QamSpawnInsertCharacterDiscovery;

int g_QamSpawnInsertCharacterTeam;

int g_QamSpawnInsertCharacterBoostHealth;
int g_QamSpawnInsertCharacterBoostCon;
int g_QamSpawnInsertCharacterBoostDamage;
int g_QamSpawnInsertCharacterBoostFocus;
int g_QamSpawnInsertCharacterBoostJink;

int g_QamSpawnInsertCharacterBoostIndex;

bool m_OpenReturn;

bool g_AI_ON;

std::vector<int> g_vec_Qy_ok;

extern winrt::Windows::UI::Core::CoreWindow g_CoreWindow;

void ag_Click(std::string f_ButtonName)
{
	if(g_WalletOpen == true)
		{
		std::vector<std::shared_ptr<BiPacket>> f_Packet = g_QcomManager->acSearch_PacketbyName(f_ButtonName);

		for(int f_XY = 0; f_XY < f_Packet.size(); f_XY++)
			{
			if(f_Packet[f_XY]->m_Name.length() > 0)
				{
				std::shared_ptr<Qcom> f_com = f_Packet[f_XY]->m_Operator_Com;

				f_com->ac_Execute();
				}
			}
		}
}

float ag_Unsign(float f_Input)
{
	float f_Result = 0;

	if(f_Input < 0)
		{
		f_Result = f_Input * -1;
		}
	else
		{
		f_Result = f_Input;
		}

	return f_Result;
}

template<typename f_A>
f_A ag_CheckBoth(f_A f_Input)
{
	std::string f_TypeName = typeid(f_A).name();

	if(f_TypeName.compare(typeid(float).name()) == 0)
		{
		char f_XY_char = ag_ClearChar(512);
		sprintf(f_XY_char, "%f", f_Input);
		std::string f_Result = f_XY_char;
		delete f_XY_char;

		return ag_CheckFloat(f_Result);
		}
	else if(f_TypeName.compare(typeid(int).name()) == 0)
		{
		char f_XY_char = ag_ClearChar(512);
		sprintf(f_XY_char, "%i", f_Input);
		std::string f_Result = f_XY_char;
		delete f_XY_char;

		return ag_CheckInteger(f_Result);
		}
	else if(f_TypeName.compare(typeid(std::string).name()) == 0)
		{
		return f_Input;
		}

#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak();
		}
#endif

	return f_Input;
}

int ag_CheckInteger(std::string f_InputString)
{
	if(f_InputString.length() <= 0)
		{
		return -1;
		}

	for(int f_Jet = 0; f_Jet < f_InputString.length(); f_Jet++)
		{
		char f_Char = f_InputString.at(f_Jet);

		if(f_Char < '0')
			{
			if(f_Char != '-')
				{
				return -1;
				}
			}

		if(f_Char > '9')
			{
			if(f_Char != '-')
				{
				return -1;
				}
			}
		}

	return atoi(f_InputString.c_str());
}

float ag_CheckFloat(std::string f_InputString)
{
	if(f_InputString.length() <= 0)
		{
		return -1.0f;
		}

	for(int f_Jet = 0; f_Jet < f_InputString.length(); f_Jet++)
		{
		char f_Char = f_InputString.at(f_Jet);

		if(f_Char < '0')
			{
			if((f_Char != '-') && (f_Char != '.'))
				{
				return -1.0f;
				}
			}

		if(f_Char > '9')
			{
			if((f_Char != '-') && (f_Char != '.'))
				{
				return -1.0f;
				}
			}
		}

	return atof(f_InputString.c_str());
}

template<typename f_A>
void ag_FreshOn(std::vector<f_A>& f_AS, int f_IDX, f_A f_Resultance)
{
	if(f_IDX < f_AS.size())
		{
		f_AS[f_IDX] = f_Resultance;
		}
	else
		{
		while(f_IDX >= f_AS.size())
			{
			f_AS.push_back(f_Resultance);
			}
		}
}

template<typename f_B>
void ag_Freshanon(std::vector<f_B>& f_AS, int f_IDX, f_B f_Resultance)
{
	while(f_IDX >= f_AS.size())
		{
		f_AS.push_back(f_Resultance);
		}
}

template<typename f_C>
f_C ag_FreshOnly(std::vector<f_C>& f_AS, int f_IDX, f_C f_Resultance)
{
	if(f_IDX < f_AS.size())
		{
		f_AS[f_IDX] = f_Resultance;
		}
	else
		{
		while(f_IDX >= f_AS.size())
			{
			f_AS.push_back(f_Resultance);
			}
		}

	return f_Resultance;
}

template<typename f_D>
f_D ag_FreshAndOnly(std::vector<f_D>& f_AS, int f_IDX, f_D f_Resultance)
{
	f_D h_Sorda = 0;

	std::string f_StrTypeName = typeid(f_D).name();

	if(f_IDX < f_AS.size())
		{
		if(f_StrTypeName.compare(typeid(std::string).name()) == 0)
			{
			return f_AS.at(f_IDX);
			}
		else
			{
			f_D f_Hossa = f_AS.at(f_IDX);

			if(f_Hossa != 0)
				{
				h_Sorda = f_Hossa;

				return h_Sorda;
				}
			else
				{
				h_Sorda = f_Resultance;

				return h_Sorda;
				}
			}
		}
	else
		{
		while(f_IDX >= f_AS.size())
			{
			f_AS.push_back(f_Resultance);
			}

		h_Sorda = f_Resultance;

		if(f_IDX < f_AS.size())
			{
			if(f_StrTypeName.compare(typeid(std::string).name()) == 0)
				{
				return f_AS.at(f_IDX);
				}
			else
				{
				f_D f_Hossa = f_AS.at(f_IDX);

				if(f_Hossa != 0)
					{
					h_Sorda = f_Hossa;

					return h_Sorda;
					}
				else
					{
					h_Sorda = f_Resultance;

					return h_Sorda;
					}
				}
			}
		else
			{
			while(f_IDX >= f_AS.size())
				{
				f_AS.push_back(f_Resultance);
				}
			}

		h_Sorda = f_Resultance;

		if(f_StrTypeName.compare(typeid(std::string).name()) == 0)
			{
			return f_AS.at(f_IDX);
			}
		else
			{
			f_D f_Hossa = f_AS.at(f_IDX);

			if(f_Hossa != 0)
				{
				h_Sorda = f_Hossa;

				return h_Sorda;
				}
			else
				{
				h_Sorda = f_Resultance;

				return h_Sorda;
				}
			}
		}

	return h_Sorda;
}

void ag_PrepareChar(char* f_Char, int f_ArraySize)
{
	for(int f_Jet = 0; f_Jet < f_ArraySize; f_Jet++)
		{
		f_Char[f_Jet] = '\0';
		}
}

int StringToWString(std::wstring& ws, const std::string& s)
{
	std::wstring wsTmp(s.begin(), s.end());

	ws = wsTmp;

	return 0;
}

void FillChar(char* f_Char, int f_Max)
{
	for(int f_Count = 0; f_Count < f_Max; f_Count++)
		{
		f_Char[f_Count] = '\0';
		}
}

char acFileReadChar(std::string f_Buffer, size_t f_Count)
{
	int c = 0;
	if(f_Count < f_Buffer.length())
		{
		c = f_Buffer.at(f_Count);

		if(c == EOF)
			{
			return '\0';
			}
		else
			{
			return (char)c;
			}
		}
	else
		{
		return '\0';
		}
}

char acFileReadChar(std::string f_Buffer, size_t* f_Count)
{
	int c = 0;

	if(*(f_Count) < f_Buffer.length())
		{
		c = f_Buffer.at(*(f_Count));

		*(f_Count)++;

		if(c == EOF)
			{
			return '\0';
			}
		else
			{
			return (char)c;
			}
		}
	else
		{
		return '\0';
		}
}

int acBufreadValueInteger(const std::string& f_Buffer, uint* f_CHK)
{
	std::string f_Samp = "";
	bool f_Scan = true;

	while(f_Scan == true)
		{
		char f_c = f_Buffer.at(*(f_CHK));

		if(f_c != ' ')
			{
			f_Samp.push_back(f_c);
			}
		else
			{
			f_Scan = false;
			}

		*(f_CHK) += 1;

		if(*(f_CHK) >= f_Buffer.length())
			{
			f_Scan = false;
			}
		}

	return atoi(f_Samp.c_str());
}

float acBufreadValueFloat(const std::string& f_Buffer, uint* f_CHK)
{
	std::string f_Samp = "";
	bool f_Scan = true;

	while(f_Scan == true)
		{
		char f_c = f_Buffer.at(*(f_CHK));

		if(f_c != ' ')
			{
			f_Samp.push_back(f_c);
			}
		else
			{
			f_Scan = false;
			}

		*(f_CHK) += 1;

		if(*(f_CHK) >= f_Buffer.length())
			{
			f_Scan = false;
			}
		}

	return atof(f_Samp.c_str());
}

unsigned long long acBufreadValueUL(const std::string& f_Buffer, uint* f_CHK)
{
	std::string f_Samp = "";
	bool f_Scan = true;

	while(f_Scan == true)
		{
		char f_c = f_Buffer.at(*(f_CHK));

		if(f_c != ' ')
			{
			f_Samp.push_back(f_c);
			}
		else
			{
			f_Scan = false;
			}

		*(f_CHK) += 1;

		if(*(f_CHK) >= f_Buffer.length())
			{
			f_Scan = false;
			}
		}

	return atoi(f_Samp.c_str());
}

double acBufreadValueDouble(const std::string& f_Buffer, uint* f_CHK)
{
	std::string f_Samp = "";
	bool f_Scan = true;

	while(f_Scan == true)
		{
		char f_c = f_Buffer.at(*(f_CHK));

		if(f_c != ' ')
			{
			f_Samp.push_back(f_c);
			}
		else
			{
			f_Scan = false;
			}

		*(f_CHK) += 1;

		if(*(f_CHK) >= f_Buffer.length())
			{
			f_Scan = false;
			}
		}

	return atof(f_Samp.c_str());
}

void acBufwriteValueInt(std::string* f_Buffer, int f_Int)
{
	char f_Char[512];

	FillChar(f_Char, 512);

	sprintf_s(f_Char, "%i", f_Int);
	*(f_Buffer) += f_Char;
}

void acBufwriteValueFloat(std::string* f_Buffer, float f_Float)
{
	char f_Char[512];

	FillChar(f_Char, 512);

	sprintf_s(f_Char, "%f ", f_Float);
	*(f_Buffer) += f_Char;
}

void acBufwriteValueUL(std::string* f_Buffer, unsigned long long f_LongLong)
{
	char f_Char[512];

	FillChar(f_Char, 512);

	sprintf_s(f_Char, "%llu ", f_LongLong);
	*(f_Buffer) += f_Char;
}

std::string acBufreadValueString(const std::string& f_Buffer, uint* f_CHK)
{
	std::string f_Result;
	char* f_TestChar = new char[4];
	bool m_End = false;
	std::string f_PushString;
	bool f_Start = true;

	FillChar(f_TestChar, 4);

	if(*(f_CHK) + 4 >= f_Buffer.length())
		{
		*(f_CHK) = f_Buffer.length();

		return std::string("Empty");
		}
	
	f_TestChar[3] = f_Buffer.at(*(f_CHK));
	*(f_CHK) += 1;
	f_TestChar[2] = f_Buffer.at(*(f_CHK));
	*(f_CHK) += 1;
	f_TestChar[1] = f_Buffer.at(*(f_CHK));
	*(f_CHK) += 1;
	f_TestChar[0] = f_Buffer.at(*(f_CHK));
	*(f_CHK) += 1;

	if (f_TestChar[3] == ':' &&
		f_TestChar[2] == ':' &&
		f_TestChar[1] == ':' &&
		f_TestChar[0] == ':')
		{
		m_End = true;
		}
	else
		{
		if(f_TestChar[3] != ' ')
			{
			f_PushString.clear();
			f_PushString.push_back(f_TestChar[3]);
			f_Result = f_Result + f_PushString;
			}
		}

	while(m_End == false)
		{
		f_TestChar[3] = f_TestChar[2];
		f_TestChar[2] = f_TestChar[1];
		f_TestChar[1] = f_TestChar[0];
		f_TestChar[0] = f_Buffer.at(*(f_CHK));
		*(f_CHK) += 1;

		if(f_TestChar[0] == '\0')
			{
			f_Result.push_back(f_TestChar[3]);
			f_Result.push_back(f_TestChar[2]);
			f_Result.push_back(f_TestChar[1]);
			m_End = true;
			}

		if((f_TestChar[3] == ':' &&
			f_TestChar[2] == ':' &&
			f_TestChar[1] == ':' &&
			f_TestChar[0] == ':'))
			{
			m_End = true;
			}

		if(*(f_CHK) >= f_Buffer.length())
			{
			m_End = true;
			}

		if(m_End == false)
			{
			if(f_Start)
				{
				if(f_TestChar[0] != ' ')
					{
					f_Result.push_back(f_TestChar[3]);
					f_Start = false;
					}
				}
			else
				{
				f_Result.push_back(f_TestChar[3]);
				}
			}
		}

	*(f_CHK) = *(f_CHK);

	delete[] f_TestChar;

	return f_Result;
}

void acBufwriteValueInteger(std::string* f_Buffer, int f_Int)
{
	char f_Char[512];

	FillChar(f_Char, 512);

	sprintf_s(f_Char, "%i ", f_Int);

	*(f_Buffer) = *(f_Buffer) + f_Char;
}

void acBufwriteValueDouble(std::string* f_Buffer, double f_Double)
{
	char f_Char[512];

	FillChar(f_Char, 512);

	sprintf_s(f_Char, "%.15f ", f_Double);
	*(f_Buffer) = *(f_Buffer)+f_Char;
}

std::string acBufreadCodeString(std::string f_Buffer, uint* f_CHK)
{
	std::string f_Result;
	char* f_TestChar = ag_ClearChar(4);
	bool m_End = false;
	std::string f_Pushstring;
	bool f_Start = true;

	FillChar(f_TestChar, 4);
	
	f_TestChar[3] = acFileReadChar(f_Buffer, *(f_CHK));
	*(f_CHK) += 1;
	f_TestChar[2] = acFileReadChar(f_Buffer, *(f_CHK));
	*(f_CHK) += 1;
	f_TestChar[1] = acFileReadChar(f_Buffer, *(f_CHK));
	*(f_CHK) += 1;
	f_TestChar[0] = acFileReadChar(f_Buffer, *(f_CHK));
	*(f_CHK) += 1;

	if(f_TestChar[0] == '\0')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[0] == '\n')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '*' &&
		f_TestChar[0] == '*')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '%' &&
		f_TestChar[0] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '%' &&
		f_TestChar[0] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '#' &&
		f_TestChar[0] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '#' &&
		f_TestChar[0] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '&' &&
		f_TestChar[0] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '&' &&
		f_TestChar[0] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '&' &&
		f_TestChar[0] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '%' &&
		f_TestChar[0] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '&' &&
		f_TestChar[0] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '#' &&
		f_TestChar[0] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '&' &&
		f_TestChar[0] == '*')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '\0')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '\n')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '*' &&
		f_TestChar[1] == '*')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '%' &&
		f_TestChar[1] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '%' &&
		f_TestChar[1] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '#' &&
		f_TestChar[1] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '#' &&
		f_TestChar[1] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '&' &&
		f_TestChar[1] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '&' &&
		f_TestChar[1] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '&' &&
		f_TestChar[1] == '%')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '%' &&
		f_TestChar[1] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '&' &&
		f_TestChar[1] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '#' &&
		f_TestChar[1] == '&')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[2] == '&' &&
		f_TestChar[1] == '*')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '^' &&
		f_TestChar[0] == '^')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(f_TestChar[1] == '$' &&
		f_TestChar[0] == '$')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	 ///////
	// End
	if(f_TestChar[3] == '#' &&
		f_TestChar[2] == '#' &&
		f_TestChar[1] == '#' &&
		f_TestChar[0] == '#')
		{
		f_Pushstring.clear();
		f_Pushstring.push_back(f_TestChar[3]);
		f_Pushstring.push_back(f_TestChar[2]);
		f_Pushstring.push_back(f_TestChar[1]);
		f_Pushstring.push_back(f_TestChar[0]);
		f_Result = f_Result + f_Pushstring;
		m_End = true;
		}

	if(!m_End)
		{
		if (f_TestChar[3] == '/' &&
			f_TestChar[2] == '/' &&
			f_TestChar[1] == '/' &&
			f_TestChar[0] == '/')
			{
			f_Pushstring.push_back(f_TestChar[3]);
			f_Pushstring.push_back(f_TestChar[2]);
			f_Pushstring.push_back(f_TestChar[1]);
			f_Pushstring.push_back(f_TestChar[0]);
			f_Result = f_Result + f_Pushstring;
			m_End = true;
			}
		else
			{
			if(f_TestChar[3] != ' ')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Result = f_Result + f_Pushstring;
				}
			}

		while(!m_End)
			{
			f_TestChar[3] = f_TestChar[2];
			f_TestChar[2] = f_TestChar[1];
			f_TestChar[1] = f_TestChar[0];
			f_TestChar[0] = acFileReadChar(f_Buffer, *(f_CHK));
			*(f_CHK) += 1;

			if(f_TestChar[0] == '\0')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[0] == '\n')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '*' &&
				f_TestChar[0] == '*')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '%' &&
				f_TestChar[0] == '%')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '%' &&
				f_TestChar[0] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '#' &&
				f_TestChar[0] == '%')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '^' &&
				f_TestChar[0] == '^')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '#' &&
				f_TestChar[0] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[3] == '#' &&
				f_TestChar[2] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[2] == '#' &&
				f_TestChar[1] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '#' &&
				f_TestChar[0] == '&')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '&' &&
				f_TestChar[0] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '&' &&
				f_TestChar[0] == '&')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '&' &&
				f_TestChar[0] == '%')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '%' &&
				f_TestChar[0] == '&')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '&' &&
				f_TestChar[0] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '#' &&
				f_TestChar[0] == '&')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[0] == '#')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '&' &&
				f_TestChar[0] == '*')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[1] == '$' &&
				f_TestChar[0] == '$')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(f_TestChar[3] == '/' &&
				f_TestChar[2] == '/' &&
				f_TestChar[1] == '/' &&
				f_TestChar[0] == '/')
				{
				f_Pushstring.clear();
				f_Pushstring.push_back(f_TestChar[3]);
				f_Pushstring.push_back(f_TestChar[2]);
				f_Pushstring.push_back(f_TestChar[1]);
				f_Pushstring.push_back(f_TestChar[0]);
				f_Result = f_Result + f_Pushstring;
				m_End = true;
				}

			if(!m_End)
				{
				if(f_Start)
					{
					if(f_TestChar[0] != ' ' &&
						f_TestChar[0] != '\n')
						{
						f_Pushstring.clear();
						f_Pushstring.push_back(f_TestChar[3]);
						f_Result = f_Result + f_Pushstring;
						f_Start = false;
						}
					}
				else
					{
					f_Pushstring.clear();
					f_Pushstring.push_back(f_TestChar[3]);
					f_Result = f_Result + f_Pushstring;
					}
				}
			}
		}

	delete f_TestChar;

	return f_Result;
}

winrt::hstring StrFromChar(char char_str[])
{
	std::string s_str = std::string(char_str);
	std::wstring wid_str = std::wstring(s_str.begin(), s_str.end());
	const wchar_t* w_char = wid_str.c_str();
	winrt::hstring p_string = winrt::hstring(w_char);
	return p_string;
}

winrt::hstring StrUsingStr(std::string f_string)
{
	std::wstring wid_str = std::wstring(f_string.begin(), f_string.end());
	const wchar_t* w_char = wid_str.c_str();
	winrt::hstring p_string = winrt::hstring(w_char);
	return p_string;
}

std::string ag_StrUsingFloat(float f_Float)
{
	char* f_Char = ag_ClearChar(64);

	sprintf(f_Char, "%f", f_Float);

	std::string f_String = f_Char;

	delete f_Char;

	return f_String;
}

// Convert from wstring into a string
std::string to_string(const std::wstring & wtxt)
{
	std::string str;
	str.resize(wtxt.size() + 1);

	size_t numConverted;
	errno_t err = wcstombs_s(&numConverted, (char *)str.data(), str.size(), wtxt.data(), wtxt.size());

	str.pop_back();
	return str;
}

std::string to_string(winrt::hstring pstring)
{
	std::wstring wStr(pstring.data());

	return to_string(wStr);
}

std::string to_string(wchar_t* wstring)
{
	std::wstring ws(wstring);

	return to_string(ws);
}

  //////////////////////////
 // OSIREM 
// Memory Improvements
std::vector<std::vector<std::string>> g_VectorObjectName;
std::vector<int> g_Proll;

std::shared_mutex g_MemLockMutex;

void ag_LockMutex(void)
{
	g_MemLockMutex.lock();
}

void ag_UnLockMutex(void)
{
	g_MemLockMutex.unlock();
}

  ////////////////////////////////////////////////
 // Osirem reflection ///////////////////////////
// ac_Push() Overloaded Specialized Deduction //

#ifndef OSI_MEM_APP
void ecom_base::ac_Push(bool& f_Var, std::string f_MemberVarName)
{
	m_Map_Bool.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(float& f_Var, std::string f_MemberVarName)
{
	m_Map_Float.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(double& f_Var, std::string f_MemberVarName)
{
	m_Map_Double.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(int& f_Var, std::string f_MemberVarName)
{
	m_Map_Int.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(unsigned int& f_Var, std::string f_MemberVarName)
{
	m_Map_UInt.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(char& f_Var, std::string f_MemberVarName)
{
	m_Map_Char.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(unsigned char& f_Var, std::string f_MemberVarName)
{
	m_Map_UChar.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::string& f_Var, std::string f_MemberVarName)
{
	m_Map_String.emplace(f_MemberVarName, &f_Var);
}
//./
//./vec
//./
void ecom_base::ac_Push(std::vector<bool>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_Bool.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<float>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_Float.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<double>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_Double.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<int>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_Int.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<unsigned int>& f_Var, std::string f_MemberVarName)
{
	if (m_veclayer1 == nullptr)
	{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
	}

	m_veclayer1->m_vec_Map_UInt.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<char>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_Char.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<unsigned char>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_UChar.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::string>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer1 == nullptr)
		{
		m_veclayer1 = make_shared<ecom_vector_layer1>();
		}

	m_veclayer1->m_vec_Map_String.emplace(f_MemberVarName, &f_Var);
}
//./
//./vec_vec
//./
void ecom_base::ac_Push(std::vector<std::vector<bool>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_Bool.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<float>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_Float.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<double>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_Double.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<int>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_Int.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<unsigned int>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_UInt.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<char>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_Char.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<unsigned char>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_UChar.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::string>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer2 == nullptr)
		{
		m_veclayer2 = make_shared<ecom_vector_layer2>();
		}

	m_veclayer2->m_vec_vec_Map_String.emplace(f_MemberVarName, &f_Var);
}
//./
//./vec_vec_vec
//./
void ecom_base::ac_Push(std::vector<std::vector<std::vector<bool>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_Bool.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<float>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_Float.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<double>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_Double.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<int>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_Int.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<unsigned int>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_UInt.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<char>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_Char.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<unsigned char>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_UChar.emplace(f_MemberVarName, &f_Var);
}

void ecom_base::ac_Push(std::vector<std::vector<std::vector<std::string>>>& f_Var, std::string f_MemberVarName)
{
	if(m_veclayer3 == nullptr)
		{
		m_veclayer3 = make_shared<ecom_vector_layer3>();
		}

	m_veclayer3->m_vec_vec_vec_Map_String.emplace(f_MemberVarName, &f_Var);
}
#endif
//...

  ////////////////////////////////////////////////
 // Osirem [GLOBAL] reflection //////////////////
// ac_Push() Overloaded Specialized Deduction //
void ag_Push(bool& f_Var, std::string f_GlobalVarName)
{
#ifdef ECOIN_OSI_MEMORY
	g_Map_Bool.emplace(f_GlobalVarName, &f_Var);
#endif
}

void ag_Push(float& f_Var, std::string f_GlobalVarName)
{
#ifdef ECOIN_OSI_MEMORY
	g_Map_Float.emplace(f_GlobalVarName, &f_Var);
#endif
}

void ag_Push(double& f_Var, std::string f_GlobalVarName)
{
#ifdef ECOIN_OSI_MEMORY
	g_Map_Double.emplace(f_GlobalVarName, &f_Var);
#endif
}

void ag_Push(int& f_Var, std::string f_GlobalVarName)
{
#ifdef ECOIN_OSI_MEMORY
	g_Map_Int.emplace(f_GlobalVarName, &f_Var);
#endif
}

void ag_Push(unsigned int& f_Var, std::string f_GlobalVarName)
{
#ifdef ECOIN_OSI_MEMORY
	g_Map_UInt.emplace(f_GlobalVarName, &f_Var);
#endif
}

void ag_Push(char& f_Var, std::string f_GlobalVarName)
{
#ifdef ECOIN_OSI_MEMORY
	g_Map_Char.emplace(f_GlobalVarName, &f_Var);
#endif
}

void ag_Push(unsigned char& f_Var, std::string f_GlobalVarName)
{
#ifdef ECOIN_OSI_MEMORY
	g_Map_UChar.emplace(f_GlobalVarName, &f_Var);
#endif
}

void ag_Push(std::string& f_Var, std::string f_GlobalVarName)
{
#ifdef ECOIN_OSI_MEMORY
	g_Map_String.emplace(f_GlobalVarName, &f_Var);
#endif
}

//...
#ifndef OSI_MEM_APP
bool* ecom_base::ac_GetBLT(std::string f_MemberVarName)
{
	return m_Map_Bool[f_MemberVarName];
}

float* ecom_base::ac_GetFLT(std::string f_MemberVarName)
{
	return m_Map_Float[f_MemberVarName];
}

int* ecom_base::ac_GetINT(std::string f_MemberVarName)
{
	return m_Map_Int[f_MemberVarName];
}

std::string* ecom_base::ac_GetSTR(std::string f_MemberVarName)
{
	return m_Map_String[f_MemberVarName];
}

#if 0
template<typename _Ret, typename _Class, typename... T>
void ag_PushFunction(std::string f_NameString, boost::any f_AnyFunction, _Ret(_Class::* f_Pm)(T... args))
{
	//save main function globally conditionally
	g_Map_Function.emplace(f_NameString, f_AnyFunction);

	//save main function signal globally conditionally
	g_Map_Function_Sig.emplace(f_NameString, std::make_shared<sig_t>(f_NameString, f_Pm));
}

template<typename _Class, typename... T>
void ag_PushFunction(std::string f_NameString, bool f_Void, boost::any f_AnyFunction, void(_Class::* f_Pm)(T... args))
{
	//save main function globally conditionally
	g_Map_Function.emplace(f_NameString, f_AnyFunction);

	//save main function signal globally conditionally
	g_Map_Function_Sig.emplace(f_NameString, std::make_shared<sig_t>(f_NameString, f_Pm, f_Void));
}
#endif

std::shared_ptr<ecom_base> ag_Produce_base(std::string f_MappingString)
{
	std::shared_ptr<ecom_base> f_VoxelGridManagerRefBase = nullptr;

	if(g_Map_ecomRefBase.find(f_MappingString) != g_Map_ecomRefBase.end())
		{//////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////
		f_VoxelGridManagerRefBase = g_Map_ecomRefBase[f_MappingString];
		}
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak(); //not found in reflection! Lose! //add debug message
		}
#endif

	return f_VoxelGridManagerRefBase;
}
#endif

void ag_DeleteMapObject(std::string f_MapNamePath)
{
#ifndef OSI_MEM_APP
	if(g_Map_ecomRefBase.find(f_MapNamePath) != g_Map_ecomRefBase.end())
        {
        std::shared_ptr<ecom_base> f_base = g_Map_ecomRefBase[f_MapNamePath];

        if(f_base->m_PathName.length() > 1)
            {
            f_base->m_PathName.clear();
            f_base->m_Status = 3;

			g_Map_ecomRefBase[f_MapNamePath].reset();
            }
        }
#endif
}

std::string ag_Build_Path(PathPosition f_PP)
{
	std::string f_Path = "";
	std::string f_UsualPath = "";

	for(int f_XY = 0; f_XY < g_vec_Path[f_PP.m_X].size(); f_XY++)
		{
		std::string f_String = g_vec_Path[f_PP.m_X][f_XY];

		if(f_UsualPath.compare(f_String) != 0)
			{
			f_UsualPath = f_String;

			f_Path += f_String + g_ref_Path_Div;
			}
		}

	return f_Path;
}

PathPosition ag_Find_Path_Index(std::string f_MicroPath)
{
	if(g_vec_Path.size() > 0)
		{
		for(int f_X = g_vec_Path.size() - 1; f_X >= 0; f_X--)
			{
			for(int f_Y = g_vec_Path[f_X].size() - 1; f_Y >= 0; f_Y--)
				{
				if(g_vec_Path[f_X][f_Y].compare(f_MicroPath) == 0)
					{
					return PathPosition(f_X, f_Y);
					}
				}
			}
		}

	return PathPosition(-1, -1);
}

void ag_CentraliseCull(std::string f_CullStringPath)
{
	if(g_vec_Path.size() > 0)
		{
		for(int f_Y = g_vec_Path[g_PP.m_X].size() - 1; f_Y >= 0; f_Y--)
			{
			if(g_vec_Path[g_PP.m_X][f_Y].compare(f_CullStringPath) == 0)
				{
				g_vec_Path[g_PP.m_X].pop_back();
				g_vec_PathLabel[g_PP.m_X].pop_back();

				if(g_PP.m_Y >= g_vec_Path[g_PP.m_X].size())
					{
					g_PP.m_Y = g_vec_Path[g_PP.m_X].size() - 1;
					}
				}
			}
		}
}

int g_starttime;
int g_curfps;
int g_frame_count;

int gui_InsertType;
int g_Spawn_Finger;

std::string g_QA_Username;
std::string g_QA_Password;

bool g_Un;
unsigned char* g_Unn;

PathPosition g_PP;

std::vector<QINT_InterfaceItem*> g_vec_QINT_Input;
std::vector<QINT_InterfaceItem*> g_vec_QINT_Control;
std::vector<QINT_InterfaceItem*> g_vec_QINT_Output;

//access osirem reflection
void ag_StatusLive(std::string f_Path, std::string f_Label, bool f_Prepare, int f_VecIndex)
{
#ifdef ECOIN_OSI_MEMORY
#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_LockMutex();
#endif

	if(f_VecIndex >= g_VectorObjectName.size())
		{
		std::vector<std::string> f_vecstr;

		g_VectorObjectName.push_back(f_vecstr);
		}

	PathPosition f_PP = ag_Find_Path_Index(f_Path);

	//check for reset
	bool f_ChkReset = false;
	bool f_PathFound = false;
	bool f_Found = false;

	if((f_PP.m_X >= 0) && (f_PP.m_Y >= 0))
		{
		f_PathFound = true;
		}

	std::string f_SavePath = "";

	if(g_vec_Path.size() > 0)
		{
		if(f_Path.at(0) == ':')
			{
			if(f_Path.at(2) == ':')
				{
				if((f_Path.at(1) == 'E') || (f_Path.at(1) == 'F') || (f_Path.at(1) == 'G')) //win conditions reset
					{
					if(f_PathFound == true)
						{
						if(f_Path.compare(g_vec_Path[f_PP.m_X][f_PP.m_Y]) == 0)
							{
							std::string f_BuildPathA = ag_Build_Path(f_PP) + f_Label;

							f_Found = true;
							f_ChkReset = true;

							g_PP.m_X = f_PP.m_X;
							g_PP.m_Y = f_PP.m_Y;

							f_SavePath = f_BuildPathA;
							}
						else
							{
							throw; //should not be here
							}
						}
					else //win conditions - new reset vector beam
						{
						std::vector<std::string> f_vec_String;
						std::vector<std::string> f_vec_String_Label;

						f_vec_String.clear();
						f_vec_String_Label.clear();

						std::string f_BuildPathA = f_Path;

						f_vec_String.push_back(f_BuildPathA);

						std::string f_BuildPathB = f_Path + g_ref_Path_Div + f_Label;

						f_vec_String_Label.push_back(f_BuildPathB);

						g_vec_Path.push_back(f_vec_String);
						g_vec_PathLabel.push_back(f_vec_String_Label);

						g_PP.m_X = g_vec_Path.size() - 1;
						g_PP.m_Y = 0;

						f_SavePath = f_BuildPathB;

						f_ChkReset = true;
						}
					}
				}
			}

		if(f_ChkReset == false)
			{
			if((f_PathFound == true) && (f_Found == false))
				{
				if(f_Path.compare(g_vec_Path[f_PP.m_X][f_PP.m_Y]) == 0)
					{
					std::string f_BuildPathA = ag_Build_Path(f_PP) + f_Label;

					if((g_PP.m_X == f_PP.m_X) && (g_PP.m_Y != f_PP.m_Y))
						{
						int f_CurrentStackMax = g_vec_Path[f_PP.m_X].size();

						if(f_PP.m_Y < g_PP.m_Y)
							{
							int f_NewStackMax = f_CurrentStackMax - f_PP.m_Y;

							for(int f_Y = 0; f_Y < f_NewStackMax; f_Y++)
								{
								g_vec_Path[g_PP.m_X].pop_back();
								g_vec_PathLabel[g_PP.m_X].pop_back();
								}

							g_PP.m_Y = f_PP.m_Y;
							}
						else if(f_PP.m_Y == g_PP.m_Y)
							{
							//... win
							}
						else if(f_PP.m_Y > g_PP.m_Y)
							{
							g_PP.m_Y = f_PP.m_Y;
							}
						else
							{
							throw;
							}

						f_SavePath = f_BuildPathA;

						f_Found = true; //win conditions on same scope x differ y
						}
					else if(g_PP.m_Y != f_PP.m_Y)
						{
						int f_CurrentStackMax = g_vec_Path[g_PP.m_X].size();

						if(f_PP.m_Y < f_CurrentStackMax)
							{
							int f_NewStackMax = f_CurrentStackMax - f_PP.m_Y;

							for(int f_Y = 0; f_Y < f_NewStackMax; f_Y++)
								{
								g_vec_Path[g_PP.m_X].pop_back();
								g_vec_PathLabel[g_PP.m_X].pop_back();
								}

							g_PP.m_X = f_PP.m_X;
							g_PP.m_Y = f_PP.m_Y;
							}
						else if(f_PP.m_Y == g_PP.m_Y)
							{
							g_PP.m_X = f_PP.m_X;

							//... win
							}
						else if(f_PP.m_Y > g_PP.m_Y)
							{
							g_PP.m_X = f_PP.m_X;
							g_PP.m_Y = f_PP.m_Y;
							}
						else
							{
							throw;
							}

						f_SavePath = f_BuildPathA;

						f_Found = true; //win conditions on same scope x differ y
						}
					else
						{
						f_SavePath = f_BuildPathA; //win same path
						}
					}
				else
					{
					throw; //unlikely
					}
				}
			else
				{
				g_vec_Path[g_PP.m_X].push_back(f_Path);

				g_PP.m_Y = g_vec_Path[g_PP.m_X].size() - 1;

				std::string f_BuildPathA = ag_Build_Path(g_PP) + f_Label;
				
				g_vec_PathLabel[g_PP.m_X].push_back(f_BuildPathA);

				f_SavePath = f_BuildPathA;
				}
			}
		}
	else
		{
		g_PP.m_X = 0;
		g_PP.m_Y = 0;

		std::vector<std::string> f_vec_String;
		std::vector<std::string> f_vec_String_Label;

		f_vec_String.clear();
		f_vec_String.push_back(f_Path);

		std::string f_BuildPathB = f_Path + g_ref_Path_Div + f_Label;

		f_vec_String_Label.clear();
		f_vec_String_Label.push_back(f_BuildPathB);

		g_vec_Path.push_back(f_vec_String);
		g_vec_PathLabel.push_back(f_vec_String_Label);

		f_SavePath = f_BuildPathB;
		}

	g_VectorObjectName[f_VecIndex].push_back(f_SavePath);

	g_Proll.push_back(f_VecIndex);

#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_UnLockMutex();
#endif
#endif
}

void ag_StatusSync(std::string f_Path, std::string f_Label, bool f_Prepare, int f_VecIndex)
{
#ifdef ECOIN_OSI_MEMORY
#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_LockMutex();
#endif

	//Call ag_SyncState

#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_UnLockMutex();
#endif
#endif
}

std::string ag_AcceptObjectName(void)
{
#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_LockMutex();
#endif

    if(g_VectorObjectName.size() > 0 && (g_Proll.size() > 0))
        {
		int f_Int = g_Proll[g_Proll.size() - 1];

		if(g_VectorObjectName[f_Int].size() > 0)
			{
			std::string f_PulledObjectName = g_VectorObjectName[f_Int][0];

			for(int f_Jet = 0; f_Jet < g_VectorObjectName[f_Int].size() - 1; f_Jet++)
				{
				g_VectorObjectName[f_Int][f_Jet] = g_VectorObjectName[f_Int][f_Jet + 1];
				}

			g_VectorObjectName[f_Int].pop_back();

			g_Proll.pop_back();

#ifdef ECOIN_DBG_BREAK
#ifdef ECOIN_REFLECT_STATUS_LIVE_OVERFLOW
			if(g_VectorObjectName[f_Int].size() > 1)
				{
				__debugbreak();
				}
#endif
#endif //add debug message

#ifdef ECOIN_MEMORY_FULL_MUTEX
			ag_UnLockMutex();
#endif

			return f_PulledObjectName;
			}
        }

#ifdef ECOIN_MEMORY_FULL_MUTEX
	ag_UnLockMutex();
#endif

#ifdef ECOIN_DBG_BREAK
	__debugbreak();
#endif //add debug message

#ifdef ECOIN_DEBUG_BREAKS
	__debugbreak();
#endif //add debug message

    return std::string("noname");
}

bool ag_GetKey(int f_Key)
{
	return g_Qy[f_Key];
}

EGLSurface g_RenderSurface(EGL_NO_SURFACE);
angle::OpenGLES g_OpenGLES;

//Thread Control
std::shared_mutex g_OGL_Muti;
int g_Current_ThreadID;

void ag_Lock_OpenGL(int f_ThreadID)
{
	g_OGL_Muti.lock();

	if(f_ThreadID != g_Current_ThreadID)
		{
		g_UpdatingMuti.lock(); //???!!!

		g_OpenGLES.MakeCurrent(g_RenderSurface);

		g_UpdatingMuti.unlock();
		}

	g_Current_ThreadID = f_ThreadID;
}

void ag_UnLock_OpenGL(int f_ThreadID)
{
#ifdef ECOIN_DEBUG_BREAKS
	if(f_ThreadID != g_Current_ThreadID)
		{
		__debugbreak(); //add debug message
		}
#endif

	g_OGL_Muti.unlock();
}

void ecom_base::ac_Attach_Void(std::string f_FuncString, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
{
	//aquire function signiture
	std::shared_ptr<FuncHolding> f_FuncHolding = g_Map_Function_Sig[f_FuncString]; //ac_Call_FuncVar

	if(f_FuncHolding->m_VOIDCNT == 1)
		{
		//call function
		if(f_CodeLine->m_vec_Variable.size() <= 0)
			{
			f_FuncHolding->ac_Call_FuncVoidVoid((std::shared_ptr<ecom_base>)this);
			}
		else
			{
			f_FuncHolding->ac_Call_FuncVoidPrm((std::shared_ptr<ecom_base>)this, f_CodeLine);
			}
		}
	else if(f_FuncHolding->m_VOIDCNT == 2)
		{
		//call function
		f_FuncHolding->ac_Call_FuncVoidVoid((std::shared_ptr<ecom_base>)this);
		}
#ifdef ECOIN_DEBUG_BREAKS
	else
		{
		__debugbreak(); //add debug breaks
		}
#endif
}

ecom_base::base_type ecom_base::ac_Attach_Base(std::string f_FuncString, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
{
	//aquire function signiture
	std::shared_ptr<FuncHolding> f_FuncHolding = g_Map_Function_Sig[f_FuncString]; //ac_Call_FuncVar

	if(f_FuncHolding->m_VOIDCNT == 1)
		{
		//call function
		if(f_CodeLine->m_vec_Variable.size() <= 1)
			{
			f_FuncHolding->ac_Call_FuncBaseVoid((std::shared_ptr<ecom_base>)this);
			}
		else
			{
			f_FuncHolding->ac_Call_FuncBase((std::shared_ptr<ecom_base>)this, f_CodeLine);
			}
		}

	//call function
	return f_FuncHolding->ac_Call_FuncBase((std::shared_ptr<ecom_base>)this, f_CodeLine);
}

std::shared_ptr<ecoin::Variable> ecom_base::ac_Attach_Var(std::string f_FuncString, std::shared_ptr<ecoin::CodeLine> f_CodeLine)
{
	//aquire function signiture
	std::shared_ptr<FuncHolding> f_FuncHolding = g_Map_Function_Sig[f_FuncString]; //ac_Call_FuncVar

	if(f_FuncHolding->m_VOIDCNT == 1)
		{
		//call function
		if(f_CodeLine->m_vec_Variable.size() <= 1)
			{
			f_FuncHolding->ac_Call_FuncVarVoid((std::shared_ptr<ecom_base>)this);
			}
		else
			{
			f_FuncHolding->ac_Call_FuncVar((std::shared_ptr<ecom_base>)this, f_CodeLine);
			}
		}

	//call function
	return f_FuncHolding->ac_Call_FuncVar((std::shared_ptr<ecom_base>)this, f_CodeLine);
}

#ifdef REFLECT_LAZY_ECOM_OVERLOAD
template <typename _Class, typename _String, typename _V1>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1), _V1 f_V1)
{
	std::shared_ptr<LazyFunctionEV1<_Class, _String, _V1>> f_LazyFunc = std::make_shared<LazyFunctionEV1<_Class, _String, _V1>>(std::forward<std::string>(f_String), 0, _Pm, f_V1);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2), _V1 f_V1, _V2 f_V2)
{
	std::shared_ptr<LazyFunctionEV2<_Class, _String, _V1, _V2>> f_LazyFunc = std::make_shared<LazyFunctionEV2<_Class, _String, _V1, _V2>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3), _V1 f_V1, _V2 f_V2, _V3 f_V3)
{
	std::shared_ptr<LazyFunctionEV3<_Class, _String, _V1, _V2, _V3>> f_LazyFunc = std::make_shared<LazyFunctionEV3<_Class, _String, _V1, _V2, _V3>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4)
{
	std::shared_ptr<LazyFunctionEV4<_Class, _String, _V1, _V2, _V3, _V4>> f_LazyFunc = std::make_shared<LazyFunctionEV4<_Class, _String, _V1, _V2, _V3, _V4>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5)
{
	std::shared_ptr<LazyFunctionEV5<_Class, _String, _V1, _V2, _V3, _V4, _V5>> f_LazyFunc = std::make_shared<LazyFunctionEV5<_Class, _String, _V1, _V2, _V3, _V4, _V5>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6)
{
	std::shared_ptr<LazyFunctionEV6<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6>> f_LazyFunc = std::make_shared<LazyFunctionEV6<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7)
{
	std::shared_ptr<LazyFunctionEV7<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7>> f_LazyFunc = std::make_shared<LazyFunctionEV7<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8)
{
	std::shared_ptr<LazyFunctionEV8<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8>> f_LazyFunc = std::make_shared<LazyFunctionEV8<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9)
{
	std::shared_ptr<LazyFunctionEV9<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9>> f_LazyFunc = std::make_shared<LazyFunctionEV9<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10)
{
	std::shared_ptr<LazyFunctionEV10<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10>> f_LazyFunc = std::make_shared<LazyFunctionEV10<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11)
{
	std::shared_ptr<LazyFunctionEV11<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11>> f_LazyFunc = std::make_shared<LazyFunctionEV11<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12)
{
	std::shared_ptr<LazyFunctionEV12<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12>> f_LazyFunc = std::make_shared<LazyFunctionEV12<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13)
{
	std::shared_ptr<LazyFunctionEV13<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13>> f_LazyFunc = std::make_shared<LazyFunctionEV13<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14)
{
	std::shared_ptr<LazyFunctionEV14<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14>> f_LazyFunc = std::make_shared<LazyFunctionEV14<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15)
{
	std::shared_ptr<LazyFunctionEV15<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15>> f_LazyFunc = std::make_shared<LazyFunctionEV15<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16)
{
	std::shared_ptr<LazyFunctionEV16<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16>> f_LazyFunc = std::make_shared<LazyFunctionEV16<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17)
{
	std::shared_ptr<LazyFunctionEV17<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17>> f_LazyFunc = std::make_shared<LazyFunctionEV17<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18)
{
	std::shared_ptr<LazyFunctionEV18<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18>> f_LazyFunc = std::make_shared<LazyFunctionEV18<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17, f_V18);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19)
{
	std::shared_ptr<LazyFunctionEV19<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19>> f_LazyFunc = std::make_shared<LazyFunctionEV19<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17, f_V18, f_V19);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19, typename _V20>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19, _V20 f_V20)
{
	std::shared_ptr<LazyFunctionEV20<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20>> f_LazyFunc = std::make_shared<LazyFunctionEV20<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17, f_V18, f_V19, f_V20);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}
#endif

template <typename _Ret, typename _Class, typename _String, typename _V1>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1), _V1 f_V1)
{
	std::shared_ptr<LazyFunctionVV1<_Ret, _Class, _String, _V1>> f_LazyFunc = std::make_shared<LazyFunctionVV1<_Ret, _Class, _String, _V1>>(std::forward<std::string>(f_String), 0, _Pm, f_V1);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2), _V1 f_V1, _V2 f_V2)
{
	std::shared_ptr<LazyFunctionVV2<_Ret, _Class, _String, _V1, _V2>> f_LazyFunc = std::make_shared<LazyFunctionVV2<_Ret, _Class, _String, _V1, _V2>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3), _V1 f_V1, _V2 f_V2, _V3 f_V3)
{
	std::shared_ptr<LazyFunctionVV3<_Ret, _Class, _String, _V1, _V2, _V3>> f_LazyFunc = std::make_shared<LazyFunctionVV3<_Ret, _Class, _String, _V1, _V2, _V3>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4)
{
	std::shared_ptr<LazyFunctionVV4<_Ret, _Class, _String, _V1, _V2, _V3, _V4>> f_LazyFunc = std::make_shared<LazyFunctionVV4<_Ret, _Class, _String, _V1, _V2, _V3, _V4>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5)
{
	std::shared_ptr<LazyFunctionVV5<_Ret, _Class, _String, _V1, _V2, _V3, _V4, _V5>> f_LazyFunc = std::make_shared<LazyFunctionVV5<_Ret, _Class, _String, _V1, _V2, _V3, _V4, _V5>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6)
{
	std::shared_ptr<LazyFunctionVV6<_Ret, _Class, _String, _V1, _V2, _V3, _V4, _V5, _V6>> f_LazyFunc = std::make_shared<LazyFunctionVV6<_Ret, _Class, _String, _V1, _V2, _V3, _V4, _V5, _V6>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7)
{
	std::shared_ptr<LazyFunctionVV7<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7>> f_LazyFunc = std::make_shared<LazyFunctionVV7<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8)
{
	std::shared_ptr<LazyFunctionVV8<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8>> f_LazyFunc = std::make_shared<LazyFunctionVV8<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9)
{
	std::shared_ptr<LazyFunctionVV9<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9>> f_LazyFunc = std::make_shared<LazyFunctionVV9<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10)
{
	std::shared_ptr<LazyFunctionVV10<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10>> f_LazyFunc = std::make_shared<LazyFunctionVV10<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11)
{
	std::shared_ptr<LazyFunctionVV11<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11>> f_LazyFunc = std::make_shared<LazyFunctionVV11<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12)
{
	std::shared_ptr<LazyFunctionVV12<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12>> f_LazyFunc = std::make_shared<LazyFunctionVV12<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13)
{
	std::shared_ptr<LazyFunctionVV13<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13>> f_LazyFunc = std::make_shared<LazyFunctionVV13<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14)
{
	std::shared_ptr<LazyFunctionVV14<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14>> f_LazyFunc = std::make_shared<LazyFunctionVV14<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15)
{
	std::shared_ptr<LazyFunctionVV15<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15>> f_LazyFunc = std::make_shared<LazyFunctionVV15<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16)
{
	std::shared_ptr<LazyFunctionVV16<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16>> f_LazyFunc = std::make_shared<LazyFunctionVV16<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17)
{
	std::shared_ptr<LazyFunctionVV17<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17>> f_LazyFunc = std::make_shared<LazyFunctionVV17<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18)
{
	std::shared_ptr<LazyFunctionVV18<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18>> f_LazyFunc = std::make_shared<LazyFunctionVV18<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17, f_V18);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19)
{
	std::shared_ptr<LazyFunctionVV19<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19>> f_LazyFunc = std::make_shared<LazyFunctionVV19<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17, f_V18, f_V19);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Ret, typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19, typename _V20>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19, _V20 f_V20)
{
	std::shared_ptr<LazyFunctionVV20<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20>> f_LazyFunc = std::make_shared<LazyFunctionVV20<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20>>(std::forward<std::string>(f_String), 0, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17, f_V18, f_V19, f_V20);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1), _V1 f_V1)
{
	std::shared_ptr<LazyFunctionRV1<_Class, _String, _V1>> f_LazyFunc = std::make_shared<LazyFunctionRV1<_Class, _String, _V1>>(std::forward<std::string>(f_String), 1, _Pm, f_V1);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2), _V1 f_V1, _V2 f_V2)
{
	std::shared_ptr<LazyFunctionRV2<_Class, _String, _V1, _V2>> f_LazyFunc = std::make_shared<LazyFunctionRV2<_Class, _String, _V1, _V2>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3), _V1 f_V1, _V2 f_V2, _V3 f_V3)
{
	std::shared_ptr<LazyFunctionRV3<_Class, _String, _V1, _V2, _V3>> f_LazyFunc = std::make_shared<LazyFunctionRV3<_Class, _String, _V1, _V2, _V3>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4)
{
	std::shared_ptr<LazyFunctionRV4<_Class, _String, _V1, _V2, _V3, _V4>> f_LazyFunc = std::make_shared<LazyFunctionRV4<_Class, _String, _V1, _V2, _V3, _V4>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5)
{
	std::shared_ptr<LazyFunctionRV5<_Class, _String, _V1, _V2, _V3, _V4, _V5>> f_LazyFunc = std::make_shared<LazyFunctionRV5<_Class, _String, _V1, _V2, _V3, _V4, _V5>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6)
{
	std::shared_ptr<LazyFunctionRV6<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6>> f_LazyFunc = std::make_shared<LazyFunctionRV6<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7)
{
	std::shared_ptr<LazyFunctionRV7<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7>> f_LazyFunc = std::make_shared<LazyFunctionRV7<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8)
{
	std::shared_ptr<LazyFunctionRV8<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8>> f_LazyFunc = std::make_shared<LazyFunctionRV8<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9)
{
	std::shared_ptr<LazyFunctionRV9<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9>> f_LazyFunc = std::make_shared<LazyFunctionRV9<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10)
{
	std::shared_ptr<LazyFunctionRV10<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10>> f_LazyFunc = std::make_shared<LazyFunctionRV10<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11)
{
	std::shared_ptr<LazyFunctionRV11<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11>> f_LazyFunc = std::make_shared<LazyFunctionRV11<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12)
{
	std::shared_ptr<LazyFunctionRV12<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12>> f_LazyFunc = std::make_shared<LazyFunctionRV12<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13)
{
	std::shared_ptr<LazyFunctionRV13<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13>> f_LazyFunc = std::make_shared<LazyFunctionRV13<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14)
{
	std::shared_ptr<LazyFunctionRV14<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14>> f_LazyFunc = std::make_shared<LazyFunctionRV14<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15)
{
	std::shared_ptr<LazyFunctionRV15<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15>> f_LazyFunc = std::make_shared<LazyFunctionRV15<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16)
{
	std::shared_ptr<LazyFunctionRV16<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16>> f_LazyFunc = std::make_shared<LazyFunctionRV16<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17)
{
	std::shared_ptr<LazyFunctionRV17<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17>> f_LazyFunc = std::make_shared<LazyFunctionRV17<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18)
{
	std::shared_ptr<LazyFunctionRV18<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18>> f_LazyFunc = std::make_shared<LazyFunctionRV18<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17, f_V18);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19)
{
	std::shared_ptr<LazyFunctionRV19<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19>> f_LazyFunc = std::make_shared<LazyFunctionRV19<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17, f_V18, f_V19);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String, typename _V1, typename _V2, typename _V3, typename _V4, typename _V5, typename _V6, typename _V7, typename _V8, typename _V9, typename _V10, typename _V11, typename _V12, typename _V13, typename _V14, typename _V15, typename _V16, typename _V17, typename _V18, typename _V19, typename _V20>
void make_lazy(_String f_String, void(_Class::* _Pm)(_V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20), _V1 f_V1, _V2 f_V2, _V3 f_V3, _V4 f_V4, _V5 f_V5, _V6 f_V6, _V7 f_V7, _V8 f_V8, _V9 f_V9, _V10 f_V10, _V11 f_V11, _V12 f_V12, _V13 f_V13, _V14 f_V14, _V15 f_V15, _V16 f_V16, _V17 f_V17, _V18 f_V18, _V19 f_V19, _V20 f_V20)
{
	std::shared_ptr<LazyFunctionRV20<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20>> f_LazyFunc = std::make_shared<LazyFunctionRV20<_Class, _String, _V1, _V2, _V3, _V4, _V5, _V6, _V7, _V8, _V9, _V10, _V11, _V12, _V13, _V14, _V15, _V16, _V17, _V18, _V19, _V20>>(std::forward<std::string>(f_String), 1, _Pm, f_V1, f_V2, f_V3, f_V4, f_V5, f_V6, f_V7, f_V8, f_V9, f_V10, f_V11, f_V12, f_V13, f_V14, f_V15, f_V16, f_V17, f_V18, f_V19, f_V20);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

#ifdef REFLECT_LAZY_ECOM_OVERLOAD
template <typename _Class, typename _String>
void make_lazy(_String f_String, std::shared_ptr<ecom_base>(_Class::* _Pm)(void))
{
	std::shared_ptr<LazyFunctionREV<_Class, _String>> f_LazyFunc = std::make_shared<LazyFunctionREV<_Class, _String>>(std::forward<std::string>(f_String), 1, _Pm);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}
#endif

template <typename _Ret, typename _Class, typename _String>
void make_lazy(_String f_String, _Ret(_Class::* _Pm)(void))
{
	std::shared_ptr<LazyFunctionRVV<_Ret, _Class, _String>> f_LazyFunc = std::make_shared<LazyFunctionRVV<_Ret, _Class, _String>>(std::forward<std::string>(f_String), 1, _Pm);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}

template <typename _Class, typename _String>
void make_lazy(_String f_String, void(_Class::* _Pm)(void))
{
	std::shared_ptr<LazyFunctionVV<_Class, _String>> f_LazyFunc = std::make_shared<LazyFunctionVV<_Class, _String>>(std::forward<std::string>(f_String), 2, _Pm);

	std::shared_ptr<FuncHolding> f_FuncHolding = f_LazyFunc;

	g_Map_Function_Sig.emplace(f_FuncHolding->m_name, f_FuncHolding);
}