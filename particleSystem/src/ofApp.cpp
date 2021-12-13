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

	drawingGrid = false;
	debugText = false;
	box.set(20);

	gui.setup();
	mixerGroup.setup("GUI");
	mixerGroup.setHeaderBackgroundColor(ofColor::darkBlue);
	mixerGroup.setBorderColor(ofColor::darkBlue);
	mixerGroup.add(sliderSize.set("size", 100, 100, 500));
	fbo3d.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	gui.add(&mixerGroup);

	particle_effect.setup(numOfParticles, emitter);
	boom.setup(particle_effect.particles, emitter);

	keyEffect = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
	emitter.update();

	if (keyEffect == 0) {
		particle_effect.particles.clear();
		particle_effect.setup(numOfParticles, emitter);
	}

	if (keyEffect == 1) {
		snow.update(particle_effect.particles, emitter, deltaTime);
	}

	if (keyEffect == 2) {
		matrix.update(particle_effect.particles, emitter, deltaTime);
	}

	if (keyEffect == 3) {
		boom.update(particle_effect.particles, emitter, deltaTime);
	}

	// std::cout << emitter.particles[10].age << '\n';
	std::cout << particle_effect.particles.size() << '\n';

	/*if (emitter.particles.size() != NULL) {
		std::cout << "velocity: " << emitter.particles[100].velocity.y << '\n';
		std::cout << "position: " << emitter.particles[100].position.y << '\n';
	}*/

	// std::cout << "width: " << ofGetWidth() << " height: " << ofGetHeight() << '\n';

	// std::cout << cam.worldToScreen(glm::vec3(100, 100, 100)) << '\n';
	if (sliderSize != temp_size) {
		particle_effect.particles.clear();
		particle_effect.setup(numOfParticles, emitter);
		temp_size = sliderSize;
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDisableDepthTest();
	ofDisableSeparateSpecularLight();
	ofDisableLighting();
	gui.draw();

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
	box.setPosition(0, 0, 0);
	//box.drawAxes(3);
	//box.drawWireframe();

	light.enable();
	light.setPosition(0, 60, 0);
	//light.setDirectional();
	light.draw();
	////light.rotateDeg(10, 0, 0, 90);
	////light.setSpotlight();
	light.setDiffuseColor(ofColor::orange); // pogchamp light color
	////light.disable();
	////ofDisableLighting();
	emitter.draw(sliderSize);

	if (keyEffect == 1) {
		snow.draw(particle_effect.particles);
	}

	if (keyEffect == 2) {
		matrix.draw(particle_effect.particles);
	}

	if (keyEffect == 3 ) {
		boom.draw(particle_effect.particles);
	}

	
	light.disable();

	ofSetColor(255, 255, 255);
	ofDrawSphere(light.getPosition(), 2.0);

	if (drawingGrid) { grid.draw(); }

	if (debugText) {
		ofDrawBitmapString(".(x:-50, y:50, z:50) ", glm::vec3(-50, 50, 50));
		ofDrawBitmapString(".(x:50, y:-50, z:50) ", glm::vec3(50, -50, 50));
		ofDrawBitmapString(".(x:50, y:50, z:-50) ", glm::vec3(50, 50, -50));
		ofDrawBitmapString(".(x:-50, y:-50, z:50) ", glm::vec3(-50, -50, 50));
		ofDrawBitmapString(".(x:50, y:-50, z:-50) ", glm::vec3(50, -50, -50));
		ofDrawBitmapString(".(x:-50, y:50, z:-50) ", glm::vec3(-50, 50, -50));
		ofDrawBitmapString(".(x:-50, y:-50, z:-50) ", glm::vec3(-50, -50, -50));
		ofDrawBitmapString(".(x:50, y:50, z:50) ", glm::vec3(50, 50, 50));

		ofDrawBitmapString(".boxCorner", (box.getSize() / 2));
		ofDrawBitmapString(".boxCorner", (-box.getSize() / 2));

		ofDrawBitmapString(".boxCorner", -box.getSize().x / 2, box.getSize().y / 2, box.getSize().z / 2);
		ofDrawBitmapString(".boxCorner", box.getSize().x / 2, -box.getSize().y / 2, box.getSize().z / 2);
		ofDrawBitmapString(".boxCorner", box.getSize().x / 2, box.getSize().y / 2, -box.getSize().z / 2);

		ofDrawBitmapString(".boxCorner", -box.getSize().x / 2, -box.getSize().y / 2, box.getSize().z / 2);
		ofDrawBitmapString(".boxCorner", box.getSize().x / 2, -box.getSize().y / 2, -box.getSize().z / 2);
		ofDrawBitmapString(".boxCorner", -box.getSize().x / 2, box.getSize().y / 2, -box.getSize().z / 2);

		ofDrawBitmapString(".boxCenter", (box.getGlobalPosition()));
	}

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
		particle_effect.particles.clear();
		particle_effect.setup(numOfParticles, emitter);
	}

	if (key == 't') {
		if (!debugText) {
			debugText = true;
		}
		else {
			debugText = false;
		}
	}

	if (key == '0') {
		particle_effect.particles.clear();
		particle_effect.setup(numOfParticles, emitter);
		keyEffect = 0;
	}

	if (key == '1') {
		particle_effect.particles.clear();
		particle_effect.setup(numOfParticles, emitter);
		keyEffect = 1;
	}

	if (key == '2') {
		particle_effect.particles.clear();
		particle_effect.setup(numOfParticles, emitter);
		keyEffect = 2;
	}

	if (key == '3') {
		particle_effect.particles.clear();
		particle_effect.setup(numOfParticles, emitter);
		boom.setup(particle_effect.particles, emitter);
		keyEffect = 3;
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
