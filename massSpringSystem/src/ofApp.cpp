#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	int counter = 0;

	for (int x = 0; x < clothSize.y; x++) {
		for (int y = 0; y < clothSize.x; y++) {

			Point* p = new Point();

			p->position = glm::vec2(startPos.x + x * spacing, startPos.y + y * spacing);
			p->grid = glm::vec2(x, y);
			p->index = counter;

			p->velocity = glm::vec2(0, 0);
			p->acc = glm::vec2(0, 0);
			p->mass = 1.0;

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

		if (points[i]->grid.y != clothSize.x - 1) {

			Constraint c;

			c.p1 = points[i];
			c.p2 = points[i + 1];

			constraints.push_back(c);
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

		if (points[i]->grid.x != clothSize.y - 1) {

			Constraint c;
			c.p1 = points[i];
			c.p2 = points[i + clothSize.x];

			constraints.push_back(c);
		}
	}

	std::cout << "krawedzi ma byc: " << points.size() * (points.size() - 1) / 2 << '\n';

	// ----	CONSOLE DEBUG ----
	std::cout << points.size() << '\n';
	std::cout << constraints.size() << '\n';
	
	//int k = 0;
	//for (int i = 0; i < points.size(); i++) {
	//	for (int j = 0; j < points.size(); j++) {
	//		if (glm::distance(points[i].currentPos, points[j].currentPos) == spacing) {
	//			
	//			// tu sa wylapane wszystkie powiazania pomiedzy punktami
	//			// wiec jesli teraz usune te podwojne to moge tutaj
	//			// tworzyc constrainty biorac pozycje od i oraz od j
	//			// TODO:
	//			// 1. rozkminic rysowanie constrainsow
	//			// 2. dodac fizyke punktow
	//			k += 1;
	//			std::cout << "[" << k << "] " << i << " is neigh. to " << j << '\n';
	//		}	
	//	}
	//}

	// tyle ma byc krawedzi bez duplikatow
	//std::cout << k / 2 << '\n';

	
}

//--------------------------------------------------------------
void ofApp::update() {

	double dt = ofGetLastFrameTime();

	for (int i = 0; i < points.size(); i++) {
		//points[i]->update(dt);
		//points[i]->applyForce();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	for (int i = 0; i < points.size(); i++) {

		points[i]->draw();
		ofDrawBitmapString(points[i]->index, points[i]->position);

	

		/*if (points[i].isEdge == false) {

			ofSetColor(ofColor::gray);
			ofDrawLine(points[i].currentPos, points[i + 1].currentPos);
			ofDrawLine(points[i].currentPos, points[i + 8].currentPos);
		}

		if (i >= 72 and i < points.size() - 1) {
			ofSetColor(ofColor::gray);
			ofDrawLine(points[i].currentPos, points[i + 1].currentPos);
		}

		if (points[i].isEdge and i < points.size() - 8) {
			ofSetColor(ofColor::gray);
			ofDrawLine(points[i].currentPos, points[i + 8].currentPos);
		}*/

		/*if (points[i].isHorizontal == true and i != points.size() - 1) {
			ofSetColor(ofColor::gray);
			ofDrawLine(points[i].currentPos, points[i + 1].currentPos);
		}*/

	}

	for (int i = 0; i < constraints.size(); i++) {

		ofDrawLine(constraints[i].p1->position, constraints[i].p2->position);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
