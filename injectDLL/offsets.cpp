#include "stdafx.h"
#include "offsets.h"

 DWORD baseAddr;

 const DWORD weapon_baseOffset = 0x0010F4F4;
//std::vector<DWORD>WPN_2ND_CLASS_OFFSETS = { 0x378, 0x18, 0x1FC };
 const std::vector<DWORD>WPN_CURRENT_CLASS_OFFSETS = { 0x374, 0x0 };
//std::vector<DWORD>WPN_2ND_CLASS_OFFSETS = { 0x378 };
//std::vector<DWORD>weapon_class_assault_vft = { 0x378, 0x18, 0x1FC ,0x0 };
//std::vector<DWORD>weapon_class_assault_spreadFunc = { 0x378, 0x18, 0x1FC ,0x0, 0x04 };
//std::vector<DWORD>weapon_class_assault_recoilFunc = { 0x378, 0x18, 0x1FC ,0x0, 0x08 };
 const std::vector<DWORD>WPN_CURRENT_MAG_OFFSETS = { 0x374, 0x14, 0x0 };
 const std::vector<DWORD>WPN_CURRENT_WAIT_OFFSETS = { 0x374, 0x18, 0x0 };
//std::vector<DWORD>WPN_2ND_MAG_OFFSETS = { 0x378, 0x18, 0x1FC, 0x14 };
//std::vector<DWORD>WPN_2ND_WAIT_OFFSETS = { 0x378, 0x18, 0x1FC, 0x18 };
//std::vector<DWORD>WPN_2ND_MAG_OFFSETS = { 0x378, 0x14 };
//std::vector<DWORD>WPN_2ND_WAIT_OFFSETS = { 0x378, 0x18 };
 const std::vector<DWORD>WPN_CURRENT_INFO_OFFSETS = { 0x374,0x0B, 0x0 };
 const std::vector<DWORD>WPN_CURRENT_ISAUTO_OFFSETS = { 0x374, 0xC, 0x128 };           //auto weapon flag 
 const std::vector<DWORD>WPN_CURRENT_DELAY_OFFSETS = { 0x374, 0xC, 0x10A };