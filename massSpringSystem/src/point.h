#pragma once
#include "ofMain.h"
#include "constraint.h"

class Point {
public:
	
	glm::vec2 currentPos;
	glm::vec2 oldPos;
	glm::vec2 velocity;
	glm::vec2 index;
	bool isEdge;
	bool isVertical;
	bool isHorizontal = false;

	void update(double& deltaTime);
	void draw();
	void addGrav();
};

