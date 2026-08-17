#pragma once

#ifndef AB_ALL_HPP
#define AB_ALL_HPP

/** Aban Leagued Ledger */
class All {
public:
  /* System Error Begin */
  static void reportSystemError(const char* custom_message);
  /* System Error End */

  static void sdlInitFailed();
  static void vulkanEnumerateInstanceExtensionPropertiesCountFailed();
  static void firstPoolAllocationForArtFailed();

  static All def();

private:
  All();

};

#endif /* AB_ALL_HPP */
