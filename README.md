# AssaultCube Internal Cheat

My first internal cheat for **AssaultCube**.  
Built mainly to learn internal DLL injection, memory editing, and basic game hacking concepts.

## Features
- No recoil  
- Rapid fire  
- Infinite health  
- Infinite ammo  
- Infinite grenades  
- Infinite jump  
- Infinite armor  
- Knife spam
- Grenade Spam
- Hooking ClipCursor() from the WinAPI

Focus of this project is understanding:
- Internal DLL cheats
- Memory manipulation
- Function hooking
- Basic in‑game feature toggles

## Credits
Big thanks to the creator of this OpenGL ImGui hook used for rendering the menu:

https://github.com/adafcaefc/Universal-OpenGL-2-Kiero-Hook

## Build Instructions
1. Open the `.slnx` file in **Visual Studio**
2. Set configuration:
   - **Release**
   - **Win32**
3. Build the project  
4. The compiled DLL will be inside the `Release` folder

## Usage
1. Start `ac_client.exe`
2. Inject the compiled DLL into the game process
3. Open the menu in-game and toggle features
4. You can hide/show the menu by pressing Insert

Recommended injector:  
https://github.com/DarthTon/Xenos

## Notes
Created for learning and research purposes (internal game hacking, reversing, memory structures, hooking).

Feel free to fork, improve, or build your own features on top of it.
