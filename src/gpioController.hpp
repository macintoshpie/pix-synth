//
//  gpioController.hpp
//  pixsynth
//
//  Created by Ted Summer on 7/28/20.
//

#ifndef gpioController_hpp
#define gpioController_hpp

#include <stdio.h>
#include "synth.h"
#include "ofxGPIO.h"

class GPIOController {
private:
    MCP* mcp;
    GPIO gpio17;
    GPIO gpio27;
    GPIO gpio22;
    GPIO gpio23;

    int button1;
    int button2;
    int button3;
    int button4;
    int knob1;
    int knob2;
    int knob3;
    int knob4;
    bool knob1Locked;
    bool knob2Locked;
    bool knob3Locked;
    bool knob4Locked;

    ChannelId currentChn;
    map<ChannelId, map<string, int>>  chnKnobs;
    float currentSpeed;
    int currentLength;
    ShapeId currentShape;
    ChannelId currentModSrc;
    float currentModAmt;
    float currentWeight;
    ModDst currentModDst;
    Synth* synth;

    void updateState();
    void maybeUnlockKnob(bool* knobLocked, int knobVal, int currentChannelKnobVal);
public:
    GPIOController();
    GPIOController(Synth* synth_);
    void update();
};

#endif /* gpioController_hpp */
