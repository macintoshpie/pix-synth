//
//  kbController.cpp
//  pixsynth
//
//  Created by Ted Summer on 7/28/20.
//

#include <iostream>
#include "gpioController.hpp"
#include "wave.h"
#include "channel.hpp"
#include "utils.h"
#include "ofxGPIO.h"

void setupGPIOButton(GPIO* gpio, string pin) {
    gpio->setup(pin);
    gpio->export_gpio();
    usleep(500000);
    gpio->setdir_gpio("in");
}

GPIOController::GPIOController() {
    synth = nullptr;
    currentChn = chnRed;
    currentSpeed = 0.0;
    currentLength = 1;
    currentShape = shapeSaw;
    currentModSrc = chnRed;
    currentModAmt = 0.0;
    currentWeight = 1.0;
    currentModDst = modPhase;
}

GPIOController::GPIOController(Synth* synth_) {
    synth = synth_;
    currentChn = chnRed;
    currentSpeed = 0.0;
    currentLength = 1;
    currentShape = shapeSaw;
    currentModSrc = chnRed;
    currentModAmt = 0.0;
    currentWeight = 1.0;
    currentModDst = modPhase;

    button1 = 0;
    button2 = 0;
    button3 = 0;
    button4 = 0;

    knob1Locked = true;
    knob2Locked = true;
    knob3Locked = true;
    knob4Locked = true;

    mcp = new MCP();
    mcp->setup("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);

    setupGPIOButton(&gpio17, "17");
    setupGPIOButton(&gpio27, "27");
    setupGPIOButton(&gpio22, "22");
    setupGPIOButton(&gpio23, "23");

    chnKnobs[chnRed]["1"] = 10;
    chnKnobs[chnRed]["2"] = 10;
    chnKnobs[chnRed]["3"] = 10;
    chnKnobs[chnRed]["4"] = 10;

    chnKnobs[chnGreen]["1"] = 10;
    chnKnobs[chnGreen]["2"] = 10;
    chnKnobs[chnGreen]["3"] = 10;
    chnKnobs[chnGreen]["4"] = 10;

    chnKnobs[chnBlue]["1"] = 10;
    chnKnobs[chnBlue]["2"] = 10;
    chnKnobs[chnBlue]["3"] = 10;
    chnKnobs[chnBlue]["4"] = 10;
}

void updateButton(GPIO* gpio, int* button) {
    int currentState;
    gpio->getval_gpio(currentState);

    if (currentState == 0) {
        // button has been released
        *button = 0;
    } else if (currentState == 1 && *button == 0) {
        // button was previously released, and is now pressed
        *button = 1;
    } else if (currentState == 1 && *button == 1) {
        // button was previously pressed, and is now pressed, ignore it
        *button = -1;
    }
}

void GPIOController::updateState() {
    updateButton(&gpio17, &button1);
    updateButton(&gpio27, &button2);
    updateButton(&gpio22, &button3);
    updateButton(&gpio23, &button4);

    knob1 = mcp->getValueChannel(0);
    knob2 = mcp->getValueChannel(1);
    knob3 = mcp->getValueChannel(2);
    knob4 = mcp->getValueChannel(3);
}

void GPIOController::maybeUnlockKnob(bool* knobLocked, int knobVal, int knobValStored) {
    if (!*knobLocked) {
        return;
    }

    if ((knobValStored - 5 <= knobVal) && (knobVal <= knobValStored + 5)) {
        *knobLocked = false;
    }
}

void GPIOController::update() {
    updateState();

    if (button1 == 1) {
        currentChn = nextChannel(currentChn);
        knob1Locked = true;
        knob2Locked = true;
        knob3Locked = true;
        knob4Locked = true;
    }
    
    if (button2 == 1) {
        currentShape = nextShape(currentShape);
        synth->setShape(currentChn, currentShape);
    }

    if (button3 == 1) {
        currentModSrc = nextChannel(currentModSrc);
        synth->setModSrc(currentChn, currentModSrc);
    }

    if (button4 == 1) {
        currentModDst = nextModDst(currentModDst);
        synth->setModDst(currentChn, currentModDst);
    }

    maybeUnlockKnob(&knob1Locked, knob1, chnKnobs[currentChn]["1"]);
    maybeUnlockKnob(&knob2Locked, knob2, chnKnobs[currentChn]["2"]);
    maybeUnlockKnob(&knob3Locked, knob3, chnKnobs[currentChn]["3"]);
    maybeUnlockKnob(&knob4Locked, knob4, chnKnobs[currentChn]["4"]);

    if (!knob1Locked) {
        chnKnobs[currentChn]["1"] = knob1;
        synth->setSpeed(currentChn, mapVal(knob1, 0, 1027, 0, 1));
    }

    if (!knob2Locked) {
        chnKnobs[currentChn]["2"] = knob2;
        synth->setLength(currentChn, mapVal(knob2, 0, 1027, 0, 513));
    }

    if (!knob3Locked) {
        chnKnobs[currentChn]["3"] = knob3;
        synth->setWeight(currentChn, mapVal(knob3, 0, 1027, 0, 1));
    }

    if (!knob4Locked) {
        chnKnobs[currentChn]["4"] = knob4;
        synth->setModAmt(currentChn, mapVal(knob4, 0, 1027, 0, 1));
    }
}

