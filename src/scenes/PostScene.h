#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "ofxJSON.h"

#include "token.h"

class PostScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    PostScene(ofxSceneManager& sm, string& n, string& d, string& u, string& q, ofxJSONElement& r) : sceneManager(sm), node(n),device(d),url(u), qr(q), response(r), ofxScene(POST_SCENE_NAME, false) {
        posted=true;
    }
    
    // scene setup
    void setup() {

        ofPixels img;
        ofLoadImage(img,"logo.png");
        logo.loadData(img);
        logo.setAnchorPercent(0.5,0.5);
        
        posted=false;
                
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {

            ofLogVerbose(POST_SCENE_NAME) << "update enter";
        }
        
        //update();
		
        // call finishedEntering() to indicate scne is done entering
        if(true) {
            finishedEntering();
            ofLogVerbose(POST_SCENE_NAME) << "update enter done";
        }
    }
    
    // normal update
    void update() {
        float t = ofGetElapsedTimef();
        float dt = t - time;
        time = t;
        
        if(!posted){
            // create the url string
            string uri = url;
            
            string varQR = "%Q";
            size_t start_pos_QR = uri.find(varQR);
            if(start_pos_QR != std::string::npos)
                uri.replace(start_pos_QR, varQR.length(), qr);
            else
                uri=uri+qr;
            
            string varNode = "%N";
            size_t start_pos_Node = uri.find(varNode);
            if(start_pos_Node != std::string::npos)
                uri.replace(start_pos_Node, varNode.length(), node);
            
            string varDevice = "%D";
            size_t start_pos_Device = uri.find(varDevice);
            if(start_pos_Device != std::string::npos)
                uri.replace(start_pos_Device, varDevice.length(), device);

            if(uri.substr(0,4).compare("http")!=0)
                uri="http://"+uri;

            ofLogNotice(POST_SCENE_NAME) << "URI: " << uri;
            ofHttpResponse res = ofLoadURL(uri);
            posted=true;
            ofLogNotice(POST_SCENE_NAME) << "HTTP GET: " << res.status;
            if(res.status > 0) {
                if(res.status == 200){
                    bool parsing = response.parse(res.data.getText());
                    if(parsing){
                        string token = APP_TOKEN;
                        if(token.compare(response["token"].asString())==0){
                            ofLogNotice(POST_SCENE_NAME) << "Respuesta: " << res.data.getText();
                            sceneManager.gotoScene(DATOS_SCENE_NAME);
                        }
                        else{
                            ofLogError(POST_SCENE_NAME) << "Token invalido.";
                            sceneManager.gotoScene(ERROR_SCENE_NAME);
                        }
                    }
                    else{
                        ofLogError(POST_SCENE_NAME) << "Problemas con el parseo de la respuesta: " << res.data.getText();
                        sceneManager.gotoScene(ERROR_SCENE_NAME);
                    }
                }
                else{
                    ofLogError(POST_SCENE_NAME) << "Problemas con la URL: " << res.data.getText();
                    sceneManager.gotoScene(ERROR_SCENE_NAME);
                }
            }
            else{
                ofLogError(POST_SCENE_NAME) << "Problemas con la conexión: " << res.data.getText();
                sceneManager.gotoScene(ERROR_SCENE_NAME);
            }
        }
    }
    
    // called when scene is exiting
    void updateExit() {
		
        // called on first exit update
        if(isExitingFirst()) {
            ofLogVerbose(POST_SCENE_NAME) << "update exit";
        }
        
        //update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(true) {
            finishedExiting();
            ofLogVerbose(POST_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(ofGetWidth()*0.5,ofGetHeight()*0.5);
        logo.draw(0,0);
        ofPopMatrix();
    }

#ifdef TARGET_ANDROID
    bool backPressed(){
        sceneManager.gotoScene(QR_SCENE_NAME);
        return true;
    }
#endif
    
    // cleanup
    void exit() {
        posted=true;
        ofLogVerbose(POST_SCENE_NAME) << "exit";
    }
    
    bool posted;
    ofTexture logo;
    float time;
    string& node;
    string& device;
    string& url;
    string& qr;
    ofxJSONElement& response;
    ofxSceneManager& sceneManager;
};
