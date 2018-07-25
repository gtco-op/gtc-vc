/*
    Grand Theft CO-OP: Vice City
    -----------------------------
    FILE: CRadarManager.cpp
    DESCRIPTION: Manages the radar blips in game.
    AUTHOR(S): Zurix

    License: GPL v2
    Copyrights (c) 2017-2018 GTC Team
*/
#include "main.h"
CRadarManager::CRadarManager() {};
int CRadarManager::SetBlipToPed(CPed *ped) {
	//Creates Blip : CRadar::SetCoorsBlip
	int CoordBlip = CallAndReturn<int, 0x4C3C80, unsigned int, CVector, unsigned int, unsigned int>(4, ped->GetPosition(), 0, 3);
	//Sets the Scale: CRadar::ChangeBlipScale
	plugin::Call<0x4C3840, int, int>(CoordBlip, 2);
	//Sets the color: CRadar::ChangeBlipColour
	plugin::Call<0x4C3930, int, unsigned int>(CoordBlip, 3);

	return CoordBlip;
}
int CRadarManager::SetBlipToVeh(CVehicle *veh) {

	int CoordBlip = CallAndReturn<int, 0x4C3C80, unsigned int, CVector, unsigned int, unsigned int>(4, veh->GetPosition(), 0, 3);
	// you dont have to set a scale it will be a small one as it supposed to be for vehicles
	plugin::Call<0x4C3930, int, unsigned int>(CoordBlip, 3);
	return CoordBlip;
}

int CRadarManager::AddCustomBlip(CVector pos, unsigned int SpriteID) {
	int CoordBlip = CallAndReturn<int, 0x4C3C80, unsigned int, CVector, unsigned int, unsigned int>(4, pos, 0, 3);
	plugin::Call<0x4C3780, int, int>(CoordBlip, SpriteID);
	return CoordBlip;
}

void CRadarManager::ChangeBlipPos(int BlipID, CVector pos) {
	int BlipIndex = 28 * BlipID / 2;

	float * vecBlipPos_X = (float*)0x7D7D44;
	float * vecBlipPos_Y = (float*)0x7D7D48;
	float *	vecBlipPos_Z = (float*)0x7D7D4C;

	vecBlipPos_X[BlipIndex] = pos.x;
	vecBlipPos_Y[BlipIndex] = pos.y;
	vecBlipPos_Z[BlipIndex] = pos.z;
}
int CRadarManager::AddBlip(CVector pos, int scale, int sprite, int color) {
	int CoordBlip = CallAndReturn<int, 0x4C3C80, unsigned int, CVector, unsigned int, unsigned int>(4, pos, 0, 3);
	plugin::Call<0x4C3840, int, int>(CoordBlip, scale);
	plugin::Call<0x4C3780, int, int>(CoordBlip, sprite);
	plugin::Call<0x4C3930, int, unsigned int>(CoordBlip, color);
}

