////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "inputclass.h"


InputClass::InputClass()
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
}


InputClass::InputClass(const InputClass& other)
{
}


InputClass::~InputClass()
{
}


bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;


	// Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize the location of the mouse on the screen.
	m_oldMouseX = 0;
	m_oldMouseY = 0;
	m_currentMouseX = 0;
	m_currentMouseY = 0;

	// Initialize the mouse sensitivity values.
	m_mouseXSensitivity = 0.3f;
	m_mouseYSensitivity = 0.2f;

	// Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the keyboard.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the keyboard to not share with other programs.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(result))
	{
		return false;
	}

	// Now acquire the keyboard.
	result = m_keyboard->Acquire();
	if(FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the mouse.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if(FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the mouse to share with other programs.
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(result))
	{
		return false;
	}

	// Acquire the mouse.
	result = m_mouse->Acquire();
	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void InputClass::Shutdown()
{
	// Release the mouse.
	if(m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// Release the keyboard.
	if(m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// Release the main interface to direct input.
	if(m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;
}


bool InputClass::Frame()
{
	bool result;


	// Read the current state of the keyboard.
	result = ReadKeyboard();
	if(!result)
	{
		return false;
	}

	// Read the current state of the mouse.
	result = ReadMouse();
	if(!result)
	{
		return false;
	}

	// Process the changes in the mouse and keyboard.
	ProcessInput();

	return true;
}


bool InputClass::ReadKeyboard()
{
	HRESULT result;


	// Read the keyboard device.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if(FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
		
	return true;
}


bool InputClass::ReadMouse()
{
	HRESULT result;


	// Read the mouse device.
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if(FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}


void InputClass::ProcessInput()
{
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	m_currentMouseX += m_mouseState.lX;
	m_currentMouseY += m_mouseState.lY;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (m_currentMouseX < 0.0f)
	{
		m_oldMouseX = m_screenWidth + (m_currentMouseX - m_oldMouseX);
		m_currentMouseX = m_screenWidth;
	}
	if (m_currentMouseY < 0.0f)
	{
		m_oldMouseY = m_screenHeight + (m_currentMouseY - m_oldMouseY);
		m_currentMouseY = m_screenHeight;
	}
	if (m_currentMouseX > m_screenWidth)
	{
		m_oldMouseX = m_currentMouseX - m_oldMouseX;
		m_currentMouseX = 0.0f;
	}
	if (m_currentMouseY > m_screenHeight)
	{
		m_oldMouseY = m_currentMouseY - m_oldMouseY;
		m_currentMouseY = 0.0f;
	}

	return;
}


void InputClass::GetMouseLocation(float& mouseX, float& mouseY)
{
	mouseX = GetCurrentMouseX();
	mouseY = GetCurrentMouseY();
	return;
}


float InputClass::GetOldMouseX()
{
	return m_oldMouseX;
}

float InputClass::GetOldMouseY()
{
	return m_oldMouseY;
}

void InputClass::SetOldMouseX(float mouseX)
{
	m_oldMouseX = mouseX;
}

void InputClass::SetOldMouseY(float mouseY)
{
	m_oldMouseY = mouseY;
}

float InputClass::GetCurrentMouseX()
{
	return m_currentMouseX;
}

float InputClass::GetCurrentMouseY()
{
	return m_currentMouseY;
}

float InputClass::GetMouseXDelta()
{
	return GetCurrentMouseX() - GetOldMouseX();
}

float InputClass::GetMouseYDelta()
{
	return GetCurrentMouseY() - GetOldMouseY();
}

void InputClass::UpdateOldMouse()
{
	SetOldMouseX(GetCurrentMouseX());
	SetOldMouseY(GetCurrentMouseY());
}

void InputClass::ResetCursorPosition()
{
	SetCursorPos(m_screenWidth * 0.5f, m_screenHeight * 0.5f);
}

float InputClass::GetMouseXSensitivity()
{
	return m_mouseXSensitivity;
}

float InputClass::GetMouseYSensitivity()
{
	return m_mouseYSensitivity;
}

bool InputClass::IsEscapePressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if(m_keyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsLeftPressed()
{
	// Do a bitwise and on the keyboard state to check if either of the acceptable keys are currently being pressed.
	if(m_keyboardState[DIK_LEFT] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsRightPressed()
{
	// Do a bitwise and on the keyboard state to check if either of the acceptable keys are currently being pressed.
	if(m_keyboardState[DIK_RIGHT] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsUpPressed()
{
	// Do a bitwise and on the keyboard state to check if either of the acceptable keys are currently being pressed.
	if(m_keyboardState[DIK_UP] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsDownPressed()
{
	// Do a bitwise and on the keyboard state to check if either of the acceptable keys are currently being pressed.
	if(m_keyboardState[DIK_DOWN] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsWPressed()
{
	// Do a bitwise and on the keyboard state to check if the key is currently being pressed.
	if (m_keyboardState[DIK_W] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsAPressed()
{
	// Do a bitwise and on the keyboard state to check if the key is currently being pressed.
	if(m_keyboardState[DIK_A] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsSPressed()
{
	// Do a bitwise and on the keyboard state to check if the key is currently being pressed.
	if(m_keyboardState[DIK_S] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsDPressed()
{
	// Do a bitwise and on the keyboard state to check if the key is currently being pressed.
	if (m_keyboardState[DIK_D] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsPgUpPressed()
{
	// Do a bitwise and on the keyboard state to check if the key is currently being pressed.
	if(m_keyboardState[DIK_PGUP] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsPgDownPressed()
{
	// Do a bitwise and on the keyboard state to check if the key is currently being pressed.
	if(m_keyboardState[DIK_PGDN] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsCtrlPressed()
{
	// Do a bitwise and on the keyboard state to check if the key is currently being pressed.
	if (m_keyboardState[DIK_LCONTROL] & 0x80 || m_keyboardState[DIK_RCONTROL] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsShiftPressed()
{
	// Do a bitwise and on the keyboard state to check if the key is currently being pressed.
	if (m_keyboardState[DIK_LSHIFT] & 0x80 || m_keyboardState[DIK_RSHIFT] & 0x80)
	{
		return true;
	}

	return false;
}


bool InputClass::IsEnterPressed()
{
	// Do a bitwise and on the keyboard state to check if the key is currently being pressed.
	if (m_keyboardState[DIK_RETURN] & 0x80)
	{
		return true;
	}

	return false;
}
