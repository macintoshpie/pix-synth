//
//  wave.cpp
//  pixsynth
//
//  Created by Ted Summer on 7/13/20.
//

#include <stdio.h>
#include <math.h>

#include "ofMain.h"

#include "wave.h"
#include "utils.h"
#include "generator.hpp"

static float hello[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

WaveSummary::WaveSummary(int waveLength_, int speed_, int tZ_) {
    waveLength = waveLength_;
    speed = speed_;
    tZ = tZ_;
}

Wave::Wave() {
    waveTable = hello;
    waveTableLength = 10;
    waveLength = 10;
    speed = 1;
    tZ = 0;
}

Wave::Wave(float* waveTable_, int waveTableLength_, int waveLength_, int speed_) {
    waveTable = waveTable_;
    waveTableLength = waveTableLength_;
    waveLength = waveLength_;
    speed = speed_;
    tZ = 0.0;
    stepSize = 1.0;
    updateStepSize();
}

void Wave::updateStepSize() {
    stepSize = (float)waveTableLength / (float)waveLength;
}

void Wave::step(int stepMod) {
    // const int stepSize = waveTableLength / waveLength;
    tZ = fmod((tZ + (speed * stepSize) + stepMod), waveTableLength);
}

float Wave::interp(float idx) {
    const int integral = floor(idx);
    const float fractional = idx - integral;
    const float valLower = waveTable[integral];
    const float valUpper = waveTable[integral + 1];
    return valLower + ((valUpper - valLower) * fractional);
}

float Wave::getVal(int tD) {
    const float getIdx = fmod((tZ + ((float)tD * stepSize)), waveTableLength);
    return interp(getIdx);
}

void Wave::setSpeed(float pct) {
    speed = (int)mapVal(pct, 0.0, 1.0, 0, waveLength);
    // when speed == waveLength, there is drift in tZ, this fixes that
    // drift occurs b/c in step() are doing x % waveTableLength, which is often non-zero
    speed = speed % waveLength;
}

void Wave::setLength(int length) {
    waveLength = (int)clamp(length, 1, waveTableLength);
    updateStepSize();
}

void Wave::setShape(ShapeId shape) {
    switch (shape) {
        case shapeSaw:
            waveTable = sawTable;
            break;
        case shapeTriangle:
            waveTable = triangleTable;
            break;
        case shapeSquare:
            waveTable = squareTable;
            break;
    }
}

WaveSummary* Wave::summary() {
    return new WaveSummary(waveLength, speed, tZ);
}
