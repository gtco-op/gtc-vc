/*
    Grand Theft CO-OP: Vice City
    -----------------------------
    FILE: CMissionManager.cpp
    DESCRIPTION: Manages the missions in game.
    AUTHOR(S): LemonHaze
               Zolika1351

    License: GPL v2
    Copyrights (c) 2017-2018 GTC Team
*/
#include "main.h"
void CMissionManager::MountMainSCM() {
    //The First Mission will be loaded
    
    // Load the SCM Script (restore)..
    MemCpy(0x4506D6, "\xE8\x55\xD9\x03\x00", 5);

    // Restore the CRunningScript::Process() hook..
    MemCpy((void*)0x450245, "\xE8\x26\xFB\xFF\xFF", 5);

    // Call CTheScripts::Init(void)
    Call(0x450330);
    // Call CTheScripts::StartNewScript(int)
    CRunningScript* rs = CallAndReturn<CRunningScript*, 0x450270, int>(0);
    
}
void CMissionManager::StartMission(unsigned int iMissionID) {
    Command<Commands::FAIL_CURRENT_MISSION>();
    Command<Commands::LOAD_AND_LAUNCH_MISSION_INTERNAL>(iMissionID);
}
void CMissionManager::FailCurrentMission() {
    Command<Commands::FAIL_CURRENT_MISSION>();
}