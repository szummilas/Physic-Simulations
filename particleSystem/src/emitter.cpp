#include "emitter.h"

Emitter::Emitter() {

}

void Emitter::setup(int numOfParticles) {
	zeroVec = glm::vec3(0, 0, 0);

	for (unsigned int i = 0; i < numOfParticles; i++) {
		Particle newParticle;
		newParticle.position = zeroVec;
		newParticle.velocity = glm::vec3(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
		newParticle.color = ofColor::white;

		newParticle.age = 0;
		newParticle.lifetime = ofRandom(5, 10);

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
		ofDrawSphere(particles[i].position, 1 / particles[i].age);
		//ofDrawBox(particles[i].position, 1);
	}
}

void Emitter::update() {
	float dt = ofGetLastFrameTime();
	

	for (unsigned int i = 0; i < particles.size(); i++) {
		// computing particle age
		particles[i].age += ofGetLastFrameTime();

		// particle physics
		particles[i].position += particles[i].velocity * dt;
		//particles[i].velocity += -0.1f * particles[i].position * dt;

		// particle disapearing
		if (particles[i].age > particles[i].lifetime) {
			particles.erase(particles.begin() + i);
		}
	}
}
