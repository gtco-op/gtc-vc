#pragma once
class CVehicleManager
{
public:
	CVehicleManager();	

	CVehicle *Create(int modelid, const CVector& position);
	eVehicleType GetVehicleType(int modelid);
};