#include "Camera.h"
#include <iostream>
#include "glm/gtx/rotate_vector.hpp"

void Camera::setPos(const glm::vec3& pos) {
	m_position = pos;
}

void Camera::move(const glm::vec3& dir){
	m_position += dir;
}

void Camera::recalculatePerspective(int width, int height) {
	m_perspective = glm::perspective(m_fov, (float)width / (float)height, m_zNear, m_zFar);
}

void Camera::rotate(float x, float y) {
	if (x == 0 && y == 0) return;

	m_yaw += x;
	m_pitch += y;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;

	else if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	glm::vec3 forward;
	forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	forward.y = sin(glm::radians(m_pitch));		
	forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));	

	m_forward = glm::normalize(forward);
}