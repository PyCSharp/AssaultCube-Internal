#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "app.h"
#include "cheat_states.h"
#include "imgui_hook.h"
#include "external/imgui/imgui.h"
#include "external/kiero/minhook/include/MinHook.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "user32.lib")

typedef BOOL(WINAPI* tClipCursor)(const RECT* lpRect);
tClipCursor oClipCursor = nullptr;

namespace app
{
    bool showWindow = true;

    // hook function to let the cusor move
    BOOL WINAPI hkClipCursor(const RECT* lpRect) {
        if (app::showWindow) {
            return oClipCursor(NULL);
        }
        return oClipCursor(lpRect);
    }

    // hide/show imgui when insert is pressed
    DWORD WINAPI GetInsertKey(LPVOID lpParam) {
        while (true) {
            if (GetAsyncKeyState(VK_INSERT) & 1) showWindow = !showWindow;
        }
    }

    // initialize ImGui
    void initializeImGui()
    {
        CreateThread(nullptr, 0, GetInsertKey, nullptr, 0, nullptr);
        ImGui::StyleColorsDark();
    }

    // rendering loop for imgui
    void renderImGui()
    {
        if (showWindow) {
            ImGui::SetNextWindowSize(ImVec2(300, 350));

            if (ImGui::Begin("AssaultCube Internal - PySharp", nullptr, ImGuiWindowFlags_NoResize)) {
                ImGui::Checkbox("Infinite Health", &infiniteHealthActivated);
                ImGui::Checkbox("Infinite Ammo", &infiniteAmmoActivated);
                ImGui::Checkbox("Infinite Armor", &infiniteArmorActivated);
                ImGui::Checkbox("Infinite Grenades", &infiniteGrenadesActivated);
                ImGui::Checkbox("Infinite Jump", &infiniteJumpActivated);
                ImGui::Checkbox("Knife Spam", &knifeSpamActivated);
                ImGui::Checkbox("Grenade Spam", &grenadeSpamActivated);
                ImGui::Checkbox("No Recoil", &noRecoilActivated);
                ImGui::Checkbox("Rapid Fire", &rapidFireActivated);
            }

            ImGui::End();
        }
    }

    // initialize the hooks
    void initializeHook() {
        if (MH_Initialize() != MH_OK) return;

        MH_CreateHookApi(L"user32.dll", "ClipCursor", &hkClipCursor, reinterpret_cast<LPVOID*>(&oClipCursor));
        MH_EnableHook(MH_ALL_HOOKS);

        if (!ImGuiHook::Load(renderImGui, initializeImGui)) { }
    }
}
