#include "main.h"

CPad			localPlayerKeys;
CMatrix			cameraAimMatrix;
BYTE			localPlayerCameraMode;
CAMERA_AIM		localPlayerLookFrontX;
BYTE			internalPlayerID = 0;
CVehicle *		_pVehicle;
static bool		scriptProcessed = false;

char(__thiscall* original_CPlayerPed__ProcessControl)(CPlayerPed*);
char __fastcall CPlayerPed__ProcessControl_Hook(CPlayerPed * This, DWORD _EDX)
{
	if (This != FindPlayerPed())
	{
		int currentPlayerID = gPlayerPedManager->GetPlayerPedSlot(This);

		if (currentPlayerID == -1)return 0;

		// set player to focus
		CWorld::PlayerInFocus = currentPlayerID;

		// save local player's keys
		localPlayerKeys = *CPad::GetPad(0);

		// set remote player's keys
		*CPad::GetPad(0) = *new CPad();

		// save the internal cammode.
		localPlayerCameraMode = TheCamera.Cams[TheCamera.ActiveCam].Mode;

		// onfoot mouse looking mode.
		TheCamera.Cams[TheCamera.ActiveCam].Mode = 4;

		// save local player's aim
		localPlayerLookFrontX = *(CAMERA_AIM*)&TheCamera.Cams[TheCamera.ActiveCam].Front;

		// set remote player's aim
		*(CMatrix*)&TheCamera.Cams[TheCamera.ActiveCam].Front = cameraAimMatrix;

		// call the internal CPlayerPed[]::Process
		original_CPlayerPed__ProcessControl(This);

		// restore the camera mode.
		TheCamera.Cams[TheCamera.ActiveCam].Mode = localPlayerCameraMode;

		// restore local player keys
		*CPad::GetPad(0) = localPlayerKeys;

		// restore the local player's id
		CWorld::PlayerInFocus = 0;

		//restore local player's aim
		*(CAMERA_AIM*)&TheCamera.Cams[TheCamera.ActiveCam].Front = localPlayerLookFrontX;
		return 0;
	}
	return original_CPlayerPed__ProcessControl(This);
}

CPlayerPedManager::CPlayerPedManager() 
{

	for (int i = 0; i < 500; i++)
	{
		this->playerSlots[i] = false;
	}
	this->playerSlots[0] = true; //0 is always local player
	//this->playerSlots[1] = true; //1 is always the second player, coop leftover

	original_CPlayerPed__ProcessControl = (char(__thiscall*)(CPlayerPed*))DetourFunction((PBYTE)0x537270, (PBYTE)CPlayerPed__ProcessControl_Hook);
}

CPlayerPed *CPlayerPedManager::Create(int modelid, const CVector& position)
{

	gModelManager->LoadModel(modelid);
	int playerid = this->GetFreePlayerSlot(); 
	CPlayerPed *player;
	player->m_nPedFlags = FindPlayerPed()->m_nPedFlags;
	//player->m_dwPedType = ePedType::PEDTYPE_PLAYER2;
	printf("[CPlayerPedManager]Create - %d\n", playerid);
	CWorld::Add(player);
	player->SetModelIndex(modelid);
	player->m_placement.SetOrientation(0.0f, 0.0f, 0.0f);
	player->Teleport(position);


	this->playerSlots[playerid] = true;
	this->players[playerid] = player;


	return player;
}

int CPlayerPedManager::GetFreePlayerSlot()
{
	for (int i = 1; i < 500; i++)
	{
		if (!this->playerSlots[i])return i;
	}
	return -1;
}

int CPlayerPedManager::GetPlayerPedSlot(CPlayerPed * player)
{
	for (int i = 0; i < 500; i++)
	{
		if (this->players[i] == player)return i;
	}
	return -1;
}