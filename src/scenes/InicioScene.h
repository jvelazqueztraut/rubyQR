#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "ofxTextInputField.h"
#include "ofxJSONElement.h"

#define TEXTINPUT_PADDING 3
#define TEXTINPUT_WIDTH 350
#define TEXTINPUT_HEIGHT 30

#define BUTTON_WIDTH 350
#define BUTTON_HEIGHT 50

class InicioScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    InicioScene(ofxSceneManager& sm, string& n, string& d, string& u) : sceneManager(sm), node(n), device(d), url(u), ofxScene(INICIO_SCENE_NAME, false) {
        font.load("fonts/Calibri/calibri.ttf",16);
        hints.load("fonts/Calibri/CalibriL.ttf",10);
        loginText.load("fonts/Calibri/calibri.ttf",18);
        
        loginButton.x=0;
        loginButton.y=0;
        loginButton.width=BUTTON_WIDTH;
        loginButton.height=BUTTON_HEIGHT;
        
        nodeInput.setup();
        nodeInput.bounds.x = 0;
        nodeInput.bounds.y = 0;
        nodeInput.bounds.width = TEXTINPUT_WIDTH;
        nodeInput.bounds.height = TEXTINPUT_HEIGHT;
        nodeInput.setFont(font);
        nodeInput.disable();
        
        deviceInput.setup();
        deviceInput.bounds.x = 0;
        deviceInput.bounds.y = 0;
        deviceInput.bounds.width = TEXTINPUT_WIDTH;
        deviceInput.bounds.height = TEXTINPUT_HEIGHT;
        deviceInput.setFont(font);
        deviceInput.disable();
        
        urlInput.setup();
        urlInput.bounds.x = 0;
        urlInput.bounds.y = 0;
        urlInput.bounds.width = TEXTINPUT_WIDTH;
        urlInput.bounds.height = TEXTINPUT_HEIGHT;
        urlInput.setFont(font);
        urlInput.disable();
        
    }
    
    // scene setup
    void setup() {
        nodeInput.bounds.setPosition(ofPoint(ofGetWidth()*0.5-TEXTINPUT_WIDTH/2,ofGetHeight()*0.5-TEXTINPUT_HEIGHT*1.75)-ofPoint(TEXTINPUT_PADDING,TEXTINPUT_PADDING+font.getLineHeight()));
        nodeInput.text=node;
        nodeInput.disable();
        
        deviceInput.bounds.setPosition(ofPoint(ofGetWidth()*0.5-TEXTINPUT_WIDTH/2,ofGetHeight()*0.5)-ofPoint(TEXTINPUT_PADDING,TEXTINPUT_PADDING+font.getLineHeight()));
        deviceInput.text=device;
        deviceInput.disable();
        
        urlInput.bounds.setPosition(ofPoint(ofGetWidth()*0.5-TEXTINPUT_WIDTH/2,ofGetHeight()*0.5+TEXTINPUT_HEIGHT*1.75)-ofPoint(TEXTINPUT_PADDING,TEXTINPUT_PADDING+font.getLineHeight()));
        urlInput.text=url;
        urlInput.disable();
        
        loginButton.setPosition(ofGetWidth()*0.5-loginButton.width/2,ofGetHeight()-loginButton.height*1.5);
                
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            
            ofLogVerbose(INICIO_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(true) {
            nodeInput.enable();
            nodeInput.beginEditing();
            
            deviceInput.enable();
            
            urlInput.enable();
            
            finishedEntering();
            ofLogVerbose(INICIO_SCENE_NAME) << "update enter done";
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
            node=nodeInput.text;
            nodeInput.endEditing();
            nodeInput.disable();
            
            device=deviceInput.text;
            deviceInput.endEditing();
            deviceInput.disable();
            
            url=urlInput.text;
            urlInput.endEditing();
            urlInput.disable();
            
            ofLogNotice(INICIO_SCENE_NAME) << "NODE: " << node;
            ofLogNotice(INICIO_SCENE_NAME) << "DEVICE: " << device;
            ofLogNotice(INICIO_SCENE_NAME) << "URL: " << url;
            
            ofxJSONElement login;
            login["node"]=node;
            login["device"]=device;
            login["url"]=url;
            login.save("login.json");

            ofLogVerbose(INICIO_SCENE_NAME) << "update exit";
        }
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(true) {
            finishedExiting();
            ofLogVerbose(INICIO_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        ofPushStyle();
        
        ofSetColor(255,255);
        nodeInput.draw();
        deviceInput.draw();
        urlInput.draw();
        
        ofSetColor(255,200);
        ofDrawLine(nodeInput.bounds.x,nodeInput.bounds.y+nodeInput.bounds.height+2,nodeInput.bounds.x+nodeInput.bounds.width,nodeInput.bounds.y+nodeInput.bounds.height+2);
        ofDrawLine(deviceInput.bounds.x,deviceInput.bounds.y+deviceInput.bounds.height+2,deviceInput.bounds.x+deviceInput.bounds.width,deviceInput.bounds.y+deviceInput.bounds.height+2);
        ofDrawLine(urlInput.bounds.x,urlInput.bounds.y+urlInput.bounds.height+2,urlInput.bounds.x+urlInput.bounds.width,urlInput.bounds.y+urlInput.bounds.height+2);

        
        ofSetColor(255,150);
        hints.drawString("node",nodeInput.bounds.x,nodeInput.bounds.y);
        hints.drawString("device",deviceInput.bounds.x,deviceInput.bounds.y);
        hints.drawString("url",urlInput.bounds.x,urlInput.bounds.y);
        
        ofSetColor(255,200);
        string loginStr = "LOGIN";
        loginText.drawString(loginStr,loginButton.x+loginButton.width/2-loginText.stringWidth(loginStr)/2,loginButton.y+loginButton.height/2+loginText.stringHeight(loginStr)/2);
        ofNoFill();
        ofDrawRectangle(loginButton);

        ofPopStyle();
    }
    
    // cleanup
    void exit() {
        nodeInput.disable();
        deviceInput.disable();
        urlInput.disable();
        ofLogVerbose(INICIO_SCENE_NAME) << "exit";
    }
    
    void mouseReleased(int x, int y, int button){
        if(isExiting())
            return;
        if(loginButton.inside(x,y)){
            sceneManager.gotoScene(QR_SCENE_NAME);
        }
        
        if(nodeInput.getIsEditing()){
            deviceInput.endEditing();
            urlInput.endEditing();
        }
        else if(deviceInput.getIsEditing()){
            nodeInput.endEditing();
            urlInput.endEditing();
        }
        else if(urlInput.getIsEditing()){
            nodeInput.endEditing();
            deviceInput.endEditing();
        }
    }
    
    void keyPressed(int key){
        switch(key){
            case OF_KEY_RETURN:
                if(nodeInput.getIsEditing()){
                    nodeInput.endEditing();
                    deviceInput.beginEditing();
                }
                else if(deviceInput.getIsEditing()){
                    deviceInput.endEditing();
                    urlInput.beginEditing();
                }
                else if(urlInput.getIsEditing()){
                    urlInput.endEditing();
                }
                break;
            default:
                break;
        }
    }
    
    ofxTextInputField nodeInput,deviceInput,urlInput;
    ofTrueTypeFont font;
    ofTrueTypeFont hints;
    ofRectangle loginButton;
    ofTrueTypeFont loginText;
    float time;
    string& node;
    string& device;
    string& url;
    ofxSceneManager& sceneManager;
};
