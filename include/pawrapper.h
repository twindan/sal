/*
 pawrapper.h
 Spatial Audio Library (SAL)
 Copyright (c) 2016, Enzo De Sena
 All rights reserved.
 
 Authors: Enzo De Sena, enzodesena@me.com
 
 */

#ifndef SAL_pawrapper_h
#define SAL_pawrapper_h

#include "saltypes.h"
#include "mcltypes.h"
#include "portaudio.h"
#include "decoder.h"
#include <strings.h>
#include "salconstants.h"

namespace sal {
  
/** A wrapper for portaudio */
class SAL_API PaWrapper {
public:
  PaWrapper(Decoder* decoder, Time sampling_frequency, Int frames_per_buffer,
            Int out_dev_num, std::vector<Int> channel_ids);
  
  PaError StartStream();
  
  PaError WriteDecoderToStream();
  
  PaError WriteDecoderToStream(const Int num_samples);
  
  PaError WriteStream(const Int num_samples);
  
  PaError StopStream();
  
  Int max_num_channels() { return channel_ids_.size(); }
  
  static void PrintError(PaError err);
  
  static void PrintDevicesInfo();
  static Int NumOutputChannels(const Int out_dev_id);
  static std::vector<mcl::Int> SelectChannelIds(const Int num_loudspeakers,
                                                const Int out_dev_id);
  
  ~PaWrapper();
private:
  static PaError Init();
  static PaError Terminate();
  
  PaStream* stream_;
  Decoder* decoder_;
  std::vector<Int> channel_ids_;
  Int frames_per_buffer_;
};
  
  
} // namespace sal

#endif
