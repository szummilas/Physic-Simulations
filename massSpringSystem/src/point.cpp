#include "point.h"

Point::Point() {
	this->position = position;

}

void Point::update(double& deltaTime) {
	/*glm::vec2 forceGravity = glm::vec2(0.f, -1.5f);

	glm::vec2 temporary = currentPos;
	currentPos = currentPos + (currentPos - oldPos) * (0.09f) + (forceGravity * deltaTime);
	oldPos = temporary;
	forceGravity = glm::vec2(0, 0);*/

	velocity = position - lastPosition;

	velocity *= 0.99;

	nextPosition = position + velocity + 0.5 * acc * (deltaTime * deltaTime);

	lastPosition = position;

	position = nextPosition;
}

void Point::draw() {
	ofSetColor(ofColor::white);
	ofFill();
	ofDrawCircle(position, 4);
}

void Point::applyForce() {
	// gravity

	acc.y += 980 / mass;
}

