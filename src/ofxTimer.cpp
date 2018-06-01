/***********************************************************************

 Copyright (c) 2009, Todd Vanderlin, www.vanderlin.cc

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

#include "ofxTimer.h"

ofxTimer::ofxTimer() {
}

ofxTimer::~ofxTimer() {
    ofRemoveListener(ofEvents().update, this, &ofxTimer::update);
    printf("*** Timer Destroyed ***\n");
}

// ---------------------------------------

void ofxTimer::setup(float _millSeconds, bool _bLoopTimer, bool _bStartTimer) {

    count = 0;
    bLoop = _bLoopTimer;
    bTimerRunning = false;
    bPauseTimer = !_bStartTimer;
    bStartTimer = true;
    bTimerFinished = false;
    delay = _millSeconds;
    timerStart = 0;

    // events
    ofAddListener(ofEvents().update, this, &ofxTimer::update);
}

// ---------------------------------------
void ofxTimer::reset(bool _bStartTimer) {
    count = 0;
    timerStart = 0;
    bTimerRunning = false;
    bStartTimer = _bStartTimer;
    bTimerFinished = false;

}

// ---------------------------------------
void ofxTimer::setLoop(bool _bLoop) {
    bLoop = _bLoop;
}

// ---------------------------------------
bool ofxTimer::isTimerRunning(){
    return bTimerRunning;
}

// ---------------------------------------
void ofxTimer::update(ofEventArgs &e) {

    if (!bPauseTimer) {

        if (bStartTimer) {
            bTimerRunning = true;
            bStartTimer = false;
            timerStart = ofGetElapsedTimeMillis();
            cout << "start time " << timerStart << endl;
        }

        float time = ofGetElapsedTimeMillis() - timerStart;

        if (time >= delay) {

            count++;

            bPauseTimer = true;
            bTimerRunning = false;
            static ofEventArgs timerEventArgs;
            ofNotifyEvent(timerReached, timerEventArgs, this);

            if (bLoop) {
                startTimer();
            } else {
                bTimerFinished = true;
            }
        }
    }
}

// for debugin
// ---------------------------------------
void ofxTimer::draw() {
    string info = "";
    info += "Delay " + ofToString(delay) + "\n";
    info += "Millis left " + ofToString(getTimeLeftInMillis() / 1000.0) + "\n";
    info += "Count " + ofToString(count) + "\n";
    info += "bPauseTimer " + ofToString(bPauseTimer) + "\n";
    info += "bTimerFinished " + ofToString(bTimerFinished) + "\n";

    ofDrawBitmapString(info, 20, 20);

    float x = getTimef();
    ofFill();
    ofDrawRectangle(0, 100, ofGetWidth() * x, 100);
}

// ---------------------------------------
float ofxTimer::getTimeLeftInMillis() {
    if (bPauseTimer) {
        return delay;
    }
    if (bTimerFinished) {
        return 0;
    }

    float t = ofGetElapsedTimeMillis() - timerStart;
    return delay - t;
}

// ---------------------------------------
float ofxTimer::getTimef() {
    float t = 1.0 - (getTimeLeftInMillis() / delay);
    return t;
}

// ---------------------------------------
void ofxTimer::setTimer(float _millSeconds) {
    delay = _millSeconds;
}

// ---------------------------------------
void ofxTimer::startTimer() {
    bPauseTimer = false;
    bStartTimer = true;
    bTimerFinished = false;
}

// ---------------------------------------
void ofxTimer::stopTimer() {
    bPauseTimer = true;
}

// ---------------------------------------
bool ofxTimer::isTimerFinished() {
    return bTimerFinished;
}
