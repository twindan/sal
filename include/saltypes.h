/*
 saltypes.h
 Spatial Audio Library (SAL)
 Copyright (c) 2011, Enzo De Sena
 All rights reserved.
 
 Authors: Enzo De Sena, enzodesena@me.com
 
 This file contains several types, macros and supporting classes definitions.
 
 */

#ifndef SAL_TYPES_H
#define SAL_TYPES_H

#include <vector>

namespace sal {

typedef double Sample;
typedef double Time;
typedef double Speed;
typedef double Length;
typedef double Angle;
typedef unsigned long UInt;
typedef long Int;

  
typedef std::vector<Sample> Signal;
  
struct StereoSignal {
  Signal left;
  Signal right;
};
  
  
enum Ear {
  left_ear,
  right_ear
};

  
  
} // namespace sal




#endif