#pragma once
#include "emitter.h"

class ParticleEffect
{
public:
	struct Particle {
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 friction;
		ofColor color;
		float age;
		float lifetime;

		float uniqueVal;
		float drag;
	};

	std::vector<Particle> particles;

	void setup(int& numOfParticles, Emitter& emitter);
};

class Snow : public ParticleEffect {
public:
	void draw(std::vector<Particle>& particles);
	void update(std::vector<Particle>& particles, Emitter& emitter, float& dt);
};

class Matrix : public ParticleEffect {
public:
	void draw(std::vector<Particle>& particles);
	void update(std::vector<Particle>& particles, Emitter& emitter, float& dt);
};

class Boom : public ParticleEffect {
public:
	void setup(std::vector<Particle>& particles, Emitter& emitter);
	void draw(std::vector<Particle>& particles);
	void update(std::vector<Particle>& particles, Emitter& emitter, float& dt);
};

class CustomEffect : public ParticleEffect {

};


