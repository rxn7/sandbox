#include "Player.h"
#include "core/Math.h"

Player::Player(const Camera camera) {
	mp_camera = new Camera(camera.getPosition(), camera.getFov(), camera.getAspect(), camera.getZnear(), camera.getZfar());
	m_position = camera.getPosition();
}

Player::~Player() {
	delete mp_camera;
}

void Player::update(float dt) {
	/*TODO: Lerp this. */
	m_velocity = m_targetVelocity;

	m_position += m_velocity;
	mp_camera->setPosition(m_position);
}
