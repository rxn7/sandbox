#pragma once

#include "Libs.h"

class Transform {
public:
	Transform();
	Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
	
public:
	inline glm::mat4 getMatrix() const {
		glm::mat4 posMatrix = glm::translate(m_pos);
		glm::mat4 rotMatrixX = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotMatrixY = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotMatrixZ = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(m_scale);
	
		glm::mat4 rotMatrix = rotMatrixZ * rotMatrixY * rotMatrixX;
		
		return posMatrix * rotMatrix * scaleMatrix;
	}

	inline glm::vec3& getPos() { return m_pos; }
	inline glm::vec3& getRot() { return m_rot; }
	inline glm::vec3& getScale() { return m_scale; }

	inline void setPos(const glm::vec3& pos) { m_pos = pos; }
	inline void setRot(const glm::vec3& rot) { m_pos = rot; }
	inline void setScale(const glm::vec3& scale) { m_pos = scale; }

private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};

