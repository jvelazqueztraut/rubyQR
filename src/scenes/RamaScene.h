#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"

#define RAMA_MARGIN 550

class RamaScene : public ofxScene {
public:
    
    // set the scene name through the base class initializer
    RamaScene(ofxSceneManager& sm, Data& d) : sceneManager(sm), data(d), ofxScene(RAMA_SCENE_NAME, false) {
        ofImage img;
        ofLoadImage(img,"02_Rama/option.png");
        option.loadData(img);
        option.setAnchorPercent(0.475f,0.475f);
        
        ofLoadImage(img,"02_Rama/titulo.png");
        title.loadData(img);
        title.setAnchorPercent(0.5,0.5);
        title.setPosition(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.2));
        title.color.setDuration(0.5f);
        title.size.setDuration(0.5f);
    }
    
    // scene setup
    void setup() {
        title.setColor(ofColor(255,0));
        
        int total = data.filteredRamas.size();
        
        ramas.clear();
        ramas.assign(total,ofxAnimatableObject<ofTrueTypeFont>());
        
        for(int i=0; i<total; i++){
            ramas[i].ofTrueTypeFont::load("DINBold.otf",36);
            ramas[i].ofTrueTypeFont::setLineHeight(32);
            ramas[i].setText(data.filteredRamas[i]->nombre);
            ramas[i].setAnchorPercent(0.5,0.5);
            ramas[i].setSize(0.5f);
            if(i<floor(total/2))
                ramas[i].setPosition(ofGetWidth()*0.5-(floor(total/2)*RAMA_MARGIN)/2.0f + i*RAMA_MARGIN + RAMA_MARGIN/2, ofGetHeight()*0.5 - 100);
            else
                ramas[i].setPosition(ofGetWidth()*0.5-((total-floor(total/2))*RAMA_MARGIN)/2.0f + (i-floor(total/2))*RAMA_MARGIN + RAMA_MARGIN/2, ofGetHeight()*0.5 + 100);
            ramas[i].setColor(ofColor(0,0));
            ramas[i].color.setDuration(0.5f);
            ramas[i].size.setDuration(0.5f);
        }
        
        selected=0;
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            title.color.animateTo(ofColor(255,255));
            for(int i=0;i<ramas.size();i++){
                ramas[i].color.animateToAfterDelay(ofColor(0,255),i*0.25f);
                ramas[i].size.animateToAfterDelay(1.0f,i*0.25f);
            }
            
            ofLogNotice(RAMA_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(!ramas[selected].isOrWillBeAnimating()) {
            finishedEntering();
            ofLogNotice(RAMA_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        title.update(dt);
        for(int i=0;i<ramas.size();i++){
            ramas[i].update(dt);
        }
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {
            title.color.animateTo(ofColor(255,0));
            
            for(int i=0;i<ramas.size();i++){
                ramas[i].color.animateTo(ofColor(0,0));
            }

            ofLogNotice(RAMA_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(!ramas[selected].isOrWillBeAnimating()) {
            finishedExiting();            
            ofLogNotice(RAMA_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        title.draw();

        for(int i=0;i<ramas.size();i++){
            ofPushMatrix();
            ofTranslate(ramas[i].position.getCurrentPosition());
            ofScale(ramas[i].size.getCurrentValue(),ramas[i].size.getCurrentValue());
            ofPushStyle();
            ofSetColor(ofColor(255,ramas[i].color.getCurrentColor().a));
            option.draw(0,0);
            ofPopStyle();
            ofPopMatrix();
            ramas[i].draw();
        }
    }
    
    // cleanup
    void exit() {
        ofLogNotice(RAMA_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        
        for(int i=0;i<ramas.size();i++){
            if(ramas[i].inside(ofPoint(x,y))){
                selected=i;
                data.applyRamaFilter(data.filteredRamas[i]);
                ramas[i].size.animateTo(1.15);
                if(!data.provinciaFilterApplied && data.filteredProvincias.size()>1)
                    sceneManager.gotoScene(PROVINCIA_SCENE_NAME);
                else if(!data.universidadFilterApplied && data.filteredUniversidades.size()>1)
                    sceneManager.gotoScene(UNIVERSIDAD_SCENE_NAME);
                else
                    sceneManager.gotoScene(INFO_SCENE_NAME);
                break;
            }
        }
    }
    
    vector< ofxAnimatableObject<ofTrueTypeFont> > ramas;
    int selected;
    ofxAnimatableObject<ofTexture> title;
    ofTexture option;
    float time;

    Data& data;
    ofxSceneManager& sceneManager;
};
