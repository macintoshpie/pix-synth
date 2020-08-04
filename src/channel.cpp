//
//  channel.cpp
//  pixsynth
//
//  Created by Ted Summer on 7/26/20.
//

#include "channel.hpp"
#include "wave.h"
#include "utils.h"

#define MAX_DEPTH 5

Channel::Channel() {
    wave = new Wave();
    simple = true;
    weight = 1.0;
    modSrc = nullptr;
    modAmt = 0.0;
    modDst = modPhase;
}

Channel::Channel(Wave* wave_, bool simple_, float weight_, Channel* modSrc_, float modAmt_, ModDst modDst_) {
    wave = wave_;
    simple = simple_;
    weight = weight_;
    modSrc = modSrc_;
    modAmt = modAmt_;
    modDst = modDst_;
}

void Channel::step() {
    float stepMod = 0.0;
    if (modDst == modSpeed && modAmt != 0 && modSrc != nullptr) {
        float modVal = getMod(0, 0);
        stepMod = mapVal(modVal, 0, 1, -1, 1) * (modAmt * 100);
    }

    wave->step((int)stepMod);
}

float Channel::getMod(int tD, int stackDepth) {
    float modVal = 0.0;
    if (stackDepth <= MAX_DEPTH && modSrc != nullptr) {
        modVal = modSrc->getVal(tD, false, stackDepth + 1);
    }
    return modVal;
}

float Channel::getVal(int tD, bool weighted, int stackDepth) {
    if (simple) {
        return wave->getVal(tD);
    }

    const int i = tD;
    float waveVal;
    if (modDst == modPhase && modAmt != 0 && modSrc != nullptr) {
        float modVal = mapVal(getMod(i, stackDepth), 0, 1, -1, 1);
        waveVal = wave->getVal((int)(i + (modVal * (modAmt * 100))));
    } else if (modDst == weight && modAmt != 0 && modSrc != nullptr) {
        float modVal = getMod(i, stackDepth);
        waveVal = wave->getVal(i) * modVal * ((1 - modAmt) * 2);
    } else {
        waveVal = wave->getVal(i);
    }

    return weighted ? waveVal * weight : waveVal;
}

void Channel::setModSrc(Channel* channel) {
    modSrc = channel;
}

void Channel::setModAmt(float pct) {
    modAmt = clamp(pct, 0, 1);
}

void Channel::setWeight(float pct) {
    weight = clamp(pct, 0.0, 1.1);
}

void Channel::setSpeed(float pct) {
    wave->setSpeed(pct);
}

void Channel::setLength(int length) {
    wave->setLength(length);
}

void Channel::setShape(ShapeId shape) {
    wave->setShape(shape);
}

void Channel::setModDst(ModDst dst) {
    modDst = dst;
}

ChannelSummary* Channel::summary() {
    WaveSummary* waveSummary = wave->summary();
    ChannelSummary* chnSummary = new ChannelSummary(simple, weight, modAmt, modDst, waveSummary);
    return chnSummary;
}

ChannelSummary::ChannelSummary(bool simple_, float weight_, float modAmt_, ModDst modDst_, WaveSummary* waveSummary_) {
    simple = simple_;
    weight = weight_;
    modAmt = modAmt_;
    modDst = modDst_;
    waveSummary = waveSummary_;
}
