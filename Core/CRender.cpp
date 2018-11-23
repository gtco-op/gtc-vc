
#include "main.h"
#include "rwd3d9.h"


bool gui_focus = false;
bool gui_initialized = false;

HWND hwnd = ::FindWindow(NULL, "GTA: Vice City");

void Draw() {
    if (gui_initialized)
    {
        printf("Drawing...\n");
        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();
        ImGui::Begin("Test ;-;", (bool*)1, 0);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
        ImGui::EndFrame();

        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }

}
CRender::CRender() {

    printf("Setting  ImGUI...\n");
    Events::drawingEvent += []
    {
            if (!gui_initialized) {   
                if (!hwnd) {
                    if (!RwD3D9GetCurrentD3DDevice()) {
                    }
                }
                        printf("Initalized\n");
                        IMGUI_CHECKVERSION();
                        ImGui::CreateContext();
                        ImGuiIO& io = ImGui::GetIO();


                        ImGui_ImplWin32_Init((void*)hwnd);

                        ImGui_ImplDX9_Init(reinterpret_cast<IDirect3DDevice9 *>(RwD3D9GetCurrentD3DDevice()));
                        ImGui::StyleColorsLight();

                        gui_initialized = true;
                        gui_focus = false;
 

            }
    };    

    Events::drawingEvent += []
    {
        Draw();
    };

    Events::shutdownRwEvent += []
    {
        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    };
}

CRender::~CRender() {

}