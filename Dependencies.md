
# Dependencies

Required Build Tools:
- gcc, g++: Or compatible compilers like clang.
- CMake
- pkgconf, pkg-config

Required Library:
- SDL: SDL3 or SDL2 preferred. SDL1 can work on GNU/Linux but its features are limited.

Can be turned off:
- Vulkan: Vulkan dev files. Can be trun off by `AB_VULKAN` CMake option.

Already Included:
- Glad: OpenGL Loader
- Volk: Vulkan Loader
