#pragma once

#include "ofMain.h"

#ifdef TARGET_ANDROID
#include "ofxAndroid.h"
#endif

#include <vector>

#include "ofxZxing.h"
#include "ofxAnimatableObject.h"
#include "ofxAppUtils.h"
#include "ofxJSON.h"

#include "scenes/scenes.h"

#define _DEBUG

class ofApp : public ofxApp{
	
	public:
		
		void setup();
		void update();
		void draw();

        void mousePressed(int x, int y, int button);
        void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);

#ifdef TARGET_ANDROID
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
#endif
    
		// handles the scenes
		ofxSceneManager sceneManager;
		int lastScene;
    
        string node,device,url,qr;
    
        ofxJSONElement response;
    
        ofxAnimatableObject<ofTexture> inicio;

       	float time;
};
