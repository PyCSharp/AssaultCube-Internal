#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "app.h"
#include "imgui_hook.h"
#include "cheat_functions.h"

static HMODULE g_hModule = nullptr;
static bool    g_isDetached = false;

DWORD WINAPI MainThread(LPVOID lpThreadParameter)
{
    g_hModule = (HMODULE)lpThreadParameter;

    uintptr_t ModBase = (uintptr_t)GetModuleHandle(nullptr);

    CreateThread(nullptr, 0, noRecoil, (LPVOID)ModBase, 0, nullptr);
    CreateThread(nullptr, 0, rapidFire, (LPVOID)ModBase, 0, nullptr);
    CreateThread(nullptr, 0, infiniteHealth, (LPVOID)ModBase, 0, nullptr);
    CreateThread(nullptr, 0, infiniteAmmo, (LPVOID)ModBase, 0, nullptr);
    CreateThread(nullptr, 0, knifeSpam, (LPVOID)ModBase, 0, nullptr);
    CreateThread(nullptr, 0, infiniteGrenades, (LPVOID)ModBase, 0, nullptr);
    CreateThread(nullptr, 0, infiniteArmor, (LPVOID)ModBase, 0, nullptr);
    CreateThread(nullptr, 0, infiniteJump, (LPVOID)ModBase, 0, nullptr);

    app::initializeHook();
    return S_OK;
}

DWORD WINAPI ExitThread(LPVOID lpThreadParameter)
{
    if (!g_isDetached)
    {
        g_isDetached = true;
        ImGuiHook::Unload();
        FreeLibraryAndExitThread(g_hModule, TRUE);
    }
    return S_OK;
}

BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hMod);
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        CreateThread(nullptr, 0, ExitThread, nullptr, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}