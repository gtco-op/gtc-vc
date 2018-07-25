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


using namespace plugin;

CModelManager		*gModelManager = nullptr;
CVehicleManager		*gVehicleManager = nullptr;
CPedManager			*gPedManager = nullptr;
CPlayerPedManager	*gPlayerPedManager = nullptr;
CRadarManager		*gRadarManager = nullptr;
CPickupManager		*gPickupManager = nullptr;
CMissionManager      *gMissionManager = nullptr;
CGamePatches         *gGamePatches = nullptr;

CCompanionNetworking *gCompanion = nullptr;
CHostNetworking *gHost = nullptr;

static bool JustABool = false;




class Core {
public:

    Core() {


        //Allocating Console.
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        //freopen("CONIN$", "r", stdin);

        //Checking coop.ini

        INIReader reader = INIReader("coop.ini");
        if (reader.ParseError() < 0) {
            printf("Cant Load coop.ini\n");
        }
        else {
            printf("coop.ini found\n");
            if (reader.Get("GAME", "Type", "sp") != "sp"){
                if (reader.Get("GAME", "Type", "sp") == "host") {
                    static int port = reader.GetInteger("HOST", "port", 23245);
                    Events::gameProcessEvent += [] {
                        if (!JustABool) {
                            JustABool = true;
                            gHost = new CHostNetworking(port);
                        }
                    };

                }
                else if (reader.Get("GAME", "Type", "sp") == "companion") {
                    const char* ip = reader.Get("COMPANION", "IP", "127.0.0.1").c_str();
                    int port = reader.GetInteger("COMPANION", "port", 23245);
                    gCompanion = new CCompanionNetworking(ip, port);

                }
                else if (reader.Get("GAME", "Type", "sp") == "sp") {
                    //Game runs in singleplayer normally
                }
                else {
                    printf("The INI File is corrupt, please report that to GTC Developers.\n");
                    MessageBoxA(0, TEXT("The INI file is in corrupted format, GTC will not be launched"), TEXT("Error"), 0);
                }
            }
        }


        
        Events::drawingEvent += [] {
            gamefont::Print("Grand Theft CO-OP: Vice City 0.1 Alpha", 25.0f, 25.0f, 0, 0.9f, 0.9f, color::White, gamefont::AlignLeft); 
        };

        Events::gameProcessEvent += [] {
            if (!JustABool) {
                JustABool = true;
            }
        };


    }
} core;
