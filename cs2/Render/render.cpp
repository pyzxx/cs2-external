#include "render.h"
#include "overlay.h"
#include <thread>
#include <iostream>
#include "../globals/globals.h"
#include <string>
#include "custom.hpp"





void ovcontrol() {
    while (g.Run) {
        if (GetAsyncKeyState(VK_INSERT))
            g.Showmenu = !g.Showmenu;

        Sleep(100);
    }
}


bool Renderer::Render::loopRender()
{



    std::thread([&]() { ovcontrol(); }).detach();

    // starta/configura o imgui
    InitMenu();

    // renderiza o menu
    BeatMenu();
    DestroyMenu();

    return true;
}


void overlayX::menu() {
    //Start the Dear ImGui frame
    static bool bools[50]{};
    static int ints[50]{};
    vector < const char* > items = { "Head", "Chest", "Body", "Legs", "Feet" };

    static float color[4] = { 1.f, 1.f, 1.f, 1.f };

    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(510, 380));

    ImGui::Begin("Hello, world!", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse); {

        auto window = GetCurrentWindow();
        auto draw = window->DrawList;
        auto pos = window->Pos;
        auto size = window->Size;
        auto style = GetStyle();

        custom.m_anim = ImLerp(custom.m_anim, 1.f, 0.03f);

        draw->AddLine(pos + ImVec2(65, 40), pos + ImVec2(size.x - 15, 40), ImColor(1.f, 1.f, 1.f, 0.05f));

        switch (custom.m_tab) {

        case 0:

            SetCursorPos(ImVec2(70, 13));
            BeginGroup();

            for (int i = 0; i < custom.rage_subtabs.size(); ++i) {

                if (custom.sub_tab(custom.rage_subtabs.at(i), custom.m_rage_subtab == i) && custom.m_rage_subtab != i)
                    custom.m_rage_subtab = i, custom.m_anim = 0.f;

                if (i != custom.rage_subtabs.size() - 1)
                    SameLine();
            }

            EndGroup();

            SetCursorPos(ImVec2(65, 50));
            BeginChild("##rage_childs", ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {

                switch (custom.m_rage_subtab) {

                case 0:

                    custom.begin_child("General", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
                      
                     

                        Checkbox("Show Fov", &g.ShowFov);
                        SliderFloat("FOV", &g.AimFov, 30.f, 300.f);
                    } custom.end_child();

                    SameLine();

                    custom.begin_child("Other", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
                       


                        Checkbox("Team Check", &g.TeamCheck);
                        

                    } custom.end_child();

                    break;

                }

            } EndChild();

            break;

        case 1:

            SetCursorPos(ImVec2(70, 13));
            BeginGroup();

            for (int i = 0; i < custom.visuals_subtabs.size(); ++i) {

                if (custom.sub_tab(custom.visuals_subtabs.at(i), custom.m_visuals_subtab == i) && custom.m_visuals_subtab != i)
                    custom.m_visuals_subtab = i, custom.m_anim = 0.f;

                if (i != custom.visuals_subtabs.size() - 1)
                    SameLine();
            }

            EndGroup();

            SetCursorPos(ImVec2(65, 50));
            BeginChild("##visuals_childs", ImVec2(GetWindowWidth() - 80, GetWindowHeight() - 80)); {

                switch (custom.m_visuals_subtab) {

                case 0: // ESP Settings


                    custom.begin_child("ESP", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {
                        // Configurações do ESP
                  
                        ImGui::Checkbox("Box", &g.e_box);
                        ImGui::Checkbox("HealthBar", &g.healthBar);
                        ImGui::Checkbox("Lines", &g.lines);
                        ImGui::Checkbox("distance", &g.distance);
                        ImGui::Checkbox("skeleton", &g.skeleton);
                    } custom.end_child();

                    SameLine();

                    custom.begin_child("ESP COLORS", ImVec2(GetWindowWidth() / 2 - GetStyle().ItemSpacing.x / 2, GetWindowHeight())); {

                        // Cor para Skeleton
                      

                        // Cor para Box
                        

                        // Cor para Lines
                       

                        Checkbox("StreamProof", &g.streamproof);
                        if (ImGui::Button("Desinject (clean)")) {
                            g.Run = false;
                            exit(0);
                        }
                    } custom.end_child();
                    break;
                }

            } EndChild();

            break;
        }





        SetCursorPosY(0);
        custom.tab_area("##tab_area", ImVec2(50, size.y - 20), []() {

            for (int i = 0; i < custom.tabs.size(); ++i)
                if (custom.tab(custom.tabs_icons.at(i), custom.tabs.at(i), custom.m_tab == i) && custom.m_tab != i)
                    custom.m_tab = i, custom.m_anim = 0.f;

            });

        // footer
        draw->AddRectFilled(pos + ImVec2(0, size.y - 20), pos + size, ImColor(10, 10, 10), style.WindowRounding, ImDrawFlags_RoundCornersBottom);
        draw->AddText(pos + ImVec2(5, size.y - 18), GetColorU32(ImGuiCol_Text), "Private External");
        draw->AddText(pos + ImVec2(size.x - CalcTextSize("Phantom.lol").x - 5, size.y - 18), GetColorU32(ImGuiCol_Text), "Phantom.lol");

    } ImGui::End();

    PopStyleVar(2);
}

