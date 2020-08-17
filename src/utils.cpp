//
//  utils.cpp
//  pixsynth
//
//  Created by Ted Summer on 7/26/20.
//

#include <stdio.h>
#include "channel.hpp"
#include "wave.h"

float mapVal(float val, float origMin, float origMax, float newMin, float newMax) {
    return (val - origMin) / (origMax - origMin) * (newMax - newMin) + newMin;
}

float clamp(float val, float min, float max) {
    if (val < min) {
        return min;
    }
    if (val > max) {
        return max;
    }
    return val;
}

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

