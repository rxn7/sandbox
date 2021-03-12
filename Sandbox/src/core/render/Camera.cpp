#include "Camera.h"
#include <iostream>
#include "glm/gtx/rotate_vector.hpp"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
	setPosition(pos);
	setForward(glm::vec3(0, 0, -1));
	m_up = glm::vec3(0, 1, 0);
	
	setPerspectiveMatrix(fov, aspect, zNear, zFar);
}

void Camera::setPosition(const glm::vec3& pos) {
	m_position = pos;
	recalculateViewMatrix();
}

void Camera::move(const glm::vec3& dir){
	m_position += dir;
	recalculateViewMatrix();
}

void Camera::recalculateViewMatrix() {
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
}

void Camera::recalculateProjectionMatrix() {
	m_projMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_zNear, m_zFar);
}

void Camera::setAspect(float aspect) {
	m_aspect = aspect;

	recalculateProjectionMatrix();
}

void Camera::setPerspectiveMatrix(float fov, float aspect, float zNear, float zFar) {
	m_fov = fov;
	m_aspect = aspect;
	m_zNear = zNear;
	m_zFar = zFar;

	recalculateProjectionMatrix();
}

void Camera::onMouseMovement(double xOffset, double yOffset) {
	m_pitch += yOffset;
	m_yaw += xOffset;
	
	if (m_pitch > 89.0f) m_pitch = 89.0f;
	if (m_pitch < -89.0f) m_pitch = -89.0f;

	glm::vec3 forward;
	forward.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	forward.y = sin(glm::radians(m_pitch));
	forward.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
	setForward(forward);
}

void Camera::setForward(const glm::highp_vec3& forward) {
	m_forward = forward;
	recalculateViewMatrix();
}

void Camera::setFov(float fov) {
	m_fov = fov;
	recalculateProjectionMatrix();
}
