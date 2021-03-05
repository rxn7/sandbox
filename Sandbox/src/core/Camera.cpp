#include "Camera.h"

void Camera::setPos(const glm::vec3& pos) {
	m_position = pos;
}

void Camera::move(const glm::vec3& dir){
	m_position += dir;
}