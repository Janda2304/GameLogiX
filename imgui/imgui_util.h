#ifndef IMGUI_UTIL_H
#define IMGUI_UTIL_H
#include <imgui.h>




class imgui_util
{
public:
    //colors
    static void change_background_color(ImVec4 color);
    static void change_background_color(float r, float g, float b, float a);

    static void change_text_color(ImVec4 color);
    static void change_text_color(float r, float g, float b, float a);

    static void change_button_color(ImVec4 color);
    static void change_button_color(float r, float g, float b, float a);
    static void change_button_hover_color(ImVec4 color);
    static void change_button_hover_color(float r, float g, float b, float a);
    static void change_button_clicked_color(ImVec4 color);
    static void change_button_clicked_color(float r, float g, float b, float a);

    static void change_frame_background_color(ImVec4 color);
    static void change_frame_background_color(float r, float g, float b, float a);

    static void change_item_rounding(float rounding);

    static void change_item_spacing(ImVec2 spacing);
    static void change_item_spacing(float x, float y);
    static void change_item_spacing_x(float x);
    static void change_item_spacing_y(float y);
    static void reset_item_spacing();

    static void change_slider_grab_color(ImVec4 color);
    static void change_slider_grab_color(float r, float g, float b, float a);

    static void change_slider_grab_active_color(ImVec4 color);
    static void change_slider_grab_active_color(float r, float g, float b, float a);

    static void reset_color(int count = 1);

    static void change_item_width(float width);

    static bool rounded_button(const char* label, ImVec2 size, float rounding);

    static void dummy(ImVec2 size);
    static void dummy(float x, float y);

    static void reset_styling(int count = 1);

    static bool back_button(const char* label, ImVec2 size, float rounding);

    static bool begin_rounded_list_box(const char* label, ImVec2 size, float rounding);
};



#endif //IMGUI_UTIL_H
