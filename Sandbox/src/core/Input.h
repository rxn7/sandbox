#pragma once
class Input {
private:
	static bool keys[512];
	static bool pressedKeys[512];

public:
	static void setKey(int key, bool value) { keys[key] = value; }
	static void setPressedKey(int key, bool value) { pressedKeys[key] = value; }

	static bool getKey(int key) { return keys[key]; }
	static bool getPressedKey(int key) { return pressedKeys[key]; }
};