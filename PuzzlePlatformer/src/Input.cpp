#include "Input.h"
#include "Logger.h"

std::map<int, bool> Input::keyPress;
std::map<int, bool> Input::keyPressRepeat;
std::map<int, bool> Input::keyHeld;
std::map<int, bool> Input::keyRelease;

bool Input::KeyboardCheck(int key)
{
	if (keyHeld.find(key) == keyHeld.end())
	{
		// key not held
		return false;
	}
	else
	{
		// key is held
		return true;
	}
}

bool Input::KeyboardCheckPressed(int key)
{
	if (keyPress.find(key) == keyPress.end())
	{
		// key not held
		return false;
	}
	else
	{
		// key is held
		return true;
	}
}

bool Input::KeyboardCheckPressedRepeat(int key)
{
	if (keyPressRepeat.find(key) == keyPressRepeat.end())
	{
		// key not held
		return false;
	}
	else
	{
		// key is held
		return true;
	}
}

bool Input::KeyboardCheckReleased(int key)
{
	if (keyRelease.find(key) == keyRelease.end())
	{
		// key not held
		return false;
	}
	else
	{
		// key is held
		return true;
	}
}

void Input::SetKeyDown(int key)
{
	keyPress[key] = true;
	keyPressRepeat[key] = true;
	keyHeld[key] = true;
	//Logger::Log("Keydown");
}

void Input::SetKeyDownRepeat(int key)
{
	keyPressRepeat[key] = true;
	keyHeld[key] = true;
	//Logger::Log("Keydown Repeat");
}

void Input::SetKeyUp(int key)
{
	keyRelease[key] = true;
	keyHeld.erase(key);
	//Logger::Log("Keyup");
}

void Input::Update()
{
	keyPress.clear();
	keyPressRepeat.clear();
	keyRelease.clear();
}
