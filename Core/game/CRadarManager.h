#pragma once

class CRadarManager {
public:
	CRadarManager();

	enum eBlipType {
		BLIP_NONE,          // 0
		BLIP_CAR,           // 1
		BLIP_CHAR,          // 2
		BLIP_OBJECT,        // 3
		BLIP_COORD,         // 4 - Checkpoint.
		BLIP_CONTACTPOINT,  // 5 - Sphere.
		BLIP_SPOTLIGHT,     // 6
		BLIP_PICKUP,        // 7
	};

	enum eBlipDisplay {
		BLIP_DISPLAY_NEITHER,    // 0
		BLIP_DISPLAY_MARKERONLY, // 1
		BLIP_DISPLAY_BLIPONLY,   // 2
		BLIP_DISPLAY_BOTH        // 3
	};


	//unsigned int __cdecl CRadar::SetEntityBlip(eBlipType type, int entityHandle, int a3, eBlipDisplay display)
	int SetBlipToPed(CPed *ped);
	int SetBlipToVeh(CVehicle *veh);
	int AddCustomBlip(CVector pos, unsigned int SpriteID);
	void ChangeBlipPos(int blip,CVector pos);
	int AddBlip(CVector pos, int scale, int sprite, int color);
};