/*
 delayfilter.h
 Spatial Audio Library (SAL)
 Copyright (c) 2011, Enzo De Sena
 All rights reserved.
 
 Authors: Enzo De Sena, enzodesena@me.com
 
 */

#ifndef SAL_DELAYFILTER_H
#define SAL_DELAYFILTER_H

#define DEFAULT_MAX_LATENCY 3276800

#include "saltypes.h"
#include "digitalfilter.h"
#include "salconstants.h"

namespace sal {
  
class SAL_API DelayFilter : public mcl::DigitalFilter {
  
public:
  /**
   Constructs a delay filter object with intial latency given by latency. A maximum
   latency has to be given to allocate the maximum amount of memory of the circular
   memory.
   */
  DelayFilter(const sal::Int latency,
              sal::Int max_latency) noexcept;
  
  ~DelayFilter() noexcept { delete[] start_; }
  
  /**
   This writes the next sample into the filter. If this method is called 2 times
   before the Tick() operation, the former value will be overwritten.
   */
  inline void Write(const sal::Sample& sample) noexcept { *write_index_ = sample; }
  
  /** Resets the state of the filter */
  virtual void Reset() noexcept;
  
  /**
   Returns the current sample from the filter. Between two Tick() operation it will
   give always the same output.
   */
  inline sal::Sample Read() const noexcept { return *read_index_; }
  
  sal::Sample Read(const Int& delay_tap) const noexcept;
  
  sal::Sample FractionalRead(const Time fractional_delay_tap) const noexcept;
  
  /** This causes time to tick by one sample. */
  inline void Tick() noexcept {
    write_index_ = (write_index_ != end_) ? (write_index_+1) : start_;
    read_index_ = (read_index_ != end_) ? (read_index_+1) : start_;
  }
  
  
  /**
   Resets the latency of the filter. This can introduce artifacts if the
   latency is updated too fast.
   */
  void set_latency(const sal::Int) noexcept;
  
  /** Returns the current latency of the delay filter */
  sal::Int latency() const noexcept;
  
  /** Returns the maximum latency of the delay filter */
  sal::Int max_latency() const noexcept;
  
  DelayFilter& operator= (const DelayFilter&);
  DelayFilter (const DelayFilter&);
  
  virtual mcl::Real Filter(const mcl::Real input) noexcept;
  
  static bool Test();
protected:
  sal::Sample* start_;
  sal::Sample* end_;
  sal::Sample* write_index_;
  sal::Sample* read_index_;
  sal::Int latency_;
  sal::Int max_latency_;
};
  
} // namespace sal

#endif
