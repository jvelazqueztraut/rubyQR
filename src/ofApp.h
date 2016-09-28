#pragma once

#include "ofMain.h"
#include "ofxAndroid.h"

#include <vector>

#include "ofxZxing.h"
#include "ofxAnimatable.h"
#include "ofxAppUtils.h"

class ofApp : public ofxAndroidApp{
	
	public:
		
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);

		void touchDown(int x, int y, int id);
		void touchMoved(int x, int y, int id);
		void touchUp(int x, int y, int id);
		void touchDoubleTap(int x, int y, int id);
		void touchCancelled(int x, int y, int id);
		void swipe(ofxAndroidSwipeDir swipeDir, int id);

		void pause();
		void stop();
		void resume();
		void reloadTextures();

		bool backPressed();
		void okPressed();
		void cancelPressed();

		ofVideoGrabber camera;

		float lastFound;
		ofxZxing::Result result;

		int one_second_time;
		int camera_fps;
		int frames_one_sec;
};
