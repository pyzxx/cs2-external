#include "../imgui/imgui.h"
#include <sstream>


namespace desenho
{
    ImDrawList* GetDrawList() {
        return ImGui::GetForegroundDrawList();
    }

    void DrawCornerBox(float x, float y, float width, float height, ImVec4 boxColor, float boxThickness) {
        // Tamanho do canto do box
        float cornerSize = width / 4.0f;

        // Bordas (superior, inferior, esquerda, direita)
        GetDrawList()->AddLine(ImVec2(x, y), ImVec2(x + cornerSize, y), ImColor(boxColor), boxThickness); // superior esquerda
        GetDrawList()->AddLine(ImVec2(x, y), ImVec2(x, y + cornerSize), ImColor(boxColor), boxThickness); // superior esquerda
        GetDrawList()->AddLine(ImVec2(x + width, y), ImVec2(x + width - cornerSize, y), ImColor(boxColor), boxThickness); // superior direita
        GetDrawList()->AddLine(ImVec2(x + width, y), ImVec2(x + width, y + cornerSize), ImColor(boxColor), boxThickness); // superior direita
        GetDrawList()->AddLine(ImVec2(x, y + height), ImVec2(x + cornerSize, y + height), ImColor(boxColor), boxThickness); // inferior esquerda
        GetDrawList()->AddLine(ImVec2(x, y + height), ImVec2(x, y + height - cornerSize), ImColor(boxColor), boxThickness); // inferior esquerda
        GetDrawList()->AddLine(ImVec2(x + width, y + height), ImVec2(x + width - cornerSize, y + height), ImColor(boxColor), boxThickness); // inferior direita
        GetDrawList()->AddLine(ImVec2(x + width, y + height), ImVec2(x + width, y + height - cornerSize), ImColor(boxColor), boxThickness); // inferior direita
    }
}
