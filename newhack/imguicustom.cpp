#include "imguicustom.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"


imguicustom::imguicustom()
{

}

imguicustom::~imguicustom()
{

}

// ..

void imguicustom::defaultstyle()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	ImGui::StyleColorsClassic();
	colors[ImGuiCol_MenuBarBg] = ImColor(127, 115, 177, 70);
	colors[ImGuiCol_WindowBg] = ImColor(9, 6, 23, 200);
	style->WindowRounding = 0;
	style->FrameRounding = 4;
	style->GrabMinSize = 15;
	style->WindowBorderSize = 0;
	style->GrabRounding = 4;
}

void imguicustom::stylealpha(float alpha)
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->Alpha = alpha;
}

void imguicustom::scalesize(float scale) // +scale -scale
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->ScaleAllSizes(scale);
}

// ??idea: create a custom color picker.

// ??idea: create a custom slider that has paramiters of what varebal it is.