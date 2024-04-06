#include "imgui_util.h"
#include "../src/color.hpp"

void imgui_util::change_background_color(const ImVec4 color)
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, color);
}

void imgui_util::change_background_color(const float r, const float g, const float b, const float a)
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(r, g, b, a));
}

void imgui_util::change_text_color(ImVec4 color)
{
    ImGui::PushStyleColor(ImGuiCol_Text, color);
}

void imgui_util::change_text_color(float r, float g, float b, float a)
{
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(r, g, b, a));
}

void imgui_util::change_button_color(ImVec4 color)
{
    ImGui::PushStyleColor(ImGuiCol_Button, color);
}

void imgui_util::change_button_color(float r, float g, float b, float a)
{
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(r, g, b, a));
}

void imgui_util::change_button_hover_color(ImVec4 color)
{
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, color);
}

void imgui_util::change_button_hover_color(float r, float g, float b, float a)
{
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(r, g, b, a));
}

void imgui_util::change_button_clicked_color(ImVec4 color)
{
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, color);
}

void imgui_util::change_button_clicked_color(float r, float g, float b, float a)
{
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(r, g, b, a));
}

void imgui_util::change_frame_background_color(ImVec4 color)
{
    ImGui::PushStyleColor(ImGuiCol_FrameBg, color);
}

void imgui_util::change_frame_background_color(float r, float g, float b, float a)
{
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(r, g, b, a));
}

void imgui_util::change_item_rounding(float rounding)
{
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, rounding);
}

void imgui_util::change_item_spacing(ImVec2 spacing)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, spacing);
}

void imgui_util::change_item_spacing(float x, float y)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(x, y));
}

void imgui_util::change_item_spacing_x(float x)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(x, 0));
}

void imgui_util::change_item_spacing_y(float y)
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, y));
}

void imgui_util::reset_item_spacing()
{
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
}

void imgui_util::reset_styling()
{
    ImGui::PopStyleVar();
}

bool imgui_util::back_button(const char *label, ImVec2 size, float rounding = 5)
{
    change_button_color(color::persian_red(0.6f));
    change_button_hover_color(color::persian_red(0.3f));
    change_button_clicked_color(color::persian_red(0.8f));
    bool state = rounded_button(label, size, rounding);
    reset_color();
    reset_color();
    reset_color();
    return state;
}

void imgui_util::change_slider_grab_color(const ImVec4 color)
{
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, color);
}

void imgui_util::change_slider_grab_color(const float r, const float g, const float b, const float a)
{
    ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(r, g, b, a));
}

bool imgui_util::rounded_button(const char *label, const ImVec2 size, const float rounding)
{
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, rounding);
    bool result = ImGui::Button(label, size);
    ImGui::PopStyleVar();
    return result;
}

void imgui_util::dummy(const ImVec2 size)
{
    ImGui::Dummy(size);
}

void imgui_util::dummy(const float x, const float y)
{
    ImGui::Dummy(ImVec2(x, y));
}

void imgui_util::change_slider_grab_active_color(const ImVec4 color)
{
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0, 0.5f, 0, 1.0f));
}

void imgui_util::change_slider_grab_active_color(const float r, const float g, const float b, const float a)
{
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(r, g, b, a));
}

void imgui_util::reset_color()
{
    ImGui::PopStyleColor();
}

void imgui_util::change_item_width(const float width)
{
    ImGui::PushItemWidth(width);
}



