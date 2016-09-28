#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(50,50,50);
	ofSetLogLevel(OF_LOG_NOTICE);
	//ofSetOrientation(OF_ORIENTATION_90_LEFT);

	ofPixels img;
    ofLoadImage(img,"inicio.png");
    inicio.loadData(img);
    inicio.setAnchorPercent(0.5,0.5);
    inicio.color.setDuration(0.75f);
    inicio.setPosition(ofPoint(ofGetWidth()*0.95,ofGetHeight()*0.1));
    inicio.setColor(ofColor(255,255));

	camera.setup(1920,1080);

	// load scenes
    sceneManager.add(new InicioScene(sceneManager,inicio));

    // overlap scenes when transitioning
    // sceneManager.setOverlap(true);
    
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
    
    // create the google url string
    string url = "http://www.opcion2.com.ar/ruby/app/qr/?qr=456";
    ofHttpResponse res = ofLoadURL(url);
    
    if(res.status > 0) {
        // copy over the response date fromt the url load
        cout << res.data.getText() << endl;
    }

	time = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update(){
	float t = ofGetElapsedTimef();
	float dt = t - time;
	time = t;

	camera.update();
	if(camera.isFrameNew()){
		ofxZxing::Result result = ofxZxing::decode(camera.getPixels(), true);
	}

	sceneManager.update();
    
    inicio.update(dt);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255);

	sceneManager.draw();
	
	camera.draw(0, 0);

	if(result.getFound()) {
		result.draw();		
	}

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