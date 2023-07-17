/*

Code - osirem.com
Copyright OSIREM LTD (C) 2016
bitolyl.com bitcoin-office.com ecn.world

This source is proprietary, and cannot be used, in part or in full without
the express permission of the original author. The original author retain the
rights to use, modify, and/or relicense this code without notice.

*/

#include "pch.h"

#include "Code/myBO/icSafeL.h"

#include "Wallet/Wallet.h"

#include "Code/ICS/ICS_Types.h"
#include "Code/Cube/qcom.h"
#include "Code/Cube/predator.h"

#include <cctype>
#include <iostream>
#include <cstring>

#include "utilstrencodings.h"

using namespace ecoin;

namespace ecoin
{

template <unsigned int BITS>
ics_base_blob<BITS>::ics_base_blob(const std::vector<unsigned int>& vch)
{
    assert(vch.size() == sizeof(data));
    memcpy(data, vch.data(), sizeof(data));
}

template <unsigned int BITS>
std::string ics_base_blob<BITS>::GetHex() const
{
    return HexStr(std::reverse_iterator<const unsigned int*>(data + sizeof(data)), std::reverse_iterator<const unsigned int*>(data));
}

template <unsigned int BITS>
void ics_base_blob<BITS>::SetHex(const char* psz)
{
    memset(data, 0, sizeof(data));

    // skip leading spaces
    while (isspace(*psz))
        psz++;

    // skip 0x
    if (psz[0] == '0' && tolower(psz[1]) == 'x')
        psz += 2;

    // hex string to uint
    const char* pbegin = psz;
    while (::HexDigit(*psz) != -1)
        psz++;
    psz--;
    unsigned int* p1 = (unsigned int*)data;
    unsigned int* pend = p1 + WIDTH;
    while (psz >= pbegin && p1 < pend) {
        *p1 = ::HexDigit(*psz--);
        if (psz >= pbegin) {
            *p1 |= ((unsigned int)::HexDigit(*psz--) << 4);
            p1++;
        }
    }
}

template <unsigned int BITS>
void ics_base_blob<BITS>::SetHex(const std::string& str)
{
    SetHex(str.c_str());
}

template <unsigned int BITS>
std::string ics_base_blob<BITS>::ToString() const
{
    return (GetHex());
}

// Explicit instantiations for ics_base_blob<160>
template ics_base_blob<160>::ics_base_blob(const std::vector<unsigned int>&);
template std::string ics_base_blob<160>::GetHex() const;
template std::string ics_base_blob<160>::ToString() const;
template void ics_base_blob<160>::SetHex(const char*);
template void ics_base_blob<160>::SetHex(const std::string&);

// Explicit instantiations for ics_base_blob<256>
template ics_base_blob<256>::ics_base_blob(const std::vector<unsigned int>&);
template std::string ics_base_blob<256>::GetHex() const;
template std::string ics_base_blob<256>::ToString() const;
template void ics_base_blob<256>::SetHex(const char*);
template void ics_base_blob<256>::SetHex(const std::string&);

};