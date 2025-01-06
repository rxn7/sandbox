#include "Camera.h"
#include <iostream>
#include "glm/gtx/rotate_vector.hpp"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) {
	SetPosition(pos);
	SetForward(glm::vec3(0, 0, -1));
	m_up = glm::vec3(0, 1, 0);
	
	SetPerspectiveMatrix(fov, aspect, zNear, zFar);
}

void Camera::SetPosition(const glm::vec3& pos) {
	m_position = pos;
	RecalculateViewMatrix();
}

void Camera::Move(const glm::vec3& dir){
	m_position += dir;
	RecalculateViewMatrix();
}

void Camera::RecalculateViewMatrix() {
	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);
}

void Camera::RecalculateProjectionMatrix() {
	m_projMatrix = glm::perspective(glm::radians(m_fov), m_aspect, m_zNear, m_zFar);
}

void Camera::SetAspect(float aspect) {
	m_aspect = aspect;

	RecalculateProjectionMatrix();
}

void Camera::SetPerspectiveMatrix(float fov, float aspect, float zNear, float zFar) {
	m_fov = fov;
	m_aspect = aspect;
	m_zNear = zNear;
	m_zFar = zFar;

	RecalculateProjectionMatrix();
}

void Camera::OnMouseMovement(double xOffset, double yOffset) {
	m_pitch += yOffset;
	m_yaw += xOffset;
	
	if (m_pitch > 89.0f) m_pitch = 89.0f;
	if (m_pitch < -89.0f) m_pitch = -89.0f;

	glm::vec3 forward;
	forward.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	forward.y = sin(glm::radians(m_pitch));
	forward.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
	SetForward(forward);
}

void Camera::SetForward(const glm::highp_vec3& forward) {
	m_forward = forward;
	RecalculateViewMatrix();
}

void Camera::SetFov(float fov) {
	m_fov = fov;
	RecalculateProjectionMatrix();
}

float Camera::GetZfar() const {
	return m_zFar;
}

float Camera::GetZnear() const {
	return m_zNear;
}

float Camera::GetAspect() const {
	return m_aspect;
}

float Camera::GetFov() const {
	return m_fov;
}

glm::mat4 Camera::GetProjectionMatrix() const {
	return m_projMatrix;
}

glm::mat4 Camera::GetViewMatrix() const {
	return m_viewMatrix;
}

glm::vec3 Camera::GetPosition() const {
	return m_position;
}

glm::vec3 Camera::GetForward() const {
	return m_forward;
}

glm::vec3 Camera::GetLeft() const { 
	return glm::normalize(glm::cross(m_up, m_forward)); 
}

glm::vec3 Camera::GetRight() const { 
	return glm::normalize(glm::cross(m_forward, m_up)); 
}
