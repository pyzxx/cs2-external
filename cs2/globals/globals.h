#include <cstddef>
#include "../imgui/imgui.h"

struct globals
{
	HWND hwnd;
	WNDCLASSEXW wc;
	RECT csRect{};
	POINT csPoint{};

	bool Run = true;
	bool streamproof = false;
	bool Showmenu = false;

	//visuals 
	bool e_box = false;
	bool ShowFov = false;
	bool TeamCheck = false;

	float AimFov = 30.0f;
	//colors 
	ImVec4 boxColor = ImVec4(0.0f, 1.0f, 1.0f, 1.0f); // Ciano
};
inline globals g;



namespace offsets
{
	//att constantemente //offsets.hpp cs2 dumper
	constexpr std::ptrdiff_t dwEntityList = 0x1A146E8;
	constexpr std::ptrdiff_t dwGlobalVars = 0x185C9B0;
	constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1868CC8;
	constexpr std::ptrdiff_t dwViewAngles = 0x1A89710;
	constexpr std::ptrdiff_t dwViewMatrix = 0x1A7F610;

	constexpr std::ptrdiff_t dwLocalPlayerController = 0x1A64E80;


	constexpr std::ptrdiff_t m_vecC4ExplodeSpectatePos = 0x14B8; // Vector


	constexpr std::ptrdiff_t dwWindowHeight = 0x6140CC;
	constexpr std::ptrdiff_t dwWindowWidth = 0x6140C8;
	constexpr std::ptrdiff_t dwWeaponC4 = 0x19F55F8;
	constexpr std::ptrdiff_t dwPlantedC4 = 0x1A84F90;


	// att dificilmente // client_dll.cs cs2 dumper               https://github.com/a2x/cs2-dumper/blob/main/output/client_dll.cs
	constexpr std::ptrdiff_t m_iTeamNum = 0x3E3;
	constexpr std::ptrdiff_t m_vOldOrigin = 0x1324; //vector3
	constexpr std::ptrdiff_t m_vecViewOffset = 0xCB0;
	constexpr std::ptrdiff_t m_lifeState = 0x348;
	constexpr std::ptrdiff_t m_entitySpottedState = 0x23D0;
	constexpr std::ptrdiff_t m_bSpotted = 0x8;
	constexpr std::ptrdiff_t m_bSpottedByMask = 0xC;
	constexpr std::ptrdiff_t dwViewRender = 0x1A54D60;
	constexpr std::ptrdiff_t m_modelState = 0x170;
	constexpr std::ptrdiff_t m_vecAbsOrigin = 0xD0; // Vector
	constexpr std::ptrdiff_t m_pGameSceneNode = 0x328;
	constexpr std::ptrdiff_t m_hPlayerPawn = 0x80C;
	constexpr std::ptrdiff_t m_iHealth = 0x344;
	constexpr std::ptrdiff_t m_aimPunchAngle = 0x1574;
	constexpr std::ptrdiff_t m_hPawn = 0x62C;
	constexpr std::ptrdiff_t m_pCameraServices = 0x11E0;
	constexpr std::ptrdiff_t m_iFOV = 0x210;
	constexpr std::ptrdiff_t m_bIsScoped = 0x23D0;
	constexpr std::ptrdiff_t m_iszPlayerName = 0x660;
	constexpr std::ptrdiff_t m_sSanitizedPlayerName = 0x770;
	constexpr std::ptrdiff_t m_bUseScreenAspectRatio = 0x585; // bool
}
