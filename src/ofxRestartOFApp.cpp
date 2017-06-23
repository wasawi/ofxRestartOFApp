#include "ofxRestartOFApp.h"

//--------------------------------------------------------------
ofxRestartOFApp:: ofxRestartOFApp(){
	bWaitingToRestart	= false;
	bRestarting			= false;
	elapsedTime,
	startTime,
	countdown = 0;

//	ofAddListener(this->RESTART, this, &ofxRestartOFApp::restartEvent);

}
ofxRestartOFApp:: ~ofxRestartOFApp(){
	ofRemoveListener(ofEvents().update, this, &ofxRestartOFApp::update);
	ofRemoveListener(ofEvents().draw, this, &ofxRestartOFApp::draw);
}

/*
//--------------------------------------------------------------
void ofxRestartOFApp::restartEvent(float &e){
	
	initRestart(e);

}
*/

//--------------------------------------------------------------
void ofxRestartOFApp::initRestart(float delaySeconds, bool drawMessage){
	
	startTime = ofGetElapsedTimef();
	bWaitingToRestart=true;

	delay				= delaySeconds;
	bDrawMessage		= drawMessage;
		
	ofLogVerbose("ofxRestartOFApp")<<"Secs to wait before restart "<< delay;
	
	//events
	ofAddListener(ofEvents().update, this, &ofxRestartOFApp::update);
	ofAddListener(ofEvents().draw, this, &ofxRestartOFApp::draw,OF_EVENT_ORDER_AFTER_APP);

}

//--------------------------------------------------------------
void ofxRestartOFApp::update(ofEventArgs &e){
	
	if (bWaitingToRestart){
		elapsedTime = ofGetElapsedTimef() - startTime;
		countdown = delay - elapsedTime;
		
		if (countdown < 0 && !bRestarting){
			ofLogVerbose("ofxRestartOFApp")<<"Restarting application:"<< ofGetAppPath();
			restartApp();
			bRestarting = true;
		}
	
	}
}

//--------------------------------------------------------------
void ofxRestartOFApp::draw(ofEventArgs &e){
	if (bWaitingToRestart && bDrawMessage){
		string msg = "waiting to restart "+ofToString(countdown)+" seconds";
		ofDrawBitmapStringHighlight(msg,
						   ofGetWidth()/2 - 100,
						   ofGetHeight()/2);
	}
}

//--------------------------------------------------------------
void ofxRestartOFApp::restartApp(int type){
	switch (type) {
		case 0:
#ifdef TARGET_OSX
			ofSystem("open " + ofGetAppPath());
#endif
#ifdef TARGET_WIN32
			_popen(("start " + ofGetAppPath()).c_str(), "w");
#endif
			ofLogVerbose("ofxRestartOFApp")<<"restartApp()"<<"new app launched";
			ofExit();
			break;
		default:
			// not working well :/
			//				string restart =ofGetAppPath()+" &";
			//				ofSystem(restart);
			//				ofLogNotice("ofRestart()")<<"new app launched";
			//				ofExit();
			break;
	}
	
	// this will never print, the app must be already closed
	ofLogError("ofRestart()")<<"restart did not work";
}
