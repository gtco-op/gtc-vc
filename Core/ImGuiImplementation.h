#pragma once
#include "main.h"

class ImGuiImplementation
{
public:


    void Initialize(HWND hwnd, IDirect3DDevice9* device);
    void Draw();
    void Shutdown();
    void DrawConnectMenu();
    bool m_bInitialized = false;
    char* IPBuf;
    int* PortBuf;
};

