////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "positionclass.h"
#include "directxmath.h"

using namespace DirectX;


PositionClass::PositionClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 0.0f;

	m_movementSpeedIncrease = 0.001f;
	m_movementSpeedDecrease = 0.0007f;
	m_movementSpeedCap = 0.03f;
	m_movementSpeedLowerCap = 0.015f;
	m_movementSpeedHigherCap = 0.06f;

	m_forwardSpeed   = 0.0f;
	m_backwardSpeed  = 0.0f;
	m_leftSpeed      = 0.0f;
	m_rightSpeed     = 0.0f;
	m_upwardSpeed    = 0.0f;
	m_downwardSpeed  = 0.0f;
	m_leftTurnSpeed  = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed    = 0.0f;
	m_lookDownSpeed  = 0.0f;
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}


void PositionClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void PositionClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


void PositionClass::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}


void PositionClass::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}


void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}


void PositionClass::MoveForward(bool keydown, bool slowerkeydown, bool fasterkeydown)
{
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_forwardSpeed += m_frameTime * m_movementSpeedIncrease;

		if (slowerkeydown && !fasterkeydown)
		{
			if (m_forwardSpeed > (m_frameTime * m_movementSpeedLowerCap))
			{
				m_forwardSpeed = m_frameTime * m_movementSpeedLowerCap;
			}
		}
		else if (fasterkeydown && !slowerkeydown)
		{
			if (m_forwardSpeed > (m_frameTime * m_movementSpeedHigherCap))
			{
				m_forwardSpeed = m_frameTime * m_movementSpeedHigherCap;
			}
		}
		else if (m_forwardSpeed > (m_frameTime * m_movementSpeedCap))
		{
			m_forwardSpeed = m_frameTime * m_movementSpeedCap;
		}
	}
	else
	{
		m_forwardSpeed -= m_frameTime * m_movementSpeedDecrease;

		if (m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	// Update the position.
	m_positionX += (sinf(XMConvertToRadians(m_rotationY)) * cosf(XMConvertToRadians(m_rotationX))) * m_forwardSpeed;
	m_positionY -= (sinf(XMConvertToRadians(m_rotationX))) * m_forwardSpeed;
	m_positionZ += (cosf(XMConvertToRadians(m_rotationY)) * cosf(XMConvertToRadians(m_rotationX))) * m_forwardSpeed;

	return;
}


void PositionClass::MoveBackward(bool keydown, bool slowerkeydown, bool fasterkeydown)
{
	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_backwardSpeed += m_frameTime * m_movementSpeedIncrease;

		if (slowerkeydown && !fasterkeydown)
		{
			if (m_backwardSpeed > (m_frameTime * m_movementSpeedLowerCap))
			{
				m_backwardSpeed = m_frameTime * m_movementSpeedLowerCap;
			}
		}
		else if (fasterkeydown && !slowerkeydown)
		{
			if (m_backwardSpeed > (m_frameTime * m_movementSpeedHigherCap))
			{
				m_backwardSpeed = m_frameTime * m_movementSpeedHigherCap;
			}
		}
		else if (m_backwardSpeed > (m_frameTime * m_movementSpeedCap))
		{
			m_backwardSpeed = m_frameTime * m_movementSpeedCap;
		}
	}
	else
	{
		m_backwardSpeed -= m_frameTime * m_movementSpeedDecrease;
		
		if (m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	// Update the position.
	m_positionX -= (sinf(XMConvertToRadians(m_rotationY)) * cosf(XMConvertToRadians(m_rotationX))) * m_backwardSpeed;
	m_positionY += (sinf(XMConvertToRadians(m_rotationX))) * m_backwardSpeed;
	m_positionZ -= (cosf(XMConvertToRadians(m_rotationY)) * cosf(XMConvertToRadians(m_rotationX))) * m_backwardSpeed;

	return;
}


void PositionClass::MoveUpward(bool keydown)
{
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_upwardSpeed += m_frameTime * m_movementSpeedIncrease;

		if(m_upwardSpeed > (m_frameTime * m_movementSpeedCap))
		{
			m_upwardSpeed = m_frameTime * m_movementSpeedCap;
		}
	}
	else
	{
		m_upwardSpeed -= m_frameTime * m_movementSpeedDecrease;

		if(m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY += m_upwardSpeed;

	return;
}


void PositionClass::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_downwardSpeed += m_frameTime * m_movementSpeedIncrease;

		if(m_downwardSpeed > (m_frameTime * m_movementSpeedCap))
		{
			m_downwardSpeed = m_frameTime * m_movementSpeedCap;
		}
	}
	else
	{
		m_downwardSpeed -= m_frameTime * m_movementSpeedDecrease;

		if(m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_positionY -= m_downwardSpeed;

	return;
}


void PositionClass::MoveLeft(bool keydown, bool slowerkeydown, bool fasterkeydown)
{
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_leftSpeed += m_frameTime * m_movementSpeedIncrease;


		if (slowerkeydown && !fasterkeydown)
		{
			if (m_leftSpeed > (m_frameTime * m_movementSpeedLowerCap))
			{
				m_leftSpeed = m_frameTime * m_movementSpeedLowerCap;
			}
		}
		else if (fasterkeydown && !slowerkeydown)
		{
			if (m_leftSpeed > (m_frameTime * m_movementSpeedHigherCap))
			{
				m_leftSpeed = m_frameTime * m_movementSpeedHigherCap;
			}
		}
		else if (m_leftSpeed > (m_frameTime * m_movementSpeedCap))
		{
			m_leftSpeed = m_frameTime * m_movementSpeedCap;
		}
	}
	else
	{
		m_leftSpeed -= m_frameTime * m_movementSpeedDecrease;

		if (m_leftSpeed < 0.0f)
		{
			m_leftSpeed = 0.0f;
		}
	}

	// Update the position.
	m_positionX -= cosf(XMConvertToRadians(m_rotationY)) * m_leftSpeed;
	m_positionZ += sinf(XMConvertToRadians(m_rotationY)) * m_leftSpeed;

	return;
}

void PositionClass::TurnLeft(bool keydown)
{
	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;

		if(m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime* 0.005f;

		if(m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY -= m_leftTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if(m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}


void PositionClass::MoveRight(bool keydown, bool slowerkeydown, bool fasterkeydown)
{
	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if (keydown)
	{
		m_rightSpeed += m_frameTime * m_movementSpeedIncrease;

		if (slowerkeydown && !fasterkeydown)
		{
			if (m_rightSpeed > (m_frameTime * m_movementSpeedLowerCap))
			{
				m_rightSpeed = m_frameTime * m_movementSpeedLowerCap;
			}
		}
		else if (fasterkeydown && !slowerkeydown)
		{
			if (m_rightSpeed > (m_frameTime * m_movementSpeedHigherCap))
			{
				m_rightSpeed = m_frameTime * m_movementSpeedHigherCap;
			}
		}
		else if (m_rightSpeed > (m_frameTime * m_movementSpeedCap))
		{
			m_rightSpeed = m_frameTime * m_movementSpeedCap;
		}
	}
	else
	{
		m_rightSpeed -= m_frameTime * m_movementSpeedDecrease;

		if (m_rightSpeed < 0.0f)
		{
			m_rightSpeed = 0.0f;
		}
	}

	// Update the position.
	m_positionX += cosf(XMConvertToRadians(m_rotationY)) * m_rightSpeed;
	m_positionZ -= sinf(XMConvertToRadians(m_rotationY)) * m_rightSpeed;

	return;
}

void PositionClass::TurnRight(bool keydown)
{
	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;

		if(m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime* 0.005f;

		if(m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY += m_rightTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if(m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;
}


void PositionClass::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.01f;

		if(m_lookUpSpeed > (m_frameTime * 0.15f))
		{
			m_lookUpSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookUpSpeed -= m_frameTime* 0.005f;

		if(m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX -= m_lookUpSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}

	return;
}


void PositionClass::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookDownSpeed += m_frameTime * 0.01f;

		if(m_lookDownSpeed > (m_frameTime * 0.15f))
		{
			m_lookDownSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookDownSpeed -= m_frameTime* 0.005f;

		if(m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX += m_lookDownSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}

	return;
}

void PositionClass::MouseUpdate(float mouseX, float mouseY)
{
	// Keep the x rotation maximum 90 degrees.
	if ((m_rotationX + mouseY) > 90.0f)
	{
		m_rotationX = 90.0f;
	}
	else if ((m_rotationX + mouseY) < -90.0f)
	{
		m_rotationX = -90.0f;
	}
	else
	{
		m_rotationX += mouseY;
	}

	// Keeping the y rotation within 360 degrees.
	while (m_rotationY < -180.0f)
	{
		m_rotationY += 360.0f;
	}
	while (m_rotationY > 180.0f)
	{
		m_rotationY -= 360.0f;
	}

	// Update the rotation.
	m_rotationY += mouseX;
}
