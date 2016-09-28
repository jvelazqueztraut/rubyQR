#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "Data.h"

class InicioScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    InicioScene(ofxSceneManager& sm, Data& d, ofxAnimatableObject<ofTexture>& i) : sceneManager(sm), data(d), inicio(i), ofxScene(INICIO_SCENE_NAME, false) {
        ofImage img;
        ofLoadImage(img,"00_Inicio/background.png");
        background.loadData(img);
        background.color.setDuration(0.5f);
        
        ofLoadImage(img,"00_Inicio/front.png");
        front.loadData(img);
        front.position.setDuration(2.0f);
        front.color.setDuration(0.5f);
    }
    
    // scene setup
    void setup() {
        background.setColor(ofColor(255,0));

        front.setPosition(-ofGetHeight(),ofGetHeight());
        front.setColor(ofColor(255,255));
        
        data.resetFiltered();
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            background.color.animateTo(ofColor(255,255));
            front.position.animateTo(ofPoint(0,0));
            
            inicio.color.animateTo(ofColor(255,0));
            
            ofLogNotice(INICIO_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(!front.isOrWillBeAnimating()) {
            finishedEntering();
            ofLogNotice(INICIO_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        background.update(dt);
        front.update(dt);
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {
            background.color.animateTo(ofColor(255,0));
            front.color.animateTo(ofColor(255,0));
            
            inicio.color.animateToAfterDelay(ofColor(255,255),1.0f);
            
            ofLogNotice(INICIO_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(!front.isOrWillBeAnimating()) {
            finishedExiting();
            ofLogNotice(INICIO_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        background.draw();
        front.draw();
    }
    
    // cleanup
    void exit() {
        ofLogNotice(INICIO_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        sceneManager.gotoScene(MENU_SCENE_NAME);
    }
    
    ofxAnimatableObject<ofTexture> background;
    ofxAnimatableObject<ofTexture> front;
    float time;
    
    ofxAnimatableObject<ofTexture>& inicio;
    Data& data;
    ofxSceneManager& sceneManager;
};
