//
//  utils.cpp
//  pixsynth
//
//  Created by Ted Summer on 7/26/20.
//

#include <stdio.h>

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
