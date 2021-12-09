#include "emitter.h"

Emitter::Emitter() {

}

void Emitter::setup(int numOfParticles) {
	zeroVec = glm::vec3(0, 0, 0);

	for (unsigned int i = 0; i < numOfParticles; i++) {
		Particle newParticle;
		newParticle.position = zeroVec;
		newParticle.velocity = glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
		newParticle.color = ofColor::white;
		particles.push_back(newParticle);
	}
	
}

void Emitter::draw() {
	ofPushStyle();

	ofSetColor(ofColor::teal);
	ofNoFill();
	ofDrawBox(100);

	ofPopStyle();

	for (unsigned int i = 0; i < particles.size(); i++) {
		ofDrawSphere(particles[i].position, 1);
	}
}

void Emitter::update() {
	float dt = ofGetLastFrameTime();

	for (unsigned int i = 0; i < particles.size(); i++) {
		particles[i].position += particles[i].velocity * dt;
	}
}
