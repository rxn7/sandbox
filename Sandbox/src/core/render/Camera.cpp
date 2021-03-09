#include "Camera.h"
#include <iostream>
#include "glm/gtx/rotate_vector.hpp"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
	m_fov = fov;
	m_zNear = zNear;
	m_zFar = zFar;

	m_perspective = glm::perspective(fov, aspect, zNear, zFar);
	m_position = pos;
	m_forward = glm::vec3(0, 0, -1);
	m_up = glm::vec3(0, 1, 0);

	update();
}

void Camera::setPos(const glm::vec3& pos) {
	m_position = pos;
	update();
}

void Camera::move(const glm::vec3& dir){
	m_position += dir;
	update();
}

void Camera::update() {
	m_viewProj = m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
}

void Camera::recalculatePerspective(int width, int height) {
	m_perspective = glm::perspective(glm::radians(m_fov), (float)width/(float)height, m_zNear, m_zFar);
}

void Camera::rotate(float x, float y) {
	if (x == 0 && y == 0) return;

	m_yaw += x;
	m_pitch += y;

	/*Limiting the rotation*/
	if (m_pitch > 89.95f)			m_pitch = 89.95f;
	else if (m_pitch < -89.95f)		m_pitch = -89.95f;
	if (m_yaw > 360)				m_yaw -= 360;
	else if (m_yaw < -360)			m_yaw += 360;

	glm::vec3 forward;
	forward.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	forward.y = sin(glm::radians(m_pitch));
	forward.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_forward = glm::normalize(forward);

	update();
}