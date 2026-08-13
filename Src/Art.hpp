#pragma once

#ifndef AB_ART_HPP
#define AB_ART_HPP

#include "Main.hpp"

/** Aban Runtime */
class Art {
public:

  struct Step {
  public:
    u8 just_continue : 1;
    u8 calculate_delta_time : 1;
    u8 window_check : 1;
    u8 window_undef : 1;
    u8 window_def : 1;
    // ReSharper disable once CppDeclaratorNeverUsed
    u8 _pad03_ : 1;
    // ReSharper disable once CppDeclaratorNeverUsed
    u8 _pad02_ : 1;
    // ReSharper disable once CppDeclaratorNeverUsed
    u8 _pad01_ : 1;
    // ReSharper disable once CppDeclaratorNeverUsed
    u8 _pad00_[mmBufferSize(0) - 1];
  };
  staticAssert(sizeof(Step) == sizeof(Buffer0), Step_FIT_INTO_ONE_Buffer0)

  /** \return Check return for null.
   * Exit as failure in case of null. */
  static Art* def();

  /** \return Always returns null. */
  Art* undef();

protected:
  Art() { /* Empty */ };

};
staticAssert(sizeof(Art) <= PTR_SIZE, Art_IS_JUST_AN_OPAQUE_TYPE)

#endif /* AB_ART_HPP */
