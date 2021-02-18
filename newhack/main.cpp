#include "includes.h"
#include "Misc.h"
#include "ModuleGet.h"
#include "structandstuff.h"

ModuleGet modget1;
Misc misc;

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiStyle* style = &ImGui::GetStyle();
	ImGuiIO* io = &ImGui::GetIO();
	io->ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
	ImGui::StyleColorsClassic();
	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(ImColor(127, 115, 177, 70)));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(9, 6, 23, 200)));
	style->WindowRounding = 0;
	style->FrameRounding = 4;
	style->GrabMinSize = 15;
	style->WindowBorderSize = 0;
	style->GrabRounding = 4;
}
bool isopen = true;
bool init = false;
bool join = true;
bool new_window = false;
bool radarHax = false;
bool bhop = false;
bool nothing = false;


int playercheck = 0;
int healthv = 0;
int bhop_timing = 0;  //	DO THIS :D

float flspeed;
float flash = 100;

ImVec2 MAINWINDOW_POS;
ImVec2 NEWWINDOW_SIZE;



void Haxinit()
{

}


long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!init)
	{
		InitImGui(pDevice);
		Haxinit();
		init = true;
	}

	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		isopen = !isopen;
	}

	if (GetAsyncKeyState(VK_HOME) & 1)
	{
		
	}
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (isopen) // insert open
	{


		// START OF MAIN_WINDOW
		
		ImGui::Begin("Aquila", 0,
				  ImGuiWindowFlags_MenuBar
				| ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoCollapse
				| ImGuiWindowFlags_NoTitleBar);

		

		
		ImGui::TextColored(ImVec4(ImColor(152, 126, 222, 255)), "Aquila");
		if (ImGui::IsItemHovered())
		{
			ImGui::SetTooltip("Made By: Under44");
		}

		//	startmenubar
		ImGui::BeginMenuBar();
		if (ImGui::BeginMenu("EXIT"))
		{
			ImGui::EndMenu();
			DllMain(0, 0, 0);
		}
		if (ImGui::BeginMenu("tools"))
		{
			if (ImGui::MenuItem("dev"))
			{
			new_window = !new_window;
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
		//	endmenubar

				ImGui::Checkbox("BHOP", &bhop);
				ImGui::Checkbox("RADAR", &radarHax);
				ImGui::SliderFloat("", &flash, 0.f, 100, "%.2f");
				if (ImGui::IsItemHovered())
				{
					ImGui::SetTooltip("FLASH");
				}

		ImGui::SetWindowSize(ImVec2(400, 260));
		MAINWINDOW_POS = ImGui::GetWindowPos();
		ImGui::End();
		// END OF MAIN_WINDOW

		// mid...

		// START OF NEW_WINDOW/DEV_WINDOW
		if (new_window)
		{
			ImGui::Begin("Developer Tool Window", &new_window, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
			ImGui::SetWindowSize(ImVec2(400, 130));
			ImGui::SetWindowPos(ImVec2(MAINWINDOW_POS.x, MAINWINDOW_POS.y + 262));
			std::string playercheckS = std::to_string(playercheck);
			std::string healthS = std::to_string(healthv);
			std::string FrameS = std::to_string(ImGui::GetIO().Framerate);
			std::string flspeedS = std::to_string(flspeed);
			FrameS.erase(6, 9);
			flspeedS.erase(6, 9);
			ImGui::Text(playercheckS.c_str()); ImGui::SameLine(); ImGui::Text(" | localPlayer");
			ImGui::Text(healthS.c_str()); ImGui::SameLine(); ImGui::Text(" | Health");
			ImGui::Text(flspeedS.c_str()); ImGui::SameLine(); ImGui::Text(" | Velocity");
			ImGui::Separator();
			ImGui::Text(FrameS.c_str()); ImGui::SameLine(); ImGui::Text("UI.FPS");
			ImGui::End();
		}
		// END OF NEW_WINDOW/DEV_WINDOW
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(pDevice);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	window = handle;
	return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool attached = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		{
			kiero::bind(42, (void**)& oEndScene, hkEndScene);
			do
				window = GetProcessWindow();
			while (window == NULL);
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			attached = true;
		}
	} while (!attached);
	return TRUE;
}

DWORD WINAPI heavyThread(LPVOID lpReserved)
{
	// no sleep
	while (playercheck == 0)
	{
		Sleep(500); // buffer
	}
		while (join)
		{
			misc.bhop(bhop);
			misc.noflash(flash);
		}
	return 0;
}

DWORD WINAPI lightThread(LPVOID lpReserved)
{
	// sleep with 50
	while (playercheck == 0)
	{
		Sleep(500); // buffer
	}
	while (join)
	{
		misc.radar(radarHax);
		healthv = modget1.getplayerHealth();
		flspeed = misc.velocity();
		Sleep(50);
	}
	misc.noflash(100); //	go back to default amount.
	return 0;
}

DWORD WINAPI playercheckThread(LPVOID lpReserved)
{
	while (join)
	{
		playercheck = misc.playercheck(playercheck);
		Sleep(50);
	}
	return 0;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, heavyThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, lightThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, playercheckThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		
		join = false;
		kiero::shutdown();
		break;
	}
	return TRUE;
}