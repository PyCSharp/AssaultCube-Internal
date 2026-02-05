#include <Windows.h>
#include <cstdint>
#include <cmath>
#include <cwchar>
#include "cheat_states.h"

DWORD WINAPI infiniteArmor(LPVOID base) {
	uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>((uintptr_t)base + 0x0017E0A8); // dereference a pointer that points to the playerent class
	uintptr_t armor = localPlayer + 0xF0; // offset in the playerent class

	bool lastState = false;

	while (true) {
		bool currentState = infiniteArmorActivated;

		if (currentState) // write when the cheat is activated
			*reinterpret_cast<uint32_t*>(armor) = 9999; // write value

		if (lastState && !currentState) // reset when the cheat is not activated
			*reinterpret_cast<uint32_t*>(armor) = 100;

		lastState = currentState;
	}
}

DWORD WINAPI infiniteAmmo(LPVOID base) {
	uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>((uintptr_t)base + 0x0017E0A8); // dereference a pointer that points to the playent class 
	uintptr_t ammoMachineGun = localPlayer + 0x140; // offset in the playerent class
	uintptr_t ammoPistol = localPlayer + 0x12C; // offset in the playerent class
	uintptr_t ammoAkimbo = localPlayer + 0x148; // offset in the playerent class

	bool lastState = false;

	while (true) {
		bool currentState = infiniteAmmoActivated;

		if (currentState) { // write when the cheat is activated
			*reinterpret_cast<int*>(ammoMachineGun) = 9999; // write value
			*reinterpret_cast<int*>(ammoPistol) = 9999; // write value
			*reinterpret_cast<int*>(ammoAkimbo) = 9999; // write value
		}

		if (lastState && !currentState) { // reset when the cheat is not activated
			*reinterpret_cast<int*>(ammoMachineGun) = 20; // write value
			*reinterpret_cast<int*>(ammoPistol) = 10; // write value
			*reinterpret_cast<int*>(ammoAkimbo) = 20; // write value
		}

		lastState = currentState;

		Sleep(5);
	}
}

DWORD WINAPI knifeSpam(LPVOID base) {
	uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>((uintptr_t)base + 0x0017E0A8); // dereference a pointer that points to the playerent class
	uintptr_t knifeDelay = localPlayer + 0x14C; // offset in the playerent class

	while (true) {
		if (knifeSpamActivated) // write when the cheat is actiavted
			*reinterpret_cast<uint16_t*>(knifeDelay) = 0x0000;

		else {}

		Sleep(5);
	}
}

DWORD WINAPI infiniteHealth(LPVOID base) {
	uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>((uintptr_t)base + 0x0017E0A8); // dereference a pointer that points to the playerent class
	uintptr_t health = localPlayer + 0xEC; // offset in the playerent class

	bool lastState = false;

	while (true) {
		bool currentState = infiniteHealthActivated;

		if (currentState) // write when the cheat is actiavted
			*reinterpret_cast<int*>(health) = 9999;

		if (lastState && !currentState) // reset when the cheat is not activated
			*reinterpret_cast<int*>(health) = 100;

		lastState = currentState;
		Sleep(5);
	}
}


DWORD WINAPI infiniteGrenades(LPVOID base) {
	uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>((uintptr_t)base + 0x0017E0A8); // dereference a pointer that points to the playerent class
	uintptr_t grenades = localPlayer + 0x144; // offset in the playerent class

	bool lastState = false;

	while (true) {
		bool currentState = infiniteGrenadesActivated;

		if (currentState) // write when the cheat is activated
			*reinterpret_cast<int*>(grenades) = 9999; // write value

		if (lastState && !currentState) // reset when the cheat is not activated
			*reinterpret_cast<int*>(grenades) = 1;

		lastState = currentState;
		Sleep(5);
	}
}

DWORD WINAPI rapidFire(LPVOID base) {
	uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>((uintptr_t)base + 0x0017E0A8); // dereference a pointer that points to the playerent class
	uintptr_t attackDelay = localPlayer + 0x164; // offset in the playerent class

	while (true) {
		if (rapidFireActivated) // write when the cheat is activated
			*reinterpret_cast<uint8_t*>(attackDelay) = 25;

		else {}

		Sleep(5);
	}
}

DWORD WINAPI infiniteJump(LPVOID base) {
	uintptr_t localPlayer = *reinterpret_cast<uintptr_t*>((uintptr_t)base + 0x0017E0A8); // dereference a pointer that points to the playerent class
	uintptr_t onfloorBool = localPlayer + 0x5D; // offset in the playerent class

	while (true) {
		if (infiniteJumpActivated) // write when the cheat is activated
			*reinterpret_cast<uint8_t*>(onfloorBool) = 0x01;

		else {}

		Sleep(20);
	}
}

DWORD WINAPI noRecoil(LPVOID base) {
	DWORD oldProtect;
	uintptr_t changeViewAngleAddr = (uintptr_t)base + 0xC2EC3;

	bool lastState = false;

	// movss dword ptr [esi+38h], xmm2
	uint8_t originalBytes[5] = {
		0xF3, 0x0F, 0x11, 0x56, 0x38
	};

	VirtualProtect((LPVOID)changeViewAngleAddr, 5, PAGE_EXECUTE_READWRITE, &oldProtect); // set pageprotection
	while (true) {
		bool currentState = noRecoilActivated;
		if (currentState && !lastState) // write when the cheat is activated
			memset((void*)changeViewAngleAddr, 0x90, 5); // apply patch

		if (!currentState && lastState) { //reset when the cheat is not activated
			memcpy((void*)changeViewAngleAddr, (const void*)originalBytes, 5); // apply patch
			FlushInstructionCache(GetCurrentProcess(), (LPCVOID)changeViewAngleAddr, 5); //flush instruction cache
		}

		lastState = currentState;

		Sleep(5);
	}
	VirtualProtect((LPVOID)changeViewAngleAddr, 5, oldProtect, nullptr); // reset pageprotection
}