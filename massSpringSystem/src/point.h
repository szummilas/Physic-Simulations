#pragma once
#include "ofMain.h"

class Point;

struct Constraint {
	Point* p1;
	Point* p2;

	float diff;
};

class Point {
public:
	
	Point();

	glm::vec2 position;
	glm::vec2 lastPosition;
	glm::vec2 nextPosition;

	glm::vec2 velocity;
	glm::vec2 acc;
	float mass;
	float restDist;

	glm::vec2 grid;
	int index;

	bool locked;
	glm::vec2 lockedPosition;

	void draw();
	void setup(float restDistance);

	// https://www.gpgstudy.com/gpgiki/GDC_2001:_Advanced_Character_Physics#fn-1
	// https://www.cs.cmu.edu/afs/cs/academic/class/15462-s13/www/lec_slides/Jakobsen.pdf

	void Verlet(float deltaTime);
	void SatisfyConstraints();
	void AccumulateForces();

	std::vector<Constraint> constraints;
};



