#include "sdk.h"
#include "../globals/globals.h"
#include <thread>
#include <wtypes.h>
#include "../Math/bones.hpp"
#include "../imgui/imgui_internal.h"
#include "../Math/Vector.h"
#include "../globals/Draw.hpp"

//pegar o client do cs2
bool Sdk::ThreadLoop()
{
	
	DWORD pid = mem.getPid(L"cs2.exe"); //pid
	if (!pid)
		return false;

	sdk.base = mem.GetBase(pid, L"client.dll");
	if (!sdk.base)
		return false;


	return true;

}
void Sdk::RenderDbg()
{
	if (g.ShowFov)
	{
		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		float distance = 10000000.f;
		// Obtém o viewport principal
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 viewportPos = viewport->Pos;
		ImVec2 viewportSize = viewport->Size;

		// Calcula o centro da tela manualmente
		ImVec2 center;
		center.x = viewportPos.x + (viewportSize.x * 0.5f);
		center.y = viewportPos.y + (viewportSize.y * 0.5f);

		// Obtém o tempo atual
		float time = ImGui::GetTime(); // Tempo em segundos desde o início do aplicativo

		// Calcula a cor com base no tempo
		float red = 0.5f + 0.5f * std::sin(time);   // Varia de 0.0 a 1.0
		float green = 0.5f + 0.5f * std::sin(time + 2.0f); // Varia de 0.0 a 1.0, mas deslocado no tempo
		float blue = 0.5f + 0.5f * std::sin(time + 4.0f); // Varia de 0.0 a 1.0, deslocado no tempo

		// Garante que a cor esteja no intervalo de 0.0 a 1.0


		// Define a cor atual
		ImU32 color = ImColor(red, green, blue, 1.0f); // Totalmente opaco

		// Desenha um círculo pequeno preto preenchido no centro

		// Desenha o círculo do FOV com a cor que muda
		drawList->AddCircle(center, g.AimFov, color, 0, 1.f); // O 0 define a suavização padrão e 1.0f a espessura da borda
		if (distance < g.AimFov)
			return;
	}
}
void Sdk::RenderEsp()
{
	//localPlayer
	uintptr_t localplayer = mem.Read<uintptr_t>(sdk.base + offsets::dwLocalPlayerPawn);
	Vector3 localPos = mem.Read<Vector3>(localplayer + offsets::m_vOldOrigin);
	uint8_t localTeam = mem.Read<uint8_t>(localplayer + offsets::m_iTeamNum);

	//game
	view_matrix_t view_matrix = mem.Read<view_matrix_t>(sdk.base + offsets::dwViewMatrix);

	//entidades
	uintptr_t entidade = mem.Read<uintptr_t>(sdk.base + offsets::dwEntityList);

	for (int i = 0; i < 64; i++)
	{
		uintptr_t listEntry = mem.Read<uintptr_t>(entidade + 0x10);
		if (listEntry == 0)
			continue;

		uintptr_t currentConroller = mem.Read<uintptr_t>(listEntry + i * 0x78);
		if (currentConroller == 0)
			continue;

		int pawnHandle = mem.Read<int>(currentConroller + offsets::m_hPlayerPawn);
		if (pawnHandle == 0)
			continue;

		uintptr_t listEntry2 = mem.Read<uintptr_t>(entidade + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 0x10);

		uintptr_t currentPawn = mem.Read<uintptr_t>(listEntry2 + 0x78 * (pawnHandle & 0x1FF));
		if (currentPawn == 0)
			continue;

		//verificações
		uint32_t healthentity = mem.Read<uint32_t>(currentPawn + offsets::m_iHealth);
		uint8_t enemyTeam = mem.Read<uint8_t>(currentPawn + offsets::m_iTeamNum);
		int lifeState = mem.Read<int>(currentPawn + offsets::m_lifeState);

		if (g.TeamCheck == true)
		{
			if (localTeam == enemyTeam)
				continue;
		}

		if (healthentity <= 0 || lifeState != 256 || currentPawn == localplayer)
			continue;

		//preparamentos para desenhar 

		//acessar os bones da cabeça e do pé
		auto gamescene = mem.Read<uintptr_t>(currentPawn + offsets::m_pGameSceneNode);
		auto bonearray = mem.Read<uintptr_t>(gamescene + offsets::m_modelState + 0x80);

		//pos bones
		Vector3 origin = mem.Read<Vector3>(currentPawn + offsets::m_vOldOrigin);

		Vector3 head3d = mem.Read<Vector3>(bonearray + bones::head * 32); 
		Vector3 feet3d = mem.Read<Vector3>(bonearray + bones::right_feet * 32);

		//pos bones 2d
		Vector3 origin2d = origin.WTS(view_matrix);
		Vector3 head2d = head3d.WTS(view_matrix);
		Vector3 feet2d = feet3d.WTS(view_matrix);

		float headHeigth = (feet2d.y - head2d.y) / 8;
		float heigth = feet2d.y - head2d.y + 15.f;
		float width = heigth / 1.4f;

		if (g.e_box == true)
		{
			if (head2d.z > 0.1f && feet2d.z > 0.1f)
			{
				desenho::DrawCornerBox(
					feet2d.x - width / 2,
					head2d.y - headHeigth,
					width,
					heigth,
					g.boxColor,
					1
				);
			}
		}

	}
}