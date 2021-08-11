#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		vector<float>noiseSeeds;
		float angleStep, stepSize, radius, sp;
		int sunLocX, sunLocY, totalRays;
		int cRad, nMax;

		void keyPressed(int key);
		
		

     
};
