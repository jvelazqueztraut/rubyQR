#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(30);
    ofLogWarning() << "Width: "<< ofGetWidth() << ", Height: "<< ofGetHeight();
	ofBackground(255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetOrientation(OF_ORIENTATION_DEFAULT);

	ofPixels img;
    ofLoadImage(img,"passter.png");
    inicio.loadData(img);
    inicio.setAnchorPercent(0.5,0.5);
    inicio.color.setDuration(0.75f);
    inicio.setPosition(ofPoint(ofGetWidth()-inicio.getWidth()*0.5,inicio.getHeight()*0.5));
    inicio.setColor(ofColor(255,255));
    
    std::string file = "login.json";
    if(ofFile::doesFileExist(ofxiOSGetDocumentsDirectory()+file)){
        // Now parse the JSON
        ofxJSONElement login;
        bool parsing = login.open(ofxiOSGetDocumentsDirectory()+file);
        if(parsing){
            node = login["node"].asString();
            device = login["device"].asString();
            url = login["url"].asString();
        }
    }

	// load scenes
    sceneManager.add(new InicioScene(sceneManager,node,device,url));
    sceneManager.add(new QRScene(sceneManager,qr));
    sceneManager.add(new PostScene(sceneManager,node,device,url,qr,response));
    sceneManager.add(new DatosScene(sceneManager,response,url,qr));
    sceneManager.add(new ErrorScene(sceneManager));

    // overlap scenes when transitioning
    // sceneManager.setOverlap(true);
    
    // do not wait to change scenes
    sceneManager.setMinChangeTime(0);
    
    //sceneManager.setup(true);	// true = setup all the scenes now (not on the fly)
	ofSetLogLevel("ofxSceneManager", OF_LOG_VERBOSE); // lets see whats going on inside
	
	// start with a specific scene
	// set now to true in order to ignore the scene fade and change now
	sceneManager.gotoScene(INICIO_SCENE_NAME, false);
	lastScene = sceneManager.getCurrentSceneIndex();
	
	// you can also turn off the auto sceneManager update and draw calls with:
	setSceneManagerUpdate(false);
	setSceneManagerDraw(false);
	//
	// the input callbacks in your scenes will be called if they are implemented
	//
	setSceneManager(&sceneManager);

	time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
	float t = ofGetElapsedTimef();
	float dt = t - time;
	time = t;

	sceneManager.update();
    
    inicio.update(dt);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);
    
    //ofPushMatrix();
    //ofScale(ofGetWidth()/APP_WIDTH,ofGetHeight()/APP_HEIGHT);
    
	sceneManager.draw();
    
    //ofPopMatrix();
    
    inicio.draw();
    
#ifdef _DEBUG
	// draw current scene info using the ofxBitmapString stream interface
	// to ofDrawBitmapString
	ofSetColor(255);
	ofxBitmapString(12, ofGetHeight()-8)
		<< "Current Scene: " << sceneManager.getCurrentSceneIndex()
		<< " " << sceneManager.getCurrentSceneName() << endl;
#endif
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(inicio.inside(ofPoint(x,y))){
        sceneManager.gotoScene(INICIO_SCENE_NAME, false);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
#ifdef TARGET_ANDROID
//--------------------------------------------------------------
void ofApp::touchDown(int x, int y, int id){
	if(inicio.inside(ofPoint(x,y))){
        sceneManager.gotoScene(INICIO_SCENE_NAME, false);
    }
}

//--------------------------------------------------------------
void ofApp::touchMoved(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchUp(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(int x, int y, int id){

}

//--------------------------------------------------------------
void ofApp::swipe(ofxAndroidSwipeDir swipeDir, int id){

}

//--------------------------------------------------------------
void ofApp::pause(){

}

//--------------------------------------------------------------
void ofApp::stop(){

}

//--------------------------------------------------------------
void ofApp::resume(){

}

//--------------------------------------------------------------
void ofApp::reloadTextures(){
    ofPixels img;
    ofLoadImage(img,"ruby.png");
    inicio.loadData(img);
    inicio.setAnchorPercent(0.5,0.5);
}

//--------------------------------------------------------------
bool ofApp::backPressed(){
	return false;
}

//--------------------------------------------------------------
void ofApp::okPressed(){

}

//--------------------------------------------------------------
void ofApp::cancelPressed(){

}
#endif
