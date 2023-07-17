/*

Target.h - Class Target osirem.com
Copyright OSIREM LTD (C) 2016
www.osirem.com www.ecn.world www.bitcoin-office.com www.bitolyl.com

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#ifndef ICS_TYPES
#define ICS_TYPES

#include <stdint.h>
#include <vector>
#include <math.h>

#include "tinyformat.h"

#include <cstdlib>
#include <cstring>
#include <errno.h>
#include <limits>
#include <random>

//Convertion Headers
#include "Code\Hash\utilstrencodings.h"
#include "Code\Hash\base58.h"

using namespace Cube;
using namespace std;

namespace ecoin
{

#define ICS_RESULTANT_PREC 4096

#define ICS_PASSWORD_LEN 256
#define ICS_PASSWORD_MAX_LEN 1130
#define ICS_PASSWORD_MIX_MAX 50000000
#define ICS_PASSWORD_MINCHAR 128

template<unsigned int BITS>
class ics_base_blob
{
protected:
    enum { WIDTH = BITS / 32 };
    unsigned int data[WIDTH];

public:
    ics_base_blob()
        {
        memset(data, 0, sizeof(data));
        }

    explicit ics_base_blob(const std::vector<unsigned int>& vch);

    bool IsNull() const
        {
        for(int i = 0; i < WIDTH; i++)
            {
            if(data[i] != 0)
                {
                return false;
                }
            }

        return true;
        }

    void SetNull()
        {
        memset(data, 0, sizeof(data));
        }

    inline int Compare(const ics_base_blob& other) const { return memcmp(data, other.data, sizeof(data)); }

    friend inline bool operator==(const ics_base_blob& a, const ics_base_blob& b) { return a.Compare(b) == 0; }
    friend inline bool operator!=(const ics_base_blob& a, const ics_base_blob& b) { return a.Compare(b) != 0; }
    friend inline bool operator<(const ics_base_blob& a, const ics_base_blob& b) { return a.Compare(b) < 0; }

    std::string GetHex() const;
    void SetHex(const char* psz);
    void SetHex(const std::string& str);
    std::string ToString() const;

    unsigned int* begin()
        {
        return &data[0];
        }

    unsigned int* end()
        {
        return &data[WIDTH];
        }

    const unsigned int* begin() const
        {
        return &data[0];
        }

    const unsigned int* end() const
        {
        return &data[WIDTH];
        }

    unsigned int size() const
        {
        return sizeof(data);
        }

    uint64_t GetUint64(int pos) const
        {
        const uint8_t* ptr = data + pos * 8;

        return ((uint64_t)ptr[0]) | \
               ((uint64_t)ptr[1]) << 8 | \
               ((uint64_t)ptr[2]) << 16 | \
               ((uint64_t)ptr[3]) << 24 | \
               ((uint64_t)ptr[4]) << 32 | \
               ((uint64_t)ptr[5]) << 40 | \
               ((uint64_t)ptr[6]) << 48 | \
               ((uint64_t)ptr[7]) << 56;
        }

    std::size_t acActiveIndex(void)
        {
        unsigned int f_UInt = data[0];

        if(f_UInt >= UINT_MAX)
            {
            return 0;
            }

        std::size_t f_Index = 1;

        while(f_UInt >= UINT_MAX)
            {
            f_UInt = data[f_Index];

            f_Index++;
            }

        return f_Index;
        }

    void acPlus(int f_Amount)
        {
        data[acActiveIndex()] = f_Amount;
        }

    template<typename Stream>
    void Serialize(Stream& s) const
        {
        s.write((char*)data, sizeof(data));
        }

    template<typename Stream>
    void Unserialize(Stream& s)
        {
        s.read((char*)data, sizeof(data));
        }
};

class ICS_Mainstream;

#ifdef ICS_LARGE_SIZE
class ICS_Resultant : public ics_base_blob<ICS_RESULTANT_PREC>
#else
class ICS_Resultant
#endif
{
public:
    ICS_Resultant()
        {
        m_Mainstream = nullptr;

        m_FLR = 0.0f;
        m_FinalXLength = 0.0f;
        }

    ICS_Resultant(float f_FinalXlength)
        {
        m_Mainstream = nullptr;

        m_FLR = 0.0f;
        m_FinalXLength = f_FinalXlength;
        }

#ifdef ICS_LARGE_SIZE
    explicit ICS_Resultant(const std::vector<unsigned int>& vch) : ics_base_blob<ICS_RESULTANT_PREC>(vch)
        {
        m_Mainstream = nullptr;

        m_FLR = 0.0f;
        m_FinalXLength = 0.0f;
        }
#endif

    //Add Mainstream
    void acConnectMainstream(std::Smart_Ptr<ICS_Mainstream> f_Mainstream)
        {
        m_Mainstream = f_Mainstream;
        }

    //Spin LEVER
    void acForwardFrameOn(void);
    void acForwardFrameOff(void);

    //Register Frame
    void acRegisterFrame(void);

    //Add Boolean Measurement
    void acBLTV1(bool f_Measurement);

    //Add Integer Measurement
    void acINTV1(int f_StartRange, int f_EndRange, int f_Result);

    //Receive Boolean Measurement
    bool acReceive_BLTV1(void);

    //Receive Integer Measurement
    int acReceive_INTV1(int f_StartRange, int f_EndRange);

    std::Smart_Ptr<ICS_Mainstream> m_Mainstream;

    double m_FLR;

    float m_FinalXLength; //Relative Align Com X Vector Value
};

class ICS_CheckPointPassword
{
public:
    //Default Constructor
    ICS_CheckPointPassword() = default;

    //Salt Constructor
    ICS_CheckPointPassword(bool f_Marker)
        {
        std::random_device engine;

		for(int f_Jet = 0; f_Jet < ICS_PASSWORD_LEN; f_Jet += 2)
			{
			unsigned int f_x = engine();

			unsigned char f_ch[2];

			memcpy(f_ch, (char*)&f_x, sizeof(unsigned int));

            m_Data.push_back(f_ch[0]);
            m_Data.push_back(f_ch[1]);
			}

        //Prepare Print Key Output
        acEncodePrint();
        }

    //Recovery Password
    ICS_CheckPointPassword(std::string f_Password)
        {
        bool f_hOK = DecodeBase58(f_Password, m_Data);

        //Prepare Print Key Output
        m_PrintString = f_Password;
        }

    int acMixFactor(void)
        {
        int f_Result = 0;

		for(int f_Jet = 0; f_Jet < m_Data.size(); f_Jet++)
			{
			unsigned char f_ch = m_Data[f_Jet];

            if(f_Result + f_ch < ICS_PASSWORD_MIX_MAX)
                {
                f_Result += f_ch;
                }
            else
                {
                if(f_Result - f_ch >= 0)
                    {
                    f_Result -= f_ch;
                    }
                }
			}

        return f_Result;
        }
    
    void acEncodePrint(void)
        {
#if 0
        std::string f_HexString = HexStr(std::reverse_iterator<const uint8_t*>(m_Data + sizeof(m_Data)), std::reverse_iterator<const uint8_t*>(m_Data));

		unsigned char *f_p5 = new unsigned char[ICS_PASSWORD_LEN * 2];

		Cube::ag_hex2bin(f_p5, f_HexString.c_str(), f_HexString.length());
#endif

        m_PrintString = EncodeBase58(m_Data);

#if 0
#ifdef ECOIN_DEBUG_BREAKS
        if(m_PrintString.length() != ICS_PASSWORD_LEN)
            {
            __debugbreak();
            }
#endif
#endif
        }

    std::vector<unsigned char> m_Data;
    std::string m_PrintString;
};

class ics_uint256 : public ics_base_blob<256>
{
public:
    ics_uint256() {}

    explicit ics_uint256(const std::vector<unsigned int>& vch) : ics_base_blob<256>(vch) {/**/}

    /** A cheap hash function that just returns 64 bits from the result, it can be
     * used when the contents are considered uniformly random. It is not appropriate
     * when the value can easily be influenced from outside as e.g. a network adversary could
     * provide values to trigger worst-case behavior.
     */
    uint64_t GetCheapHash() const
        {
        return ReadLE64((unsigned char*)data);
        }
};

}; //end ecoin::classTarget namespace

#endif