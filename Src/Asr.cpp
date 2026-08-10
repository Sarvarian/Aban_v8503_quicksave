#include "Asr.hpp"

#include "Journal.hpp"

Asr::Asr() {
}

Asr* Asr::def() {
  return null;
}

Asr* Asr::undef() {
  return null;
}

u32 Asr::isVulkanInstanceExtensionsAvailable() {
  u32 count = 0;
#if AB_VULKAN
  const VkResult res = vkEnumerateInstanceExtensionProperties(null, &count, null);
  if (res != VK_SUCCESS) {
    Journal::vulkanEnumerateInstanceExtensionPropertiesCountFailed();
    debugBreak;
    return 0;
  }
#endif
  return count;
}

bool Asr::isOpenGL4Supported() {
  return false;
}

