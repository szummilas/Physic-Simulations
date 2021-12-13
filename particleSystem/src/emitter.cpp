#include "emitter.h"

//
//void Emitter::setup(int numOfParticles) {
//	zeroVec = glm::vec3(0, 0, 0);
//	
//
//	for (unsigned int i = 0; i < numOfParticles; i++) {
//		Particle newParticle;
//		newParticle.position = glm::vec3((int)ofRandom(-box.getSize().x / 2, box.getSize().x / 2), box.getSize().y / 2, (int)ofRandom(-box.getSize().x / 2, box.getSize().x / 2));;
//		//newParticle.position = zeroVec;
//		newParticle.velocity = glm::vec3(0, ofRandom(0, 1), 0);
//		newParticle.friction = zeroVec;
//		newParticle.color = ofColor::white;
//		newParticle.drag = ofRandom(0.97, 0.99);
//		//newParticle.velocity.y = fabs(newParticle.velocity.y) * 3.0;
//		newParticle.uniqueVal = ofRandom(-10000, 10000);
//
//		newParticle.age = 0;
//		newParticle.lifetime = ofRandom(5, 10);
//
//		particles.push_back(newParticle);
//	}
//	
//}

void Emitter::draw(ofParameter<int> &boxSize) {
	ofPushStyle();

	ofSetColor(ofColor::teal);
	ofNoFill();
	ofDrawBox(boxSize);

	ofPopStyle();

	box.set(boxSize);
	//box.draw();

	//for (unsigned int i = 0; i < particles.size(); i++) {
		//ofDrawSphere(particles[i].position, 1 / particles[i].age);
		//ofDrawSphere(particles[i].position, ofRandom(0.3, 0.5));
		//ofDrawBox(particles[i].position, 1);
		//ofDrawPlane(particles[i].position, 0.5, 0.5);
		/*ofSetColor(0, 255, 0);

		if (i % 2 == 0) {
			ofDrawBitmapString("1", particles[i].position);
		}
		else {
			ofDrawBitmapString("0", particles[i].position);
		}*/
	//}
}

void Emitter::update() {
	//float dt = ofGetLastFrameTime();
	

	//for (unsigned int i = 0; i < particles.size(); i++) {
		// computing particle age
		//particles[i].age += ofGetLastFrameTime();

		//// ------- SNOW -------
		/*float fakeWindX = ofSignedNoise(particles[i].position.x * 0.003, particles[i].position.y * 0.006, ofGetElapsedTimef() * 0.6);
		particles[i].friction.x = fakeWindX * 0.25 + ofSignedNoise(particles[i].uniqueVal, particles[i].position.y * 0.04) * 0.6;
		particles[i].friction.y = ofSignedNoise(particles[i].uniqueVal, particles[i].position.x * 0.006, ofGetElapsedTimef() * 0.2) * 0.09 + 0.18;

		particles[i].velocity *= particles[i].drag;
		particles[i].velocity += particles[i].friction * 0.04;*/

		//we do this so as to skip the bounds check for the bottom and make the particles go back to the top of the screen
		//if (particles[i].position.y + particles[i].velocity.y < -box.getSize().y / 2) {
		//	particles[i].position.y += box.getSize().y;
		//}

		// particle physics
		//particles[i].position -= particles[i].velocity;
		//particles[i].velocity += -0.1f * particles[i].position * dt;

		// particle disapearing
		//if (particles[i].age > particles[i].lifetime) {
		//	particles.erase(particles.begin() + i);
		//}

		

		//if (particles[i].position.x > (box.getSize().x / 2)) {
		//	particles[i].position.x = (box.getSize().x / 2);
		//	particles[i].velocity.x *= -1.0;
		//}
		//else if (particles[i].position.x < -(box.getSize().x / 2)) {
		//	particles[i].position.x = -(box.getSize().x / 2);
		//	particles[i].velocity.x *= -1.0;
		//}
		///*if (particles[i].position.y > 50) {
		//	particles[i].position.y = 50;
		//	particles[i].velocity.y *= -1.0;
		//}
		//if (particles[i].position.y < -50) {
		//	particles[i].position.y = 50;
		//	particles[i].velocity.y *= -1.0;
		//}*/

		//if (particles[i].position.z > (box.getSize().z / 2)) {
		//	particles[i].position.z = (box.getSize().z / 2);
		//	particles[i].velocity.z *= -1.0;
		//}
		//else if (particles[i].position.z < -(box.getSize().z / 2)) {
		//	particles[i].position.z = -(box.getSize().z / 2);
		//	particles[i].velocity.z *= -1.0;
		//}
	//}
}
