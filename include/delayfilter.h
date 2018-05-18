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
  
class DelayFilter : public mcl::DigitalFilter {
  
public:
  /**
   Constructs a delay filter object with intial latency given by latency. A maximum
   latency has to be given to allocate the maximum amount of memory of the circular
   memory.
   */
  DelayFilter(const Int latency, Int max_latency) noexcept;
  
  ~DelayFilter() noexcept { delete[] start_; }
  
  /**
   This writes the next sample into the filter. If this method is called 2 times
   before the Tick() operation, the former value will be overwritten.
   */
  inline void Write(const Sample sample) noexcept { *write_index_ = sample; }
  
  void Write(const Sample* samples, const Int num_samples) noexcept;
  
  /** Resets the state of the filter */
  virtual void Reset() noexcept;
  
  /**
   Returns the current sample from the filter. Between two Tick() operation it will
   give always the same output.
   */
  inline Sample Read() const noexcept { return *read_index_; }
  
  /** This allows to read at a different location from the read pointer. */
  Sample ReadAt(const Int delay_tap) const noexcept;
  
  /** Read the next `num_samples` samples.
   @param[in] num_samples the number of samples to be read.
   @param[out] output_data the array where to write these samples. */
  void Read(const Int num_samples, Sample* output_data) const noexcept;
  
  Sample FractionalReadAt(const Time fractional_delay_tap) const noexcept;
  
  /** This causes time to tick by one sample. */
  inline void Tick() noexcept {
    write_index_ = (write_index_ != end_) ? (write_index_+1) : start_;
    read_index_ = (read_index_ != end_) ? (read_index_+1) : start_;
  }
  
  /** This causes time to tick by more than one sample (use only if you
   understand what you are doing!). */
  void Tick(const Int num_samples) noexcept;
  
  /**
   Resets the latency of the filter. This can introduce artifacts if the
   latency is updated too fast.
   */
  void set_latency(const Int) noexcept;
  
  /** Returns the current latency of the delay filter */
  Int latency() const noexcept;
  
  /** Returns the maximum latency of the delay filter */
  Int max_latency() const noexcept;
  
  DelayFilter& operator= (const DelayFilter&);
  DelayFilter (const DelayFilter&);
  
  virtual mcl::Real Filter(const mcl::Real input) noexcept;
  
  static bool Test();
protected:
  Sample* start_;
  Sample* end_;
  Sample* write_index_;
  Sample* read_index_;
  sal::Int latency_;
  sal::Int max_latency_;
};
  
} // namespace sal

#endif
