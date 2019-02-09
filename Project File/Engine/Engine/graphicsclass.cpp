////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Position = 0;
	m_Camera = 0;
	m_CameraType = GraphicsClass::CameraType::Free;
	m_Sound = 0;
	m_SkySphere = 0;
	m_SkyPlane = 0;
	m_MyScene = 0;

	m_CameraTypeSwitchable = true;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 110.0f, -200.0f);
	m_Position->SetRotation(37.5f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, -1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

	// Create the sound object.
	m_Sound = new SoundClass;
	if (!m_Sound)
	{
		return false;
	}

	// Initialize the sound object.
	result = m_Sound->Initialize(hwnd, "../Engine/data/Music/Beach Party.wav");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectSound.", L"Error", MB_OK);
		return false;
	}

	// Play the sound object's loaded WAV file.
	result = m_Sound->PlayWaveFile(true);
	if (!result)
	{
		return false;
	}

	// Create the skysphere object.
	m_SkySphere = new ModelClass;
	if (!m_SkySphere)
	{
		return false;
	}

	// Initialize the skysphere object.
	result = m_SkySphere->Initialize(m_D3D->GetDevice(), "../Engine/data/Skysphere/Version 1 (rotated)/quadsphere7.txt", L"../Engine/data/Skysphere/Version 1 (rotated)/final.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the skysphere.", L"Error", MB_OK);
		return false;
	}

	// Create the sky plane object.
	m_SkyPlane = new SkyPlaneClass;
	if (!m_SkyPlane)
	{
		return false;
	}

	// Initialize the sky plane object.
	result = m_SkyPlane->Initialize(m_D3D->GetDevice(), L"../Engine/data/Clouds/cloud.dds", L"../Engine/data/Clouds/perturb.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sky plane object.", L"Error", MB_OK);
		return false;
	}

	// Create the scene
	m_MyScene = new MyScene(m_D3D->GetDevice(), m_ShaderManager);
	if (!m_MyScene)
	{
		return false;
	}

	// Initialize the scene
	result = m_MyScene->InitializeObjects();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the scene.", L"Error", MB_OK);
		return false;
	}


	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the scene.
	if (m_MyScene)
	{
		m_MyScene->ShutdownObjects();
		delete m_MyScene;
		m_MyScene = 0;
	}

	// Release the sky plane object.
	if (m_SkyPlane)
	{
		m_SkyPlane->Shutdown();
		delete m_SkyPlane;
		m_SkyPlane = 0;
	}

	// Release the skysphere object.
	if(m_SkySphere)
	{
		m_SkySphere->Shutdown();
		delete m_SkySphere;
		m_SkySphere = 0;
	}

	// Release the sound object.
	if (m_Sound)
	{
		m_Sound->Shutdown();
		delete m_Sound;
		m_Sound = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Do the sky plane frame processing.
	m_SkyPlane->Frame();

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown;
	bool slowerKeyDown;
	bool fasterKeyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the keyboard input.
	slowerKeyDown = m_Input->IsCtrlPressed();
	fasterKeyDown = m_Input->IsShiftPressed();

	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->LookDownward(keyDown);

	keyDown = m_Input->IsWPressed();
	m_Position->MoveForward(keyDown, slowerKeyDown, fasterKeyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveLeft(keyDown, slowerKeyDown, fasterKeyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->MoveBackward(keyDown, slowerKeyDown, fasterKeyDown);

	keyDown = m_Input->IsDPressed();
	m_Position->MoveRight(keyDown, slowerKeyDown, fasterKeyDown);

	keyDown = m_Input->IsPgUpPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = m_Input->IsEnterPressed();
	if (keyDown)
	{
		// If the camera type is ready for switching
		if (m_CameraTypeSwitchable)
		{
			m_Sound->StopWaveFile();
			// Switching the camera type/loading a wave file based on the camera's type
			if (m_CameraType == GraphicsClass::CameraType::Free)
			{
				m_CameraType = GraphicsClass::CameraType::Attached;
				m_Sound->LoadWaveFile("../Engine/data/Music/Crab Rave.wav");
			}
			else if (m_CameraType == GraphicsClass::CameraType::Attached)
			{
				m_CameraType = GraphicsClass::CameraType::Free;
				m_Sound->LoadWaveFile("../Engine/data/Music/Beach Party.wav");
			}
			m_Sound->PlayWaveFile(true);
		}

		m_CameraTypeSwitchable = false;
	}
	else
	{
		m_CameraTypeSwitchable = true;
	}

	// Handle the mouse input.
	m_Position->MouseUpdate(
		m_Input->GetMouseXDelta() * m_Input->GetMouseXSensitivity(),
		m_Input->GetMouseYDelta() * m_Input->GetMouseYSensitivity());
	m_Input->UpdateOldMouse();

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Reset the cursor position.
	m_Input->ResetCursorPosition();

	/* If the camera type is 'Attached',
	set the camera's position to the position of a chosen object,
	and lock the camera's Y rotation to look at a second chosen object. */
	if (m_CameraType == GraphicsClass::CameraType::Attached)
	{
		ObjectClass* attachObject = m_MyScene->GetWorldObject("Gull 1");
		float yOffset = 2.5f;
		float xRotation = 25.0f;
		if (attachObject)
		{
			XMFLOAT3 worldTranslation = attachObject->GetWorldTranslation();
			posX = worldTranslation.x;
			posY = worldTranslation.y + yOffset;
			posZ = worldTranslation.z;
		}
		ObjectClass* lookAtObject = m_MyScene->GetWorldObject("Island");
		if (lookAtObject)
		{
			XMVECTOR attachToLookAt = lookAtObject->GetWorldTranslationVector() - attachObject->GetWorldTranslationVector();
			attachToLookAt = XMVector3Normalize(attachToLookAt);

			rotX = xRotation;
			rotY = XMConvertToDegrees(atan2(XMVectorGetX(attachToLookAt), XMVectorGetZ(attachToLookAt)));
		}
	}

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);
	

	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix, scaleMatrix;
	bool result;

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Setup the translation of the skysphere.
	XMFLOAT3 cameraPosition = m_Camera->GetPosition();
	translateMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);
	scaleMatrix = XMMatrixScaling(-1000.0f, -1000.0f, -1000.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleMatrix);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Turning off the culling/z buffer in preparation for rendering the skysphere and sky plane
	m_D3D->TurnOffCulling();
	m_D3D->TurnZBufferOff();

	// Render the skysphere using the texture shader.
	m_SkySphere->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_SkySphere->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_SkySphere->GetTexture());
	if(!result)
	{
		return false;
	}

	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Setup the translation of the sky plane.
	float skyPlaneYOffset = 250.0f;
	translateMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y + skyPlaneYOffset, cameraPosition.z);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Enable additive blending so the clouds blend with the skysphere color.
	m_D3D->EnableSecondBlendState();
	// Render the sky plane using the sky plane shader.
	m_SkyPlane->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderSkyPlaneShader(m_D3D->GetDeviceContext(), m_SkyPlane->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_SkyPlane->GetCloudTexture(), m_SkyPlane->GetPerturbTexture(), m_SkyPlane->GetTranslation(), m_SkyPlane->GetScale(),
		m_SkyPlane->GetBrightness());
	if (!result)
	{
		return false;
	}
	m_D3D->TurnOffAlphaBlending();

	// Turning the culling/z buffer back on now that the skysphere and sky plane have been rendered
	m_D3D->TurnOnCulling();
	m_D3D->TurnZBufferOn();

	// Render the scene
	result = m_MyScene->RenderObjects(m_D3D, m_Camera, &worldMatrix, &viewMatrix, &projectionMatrix, m_Light);
	if (!result)
	{
		return false;
	}


	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}
