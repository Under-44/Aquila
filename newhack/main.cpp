#include <Windows.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
#include "OffSets.h"
#include "kiero/kiero.h"
#include "kiero/minhook/include/MinHook.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "imguicustom.h"
#define WINDOW_NAME "Aquila"
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
#include "Misc.h"
#include "ModuleGet.h"


ModuleGet modget1;
Misc misc;

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

EndScene oEndScene = NULL;
WNDPROC oWndProc;
static HWND window = NULL;
imguicustom imcustom;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiStyle* style = &ImGui::GetStyle();
	ImGuiIO* io = &ImGui::GetIO();
	io->ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
	imcustom.defaultstyle();
	/*AllocConsole();
	FILE* fDummy;
	freopen_s(&fDummy, "CONIN$", "r", stdin);
	freopen_s(&fDummy, "CONOUT$", "w", stderr);
	freopen_s(&fDummy, "CONOUT$", "w", stdout);
	printf("Debugging Window:\n");*/ // this is a debug console
}
bool isopen = true;
bool init = false;
bool join = true;
bool new_window = false;
bool radarHax = false;
bool bhop = false;
bool nothing = false;
bool glow = false;
bool fullBloomlocal = false;
bool fullBloomenemy = false;
bool velocityglow_enemy = false;
bool velocityglow_local = false;



uintptr_t playercheck;
int healthv = 0;
int bhop_timing = 0;  //	DO THIS :D
int window_no_move = 4;
int player_dormant;

float flspeed;
float flash = 100;
float flash255;


AquilaColor TeamGlow = { 0.f, 1.f, 0.f, 100.f };  // red, green, blue, alpha
AquilaColor EnemyGlow = { 1.f, 0.f, 0.f, 100.f }; // red, green, blue, alpha


int windowHeight, windowWidth;

ImVec2 MAINWINDOW_POS;
ImVec2 NEWWINDOW_SIZE;


long __stdcall hkEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!init)
	{
		InitImGui(pDevice);
		
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

	flash255 = (flash * static_cast<float>(2.55)); // testing d3d9


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
		if (ImGui::BeginMenu("tools"))
		{
			if (ImGui::MenuItem("dev"))
			{
			new_window = !new_window;
			window_no_move = 4;
			ImGui::SetNextWindowPos(ImVec2(MAINWINDOW_POS.x, MAINWINDOW_POS.y + 262));
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
		//	endmenubar
				ImGui::Checkbox("BHOP", &bhop);
				ImGui::Checkbox("RADAR", &radarHax);
				ImGui::Checkbox("GLOW", &glow);
				ImGui::SliderFloat("", &flash, 0.f, 100, "%.2f");
				if (ImGui::IsItemActive())
				{
					ImGui::SetTooltip("FLASH");
					D3DRECT rect = { 25, 25, 100, 100 };
					pDevice->Clear(1, &rect, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, static_cast<int>(flash255), 0), 0, 0);
				}
				if (ImGui::Button("UNHOOK"))
				{
					DllMain(0, 0, 0);
				}

		ImGui::SetWindowSize(ImVec2(400, 260));
		MAINWINDOW_POS = ImGui::GetWindowPos();
		ImGui::End();
		// END OF MAIN_WINDOW

		// mid...

		// START OF NEW_WINDOW/DEV_WINDOW
		if (new_window)
		{
			ImGui::Begin("Developer Tool Window", &new_window, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | window_no_move);
			ImGui::SetWindowSize(ImVec2(400, 130));
			if (window_no_move == 4)
			{
				ImGui::SetWindowPos(ImVec2(MAINWINDOW_POS.x, MAINWINDOW_POS.y + 262));
			}
			std::string playercheckS = std::to_string(playercheck);
			std::string healthS = std::to_string(healthv);
			std::string FrameS = std::to_string(ImGui::GetIO().Framerate);
			std::string flspeedS = std::to_string(flspeed);
			std::string playerdormantS = std::to_string(player_dormant);
			FrameS.erase(6, 9);
			flspeedS.erase(6, 9);
			ImGui::Text(playercheckS.c_str()); ImGui::SameLine(); ImGui::Text(" | localPlayer");
			ImGui::Text(healthS.c_str()); ImGui::SameLine(); ImGui::Text(" | Health");
			ImGui::Text(flspeedS.c_str()); ImGui::SameLine(); ImGui::Text(" | Velocity");
			ImGui::Text(playerdormantS.c_str()); ImGui::SameLine(); ImGui::Text(" | playerdormant");
			ImGui::Separator();
			ImGui::Text(FrameS.c_str()); ImGui::SameLine(); ImGui::Text("UI.FPS");
			ImGui::Separator();
			if (window_no_move > 0)
			{
				if (ImGui::Button("Seperate"))
				{
					window_no_move = 0;
				}
			}
			ImGui::End();
		}
		// END OF NEW_WINDOW/DEV_WINDOW
		
		//start of glow
		if (glow) // make this window closable, so the menu doesnt look so huge.
		{
			ImGui::Begin("Glow", 0,
				ImGuiWindowFlags_NoResize
				| ImGuiWindowFlags_NoCollapse
				| ImGuiWindowFlags_NoTitleBar
				| ImGuiWindowFlags_NoMove);
			ImGui::SetWindowSize(ImVec2(400, 750));
			ImGui::SetWindowPos(ImVec2(MAINWINDOW_POS.x + 402, MAINWINDOW_POS.y));
			ImGui::TextColored(ImColor(25, 194, 98, 255), "Team");
			ImGui::Separator();
			ImGui::Checkbox("FullBloom###localfullbloom", &fullBloomlocal);
			ImGui::Checkbox("VelocityGlow###localvelocityglow", &velocityglow_local);
			ImGui::Separator();
			//teamglow
			ImGui::ColorPicker3("TeamGlowPicker", (float*)&TeamGlow, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoTooltip
			 | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview
			 | ImGuiColorEditFlags_DisplayRGB);
			ImGui::SliderFloat("ALPHA###alpha1", &TeamGlow.a, 0.f, 100.f);
			ImGui::Separator();

			ImGui::TextColored(ImColor(217, 72, 20, 255), "Enemy");
			ImGui::Separator();
			ImGui::Checkbox("FullBloom###enemyfullbloom", &fullBloomenemy);
			ImGui::Checkbox("VelocityGlow###enemyvelocityglow", &velocityglow_enemy);
			ImGui::Separator();
			//enemyglow
			ImGui::ColorPicker3("EnemyGlowPicker", (float*)&EnemyGlow, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoTooltip
				| ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview
				| ImGuiColorEditFlags_DisplayRGB);
			ImGui::SliderFloat("ALPHA###alpha2", &EnemyGlow.a, 0.f, 100.f);
		ImGui::End();
		}
		//end of glow
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

	RECT size;
	GetWindowRect(window, &size);
	windowWidth = size.right - size.left;
	windowHeight = size.bottom - size.top;
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

DWORD WINAPI heavyThread(LPVOID lpReserved, HMODULE hMod)
{
	while (join)
	{
		// no sleep
		while (!playercheck)
		{
			Sleep(500); // buffer
		}
		while (join)
		{
			misc.bhop(bhop);
			misc.noflash(flash);
			misc.Glow(glow, EnemyGlow, TeamGlow, fullBloomlocal, fullBloomenemy, velocityglow_local, velocityglow_enemy);
			if (!playercheck) { break; }
			
		}
	}
		FreeLibraryAndExitThread(hMod, 0);
	return 0;
}

DWORD WINAPI lightThread(LPVOID lpReserved, HMODULE hMod)
{
	while (join) {
		// sleep with 50
		while (!playercheck)
		{
			Sleep(500); // buffer
		}
		while (join)
		{
			misc.radar(radarHax);
			healthv = modget1.getplayerHealth();
			flspeed = misc.velocity();
			player_dormant = modget1.getplayerdormant();
			if (!playercheck) { break; }
			Sleep(50);
		}
	}
	misc.noflash(100); //	go back to default amount.
	FreeLibraryAndExitThread(hMod, 0);
	return 0;
}

DWORD WINAPI playercheckThread(LPVOID lpReserved, HMODULE hMod)
{
	while (join)
	{
		playercheck = modget1.getLocalPlayer(); // !!fixed, was writing to a int, FellsDonkMan Clap :D
		Sleep(50);
	}
	FreeLibraryAndExitThread(hMod, 0);
	return 0;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)heavyThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)lightThread, hMod, 0, nullptr);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)playercheckThread, hMod, 0, nullptr);
		break;
	case DLL_PROCESS_DETACH:
		
		join = false;
		kiero::shutdown();
		break;
	}
	return TRUE;
}