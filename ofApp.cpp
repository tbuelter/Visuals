#include "ofApp.h"

using namespace std;
using namespace chrono;
//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowShape(1600, 1600);
	ofBackground(119, 114, 116);
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetBackgroundAuto(false);
	// Play a sound for stage 4
	if (curStage = 4) {
		sound.load("\\track.mp3");
		sound.play();

		for (size_t i = 0; i < 512; i++) {
			fft.push_back(0);
		}
		bands = 512;
	}
	startTime = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
	drawStage4();
}	

void ofApp::drawStage4(){

	timeElapsed = (ofGetElapsedTimeMillis() - startTime) ;//Count the seconds to change the Animation


	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 );
	ofSetColor(25, 25, 25);
	ofSoundUpdate();

	//if (timeElapsed >= 1000/12 + timeEnd2) { // 12 steps every Second
		soundSpectrum = ofSoundGetSpectrum(bands);
		timeEnd2 = timeElapsed;
		for (size_t i = 0; i < 512; i++) {
			fft[i] *= 0.96;
			if (fft[i] < soundSpectrum[i]) {
				fft[i] = soundSpectrum[i];
			}
			fft[i] = soundSpectrum[i];

		}
	//}
		//ofSoundSetVolume(0);

	// Reverse the Array so Bass is on the Outside of the Circle instead of the Center
	reverse(fft.begin(), fft.end());

	// Make it Spin
	if (timeElapsed >= 1 + timeEnd) { // Rotate every 1 MilliSeconds
		timeEnd = timeElapsed;

		inc3 += 0.00086746987952; // 0.002 Degrees of Rotation every millisecond. 2 Degrees per second
		ofRotate(inc3);

		double width;
		// Draw the Spectrumanalyzer
		for (int i = 0; i < steps; i++) {
			if (i > 0) {
				width = (double)i / steps;
			}else {
				width = 0;
			}
			ofColor c = ofColor::fromHsb(0, 255, 255); // bright red
			c.setHue(128); // now bright cyan	
			ofSetColor(c);

			ofDrawRectangle(ofRectangle(0, i * 0.9, 3 * width,  fft[i] *10));
		}
	}
}











	//	----- STAGE 2  HYPERCUBE----- //
void ofApp::drawStage2() {
	//Size of the Cube
	size = 1; //+ abs(sin(inc/8)*35);
	inc += 0.1;
	angle = inc / 14;

	//HYPERCUBE POINTS
	points[0] = ofVec4f(-size, -size, -size, size);
	points[1] = ofVec4f(-size, size, -size, size);
	points[2] = ofVec4f(size, -size, -size, size);
	points[3] = ofVec4f(size, size, -size, size);
	points[4] = ofVec4f(-size, -size, size, size);
	points[5] = ofVec4f(-size, size, size, size);
	points[6] = ofVec4f(size, -size, size, size);
	points[7] = ofVec4f(size, size, size, size);
	points[8] = ofVec4f(-size, -size, -size, -size);
	points[9] = ofVec4f(-size, size, -size, -size);
	points[10] = ofVec4f(size, -size, -size, -size);
	points[11] = ofVec4f(size, size, -size, -size);
	points[12] = ofVec4f(-size, -size, size, -size);
	points[13] = ofVec4f(-size, size, size, -size);
	points[14] = ofVec4f(size, -size, size, -size);
	points[15] = ofVec4f(size, size, size, -size);

	//Center
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	
	//Rotate the View
	ofRotateX(-inc);
	ofRotateY(-inc);

	//Rotation Matrices
	ofMatrix4x4 rotationXY;
	ofMatrix4x4 rotationZW;
	ofMatrix4x4 projection;


	rotationXY.set(
		cos(angle), -sin(angle), 0, 0,
		sin(angle), cos(angle), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);

	rotationZW.set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, cos(angle), -sin(angle),
		0, 0, sin(angle), cos(angle)
	);

	ofVec4f rotated;
	ofVec4f projected;

	for (int i = 0; i < 16; i++) {
		ofPushMatrix();

		rotated = rotationZW * points[i];
		//rotated = rotationXY * rotated;
		
		float w = 1 / (2 - rotated.w);
		projection.set(
			w, 0, 0, 0,
			0, w, 0, 0,
			0, 0, w, 0,
			0, 0, 0, 0
		);
		projected = projection * rotated;
		projected *= 100;
		points4D[i] = projected;
		//ofRotateZ(inc);
		ofSetColor(200, 200, 200);
		connect(points4D);
		ofDrawSphere(projected.x,projected.y,projected.z, 4);
		ofPopMatrix();
	}

}
	//	----- STAGE 1  ROTATING SQUARES ----- //
void ofApp::drawStage1() {
	size = 10;
	inc			+= speed; //0.01 base, start 0.005

	angle		= sin(-inc) * 3;
	rotation	= angle * -RAD_TO_DEG;
	move		= PI / 2 + sin(inc) ;
	opac		= ofMap(move, 0.5, 2.6, 90, 155);//colormapping
	
	if (timeElapsed > stage[0]) {		// STAGE 1.2
		if (ofInRange(rotation, -1, 1)) {
			xRotate = 0.5;    //Activate X Rotation
			speed   = 0.01;   //Set the Speed higher
		}
	}
	if (timeElapsed > stage[1]) {		// STAGE 1.2
		if (ofInRange(rotation, -1, 1)) {
			zRotate = 1;
		}
	}
	for (int x = size; x < ofGetWidth(); x += size * 2) {//for loop for x axis
		for (int y = size; y < ofGetHeight(); y += size * 2) { //for loop for y axis
			ofPushMatrix();
			ofSetColor(opac);
			ofTranslate(x, y);
			ofRotateZ(-rotation * zRotate);		// 1 
			ofRotateX( rotation * xRotate );		// 0.5
			//ofRotateY( rotation * yRotate);		// 1
			ofDrawRectangle(0, 0, size * size / 8, size * size / 8);
			ofPopMatrix();
		}
	}
}
	//	----- STAGE 3  DIGITAL ART PARAMETRIC ----- //
void ofApp::drawStage3() {

	float speed = 0.25;
	float dist = 1;
	float size = 3;
	int amount = 25;

	inc3 += speed;

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);

	ofVec2f pointA, pointB;
	float aX, aY, bX, bY, aXm, aYm, bXm, bYm;
	for (int i = 0; i < amount; i += 1) {
		if ((20 * sin(i / 10) * 10) == 180) {
			inc3 = 0;
		}
			aX = cos((inc3 + i * dist) / 12) * 60 * 0;
			aY = sin((inc3 + i * dist) / 32) * 60   ;

			bY = cos((inc3 + i * dist) / 12) * 100 + sin((inc3 + i * dist) / 12) * 100;
			bX = sin((inc3 + i * dist) / 15) * 10 ;

			aX = sin((inc3 + i * dist*sin(inc3/100)*10) / 10) + cos((inc3 + i * dist) / 10) * 10;
			aY = sin((inc3 + i * dist) / 12) * 100 + cos((inc3 + i * dist) / 10) * 10;

			bX = cos((inc3 + i * dist) / 10) * 100 + sin((inc3 + i * dist) / 5) * 25 * sin(inc3 / 100) * 10/ 10 + 2;
			bY = sin((inc3 + i * dist) / 10) * 100 + cos((inc3 + i * dist) / 5) * 10;

			ofSetLineWidth(size);
			int x;
			x = 3;
			ofRotateDeg(x/10);
			glm::vec3 a(aX, aY, 5);
			glm::vec3 b(aX, bY, 5);
			b = b;//glm::polar(b) * 100;
				a = a;//glm::polar(a) * 100;
				ofSetColor(ofColor::fromHsb(100 +50 / amount * i * sin(inc3 / 10), 150, 150));
			ofDrawLine(a.x * x, a.y * x, b.y *x, b.x * x);
			
			//ofDrawLine(b.x * x, b.y * x,-a.x * x, -a.y * x);
	}

	if (ofInRange(aX-aXs,-0.3,0.3)) {
		cout << timeElapsed << endl;
	}
	/*glm::vec3 a(bX, aY, 10);
		glm::vec3 b(1, 1, aX*bY);
		b = glm::polar(b) *400;
		a = glm::polar(a) *400;
*/
}

void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
