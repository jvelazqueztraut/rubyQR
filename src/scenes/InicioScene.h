#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "ofxJSONElement.h"
#include "ofxiOSKeyboard.h"

#define TEXTINPUT_PADDING (5*ofGetWidth()/APP_WIDTH)
#define TEXTINPUT_WIDTH (500*ofGetWidth()/APP_WIDTH)
#define TEXTINPUT_HEIGHT (50*ofGetWidth()/APP_WIDTH)

class InicioScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    InicioScene(ofxSceneManager& sm, string& n, string& d, string& u) : sceneManager(sm), node(n), device(d), url(u), ofxScene(INICIO_SCENE_NAME, false) {
        font.load("fonts/Calibri/calibri.ttf",24*ofGetWidth()/APP_WIDTH);
        hints.load("fonts/Calibri/CalibriL.ttf",14*ofGetWidth()/APP_WIDTH);
        loginText.load("fonts/Calibri/calibri.ttf",24*ofGetWidth()/APP_WIDTH);
        
        loginButton.x=0;
        loginButton.y=0;
        loginButton.width=BUTTON_WIDTH;
        loginButton.height=BUTTON_HEIGHT;
        
        iOSScale = 1.0;
        
        if(ofxiOSGetOFWindow()->isRetinaEnabled() && ofxiOSGetOFWindow()->isRetinaSupportedOnDevice()){
            iOSScale/=ofxiOSGetOFWindow()->getRetinaScale();
        }
        
        nodeInputBounds.set(ofGetWidth()*0.5-TEXTINPUT_WIDTH/2-TEXTINPUT_PADDING,ofGetHeight()*0.5-TEXTINPUT_HEIGHT*1.75-TEXTINPUT_PADDING-font.getLineHeight(),TEXTINPUT_WIDTH,TEXTINPUT_HEIGHT);
        nodeInput = new ofxiOSKeyboard(0,0,nodeInputBounds.width,nodeInputBounds.height);
        nodeInput->setVisible(true);
        nodeInput->setBgColor(255, 255, 255, 0);
        nodeInput->setFontColor(255,255,255, 255);
        nodeInput->setFontSize(24*iOSScale*ofGetHeight()/APP_HEIGHT);
        
        deviceInputBounds.set(ofGetWidth()*0.5-TEXTINPUT_WIDTH/2-TEXTINPUT_PADDING,ofGetHeight()*0.5-TEXTINPUT_PADDING-font.getLineHeight(),TEXTINPUT_WIDTH,TEXTINPUT_HEIGHT);
        deviceInput = new ofxiOSKeyboard(0,0,deviceInputBounds.width,deviceInputBounds.height);
        deviceInput->setVisible(true);
        deviceInput->setBgColor(255, 255, 255, 0);
        deviceInput->setFontColor(255,255,255, 255);
        deviceInput->setFontSize(24*iOSScale*ofGetHeight()/APP_HEIGHT);
        
        urlInputBounds.set(ofGetWidth()*0.5-TEXTINPUT_WIDTH/2-TEXTINPUT_PADDING,ofGetHeight()*0.5+TEXTINPUT_HEIGHT*1.75-TEXTINPUT_PADDING-font.getLineHeight(),TEXTINPUT_WIDTH,TEXTINPUT_HEIGHT);
        urlInput = new ofxiOSKeyboard(0,0,urlInputBounds.width,urlInputBounds.height);
        urlInput->setVisible(true);
        urlInput->setBgColor(255, 255, 255, 0);
        urlInput->setFontColor(255,255,255, 255);
        urlInput->setFontSize(24*iOSScale*ofGetHeight()/APP_HEIGHT);
    }
    
    // scene setup
    void setup() {
        nodeInput->setPosition(nodeInputBounds.x*iOSScale,nodeInputBounds.y*iOSScale-TEXTINPUT_PADDING/iOSScale);
        nodeInput->setText(node);
        
        deviceInput->setPosition(deviceInputBounds.x*iOSScale,deviceInputBounds.y*iOSScale-TEXTINPUT_PADDING/iOSScale);
        deviceInput->setText(device);
        
        
        urlInput->setPosition(urlInputBounds.x*iOSScale,urlInputBounds.y*iOSScale-TEXTINPUT_PADDING/iOSScale);
        urlInput->setText(url);
        
        loginButton.setPosition(ofGetWidth()*0.5-loginButton.width/2,ofGetHeight()-loginButton.height*1.5);
                
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            nodeInput->setVisible(true);
            deviceInput->setVisible(true);
            urlInput->setVisible(true);
            
            ofLogVerbose(INICIO_SCENE_NAME) << "update enter";
        }
        
        update();
		
        // call finishedEntering() to indicate scne is done entering
        if(true) {
            
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
            node=nodeInput->getText();
            
            device=deviceInput->getText();

            url=urlInput->getText();

            
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
            nodeInput->setVisible(false);
            deviceInput->setVisible(false);
            urlInput->setVisible(false);
            
            finishedExiting();
            ofLogVerbose(INICIO_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        ofPushStyle();
        
        ofSetColor(255,255);
        
        ofSetColor(255,200);
        ofDrawLine(nodeInputBounds.x,nodeInputBounds.y+nodeInputBounds.height+2,nodeInputBounds.x+nodeInputBounds.width,nodeInputBounds.y+nodeInputBounds.height+2);
        ofDrawLine(deviceInputBounds.x,deviceInputBounds.y+deviceInputBounds.height+2,deviceInputBounds.x+deviceInputBounds.width,deviceInputBounds.y+deviceInputBounds.height+2);
        ofDrawLine(urlInputBounds.x,urlInputBounds.y+urlInputBounds.height+2,urlInputBounds.x+urlInputBounds.width,urlInputBounds.y+urlInputBounds.height+2);

        
        ofSetColor(255,150);
        hints.drawString("node",nodeInputBounds.x,nodeInputBounds.y);
        hints.drawString("device",deviceInputBounds.x,deviceInputBounds.y);
        hints.drawString("url",urlInputBounds.x,urlInputBounds.y);
        
        ofSetColor(255,200);
        string loginStr = "LOGIN";
        loginText.drawString(loginStr,loginButton.x+loginButton.width/2-loginText.stringWidth(loginStr)/2,loginButton.y+loginButton.height/2+loginText.stringHeight(loginStr)/2);
        ofNoFill();
        ofDrawRectangle(loginButton);

        ofPopStyle();
    }
    
    // cleanup
    void exit() {
        ofLogVerbose(INICIO_SCENE_NAME) << "exit";
    }
    
    void mouseReleased(int x, int y, int button){
        if(isExiting())
            return;
        if(loginButton.inside(x,y)){
            sceneManager.gotoScene(QR_SCENE_NAME);
        }
        
        /*if(nodeInput.getIsEditing()){
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
        }*/
    }
    
    void keyPressed(int key){
        switch(key){
            case OF_KEY_RETURN:
                /*if(nodeInput.getIsEditing()){
                    nodeInput.endEditing();
                    deviceInput.beginEditing();
                }
                else if(deviceInput.getIsEditing()){
                    deviceInput.endEditing();
                    urlInput.beginEditing();
                }
                else if(urlInput.getIsEditing()){
                    urlInput.endEditing();
                }*/
                break;
            default:
                break;
        }
    }
    
    float iOSScale;

    ofxiOSKeyboard * nodeInput;
    ofxiOSKeyboard * deviceInput;
    ofxiOSKeyboard * urlInput;
    ofRectangle nodeInputBounds,deviceInputBounds,urlInputBounds;
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
