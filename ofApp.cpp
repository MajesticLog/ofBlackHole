#include "ofApp.h"

// Made by Zoe Caudron, @life.as.a.plant
// Inspired by Roni Kaufman's sketch, https://openprocessing.org/sketch/792407


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundAuto(false);
    ofSetFrameRate(60);
    ofBackground(0);
	ofSetCircleResolution(100);
	totalRays = 15;
	sp = 0.0009;
	stepSize = 0;
	radius = 100;
	cRad = 105;
	nMax = 0;
	angleStep = 360.0 / totalRays;
	sunLocX = ofGetWidth() / 2;
	sunLocY = ofGetHeight() / 2;
	ofNoFill();
	for (int i = 0; i < totalRays; i++) {
		noiseSeeds.push_back(ofRandom(10000));
	}

  
}

//--------------------------------------------------------------
void ofApp::update(){
	radius += sp; //if you want an increase of the spacing
//	radius += 1;  //if you want the circles evenly spaced
	stepSize += 3;  //increase of the noisiness
	nMax += 1;
//	cRad += 1;

	if (radius > 350) {
		nMax = 300; //helps stop the sketch whilst keeping the same effect
	}

	if (stepSize > 350) {
		nMax = 300;
	}
	sp += sp/4;
}

//--------------------------------------------------------------
void ofApp::draw(){


	ofPushMatrix();
	ofPushStyle();
    ofTranslate(sunLocX, sunLocY);
	ofSetColor(255,2);

//	for (int r = 105; r < 110; r+=2) {   if you want a well defined, brighter center circle - kinda patchy but does the job
//		ofPushStyle();
//		ofSetColor(255, 2);
//		ofDrawCircle(0, 0, r);
//		ofPopStyle();
//	}


	ofBeginShape();  // now this a bit tricky, and taken from Goldsmith's tutor, Theo P. The beginShape/endShape doesn't fully close with the noise, creating unpleasant artifacts.
					 // This helps fully close the shape. Probably not optimal but I need to spend more time figuring that out

	ofPoint end;
	float nRad = radius + ofNoise(noiseSeeds[noiseSeeds.size()-1]) * stepSize;
	end.x = cos(ofDegToRad(angleStep*noiseSeeds.size() - 1)) * nRad;
	end.y = sin(ofDegToRad(angleStep*noiseSeeds.size() - 1)) * nRad;
	ofCurveVertex(end);

	for(int c=nMax;c<300;c++){

		for (int i=0; i<totalRays; i++)
		 {
		ofPoint end;
		float nRad = radius + ofNoise(noiseSeeds[i]) * stepSize;     
        end.x = cos(ofDegToRad(angleStep*i)) * nRad;
        end.y = sin(ofDegToRad(angleStep*i)) * nRad;
		noiseSeeds[i] += 0.01;
		ofCurveVertex(end);    
		
		
		  }
		
	}

	nRad = radius + ofNoise(noiseSeeds[0]) * stepSize;
	end.x = cos(ofDegToRad(angleStep*0)) * nRad;
	end.y = sin(ofDegToRad(angleStep*0)) * nRad;
	ofCurveVertex(end);

	
    nRad = radius + ofNoise(noiseSeeds[1]) * stepSize;
	end.x = cos(ofDegToRad(angleStep*1)) * nRad;
	end.y = sin(ofDegToRad(angleStep*1)) * nRad;
	ofCurveVertex(end);


	ofEndShape(true);
	ofPopStyle();
	ofPopMatrix();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		glReadBuffer(GL_FRONT);
		ofSaveScreen(ofToString(ofGetFrameNum()) + ".jpg");  //to save the final image in your project folder
	}

	if (key == 'r') { //resets the sketch - useful when doing a screengrab/recording!
		setup();
	}
}

