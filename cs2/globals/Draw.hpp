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

   
    ImVec4 CalculateHealthColor(int health) {
        float r = (100 - health) / 100.0f;
        float g = health / 100.0f;
        return ImVec4(r, g, 0.0f, 1.0f); // Gradiente de vermelho para verde
    }

    void DrawHealthBar(float x, float y, float height, int health, ImVec4 healthColor) {
        // Desenhar a barra de vida proporcional
        float barHeight = height * (health / 100.0f); // A altura da barra depende da saúde
        float barX = x - 5;   // Barra de vida um pouco à esquerda do box
        float barY = y + height; // Inicia na parte inferior do box
        float barWidth = 3.0f;  // Largura da barra de vida

        // Fundo da barra de vida (cinza)
        GetDrawList()->AddRectFilled(ImVec2(barX, y), ImVec2(barX + barWidth, barY), ImColor(50, 50, 50, 255));

        // Barra de vida com cor proporcional
        GetDrawList()->AddRectFilled(ImVec2(barX, barY - barHeight), ImVec2(barX + barWidth, barY), ImColor(healthColor));
    }

    void Line(float x1, float y1, float x2, float y2, ImVec4 color, float thickness) {
        GetDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImColor(color), thickness);
    }

    //distance draw

    void DrawDistance(float playerX, float playerY, float entityX, float entityY, ImVec4 color, float boxX, float boxY, float boxWidth, float boxHeight) {
        // Calcular a distância entre o jogador e a entidade
        float distance = std::sqrt(std::pow(entityX - playerX, 2) + std::pow(entityY - playerY, 2));
        distance /= 1000.0f; // Ajustar escala da distância

        // Criar o texto da distância com valores compactos
        std::stringstream distanceStream;
        distanceStream.precision(0); // Sem casas decimais
        distanceStream << std::fixed << distance;
        std::string distanceText = distanceStream.str() + "m"; // Texto compacto

        // Calcular posição para o texto (bem próximo do box)
        float textX = boxX + (boxWidth / 2.8f); // Ajuste para centralizar levemente à esquerda
        float textY = boxY + boxHeight + 1.0f; // Reduzir espaçamento abaixo do box

        // Adicionar o texto no DrawList
        GetDrawList()->AddText(ImVec2(textX, textY), ImColor(color), distanceText.c_str());
    }


}
