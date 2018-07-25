/*
    Grand Theft CO-OP: Vice City
    -----------------------------
    FILE: CPickupManager
    DESCRIPTION: Manages the pickups in game.
    AUTHOR(S): Zurix

    License: GPL v2
    Copyrights (c) 2017-2018 GTC Team
*/
#include "main.h"

int CPickupManager::AddPickup(CVector pos, ePickupType type, unsigned int model) {
	//int __cdecl CPickups::GenerateNewOne(float x, float y, float z, __int16 modelId, char pickupType, int ammo, __int16 moneyPerDay, char isEmpty, const char *message)
	//int __usercall CPickups::GenerateNewOne@<eax>(signed int i@<ebx>, float a2, float a3, float a4, __int16 mdoelid, char type, int ammo, __int16 moneyperday, char isempty, int a10)
	if (gModelManager->LoadModel(model))
	{
		int pk;
		pk = CPickups::GenerateNewOne(pos, model, type, 0, 0, 1, 0);

		return pk;

	}
	return 0;
	
};

void CPickupManager::RemovePickup(int pickHandle) {
	CPickups::RemovePickUp(pickHandle);
}