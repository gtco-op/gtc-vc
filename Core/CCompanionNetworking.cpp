/*
    Grand Theft CO-OP: Vice City
    -----------------------------
    FILE: CCompanionNetworking.cpp
    DESCRIPTION: Networking of the Companion.
    AUTHOR(S): Zurix

    License: GPL v2
    Copyrights (c) 2017-2018 GTC Team
*/

#pragma once
#include "CCompanionNetworking.h"
#include "vendor/librg/librg.h"
#include "main.h"

HANDLE thrd;
librg_ctx_t cli_ctx = { 0 };
static const char* m_ip; static int m_port;

#pragma region Events
void  cli_on_connection_request(librg_event_t *event) {
    printf("[CCompanionNetworking] Connecting...\n");
}
void cli_on_connection_accept(librg_event_t *event) {
    printf("[CCompanionNetworking] Connection Accepted. \n");
}
void cli_on_connection_refuse(librg_event_t *event) {
    //later
}
void cli_on_entity_create(librg_event_t*event) {
    
}
void cli_on_entity_update(librg_event_t *event) {

}
void cli_on_disconnection(librg_event_t *event) {

}
#pragma endregion

void CompanionThread() {
    // Initalizing Companion
    cli_ctx.tick_delay = 45;
    cli_ctx.mode = LIBRG_MODE_CLIENT;
    librg_init(&cli_ctx);
    printf("[CCompanionNetworking] Initalized \n");
    
    //Registering Events
    librg_event_add(&cli_ctx, LIBRG_CONNECTION_REQUEST, cli_on_connection_request);
    librg_event_add(&cli_ctx, LIBRG_CONNECTION_ACCEPT, cli_on_connection_accept);
    librg_event_add(&cli_ctx, LIBRG_CONNECTION_DISCONNECT, cli_on_disconnection);
    librg_event_add(&cli_ctx, LIBRG_ENTITY_UPDATE, cli_on_entity_update);
    librg_event_add(&cli_ctx, LIBRG_ENTITY_CREATE, cli_on_entity_create);
    
    //Connecting
    librg_address_t address = { m_port, (char*)m_ip };
    librg_network_start(&cli_ctx, address);
    printf("[CompanionNetworking] Connected to %s:%d", m_ip, m_port);
    CHud::SetHelpMessage("Connecting :)", 0,0,0);

    bool client_running = true;
    while (client_running) {
        librg_tick(&cli_ctx);
        zpl_sleep_ms(1);
    }

    librg_network_stop(&cli_ctx);
    librg_free(&cli_ctx);
}
void CCompanionNetworking::JoinGame(const char* IP, int port)
{
    gGamePatches->DestructingMenu();
    printf("[CCompanionNetworking] Initalizing Companion Thread");
    m_ip = IP; m_port = port;

    thrd = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&CompanionThread, 0,0,0);
}

CCompanionNetworking::~CCompanionNetworking()
{   
    printf("[CCompanionNetworking]Desturcting...");
    librg_network_stop(&cli_ctx);
    librg_free(&cli_ctx);
}
