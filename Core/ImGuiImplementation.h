#pragma once

class ImGuiImplementation
{
public:
    void Initialize();
    void Draw();
    void Shutdown();
    void DrawMenu();

    bool m_bInitialized = false;
	bool m_bDrawConnectMenu = false;

	static char serverHostname[64];
	static int serverPort;
};

