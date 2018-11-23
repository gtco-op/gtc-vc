/*
    Grand Theft CO-OP: Vice City
    -----------------------------
    FILE: Core.cpp
    DESCRIPTION: Main Entry point of the executable.
    AUTHOR(S): Zurix

    License: GPL v2
    Copyrights (c) 2017-2018 GTC Team
*/
#include "main.h"
#include "ImGuiImplementation.h"
//#define GTC_DEBUG

using namespace plugin;

CModelManager		*gModelManager = nullptr;
CVehicleManager		*gVehicleManager = nullptr;
CPedManager			*gPedManager = nullptr;
CPlayerPedManager	*gPlayerPedManager = nullptr;
CRadarManager		*gRadarManager = nullptr;
CPickupManager		*gPickupManager = nullptr;
CMissionManager      *gMissionManager = nullptr;
CGamePatches         *gGamePatches = new CGamePatches();

CCompanionNetworking *gCompanion = nullptr;
CHostNetworking *gHost = nullptr;


static bool Once = true;

ImGuiImplementation imgui;

HWND hwnd = NULL;


void thr()
{
    printf("Initializing... \n");

    while (hwnd == NULL)
    {
        hwnd = ::FindWindow(NULL, "GTA: Vice City");
        Sleep(1);
    }
    printf("done.\n");
}

class Core {
public:
    Core() {
#ifdef GTC_DEBUG

        //Allocating Console.
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        //freopen("CONIN$", "r", stdin);
#endif


        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&thr, NULL, 0, NULL);


        Events::initRwEvent += []
        {
            imgui.Initialize(hwnd, (IDirect3DDevice9*)RwD3D9GetCurrentD3DDevice());
        };

        Events::d3dResetEvent += []
        {
            imgui.Shutdown();
            imgui.Initialize(hwnd, (IDirect3DDevice9*)RwD3D9GetCurrentD3DDevice());
        };

        Events::drawingEvent += [] {
            //gamefont::Print("Mike 200 {", 20.0f, 100.0f, 2, 0.9f, 0.9f,color::HotPink, gamefont::AlignLeft); 
            imgui.Draw();
        };
 
        Events::gameProcessEvent += [] {        
            
            if (Once) {
                CHud::SetHelpMessage(L"~h~Don't forget to play ~t~CO-OP Campaign ~h~ with your fiends, Press ~g~ F9", 0,0,0);
            }

        };
        
    }
} core;
