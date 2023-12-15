////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "inputclass.h"

InputClass::InputClass()
{
	m_MouseMovingValues = new std::pair<float, float>(0.0f, 0.0f);
}

InputClass::InputClass(const InputClass& other)
{
}


InputClass::~InputClass()
{
	if (m_MouseMovingValues) {
		delete m_MouseMovingValues;
		m_MouseMovingValues = 0;
	}
}


bool InputClass::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	// Reference : https://copynull.tistory.com/262

	int i;
	HRESULT result;

	/*
	// Initialize all the keys to being released and not pressed.
	for(i=0; i<256; i++)
	{
		m_keys[i] = false;
	}
	*/

	result = DirectInput8Create(hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_DirectInput,
		NULL);
	if(FAILED(result))
	{
		return false;
	}

	// ---- Keyboard ----

	result = m_DirectInput->CreateDevice(GUID_SysKeyboard,
		&m_DIKeyboard,
		NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	result = m_DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}


	// ---- Mouse ----

	result = m_DirectInput->CreateDevice(GUID_SysMouse,
		&m_DIMouse,
		NULL);
	if (FAILED(result))
	{
		return false;
	}

	result = m_DIMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	result = m_DIMouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void InputClass::Shutdown()
{
	if (m_DIMouse)
	{
		m_DIMouse->Unacquire();
		m_DIMouse->Release();
		m_DIMouse = 0;
	}
	if (m_DIKeyboard)
	{
		m_DIKeyboard->Unacquire();
		m_DIKeyboard->Release();
		m_DIKeyboard = 0;
	}
	if (m_DirectInput)
	{
		m_DirectInput->Release();
		m_DirectInput = 0;
	}
}



void InputClass::Frame()
{
	m_DIMouse->Acquire();
	m_DIKeyboard->Acquire();

	m_DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_MouseCurrentState);

	m_DIKeyboard->GetDeviceState(sizeof(m_KeyboardState), (LPVOID)&m_KeyboardState);
}

const std::pair<float, float>* InputClass::GetMouseMovingValues()
{
	m_MouseMovingValues->first = m_MouseCurrentState.lX;
	m_MouseMovingValues->second = m_MouseCurrentState.lY;
	return m_MouseMovingValues;
}

const DIMOUSESTATE& InputClass::GetMouseState()
{
    return m_MouseCurrentState;
}

const BYTE* InputClass::GetKeyboardState()
{
	return m_KeyboardState;
}

bool InputClass::GetKeyDown(int key)
{
	return m_KeyboardState[key] & 0x80;
}



