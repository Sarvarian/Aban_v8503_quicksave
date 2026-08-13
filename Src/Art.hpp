#pragma once

#ifndef AB_ART_HPP
#define AB_ART_HPP

#include "Main.hpp"

/** Aban Runtime */
class Art {
public:

  class Step {
  protected:
    friend class ArtCore;
    u8 just_continue : 1;
    u8 calculate_delta_time : 1;
    u8 window_check : 1;
    u8 window_undef : 1;
    u8 window_def : 1;
    u8 _pad03_ : 1;
    u8 _pad02_ : 1;
    u8 _pad01_ : 1;
    u8 _pad00_[mmBufferSize(0) - 1];
    void clearAllFields();
    Step();
  public:
  };
  staticAssert(sizeof(Step) == sizeof(Buffer0), Step_FIT_INTO_ONE_Buffer0)

  /** \return Check return for null.
   * Exit as failure in case of null. */
  static Art* def();

  /** \return Always returns null. */
  Art* undef();

  /** Returns current step, and swap steps. */
  Step& stepForward();

  /** Returns future/next steup. */
  Step& stepFuture();

protected:
  Art() { /* Empty */ };

  class ArtCore& castCore();

};
staticAssert(sizeof(Art) <= PTR_SIZE, Art_IS_JUST_AN_OPAQUE_TYPE)

#endif /* AB_ART_HPP */
