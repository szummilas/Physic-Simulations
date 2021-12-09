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
	cam.setDistance(1000);
	cam.setNearClip(10);
	cam.setFarClip(10000);


	emitter.setup(1000);

	drawingGrid = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	emitter.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();

	ofEnableDepthTest();
	ofEnableLighting();

	// draw the outer box
	/*material.begin();
	ofNoFill();
	ofDrawBox(0, 0, max(ofGetWidth(), ofGetHeight()));
	material.end();*/

	ofPushStyle();

	light.enable();
	light.setPosition(-100, 0, 0);
	light.rotateDeg(10, 0, 0, 90);
	light.setSpotlight();
	// light.setDiffuseColor(ofColor::orange); // pogchamp light color
	light.draw();
	//light.disable();
	//ofDisableLighting();
	emitter.draw();
	if (drawingGrid) { grid.draw(); }

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
