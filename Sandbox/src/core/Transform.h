#pragma once

#include "Libs.h"

class Transform {
public:
	Transform();
	Transform(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& scale);
	
public:
	/// <summary> Calculates the position matrix, rotation matrix and scale matrix and returns posMat*rotMat*scaleMat. </summary>
	inline glm::mat4 getMatrix() const {
		glm::mat4 posMatrix = glm::translate(m_pos);
		glm::mat4 rotMatrixX = glm::rotate(m_rot.x, glm::vec3(1, 0, 0));
		glm::mat4 rotMatrixY = glm::rotate(m_rot.y, glm::vec3(0, 1, 0));
		glm::mat4 rotMatrixZ = glm::rotate(m_rot.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(m_scale);
		
		glm::mat4 rotMatrix = rotMatrixZ * rotMatrixY * rotMatrixX;
		
		return posMatrix * rotMatrix * scaleMatrix;
	}

	/// <summary> Returns the reference to m_pos. </summary>
	inline glm::vec3& getPos() { return m_pos; }

	/// <summary> Returns the reference to m_rot. </summary>
	inline glm::vec3& getRot() { return m_rot; }
	
	/// <summary> Returns the reference to m_scale. </summary>
	inline glm::vec3& getScale() { return m_scale; }

	/// <summary> Sets the m_pos value to the specified one. </summary>
	inline void setPos(const glm::vec3& pos) { m_pos = pos; }

	/// <summary> Sets the m_rot value to the specified one. </summary>
	inline void setRot(const glm::vec3& rot) { m_rot = rot; }
	
	/// <summary> Sets the m_scale value to the specified one. </summary>
	inline void setScale(const glm::vec3& scale) { m_scale = scale; }

private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};

