//
//  kbController.cpp
//  pixsynth
//
//  Created by Ted Summer on 7/28/20.
//

#include "kbController.hpp"
#include "wave.h"
#include "channel.hpp"
#include "utils.h"

ShapeId nextShape(ShapeId shape) {
    switch (shape) {
        case shapeSquare:
            return shapeSaw;
        case shapeSaw:
            return shapeTriangle;
        case shapeTriangle:
            return shapeSquare;
    }
    return shapeSquare;
}

ChannelId nextChannel(ChannelId chn) {
    switch (chn) {
        case chnRed:
            return chnGreen;
        case chnGreen:
            return chnBlue;
        case chnBlue:
            return chnRed;
    }
    return chnRed;
}

ModDst nextModDst(ModDst dst) {
    switch (dst) {
        case modPhase:
            return modSpeed;
        case modSpeed:
            return modWeight;
        case modWeight:
            return modPhase;
    }
    return modPhase;
}

KbController::KbController() {
    synth = nullptr;
    redSpeed = 0.0;
    greenSpeed = 0.0;
    blueSpeed = 0.0;
    speedStep = 0.05;
}

KbController::KbController(Synth* synth_) {
    synth = synth_;
    redSpeed = 0.0;
    greenSpeed = 0.0;
    blueSpeed = 0.0;
    speedStep = 0.05;
    
    redLength = 1;
    greenLength = 1;
    blueLength = 1;
    lengthStep = 1;
    
    redShape = shapeSaw;
    greenShape = shapeSaw;
    blueShape = shapeSaw;
    
    redModSrc = chnRed;
    greenModSrc = chnRed;
    blueModSrc = chnRed;
    
    redModAmt = 0.0;
    greenModAmt = 0.0;
    blueModAmt = 0.0;
    modAmtStep = 0.05;
    
    redWeight = 0.0;
    greenWeight = 0.0;
    blueWeight = 0.0;
    weightStep = 0.05;
    
    redModDst = modPhase;
    greenModDst = modPhase;
    blueModDst = modPhase;
}

void KbController::keyPressed(int key) {
    switch (key) {
        // SPEED
        case 'q':
            redSpeed = clamp(redSpeed - speedStep, 0.0, 1.0);
            synth->setSpeed(chnRed, redSpeed);
            break;
        case 'w':
            redSpeed = clamp(redSpeed + speedStep, 0.0, 1.0);
            synth->setSpeed(chnRed, redSpeed);
            break;
        case 'a':
            greenSpeed = clamp(greenSpeed - speedStep, 0.0, 1.0);
            synth->setSpeed(chnGreen, greenSpeed);
            break;
        case 's':
            greenSpeed = clamp(greenSpeed + speedStep, 0.0, 1.0);
            synth->setSpeed(chnGreen, greenSpeed);
            break;
        case 'z':
            blueSpeed = clamp(blueSpeed - speedStep, 0.0, 1.0);
            synth->setSpeed(chnBlue, blueSpeed);
            break;
        case 'x':
            blueSpeed = clamp(blueSpeed + speedStep, 0.0, 1.0);
            synth->setSpeed(chnBlue, blueSpeed);
            break;
        // LENGTH
        case 'e':
            redLength = (int)clamp(redLength - lengthStep, 1.0, 513.0);
            synth->setLength(chnRed, redLength);
            break;
        case 'r':
            redLength = (int)clamp(redLength + lengthStep, 1.0, 513.0);
            synth->setLength(chnRed, redLength);
            break;
        case 'd':
            greenLength = (int)clamp(greenLength - lengthStep, 1.0, 513.0);
            synth->setLength(chnGreen, greenLength);
            break;
        case 'f':
            greenLength = (int)clamp(greenLength + lengthStep, 1.0, 513.0);
            synth->setLength(chnGreen, greenLength);
            break;
        case 'c':
            blueLength = (int)clamp(blueLength - lengthStep, 1.0, 513.0);
            synth->setLength(chnBlue, blueLength);
            break;
        case 'v':
            blueLength = (int)clamp(blueLength + lengthStep, 1.0, 513.0);
            synth->setLength(chnBlue, blueLength);
            break;
        // SHAPE
        case 't':
            redShape = nextShape(redShape);
            synth->setShape(chnRed, redShape);
            break;
        case 'g':
            greenShape = nextShape(greenShape);
            synth->setShape(chnGreen, greenShape);
            break;
        case 'b':
            blueShape = nextShape(blueShape);
            synth->setShape(chnBlue, blueShape);
            break;
        // MOD SOURCE
        case 'y':
            redModSrc = nextChannel(redModSrc);
            synth->setModSrc(chnRed, redModSrc);
            break;
        case 'h':
            greenModSrc = nextChannel(greenModSrc);
            synth->setModSrc(chnGreen, greenModSrc);
            break;
        case 'n':
            blueModSrc = nextChannel(blueModSrc);
            synth->setModSrc(chnBlue, blueModSrc);
            break;
        // MOD AMOUNT
        case 'u':
            redModAmt = clamp(redModAmt - modAmtStep, 0.0, 1.0);
            synth->setModAmt(chnRed, redModAmt);
            break;
        case 'i':
            redModAmt = clamp(redModAmt + modAmtStep, 0.0, 1.0);
            synth->setModAmt(chnRed, redModAmt);
            break;
        case 'j':
            greenModAmt = clamp(greenModAmt - modAmtStep, 0.0, 1.0);
            synth->setModAmt(chnGreen, greenModAmt);
            break;
        case 'k':
            greenModAmt = clamp(greenModAmt + modAmtStep, 0.0, 1.0);
            synth->setModAmt(chnGreen, greenModAmt);
            break;
        case 'm':
            blueModAmt = clamp(blueModAmt - modAmtStep, 0.0, 1.0);
            synth->setModAmt(chnBlue, blueModAmt);
            break;
        case ',':
            blueModAmt = clamp(blueModAmt + modAmtStep, 0.0, 1.0);
            synth->setModAmt(chnBlue, blueModAmt);
            break;
        // WEIGHT
        case 'o':
            redWeight = clamp(redWeight - weightStep, 0.0, 1.0);
            synth->setWeight(chnRed, redWeight);
            break;
        case 'p':
            redWeight = clamp(redWeight + weightStep, 0.0, 1.0);
            synth->setWeight(chnRed, redWeight);
            break;
        case 'l':
            greenWeight = clamp(greenWeight - weightStep, 0.0, 1.0);
            synth->setWeight(chnGreen, greenWeight);
            break;
        case ';':
            greenWeight = clamp(greenWeight + weightStep, 0.0, 1.0);
            synth->setWeight(chnGreen, greenWeight);
            break;
        case '.':
            blueWeight = clamp(blueWeight - weightStep, 0.0, 1.0);
            synth->setWeight(chnBlue, blueWeight);
            break;
        case '/':
            blueWeight = clamp(blueWeight + weightStep, 0.0, 1.0);
            synth->setWeight(chnBlue, blueWeight);
            break;
        // MOD DESTINATION
        case '[':
            redModDst = nextModDst(redModDst);
            synth->setModDst(chnRed, redModDst);
            break;
        case ']':
            greenModDst = nextModDst(greenModDst);
            synth->setModDst(chnGreen, greenModDst);
            break;
        case '\\':
            blueModDst = nextModDst(blueModDst);
            synth->setModDst(chnBlue, blueModDst);
            break;
    }
}
