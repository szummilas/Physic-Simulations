#include "point.h"

void Point::update(double& deltaTime) {
	glm::vec2 forceGravity = glm::vec2(0.f, -1.5f);

	glm::vec2 temporary = currentPos;
	currentPos = currentPos + (currentPos - oldPos) * (0.09f) + (forceGravity * deltaTime);
	oldPos = temporary;
	forceGravity = glm::vec2(0, 0);
}

void Point::draw() {
	ofSetColor(ofColor::white);
	ofFill();
	ofDrawCircle(currentPos, 4);
}

