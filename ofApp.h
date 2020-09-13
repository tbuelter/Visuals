#pragma once

#include "ofMain.h"

#include <time.h>
#include <chrono>
class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void drawStage1();
		void drawStage2();
		void drawStage3();
		void drawStage4();
		//Connection of 2 Points
		void connect(ofVec4f* points);
		float inc = 4.5, size = 1, angle, move, opac, xRotate = 0, yRotate = 1, zRotate = 0, rotation = 0; // counter
		float speed = 0.005;
		int curStage = 0;
		int timeElapsed;
		vector<int> stage = { 10, 30, 30, 40, 50 };
		time_t startTime = time(0), timer;

		//STAGE HYPERCUPE
		float size4D = 1;
		ofVec4f* points = new ofVec4f[16];
		ofVec4f* points4D = new ofVec4f(128);

		//STAGE3 PARAMETRIC ART
		float inc3;

		float aXs = sin((0.3 + 1 * 1 * sin(0.3 / 100) * 10) / 10) + cos((0.3 + 1 * 1) / 10) * 10;
		float aYs = sin((0.3 + 1 * 1) / 12) * 100 + cos((0.3 + 1 * 1) / 10) * 50;

		float bXs = cos((0.3 + 1 * 1) / 10) * 300 + cos((0.3 + 1 * 1) / 5) * 50;
		float bYs = sin((0.3 + 1 * 1) / 10) * 100 + cos((0.3 + 1 * 1) / 15) * 170;


		// Art
		int steps = 512;

		ofSoundPlayer sound;
		//float* fft;
		vector<float> fft;
		float* soundSpectrum;
		int bands;
		int timeEnd = 0;
		int timeEnd2 = 0;

};
