////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: PositionClass
////////////////////////////////////////////////////////////////////////////////
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void GetPosition(float&, float&, float&);
	void SetPosition(float, float, float);
	void GetRotation(float&, float&, float&);
	void SetRotation(float, float, float);

	void SetFrameTime(float);

	void MoveForward(bool, bool, bool);
	void MoveBackward(bool, bool, bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void MoveLeft(bool, bool, bool);
	void MoveRight(bool, bool, bool);
	void TurnLeft(bool);
	void TurnRight(bool);
	void LookUpward(bool);
	void LookDownward(bool);
	void MouseUpdate(float, float);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;

	float m_movementSpeedIncrease;
	float m_movementSpeedDecrease;
	float m_movementSpeedCap;
	float m_movementSpeedLowerCap;
	float m_movementSpeedHigherCap;

	float m_forwardSpeed, m_backwardSpeed;
	float m_leftSpeed, m_rightSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;
};

#endif