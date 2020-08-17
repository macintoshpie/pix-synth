//
//  synth.cpp
//  pixsynth
//
//  Created by Ted Summer on 7/16/20.
//

#include "ofMain.h"

#include "synth.h"
#include "channel.hpp"
#include "generator.hpp"

static const float hello[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

Synth::Synth() {
    red = new Channel();
    green = new Channel();
    blue = new Channel();
    width = 60;
    pixels.allocate(width, width, OF_PIXELS_RGB);
    texture.allocate(pixels);
}

Synth::Synth(Channel* red_, Channel* green_, Channel* blue_, int width_) {
    red = red_;
    green = green_;
    blue = blue_;
    width = width_;
    pixels.allocate(width, width, OF_PIXELS_RGB);
    texture.allocate(pixels);
}

std::string Synth::channelDebugString(std::string name, Channel* chn) {
    ChannelSummary* chnSummary = chn->summary();
    std::string summaryStr(name + ":\n  weight: ");
    summaryStr.append(to_string(chnSummary->weight));
    summaryStr.append("\n  modAmt: ");
    summaryStr.append(to_string(chnSummary->modAmt));
    summaryStr.append("\n  modDst: ");
    summaryStr.append(to_string(chnSummary->modDst));
    summaryStr.append("\n  speed: ");
    summaryStr.append(to_string(chnSummary->waveSummary->speed));
    summaryStr.append("\n  length: ");
    summaryStr.append(to_string(chnSummary->waveSummary->waveLength));
    summaryStr.append("\n  tZ: ");
    summaryStr.append(to_string(chnSummary->waveSummary->tZ));
    return summaryStr;
}

void Synth::draw() {
    // https://forum.openframeworks.cc/t/drawing-pixels-in-checkerboard-pattern/30866/2
    int i = 0;
    for(auto line: pixels.getLines()){
        int j = 0;
        for(auto pixel: line.getPixels()){
            const int idx = i*width + j;
            pixel[0] = red->getVal(idx, true, 0) * 255;
            pixel[1] = green->getVal(idx, true, 0) * 255;
            pixel[2] = blue->getVal(idx, true, 0) * 255;
            j += 1;
        }
        i += 1;
    }
    texture.loadData(pixels);
    texture.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    
    texture.draw(0,0, ofGetHeight(), ofGetHeight());
    //texture.draw(0, 0);
    if (debug) {
        std::string summaryStr = channelDebugString("red", red);
        summaryStr.append(channelDebugString("\ngreen", green));
        summaryStr.append(channelDebugString("\nblue", blue));
        ofDrawBitmapString(summaryStr, 10, 10);
    }
}

void Synth::update() {
    red->step();
    green->step();
    blue->step();
}

void Synth::toggleDebugger() {
    debug = !debug;
}

Channel* Synth::getChn(ChannelId chn) {
    switch (chn) {
        case chnRed:
            return red;
        case chnGreen:
            return green;
        case chnBlue:
            return blue;
    }
    return nullptr;
}

void Synth::setSpeed(ChannelId chn, float pct) {
    Channel* selectedChn = getChn(chn);
    selectedChn->setSpeed(pct);
}

void Synth::setLength(ChannelId chn, int length) {
    Channel* selectedChn = getChn(chn);
    selectedChn->setLength(length);
}

void Synth::setShape(ChannelId chn, ShapeId shape) {
    Channel* selectedChn = getChn(chn);
    selectedChn->setShape(shape);
}

void Synth::setModSrc(ChannelId chn, ChannelId src) {
    Channel* selectedChn = getChn(chn);
    Channel* sourceChannel = getChn(src);
    selectedChn->setModSrc(sourceChannel);
}

void Synth::setModAmt(ChannelId chn, float pct) {
    Channel* selectedChn = getChn(chn);
    selectedChn->setModAmt(pct);
}

void Synth::setWeight(ChannelId chn, float pct) {
    Channel* selectedChn = getChn(chn);
    selectedChn->setWeight(pct);
}

void Synth::setModDst(ChannelId chn, ModDst dst) {
    Channel* selectedChn = getChn(chn);
    selectedChn->setModDst(dst);
}
