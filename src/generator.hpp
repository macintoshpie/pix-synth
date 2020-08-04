//
//  generator.hpp
//  pixsynth
//
//  Created by Ted Summer on 7/26/20.
//

#ifndef generator_hpp
#define generator_hpp

#include <stdio.h>

#define TABLE_LENGTH 513

float* saw(int length);
float* triangle(int length);
float* square(int length);

extern float* triangleTable;
extern float* sawTable;
extern float* squareTable;

#endif /* generator_hpp */
