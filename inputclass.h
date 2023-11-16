////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

// for extern value &c_dfDIMouse and &c_dfDIKeyboard
#pragma comment(lib, "dinput8.lib")

#include <dinput.h>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND);
	void Shutdown();

	void Frame();

	const std::pair<float, float>* GetMouseMovingValues();
	const BYTE* GetKeyboardState();
	bool GetKeyDown(int key);

private:
	// bool m_keys[256];

	IDirectInputDevice8* m_DIMouse;
	IDirectInputDevice8* m_DIKeyboard;

	LPDIRECTINPUT8 m_DirectInput;

	DIMOUSESTATE m_MouseCurrentState;
	BYTE m_KeyboardState[256] = {0, };

	std::pair<float, float>* m_MouseMovingValues;
};

#endif