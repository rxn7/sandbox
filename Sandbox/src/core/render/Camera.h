#pragma once

#include "../Libs.h"

class Camera {
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
	
public:
	/// <summary> Returns normalized cross product of camera's forward and up direction. </summary>
	glm::vec3 GetRight() const;

	/// <summary> Returns normalized cross product of camera's up and forward direction. </summary>
	glm::vec3 GetLeft() const;
	
	/// <summary> Returns the forward direction of the camrea. </summary>
	glm::vec3 GetForward() const;
	
	/// <summary> Returns the position of the camera. </summary>
	glm::vec3 GetPosition() const;
	
	/// <summary> Returns view matrix of this camera. </summary>
	glm::mat4 GetViewMatrix() const;

	/// <summary> Returns projection matrix of this camera. </summary>
	glm::mat4 GetProjectionMatrix() const;

	/// <summary Retruns the fov of the camera. </summary>
	float GetFov() const;

	/// <summary> returns the aspect of the camera. </summary>
	float GetAspect() const;

	/// <summary> returns the zNear of the camera. </summary>
	float GetZnear() const;

	/// <summary> returns the zFar of the camera. </summary>
	float GetZfar() const;

	/// <summary> Recalculates camera projection matrix. </summary>
	void RecalculateProjectionMatrix();

	/// <summary> Recalculates camera view matrix. </summary>
	void RecalculateViewMatrix();
	
	/// <summary> Sets camera position to specified value.. </summary>
	void SetPosition(const glm::vec3& pos);
		
	/// <summary> Sets m_ratio to specified value. </summary>
	void SetAspect(float aspect);

	/// <summary> Sets m_forward to specified value. </summary>
	void SetForward(const glm::highp_vec3& forward);

	/// <summary> Sets m_fov to specified value. </summary>
	void SetFov(float fov);

	/// <summary> Moves camera by the specified offset. </summary>
	void Move(const glm::vec3& dir);

	/// <summary> Sets m_fov to fov, m_aspect to aspect, m_zNear to zNear, m_zFar to zFar. </summary>
	void SetPerspectiveMatrix(float fov, float aspect, float zNear, float zFar);

	/// <summary> Rotates the camera based on mouse movement. </summary>
	void OnMouseMovement(double xOffset, double yOffset);

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