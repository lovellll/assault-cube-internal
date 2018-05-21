#pragma once
#include <vector>

extern DWORD baseAddr;

extern const DWORD weapon_baseOffset;
//std::vector<DWORD>WPN_2ND_CLASS_OFFSETS = { 0x378, 0x18, 0x1FC };
extern const std::vector<DWORD>WPN_CURRENT_CLASS_OFFSETS;
//std::vector<DWORD>WPN_2ND_CLASS_OFFSETS = { 0x378 };
//std::vector<DWORD>weapon_class_assault_vft = { 0x378, 0x18, 0x1FC ,0x0 };
//std::vector<DWORD>weapon_class_assault_spreadFunc = { 0x378, 0x18, 0x1FC ,0x0, 0x04 };
//std::vector<DWORD>weapon_class_assault_recoilFunc = { 0x378, 0x18, 0x1FC ,0x0, 0x08 };
extern const std::vector<DWORD>WPN_CURRENT_MAG_OFFSETS;
extern const std::vector<DWORD>WPN_CURRENT_WAIT_OFFSETS;
//std::vector<DWORD>WPN_2ND_MAG_OFFSETS = { 0x378, 0x18, 0x1FC, 0x14 };
//std::vector<DWORD>WPN_2ND_WAIT_OFFSETS = { 0x378, 0x18, 0x1FC, 0x18 };
//std::vector<DWORD>WPN_2ND_MAG_OFFSETS = { 0x378, 0x14 };
//std::vector<DWORD>WPN_2ND_WAIT_OFFSETS = { 0x378, 0x18 };
extern const std::vector<DWORD>WPN_CURRENT_INFO_OFFSETS;
extern const std::vector<DWORD>WPN_CURRENT_ISAUTO_OFFSETS;    //auto weapon flag 
extern const std::vector<DWORD>WPN_CURRENT_DELAY_OFFSETS;