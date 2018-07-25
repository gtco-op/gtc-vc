/*
    Grand Theft CO-OP: Vice City
    -----------------------------   
    FILE: CCompanionNetworking.cpp
    DESCRIPTION: Networking of game hoster.
    AUTHOR(S): Zurix

    License: GPL v2
    Copyrights (c) 2017-2018 GTC Team
*/

#define LIBRG_DEBUG
#define LIBRG_IMPLEMENTATION
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "CHostNetworking.h"
#include "vendor/librg/librg.h"
#include "main.h"


HANDLE ThreadHandle;
librg_ctx_t ctx = { 0 };
bool server_running = false;
librg_entity_t* companion = nullptr;
CPed * comp_ped = nullptr;

static int m_port;


#pragma region Events
    void  on_connection_request(librg_event_t *event) {
        printf("[CHostNetowrking] Companion is Requesting to connect IP:  %d\n", event->peer->address);

    }
    void on_connection_accept(librg_event_t *event) {
        printf("[CHostNetworking] The Companion Connected.");
        companion = event->entity;
        librg_entity_control_set(event->ctx, event->entity->id, event->entity->client_peer);
    }
    void on_entity_create(librg_event_t*event) {
        comp_ped = gPedManager->Create(10, FindPlayerCoors(), false);

    }
    void on_entity_update(librg_event_t *event) {

    }
    void on_disconnection(librg_event_t *event) {
        companion == nullptr;
        gPedManager->Destroy(comp_ped);
    }
#pragma endregion

    void ServerThread() {

        //Initalizing Server
        printf("[CHostNetworking] Initalizing Server Data..\n");
        ctx.world_size = zplm_vec3(5000.0f, 5000.0f, 5000.0f);
        ctx.mode = LIBRG_MODE_SERVER;
        ctx.tick_delay = 32;
        ctx.max_connections = 1;

        librg_init(&ctx);
        printf("[CHostNetworking] Server Initalized");

        //Registering Events
        librg_event_add(&ctx, LIBRG_CONNECTION_REQUEST, on_connection_request);
        librg_event_add(&ctx, LIBRG_CONNECTION_ACCEPT, on_connection_accept);
        librg_event_add(&ctx, LIBRG_CONNECTION_DISCONNECT, on_disconnection);
        librg_event_add(&ctx, LIBRG_ENTITY_UPDATE, on_entity_update);
        librg_event_add(&ctx, LIBRG_ENTITY_CREATE, on_entity_create);

        //Starting Server
        librg_address_t address = { m_port };
        librg_network_start(&ctx, address);
        printf("[CHostNetworking] Server started at %d\n", address.port);


        while (server_running) {
            if (companion != nullptr) {
                PlayerSyncData *plr = (PlayerSyncData*)companion->user_data;
                printf("Reciving Companion Position: X: %.f Y: &.f Z: %.f", plr->Position.x, plr->Position.y, plr->Position.z);

            }

        }

    }





CHostNetworking::CHostNetworking(int port)
{
    CHud::SetHelpMessage(L"Welcome to ~g~ GTC:VC ~h~ your game is hosted now, ~t~ Invite you friends and have fun! :D", 0, 0, 0);
    printf("[CHostNetworking] Host Initalized\n");
    m_port = port;
    ThreadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&ServerThread, 0, 0, 0);
}



CHostNetworking::~CHostNetworking()
{
    printf("[CHostNetworking] Closing down/n");
    TerminateThread(ThreadHandle, 0);
}


