#pragma once

#include "../Libs.h"

class Camera {
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	
public:
	/// <summary> Returns normalized cross product of camera's forward and up direction. </summary>
	inline glm::vec3 getRight() const		    { return glm::normalize(glm::cross(m_forward, m_up)); }

	/// <summary> Returns normalized cross product of camera's up and forward direction. </summary>
	inline glm::vec3 getLeft() const			{ return glm::normalize(glm::cross(m_up, m_forward)); }
	
	/// <summary> Returns m_forward. </summary>
	inline glm::vec3 getForward() const			{ return m_forward; }
	
	/// <summary> Returns m_position. </summary>
	inline glm::vec3 getPosition() const		{ return m_position; }
	
	/// <summary> Returns m_viewProj. </summary>
	inline glm::mat4 getViewMatrix() const	{ return m_viewMatrix; }

	/// <summary> Returns m_projMatrix. </summary>
	inline glm::mat4 getProjMatrix() const { return m_projMatrix; }

	/// <summary Retruns m_fov. </summary>
	inline float getFov() const { return m_fov; }

	/// <summary> returns m_aspect. </summary>
	inline float getAspect() const { return m_aspect; }

	/// <summary> returns m_zNear. </summary>
	inline float getZnear() const { return m_zNear; }

	/// <summary> returns m_zFar. </summary>
	inline float getZfar() const { return m_zFar; }

	/// <summary> Recalculates camera projection matrix. </summary>
	void recalculateProjectionMatrix();

	/// <summary> Recalculates camera view matrix. </summary>
	void recalculateViewMatrix();
	
	/// <summary> Sets camera position to specified value.. </summary>
	void setPosition(const glm::vec3& pos);
		
	/// <summary> Sets m_ratio to specified value. </summary>
	void setAspect(float aspect);

	/// <summary> Sets m_forward to specified value. </summary>
	void setForward(const glm::highp_vec3& forward);

	/// <summary> Sets m_fov to specified value. </summary>
	void setFov(float fov);

	/// <summary> Moves camera by the specified offset. </summary>
	void move(const glm::vec3& dir);

	/// <summary> Sets m_fov to fov, m_aspect to aspect, m_zNear to zNear, m_zFar to zFar. </summary>
	void setPerspectiveMatrix(float fov, float aspect, float zNear, float zFar);

	/// <summary> Rotates the camera based on mouse movement. </summary>
	void onMouseMovement(double xOffset, double yOffset);

private:
	glm::mat4 m_projMatrix;
	//glm::mat4 m_viewProjMatrix;
	glm::mat4 m_viewMatrix;
	glm::vec3 m_position;
	glm::highp_vec3 m_forward;
	glm::vec3 m_up;

	float m_zNear;
	float m_zFar;
	float m_aspect;
	double m_yaw=0, m_pitch=0;
	float m_fov;
};