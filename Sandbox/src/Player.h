#pragma once
#include "core/render/Camera.h"
#include "glm/gtx/compatibility.hpp"

#define MAX_SPEED = 100
#define DRAG = 30

class Player {
public:
	Player(const Camera camera);
	virtual ~Player();

public:
	void update(float dt);

	inline void resetVelocity() { m_velocity = glm::vec3(0); }

	inline Camera& getCamera() const { return *mp_camera; }

	inline glm::vec3 getPosition() const { return m_position; }

	inline glm::vec3 getVeloctiy() const { return m_velocity; }
	
	inline glm::vec3 getTargetVelocity() const { return m_targetVelocity; }

	inline void setTargetVelocity(const glm::vec3& val) { m_targetVelocity = val; }

private:
	Camera* mp_camera;
	
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	glm::vec3 m_targetVelocity;
};

