#pragma once

class CPickupManager {
public:

	int AddPickup(CVector pos, ePickupType type, unsigned int model);
	void RemovePickup(int pickHandle);
};
