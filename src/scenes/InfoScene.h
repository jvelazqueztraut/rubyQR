#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "Data.h"

class InfoScene : public ofxScene {
    
public:
    
    // set the scene name through the base class initializer
    InfoScene(ofxSceneManager& sm, Data& d) : sceneManager(sm), data(d), ofxScene(INFO_SCENE_NAME, false) {
        ofImage img;
        ofLoadImage(img,"05_Info/background.png");
        background.loadData(img);
        background.color.setDuration(1.0f);
        
        ofLoadImage(img,"05_Info/titulo.png");
        title.loadData(img);
        title.setAnchorPercent(0.0f,0.0f);
        
        rama.ofTrueTypeFont::load("DINBold.otf",44);
        rama.ofTrueTypeFont::setLineHeight(32);
        rama.setAnchorPercent(0.0,0.5);
        rama.setSize(1.);
        rama.setPosition(70, 350);
        
        provincia.ofTrueTypeFont::load("DINRegular.otf",44);
        provincia.ofTrueTypeFont::setLineHeight(32);
        provincia.setAnchorPercent(0.0,0.5);
        provincia.setSize(1.);
        provincia.setPosition(70, 410);
        
        universidad.ofTrueTypeFont::load("DINRegular.otf",44);
        universidad.ofTrueTypeFont::setLineHeight(32);
        universidad.setAnchorPercent(0.0,0.5);
        universidad.setSize(1.);
        universidad.setPosition(70, 470);
        
        disciplines.assign(5,ofxAnimatableObject<ofTexture>());
        
        ofLoadImage(img,"05_Info/Sociales.png");
        disciplines[0].loadData(img);

        ofLoadImage(img,"05_Info/Humanas.png");
        disciplines[1].loadData(img);
        
        ofLoadImage(img,"05_Info/Aplicadas.png");
        disciplines[2].loadData(img);
        
        ofLoadImage(img,"05_Info/Salud.png");
        disciplines[3].loadData(img);
        
        ofLoadImage(img,"05_Info/Basicas.png");
        disciplines[4].loadData(img);
        
        for(int i =0; i<disciplines.size(); i++){
            disciplines[i].setAnchorPercent(0.5,0.5);
            disciplines[i].setPosition(ofGetWidth()*0.5,ofGetHeight()*0.7);
        }
        selected = 0;
    }
    
    // scene setup
    void setup() {
        background.setColor(ofColor(255,0));
        title.setPosition(ofPoint(0,-title.getHeight()));
        
        rama.setText("Ejemplos de "+data.filteredRamas[0]->nombre+":");
        rama.setColor(ofColor(255,0));

        provincia.setText(data.filteredProvincias[0]->nombre);
        provincia.setColor(ofColor(255,0));

        universidad.setText(data.filteredUniversidades[0]->nombre);
        universidad.setColor(ofColor(255,0));
        
        if(data.filteredRamas[0]->nombre.find("Social")!=std::string::npos){
            selected=0;
        }
        else if(data.filteredRamas[0]->nombre.find("Humanas")!=std::string::npos){
            selected=1;
        }
        else if(data.filteredRamas[0]->nombre.find("Aplicadas")!=std::string::npos){
            selected=2;
        }
        else if(data.filteredRamas[0]->nombre.find("Salud")!=std::string::npos){
            selected=3;
        }
        else{
            selected=4;
        }
        
        for(int i =0; i<disciplines.size(); i++){
            disciplines[i].setColor(ofColor(255,0));
            disciplines[i].setSize(0.5);
        }
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            background.color.animateTo(ofColor(255,255));
            title.position.animateTo(ofPoint(0,0));
            
            rama.color.animateTo(ofColor(255,255));
            provincia.color.animateTo(ofColor(255,255));
            universidad.color.animateTo(ofColor(255,255));
            
            disciplines[selected].color.animateTo(ofColor(255,255));
            disciplines[selected].size.animateTo(1.0f);
            
            ofLogNotice(INFO_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(!title.isOrWillBeAnimating()) {
            finishedEntering();
            ofLogNotice(INFO_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        
        rama.update(dt);
        provincia.update(dt);
        universidad.update(dt);
        
        disciplines[selected].update(dt);
        
        background.update(dt);
        title.update(dt);
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {
            background.color.animateTo(ofColor(255,0));
            title.position.animateTo(ofPoint(0,-title.getHeight()));
            
            rama.color.animateTo(ofColor(255,0));
            provincia.color.animateTo(ofColor(255,0));
            universidad.color.animateTo(ofColor(255,0));
            
            disciplines[selected].color.animateTo(ofColor(255,0));
            
            ofLogNotice(INFO_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(!title.isOrWillBeAnimating()) {
            finishedExiting();
            
            ofLogNotice(INFO_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        background.draw();
        title.draw();
        disciplines[selected].draw();
        rama.draw();
        //provincia.draw();
        //universidad.draw();
    }
    
    // cleanup
    void exit() {
        ofLogNotice(INFO_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        sceneManager.gotoScene(INICIO_SCENE_NAME);
    }
    
    ofxAnimatableObject<ofTexture> background;
    ofxAnimatableObject<ofTexture> title;
    vector< ofxAnimatableObject<ofTexture> > disciplines;
    int selected;
    ofxAnimatableObject<ofTrueTypeFont> rama;
    ofxAnimatableObject<ofTrueTypeFont> provincia;
    ofxAnimatableObject<ofTrueTypeFont> universidad;
    float time;
    
    Data& data;
    ofxSceneManager& sceneManager;
};
