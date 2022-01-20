#include "point.h"

Point::Point() {

}

void Point::draw() {
	ofSetColor(ofColor::white);
	ofFill();
	ofDrawCircle(position, 4);
}

void Point::setup(float restDistance) {
	restDist = restDistance;
	
	std::cout << constraints.size() << '\n';
}

void Point::Verlet(float deltaTime) {

	velocity = position - lastPosition;

	velocity *= 0.99;

	nextPosition = position + velocity + 0.5 * acc * (deltaTime * deltaTime);

	lastPosition = position;

	position = nextPosition;

	/*glm::vec2 temp = position;

	position += (position - lastPosition) + acc * (deltaTime * deltaTime);

	lastPosition = temp;*/
}

// here constraints should be satisfied
void Point::SatisfyConstraints() {
	for (int i = 0; i < constraints.size(); i++) {
		// position of the two points
		glm::vec2 pos1 = constraints[i].p1->position;
		glm::vec2 pos2 = constraints[i].p2->position;

		// calculate the distance between the two points
		glm::vec2 delta = pos1 - pos2;
		//float deltaLen = delta.length();	// sqrt(diff.x * diff.x + diff.y * diff.y)
		float deltaLen = sqrt(delta.x * delta.x + delta.y * delta.y);

		// find the difference, ot the ratio of how far along the restingDistance the actual distance is.
		constraints[i].diff = (restDist - deltaLen) / deltaLen;

		// push/pull
		pos1 += delta * 0.5 * constraints[i].diff;

		pos2 -= delta * 0.5 * constraints[i].diff;

		// -----------------------------

		// boundary constraints
		/*if (position.y < 10)
			position.y = 2 * 10 - position.y;
		if (position.y > ofGetHeight() - 10)
			position.y = 2 * (ofGetHeight() - 10) - position.y;

		if (position.x < 10)
			position.x = 2 * 10 - position.x;
		if (position.x > ofGetWidth() - 10)
			position.x = 2 * (ofGetWidth() - 10) - position.x;*/

		// other constraints
		if (locked)
			position = lockedPosition;
	}
}

// function to accumulate forces for each particle
void Point::AccumulateForces() {
	acc = glm::vec2(0, 9.81);
}

