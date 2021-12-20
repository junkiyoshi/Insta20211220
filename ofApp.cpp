#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	
	this->mesh.clear();
	this->circle_list.clear();
	
	vector<glm::vec2> location_list;
	for (int i = 0; i < 120; i++) {

		auto location = glm::vec2(ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035), 0, 1, -300, 300), ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.0035), 0, 1, -300, 300));
		location_list.push_back(location);
	}

	for (int i = 0; i < location_list.size(); i++) {

		this->circle_list.push_back(glm::vec3(location_list[i], 0));
		auto near_count = 0;
		for (int k = 0; k < location_list.size(); k++) {

			if (i == k) { continue; }

			auto distance = glm::distance(location_list[i], location_list[k]);
			if (distance < 50) {

				this->mesh.addVertex(glm::vec3(location_list[i], 0));
				this->mesh.addVertex(glm::vec3(location_list[k], 0));

				this->mesh.addIndex(this->mesh.getNumVertices() - 1);
				this->mesh.addIndex(this->mesh.getNumVertices() - 2);

				near_count++;
			}
		}

		this->circle_list.back().z = pow(1.5, near_count);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofSetLineWidth(0.5);
	this->mesh.drawWireframe();

	ofSetLineWidth(1.5);
	for (auto& circle : this->circle_list) {

		ofFill();
		ofSetColor(0);
		ofDrawCircle(glm::vec2(circle.x, circle.y), circle.z);

		ofNoFill();
		ofSetColor(255);
		ofDrawCircle(glm::vec2(circle.x, circle.y), circle.z);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}