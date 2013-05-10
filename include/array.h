/*
 array.h
 Spatial Audio Toolbox (SAT)
 Copyright (c) 2011, Enzo De Sena
 All rights reserved.
 
 Authors: Enzo De Sena, enzodesena@me.com
 
 This file contains several types, macros and supporting classes definitions.
 
 Last committed:     $Revision: 111 $
 Last changed date:  $Date: 2012-07-18 01:36:32 +0100 (Wed, 18 Jul 2012) $
 */

#ifndef SAT_ARRAY_H
#define SAT_ARRAY_H

namespace sat {

template<typename T, std::size_t N> 
class Array {
public:
  T elems[N];
  
  T& operator[] (std::size_t i) { 
    assert(i < N); 
    return elems[i];
  }
};

} // namespace sat
  
#endif
