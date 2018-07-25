#pragma once

class CPedManager{
public:
	CPedManager();
	

	CPed *Create(int modelid, const CVector& position, bool wander = false);
    void Destroy(CPed *ped);
};