#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "ofxJSON.h"

#define DATOS_WIDTH (500*ofGetWidth()/APP_WIDTH)
#define DATOS_HEIGHT (50*ofGetWidth()/APP_WIDTH)

class DatosScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    DatosScene(ofxSceneManager& sm, ofxJSONElement& r) : sceneManager(sm), response(r), ofxScene(DATOS_SCENE_NAME, false) {
        title.load("fonts/Futura/FuturaStd-Heavy.otf",36*ofGetWidth()/APP_WIDTH);
        title.setText("");
        title.setAnchorPercent(0.0,1.0);
        title.setPosition(ofPoint(ofGetWidth()*0.5-DATOS_WIDTH/2,APP_HEIGHT*0.2));
        
        status.load("fonts/Futura/FuturaStd-Medium.otf",24*ofGetWidth()/APP_WIDTH);
        status.setText("");
        status.setAnchorPercent(0.0,1.0);
        
        last.load("fonts/Futura/FuturaStd-Medium.otf",18*ofGetWidth()/APP_WIDTH);
        last.setText("");
        last.setAnchorPercent(0.0,1.0);
        
        scanText.load("fonts/Calibri/calibri.ttf",24*ofGetWidth()/APP_WIDTH);
        
        scanButton.x=0;
        scanButton.y=0;
        scanButton.width=BUTTON_WIDTH;
        scanButton.height=BUTTON_HEIGHT;
        
    }
    
    // scene setup
    void setup() {
        
        fields.clear();
        
        if(response["signup"].size()>0){
            title.setText(response["signup"]["d1"].asString());
            
            for(int i=0;i<response["signup"].size()-3;i++){
                ofxAnimatableObject<ofTrueTypeFont> field;
                field.load("fonts/Futura/FuturaStd-Medium.otf",16*ofGetWidth()/APP_WIDTH);
                field.setText(response["signup"]["d"+ofToString(i+2)].asString());
                field.setAnchorPercent(0.0,1.0);
                field.setPosition(ofPoint(ofGetWidth()*0.5-DATOS_WIDTH/2,ofGetHeight()*0.2+DATOS_HEIGHT*(i+1)));
                field.setColor(ofColor(255,0));
                field.setSize(0.8);
                fields.push_back(field);
            }
            
            std::size_t found = response["signup"]["status"].asString().find("aprov");
            if(found!=std::string::npos){
                status.setText("APROBADO");
            }
            else{
                status.setText("RECHAZADO");
            }
            last.setText("Último ingreso " + response["signup"]["last"].asString());
        }
        else{
            title.setText("No hay datos disponibles");
            
            ofxAnimatableObject<ofTrueTypeFont> field;
            field.load("fonts/Futura/FuturaStd-Medium.otf",16*ofGetWidth()/APP_WIDTH);
            field.setText("");
            field.setAnchorPercent(0.0,1.0);
            field.setPosition(ofPoint(ofGetWidth()*0.5-DATOS_WIDTH/2,ofGetHeight()*0.2+DATOS_HEIGHT));
            field.setColor(ofColor(255,0));
            field.setSize(0.8);
            fields.push_back(field);
            
            status.setText("");
            last.setText("Por favor scanee otro código QR");
        }
        
        if(status.text=="APROBADO"){
            statusIcon.load("check.png");
            statusIcon.setAnchorPercent(0.5,0.5);
        }
        else{
            statusIcon.load("alert.png");
            statusIcon.setAnchorPercent(0.5,0.5);
        }
        
        status.setColor(ofColor(255,0));
        status.setSize(0.8);
        status.setPosition(fields.back().position.getCurrentPosition()+ofPoint(50,DATOS_HEIGHT*2));
        
        last.setColor(ofColor(255,0));
        last.setSize(0.8);
        last.setPosition(fields.back().position.getCurrentPosition()+ofPoint(0,DATOS_HEIGHT*3.5));
        
        title.setColor(ofColor(255,0));
        title.setSize(0.8);
        
        scanButton.setPosition(ofGetWidth()*0.5-scanButton.width/2,ofGetHeight()-scanButton.height*1.5);
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            title.color.animateTo(ofColor(255,255));
            title.size.animateTo(1.0);
            
            for(int i=0;i<fields.size();i++){
                fields[i].color.animateToAfterDelay(ofColor(255,255),i*0.5);
                fields[i].size.animateToAfterDelay(1.0,i*0.5);
            }
            
            status.color.animateTo(ofColor(255,255));
            status.size.animateTo(1.0);
            
            last.color.animateTo(ofColor(255,255));
            last.size.animateTo(1.0);
            
            ofLogVerbose(DATOS_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(!title.isOrWillBeAnimating()) {
            
            finishedEntering();
            ofLogVerbose(DATOS_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        
        title.update(dt);
        
        for(int i=0;i<fields.size();i++){
            fields[i].update(dt);
        }
        
        status.update(dt);
        last.update(dt);

    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {
            ofLogVerbose(DATOS_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(true) {
            finishedExiting();
            ofLogVerbose(DATOS_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        title.draw();
        for(int i=0;i<fields.size();i++){
            fields[i].draw();
        }
        ofDrawLine(fields.back().position.getCurrentPosition()+ofPoint(0,DATOS_HEIGHT),fields.back().position.getCurrentPosition()+ofPoint(DATOS_WIDTH,DATOS_HEIGHT));
        
        statusIcon.draw(status.position.getCurrentPosition()-ofPoint(35,0));
        
        status.draw();
        last.draw();
        
        ofPushStyle();
        ofSetColor(255,200);
        string scanStr = "SCAN";
        scanText.drawString(scanStr,scanButton.x+scanButton.width/2-scanText.stringWidth(scanStr)/2,scanButton.y+scanButton.height/2+scanText.stringHeight(scanStr)/2);
        ofNoFill();
        ofDrawRectangle(scanButton);
        ofPopStyle();

    }

#ifdef TARGET_ANDROID
    bool backPressed(){
        sceneManager.gotoScene(QR_SCENE_NAME);
        return true;
    }
#endif
    
    // cleanup
    void exit() {
        ofLogVerbose(DATOS_SCENE_NAME) << "exit";
    }
    
    void mouseReleased(int x, int y, int button){
        if(isExiting())
            return;
        if(scanButton.inside(x,y)){
            sceneManager.gotoScene(QR_SCENE_NAME);
        }
    }
    
    float time;
    ofxJSONElement& response;
    
    ofRectangle scanButton;
    ofTrueTypeFont scanText;
    
    ofxAnimatableObject<ofTrueTypeFont> title,status,last;
    vector< ofxAnimatableObject<ofTrueTypeFont> > fields;
    
    ofImage statusIcon;
    
    ofxSceneManager& sceneManager;
};
