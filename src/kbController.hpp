//
//  kbController.hpp
//  pixsynth
//
//  Created by Ted Summer on 7/28/20.
//

#ifndef kbController_hpp
#define kbController_hpp

#include <stdio.h>
#include "synth.h"

class KbController {
private:
    float speedStep;
    float redSpeed;
    float greenSpeed;
    float blueSpeed;

    int lengthStep;
    int redLength;
    int greenLength;
    int blueLength;
    
    ShapeId redShape;
    ShapeId greenShape;
    ShapeId blueShape;
    
    ChannelId redModSrc;
    ChannelId greenModSrc;
    ChannelId blueModSrc;
    
    float modAmtStep;
    float redModAmt;
    float greenModAmt;
    float blueModAmt;
    
    float weightStep;
    float redWeight;
    float greenWeight;
    float blueWeight;
    
    ModDst redModDst;
    ModDst greenModDst;
    ModDst blueModDst;

    Synth* synth;
public:
    KbController();
    KbController(Synth* synth_);
    void keyPressed(int key);
};

#endif /* kbController_hpp */
