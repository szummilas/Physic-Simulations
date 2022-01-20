#include "cloth.h"

Cloth::Cloth() {
}

void Cloth::setup() {

	fixedDeltaTime = (int)(1000 / (float)desiredFrameRate);
	fixedDeltaTimeSeconds = (float)fixedDeltaTime / 1000.0;


	for (int x = 0; x < size.y; x++) {
		for (int y = 0; y < size.x; y++) {

			Point* p = new Point();

			p->position = glm::vec2(position.x + x * restDistance, position.y + y * restDistance);
			p->velocity = glm::vec2(0, 0);
			p->acc = glm::vec2(0, 0);

			p->grid = glm::vec2(x, y);
			p->index = counter;
			counter++;

			points.push_back(p);
		}
	}

	// do kazdego punktu przypisuje krawedz skojarzona z tym punktem oraz punktem sasiednim
	for (int i = 0; i < points.size() - 1; i++) {

		// krawedzie pionowe (od gory do dolu)
		// z wylaczeniem ostatniego rzedu poziomego (bo on nie ma juz krawedzi w dol)

		/*
				0	-> i		4
				|				|
				1	-> i + 1	5
				|				|
				2				6
				|				|
			   (3)			   (7)

			   TU NA DOLE NIE BEDZIE
			   JUZ KRAWEDZI
		*/

		if (points[i]->grid.y != size.x - 1) {

			Constraint c;

			c.p1 = points[i];
			c.p2 = points[i + 1];

			points[i]->constraints.push_back(c);
		}

		// krawedzie poziome (od lewej do prawej)
		// z wylaczeniem ostatniego rzedu pionowego (bo on juz nie ma krawedzi w prawo)

		/*
				0	--	 (4)	->	TU PO
				|		  |			PRAWEJ
				1	--   (5)		STRONIE
				|		  |			NIE BEDZIE
				2	--   (6)		JUZ KRAWEDZI
				|	      |
			   (3)	--   (7)
		*/

		if (points[i]->grid.x != size.y - 1) {

			Constraint c;
			c.p1 = points[i];
			c.p2 = points[i + size.x];

			points[i]->constraints.push_back(c);
		}

		// ------------

		if (points[i]->grid.y == 0) {
			points[i]->locked = true;
			points[i]->lockedPosition = points[i]->position;
		}

		points[i]->setup(restDistance);
	}
}

void Cloth::update() {
	for (int i = 0; i < points.size(); i++) {
		points[i]->SatisfyConstraints();
		points[i]->AccumulateForces();
		points[i]->Verlet(fixedDeltaTimeSeconds);
	}
}

void Cloth::draw() {
	for (int i = 0; i < points.size(); i++) {
		points[i]->draw();
		ofDrawBitmapString(points[i]->index, points[i]->position);

		for (int j = 0; j < points[i]->constraints.size(); j++) {
			ofDrawLine(points[i]->constraints[j].p1->position, points[i]->constraints[j].p2->position);
		}
	}
}
