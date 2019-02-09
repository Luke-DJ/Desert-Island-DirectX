////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_


///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define DIRECTINPUT_VERSION 0x0800


/////////////
// LINKING //
/////////////
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")


//////////////
// INCLUDES //
//////////////
#include <dinput.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	void GetMouseLocation(float&, float&);

	float GetOldMouseX();
	float GetOldMouseY();
	void SetOldMouseX(float);
	void SetOldMouseY(float);
	float GetCurrentMouseX();
	float GetCurrentMouseY();
	float GetMouseXDelta();
	float GetMouseYDelta();
	void UpdateOldMouse();
	void ResetCursorPosition();
	float GetMouseXSensitivity();
	float GetMouseYSensitivity();

	bool IsEscapePressed();
	bool IsLeftPressed();
	bool IsRightPressed();
	bool IsUpPressed();
	bool IsDownPressed();
	bool IsWPressed();
	bool IsAPressed();
	bool IsSPressed();
	bool IsDPressed();
	bool IsPgUpPressed();
	bool IsPgDownPressed();
	bool IsCtrlPressed();
	bool IsShiftPressed();
	bool IsEnterPressed();

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	unsigned char m_keyboardState[256];
	DIMOUSESTATE m_mouseState;

	int m_screenWidth, m_screenHeight;
	float m_oldMouseX, m_oldMouseY;
	float m_currentMouseX, m_currentMouseY;
	float m_mouseXSensitivity;
	float m_mouseYSensitivity;
};

#endif