/***********************************************************************
 
 Copyright (c) 2009, Jordi Puig, www.wasawi.com
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 ***********************************************************************/

/*
 This addon uses a countdown to restart the app. 
 If you want a immediate restart hack it yourself.
 But I warn you that it might be quite risky :)
 */

#pragma once

#include "ofMain.h"

class ofxRestartOFApp{
public:

	ofxRestartOFApp();
	~ofxRestartOFApp();

	// call this to initiate restart countdown
	void initRestart(float delaySeconds=3, bool drawMessage = true);
	
private:

	void update(ofEventArgs &e);
	void draw(ofEventArgs &e);
	
	float delay;		// fixed time before restart
	float countdown;	// time left
	float elapsedTime;
	float startTime;	// when did the stopwatch start
	
	bool bDrawMessage;
	bool bRestarting;
	bool bWaitingToRestart;

	void restartApp(int type=0);
	
	//--------------------------------------------------------------
	string ofGetAppPath(){
		string appPath = ofFilePath::getAbsolutePath(ofFilePath::getCurrentExePath());
		return appPath;
	}
};















