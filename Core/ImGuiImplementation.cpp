#include "ImGuiImplementation.h"




static D3DPRESENT_PARAMETERS    g_d3dpp;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void ImGuiImplementation::Initialize(HWND hwnd, IDirect3DDevice9* device)
{
    if (!m_bInitialized)
    {
        // Setup Dear ImGui binding
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX9_Init(device);

        // Setup style
        ImGui::StyleColorsDark();

        m_bInitialized = true;
    }
}
void ImGuiImplementation::DrawConnectMenu() {
    if (m_bInitialized) {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPosCenter();

        ImGui::Begin("Grand Theft CO-OP: Vice City", 0);
        ImGui::Button("Host Game");
        ImGui::InputText("IP", this->IPBuf, 256);
        ImGui::InputInt("Port", this->PortBuf);
        if (ImGui::Button("Join Game")) { gCompanion->JoinGame(this->IPBuf, *this->PortBuf); }

        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
}
void ImGuiImplementation::Draw()
{
    if (m_bInitialized) {
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::EndFrame();

        ImGui::Render();

        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }
}
void ImGuiImplementation::Shutdown()
{
    if (m_bInitialized) {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

        m_bInitialized = false;
    }
}