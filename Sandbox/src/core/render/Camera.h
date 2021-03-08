#pragma once

#include "../Libs.h"

class Camera {
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
		m_fov = fov;
		m_zNear = zNear;
		m_zFar = zFar;
		
		m_perspective = glm::perspective(fov, aspect, zNear, zFar);
		m_position = pos;
		m_forward = glm::vec3(0,0,-1);
		m_up = glm::vec3(0,1,0);

		update();
	}
	
public:
	inline glm::vec3 getRight() const { return glm::normalize(glm::cross(m_forward, m_up)); }
	inline glm::vec3 getLeft() const { return glm::normalize(glm::cross(m_up, m_forward)); }
	inline glm::vec3 getForward() const { return m_forward; }
	
	inline glm::vec3 getPosition() const { return m_position; }
	inline glm::mat4 getViewProjection() const { return m_viewProj; }

	void update();
	void setPos(const glm::vec3& pos);
	void move(const glm::vec3& dir);
	void rotate(float yaw, float pitch);
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