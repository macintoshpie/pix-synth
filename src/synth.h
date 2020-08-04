//
//  synth.h
//  pixsynth
//
//  Created by Ted Summer on 7/16/20.
//

#ifndef synth_h
#define synth_h

#include <stdio.h>
#include "ofMain.h"
#include "channel.hpp"

class Synth {
private:
    Channel* red;
    Channel* green;
    Channel* blue;
    ofPixels pixels;
    ofTexture texture;
    int width;
    bool debug = false;

    std::string channelDebugString(std::string name, Channel* chn);
    Channel* getChn(ChannelId chn);
public:
    Synth();
    Synth(Channel* red_, Channel* green_, Channel* blue_, int width_);
    
    void draw();
    void update();
    void toggleDebugger();

    void setSpeed(ChannelId chn, float pct);
    void setLength(ChannelId chn, int length);
    void setShape(ChannelId chn, ShapeId shape);
    void setModSrc(ChannelId chn, ChannelId src);
    void setModAmt(ChannelId chn, float pct);
    void setWeight(ChannelId chn, float pct);
    void setModDst(ChannelId chn, ModDst dst);
};

#endif /* synth_h */
