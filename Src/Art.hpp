#pragma once

#ifndef AB_ART_HPP
#define AB_ART_HPP

#include "Main.hpp"

/** Aban Runtime */
class Art {
public:

  /** \return Check return for null.
   * Exit as failure in case of null. */
  static Art* def();

  /** \return Always returns null. */
  Art* undef();

private:
  Art();
  class ArtCore* toCore();

};
staticAssert(sizeof(Art) <= PTR_SIZE, Art_IS_JUST_AN_OPAQUE_TYPE)

#endif /* AB_ART_HPP */
