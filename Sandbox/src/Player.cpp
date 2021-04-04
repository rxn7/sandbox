#include "Player.h"

Player::Player(const Camera camera) {
	mp_camera = new Camera(camera.GetPosition(), camera.GetFov(), camera.GetAspect(), camera.GetZnear(), camera.GetZfar());
	m_position = camera.GetPosition();
}

Player::~Player() {
	delete mp_camera;
}

void Player::Update(float dt) {
	/*TODO: Lerp this. */
	m_velocity = m_targetVelocity;

	m_position += m_velocity;
	mp_camera->SetPosition(m_position);
}

void Player::ResetVelocity() {
	m_velocity = glm::vec3();
	m_targetVelocity = glm::vec3();
}

void Player::SetTargetVelocity(const glm::vec3& val) {
	m_targetVelocity = val;
}

Camera& Player::GetCamera() const { 
	return *mp_camera; 
}

glm::vec3 Player::GetPosition() const { 
	return m_position; 
}

glm::vec3 Player::GetVeloctiy() const {
	return m_velocity;
}

glm::vec3 Player::GetTargetVelocity() const {
	return m_targetVelocity;
}