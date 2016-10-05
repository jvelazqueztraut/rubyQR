#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "ofxZxing.h"

class QRScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    QRScene(ofxSceneManager& sm, string& q) : sceneManager(sm), qr(q), ofxScene(QR_SCENE_NAME, false) {
        
        camera.setup(1280,720);
    }
    
    // scene setup
    void setup() {
        result = new ofxZxing::Result();
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            
            ofLogVerbose(QR_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(true) {
            
            finishedEntering();
            ofLogVerbose(QR_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        
        camera.update();
        if(camera.isFrameNew()){
            if(!isExiting()){
                *result = ofxZxing::decode(camera.getPixels(), true);
                if(result->getFound()){
                    qr = result->getText();
                    ofLogNotice(QR_SCENE_NAME) << "QR Code found: " << qr << endl;
                    sceneManager.gotoScene(POST_SCENE_NAME);
                }
            }
        }
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {
            
            ofLogVerbose(QR_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(true) {
            finishedExiting();
            ofLogVerbose(QR_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
#ifdef TARGET_ANDROID
        float scale = ofGetHeight()/camera.getWidth();
#else
        float scale = ofGetWidth()/camera.getWidth();
#endif
        ofPushStyle();
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(ofGetWidth()*0.5,ofGetHeight()*0.5);
        ofScale(scale,scale);
#ifdef TARGET_ANDROID
        ofRotate(90);
#endif
        ofTranslate(-camera.getWidth()*0.5,-camera.getHeight()*0.5);
        camera.draw(0,0);
        if(result->getFound()){
            result->draw();
        }
        ofPopMatrix();
        ofNoFill();
        ofDrawRectangle(ofGetWidth()*0.5-100,ofGetHeight()*0.5-100,200,200);
        ofPopStyle();
    }
    
    // cleanup
    void exit() {
        if(result!=NULL){
            delete result;
            result=NULL;
        }
        ofLogVerbose(QR_SCENE_NAME) << "exit";
    }

    void mousePressed(int x, int y, int button){
#ifdef _DEBUG
        qr = "http://skybox.cloud/id/YhhoQTAAuX1z";
        ofLogNotice(QR_SCENE_NAME) << "Skipping QR scene with code: " << qr << endl;
        sceneManager.gotoScene(POST_SCENE_NAME);
#endif
    }
    
    ofVideoGrabber camera;
    ofxZxing::Result * result;
    
    float time;
    string& qr;
    ofxSceneManager& sceneManager;
};
