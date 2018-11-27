/*
    Grand Theft CO-OP: Vice City
    -----------------------------
    FILE: Core.cpp
    DESCRIPTION: Entrypoint of the DLL.
    AUTHOR(S):  Zurix
				LemonHaze420

    License: GPL v2
    Copyrights (c) 2017-2018 GTC Team
*/
#include "main.h"
#include "ImGuiImplementation.h"

using namespace plugin;

CModelManager		*gModelManager		= nullptr;
CVehicleManager		*gVehicleManager	= nullptr;
CPedManager			*gPedManager		= nullptr;
CPlayerPedManager	*gPlayerPedManager	= nullptr;
CRadarManager		*gRadarManager		= nullptr;
CPickupManager		*gPickupManager		= nullptr;
CMissionManager     *gMissionManager	= nullptr;
CGamePatches        *gGamePatches		= nullptr;

CCompanionNetworking *gCompanion		= nullptr;
CHostNetworking		 *gHost				= nullptr;

ImGuiImplementation  *gImGui			= nullptr;

class Core {
public:
    Core() {

#ifdef GTC_DEBUG
		// Disable re-initialization of DirectInput mouse device by the game
		MakeNop(0x49908B, 5);
		MakeNop(0x498F92, 5);
		MakeNop(0x499014, 5);

		MakeNop(0x49908B + 0x7, 5);
		MakeNop(0x498F92 + 0x7, 5);
		MakeNop(0x499014 + 0x7, 5);
#endif

		gImGui				= new ImGuiImplementation();

		gGamePatches		= new CGamePatches();

		gModelManager		= new CModelManager();
		gVehicleManager		= new CVehicleManager();
		gPedManager			= new CPedManager();
		gPlayerPedManager	= new CPlayerPedManager();
		gRadarManager		= new CRadarManager();
		gPickupManager		= new CPickupManager();
		gMissionManager		= new CMissionManager();
		
#ifdef GTC_DEBUG
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		GTC_LOG("[INFO] Debug console allocated.\n");
#endif

        Events::initRwEvent += []        {
			gImGui->Shutdown();
			gImGui->Initialize();
			GTC_LOG("[INFO] initRwEvent occurred.\n");
        };
        Events::d3dResetEvent += []        {
			gImGui->Initialize();
			GTC_LOG("[INFO] d3dResetEvent occurred.\n");
        };
		Events::d3dLostEvent += []		{
			gImGui->Initialize();
			GTC_LOG("[INFO] d3dLostEvent occurred.\n");
		};
        Events::drawingEvent += [] {
			gImGui->Draw();
        };
    }
} core;
