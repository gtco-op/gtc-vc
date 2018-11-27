#include "main.h"

char ImGuiImplementation::serverHostname[64];
int ImGuiImplementation::serverPort;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDPROC orig_wndproc;

bool wndprocHooked = false;

bool IsWindowActive()
{
	return (GetActiveWindow() == RsGlobal.ps->window ? true : false);
}

void ImGuiImplementation::Initialize()
{
    if (!m_bInitialized)
    {
		if (!wndprocHooked)
		{
			orig_wndproc = (WNDPROC)(UINT_PTR)SetWindowLong(RsGlobal.ps->window, GWL_WNDPROC, (LONG)(UINT_PTR)WndProc);
			ImmAssociateContext(RsGlobal.ps->window, 0);
			
			wndprocHooked = true;
		}

		// Setup Dear ImGui binding
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  
		io.DisplaySize = { screen::GetScreenWidth(), screen::GetScreenHeight() };
		io.IniFilename = NULL;
		io.LogFilename = NULL;
		
        ImGui_ImplWin32_Init(RsGlobal.ps->window);
        ImGui_ImplDX9_Init(reinterpret_cast<IDirect3DDevice9*>(RwD3D9GetCurrentD3DDevice()));

        ImGui::StyleColorsDark();

        m_bInitialized = true;
    }
}
void ImGuiImplementation::DrawMenu() {
    if (m_bInitialized) {
        ImGui::SetNextWindowSize(ImVec2(250,300));

        ImGui::Begin("Grand Theft CO-OP: Vice City", &m_bInitialized);
        
		ImGui::InputText("Server:", this->serverHostname, IM_ARRAYSIZE(this->serverHostname));
		ImGui::InputInt("Server Port:", &this->serverPort);

		if (ImGui::Button("Join Game")) {			
			//gCompanion->JoinGame(this->serverHostname.c_str(), this->serverPort); 
		}
		if (ImGui::Button("Host Game")) {
			//gHost->InitServer();
		}
		ImGui::End();
    }
}
void ImGuiImplementation::Draw()
{
    if (m_bInitialized) {
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		if(m_bDrawConnectMenu)
			DrawMenu();

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
void EnableMouseInput()
{
	//Enable CPad:UpdateMouse
	MemCpy((void*)0x4AD820, "\x53", 1);
	//CControllerConfigManager::AffectPadFromKeyBoard restore
	MemCpy((void*)0x4AB6E6, "\xE8\x45\xCE\x16\x00", 5);
	//CControllerConfigManager::AffectPadFromMouse restore
	MemCpy((void*)0x4AB6F0, "\xE8\x9B\xCD\x16\x00", 5);
}
void DisableMouseInput()
{
	//Disable CPad:UpdateMouse
	MakeRet(0x4AD820);
	//CControllerConfigManager::AffectPadFromKeyBoard nop
	MakeNop(0x4AB6E6, 5);
	//CControllerConfigManager::AffectPadFromMouse nop
	MakeNop(0x4AB6F0, 5);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (gImGui->m_bInitialized && gImGui->m_bDrawConnectMenu)
	{
		DisableMouseInput();

		((IDirect3DDevice9 *)RwD3D9GetCurrentD3DDevice())->ShowCursor(true);
		ImGui::GetIO().MouseDrawCursor = true;
	}
	else if(gImGui->m_bInitialized && !gImGui->m_bDrawConnectMenu)
	{
		EnableMouseInput();

		((IDirect3DDevice9 *)RwD3D9GetCurrentD3DDevice())->ShowCursor(false);
		ImGui::GetIO().MouseDrawCursor = false;
	}

	switch (msg)
	{
	case WM_MOUSEMOVE:
		POINT ul, lr;
		RECT rect;
		GetClientRect(hWnd, &rect);

		ul.x = rect.left;
		ul.y = rect.top;
		lr.x = rect.right;
		lr.y = rect.bottom;

		MapWindowPoints(hWnd, nullptr, &ul, 1);
		MapWindowPoints(hWnd, nullptr, &lr, 1);

		rect.left = ul.x;
		rect.top = ul.y;
		rect.right = lr.x;
		rect.bottom = lr.y;

		if (IsWindowActive())
			ClipCursor(&rect);
		break;
	case WM_MOUSEHOVER:
		break;
	case WM_KEYDOWN:
		int vkey = (int)wParam;

		if (gImGui->m_bDrawConnectMenu && (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard))
			return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

		if (vkey == VK_ESCAPE)		{
			plugin::Call<0x602EE0, int, void*>(30, nullptr); // RsEventHandler
			return 0;
		}
		else if (vkey == VK_F9)
		{
			gImGui->m_bDrawConnectMenu = !gImGui->m_bDrawConnectMenu;
			return 0;
		}
		break;
	}

	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) return 0;

	return CallWindowProc(orig_wndproc, hWnd, msg, wParam, lParam);
}