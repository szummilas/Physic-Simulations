#pragma once
#include "ofMain.h"
#include "point.h"

class Constraint {
public:
	glm::vec2 pos1;
	glm::vec2 pos2;
	float lenght;
	void resolve();
	//void draw(std::vector<Point>& points);
};

