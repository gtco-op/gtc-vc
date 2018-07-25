#pragma once



class CMissionManager {
public:
    void MountMainSCM();
    void StartMission(unsigned int iMissionID);
    void FailCurrentMission();
};