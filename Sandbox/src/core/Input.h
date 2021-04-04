#pragma once
class Input {
private:
	static bool keys[512];

public:
	/// <summary> Sets the specified key value to the specified one. </summary>
	static void SetKey(int key, bool value) { keys[key] = value; }

	/// <summary> Returns the value of key. True - Pressed. False - Not pressed. </summary>
	static bool GetKey(int key) { return keys[key]; }
};