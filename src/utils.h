//
//  utils.h
//  pixsynth
//
//  Created by Ted Summer on 7/26/20.
//

#ifndef utils_h
#define utils_h

#include "wave.h"
#include "channel.hpp"

float mapVal(float val, float origMin, float origMax, float newMin, float newMax);

float clamp(float val, float min, float max);

ShapeId nextShape(ShapeId shape);
ChannelId nextChannel(ChannelId chn);
ModDst nextModDst(ModDst dst);
#endif /* utils_h */
