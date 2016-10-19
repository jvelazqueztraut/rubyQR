#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "ofxJSONElement.h"
#include "ofxAndroidExtendedEditText.h"

#define TEXTINPUT_PADDING (10*ofGetWidth()/APP_WIDTH)
#define TEXTINPUT_WIDTH (550*ofGetWidth()/APP_WIDTH)
#define TEXTINPUT_HEIGHT (50*ofGetWidth()/APP_WIDTH)

#define TEXTINPUT_CLEAR (40*ofGetWidth()/APP_WIDTH)
#define TEXTINPUT_CLEAR_MARGIN (5*ofGetWidth()/APP_WIDTH)

class InicioScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    InicioScene(ofxSceneManager& sm, string& n, string& d, string& u) : sceneManager(sm), node(n), device(d), url(u), ofxScene(INICIO_SCENE_NAME, false) {
        font.load("fonts/Calibri/calibri.ttf",16*ofGetWidth()/APP_WIDTH);
        hints.load("fonts/Calibri/CalibriL.ttf",14*ofGetWidth()/APP_WIDTH);
        loginText.load("fonts/Calibri/calibri.ttf",24*ofGetWidth()/APP_WIDTH);
        
        loginButton.x=0;
        loginButton.y=0;
        loginButton.width=BUTTON_WIDTH;
        loginButton.height=BUTTON_HEIGHT;
        
        nodeInputBounds.set(ofGetWidth()*0.5-TEXTINPUT_WIDTH/2,ofGetHeight()*0.35-TEXTINPUT_HEIGHT*1.75-TEXTINPUT_PADDING-font.getLineHeight(),TEXTINPUT_WIDTH,TEXTINPUT_HEIGHT);
        /*nodeInputBounds.x = 0;
        nodeInputBounds.y = 0;
        nodeInputBounds.width = TEXTINPUT_WIDTH;
        nodeInputBounds.height = TEXTINPUT_HEIGHT;
        nodeInput.setFont(font);
        nodeInput.disable();*/
        
        deviceInputBounds.set(ofGetWidth()*0.5-TEXTINPUT_WIDTH/2,ofGetHeight()*0.35-TEXTINPUT_PADDING-font.getLineHeight(),TEXTINPUT_WIDTH,TEXTINPUT_HEIGHT);
        /*deviceInputBounds.x = 0;
        deviceInputBounds.y = 0;
        deviceInputBounds.width = TEXTINPUT_WIDTH;
        deviceInputBounds.height = TEXTINPUT_HEIGHT;
        deviceInput.setFont(font);
        deviceInput.disable();*/
        
        urlInputBounds.set(ofGetWidth()*0.5-TEXTINPUT_WIDTH/2,ofGetHeight()*0.35+TEXTINPUT_HEIGHT*1.75-TEXTINPUT_PADDING-font.getLineHeight(),TEXTINPUT_WIDTH,TEXTINPUT_HEIGHT);
        /*urlInputBounds.x = 0;
        urlInputBounds.y = 0;
        urlInputBounds.width = TEXTINPUT_WIDTH;
        urlInputBounds.height = TEXTINPUT_HEIGHT;
        urlInput.setFont(font);
        urlInput.disable();*/

        nodeInputClear.set(nodeInputBounds.x+nodeInputBounds.width-TEXTINPUT_CLEAR,nodeInputBounds.y+TEXTINPUT_CLEAR_MARGIN,TEXTINPUT_CLEAR,TEXTINPUT_CLEAR);
        deviceInputClear.set(deviceInputBounds.x+deviceInputBounds.width-TEXTINPUT_CLEAR,deviceInputBounds.y+TEXTINPUT_CLEAR_MARGIN,TEXTINPUT_CLEAR,TEXTINPUT_CLEAR);
        urlInputClear.set(urlInputBounds.x+urlInputBounds.width-TEXTINPUT_CLEAR,urlInputBounds.y+TEXTINPUT_CLEAR_MARGIN,TEXTINPUT_CLEAR,TEXTINPUT_CLEAR);
    }
    
    // scene setup
    void setup() {
        nodeInput.setup();
        nodeInput.add(node,nodeInputBounds.x-TEXTINPUT_PADDING,nodeInputBounds.y-TEXTINPUT_PADDING,16*ofGetWidth()/APP_WIDTH,"Ingrese el nodo");
        //nodeInput.disable();
        
        deviceInput.setup();
        deviceInput.add(device,deviceInputBounds.x-TEXTINPUT_PADDING,deviceInputBounds.y-TEXTINPUT_PADDING,16*ofGetWidth()/APP_WIDTH,"Ingrese el dispositivo");
        //deviceInput.disable();
        
        urlInput.setup();
        urlInput.add(url,urlInputBounds.x-TEXTINPUT_PADDING,urlInputBounds.y-TEXTINPUT_PADDING,16*ofGetWidth()/APP_WIDTH,"Ingrese la URL");
        //urlInput.disable();
        
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
            /*nodeInput.enable();
            nodeInput.beginEditing();
            
            deviceInput.enable();
            
            urlInput.enable();*/
            
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
            node=nodeInput.getText();
            //nodeInput.endEditing();
            
            device=deviceInput.getText();
            //deviceInput.endEditing();
            
            url=urlInput.getText();
            //urlInput.endEditing();

            ofLogNotice(INICIO_SCENE_NAME) << "NODE: " << node;
            ofLogNotice(INICIO_SCENE_NAME) << "DEVICE: " << device;
            ofLogNotice(INICIO_SCENE_NAME) << "URL: " << url;
            
            ofxJSONElement login;
            login["node"]=node;
            login["device"]=device;
            login["url"]=url;
            login.save(ofToDataPath("login.json"));

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
        
        ofSetColor(255,200);
        ofDrawLine(nodeInputBounds.x,nodeInputBounds.y+nodeInputBounds.height+2*ofGetWidth()/APP_WIDTH,nodeInputBounds.x+nodeInputBounds.width,nodeInputBounds.y+nodeInputBounds.height+2*ofGetWidth()/APP_WIDTH);
        ofDrawLine(deviceInputBounds.x,deviceInputBounds.y+deviceInputBounds.height+2*ofGetWidth()/APP_WIDTH,deviceInputBounds.x+deviceInputBounds.width,deviceInputBounds.y+deviceInputBounds.height+2*ofGetWidth()/APP_WIDTH);
        ofDrawLine(urlInputBounds.x,urlInputBounds.y+urlInputBounds.height+2*ofGetWidth()/APP_WIDTH,urlInputBounds.x+urlInputBounds.width,urlInputBounds.y+urlInputBounds.height+2*ofGetWidth()/APP_WIDTH);

        ofDrawLine(nodeInputClear.x+TEXTINPUT_CLEAR_MARGIN,nodeInputClear.y+TEXTINPUT_CLEAR_MARGIN,nodeInputClear.x+nodeInputClear.width-TEXTINPUT_CLEAR_MARGIN,nodeInputClear.y+nodeInputClear.height-TEXTINPUT_CLEAR_MARGIN);
        ofDrawLine(nodeInputClear.x+TEXTINPUT_CLEAR_MARGIN,nodeInputClear.y+nodeInputClear.height-TEXTINPUT_CLEAR_MARGIN,nodeInputClear.x+nodeInputClear.width-TEXTINPUT_CLEAR_MARGIN,nodeInputClear.y+TEXTINPUT_CLEAR_MARGIN);
        ofDrawLine(deviceInputClear.x+TEXTINPUT_CLEAR_MARGIN,deviceInputClear.y+TEXTINPUT_CLEAR_MARGIN,deviceInputClear.x+deviceInputClear.width-TEXTINPUT_CLEAR_MARGIN,deviceInputClear.y+urlInputClear.height-TEXTINPUT_CLEAR_MARGIN);
        ofDrawLine(deviceInputClear.x+TEXTINPUT_CLEAR_MARGIN,deviceInputClear.y+deviceInputClear.height-TEXTINPUT_CLEAR_MARGIN,deviceInputClear.x+deviceInputClear.width-TEXTINPUT_CLEAR_MARGIN,deviceInputClear.y+TEXTINPUT_CLEAR_MARGIN);
        ofDrawLine(urlInputClear.x+TEXTINPUT_CLEAR_MARGIN,urlInputClear.y+TEXTINPUT_CLEAR_MARGIN,urlInputClear.x+urlInputClear.width-TEXTINPUT_CLEAR_MARGIN,urlInputClear.y+urlInputClear.height-TEXTINPUT_CLEAR_MARGIN);
        ofDrawLine(urlInputClear.x+TEXTINPUT_CLEAR_MARGIN,urlInputClear.y+urlInputClear.height-TEXTINPUT_CLEAR_MARGIN,urlInputClear.x+urlInputClear.width-TEXTINPUT_CLEAR_MARGIN,urlInputClear.y+TEXTINPUT_CLEAR_MARGIN);

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
        nodeInput.remove();
        deviceInput.remove();
        urlInput.remove();

        ofLogVerbose(INICIO_SCENE_NAME) << "exit";
    }
    
    void mouseReleased(int x, int y, int button){
        if(isExiting())
            return;
        if(loginButton.inside(x,y)){
            sceneManager.gotoScene(QR_SCENE_NAME);
        }

        if(nodeInputClear.inside(x,y)){
            nodeInput.setText("");
        }
        if(deviceInputClear.inside(x,y)){
            deviceInput.setText("");
        }
        if(urlInputClear.inside(x,y)){
            urlInput.setText("");
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
        ofLogWarning(INICIO_SCENE_NAME)<<"Key pressed: "<<key;
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
#ifdef TARGET_ANDROID
    void resume(){
        setup();
        ofLogError(INICIO_SCENE_NAME)<<"Reload textures now!";
    }
#endif

    ofxAndroidExtendedEditText nodeInput;
    ofxAndroidExtendedEditText deviceInput;
    ofxAndroidExtendedEditText urlInput;
    ofRectangle nodeInputBounds,deviceInputBounds,urlInputBounds;
    ofRectangle nodeInputClear,deviceInputClear,urlInputClear;
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
