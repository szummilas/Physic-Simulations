#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// ------- WINDOW SETUP STUFF -------

	ofSetVerticalSync(true);
	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	ofEnableSmoothing();

	// ------- CAMERA SETUP STUFF -------
	cam.setTarget(emitter);
	cam.setDistance(200);
	cam.setNearClip(10);
	cam.setFarClip(1000);

	// emitter.setup(10000);

	drawingGrid = false;
}

//--------------------------------------------------------------
void ofApp::update() {
	emitter.update();

	// std::cout << emitter.particles[10].age << '\n';

	/*if (emitter.particles.size() != NULL) {
		std::cout << "velocity: " << emitter.particles[100].velocity.y << '\n';
		std::cout << "position: " << emitter.particles[100].position.y << '\n';
	}*/

	// std::cout << "width: " << ofGetWidth() << " height: " << ofGetHeight() << '\n';

	std::cout << cam.worldToScreen(glm::vec3(100, 100, 100)) << '\n';
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	ofEnableDepthTest();
	//ofEnableLighting();
	ofDisableLighting();

	// draw the outer box
	/*material.begin();
	ofNoFill();
	ofDrawBox(0, 0, max(ofGetWidth(), ofGetHeight()));
	material.end();*/

	ofPushStyle();

	//light.enable();
	//light.setPosition(0, -50, 0);
	//light.setDirectional();
	//light.draw();
	////light.rotateDeg(10, 0, 0, 90);
	////light.setSpotlight();
	////light.setDiffuseColor(ofColor::orange); // pogchamp light color
	////light.disable();
	////ofDisableLighting();
	emitter.draw();

	//light.disable();
	//ofDisableLighting();

	ofSetColor(255, 255, 255);
	//ofDrawSphere(light.getPosition(), 2.0);

	if (drawingGrid) { grid.draw(); }

	ofDrawBitmapString(".(x:-50, y:50, z:50) ", glm::vec3(-50, 50, 50));
	ofDrawBitmapString(".(x:50, y:-50, z:50) ", glm::vec3(50, -50, 50));
	ofDrawBitmapString(".(x:50, y:50, z:-50) ", glm::vec3(50, 50, -50));
	ofDrawBitmapString(".(x:-50, y:-50, z:50) ", glm::vec3(-50, -50, 50));
	ofDrawBitmapString(".(x:50, y:-50, z:-50) ", glm::vec3(50, -50, -50));
	ofDrawBitmapString(".(x:-50, y:50, z:-50) ", glm::vec3(-50, 50, -50));
	ofDrawBitmapString(".(x:-50, y:-50, z:-50) ", glm::vec3(-50, -50, -50));
	ofDrawBitmapString(".(x:50, y:50, z:50) ", glm::vec3(50, 50, 50));

	ofPopStyle();

	cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'g') {
		if (!drawingGrid) {
			drawingGrid = true;
		}
		else {
			drawingGrid = false;
		}
	}

	if (key == ' ') {
		emitter.particles.clear();
		emitter.setup(1000);
	}
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
