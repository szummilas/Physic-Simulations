#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	for (int x = 0; x < clothSize.y; x++) {
		for (int y = 0; y < clothSize.x; y++) {

			Point newPoint;

			newPoint.currentPos = glm::vec2(startPos.x + x * spacing, startPos.y + y * spacing);
			newPoint.index = glm::vec2(x, y);

			if (y == clothSize.x - 1 or x == clothSize.y - 1) {
				newPoint.isEdge = true;

				if (y == clothSize.x - 1) {
					newPoint.isVertical = true;
				}

				if (x == clothSize.y - 1) {
					newPoint.isHorizontal = true;
				}

			}
			else {
				newPoint.isEdge = false;
			}

			points.push_back(newPoint);
		}
	}

	std::cout << "krawedzi ma byc: " << points.size() * (points.size() - 1) / 2 << '\n';

	// ----	CONSOLE DEBUG ----
	std::cout << points.size() << '\n';
	
	for (int i = 0; i < points.size(); i++) {

		//std::cout << "positions[" << i << "]: " << points[i].currentPos << '\n';
		//std::cout << "index[" << i << "]: " << points[i].index << " " << points[i].isEdge << '\n';

		/*if (glm::distance(points[0].currentPos, points[i + 1].currentPos) == spacing) {
			std::cout << "NEIGH" << '\n';
		}*/
	}


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

	std::cout << points[10].currentPos << '\n';

	for (int i = 0; i < points.size(); i++) {
		//points[i].currentPos.y += ofGetLastFrameTime() * 10;
		
		points[i].update(dt);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	for (int i = 0; i < points.size(); i++) {

		points[i].draw();
		ofDrawBitmapString(i, points[i].currentPos);

		if (points[i].isEdge == false) {

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
		}

		/*if (points[i].isHorizontal == true and i != points.size() - 1) {
			ofSetColor(ofColor::gray);
			ofDrawLine(points[i].currentPos, points[i + 1].currentPos);
		}*/

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
