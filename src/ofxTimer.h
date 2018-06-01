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

#pragma once
#include "ofMain.h"

class ofxTimer {

private:


    // timer
    bool        bLoop;
    bool        bPauseTimer;
    bool        bStartTimer;
    bool        bTimerRunning;
    bool        bTimerFinished;
    float       delay;
    float       timerStart;
    void update(ofEventArgs &e);

public:

    int			count;
    ofEvent <ofEventArgs> timerReached;

    ofxTimer();
    ~ofxTimer();

    // ---------------------------------------
    void reset(bool _bStartTimer=false);
    void setup(float millSeconds, bool _bLoopTimer=false, bool _bStartTimer=false);
    void draw();

    // ---------------------------------------
    bool  isTimerFinished();
    bool  isTimerRunning();
    void  setTimer(float _millSeconds);
    float getTimeLeftInMillis();
    float getTimef();
    void  startTimer();
    void  stopTimer();
    void  setLoop(bool _bLoop);

};
