//
//  wave.h
//  pixsynth
//
//  Created by Ted Summer on 7/13/20.
//

#ifndef wave_h
#define wave_h

enum ShapeId {
    shapeSaw,
    shapeTriangle,
    shapeSquare,
};

class WaveSummary {
public:
    int waveLength;
    int speed;
    int tZ;

    WaveSummary(int waveLength_, int speed_, int tZ_);
};

class Wave {
private:
    float tZ;
    int waveTableLength;
    int waveLength; // number of samples in a period, used for downsampling the waveTable
    int speed; // number of steps to take for each update (should range from 0 to len(waveLength) - 1)
    float *waveTable;
    float stepSize;
    
    void updateStepSize();
    float interp(float idx);
public:
    Wave();
    Wave(float* waveTable, int waveTableLength, int waveLength, int speed);

    void step(int stepMod);
    float getVal(int tD);
    void setSpeed(float pct);
    void setLength(int length);
    void setShape(ShapeId shape);
    WaveSummary* summary();
};




#endif /* wave_h */
