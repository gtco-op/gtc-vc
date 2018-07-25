/*
    Grand Theft CO-OP: Vice City
    -----------------------------
    FILE: CVehicleManager.cpp
    DESCRIPTION: Manages the vehicle entities in game.
    AUTHOR(S): Vektor

    License: GPL v2
    Copyrights (c) 2017-2018 GTC Team
*/

#include "main.h"

CVehicleManager::CVehicleManager() {}

CVehicle *CVehicleManager::Create(int modelid, const CVector& position)
{
	if (gModelManager->LoadModel(modelid))
	{
		CVehicle *vehicle = nullptr;

		switch (this->GetVehicleType(modelid))
		{
		case VEHICLE_HELI:
			vehicle = new CHeli(modelid, 1);
			break;
		case VEHICLE_PLANE:
			vehicle = new CPlane(modelid, 1);
			break;
		case VEHICLE_BIKE:
			vehicle = new CBike(modelid, 1);
			break;
		case VEHICLE_BOAT:
			vehicle = new CBoat(modelid, 1);
		 break;
		default:
			vehicle = new CAutomobile(modelid, 1);
			break;
		}
		if (vehicle) 
		{
			vehicle->m_placement.pos = position;
			vehicle->m_placement.SetOrientation(0.0f, 0.0f, 0.0f);
			vehicle->m_nLockStatus = CARLOCK_UNLOCKED;
			//vehicle->m_nState = 4;
			CWorld::Add(vehicle);
			return vehicle;
		}
	}
	return nullptr;
}

eVehicleType CVehicleManager::GetVehicleType(int modelid)
{
	return (eVehicleType)reinterpret_cast<CVehicleModelInfo *>(CModelInfo::ms_modelInfoPtrs[modelid])->m_nVehicleType;
}