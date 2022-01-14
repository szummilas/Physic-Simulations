#pragma once
#include "ofMain.h"

class Particle {
public:

	// ----- CONSTRUCTORS -----

	Particle();		// Default constructor
	~Particle();	// Destructor

	Particle(Particle& a_particle);

	Particle(glm::vec3 a_emitterPos, glm::vec3 a_direction,
		float a_velocity, float a_size, glm::vec4 a_startColor, glm::vec4 a_endColor, float a_lifeSpan);

	// ----- GETTERS -----

	glm::vec3 getPosition() {
		return m_position;
	}

	glm::vec3 getDirection() {
		return m_direction;
	}

	glm::vec3 getVelocity() {
		return m_velocity;
	}

	float getRadius() {
		return radius;
	}

	glm::vec4 getColor() {
		return m_color;
	}

	glm::vec4 getStartColor() {
		return m_startColor;
	}

	glm::vec4 getMidColor() {
		return m_midColor;
	}

	glm::vec4 getEndColor() {
		return m_endColor;
	}

	// ----- SETTERS -----

private:
	glm::vec3 m_position;
	glm::vec3 m_direction;
	glm::vec3 m_velocity;
	float radius;

	glm::vec4 m_color;
	glm::vec4 m_startColor;
	glm::vec4 m_midColor;
	glm::vec4 m_endColor;

};

