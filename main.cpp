#include <GLFW/glfw3.h>

#include <iostream>
#include <nlohmann/json.hpp>

#include "src/game.h"
#include "src/helper.hpp"
#include <imgui.h>
#include <thread>

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_util.h"
#include "src/color.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"

ImVec2 main_menu_button_size = ImVec2(400, 50);
float x_offset;
float y_offset;

bool is_main_menu = true;
bool add_game_menu, show_games_menu, edit_game_menu = false;

color gray7 = {0.071f, 0.071f, 0.071f, 1};
color gray20 = {0.2f, 0.2f, 0.2f, 0.5f};
ImVec4 clicked_color = color::black(0.75f);

game g = {};
char game_name[100] = "";
game game_to_edit = {};

ImFont* regular_font;
ImFont* large_font;


std::string exe_path = helper::get_exe_path();
std::string path = exe_path.substr(0, exe_path.find_last_of('/')) + "/data/games.json";

void imgui_init(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    (void) io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    regular_font = io.Fonts->AddFontFromFileTTF("../fonts/Roboto-Regular.ttf", 18.0f);
    large_font = io.Fonts->AddFontFromFileTTF("../fonts/Roboto-Regular.ttf", 24.0f);

    ImGui::StyleColorsDark();
}

void init_window(GLFWwindow*& window)
{
    if (!glfwInit()) return;

    window = glfwCreateWindow(1280, 720, "GameLogiX", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    imgui_init(window);
}



void imgui_shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    ImGui::PopFont();
}

void shutdown(GLFWwindow*& window)
{
    imgui_shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void render_loop(GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        int fb_width, fb_height;
        glfwGetFramebufferSize(window, &fb_width, &fb_height);

        int display_w, display_h;
        glfwGetWindowSize(window, &display_w, &display_h);

        ImVec2 win_pos_offset = ImVec2(static_cast<float>(display_w - fb_width) / 2, static_cast<float>(display_h - fb_height));

        ImGui::SetNextWindowPos(win_pos_offset);
        ImGui::SetNextWindowSize(ImVec2(static_cast<float>(fb_width), static_cast<float>(fb_height)));

        ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove);


        if (is_main_menu)
        {
            ImVec2 screen_size = ImGui::GetIO().DisplaySize;
            ImVec2 button_pos((screen_size.x - main_menu_button_size.x) * 0.5f, (screen_size.y - main_menu_button_size.y) * 0.4f);



            ImGui::SetCursorPos(button_pos);
            imgui_util::change_frame_background_color(color::transparent());
            ImGui::BeginListBox("##MAIN_MENU", ImVec2(main_menu_button_size.x + 5, main_menu_button_size.y * 3 + 15));

            imgui_util::reset_color();
            imgui_util::change_button_color(0, 0, 0, 0.5f);
            imgui_util::change_button_hover_color(gray20);
            imgui_util::change_button_clicked_color(clicked_color);

            if (imgui_util::rounded_button("Add Game", main_menu_button_size, 5))
            {
                is_main_menu = false;
                add_game_menu = true;
            }

            if ( imgui_util::rounded_button("Show Games", main_menu_button_size, 5))
            {
                is_main_menu = false;
                show_games_menu = true;
            }
            imgui_util::reset_color();
            imgui_util::reset_color();
            imgui_util::reset_color();

            imgui_util::change_button_color(color::persian_red(0.6f));
            imgui_util::change_button_hover_color(color::persian_red(0.3f));
            imgui_util::change_button_clicked_color(color::persian_red(0.8f));

            if (imgui_util::rounded_button("Exit", main_menu_button_size, 5))
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                shutdown(window);
            }

            imgui_util::reset_color();
            imgui_util::reset_color();
            imgui_util::reset_color();

            ImGui::EndListBox();


        }

        if (add_game_menu)
        {
            imgui_util::change_frame_background_color(0.25f, 0.25f, 0.25f, 0.5f);
            imgui_util::change_button_color(0.25f, 0.25f, 0.25f, 0.5f);

            imgui_util::change_item_width(200);
            ImGui::Text("Game: ");
            ImGui::SameLine();
            ImGui::InputText("##GAME_NAME", game_name, IM_ARRAYSIZE(game_name));

            ImGui::Text("Playtime: ");
            ImGui::SameLine();
            ImGui::InputFloat("##TIME_PLAYED", &g.time_played);

            ImGui::Text("Score: ");
            ImGui::SameLine();
            ImGui::InputInt("##SCORE", &g.score);
            std::clamp(g.score, 1, 10);

            ImGui::Checkbox("Completed", &g.completed);
            imgui_util::reset_color();
            imgui_util::reset_color();
            imgui_util::change_button_color(color::green(1));

            imgui_util::dummy(0, 25);

            if (imgui_util::rounded_button("Add Game To List", ImVec2(200, 50), 5))
            {
                g.game_name = game_name;
                game::add_game(g);
                add_game_menu = false;
                is_main_menu = true;
            }
            imgui_util::reset_color();


            if (imgui_util::back_button("Back", ImVec2(200, 50), 5))
            {
                add_game_menu = false;
                is_main_menu = true;
            }
        }

        if (show_games_menu)
        {
            ImGuiIO &io = ImGui::GetIO();
            ImVec2 screen_size = io.DisplaySize;
            (void) io;


            ImGui::PushFont(large_font);

            imgui_util::change_frame_background_color(color::transparent());
            if (ImGui::BeginListBox("##GAME_LIST", ImVec2(screen_size.x, screen_size.y - 50)))
            {
                if (imgui_util::back_button("Back", ImVec2(screen_size.x - 20, 50), 5))
                {
                    show_games_menu = false;
                    is_main_menu = true;
                }
                imgui_util::reset_color();

                imgui_util::change_item_spacing_y(7);
                for (const auto& g: game::games)
                {
                    std::string label = g.game_name + "##GAME_ENTRY";
                    imgui_util::change_frame_background_color(0.25f, 0.25f, 0.25f, 0.5f);
                    if (ImGui::BeginListBox(label.c_str(), ImVec2(screen_size.x - 20, 130)))
                    {
                        float window_width = ImGui::GetWindowSize().x;
                        float button_width = 200.0f;
                        float padding = 10.0f; // Adjust this value to your liking
                        float button_pos_x = window_width - button_width - padding;

                        imgui_util::change_text_color(0.023529411764705882f, 0.33725490196078434f, 0.7254901960784313f, 1);
                        ImGui::Text(g.game_name.c_str());
                        imgui_util::reset_color();
                        imgui_util::change_item_spacing_y(2);
                        ImGui::Text("Time Played: %.2f hours", g.time_played);
                        ImGui::Text("Score: %d/10", g.score);
                        ImGui::SameLine(button_pos_x);
                        if (imgui_util::back_button("Remove Game", ImVec2(button_width, 30), 5))
                        {
                            game::remove_game(g.game_name);
                            game::save(path);
                        }
                        ImGui::Text(g.completed ? "Completed" : "Not Completed");
                        ImGui::SameLine(button_pos_x);
                        /*if (imgui_util::rounded_button("Edit Game", ImVec2(button_width, 30), 5))
                        {
                            edit_game_menu = true;
                            show_games_menu = false;
                            game_to_edit = g;
                            std::string g_name = game_to_edit.game_name;
                            g_name.copy(game_name, sizeof(game_name) - 1);
                            game_name[sizeof(game_name) - 1] = '\0';
                        }*/
                        imgui_util::reset_styling();



                        ImGui::EndListBox();
                    }

                    imgui_util::reset_color();
                }
                imgui_util::reset_styling();
                ImGui::PopFont();
                ImGui::EndListBox();
            }


        }

        if (edit_game_menu)
        {
            std::string placeholder = game_to_edit.game_name;
            std::string playtime_placeholder = std::to_string(game_to_edit.time_played);
            std::string score_placeholder = std::to_string(game_to_edit.score);


            strcpy(game_name, placeholder.c_str());
            imgui_util::change_frame_background_color(0.25f, 0.25f, 0.25f, 0.5f);
            imgui_util::change_button_color(0.25f, 0.25f, 0.25f, 0.5f);

            imgui_util::change_item_width(200);
            ImGui::Text("Game: ");
            ImGui::SameLine();
            ImGui::SameLine();
            if (ImGui::InputText("##GAME_NAME_EDIT", &game_name[0], IM_ARRAYSIZE(game_name)))
            {
                if (ImGui::IsItemClicked() && game_name == placeholder)
                {
                    strcpy(game_name, "");
                }
                else if (ImGui::IsItemDeactivated() && game_name == "")
                {
                    strcpy(game_name, placeholder.c_str());
                }
            }

            ImGui::Text("Playtime: ");
            ImGui::SameLine();
            if(ImGui::InputFloat("##TIME_PLAYED_EDIT", &g.time_played))
            {

            }

            ImGui::Text("Score: ");
            ImGui::SameLine();
            ImGui::InputInt("##SCORE_EDIT", &g.score);
            std::clamp(g.score, 1, 10);

            ImGui::Checkbox("Completed", &g.completed);
            imgui_util::reset_color();
            imgui_util::reset_color();
            imgui_util::change_button_color(color::green(1));

            imgui_util::dummy(0, 25);

            if (imgui_util::rounded_button("Edit Game", ImVec2(200, 50), 5))
            {
                g.game_name = game_name;
                game::add_game(g);
                add_game_menu = false;
                is_main_menu = true;
            }
            imgui_util::reset_color();


            if (imgui_util::back_button("Back", ImVec2(200, 50), 5))
            {
                edit_game_menu = false;
                is_main_menu = true;
            }
        }


        ImGui::End();




        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main()
{
    std::string exe_path = helper::get_exe_path();
    std::string path = exe_path.substr(0, exe_path.find_last_of('/')) + "/data/games.json";
    game::load(path);

    GLFWwindow* window = nullptr;

    init_window(window);

    render_loop(window);

    shutdown(window);
}
