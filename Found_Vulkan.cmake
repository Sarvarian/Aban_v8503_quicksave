
pkg_check_modules(VULKAN QUIET vulkan)

#                    Volk library uses minimum CMake 3.5 requirement.
if (VULKAN_FOUND AND (NOT CMAKE_VERSION VERSION_LESS 3.5))
  set(AB_VULKAN ON)
endif ()


if (AB_VULKAN)
  add_subdirectory(Lib/volk)
endif()
