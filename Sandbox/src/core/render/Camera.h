#pragma once

#include "../Libs.h"

class Camera {
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	
public:
	/// <summary> Returns the normalized cross product of camera's forward and up direction. </summary>
	inline glm::vec3 getRight() const		    { return glm::normalize(glm::cross(m_forward, m_up)); }

	/// <summary> Returns the normalized cross product of camera's up and forward direction. </summary>
	inline glm::vec3 getLeft() const			{ return glm::normalize(glm::cross(m_up, m_forward)); }
	
	/// <summary> Returns the m_forward. </summary>
	inline glm::vec3 getForward() const			{ return m_forward; }
	
	/// <summary> Returns the m_position. </summary>
	inline glm::vec3 getPosition() const		{ return m_position; }
	
	/// <summary> Returns the m_viewProj. </summary>
	inline glm::mat4 getViewProjection() const	{ return m_viewProj; }
	
	/// <summary> Updates the camera view projection </summary>
	void update();

	/// <summary> Sets the camera position to specified vec3 and calls update(). </summary>
	void setPos(const glm::vec3& pos);
	
	/// <summary> Moves the camera by the specified offset and calls update(). </summary>
	void move(const glm::vec3& dir);
	
	/// <summary> Rotates the camera by the specified yaw and pitch and calls update(). </summary>
	void rotate(float yaw, float pitch);
	
	/// <summary> Recalculates the perspective projection. </summary>
	void recalculatePerspective(int width, int height);

public:
	float m_yaw=0, m_pitch=0;
	float m_fov;

private:
	glm::mat4 m_viewProj;
	glm::mat4 m_perspective;
	glm::vec3 m_position;
	glm::vec3 m_forward;
	glm::vec3 m_up;
	float m_zNear;
	float m_zFar;
};