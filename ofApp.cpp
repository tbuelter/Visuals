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
		sound.load("C:\\Users\\Tobias\\Desktop\\PLAYLIST\\DJ MUSIK\\Techno\\TECHNO\\track.mp3");
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
/*--------------------------------------------------------------
void ofApp::drawStage4() {
	/* Cubic Attractors
// j.tarbell   January, 2004
// Albuquerque, New Mexico
// complexification.net

// Processing 0085 Beta syntax update
// j.tarbell   April, 2005

	int dim = 200;
	int a, b;
	float t;
	float dx, dy;
	int num = 5;
	int maxnum = num * num + 1;
	int numtravelers = 200;
	boolean blackout = false;
	int mind = 64;
	float nudge;

	City[] cities;

	int maxpal = 512;
	int numpal = 0;
	color[] goodcolor = new color[maxpal];


	// MAIN --------------------------------------------------------------------

	void setup() {
		size(200, 200, P3D);
		// grab palette from image
		takecolor("longvoyage.gif");
		// erase background
		background(255);
		// define all cities
		cities = new City[maxnum];

		// place cities in grid
		nudge = dim / num;
		int i = 0;
		for (int x = 0; x < num; x++) {
			for (int y = 0; y < num; y++) {
				cities[i] = new City(int(x * nudge + nudge / 2), int(y * nudge + nudge / 2), i);
				i++;
			}
		}
	}

	void draw() {
		for (int n = 0; n < numtravelers;) {
			// pick random city A
			a = int(floor(random(num * num)));
			b = int(floor(random(num * num)));
			if ((a >= num * num) || (b >= num * num)) {
				// why does this happen?
			}
			else if (a != b) {
				if (citydistance(a, b) < mind) {
					// pick random distance between city
					t = random(PI);
					dx = sin(t) * (cities[b].x - cities[a].x) + cities[a].x;
					dy = sin(t) * (cities[b].y - cities[a].y) + cities[a].y;

					if (random(1000) > 990) {
						// noise
						dx += random(-1.5, 1.5);
						dy += random(-1.5, 1.5);
					}
					stroke(red(cities[b].myc), green(cities[b].myc), blue(cities[b].myc), 44);
					point(dx, dy);
					stroke(red(cities[a].myc), green(cities[a].myc), blue(cities[a].myc), 44);
					point(dx, dy);

					n++;
				}
			}
		}

		// move cities
		for (int c = 0; c < (num * num); c++) {
			cities[c].move();
		}

	}

	float citydistance(int a, int b) {
		if (a != b) {
			// calculate and return distance between cities
			float Dx = cities[b].x - cities[a].x;
			float Dy = cities[b].y - cities[a].y;
			float D = sqrt(Dx * Dx + Dy * Dy);
			return D;
		}
		else {
			return 0.0;
		}
	}

	// OBJECTS ------------------------------------------------------------------

	class City {

		int x;
		int y;
		float destx, desty;
		float xp, yp;
		float vx, vy;
		int idx;
		color myc = somecolor();

		City(int Dx, int Dy, int Idx) {
			// position
			xp = Dx;
			yp = Dy;
			x = Dx;
			y = Dy;
			idx = Idx;

			// pick destination
			destx = int(random(num)) * nudge + nudge / 2;
			desty = int(random(num)) * nudge + nudge / 2;
		}

		void draw() {
			stroke(255, 136);
			point(x, y);
		}
		void move() {
			vx += (destx - xp) / 2500;
			vy += (desty - yp) / 2500;

			vx *= 0.973;
			vy *= 0.973;
			xp += vx;
			yp += vy;
			x = int(xp);
			y = int(yp);

			draw();

		}
	}

	// COLOR METHODS --------------------------------------------------------------------

	color somecolor() {
		// pick some random good color
		return goodcolor[int(random(numpal))];
	}

	void takecolor(String fn) {
		PImage b;
		b = loadImage(fn);
		image(b, 0, 0);

		for (int x = 0; x < b.width; x++) {
			for (int y = 0; y < b.height; y++) {
				color c = get(x, y);
				boolean exists = false;
				for (int n = 0; n < numpal; n++) {
					if (c == goodcolor[n]) {
						exists = true;
						break;
					}
				}
				if (!exists) {
					// add color to pal
					if (numpal < maxpal) {
						goodcolor[numpal] = c;
						numpal++;
					}
					else {
						break;
					}
				}
			}
		}

		// pad with whites
		for (int n = 0; n < 6; n++) {
			goodcolor[numpal] = #FFFFFF;
			numpal++;
		}

		// pad with blacks
		for (int n = 0; n < 12; n++) {
			goodcolor[numpal] = #000000;
			numpal++;
		}

	}
	// Cubic Attractors 
	// j.tarbell   January, 2004 
}*/
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