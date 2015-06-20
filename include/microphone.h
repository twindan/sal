/*
 microphone.h
 Spatial Audio Library (SAL)
 Copyright (c) 2011, Enzo De Sena
 All rights reserved.
 
 Authors: Enzo De Sena, enzodesena@me.com
 
 */


#ifndef SAL_MICROPHONE_H
#define SAL_MICROPHONE_H

#include "mcl.h"
#include "point.h"
#include "stream.h"
#include "source.h"
#include <assert.h>
#include <map>

namespace sal {

class Microphone {
public:
  /**
   `position` is the position of the microphone, where phi, theta and psi are
   euler angles. Convention is ZYX with angles phi, theta and psi, respectively.
   If the microphone is axisymmetric, this corresponds to using the spherical
   coordinate system with the convention that theta is the angle formed with
   the z-axis, and phi is the angle formed on the x-y plane with the x-axis.
   The x-axis corresponds to (r, theta, phi) = (r, pi/2, 0).
   A microphone generally has its acoustical axis on the z-axis
   i.e. (r, theta, phi) = (r, pi/2, 0).
   
   An example on the use of this function is as follow:
   the microphone is orientated in the direction of the x-axis => you need to
   input theta=pi/2 and phi=0. For the case of a mic in the direction of the
   y-axis these become phi=pi/2 theta=pi/2. (TODO: check this y-axis example)
   
   Methods with wave_id as a parameter imply that the user should
   explicitly tell the mic to `Tick`, i.e. to inform it that we are working
   on a new sample. Methods without wave_id (i.e. assuming there
   is a single plane wave incoming) do this automatically.
   */
  Microphone(Point position, Angle theta, Angle phi, Angle psi) :
  position_(position), theta_(theta), phi_(phi), psi_(psi) {}
  
  Point position() const;
  void set_position(const Point& position);
  
  Angle theta() const { return theta_; }
  void set_theta(Angle theta);
  
  Angle phi() const { return phi_; }
  void set_phi(Angle phi);
  
  Angle psi() const { return psi_; }
  void set_psi(Angle psi);
  
  /**
   We do not implement directly the case of a single plane wave because in
   most situations the microphone is recording many plane waves at the same
   time. This method should only be called in case of a single plane wave
   impinging on the microphone. For multiple plane waves, you need to
   explicitly specify the wave_id.
   */
  void RecordPlaneWave(const Sample& sample, const Point& point) {
    RecordPlaneWave(sample, point, 0);
    Tick();
  }
  
  /**
   This method should only be called in case of a single plane wave
   impinging on the microphone. For multiple plane waves, you need to
   explicitly specify the wave_id.
   */
  void RecordPlaneWave(const Signal& signal, const Point& point) {
    for (UInt i=0; i<signal.size(); ++i) {
      RecordPlaneWave(signal[i], point);
    }
  }
  
  /**
   This method should only be called in case of a single plane wave
   impinging on the microphone. For multiple plane waves, you need to
   explicitly specify the wave_id.
   */
  void RecordPlaneWave(Source source) {
    if (! source.stream()->IsEmpty()) {
      RecordPlaneWave(source.stream()->PullAll(), source.position());
    }
  }
  
  /**
   We need to
   keep track of the wave_id because some microphones (e.g. kemar) need
   to do some filtering on the signal longer than one sample.
   The function Tick tells the microphone to advance in time.
   The microphone objects need to keep track of each plane wave. Hence,
   the first time it sees a new wave_id, it will allocate a new filter
   for it.
   */
  void RecordPlaneWave(const Sample& sample, const Point& point,
                       const UInt& wave_id);
  
  void RecordPlaneWave(const Signal& signal, const Point& point,
                       const UInt& wave_id);
  
  /**
   This function tells the microphone to advance by one `tick` in time.
   This is meant to inform the microphone that we are working on a
   new sample in time. Only need to use this when calling wave_ids explicitly.
   */
  virtual void Tick() = 0;
  
  virtual bool IsCoincident() = 0;
  
  /*
   This is true when the microphone can handle frames.
   */
  virtual bool IsFrameEnabled() { return false; }
  
  /** This method translates `point` in the reference system of the mic. */
  Point GetRelativePoint(const Point& point) const;
  
  /** Resets the state of the microphone (if any). */
  virtual void Reset() {}
  
  static bool Test();
  
  virtual ~Microphone() {}
private:
  /**
   Cache variables to speed up. Since most of the times two consecutive calls
   to `Filter()` are for the same `Point` in space, we save the result of the
   geometrical calculations.
   */
  std::map<UInt,Point> last_point_;
  
  /**
   This point is the most up-to-date point in the reference system of the mic.
   */
  std::map<UInt,Point> last_relative_point_;
  
  void CalculateRelativePoint(const Point& point, const UInt& wave_id);
  
  /**
   This is implemented by the specific type of microphones. `Point` in this
   case is relative to the microphone reference system.
   This is the most important function of this object. This filters the
   sample `sample` as a function of the position from where the sound is
   incoming `point`.
   Info for developer: the directivity should preferably have a maximum in
   the direction of the z-axis (r, 0, 0). For anthropomorphic directivities,
   the facing direction is the z-axis. An arrow going from the jaw trough
   the skull and up should preferrably be in the direction of minus-x-axis.
   Other choices could be made, as long as the conventions are kept at
   higher levels.
   */
  virtual void RecordPlaneWaveRelative(const Sample& sample,
                                       const Point& point,
                                       const UInt& wave_id) = 0;
  
  virtual void RecordPlaneWaveRelative(const Signal& signal,
                                       const Point& point,
                                       const UInt& wave_id);
  
protected:
  Point position_;
  Angle theta_;
  Angle phi_;
  Angle psi_;
  
  
  
  friend class MicrophoneArray;
};

class StereoMicrophone : public Microphone {
public:
  StereoMicrophone(Point position, Angle theta, Angle phi, Angle psi) :
  Microphone(position, theta, phi, psi) {}
  
  StereoStream* stream() { return &stream_; }
protected:
  StereoStream stream_;
};
  
} // namespace sal

#endif
