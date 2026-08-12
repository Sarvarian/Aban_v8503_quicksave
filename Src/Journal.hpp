#pragma once

#ifndef AB_JOURNAL_HPP
#define AB_JOURNAL_HPP

class Journal {
public:
  static void sdlInitFailed();
  static void firstPoolAllocationFailed();
  static void vulkanEnumerateInstanceExtensionPropertiesCountFailed();
  static void firstPoolAllocationForArtFailed();
};

#endif /* AB_JOURNAL_HPP */
