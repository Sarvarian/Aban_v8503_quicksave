#ifndef AB_ASR_HPP
#define AB_ASR_HPP

#include "Main.hpp"

/** Aban Strong Renderer */
class Asr {
public:
  static  Asr* def();

  /** Always Returns null. */
  Asr* undef();

private:
  Asr();

  /** Use this to check if Vulkan is available att all.
   *  Return 0 will indicate no Vulkan support.
   *  \returns number of extensions available.
   */
  static u32 isVulkanInstanceExtensionsAvailable();

  static bool isOpenGL4Supported();

};

#endif /* AB_ASR_HPP */
