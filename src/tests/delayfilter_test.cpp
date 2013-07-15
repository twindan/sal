/*
 delayfilter_test.cpp
 Spatial Audio Library (SAL)
 Copyright (c) 2011, Enzo De Sena
 All rights reserved.
 
 Authors: Enzo De Sena, enzodesena@me.com
 
 */

#include "delayfilter.h"
#include "mcl.h"


namespace sal {

bool DelayFilter::Test() {
  using mcl::IsEqual;
  
  DelayFilter delay_filter_a = DelayFilter(1, 100);
  delay_filter_a.Write(0.0);
  assert(IsEqual(delay_filter_a.Read(),0.0));
  
  delay_filter_a.Tick();
  delay_filter_a.Write(1.0);
  assert(IsEqual(delay_filter_a.Read(),0.0));
  
  delay_filter_a.Tick();
  delay_filter_a.Write(2.0);
  assert(IsEqual(delay_filter_a.Read(),1.0));
  
  delay_filter_a.Tick();
  delay_filter_a.Write(0.0);
  assert(IsEqual(delay_filter_a.Read(),2.0));
  
  delay_filter_a.Tick();
  delay_filter_a.Write(0.0);
  assert(IsEqual(delay_filter_a.Read(),0.0));
  
  DelayFilter delay_filter_b = DelayFilter(3, 100);
  delay_filter_b.Write(1.0);
  assert(IsEqual(delay_filter_b.Read(),0.0));
  
  delay_filter_b.Tick();
  delay_filter_b.Write(2.0);
  assert(IsEqual(delay_filter_b.Read(),0.0));
  
  delay_filter_b.Tick();
  delay_filter_b.Write(3.0);
  assert(IsEqual(delay_filter_b.Read(),0.0));
  
  delay_filter_b.Tick();
  delay_filter_b.Write(-1.0);
  assert(IsEqual(delay_filter_b.Read(),1.0));
  
  delay_filter_b.Tick();
  delay_filter_b.Write(-1.0);
  assert(IsEqual(delay_filter_b.Read(),2.0));
  
  delay_filter_b.Tick();
  delay_filter_b.Write(-1.0);
  assert(IsEqual(delay_filter_b.Read(),3.0));
  
  delay_filter_b.Tick();
  delay_filter_b.Write(-1.0);
  assert(IsEqual(delay_filter_b.Read(),-1.0));
  
  delay_filter_b.Tick();
  delay_filter_b.Write(-1.0);
  assert(IsEqual(delay_filter_b.Read(),-1.0));
  
  
  /////
  
  DelayFilter delay_filter_c = DelayFilter(2,3);
  delay_filter_c.Write(1.0);
  assert(IsEqual(delay_filter_c.Read(),0.0));
  
  delay_filter_c.Tick();
  delay_filter_c.Write(0.0);
  assert(IsEqual(delay_filter_c.Read(),0.0));
  
  delay_filter_c.Tick();
  delay_filter_c.Write(0.0);
  assert(IsEqual(delay_filter_c.Read(),1.0));
  
  delay_filter_c.set_latency(3);
  
  delay_filter_c.Tick();
  delay_filter_c.Write(2.0);
  // It is one because by setting latency to 3, the read pointer will go back 
  // and read again the last sample.
  assert(IsEqual(delay_filter_c.Read(),1.0));
  
  delay_filter_c.Tick();
  delay_filter_c.Write(0.0);
  assert(IsEqual(delay_filter_c.Read(),0.0));
  
  delay_filter_c.Tick();
  delay_filter_c.Write(0.0);
  assert(IsEqual(delay_filter_c.Read(),0.0));

  delay_filter_c.Tick();
  delay_filter_c.Write(0.0);
  assert(IsEqual(delay_filter_c.Read(),2.0));
  
  delay_filter_c.set_latency(2);
  
  delay_filter_c.Tick();
  delay_filter_c.Write(3.0);
  assert(IsEqual(delay_filter_c.Read(),0.0));
  
  delay_filter_c.Tick();
  delay_filter_c.Write(0.0);
  assert(IsEqual(delay_filter_c.Read(),0.0));
  
  delay_filter_c.Tick();
  delay_filter_c.Write(0.0);
  assert(IsEqual(delay_filter_c.Read(),3.0));
  
  
  
  DelayFilter delay_filter_d = DelayFilter(1,5);
  
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),0.0));
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  delay_filter_d.set_latency(2);
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  delay_filter_d.set_latency(4);
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  delay_filter_d.set_latency(3);
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  delay_filter_d.Tick();
  delay_filter_d.Write(1.0);
  assert(IsEqual(delay_filter_d.Read(),1.0));
  
  return true;
}

} // namespace sal
