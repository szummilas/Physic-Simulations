#pragma once
#include "ofMain.h"


class Emitter : public ofNode
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

	glm::vec3 zeroVec;

	Emitter();
	void setup(int numOfParticles);
	void draw();
	void update();
};


