//
//  generator.cpp
//  pixsynth
//
//  Created by Ted Summer on 7/26/20.
//

#include "generator.hpp"

float* saw(int length) {
    // create saw shaped array
    float* tempArray = new float[length];
    float increment = 1.0 / length;
    for (int i = 0; i < length; i++) {
        tempArray[i] = i*increment;
    }
    return tempArray;
}

float* triangle(int length) {
    // create a triangle shaped array
    float* tempArray = new float[length];
    float half = length / 2.0;
    float increment = 1 / half;
    tempArray[0] = 0;
    for (int t = 1; t < length; t++) {
        tempArray[t] = tempArray[t-1] + increment;
        if (t >= half && increment > 0) {
            increment = increment * -1;
        }
    }

    return tempArray;
}

float* square(int length) {
    // create a square shaped array
    float* tempArray = new float[length];
    for (int i = 0; i<length; i++) {
        tempArray[i] = i < length / 2 ? 1 : 0;
    }
    return tempArray;
}

// float* Tables::triangleTable = triangle(TABLE_LENGTH);

float* triangleTable = triangle(TABLE_LENGTH);
float* sawTable = saw(TABLE_LENGTH);
float* squareTable = square(TABLE_LENGTH);
