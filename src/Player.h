#pragma once
#include "core/render/Camera.h"

#define MAX_SPEED = 100
#define DRAG = 30

class Player {
public:
	Player(const Camera camera);
	virtual ~Player();

public:
	/// <summary> Calculates the velocity and position. </summary>
	void Update(float dt);

	void ResetVelocity();

	Camera& GetCamera() const;

	glm::vec3 GetPosition() const;

	glm::vec3 GetVeloctiy() const;
	
	glm::vec3 GetTargetVelocity() const;

	void SetTargetVelocity(const glm::vec3& val);

private:
	Camera* mp_camera;
	
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	glm::vec3 m_targetVelocity;
};

