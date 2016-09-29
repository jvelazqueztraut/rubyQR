#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "ofxJSON.h"

#define BUTTON_WIDTH 350
#define BUTTON_HEIGHT 50

class ErrorScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    ErrorScene(ofxSceneManager& sm) : sceneManager(sm), ofxScene(ERROR_SCENE_NAME, false) {
        errorText.load("fonts/Futura/FuturaStd-Medium.otf",18);
        
        scanText.load("fonts/Calibri/calibri.ttf",18);
        
        scanButton.x=0;
        scanButton.y=0;
        scanButton.width=BUTTON_WIDTH;
        scanButton.height=BUTTON_HEIGHT;
    }
    
    // scene setup
    void setup() {
        scanButton.setPosition(ofGetWidth()*0.5-scanButton.width/2,ofGetHeight()-scanButton.height*1.5);
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            
            ofLogVerbose(ERROR_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(true) {
            
            finishedEntering();
            ofLogVerbose(ERROR_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {
            ofLogVerbose(ERROR_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(true) {
            finishedExiting();
            ofLogVerbose(ERROR_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        errorText.drawString("Se ha producido un error",20,100);
        errorText.drawString("Por favor chequee su conexion",20,140);
        
        ofPushStyle();
        ofSetColor(255,200);
        string scanStr = "SCAN";
        scanText.drawString(scanStr,scanButton.x+scanButton.width/2-scanText.stringWidth(scanStr)/2,scanButton.y+scanButton.height/2+scanText.stringHeight(scanStr)/2);
        ofNoFill();
        ofDrawRectangle(scanButton);
        ofPopStyle();
    }
    
    // cleanup
    void exit() {
        ofLogVerbose(ERROR_SCENE_NAME) << "exit";
    }
    
    void mouseReleased(int x, int y, int button){
        if(isExiting())
            return;
        if(scanButton.inside(x,y)){
            sceneManager.gotoScene(QR_SCENE_NAME);
        }
    }
    
    ofTrueTypeFont errorText;
    
    ofRectangle scanButton;
    ofTrueTypeFont scanText;
    
    float time;
    ofxSceneManager& sceneManager;
};
