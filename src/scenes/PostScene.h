#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "ofxJSON.h"

class PostScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    PostScene(ofxSceneManager& sm, string& n, string& d, string& u, string& q, ofxJSONElement& r) : sceneManager(sm), node(n),device(d),url(u), qr(q), response(r), ofxScene(POST_SCENE_NAME, false) {
        
    }
    
    // scene setup
    void setup() {
                
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            
            ofLogVerbose(POST_SCENE_NAME) << "update enter";
        }
        
        update();
		
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
        
        if(!isEntering() && !isExiting()){
            // create the url string
            string uri = "http://" + url + "/?qr=" + qr;
            ofLogNotice(POST_SCENE_NAME) << "URI: " << uri;
            ofHttpResponse res = ofLoadURL(uri);
            ofLogNotice(POST_SCENE_NAME) << "HTTP GET: " << res.status;
            if(res.status > 0) {
                if(res.status == 200){
                    bool parsing = response.parse(res.data.getText());
                    if(parsing){
                        ofLogNotice(POST_SCENE_NAME) << "Respuesta: " << res.data.getText();
                        sceneManager.gotoScene(DATOS_SCENE_NAME);
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
        
        update();
		
        // call finishedExiting() to indicate scene is done exiting
        if(true) {
            finishedExiting();
            ofLogVerbose(POST_SCENE_NAME) << "update exit done";
        }
    }
    
    // draw
    void draw() {

    }

#ifdef TARGET_ANDROID
    bool backPressed(){
        sceneManager.gotoScene(QR_SCENE_NAME);
        return true;
    }
#endif
    
    // cleanup
    void exit() {
        ofLogVerbose(POST_SCENE_NAME) << "exit";
    }
    
    ofHttpResponse res;
    
    float time;
    string& node;
    string& device;
    string& url;
    string& qr;
    ofxJSONElement& response;
    ofxSceneManager& sceneManager;
};
