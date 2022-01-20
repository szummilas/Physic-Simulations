#pragma once
#include "ofMain.h"
#include "point.h"

class Cloth {
public:

	Cloth();
	void setup();
	void update();
	void draw();

	// number of cloth rows and columns
	glm::vec2 size = glm::vec2(8, 10);

	// top left point
	glm::vec2 position = glm::vec2(ofGetWindowWidth() / 2 - 250, ofGetWindowHeight() / 2 - 200);

	// point spacing
	int restDistance = 30;

	int counter = 0;
	int desiredFrameRate = 60;
	int fixedDeltaTime;
	float fixedDeltaTimeSeconds;

	std::vector<Point*> points;
};

