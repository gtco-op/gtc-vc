#pragma once
class CPlayerPedManager 
{
public:
	CPlayerPedManager();

	CPlayerPed *Create(int modelid, const CVector& position);
	int GetFreePlayerSlot();
	int GetPlayerPedSlot(CPlayerPed * player);

	bool playerSlots[500];
	CPlayerPed* players[500];
};