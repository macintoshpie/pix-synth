//
//  channel.hpp
//  pixsynth
//
//  Created by Ted Summer on 7/26/20.
//

#ifndef channel_hpp
#define channel_hpp

#include <stdio.h>

#include "wave.h"

enum ModDst {
    modPhase,
    modWeight,
    modSpeed,
};

enum ChannelId {
    chnRed,
    chnGreen,
    chnBlue,
};

class ChannelSummary {
public:
    bool simple;
    float weight;
    float modAmt;
    ModDst modDst;
    WaveSummary* waveSummary;

    ChannelSummary(bool simple_, float weight_, float modAmt_, ModDst modDst_, WaveSummary* waveSummary_);
};

class Channel {
private:
    Wave* wave;
    bool simple;
    float weight;
    Channel* modSrc;
    float modAmt;
    ModDst modDst;

public:
    Channel();
    Channel(Wave* wave_, bool simple_, float weight_, Channel* modSrc_, float modAmt_, ModDst modDst_);

    void step();
    float getMod(int tD, int stackDepth);
    float getVal(int tD, bool weighted, int stackDepth);
    void setModAmt(float val);
    void setWeight(float val);
    void setModSrc(Channel* channel);
    void setSpeed(float pct);
    void setLength(int length);
    void setShape(ShapeId shape);
    void setModDst(ModDst dst);
    ChannelSummary* summary();
};

#endif /* channel_hpp */
