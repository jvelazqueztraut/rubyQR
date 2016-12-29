#pragma once

#include <ofxAppUtils.h>
#include "scenes.h"
#include "ofxAnimatableObject.h"
#include "ofxJSON.h"

#include "token.h"

#define DATOS_WIDTH (500*ofGetWidth()/APP_WIDTH)
#define DATOS_HEIGHT (50*ofGetWidth()/APP_WIDTH)

#define PEOPLE_POST_TIMER 0.5
#define NUMBER_SCROLLER_QTY 15

class DatosScene : public ofxScene {
public:
    // set the scene name through the base class initializer
    DatosScene(ofxSceneManager& sm, ofxJSONElement& r, string& u, string& q) : sceneManager(sm), response(r), url(u), qr(q), ofxScene(DATOS_SCENE_NAME, false) {
        title.load("fonts/Futura/FuturaStd-Heavy.otf",36*ofGetWidth()/APP_WIDTH);
        title.setText("");
        title.setAnchorPercent(0.0,1.0);
        title.setPosition(ofPoint(ofGetWidth()*0.5-DATOS_WIDTH/2,ofGetHeight()*0.25));
        
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
        
        peopleNumberText.load("fonts/Calibri/calibrib.ttf",24*ofGetWidth()/APP_WIDTH);
        peopleSendText.load("fonts/Calibri/calibri.ttf",24*ofGetWidth()/APP_WIDTH);
        peopleTitleText.load("fonts/Calibri/calibrib.ttf",24*ofGetWidth()/APP_WIDTH);
        peopleStatusText.load("fonts/Calibri/calibrii.ttf",24*ofGetWidth()/APP_WIDTH);

        peopleSendButton.x=0;
        peopleSendButton.y=0;
        peopleSendButton.width=BUTTON_WIDTH/4;
        peopleSendButton.height=BUTTON_HEIGHT;
        peopleAddButton.x=0;
        peopleAddButton.y=0;
        peopleAddButton.width=BUTTON_WIDTH/6;
        peopleAddButton.height=BUTTON_HEIGHT;
        peopleNumberButton.x=0;
        peopleNumberButton.y=0;
        peopleNumberButton.width=BUTTON_WIDTH/3;
        peopleNumberButton.height=BUTTON_HEIGHT;
        peopleSubButton.x=0;
        peopleSubButton.y=0;
        peopleSubButton.width=BUTTON_WIDTH/6;
        peopleSubButton.height=BUTTON_HEIGHT;
        
        multiplePeople = true;
    }
    
    // scene setup
    void setup() {
        
        fields.clear();
        
        if(response["signup"].size()>0){
            title.setText(response["signup"]["d1"].asString());
            ofLogWarning(DATOS_SCENE_NAME) << response["signup"].size();
            for(int i=1;i<response["signup"].size()-3;i++){
                ofxAnimatableObject<ofTrueTypeFont> field;
                field.load("fonts/Futura/FuturaStd-Medium.otf",20*ofGetWidth()/APP_WIDTH);
                field.setText(response["signup"]["d"+ofToString(i+1)].asString());
                field.setAnchorPercent(0.0,1.0);
                field.setPosition(ofPoint(ofGetWidth()*0.5-DATOS_WIDTH/2,ofGetHeight()*0.25+DATOS_HEIGHT*(i+1)));
                field.setColor(ofColor(255,0));
                field.setSize(0.8);
                fields.push_back(field);
            }
            
            std::size_t found = response["signup"]["status"].asString().find("approv");
            if(found!=std::string::npos){
                status.setText("APROBADO");
            }
            else{
                status.setText("RECHAZADO");
            }
            last.setText("Última lectura " + response["signup"]["last"].asString());
            
            ID = response["signup"]["ID"].asString();
        }
        else{
            title.setText("No hay datos disponibles");
            
            ofxAnimatableObject<ofTrueTypeFont> field;
            field.load("fonts/Futura/FuturaStd-Medium.otf",20*ofGetWidth()/APP_WIDTH);
            field.setText("");
            field.setAnchorPercent(0.0,1.0);
            field.setPosition(ofPoint(ofGetWidth()*0.5-DATOS_WIDTH/2,ofGetHeight()*0.25+DATOS_HEIGHT));
            field.setColor(ofColor(255,0));
            field.setSize(0.8);
            fields.push_back(field);
            
            status.setText("");
            last.setText("Por favor scanee otro código QR");
            
            ID = "";
        }

        multiplePeople = (ofToInt(response["multiple"].asString())>0);
        MT = 1;
        
        ofPixels img;
        if(status.text=="APROBADO"){
            ofLoadImage(img,"check.png");
            statusIcon.loadData(img);
            statusIcon.setAnchorPercent(0.5,0.5);
        }
        else{
            ofLoadImage(img,"alert.png");
            statusIcon.loadData(img);
            statusIcon.setAnchorPercent(0.5,0.5);
        }
        
        status.setColor(ofColor(35,0));
        status.setSize(0.8);
        status.setPosition(fields.back().position.getCurrentPosition()+ofPoint(50,DATOS_HEIGHT*2));
        
        last.setColor(ofColor(35,0));
        last.setSize(0.8);
        last.setPosition(fields.back().position.getCurrentPosition()+ofPoint(0,DATOS_HEIGHT*3));
        
        title.setColor(ofColor(35,0));
        title.setSize(0.8);
        
        scanButton.setPosition(ofGetWidth()*0.5-scanButton.width/2,ofGetHeight()-scanButton.height*1.5);

        peopleSendButton.setPosition(ofGetWidth()*0.5+scanButton.width/2-peopleSendButton.width,ofGetHeight()-scanButton.height*2.75);
        peopleSubButton.setPosition(ofGetWidth()*0.5-scanButton.width/2,ofGetHeight()-scanButton.height*2.75);
        peopleNumberButton.setPosition(ofGetWidth()*0.5-scanButton.width/2+peopleSubButton.width,ofGetHeight()-scanButton.height*2.75);
        peopleAddButton.setPosition(ofGetWidth()*0.5-scanButton.width/2+peopleSubButton.width+peopleNumberButton.width,ofGetHeight()-scanButton.height*2.75);
        
        peoplePostRequest=false;
        peoplePostWaiting=false;
        peoplePostStatus="";
        peoplePostTimer=0.0f;
        
        peopleNumberScrollerArea=ofRectangle(peopleNumberButton.getPosition(),peopleNumberButton.getPosition()+ofPoint(peopleNumberButton.width,-1*NUMBER_SCROLLER_QTY*peopleNumberButton.height));
        peopleNumberScrollerOrigin.set(0,0);
        peopleShowNumberScroller=false;
        peopleNumberScrollerDragged=false;
        peopleNumberScroller=MT;
        peopleNumberScrollerRef=peopleNumberScroller;
        
        time=ofGetElapsedTimef();
    }
    
    // called when scene is entering
    void updateEnter() {
		
        // called on first enter update
        if(isEnteringFirst()) {
            title.color.animateTo(ofColor(35,255));
            title.size.animateTo(1.0);
            
            for(int i=0;i<fields.size();i++){
                fields[i].color.animateToAfterDelay(ofColor(35,255),i*0.5);
                fields[i].size.animateToAfterDelay(1.0,i*0.5);
            }
            
            status.color.animateTo(ofColor(35,255));
            status.size.animateTo(1.0);
            
            last.color.animateTo(ofColor(35,255));
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
        
        if(peoplePostTimer>0.0f){
            peoplePostTimer-=dt;
            if(peoplePostTimer<=0.0f)
                peoplePostTimer=0.0f;
        }
        
        if(peoplePostRequest){
            if(peoplePostWaiting){
                // create the url string
                string uri = url;
                
                uri=uri+"mode=multiple&multiple="+ofToString(MT)+"&qr="+qr+"&ID="+ID;
                
                if(uri.substr(0,4).compare("http")!=0)
                    uri="http://"+uri;
                
                ofLogNotice(POST_SCENE_NAME) << "URI: " << uri;
                ofHttpResponse res = ofLoadURL(uri);
                //posted=true;
                ofLogNotice(POST_SCENE_NAME) << "HTTP GET: " << res.status;
                if(res.status > 0) {
                    if(res.status == 200){
                        bool parsing = response.parse(res.data.getText());
                        if(parsing){
                            string token = APP_TOKEN;
                            if(token.compare(response["token"].asString())==0){
                                ofLogNotice(POST_SCENE_NAME) << "Respuesta: " << res.data.getText();
                                if(response["status"].asString()=="OK"){
                                    peoplePostStatus = "LISTO";
                                }
                                else{
                                    peoplePostStatus = "ERROR";
                                }
                                //sceneManager.gotoScene(DATOS_SCENE_NAME);
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
                    ofLogError(POST_SCENE_NAME) << "Problemas con la conexi√≥n: " << res.data.getText();
                    sceneManager.gotoScene(ERROR_SCENE_NAME);
                }
                peoplePostWaiting=false;
                peoplePostRequest=false;
                peoplePostTimer = PEOPLE_POST_TIMER;
            }
            else{
                peoplePostWaiting=true;
                peoplePostStatus = "...";
            }
        }
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
        ofSetColor(35);
        ofDrawLine(fields.back().position.getCurrentPosition()+ofPoint(0,DATOS_HEIGHT),fields.back().position.getCurrentPosition()+ofPoint(DATOS_WIDTH,DATOS_HEIGHT));
        
        statusIcon.draw(status.position.getCurrentPosition()-ofPoint(35,0));
        
        status.draw();
        last.draw();
        
        ofPushStyle();
        ofSetColor(35,200);
        string scanStr = "SCAN";
        scanText.drawString(scanStr,scanButton.x+scanButton.width/2-scanText.stringWidth(scanStr)/2,scanButton.y+scanButton.height/2+scanText.stringHeight(scanStr)/2);
        ofNoFill();
        ofDrawRectangle(scanButton);
        ofPopStyle();
        
        if(multiplePeople){
            ofSetColor(35,255);
            string titleStr = "ACOMPAÑANTES";
            peopleTitleText.drawString(titleStr,peopleSubButton.x,peopleSubButton.y-1.1*peopleTitleText.stringHeight(titleStr)/2);
            
            if(peopleShowNumberScroller){
                ofPushStyle();
                ofSetColor(35,200);
                ofFill();
                ofDrawRectangle(peopleNumberScrollerArea);
                
                ofPushMatrix();
                ofTranslate(0,peopleNumberButton.height*(float)(peopleNumberScroller-floor(peopleNumberScroller)));
                ofSetColor(255,255);
                for(int i=0; i<NUMBER_SCROLLER_QTY; i++){
                    ofTranslate(0,-peopleNumberButton.height);
                    string scrollStr = ofToString(floor(peopleNumberScroller)+i);
                    peopleNumberText.drawString(scrollStr,peopleNumberButton.x+peopleNumberButton.width/2-peopleNumberText.stringWidth(scrollStr)/2,peopleNumberButton.y+peopleNumberButton.height/2+peopleNumberText.stringHeight(scrollStr)/2);
                }
                ofPopMatrix();
                
                ofSetColor(255,255);
                ofFill();
                ofDrawRectangle(peopleNumberButton);
                ofPopStyle();
            }
            
            
            ofPushStyle();
            ofSetColor(35,200);
            ofFill();
            ofDrawRectangle(peopleAddButton);
            ofDrawRectangle(peopleSubButton);
            ofNoFill();
            ofDrawRectangle(peopleNumberButton);
            ofDrawRectangle(peopleSendButton);
            
            ofSetColor(255,255);
            peopleSendText.drawString("+",peopleAddButton.x+peopleAddButton.width/2-peopleSendText.stringWidth("+")/2,peopleAddButton.y+peopleAddButton.height/2+peopleSendText.stringHeight("+")/2);
            peopleSendText.drawString("-",peopleSubButton.x+peopleSubButton.width/2-peopleSendText.stringWidth("-")/2,peopleSubButton.y+peopleSubButton.height/2+peopleSendText.stringHeight("-")/2);
            
            ofSetColor(35,200);
            string peopleStr = "OK";
            peopleSendText.drawString(peopleStr,peopleSendButton.x+peopleSendButton.width/2-peopleSendText.stringWidth(peopleStr)/2,peopleSendButton.y+peopleSendButton.height/2+peopleSendText.stringHeight(peopleStr)/2);
            
            ofSetColor(35,255);
            peopleNumberText.drawString(ofToString(MT),peopleNumberButton.x+peopleNumberButton.width/2-peopleNumberText.stringWidth(ofToString(MT))/2,peopleNumberButton.y+peopleNumberButton.height/2+peopleNumberText.stringHeight(ofToString(MT))/2);
            
            peopleStatusText.drawString(peoplePostStatus,peopleSendButton.x+peopleSendButton.width-peopleStatusText.stringWidth(peoplePostStatus),peopleSendButton.y-1.1*peopleStatusText.stringHeight(peoplePostStatus)/2);
            
            if( peoplePostRequest || peoplePostTimer>0.0f){
                ofFill();
                ofSetColor(35,200);
                ofDrawRectangle(peopleSendButton);
                ofSetColor(255,255);
                peopleSendText.drawString(peopleStr,peopleSendButton.x+peopleSendButton.width/2-peopleSendText.stringWidth(peopleStr)/2,peopleSendButton.y+peopleSendButton.height/2+peopleSendText.stringHeight(peopleStr)/2);
            }
            ofPopStyle();
        }
    }
    
    // cleanup
    void exit() {
        ofLogVerbose(DATOS_SCENE_NAME) << "exit";
    }
    
    void mousePressed(int x, int y, int button){
        if(isExiting())
            return;
        
        if(multiplePeople && peopleNumberScrollerArea.inside(x,y)){
            peopleNumberScrollerOrigin.set(x,y);
            peopleNumberScrollerRef=peopleNumberScroller;
        }
        else{
            peopleNumberScrollerOrigin.set(0,0);
        }
    }

    void mouseDragged(int x, int y, int button){
        if(isExiting())
            return;
        
        if(multiplePeople && peopleNumberScrollerArea.inside(peopleNumberScrollerOrigin.x,peopleNumberScrollerOrigin.y)){
            peopleNumberScrollerDragged=true;
            peopleNumberScroller = peopleNumberScrollerRef + ((float)y - peopleNumberScrollerOrigin.y)/peopleNumberButton.height;
            if(peopleNumberScroller<1)
                peopleNumberScroller=1;
        }
    }

    void mouseReleased(int x, int y, int button){
        if(isExiting())
            return;
        
        if(multiplePeople && peopleNumberScrollerDragged){
            //GET OUT OF HEREEEEE with a threshold
            ofVec2f diff = peopleNumberScrollerOrigin-ofPoint(x,y);
            if(diff.length() > 10)
               return;
            peopleNumberScrollerDragged=false;
        }
        
        if(scanButton.inside(x,y)){
            sceneManager.gotoScene(QR_SCENE_NAME);
            return;
        }
        
        if(multiplePeople && peopleNumberButton.inside(x,y)){
            peopleShowNumberScroller = !peopleShowNumberScroller;
        }
        
        if(multiplePeople && peopleShowNumberScroller && peopleNumberScrollerArea.inside(x,y)){
            MT = floor(peopleNumberScroller + (peopleNumberButton.y - y)/peopleNumberButton.height);
            peopleShowNumberScroller = !peopleShowNumberScroller;
        }
        
        if(multiplePeople && peopleAddButton.inside(x,y)){
            MT++;
        }
        
        if(multiplePeople && peopleSubButton.inside(x,y)){
            if(MT>1)
                MT--;
        }
        
        if(multiplePeople && peopleSendButton.inside(x,y)){
            if(peoplePostTimer<=0.0f){
                peoplePostRequest=true;
            }
        }
    }
    
    float time;
    ofxJSONElement& response;
    string& url;
    string& qr;
    
    string ID;
    unsigned int MT;
    
    ofRectangle scanButton;
    ofTrueTypeFont scanText;
    
    bool multiplePeople;
    ofRectangle peopleNumberButton,peopleSendButton,peopleAddButton,peopleSubButton;
    ofTrueTypeFont peopleNumberText,peopleSendText,peopleTitleText,peopleStatusText;
    bool peoplePostRequest,peoplePostWaiting;
    string peoplePostStatus;
    float peoplePostTimer;
    
    ofRectangle peopleNumberScrollerArea;
    ofPoint peopleNumberScrollerOrigin;
    bool peopleShowNumberScroller,peopleNumberScrollerDragged;
    float peopleNumberScroller,peopleNumberScrollerRef;

    ofxAnimatableObject<ofTrueTypeFont> title,status,last;
    vector< ofxAnimatableObject<ofTrueTypeFont> > fields;
    
    ofTexture statusIcon;
    
    ofxSceneManager& sceneManager;
};
