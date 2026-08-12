#include "Apl.hpp"

#include "Ado.hpp"
#include "All.hpp"

Apl::Apl() {
}

Apl* Apl::def() {
  return null;
}

Apl* Apl::undef() {
  return null;
}

u32 Apl::isVulkanInstanceExtensionsAvailable() {
  u32 count = 0;
#if AB_VULKAN
  const VkResult res = vkEnumerateInstanceExtensionProperties(null, &count, null);
  if (res != VK_SUCCESS) {
    All::vulkanEnumerateInstanceExtensionPropertiesCountFailed();
    debugBreak;
    return 0;
  }
#endif
  return count;
}

bool Apl::isOpenGL4Supported() {
  return false;
}

