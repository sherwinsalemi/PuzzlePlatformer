#pragma once

#include <map>

class Input
{
public:
	static bool KeyboardCheck(int key);
	static bool KeyboardCheckPressed(int key);
	static bool KeyboardCheckPressedRepeat(int key);
	static bool KeyboardCheckReleased(int key);

	static void SetKeyDown(int key);
	static void SetKeyDownRepeat(int key);
	static void SetKeyUp(int key);

	static void Update();
private:
	static std::map<int, bool> keyPress;
	static std::map<int, bool> keyPressRepeat;
	static std::map<int, bool> keyHeld;
	static std::map<int, bool> keyRelease;
};
