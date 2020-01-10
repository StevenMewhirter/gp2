#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "camera.h"

struct Transform
{
public:
	Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
	{
		this->position = position;      //sets the position,rotation and scale within the game scene as vector 3s
		this->rotation = rotation;
		this->scale = scale;
	}

	inline glm::mat4 GetModelDimensions() const  //sets the constraints of a models transform
	{
		glm::mat4 positionMat = glm::translate(position);
		glm::mat4 scaleMat = glm::scale(scale);
		glm::mat4 rotationX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotationY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotationZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotationMat = rotationX * rotationY * rotationZ;

		return positionMat * rotationMat * scaleMat;
	}

	/*inline glm::mat4 GetMVP(const Camera& camera) const
	{
		glm::mat4 VP = camera.GetViewProjection();
		glm::mat4 M = GetModel();

		return VP * M;//camera.GetViewProjection() * GetModel();
	}*/

	inline glm::vec3* GetPosition() { return &position; } //getters
	inline glm::vec3* GetRotation() { return &rotation; }
	inline glm::vec3* GetScale() { return &scale; }

	inline void SetPosition(glm::vec3& position) { this->position = position; } // setters
	inline void SetRotation(glm::vec3& rotation) { this->rotation = rotation; }
	inline void SetScale(glm::vec3& scale) { this->scale = scale; }
protected:
private:
	glm::vec3 position;//set to private
	glm::vec3 rotation;
	glm::vec3 scale;
};


