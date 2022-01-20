#pragma once
#include "ofMain.h"

class Point {
public:
	
	Point();

	glm::vec2 position;
	glm::vec2 lastPosition;
	glm::vec2 nextPosition;

	glm::vec2 velocity;
	glm::vec2 acc;
	float mass;

	glm::vec2 grid;
	int index;

	void update(double& deltaTime);
	void draw();
	void applyForce();
};

struct Constraint {
	Point* p1;
	Point* p2;
};

